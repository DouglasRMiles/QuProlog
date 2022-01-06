// qem.cc - Main function for the QuAM emulator.
//
// ##Copyright##
// 
// Copyright 2000-2016 Peter Robinson  (pjr@itee.uq.edu.au)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.00 
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// ##Copyright##
//
// $Id: qem.cc,v 1.33 2006/04/04 02:44:32 qp Exp $

#include <typeinfo>

#include <stdlib.h>
#ifdef WIN32
        #include <io.h>
        #include <fcntl.h>
        #include <signal.h>
        #define _WINSOCKAPI_
        #include <windows.h>
        #include <process.h>                          
        #include <winsock2.h>  
#else
        #include <unistd.h>
        #include <sys/utsname.h>
        #include <arpa/inet.h> 
#endif

#include <fcntl.h>

#include <sys/types.h>
#include <string.h>

#include <stdio.h>

#include "config.h"

#include "atom_table.h"
#include "code.h"
#include "defs.h"
#include "pedro_env.h"
#include "executable.h"
#include "interrupt_handler.h"
#include "io_qp.h"
#include "pred_table.h"
#include "protos.h"
#include "qem.h"
#include "qem_options.h"
#include "signals.h"
#include "scheduler_status.h"
#include "scheduler.h"
#include "thread_qp.h"
#include "thread_options.h"
#include "thread_table.h"
#include "user_hash_table.h"
#include "tcp_qp.h"
#include "timer.h"

const char *Program = "qem";

#ifdef WIN32
static void handle_sigint(int);

typedef int socklen_t;
SOCKADDR_IN addr;
SOCKET PipeOutSock;
SOCKET PipeInSock;
void Thread( void* pParams )
{ 
  extern bool in_sigint;;
  setvbuf(stdin, NULL, _IONBF, 0);
  PipeOutSock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

  if (connect(PipeOutSock, (SOCKADDR*)(&addr),sizeof(addr))==SOCKET_ERROR)
    {
      std::cout<<"client pipe connection failed\n";
      std::cout<<WSAGetLastError();
    }
  SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

  if (connect(Socket, (SOCKADDR*)(&addr),sizeof(addr))==SOCKET_ERROR)
    {
      std::cout<<"client connection failed\n";
      std::cout<<WSAGetLastError();
    }
  char buffer[100000];
  int c;
  int i;
  c = getchar();
  for (;;) {
    i = 0;
    buffer[i] = (char)c;
    while (c != '\n') {
      if (c == EOF) {
        if (!in_sigint) {
          i = 0;
          buffer[0] = 255;
          getchar(); 
          break;
        } else {
          i--;
        }
      }
      c = getchar();
      i++;
      buffer[i] = (char)c;
    }
    buffer[i+1] = '\0';
    send(Socket, buffer, strlen(buffer), 0);

    c = getchar();
  }
  
}

int gettimeofday(struct timeval * tp, void * tzp)
{
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    // This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
    // until 00:00:00 January 1, 1970
  // from https://stackoverflow.com/questions/10905892/equivalent-of-gettimeday-for-windows#26085827
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;

    GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;
}

// int gettimeofday(struct timeval* tp, void* tzp) {
//     DWORD t;
//     t = timeGetTime();
//     tp->tv_sec = t / 1000;
//     tp->tv_usec = t % 1000;
//     /* 0 indicates that the call succeeded. */
//     return 0;
// }
#endif

//
// Handler for out of memory via new
//
//typedef void (*new_handler) ();
//new_handler set_new_handler(new_handler p) throw();

void noMoreMemory()
{
   cerr << "No more memory available for " << Program << endl;
   abort();
}

AtomTable *atoms = NULL;
//Object **lib_path = NULL;
Code *code = NULL;
IOManager *iom = NULL;
SocketManager *sockm = NULL;
PredTab *predicates = NULL;
QemOptions *qem_options = NULL;
Scheduler *scheduler = NULL;
SchedulerStatus *scheduler_status = NULL;
Signals *signals = NULL;
ThreadTable *thread_table = NULL;
ThreadOptions *thread_options = NULL;
char *process_symbol = NULL;
char *initial_goal = NULL;
UserHashState* user_hash = new UserHashState(100, 10);
int errorno = 0;

int pedro_port = 0;
char* pedro_address = NULL;

CodeLoc failblock;
heapobject var_id_counter = 1;

PedroMessageChannel* pedro_channel = NULL;

TimerStack timerStack;

// In order that signals to unblock selects we create a pipe and write to
// it when a signal arrives. By putting the read end of the pipe in
// the file descriptor set of the select, the select will unblock
// when a signal arrives. 

// SIGINT signal handler
#ifdef WIN32
static void
handle_sigint(int)
{
  extern Signals *signals;
  if (signals != NULL) {
    char buff[128];
    buff[0] = 'a';
    buff[1] = '\n';
    buff[2] = '\0';
    signals->Increment(SIGINT);
    signals->Status().setSignals();
    clearerr(stdin);
    int res = send(PipeOutSock, buff, 2, 0);
    if (res != 2) cerr << "Signals:  can't write to socket" << res << endl;
  } else {
    cerr << "Signals are null" << endl;
  }
  (void)signal(SIGINT, handle_sigint);
}
#else
int *sigint_pipe;

static void
handle_sigint(int)
{
  extern Signals *signals;
  extern int *sigint_pipe;
  if (signals != NULL)
    {
      char buff[128];
      buff[0] = 'a';
      int res = write(sigint_pipe[1], buff, 1);
      if (res != 1) cerr << "Signals:  can't write to pipe" << endl;
      signals->Increment(SIGINT);
      signals->Status().setSignals();
    } else {
      cerr << "Signals are null" << endl;
    }
}
#endif


// Most of the data structures are dynamically allocated for 2 reasons:
// 1) The stack for the process might blow out;
// 2) In the future, we might consider ``detaching'' all the QuProlog threads.
int
main(int32 argc, char** argv)
{
  // set the out-of-memory handler
  std::set_new_handler(noMoreMemory);

  // Signal communication structure
  signals = new Signals;

#ifndef WIN32
  sigint_pipe = new int[2];
  int ret = pipe(sigint_pipe);
  if (ret == -1) {
   cerr << "Can't create signal pipe" << endl;
   abort();
  }
  fcntl(sigint_pipe[0], F_SETFL, O_NONBLOCK);
#endif

  // Signal communication structure
  signals = new Signals;


#ifdef WIN32
  (void) signal(SIGINT, handle_sigint);
#else
  // SIGINT signal handler
  //  
  sigset_t sigs;
  sigemptyset(&sigs);
  sigaddset(&sigs, SIGINT);

  struct sigaction sa;
  sa.sa_handler = handle_sigint;
  sa.sa_mask = sigs;
  sa.sa_flags = SA_RESTART;
#if !(defined(SOLARIS) || defined(FREEBSD) || defined(MACOSX))
  sa.sa_restorer = NULL;
#endif // !(defined(SOLARIS) || defined(FREEBSD) || defined(MACOSX))
  SYSTEM_CALL_LESS_ZERO(sigaction(SIGINT, &sa, NULL));
  //
  // End of SIGINT signal handler
#endif


  // Parse the options.
  qem_options = new QemOptions(argc, argv);

  if (! qem_options->Valid())
    {
      Usage(Program, qem_options->Usage());
    }

  thread_options = new ThreadOptions(*qem_options);
 
  // Allocate areas in the Qu-Prolog Abstract Machine.
  atoms = new AtomTable(qem_options->AtomTableSize(),
			qem_options->StringTableSize(),
			0);
  predicates = new PredTab(atoms, qem_options->PredicateTableSize());

  code = new Code(qem_options->CodeSize());
  // Load executable file.
  LoadExecutable(qem_options->QxFile(), *code, *atoms, *predicates);

  // Library path.
  //lib_path = new Object*;


  //const char *lp = getenv("QPLIBPATH");
  //if (lp == NULL)
  //  {
  //    Fatal(Program, " QPLIBPATH is undefined.");
  //  }
  //*lib_path = atoms->add(lp);

  // I/O management.

  // Set standard in to be non-blocking.
#ifdef WIN32
  //setvbuf(stdin, NULL, _IONBF, 0);
#else
  setbuf(stdin, NULL);
#endif
//  fflush(stdout);
  setvbuf(stdout, NULL, _IOLBF, 0);
//  fflush(stderr);
  setvbuf(stderr, NULL, _IONBF, 0);


#ifdef WIN32
  WSADATA WsaDat;
  if(WSAStartup(MAKEWORD(2,2),&WsaDat)!=0)
    {
      std::cout<<"WSA Initialization failed!\r\n";
      WSACleanup();
      return 0;
    }
					
  SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  if(Socket==INVALID_SOCKET)
    {
      std::cout<<"Socket creation failed.\r\n";
      WSACleanup();
      return 0;
    }
  //hostent* host = gethostbyname("");

  SOCKADDR_IN serverInf;				
  serverInf.sin_family=AF_INET;
  serverInf.sin_addr.s_addr= htonl(INADDR_LOOPBACK); //((struct in_addr *)(host->h_addr))->s_addr;
  serverInf.sin_port=0;
					
  if(bind(Socket,(SOCKADDR*)(&serverInf),sizeof(serverInf))==SOCKET_ERROR)
    {
      std::cout<<"Unable to bind socket!\r\n";
      WSACleanup();
      return 0;
    }
	
  if (listen(Socket,5)==SOCKET_ERROR)
    {
      std::cout<<"Can't listen\n";
      return 0;
    }
  int length = sizeof(addr);
  if (getsockname(Socket, (SOCKADDR*)(&addr),&length)==SOCKET_ERROR) {
    std::cout<<" Can't getsockname\n";
    return 0;
  }
  _beginthread( Thread, 0, NULL );
				
  PipeInSock=SOCKET_ERROR;
  while(PipeInSock==SOCKET_ERROR)
    {
      PipeInSock=accept(Socket,NULL,NULL);
    }
  SOCKET StdInSock=SOCKET_ERROR;
  while(StdInSock==SOCKET_ERROR)
    {
      StdInSock=accept(Socket,NULL,NULL);
    }
  QPifdstream *current_input_stream = new QPifdstream(StdInSock);
#else
  QPifdstream *current_input_stream = new QPifdstream(fileno(stdin));
#endif
  QPostream *current_output_stream = new QPostream(&cout);
  QPostream *current_error_stream = new QPostream(&cerr);

  iom = new IOManager(current_input_stream,
		      current_output_stream,
		      current_error_stream);

  sockm = new SocketManager();

  scheduler_status = new SchedulerStatus;

  failblock = new word8[4];
  failblock[0] = TRUST;
  failblock[1] = 0;
  failblock[2] = 0;
  failblock[3] = FAIL;
  
  if (qem_options->InitialFile() != NULL) {
    if (qem_options->InitialGoal() != NULL) {
      int sizeif = strlen(qem_options->InitialFile());
      int size = strlen(qem_options->InitialGoal()) + sizeif + 6;
      initial_goal = new char[size];
      strcpy(initial_goal, "['");
      strcpy(initial_goal+2, qem_options->InitialFile());
      strcpy(initial_goal+2+sizeif, "'],");
      strcpy(initial_goal+2+sizeif+3, qem_options->InitialGoal());
    }
    else {
      int sizeif = strlen(qem_options->InitialFile());
      initial_goal = new char[sizeif+6];
      strcpy(initial_goal, "['");
      strcpy(initial_goal+2, qem_options->InitialFile());
      strcpy(initial_goal+2+sizeif, "'].");
    }
  }
  else if (qem_options->InitialGoal() != NULL) {
      initial_goal = new char[strlen(qem_options->InitialGoal()) + 1];
      strcpy(initial_goal, qem_options->InitialGoal());
    }      

  // Thread table. 
  thread_table = new ThreadTable(qem_options->ThreadTableSize());
  // Build the scheduler.
  scheduler 
    = new Scheduler(*thread_options, *thread_table, *signals, *predicates);

  pedro_address = qem_options->PedroServer();
  pedro_port = qem_options->PedroPort();

  pedro_channel = new PedroMessageChannel(*thread_table, *iom);
  scheduler->getChannels().push_back(pedro_channel);
  if (qem_options->ProcessSymbol() != NULL) {
    process_symbol = new char[strlen(qem_options->ProcessSymbol()) + 1];
    strcpy(process_symbol, qem_options->ProcessSymbol());
    wordlong ip_address; 
    if (ip_to_ipnum(pedro_address, ip_address) == -1) {
      Fatal(__FUNCTION__, "Cannot get host address");
    }
    if (!pedro_channel->connect(pedro_port, ip_address)) {
      Fatal(__FUNCTION__, "Cannot connect to Pedro");
    }
    if (!pedro_channel->pedro_register(atoms->add(qem_options->ProcessSymbol()))) {
      Fatal(__FUNCTION__, "Cannot register");
    }   
  }
 

#ifdef DEBUG_SCHED
  printf("%s Before scheduler->Scheduler()\n", Program);
#endif

  // Run threads.
  scheduler->Schedule();

#ifdef DEBUG_SCHED
  printf("%s After scheduler->Scheduler()\n", Program);
#endif
  
  //exit(EXIT_SUCCESS);
  exit(errorno);
}



