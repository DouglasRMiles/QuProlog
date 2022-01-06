// system.cc - Functions which use system to call CShell commands and 
//             syscall to call system commands.
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
// $Id: system.cc,v 1.20 2006/02/02 02:20:13 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"
#include "system_support.h"

#include	<stdlib.h>
#include	<string.h>
#ifdef WIN32
#include <io.h>
#include <direct.h>
#include <windows.h>
#include <unistd.h>
#else
#include        <unistd.h>
#if defined(FREEBSD) || defined(MACOSX)
#include        <pthread.h>
#include        <signal.h>
#include <sys/wait.h>
#endif //defined(FREEBSD) || defined(MACOSX)
#endif

#include <sys/stat.h>

extern AtomTable *atoms;

extern	"C"	int mkstemp(char *);
#ifndef WIN32
#if defined(FREEBSD) || defined(MACOSX)
extern char **environ;
int bsd_system (char *command) {
  int pid, status;
  
  if (command == 0)
    return 1;
  pid = fork();
  if (pid == -1)
    return -1;
  if (pid == 0) {
    signal(SIGVTALRM, SIG_IGN);
    char *argv[4];
    argv[0] = "sh";
    argv[1] = "-c";
    argv[2] = command;
    argv[3] = 0;
    execve("/bin/sh", argv, environ);
    exit(127);
  }
  do {
    if (waitpid(pid, &status, 0) == -1) {
      if (errno != EINTR)
	return -1;
    } else
      return status;
  } while(1);
}

#endif //defined(FREEBSD) || defined(MACOSX)
#endif

#ifdef WIN32
void do_async_command(void* arg)
{
  system((char*)arg);
}


#endif

//
// psi_system(constant, var).
// X0 is a string for CShell commands. X1 is unified with the return
// value from the call to the function system.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_system(Object *& object1, Object *& object2)
{
  Object* val1 = heap.dereference(object1);

  assert(val1->isAtom());
#ifdef WIN32
  char* cmd = OBJECT_CAST(Atom*, val1)->getName();
  int len = strlen(cmd);
  if (len == 0) {
    return (RV_SUCCESS);
  }
  bool async;
  if (cmd[len-1] == '&') {
    cmd[len-1] = '\0';
    _beginthread(do_async_command,NULL,(void*)cmd);
    object2 = heap.newInteger(0);
  }
  else {
    object2 = 
      heap.newInteger(system(OBJECT_CAST(Atom*, val1)->getName()));
  }
#else
#if defined(FREEBSD) || defined(MACOSX)
  object2 = 
    heap.newInteger(bsd_system(OBJECT_CAST(Atom*, val1)->getName()));
#else
  object2 = 
    heap.newInteger(system(OBJECT_CAST(Atom*, val1)->getName()));
#endif //defined(FREEBSD) || defined(MACOSX)
#endif
  return (RV_SUCCESS);
}

//
// psi_access(atom, integer, var)
// Check the file in X0 whether has the mode in X1.  Return the result in X2.
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_access(Object *& object1, Object *& object2, Object *& object3)
{
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  assert(val1->isAtom());
  assert(val2->isShort());
  
// PORT
//#ifdef WIN32
//  string tmpstr = wordexp(atoms->getAtomString(val1));
//  const char* tmpcharptr = tmpstr.c_str();
//  object3 = heap.newInteger(access(tmpcharptr,val2->getInteger()));
//#else
//  object3 =
//    heap.newInteger(access(wordexp(atoms->getAtomString(val1)).c_str(),
//                           val2->getInteger()));
//#endif
  string filename = OBJECT_CAST(Atom*, val1)->getName();
  wordexp(filename);
  char file[1024];
  strcpy(file, filename.c_str());

  object3 =
    heap.newInteger(access(file, val2->getInteger()));

  return(RV_SUCCESS);
} 

Thread::ReturnValue
Thread::psi_absolute_path(Object *& object1, Object *& object2)
{
  Object* val1 = heap.dereference(object1);
  if (!val1->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    } 
  string filename = OBJECT_CAST(Atom*, val1)->getName();
  wordexp(filename);
  char file[1024];
  strcpy(file, filename.c_str());
  object2 = atoms->add(file); 
  return(RV_SUCCESS);
}

//
// psi_chdir(atom)
// Change directory to dir given by the argument
// mode(in)
//
Thread::ReturnValue	
Thread::psi_chdir(Object *& object1)
{
  Object* val1 = heap.dereference(object1);
  if (!val1->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  string dirname = OBJECT_CAST(Atom*, val1)->getName();
  wordexp(dirname);
  char dir[1024];
  strcpy(dir, dirname.c_str());

#ifdef WIN32
  return (BOOL_TO_RV(_chdir(dir) == 0));
#else
  return (BOOL_TO_RV(chdir(dir) == 0));
#endif
}

//
// psi_getcwd(atom)
// Get the current working directory
// mode(out)
//
Thread::ReturnValue	
Thread::psi_getcwd(Object *& object1)
{
#ifdef WIN32
  if (_getcwd(atom_buf1, 255) == NULL) return RV_FAIL;
#else
  if (getcwd(atom_buf1, 255) == NULL) return RV_FAIL;
#endif
  object1 = atoms->add(atom_buf1);
  return RV_SUCCESS;
}

//
// psi_mktemp(atom, var)
// Return a temporary file name.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_mktemp(Object *& object1, Object *& object2)
{
  Object* val1 = heap.dereference(object1);

  assert(val1->isAtom());
  
  strcpy(atom_buf1, OBJECT_CAST(Atom*, val1)->getName());
#ifdef WIN32
  (void)(_mktemp(atom_buf1));
#else
  int ret = mkstemp(atom_buf1);
  if (ret == -1) return(RV_FAIL);
#endif
  object2 = atoms->add(atom_buf1);
  
  return(RV_SUCCESS);
}

//
// psi_realtime(-Integer)
//
// Returns system time.
//
Thread::ReturnValue
Thread::psi_realtime(Object *& time_arg)
{
  time_arg = heap.newInteger(static_cast<qint64>(time((time_t *) NULL)));
  return RV_SUCCESS;
}

//
// psi_gmtime(?Integer, ?timestruct)
//
// psi_gmtime(Time, TimeStruct) succeeds if
// Time is the Unix Epoch time corresponding to the time given in
// TimeStruct which is of the form 
// time(Year, Mth, Day, Hours, Mins, Secs)
Thread::ReturnValue
Thread::psi_gmtime(Object *& time_obj, Object *& time_struct)
{
  Object* time_arg = heap.dereference(time_obj);
  Object* time_struct_arg = heap.dereference(time_struct);
  if (time_arg->isInteger())
    {
      time_t etime = (time_t)time_arg->getInteger();
      struct tm *tmtime = gmtime(&etime);
      Structure* t_struct = heap.newStructure(6);
      t_struct->setFunctor(atoms->add("time"));
      t_struct->setArgument(1, heap.newInteger(tmtime->tm_year));
      t_struct->setArgument(2, heap.newInteger(tmtime->tm_mon));
      t_struct->setArgument(3, heap.newInteger(tmtime->tm_mday));
      t_struct->setArgument(4, heap.newInteger(tmtime->tm_hour));
      t_struct->setArgument(5, heap.newInteger(tmtime->tm_min));
      t_struct->setArgument(6, heap.newInteger(tmtime->tm_sec));

      return BOOL_TO_RV(unify(t_struct, time_struct_arg));
    }
  else
    {
      if (!time_arg->isVariable())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 1);
	}
      if (!time_struct_arg->isStructure())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      Structure* t_struct = OBJECT_CAST(Structure*, time_struct_arg);
      if ((t_struct->getArity() != 6) || 
	  (t_struct->getFunctor()->variableDereference() 
	   != atoms->add("time")))
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      struct tm tmtime;
      Object* arg1 = t_struct->getArgument(1)->variableDereference();
      if (!arg1->isInteger())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_year = arg1->getInteger();
      Object* arg2 = t_struct->getArgument(2)->variableDereference();
      if (!arg2->isInteger())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_mon = arg2->getInteger();
      Object* arg3 = t_struct->getArgument(3)->variableDereference();
      if (!arg3->isInteger())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_mday = arg3->getInteger();
      Object* arg4 = t_struct->getArgument(4)->variableDereference();
      if (!arg4->isInteger())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_hour = arg4->getInteger();
      Object* arg5 = t_struct->getArgument(5)->variableDereference();
      if (!arg5->isInteger())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_min = arg5->getInteger();
      Object* arg6 = t_struct->getArgument(6)->variableDereference();
      if (!arg6->isInteger())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_sec = arg6->getInteger();

      tmtime.tm_isdst = 0;

      // Remember the current value for the TZ environment variable
      char* oldTZ = getenv("TZ");
      // Set TZ to UTC time
      char envstring[1000];
      sprintf(envstring, "TZ=UTC");
      (void)putenv(envstring);
      // In UTC time localtime and gmtime are the same and so mktime gives
      // the inverse of gmtime
      time_t etime = mktime(&tmtime);
      // Reset the TZ variable
      sprintf(envstring, "TZ=%s", oldTZ);
      (void)putenv(envstring);
      if (etime == (time_t)(-1))
        {
          PSI_ERROR_RETURN(EV_TYPE, 2);
        }
      Object* timet = heap.newInteger(static_cast<qint64>(etime));

      return BOOL_TO_RV(unify(time_arg, timet));
    }
}

//
// psi_localtime(?Integer, ?timestruct)
//
// psi_localtime(Time, TimeStruct) succeeds if
// Time is the Unix Epoch time corresponding to the time given in
// TimeStruct which is of the form 
// time(Year, Mth, Day, Hours, Mins, Secs, isdst)
Thread::ReturnValue
Thread::psi_localtime(Object *& time_obj, Object *& time_struct)
{
  Object* time_arg = heap.dereference(time_obj);
  Object* time_struct_arg = heap.dereference(time_struct);
  if (time_arg->isInteger())
    {
      time_t etime = (time_t)time_arg->getInteger();
      struct tm *tmtime = localtime(&etime);
      Structure* t_struct = heap.newStructure(7);
      t_struct->setFunctor(atoms->add("time"));
      t_struct->setArgument(1, heap.newInteger(tmtime->tm_year));
      t_struct->setArgument(2, heap.newInteger(tmtime->tm_mon));
      t_struct->setArgument(3, heap.newInteger(tmtime->tm_mday));
      t_struct->setArgument(4, heap.newInteger(tmtime->tm_hour));
      t_struct->setArgument(5, heap.newInteger(tmtime->tm_min));
      t_struct->setArgument(6, heap.newInteger(tmtime->tm_sec));
      t_struct->setArgument(7, heap.newInteger(tmtime->tm_isdst));

      return BOOL_TO_RV(unify(t_struct, time_struct_arg));
    }
  if (time_arg->isVariable())
    {
      if (!time_struct_arg->isStructure())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      Structure* t_struct = OBJECT_CAST(Structure*, time_struct_arg);
      if ((t_struct->getArity() != 7) || 
	  (t_struct->getFunctor()->variableDereference() 
	   != atoms->add("time")))
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      struct tm tmtime;
      Object* arg1 = t_struct->getArgument(1)->variableDereference();
      if (!arg1->isInteger())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_year = arg1->getInteger();
      Object* arg2 = t_struct->getArgument(2)->variableDereference();
      if (!arg2->isInteger())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_mon = arg2->getInteger();
      Object* arg3 = t_struct->getArgument(3)->variableDereference();
      if (!arg3->isInteger())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_mday = arg3->getInteger();
      Object* arg4 = t_struct->getArgument(4)->variableDereference();
      if (!arg4->isInteger())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_hour = arg4->getInteger();
      Object* arg5 = t_struct->getArgument(5)->variableDereference();
      if (!arg5->isInteger())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_min = arg5->getInteger();
      Object* arg6 = t_struct->getArgument(6)->variableDereference();
      if (!arg6->isInteger())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_sec = arg6->getInteger();
      Object* arg7 = t_struct->getArgument(7)->variableDereference();
      if (!arg7->isInteger())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      tmtime.tm_isdst = arg7->getInteger();
      
      time_t etime = mktime(&tmtime);
      if (etime == (time_t)(-1))
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      Object* timet = heap.newInteger(static_cast<qint64>(etime));
      return BOOL_TO_RV(unify(time_arg, timet));
    }
  PSI_ERROR_RETURN(EV_INST, 1);
}

// @user
// @pred signal_to_atom(SignalInteger, SignalAtom)
// @type signal_to_atom(integer, atom)
// @mode signal_to_atom(+, -) is det
// @description
// Takes a signal number and maps it to the appropriate signal string.
// @end pred
// @end user
Thread::ReturnValue
Thread::psi_signal_to_atom(Object *& signum, Object *& sigatom)
{
  Object* signum_arg = heap.dereference(signum);

  if (signum_arg->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!signum_arg->isInteger())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  const int sig = signum_arg->getInteger();

  if (sig <= 0 || sig > NSIG)
    {
      PSI_ERROR_RETURN(EV_RANGE, 1);
    }

  const char *str;

  switch (sig)
    {
      //    case SIGHUP: str = "SIGHUP"; break;
    case SIGINT: str = "SIGINT"; break;
#if 0
    case SIGQUIT: str = "SIGQUIT"; break;
    case SIGILL: str = "SIGILL"; break;
    case SIGTRAP: str = "SIGTRAP"; break;
    case SIGIOT: str = "SIGIOT"; break;
#if SIGABRT != SIGIOT
    case SIGABRT: str = "SIGABRT"; break;
#endif	// SIGABRT != SIGIOT
#ifdef SIGEMT
    case SIGEMT: str = "SIGEMT"; break;
#endif	// SIGEMT
    case SIGFPE: str = "SIGFPE"; break;
    case SIGKILL: str = "SIGKILL"; break;
    case SIGBUS: str = "SIGBUS"; break;
    case SIGSEGV: str = "SIGSEGV"; break;
#ifdef SIGSYS
    case SIGSYS: str = "SIGSYS"; break;
#endif	// SIGSYS
    case SIGPIPE: str = "SIGPIPE"; break;
    case SIGALRM: str = "SIGALRM"; break;
    case SIGTERM: str = "SIGTERM"; break;
    case SIGUSR1: str = "SIGUSR1"; break;
    case SIGUSR2: str = "SIGUSR2"; break;
	// SIGCLD
    case SIGCHLD: str = "SIGCHLD"; break;
#ifdef SIGPWR
    case SIGPWR: str = "SIGPWR"; break;
#endif	// SIGPWR
    case SIGWINCH: str = "SIGWINCH"; break;
    case SIGURG: str = "SIGURG"; break;
#ifdef SIGPOLL
    case SIGPOLL: str = "SIGPOLL"; break;
#endif	// SIGPOLL
#if SIGIO != SIGPOLL
    case SIGIO: str = "SIGIO"; break;
#endif	// SIGIO != SIGPOLL
    case SIGSTOP: str = "SIGSTOP"; break;
    case SIGTSTP: str = "SIGTSTP"; break;
    case SIGCONT: str = "SIGCONT"; break;
    case SIGTTIN: str = "SIGTTIN"; break;
    case SIGTTOU: str = "SIGTTOU"; break;
    case SIGVTALRM: str = "SIGVTALRM"; break;
    case SIGPROF: str = "SIGPROF"; break;
    case SIGXCPU: str = "SIGXCPU"; break;
    case SIGXFSZ: str = "SIGXFSZ"; break;
#ifdef SIGWAITING
    case SIGWAITING: str = "SIGWAITING"; break;
#endif	// SIGWAITING
#ifdef SIGLWP
    case SIGLWP: str = "SIGLWP"; break;
#endif	// SIGLWP
#ifdef SIGFREEZE
    case SIGFREEZE: str = "SIGFREEZE"; break;
#endif	// SIGFREEZE
#ifdef SIGTHAW
    case SIGTHAW: str = "SIGTHAW"; break;
#endif	// SIGTHAW
#ifdef SIGSTKFLT
    case SIGSTKFLT: str = "SIGSTKFLT"; break;
#endif 	// SIGSTKFLT
#ifdef SIGUNUSED
    case SIGUNUSED: str = "SIGUNUSED"; break;
#endif	// SIGUNUSED
#ifdef SIGINFO
    case SIGINFO: str = "SIGINFO"; break;
#endif	// SIGINFO
#endif // 0
    default:
      return RV_FAIL;
      break;
    }

  sigatom = atoms->add(str);

  return RV_SUCCESS;
}

// @doc
// @pred nsig(NSIG)
// @type nsig(integer)
// @mode nsig(-) is det
// @description
// Returns the number of signals on this machine.
// @end pred
// @end user
Thread::ReturnValue
Thread::psi_nsig(Object *& nsig)
{
  nsig = heap.newInteger(NSIG);

  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_strerror(Object *& errno_arg, Object *& string_arg)
{
  Object* errno_arg_value = heap.dereference(errno_arg);
  if (errno_arg_value->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!errno_arg_value->isInteger())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  const char *str = strerror(errno_arg_value->getInteger());
  if (str == NULL)
    {
      PSI_ERROR_RETURN(EV_VALUE, 1);
    }

  string_arg = atoms->add(str);

  return RV_SUCCESS;
}

// call stat function
Thread::ReturnValue
Thread::psi_stat(Object *& object1, Object *& object2)
{  

  Object* val1 = heap.dereference(object1);
  assert(val1->isAtom());

  string filename = OBJECT_CAST(Atom*, val1)->getName();
  wordexp(filename);
  char file[1024];
  strcpy(file, filename.c_str());

  struct stat stat_buff;
  if (stat(file, &stat_buff) == -1)
    return RV_FAIL;
  Structure* stat_struct = heap.newStructure(2);
  stat_struct->setFunctor(atoms->add("stat"));
  stat_struct->setArgument(1, heap.newInteger(stat_buff.st_mtime));
  stat_struct->setArgument(2, heap.newInteger(stat_buff.st_size));
  object2 = stat_struct;

  return RV_SUCCESS;

}



Thread::ReturnValue
Thread::psi_file_directory_name(Object *& object1, Object *& object2)
{
  Object* val1 = heap.dereference(object1);
  assert(val1->isAtom());

  string filename = OBJECT_CAST(Atom*, val1)->getName();
  wordexp(filename);
  size_t found = filename.find_last_of("/\\");
  string path = filename.substr(0,found);
  char tmpstr[1024];
  strcpy(tmpstr, path.c_str());
  object2 = atoms->add(tmpstr); 

  return RV_SUCCESS;

}


Thread::ReturnValue
Thread::psi_file_base_name(Object *& object1, Object *& object2)
{
  Object* val1 = heap.dereference(object1);
  assert(val1->isAtom());

  string filename = OBJECT_CAST(Atom*, val1)->getName();
  wordexp(filename);
  size_t found = filename.find_last_of("/\\");
  string file = filename.substr(found+1);
  char tmpstr[1024];
  strcpy(tmpstr, file.c_str());
  object2 = atoms->add(tmpstr); 

  return RV_SUCCESS;

}

  





