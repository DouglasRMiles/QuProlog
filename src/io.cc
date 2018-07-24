// io.cc -
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
// $Id: io.cc,v 1.30 2006/01/31 23:17:50 qp Exp $

#include <string.h>
// #include <stropts.h>
#include <fcntl.h>
#ifdef WIN32
        #include <time.h>
        #include <conio.h>
        #define _WINSOCKAPI_
        #include <windows.h>
        #include <winsock2.h>
        #include <io.h>
        typedef int socklen_t;
#else
        #include <sys/time.h>
        #include <sys/types.h>
#endif

#include "global.h"
#include "io_qp.h"
#include "protos.h"
#include "thread_qp.h"
#include "scheduler.h"
#include "signals.h"
#include "thread_table.h"
#include "pedro_env.h"
#include "write_support.h"

extern Scheduler *scheduler;
extern Signals *signals;
extern ThreadTable *thread_table;
extern ThreadOptions *thread_options;

//-----------------------------------------------
//
// Sockets
//
//-----------------------------------------------
Socket::Socket(const int t, const int p, const int f)
  : FD(f, QPSOCKET),
    sstatus(SS_INIT),
    smode(SM_INIT),
    stype(t),
    sproto(p),
    istream(-1),
    ostream(-1)
{
  if (t == SOCK_STREAM)
    {
      setConnection();
    }
  else
    {
      setConnectionless();
    }

  //
  // When the socket is closed or the process dies, make sure that we
  // can reuse the address.
  //
  int opt_val = 1;

  SYSTEM_CALL_LESS_ZERO(setsockopt(getFD(), SOL_SOCKET, SO_REUSEADDR,
				   (char *) &opt_val, sizeof(opt_val)));
}

bool
Socket::isConnectAllowed(void) const
{
  bool result = false;

  switch (smode)
    {
    case SM_INIT:
      result = false;
      break;
    case SM_CONNECTION:
    case SM_CONNECTIONLESS:
      result = (sstatus == SS_SOCKET ||	sstatus == SS_BIND);
      break;
    }

  return result;
}

bool
Socket::isSendtoAllowed(void) const
{
  bool result = false;

  switch (smode)
    {
    case SM_INIT:
      result = false;
      break;
    case SM_CONNECTION:
    case SM_CONNECTIONLESS:
      result = (sstatus == SS_SOCKET || sstatus == SS_BIND ||
		sstatus == SS_CONNECTED);
      break;
    }

  return result;
}

bool
Socket::isRecvfromAllowed(void) const
{
  bool result = false;

  switch (smode)
    {
    case SM_INIT:
      result = false;
      break;
    case SM_CONNECTION:
    case SM_CONNECTIONLESS:
      result = (sstatus == SS_SOCKET || sstatus == SS_BIND ||
		sstatus == SS_CONNECTED);
      break;
    }

  return result;
}

bool
Socket::isBroadcast(void) const
{
  int val;
  socklen_t len = sizeof(val);

  if (getsockopt(getFD(),
		 SOL_SOCKET, SO_BROADCAST, (char *)&val, &len))
    {
      return false;
    }

  return val != 0;
}

bool
Socket::openSocket(const int type, const int proto)
{
  stype = type;
  sproto = proto;

  setFD(static_cast<const int>(socket(AF_INET, type, proto)));

  setIStream(-1);
  setOStream(-1);

  if (getFD() < 0)
    return false;

  setSocket();
  return true;
}

bool
Socket::closeSocket(void)
{
  if (close(getFD()) < 0)
    return false;
  
  setClose();
  
  return true;
}

void
Socket::setAccepted(Socket *sock, const int new_fd)
{
  sock->setFD(new_fd);
  sock->setConnection();
  sock->setConnected();
}


bool
Socket::isEnded(void) const
{
  return sstatus == SS_CLOSED;
}

//-----------------------------------------------
//
// Streams
//
//-----------------------------------------------

QPStream::QPStream(IOType t):type(t),lineCounter(1)
{ 
  properties = new heapobject[Structure::size(7)]; 
}

void 
QPStream::setProperties(Object* prop)
{
  assert(prop->isStructure());
  // copy the tag
  properties[0] = *(reinterpret_cast<heapobject*>(prop));
  Object* propobject = reinterpret_cast<Object*>(properties);
  assert(propobject->isStructure());
  // copy functor and args
  for (u_int i = 0; i <= OBJECT_CAST(Structure*, propobject)->getArity(); i++)
    {
        OBJECT_CAST(Structure*, propobject)->setArgument(i, OBJECT_CAST(Structure*, prop)->getArgument(i)->variableDereference());
    }
}

void
QPStream::setRSProperties(void)
{
  // !! WARNING !! Do the following a different way
  // This sets up the structure tag and arity directly.
  properties[0] = (7 << 8) | 0x0000000CUL;
  assert(reinterpret_cast<Object*>(properties)->isStructure());
  Structure* propstr = reinterpret_cast<Structure*>(properties);
  propstr->setFunctor(atoms->add("$prop"));
  propstr->setArgument(1, atoms->add("read"));
  propstr->setArgument(2, atoms->add("input"));
  propstr->setArgument(3, atoms->add("string"));
  propstr->setArgument(4, atoms->add("none"));
  propstr->setArgument(5, atoms->add("error"));
  propstr->setArgument(6, atoms->add("false"));
  propstr->setArgument(7, atoms->add("test"));
}


Object* QPStream::getProperties(void)
{
  return (reinterpret_cast<Object*>(properties));
}


///////////////////////////////////////////////////////////
// QPistream
//////////////////////////////////////////////////////////

QPistream::QPistream(const char* file): QPStream(ISTREAM), stream(file) {}

bool QPistream::seekg(streampos pos, ios::seekdir d)
{ 
  return (!stream.seekg(pos, d).fail()); 
}

///////////////////////////////////////////////////////////
// QPistringstream
//////////////////////////////////////////////////////////

QPistringstream::QPistringstream(const string& buff)
  : QPStream(ISTRSTREAM), stream(buff) {}

///////////////////////////////////////////////////////////
// QPifstream
//////////////////////////////////////////////////////////

QPifdstream::QPifdstream(int f):  
  QPStream(IFDSTREAM), stream(""), fd(f), done_get(false) { }

bool QPifdstream::get(char& ch)
{
  if (done_get && eof())
    {
      get_read();
    }
  done_get = true;
  
  return (!stream.get(ch).fail());
}

int QPifdstream::get(void)
{
  if (done_get && eof())
    {
      get_read();
    }
  done_get = true;
  
  return (stream.get());
}

bool
QPifdstream::isReady(void)
{
  // Not at end of buffer so ready to read
  if (done_get && !eof()) return true;

  // otherwise use select to see if there is anything on low-level
  // stream - and if so transfer to buffer.

  if (is_ready(fd, IFDSTREAM))
    {
      get_read();
      return true;
    }
  else
    {
      return false;
    }
}

void
QPifdstream::get_read(void)
{
  assert(fd != NO_FD);
  char buff[BUFFSIZE];
  // read from fd
  #ifdef WIN32
  int buffsize = recv(fd, buff, BUFFSIZE-1, 0);
  if (buff[0] == -1) buff[0] = '\0';
  #else
  int buffsize = read(fd, buff, BUFFSIZE-1);
  #endif
  buff[buffsize] = '\0';
  //reset strin buffer
  stream.str(buff);
  stream.seekg(0, ios::beg);
  stream.clear();
  done_get = false;
}

///////////////////////////////////////////////////////////
// QPimstream
//////////////////////////////////////////////////////////
QPimstream::QPimstream(string addr, PedroMessageChannel* pc)
  : QPStream(IMSTREAM), 
    stream(""),
    sender(addr), 
    pedro_channel(pc),
    done_get(false) 
{ }

bool
QPimstream::msgReady(void) 
{ 
  return !message_strings.empty(); 
}

void 
QPimstream::pushString(string* st) 
{
  message_strings.push_back(st); 
}

bool 
QPimstream::get(char& ch)
{
  if (done_get && eof())
    {
      get_read();
    }
  done_get = true;
  
  return (!stream.get(ch).fail());
}

int 
QPimstream::get(void)
{
  if (done_get && eof())
    {
      get_read();
    }
  done_get = true;
  
  return (stream.get());
}


bool
QPimstream::isReady(void)
{
  if (done_get && !eof()) return true;

  if (message_strings.empty()) 
    {
      return false;
    }
  else
    {
      get_read();
      return true;
    }

}

bool
QPimstream::msg_ready(void)
{
  fd_set rfds, wfds;
  FD_ZERO(&rfds);
  FD_ZERO(&wfds);
  int max_fd = 0;
  pedro_channel->updateFDSETS(&rfds, &wfds, max_fd);
  timeval tv = { 0, 0 };
  int result = select(max_fd + 1, &rfds, &wfds, NULL, &tv);
  if (result) {
    pedro_channel->ShuffleMessages();
  }
  return !message_strings.empty();
}

void
QPimstream::get_read(void)
{
  assert(!message_strings.empty());
  
  string* msg = message_strings.front();
  stream.str(*msg);
  message_strings.pop_front();
  delete msg;
  stream.seekg(0, ios::beg);
  stream.clear();
  done_get = false;

}
///////////////////////////////////////////////////////////
// QPostream
//////////////////////////////////////////////////////////

QPostream::QPostream(const char* file, ios::openmode mode)
  : QPStream(OSTREAM), 
    can_delete(true) 
{
  stream = new ofstream(file, mode);
}
QPostream::QPostream(ostream* strmptr)
  : QPStream(OSTREAM),
    can_delete(false) 
{
  stream = strmptr;
}

///////////////////////////////////////////////////////////
// QPostringstream
//////////////////////////////////////////////////////////

QPostringstream::QPostringstream(): QPStream(OSTRSTREAM) {}

///////////////////////////////////////////////////////////
// QPofstream
//////////////////////////////////////////////////////////

QPofdstream::QPofdstream(int n)
  : QPStream(OFDSTREAM), 
    fd(n), 
    auto_flush(false) 
{}

bool 
QPofdstream::put(char ch)
{
  if (stream.put(ch).fail())
    {
      return false;
    }
  if (auto_flush || (ch == '\n'))
    {
      send();
    }
  return true;
}

void 
QPofdstream::operator<<(const char c)
{
  stream << c;
  if (auto_flush || (c == '\n'))
    {
      send();
    }
}

void 
QPofdstream::operator<<(const char* s)
{
  if (auto_flush)
    {
      stream << s;
      send();
    }
  else
    {
      const char* ptr = strrchr(s, '\n');
      if (ptr == NULL)
	{
	  stream << s;
	}
      else if ((ptr - s) == ((int)strlen(s) + 1))
	{
	  stream << s;
	  send();
	}
      else
	{
	  int len = static_cast<int>(ptr-s+1);
	  char* tmpbuff = new char[len+1];
	  strncpy(tmpbuff, s, len);
	  tmpbuff[len] = '\0';
	  stream << tmpbuff;
	  send();
	  stream << (ptr+1);
          delete tmpbuff;
	}
    }
}

void 
QPofdstream::operator<<(const long n)
{
  stream << n;
  if (auto_flush) send();
}

void 
QPofdstream::operator<<(const double n)
{
  stream << n;
  if (auto_flush) send();
}

const string 
QPofdstream::str(void)
{
  return stream.str();
}

void 
QPofdstream::flush(void)
{
  if (!auto_flush && (stream.str().length() != 0)) send();
}

bool 
QPofdstream::set_autoflush(void)
{
  auto_flush = true;
  return true;
}

void
QPofdstream::send(void)
{
  if (fd == NO_FD) return;
  u_int size = static_cast<u_int>(stream.str().length());
  // WIN CHANGE u_int res = write(fd, stream.str().data(), size);
  u_int res = ::send(fd, stream.str().data(), size, 0);
  if (res != size) {
	cerr << "IO:send: can't write to fd" << endl;
  }
  stream.str("");
}


///////////////////////////////////////////////////////////
// QPomstream
//////////////////////////////////////////////////////////

QPomstream::QPomstream(Object* to_th, Object* to_proc, Object* to_mach, 
		       PedroMessageChannel* pc)
  : QPStream(OMSTREAM),
    pedro_channel(pc), 
    auto_flush(false) 
{ 
  ostringstream strm;
  strm << "p2pmsg(";
  writeAtom(strm, to_th);
  strm << ':';
  writeAtom(strm, to_proc);
  strm << '@';
  writeAtom(strm, to_mach);
  strm  << ", '$stream':";
  writeAtom(strm, pedro_channel->getName());
  strm << "@";
  writeAtom(strm,pedro_channel->getHost());
  strm << ", \"";
  msg_header = strm.str();
}

bool 
QPomstream::put(char ch)
{
  if (stream.put(ch).fail())
    {
      return false;
    }
  if (auto_flush || (ch == '\n'))
    {
      send();
    }
  return true;
}

void 
QPomstream::operator<<(const char c)
{
  stream << c;
  if (auto_flush || (c == '\n'))
    {
      send();
    }
}

void 
QPomstream::operator<<(const char* s)
{
  if (auto_flush)
    {
      stream << s;
      send();
    }
  else
    {
      const char* ptr = strrchr(s, '\n');
      if (ptr == NULL)
	{
	  stream << s;
	}
      else if ((ptr - s) == ((int)strlen(s) + 1))
	{
	  stream << s;
	  send();
	}
      else
	{
	  int len = ptr-s+1;
	  char* tmpbuff = new char[len+1];
	  strncpy(tmpbuff, s, len);
	  tmpbuff[len] = '\0';
	  stream << tmpbuff;
	  send();
	  stream << (ptr+1);
          delete tmpbuff;
	}
    }
}

void 
QPomstream::operator<<(const long n)
{
  stream << n;
  if (auto_flush) send();
}

void 
QPomstream::operator<<(const double n)
{
  stream << n;
  if (auto_flush) send();
}

const string 
QPomstream::str(void)
{
  return stream.str();
}

void 
QPomstream::flush(void)
{
  if (!auto_flush && (stream.str().length() != 0)) send();
}

bool 
QPomstream::set_autoflush(void)
{
  auto_flush = true;
  return true;
}

void
QPomstream::send(void)
{
  string thechars = stream.str();
  addEscapes(thechars, '"');

  ostringstream strm;
  strm << msg_header
       << thechars
       << "\")\n";
  pedro_channel->send(strm.str());

  stream.str("");
  //if (pedro_channel->get_ack() == 0) {
  //  cerr << "BAD ACK" << endl;
  //}
}


///////////////////////////////////////////////////////////
// IOManager
//////////////////////////////////////////////////////////

IOManager::IOManager(QPStream *in, QPStream *out, QPStream *error)
{
  for (u_int i = 0; i < NUM_OPEN_STREAMS; i++)
    {
      open_streams[i] = NULL;
    }
  assert(in != NULL);
  assert(out != NULL);
  assert(error != NULL);
  save_stdin = in;
  save_stdout = out;
  save_stderr = error;
  open_streams[0] = in;
  open_streams[1] = out;
  open_streams[2] = error;
  current_input = 0;
  current_output = 1;
  current_error = 2;
}

bool
IOManager::updateStreamMessages(string& from_addr, string& message) 
{
  for (u_int i = 0; i < NUM_OPEN_STREAMS; i++)
    {
      if ((open_streams[i] != NULL) 
	  && (open_streams[i]->Type() == IMSTREAM)
	  && (open_streams[i]->getSender() == from_addr))
	{
	  // Found stream for from handle - extract message
	  // and push onto stream message list
	  string* new_string = new string(message);
	  open_streams[i]->pushString(new_string);
	  return true;
	}
    }
  return false;
}

int 
IOManager::OpenStream(QPStream* strm)
{
  u_int i;
  for (i = 0; i < NUM_OPEN_STREAMS; i++)
    {
      if (open_streams[i] == NULL)
	{
	  break;
	}
    }
  if (i == NUM_OPEN_STREAMS)
    {
      return -1;
    }
  open_streams[i] = strm;
  return i;
}

bool 
IOManager::CloseStream(u_int i)
{
  assert(i >= 0 && i < NUM_OPEN_STREAMS);
  assert(open_streams[i] != NULL);
  if (i < 3) return false; // Can't close std streams
  delete open_streams[i];
  open_streams[i] = NULL;
  return true;
}
  
QPStream* 
IOManager::GetStream(u_int i)
{
  assert(i >= 0 && i < NUM_OPEN_STREAMS);

  return (open_streams[i]);
}

bool 
IOManager::set_std_stream(int stdstrm, u_int i)
{
  if (stdstrm < 0 || stdstrm > 2)
    {
      return false;
    }
  if (i < 0 || i >=  NUM_OPEN_STREAMS || open_streams[i] == NULL)
    {
      return false;
    }
  if (open_streams[i]->getDirection() == 
      open_streams[stdstrm]->getDirection())
    {
      open_streams[stdstrm] = open_streams[i];
      open_streams[stdstrm]->setFD(stdstrm);
      //open_streams[i] = NULL;
      return true;
    }
  return false;
}

bool 
IOManager::reset_std_stream(int stdstrm)
{
  switch (stdstrm)
    {
    case 0:
      if (open_streams[0] == save_stdin)
	{
	  return false;
	}
      //delete open_streams[0];
      open_streams[0] = save_stdin;
      break;
    case 1:
      if (open_streams[1] == save_stdout)
	{
	  return false;
	}
      //delete open_streams[1];
      open_streams[1] = save_stdout;
      break;
    case 2:
      if (open_streams[2] == save_stderr)
	{
	  return false;
	}
      //delete open_streams[2];
      open_streams[2] = save_stderr;
      break;
    default:
      assert(false);
      return false;
    }
  return true;
}





bool
is_ready(const int fd, const IOType type)
{
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(fd, &fds);

  // Set up the time value to indicate a poll
  timeval tv = { 0, 0 };

  int result = 0;
  switch (type)
    {
    case IFDSTREAM:
      result = select(fd + 1, &fds, (fd_set *) NULL, (fd_set *) NULL, &tv);
      break;
    case OFDSTREAM:
      result = select(fd + 1, (fd_set *) NULL, &fds, (fd_set *) NULL, &tv);
      break;
    case QPSOCKET:
      result = select(fd + 1, &fds, (fd_set *) NULL, (fd_set *) NULL, &tv);
      break;
    default:
      assert(false);
      result = 0;
      break;
    }

  #ifdef DEBUG_IO
  cerr << __FUNCTION__ << "result = " << result << " FD_ISSET(%ld, ...) = " << FD_ISSET(fd, &fds) << '\n';
  #endif
  //#ifdef WIN32
  //  if (result == 0 || result == 128)
  //  {
  //         return 1;
          //  } else {
  //         return 0;
  // }
  //#else
  return result && FD_ISSET(fd, &fds);
  //#endif

}


