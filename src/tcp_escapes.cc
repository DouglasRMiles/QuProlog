//
// tcp_escapes.cc - TCP interface for Qu-Prolog.
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
// Prolog Primitives to support TCP comunication
//

#include "config.h"
#include "global.h"
#include "tcp_qp.h"

#ifdef WIN32
        #include <time.h>
        #include <winsock2.h>
        #define _WINSOCKAPI_
        #include <windows.h>
        typedef int socklen_t;

        //We also need to initialise the winsock tcp crud
        //WSADATA wsaData;
        // WORD wVersionRequested = MAKEWORD( 2, 2 );
        //int err = WSAStartup( wVersionRequested, &wsaData );

#else
        #include <sys/time.h>
        #include <sys/types.h>
        #include <netdb.h>
        #include <sys/socket.h>
        #include <sys/file.h>
        #include <sys/ioctl.h>
        #include <sys/un.h>
        #include <net/if.h>
        #include <netdb.h>
#endif

#include <sys/types.h>

#ifdef HAVE_SYS_FILIO_H
#include <sys/filio.h>
#endif	// HAVE_SYS_FILIO_H
#ifdef HAVE_SYS_SOCKIO_H
#include <sys/sockio.h>
#endif	// HAVE_SYS_SOCKIO_H
#include <fcntl.h>

#if defined(HAVE_POLL)
#if defined(LINUX)
#include <sys/poll.h>
#else
#include <poll.h>
#endif // defined(LINUX)
#endif // defined(HAVE_POLL)

#include <time.h>
#include <errno.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include <ctype.h>
#include <signal.h>

#include "arpa_inet.h"
#include "atom_table.h"
#include "is_ready.h"
#include "netinet_in.h"
#include "thread_qp.h"

extern IOManager *iom;
extern SocketManager *sockm;


//
// decode_socket decodes the socket number supplied in the cell,
// and checks whether it corresponds to a currently allocated
// socket.
//
// On success, it sets the Socket ** argument to the address of the
// appropriate socket object, and returns a value of EV_NO_ERROR.
// On failure, it returns the appropriate error value.
//
static ErrorValue
decode_socket(Heap& heap,
	      Object * socket_cell,
	      Socket **socket)
{
  *socket = (Socket *) NULL;

  if (socket_cell->isVariable())
    {
      return EV_INST;
    }
  else if (socket_cell->isNumber())
    {
      const int socket_number = socket_cell->getInteger();
      if (socket_number < 0 || socket_number >= (int)NUM_OPEN_SOCKETS)
	{
	  return EV_TYPE;
	}
      *socket = sockm->GetSocket(socket_number);
      if (*socket == NULL)
	{
	  return EV_TYPE;
	}
      return EV_NO_ERROR;
    }
  else
    {
      return EV_TYPE;
    }
}

//
// DECODE_SOCKET_ARG is a wrapper for calls to decode_socket()
//
#define DECODE_SOCKET_ARG(heap, cell, arg_num, socket)			\
  do {									\
    const ErrorValue result = decode_socket(heap, cell, &socket);	\
    if (result != EV_NO_ERROR)						\
      {									\
	PSI_ERROR_RETURN(result, arg_num);				\
      }									\
  } while (0)
  
//
// decode_port() decodes a port number from the supplied cell.
// On success, the u_short& argument is set to the port number
// and EV_NO_ERROR is returned.
// On failure, an appropriate error value is returned.
// The returned port is in network byte order.
//
static ErrorValue
decode_port(Heap& heap,
	    Object * port_cell,
	    u_short& port)	// Network byte order.
{
  port = 0;

  if (port_cell->isVariable())
    {
      return EV_INST;
    }
  else if (port_cell->isInteger())
    {
      port = htons((u_short)(port_cell->getInteger()));
      return EV_NO_ERROR;
    }
  else
    {
      return EV_TYPE;
    }
}

//
// DECODE_PORT_ARG is a wrapper for decode_port() calls.
//
#define DECODE_PORT_ARG(heap, cell, arg_num, port)		\
  do {								\
    const ErrorValue result = decode_port(heap, cell, port);	\
    if (result != EV_NO_ERROR)					\
      {								\
        PSI_ERROR_RETURN(result, arg_num);			\
      }								\
  } while (0)

//
// machine_ip_address() decodes an IP address from a supplied cell.
// On success, the IP address is returned.
// (The returned value is in network byte order.)
// On failure, a value of 0 (which is an invalid address) is returned.
//
static wordlong
machine_ip_address(Heap& heap,
		   AtomTable& atoms,
		   Object * addr)
{
  if (addr->isInteger())
    {
      return(htonl((wordlong)(addr->getInteger())));
    }
  else if (addr->isAtom())
    {
      wordlong ip_address;
      char hostname[1000];
      (void)strcpy(hostname, OBJECT_CAST(Atom*, addr)->getName());
      if (ip_to_ipnum(hostname, ip_address) == -1) {
        return 0;
      }
      return ip_address;
    }
  return 0;
      /*
      char hostname[1000];
      (void)strcpy(hostname, OBJECT_CAST(Atom*, addr)->getName());
      if (strcmp(hostname, "localhost") == 0)
	{
	  if (gethostname(hostname, 1000) != 0)
	    {
	      return 0;
	    }
	}
      hostent *hp = gethostbyname(hostname);
//       if (hp == NULL)
//       {
//         struct in_addr in;
//         in.s_addr = inet_addr(hostname);
//        hp = gethostbyaddr((char *) &in, sizeof(in), AF_INET);
//     }
	  

#ifndef WIN32
      endhostent();
#endif
      if (hp != NULL)
        {
          return(*(int *)hp->h_addr_list[0]);
        }
      else
        {
          return 0;
        }
    }
  else
    {
      return 0;
    }
      */
}

//
// decode_ip_address() decodes an IP address supplied in the Object *& 
// argument.
// On success, the Object *& argument is set to the IP address, and a value
// of EV_NO_ERROR is returned.
// On failure, an appropriate error value is returned.
// (The ip address is returned in network byte order.)
//
static ErrorValue
decode_ip_address(Heap& heap, AtomTable& atoms,
		  Object * ip_address_cell,
		  wordlong& ip_address)
{
  ip_address = INADDR_NONE;

  if (ip_address_cell->isVariable())
    {
      return EV_INST;
    }

  if (ip_address_cell->isInteger() || ip_address_cell->isAtom())
    {
      if (ip_address_cell == AtomTable::inaddr_any)
        {
          ip_address = INADDR_ANY;
          return EV_NO_ERROR;
        }
      ip_address = machine_ip_address(heap, atoms, ip_address_cell);
      if (ip_address)
        {
          return EV_NO_ERROR;
        }
      else
        {
          return EV_VALUE;
        }
    }
  else
    {
      return EV_TYPE;
    }
}

//
// DECODE_IP_ADDRESS_ARG is a wrapper for decode_ip_address() calls.
//
#define DECODE_IP_ADDRESS_ARG(heap, atoms, cell, arg_num, ip_address)	 \
  do {									 \
    const ErrorValue result = decode_ip_address(heap, atoms, cell, ip_address); \
    if (result != EV_NO_ERROR)						 \
      {									 \
        PSI_ERROR_RETURN(result, arg_num);				 \
      }									 \
  } while (0)


//
// @internaldoc
// @pred '$open_socket_stream'(Socket, IOMode, Stream)
// @mode '$tcp_connect1'(+, +, -)
// @type '$tcp_connect1'(Integer, Integer, StreamID)
// @description
// Open a stream for either reading or writing on the socket.
// @end pred
// @end internaldoc

Thread::ReturnValue
Thread::psi_open_socket_stream(Object *& socket_arg, Object *& mode_arg, 
			       Object *& stream_arg)
{
  assert(mode_arg->variableDereference()->isInteger());
  int mode = mode_arg->variableDereference()->getInteger();

  Object* argS = socket_arg->variableDereference();

  Socket *socket;

  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  switch (mode)
    {
    case AM_READ:
      {
        QPifdstream *stream = new QPifdstream(socket->getFD());
	
        //
        // Return index of the stream.
        //
	int streamno = iom->OpenStream(stream);
	socket->setIStream(streamno);
        stream_arg = heap.newInteger(streamno);
        return RV_SUCCESS;
      }
      break;
    case AM_WRITE:
      {
       QPofdstream *stream = new QPofdstream(socket->getFD());
       //stream->set_autoflush();
	
        //
        // Return index of the stream.
        //
	int streamno = iom->OpenStream(stream);
	socket->setOStream(streamno);
        stream_arg = heap.newInteger(streamno);
        return RV_SUCCESS;
      }
      break;
    case AM_APPEND:
      assert(false);
      break;
    }
  return RV_FAIL;
}

// @doc 
// @pred tcp_socket(Socket, Type, Protocol)
// @mode tcp_socket(-, +, +) is semidet
// @type tcp_socket(Integer, Atom, Atom)
// @description
// Corresponds to: socket(3N)
//
// Type is the atoms:
//  'sock_stream'
//
// Protocol is the atoms:
//  'ipproto_ip'
//
// We have commited ourselves to AF_INET family.
//
// Fails if the no socket can be allocated.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_tcp_socket(
	       Object *& socket_arg,
	       Object *& type_arg,
	       Object *& protocol_arg)
{
  Object* argT = heap.dereference(type_arg);
  Object* argP = heap.dereference(protocol_arg);

  if (argT->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (argP->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 3);
    }

  int type;
  
  if (argT->isAtom())
    {

      if (argT == AtomTable::sock_stream)
	{
	  type = SOCK_STREAM;
	}
      else
	{
	  PSI_ERROR_RETURN(EV_VALUE, 2);
	}
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  
  int protocol;

  if (argP->isAtom())
    {
      if (argP == AtomTable::ipproto_ip)
	{
	  protocol = IPPROTO_IP;
	}
      else 
	{
	  PSI_ERROR_RETURN(EV_VALUE, 3);
	}
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 3);
    }


  const int fd = static_cast<const int>(socket(AF_INET, type, protocol));
  if (fd < 0)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, errno);
    }

  Socket *socket = new Socket(type, protocol, fd);

  socket->setSocket();

  socket_arg = heap.newInteger(sockm->OpenSocket(socket));

  return RV_SUCCESS;
}

// @doc
// @pred tcp_setsockopt(Socket, Optname, Value)
// @mode tcp_setsockopt(+, +, +) is det
// @type tcp_setsockopt(Integer, Atom, Integer)
// @description
// Corresponds to: setsockopt(3N)
//
// Optname is one of following atoms:
//  'so_debug'		= turn on debugging info recording
//  'so_reuseaddr'	= allow local IPAddress reuse
//  'so_keepalive'	= keep connections alive
//  'so_dontroute'	= just use interface IPAddresses
//  'so_broadcast'	= permit sending of broadcast msgs
//  'so_oobinline'	= leave received OOB data in line
//  'so_sndbuf'		= size of send buffer
//  'so_rcvbuf'		= size of receive buffer
//  'so_sndtimeo'	= send timeout
//  'so_rcvtimeo'	= receive timeout
//
// For now we only support the SOL_SOCKET level
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_tcp_setsockopt(Object *& socket_arg, Object *& option_arg,
			   Object *& value_arg)
{
  Object* argS = heap.dereference(socket_arg);
  Object* argO = heap.dereference(option_arg);
  Object* argV = heap.dereference(value_arg);

  Socket *socket;

  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  if (argO->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (argV->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 3);
    }

  int opt;
  
  if (argO->isAtom())
    {
      if (argO == AtomTable::so_debug)
	{
	  opt = SO_DEBUG;
	}
      else if (argO == AtomTable::so_reuseaddr)
	{
	  opt = SO_REUSEADDR;
	}
      else if (argO == AtomTable::so_keepalive)
	{
	  opt = SO_KEEPALIVE;
	}
      else if (argO == AtomTable::so_dontroute)
	{
	  opt = SO_DONTROUTE;
	}
      else if (argO == AtomTable::so_broadcast)
	{
	  //opt = SO_BROADCAST;
	  return RV_FAIL;
	}
      else if (argO == AtomTable::so_oobinline)
	{
	  opt = SO_OOBINLINE;
	}
      else if (argO == AtomTable::so_sndbuf)
	{
	  opt = SO_SNDBUF;
	}
      else if (argO == AtomTable::so_rcvbuf)
	{
	  opt = SO_RCVBUF;
	}
#ifdef SO_SNDTIMEO
      else if (argO == AtomTable::so_sndtimeo)
	{
	  opt = SO_SNDTIMEO;
	}
#endif	// SO_SNDTIMEO
#ifdef SO_RCVTIMEO
      else if (argO == AtomTable::so_rcvtimeo)
	{
	  opt = SO_RCVTIMEO;
	}
#endif	// SO_RCVTIMEO
      else 
	{
	  PSI_ERROR_RETURN(EV_VALUE, 2);
	}
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  
  int val;

  if (argV->isInteger())
    {
      val = argV->getInteger();
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 3);
    }

  const int ret = setsockopt(socket->getFD(),
			     SOL_SOCKET, opt, (char *)&val, sizeof(val));
  if (ret < 0)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, errno);
    }
    
  return RV_SUCCESS;
}

// @doc 
// @pred tcp_getsockopt(Socket, Optname, Value)
// @mode tcp_getsockopt(+, +, -) is det
// @type tcp_getsockopt(Integer, Atom, Integer)
// @description
// Corresponds to: getsockopt(3N)
//
// Optname is one of following atoms:
//  'so_debug'		= turn on debugging info recording
//  'so_reuseaddr'	= allow local IPAddress reuse
//  'so_keepalive'	= keep connections alive
//  'so_dontroute'	= just use interface IPAddresses
//  'so_broadcast'	= permit sending of broadcast msgs
//  'so_oobinline'	= leave received OOB data in line
//  'so_sndbuf'		= size of send buffer
//  'so_rcvbuf'		= size of receive buffer
//  'so_sndtimeo'	= send timeout
//  'so_rcvtimeo'	= receive timeout
//  'so_error'		= get error status and clear
//  'so_type'		= get socket type
//
// For now we only support the SOL_SOCKET level
// @end doc
Thread::ReturnValue
Thread::psi_tcp_getsockopt(
		   Object *& socket_arg,
		   Object *& option_arg,
		   Object *& value_arg)
{
  Object* argS = heap.dereference(socket_arg);
  Object* argO = heap.dereference(option_arg);

  Socket *socket;

  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  if (argO->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }

  int opt = 0;

  if (argO->isAtom())
    {
      if (argO == AtomTable::so_debug)
	{
	  opt = SO_DEBUG;
	}
      else if (argO == AtomTable::so_reuseaddr)
	{
	  opt = SO_REUSEADDR;
	}
      else if (argO == AtomTable::so_keepalive)
	{
	  opt = SO_KEEPALIVE;
	}
      else if (argO == AtomTable::so_dontroute)
	{
	  opt = SO_DONTROUTE;
	}
      else if (argO == AtomTable::so_broadcast)
	{
	  opt = SO_BROADCAST;
	}
      else if (argO == AtomTable::so_oobinline)
	{
	  opt = SO_OOBINLINE;
	}
      else if (argO == AtomTable::so_sndbuf)
	{
	  opt = SO_SNDBUF;
	}
      else if (argO == AtomTable::so_rcvbuf)
	{
	  opt = SO_RCVBUF;
	}
#ifdef SO_SNDTIMEO
      else if (argO == AtomTable::so_sndtimeo)
	{
	  opt = SO_SNDTIMEO;
	}
#endif	// SO_SNDTIMEO
#ifdef SO_RCVTIMEO
      else if (argO == AtomTable::so_rcvtimeo)
	{
	  opt = SO_RCVTIMEO;
	}
#endif	// SO_RCVTIMEO
      else if (argO == AtomTable::so_error)
	{
	  opt = SO_ERROR;
	}
      else if (argO == AtomTable::so_type)
	{
	  opt = SO_TYPE;
	}
      else
	{
	  PSI_ERROR_RETURN(EV_VALUE, 2);
	}
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  
  int val;
  socklen_t len = sizeof(val);

  if (getsockopt(socket->getFD(), SOL_SOCKET, opt,
		 (char *)&val, &len))
    {
      PSI_ERROR_RETURN(EV_SYSTEM, errno);
    }

  value_arg = heap.newInteger(val);

  return RV_SUCCESS;
}

// @doc 
// @pred tcp_bind(Socket, Port, IPAddress)
// @mode tcp_bind(+, +, +) is det
// @type tcp_bind(Integer, Integer, IPAddress)
// @description
// Corresponds to: bind(3N)
//
// Bind the socket to the specified port and address.
//
// An IPAddress is either an integer or the atom 'inaddr_any'.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_tcp_bind(Object *& socket_arg,
		     Object *& port_arg,
		     Object *& ip_address_arg)
{
  Object* argS = heap.dereference(socket_arg);
  Object* argP = heap.dereference(port_arg);
  Object* argA = heap.dereference(ip_address_arg);

  Socket *socket = NULL;
  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  u_short port = 0;
  DECODE_PORT_ARG(heap, argP, 2, port);

  wordlong ip_address = 0;
  DECODE_IP_ADDRESS_ARG(heap, *atoms, argA, 3, ip_address);

  if (!socket->isBindAllowed())
    {
      PSI_ERROR_RETURN(EV_NOT_PERMITTED, 1);
    }
  
  struct sockaddr_in server;
  
  server.sin_family = AF_INET;
  //server.sin_addr.s_addr = htonl((wordlong)ip_address);
  //server.sin_port = htons((u_short)port);
  server.sin_addr.s_addr = ((wordlong)ip_address);
  server.sin_port = ((u_short)port);

  const int ret = ::bind(socket->getFD(),
			 (struct sockaddr *) &server, sizeof(server));
  if (ret < 0)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, errno); 
    }

  socket->setBind();

  return RV_SUCCESS;
}

// @doc
// @pred tcp_listen(Socket)
// @mode tcp_listen(+) is det
// @type tcp_listen(Integer)
// @description
// Corresponds to: listen(3N)
//
// Set the length of the sockets queue for incoming requests to 5.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_tcp_listen(Object *& socket_arg)
{
  Object* argS = heap.dereference(socket_arg);
  
  Socket *socket;
  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  if (!socket->isListenAllowed())
    {
      PSI_ERROR_RETURN(EV_NOT_PERMITTED, 1);
    }

  const int ret = listen(socket->getFD(), 5);
  if (ret < 0)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, errno);
    }

  socket->setListen();

  return RV_SUCCESS;
}

//  @user
//  @pred tcp_accept(Socket, NewSocket, Port, IPAddress)
//  @type tcp_accept(Integer, Integer, Integer, IPAddress)
//  @mode tcp_accept(+, -, -, -, +) is semidet
//  @description
//  Corresponds to: accept(3N)
//  
//  An IPAddress is an integer or the atom 'inaddr_any'.
//  
//  Accept a connection to the given socket.
//  @internal
//  Implemented directly by pseudo-instruction.
//  @end internal
//  @end pred
//  @end user
Thread::ReturnValue
Thread::psi_tcp_accept(Object *& socket_arg,
		       Object *& new_socket_arg,
		       Object *& port_arg,
		       Object *& ip_address_arg)
{
  Object* argS = heap.dereference(socket_arg);

  Socket *socket;

  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  if (!socket->isAcceptAllowed())
    {
      PSI_ERROR_RETURN(EV_NOT_PERMITTED, 1);
    }
  
  IS_READY_SOCKET(socket);
  struct sockaddr_in add;
  socklen_t length = sizeof(struct sockaddr_in);
  
  const int newsockfd = static_cast<const int>(accept(socket->getFD(),
			       (struct sockaddr *) &add,
			       &length));
  if (newsockfd < 0)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, errno);
    }
  
  Socket *newsocket = new Socket(0, 0, newsockfd);
  socket->setAccepted(newsocket, newsockfd);
  new_socket_arg = heap.newInteger(sockm->OpenSocket(newsocket));
  port_arg = heap.newInteger(ntohs(add.sin_port));
  ip_address_arg = heap.newInteger(ntohl(add.sin_addr.s_addr));

  return RV_SUCCESS;
}

// @internaldoc
// @pred '$tcp_connect1'(Socket, Port, IPAddress)
// @mode '$tcp_connect1'(+, +, +)
// @type '$tcp_connect1'(Integer, Integer, IPAddress)
// @description
// Start off the connect() call. What will generally happen is that we'll
// get an all clear or EINPROGRESS return, both of which are (potentially)
// good news.
// @end pred
// @end internaldoc
Thread::ReturnValue
Thread::psi_tcp_connect1(
		 Object *& socket_arg,
		 Object *& port_arg,
		 Object *& ip_address_arg)
{
  Object* argS = heap.dereference(socket_arg);
  Object* argP = heap.dereference(port_arg);
  Object* argA = heap.dereference(ip_address_arg);

  Socket *socket = NULL;
  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  u_short port = 0;
  DECODE_PORT_ARG(heap, argP, 2, port);

  wordlong ip_address = 0;
  DECODE_IP_ADDRESS_ARG(heap, *atoms, argA, 3, ip_address);

  if (!socket->isConnectAllowed())
    {
      PSI_ERROR_RETURN(EV_NOT_PERMITTED, 1);
    }

  if (do_connection(socket->getFD(), port, ip_address))
    {
    return RV_SUCCESS;
    }
  else
    {
      PSI_ERROR_RETURN(EV_SYSTEM, errno);
    }
}

// @internaldoc
// @pred '$tcp_connect2'(Socket)
// @mode '$tcp_connect2'(+, +)
// @type '$tcp_connect2'(Integer)
// @description
// Polls the socket to see if the earlier connect() has finally gone through.
// @end pred
// @end internaldoc
Thread::ReturnValue
Thread::psi_tcp_connect2(Object *& socket_arg)
{
  Object* argS = heap.dereference(socket_arg);

  Socket *socket;

  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  int fd = socket->getFD();
  
  fd_set fds;

  FD_ZERO(&fds);
  FD_SET(fd, &fds);

#ifndef NDEBUG
  int result = select(fd + 1, (fd_set *) NULL, &fds, (fd_set *) NULL, NULL);
#else
  select(fd + 1, (fd_set *) NULL, &fds, (fd_set *) NULL, NULL);
#endif

  assert(result && FD_ISSET(fd, &fds));
		

  socket->setConnected();

  return RV_SUCCESS;
}

// @doc
// @pred tcp_checkconn(Socket)
// @mode tcp_checkconn(+) is semidet
// @type tcp_checkconn(Integer)
// @description
// Succeeds if the socket is in a state that allows connection; fails otherwise.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_tcp_checkconn(Object *& socket_arg)
{
  Object* argS = heap.dereference(socket_arg);

  Socket *socket;
  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  socket->setConnected();

  return RV_SUCCESS;
}

// @doc
// @pred tcp_close(Socket)
// @mode tcp_close(+) is det
// @type tcp_close(Integer)
// @description
// Corresponds to: close(2)
//
// Close the socket.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_tcp_close(
	      Object *& socket_arg)
{
  Object* argS = heap.dereference(socket_arg);

  Socket *socket;
  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  if (socket->getIStream() != -1)
    {
      iom->CloseStream(socket->getIStream());
      socket->setIStream(-1);
    }
  if (socket->getOStream() != -1)
    {
      iom->CloseStream(socket->getOStream());
      socket->setOStream(-1);
    }

  socket->closeSocket();
  sockm->CloseSocket(argS->getInteger());

  delete socket;

  return RV_SUCCESS;
}

// @doc
// @pred tcp_getsockname(Socket, Port, IPAddress)
// @mode tcp_getsockname(+, -, -) is det
// @type tcp_getsockname(Integer, Integer, Integer)
// @description
// Corresponds to: getsockname(3N)
//
// Return the local port and IP address associated with the socket.
// @end pred
// @end doc 
Thread::ReturnValue
Thread::psi_tcp_getsockname(
		    Object *& socket_arg,
		    Object *& port_arg,
		    Object *& ip_address_arg)
{
  Object* argS = heap.dereference(socket_arg);

  Socket *socket;
  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  sockaddr_in addr;
  socklen_t length = sizeof(struct sockaddr_in);

  if (getsockname(socket->getFD(),(struct sockaddr *)&addr,&length) < 0)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, errno);
    }
  if (gethostname(io_buf, IO_BUF_LENGTH) < 0)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, errno);
    }
  wordlong ip_address;

  if (ip_to_ipnum(io_buf, ip_address) == -1)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, errno);
    }
  port_arg = heap.newInteger(ntohs(addr.sin_port));
  ip_address_arg = heap.newInteger(ntohl(ip_address));

  return RV_SUCCESS;
}

// @doc
// @pred tcp_getpeername(Socket, Port, IPAddress)
// @mode tcp_getpeername(+, -, -) is det
// @type tcp_getpeername(Integer, Integer, Integer) 
// @description
// Corresponds to: getpeername(3N)
//
// Return the remote port and IP address associated with the socket.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_tcp_getpeername(
		    Object *& socket_arg,
		    Object *& port_arg,
		    Object *& ip_address_arg)
{
  Object* argS = heap.dereference(socket_arg);

  Socket *socket;
  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  struct sockaddr_in addr;
  socklen_t length = sizeof(struct sockaddr_in);

  if (getpeername(socket->getFD(),(struct sockaddr *)&addr,&length) < 0)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, errno);
    }

  port_arg = heap.newInteger(ntohs(addr.sin_port));

  ip_address_arg = heap.newInteger(ntohl(addr.sin_addr.s_addr));

  return RV_SUCCESS;
}

// @doc
// @pred tcp_host_to_ip_address(Name, IPAddress)
// @mode tcp_host_to_ip_address(+, -) is det
// @type tcp_host_to_ip_address(Atom, Integer)
// @description
// Corresponds to: nslookup(1N)
//
// Looks up the IP address of the given host.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_tcp_host_to_ip_address(Object *& host_arg,
				      Object *& ip_address_arg)
{
  Object* argH = heap.dereference(host_arg);

  if (argH->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!argH->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  char hostname[1000];
  (void)strcpy(hostname, OBJECT_CAST(Atom*, argH)->getName());
  if (strcmp(hostname, "localhost") == 0)
    {
      if (gethostname(hostname, 1000) != 0)
	{
	  PSI_ERROR_RETURN(EV_SYSTEM, errno);
	}
    }
  /*
  hostent *hp = gethostbyname(hostname);

//   if (hp == NULL)
//     {
//       struct in_addr in;
//       in.s_addr = inet_addr(hostname);
//       hp = gethostbyaddr((char *) &in, sizeof(in), AF_INET);
//     }
  if (hp == NULL)
    {
      strcpy(hostname, "127.0.0.1");
      getIPfromifconfig(hostname);
      struct in_addr in;
      #ifndef WIN32
      in.s_addr = inet_addr(hostname);
      hp = gethostbyaddr((char *) &in, sizeof(in), AF_INET);
      #endif
    }
  if (hp == NULL)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, errno);
    }
#ifndef WIN32
  endhostent();
#endif
 ip_address_arg =  heap.newInteger(ntohl(*(int *)hp->h_addr_list[0]));
  */
  wordlong ip_num;
  ip_to_ipnum(hostname, ip_num);
  ip_address_arg =  heap.newInteger(ntohl((int)ip_num));
  return RV_SUCCESS;
}

// @doc
// @pred tcp_host_from_ip_address(Name, IPAddress)
// @mode tcp_host_from_ip_address(-, +) is det
// @type tcp_host_from_ip_address(Atom, Integer)
// @description
// Corresponds to: nslookup(1N)
//
// Looks up the host name for the machine with the supplied IP address.
// (Input ip address is in host byte order.)
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_tcp_host_from_ip_address(Object *& host_arg,
				     Object *& ip_address_arg)
{
  Object* argA = heap.dereference(ip_address_arg);

  if (!argA->isInteger()) {
    PSI_ERROR_RETURN(EV_TYPE, 2);
  }
  wordlong ip_address = htonl((wordlong)(argA->getInteger()));
  char ip[200];
  if (ipnum_to_ip(ip_address, ip) == -1) {
    PSI_ERROR_RETURN(EV_SYSTEM, errno);
  }
  host_arg = atoms->add(ip);
  /*
  DECODE_IP_ADDRESS_ARG(heap, *atoms, argA, 2, ip_address);
    
  struct hostent *hp =
    gethostbyaddr((char *)&ip_address, sizeof(ip_address), AF_INET);
#ifndef WIN32
  endhostent();
#endif
  if (hp == NULL)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, errno);
    }
  hostent *hp2 = gethostbyname(hp->h_name);
  //if ((hp2 == NULL) or (ip_address != (wordlong)(*(int *)hp->h_addr_list[0])))
  if ((hp2 == NULL) or !streq(hp->h_name, hp2->h_name))
    {
      char ip_name[50];
      int p1 = ip_address >> 24;
      int p2 = (ip_address >> 16) & 0xff;
      int p3 = (ip_address >> 8) & 0xff;
      int p4 = ip_address & 0xff;
      sprintf(ip_name, "%d.%d.%d.%d", p4,p3,p2,p1);
      host_arg = atoms->add(ip_name);
    }
  else
    {
      host_arg = atoms->add(hp->h_name);
    }
  */
  return RV_SUCCESS;
}

// @internaldoc
// @pred '$tcp_service_to_proto_port'(Service, Protocol, Port)
// @mode '$tcp_service_to_proto_port'(+, -, -) is det
// @type '$tcp_service_to_proto_port'(Atom, Atom, Integer)
// @end pred
// @end internaldoc
Thread::ReturnValue
Thread::psi_tcp_service_to_proto_port(
			      Object *& service_arg,
			      Object *& proto_arg,
			      Object *& port_arg)
{
  Object* argS = heap.dereference(service_arg);

  if (argS->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!argS->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  char * proto = NULL;

  servent *sp =
    getservbyname(OBJECT_CAST(Atom*, argS)->getName(), proto);
#ifndef WIN32
  (void) endservent();
#endif
  if (!sp)
    {
      return RV_FAIL;
    }
  
  port_arg = heap.newInteger(ntohs(sp->s_port));
  proto_arg = atoms->add(sp->s_proto);
  
  return RV_SUCCESS;
}
  
// @internaldoc
// @pred '$tcp_service_proto_to_port'(Service, Protocol, Port)
// @mode '$tcp_service_proto_to_port'(+, +, -) is det
// @type '$tcp_service_proto_to_port'(Atom, Atom, Integer)
// @end pred
// @end internaldoc
Thread::ReturnValue
Thread::psi_tcp_service_proto_to_port(
			       Object *& service_arg,
			       Object *& proto_arg,
			       Object *& port_arg)
{
  Object* argS = heap.dereference(service_arg);
  Object* argPr = heap.dereference(proto_arg);

  if (argS->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!argS->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  if (argPr->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!argPr->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  const char *proto = OBJECT_CAST(Atom*, argPr)->getName();

  servent *sp = getservbyname(OBJECT_CAST(Atom*, argS)->getName(), proto);
#ifndef WIN32
  (void) endservent();
#endif

  if (!sp)
    {
      return RV_FAIL;
    }
  
  //port_arg = heap.newInteger(sp->s_port);
  port_arg = heap.newInteger(ntohs(sp->s_port));

  return RV_SUCCESS;
}

// @internaldoc
// @pred '$tcp_service_from_proto port'(Service, Proto, Port)
// @mode '$tcp_service_from_proto_port'(-, -, +) is det
// @type '$tcp_service_from_proto_port'(Atom, Integer, Integer)
// @end pred
// @end internaldoc
Thread::ReturnValue
Thread::psi_tcp_service_from_proto_port(
				 Object *& service_arg,
				 Object *& proto_arg,
				 Object *& port_arg)
{
  Object* argPr = heap.dereference(proto_arg);
  Object* argPo = heap.dereference(port_arg);
  
  u_short port;
  DECODE_PORT_ARG(heap, argPo, 3, port);
  if (argPr->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!argPr->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  const char *proto = OBJECT_CAST(Atom*, argPr)->getName();
  
  servent *sp = getservbyport(port, proto);
#ifndef WIN32
  (void) endservent();
#endif
  if (!sp)
    {
      return RV_FAIL;
    }

  service_arg = atoms->add(sp->s_name);

  return RV_SUCCESS;
}

// @internaldoc
// @pred '$tcp_service_from_proto_port'(Service, Proto, Port)
// @mode '$tcp_service_from_proto_port'(-, -, +) is det
// @type '$tcp_service_from_proto_port'(Atom, Integer, Integer)
// @end pred
// @end internaldoc
Thread::ReturnValue
Thread::psi_tcp_service_proto_from_port(
				 Object *& service_arg,
				 Object *& proto_arg,
				 Object *& port_arg)
{
  Object* argPo = heap.dereference(port_arg);

  u_short port;
  DECODE_PORT_ARG(heap, argPo, 3, port);
//  if (argPo->isVariable())
//    {
//      PSI_ERROR_RETURN(EV_INST, 2);
//    }
//  if (!argPo->isInteger())
//    {
//      PSI_ERROR_RETURN(EV_TYPE, 2);
//    }

  const char *proto = NULL;

//  const u_short port = (u_short)argPo->getInteger();
  servent *sp = getservbyport(port, proto);
#ifndef WIN32
  (void) endservent();
#endif
  if (!sp)
    {
      return RV_FAIL;
    }

  service_arg = atoms->add(sp->s_name);
  proto_arg = atoms->add(sp->s_proto);
  
  return RV_SUCCESS;
}


// @doc
// @pred tcp_is_socket(Socket)
// @mode tcp_is_socket(+) is semidet
// @type tcp_is_socket(Integer)
// @description
// Succeeds if its argument is a valid socket descriptor; fails otherwise.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_tcp_is_socket(Object *& socket_arg)
{
  Socket *socket;
  const ErrorValue ev = decode_socket(heap, socket_arg->variableDereference(),
				      &socket);

  return ev == EV_NO_ERROR ? RV_SUCCESS : RV_FAIL;
}


Thread::ReturnValue 
Thread::psi_select(Object *& in, Object *& out)
{
  Object* sockets = in->variableDereference();
  Object* next = sockets;
  fd_set fds;

  FD_ZERO(&fds);
  int max_fd = 0;

  while (next->isCons())
    {
      Cons* lst = OBJECT_CAST(Cons*, next);
      Object* head = lst->getHead()->variableDereference();
      next = lst->getTail()->variableDereference();
      Socket *socket;
      
      DECODE_SOCKET_ARG(heap, head, 1, socket);
      int fd = socket->getFD();
      if (fd > max_fd) max_fd = fd;
      FD_SET(fd, &fds);
    }
  if (max_fd == 0) return RV_FAIL;
  int result = select(max_fd+1, &fds, NULL, NULL, NULL);
  if (result <= 0) return RV_FAIL;

  out = AtomTable::nil;
  next = sockets;
  while (next->isCons())
    {
      Cons* lst = OBJECT_CAST(Cons*, next);
      Object* head = lst->getHead()->variableDereference();
      next = lst->getTail()->variableDereference();
      Socket *socket;
      
      DECODE_SOCKET_ARG(heap, head, 1, socket);
      int fd = socket->getFD();

      if (FD_ISSET(fd, &fds) != 0)
	{
	  Cons* tmp = heap.newCons(head, out);
	  out = tmp;
	}
    }
  return RV_SUCCESS;
}


Thread::ReturnValue 
Thread::psi_socket_fd(Object *&socket_arg, Object *&fd_arg)
{
  Object* argS = socket_arg->variableDereference();

  Socket *socket;

  DECODE_SOCKET_ARG(heap, argS, 1, socket);

  fd_arg = heap.newInteger(socket->getFD());

  return RV_SUCCESS;
}
