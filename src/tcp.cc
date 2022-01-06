// tcp.cc -
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
// $Id: tcp.cc,v 1.9 2005/08/31 03:20:19 qp Exp $

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef WIN32
        #include <io.h>
        #define _WINSOCKAPI_
        #include <windows.h>
        #include <winsock2.h>
#define _WIN32_WINNT 0x501
        #include <ws2tcpip.h>
        typedef int socklen_t;
#else
        #include <unistd.h>
        #include <sys/types.h>
        #include <sys/socket.h>
        #include <netinet/in.h>
        #include <arpa/inet.h>
        #include <netdb.h>
        #include <sys/utsname.h>
        #include <netdb.h>
        #include <sys/ioctl.h>
        #include <net/if.h>
        #include <ifaddrs.h>
#endif

//#include <netinet/in.h>

#include "netinet_in.h"
#include "tcp_qp.h"
#include "errors.h"


extern const char *Program;

//
// Convert from ip address to network order number for the IP
//
int
ip_to_ipnum(char* ip, wordlong& ipnum)
{
  struct addrinfo *ailist;
  struct addrinfo hint;
  struct sockaddr_in *sinp;

  hint.ai_flags = AF_INET; 
  hint.ai_family = AF_INET;
  hint.ai_socktype = 0;
  hint.ai_protocol = 0;
  hint.ai_addrlen = 0;
  hint.ai_canonname = NULL;
  hint.ai_addr = NULL;
  hint.ai_next = NULL;
  int rv;
  rv = getaddrinfo(ip, 0, &hint, &ailist);
  if (rv != 0) {
    freeaddrinfo(ailist);
    return -1;
  }
  struct addrinfo *res;
  for (res = ailist; res != NULL; res = res->ai_next)
    {
      if (res->ai_family == AF_INET) {
        sinp = (struct sockaddr_in *)res->ai_addr;
        wordlong a = (wordlong)(sinp->sin_addr.s_addr);
        freeaddrinfo(ailist);
        ipnum = a;
        return 0;
      }
    }
  freeaddrinfo(ailist);
  return -1;
}

//
// Inverse of above
//
int 
ipnum_to_ip(wordlong ipnum, char* ip)
{
  struct sockaddr_in addr;    
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = ipnum;
  addr.sin_port = 0;

  char hbuf[NI_MAXHOST];

   if (getnameinfo((struct sockaddr*)&addr, sizeof (struct sockaddr), hbuf, 
                  sizeof(hbuf), NULL,
                  0, NI_NAMEREQD | NI_NOFQDN ) == 0) {
    strcpy(ip, hbuf);
    return 0;
  }
  else if (getnameinfo((struct sockaddr*)&addr, sizeof (struct sockaddr), hbuf, 
                       sizeof(hbuf), NULL,
                       0, NI_NUMERICHOST | NI_NOFQDN ) == 0) {
    strcpy(ip, hbuf);
    return 0;
  }
  return -1;
}

int
open_socket_any_port(u_short& port)	// Network byte order.
{
  // Open the socket
  const int s = static_cast<const int>(socket(AF_INET, SOCK_DGRAM, 0));
  if (s < 0)
    {
      perror(__FUNCTION__);
      Fatal(__FUNCTION__, "socket() failed");
    }

  // Bind the socket
  sockaddr_in addr;
  
  memset(&addr, 0, sizeof(addr));
  
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = 0;			// System chooses port number
  
  SYSTEM_CALL_LESS_ZERO(bind(s, (sockaddr *)&addr, sizeof(addr)));
  
  // Ensure the port is reusable
  int opt_val = 1;
  SYSTEM_CALL_LESS_ZERO(setsockopt(s, SOL_SOCKET, SO_REUSEADDR, 
				   (char *) &opt_val, sizeof(opt_val)));

  // Find out the port number we were given
  memset(&addr, 0, sizeof(addr));
  socklen_t addr_len = sizeof(addr);
  
  // Extract the port we were assigned from socket information
  SYSTEM_CALL_LESS_ZERO(getsockname(s, (sockaddr *)&addr, &addr_len));
  
  port = addr.sin_port;

  return s;
}

int
open_socket_any_port(void)
{
  u_short port;
  return open_socket_any_port(port);
}

int
open_socket(const u_short port)	// Network byte order.
{
  // Open the socket
  const int s = static_cast<const int>(socket(AF_INET, SOCK_DGRAM, 0));
  if (s < 0)
    {
      perror(__FUNCTION__);
      Fatal(__FUNCTION__, "socket() failed");
    }

  // Bind the socket
  sockaddr_in addr;
  
  memset(&addr, 0, sizeof(addr));
  
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = port;
  
  SYSTEM_CALL_LESS_ZERO(bind(s, (sockaddr *)&addr, sizeof(addr)));

  // Ensure the port is reusable
  int opt_val = 1;
  SYSTEM_CALL_LESS_ZERO(setsockopt(s, SOL_SOCKET, SO_REUSEADDR, 
				    (char *) &opt_val, sizeof(opt_val)));

  return s;
}

void
close_socket(const int s)
{
  SYSTEM_CALL_LESS_ZERO(close(s));
}

/*
//
// Given a machine's name, try to find its internet address.
// (Result is in network byte order.)
//
wordlong
LookupMachineIPAddress(const std::string& name)
{
  return LookupMachineIPAddress(name.c_str());
}

wordlong
LookupMachineIPAddress(const char *name)
{
  //
  // Code adapted from W. Richard Stevens ``Unix Network Programming''.
  //
  // First try to convert the host name as a dotted-decimal number.
  // Only if that fails do we call gethostbyname().
  //
  hostent host_info;
  sockaddr_in remote_addr;

#ifdef WIN32
  unsigned long res = inet_addr(name);
  if (res != INADDR_NONE)
    {
      return res;
    }
#else
  struct in_addr inp;
  int res = inet_aton(name, &inp);
  if (res != 0)
    {
      return inp.s_addr;
    }
#endif
  else
    {
      char hostname[255];
      strcpy(hostname, name);
      // if (strcmp(hostname, "localhost") == 0)
      //   {
      //     if (gethostname(hostname, 255) != 0)
      //       {
      //         return 0;
      //       }
      //   }
      hostent *hp;
      
      if ( (hp = gethostbyname(hostname)) == NULL)
// 	{
// 	  struct in_addr in;
// 	  in.s_addr = inet_addr(hostname);
// 	  hp = gethostbyaddr((char *) &in, sizeof(in), AF_INET);
// 	}
//       if (hp == NULL)
      //   {
      //     strcpy(hostname, "127.0.0.1");
      //     getIPfromifconfig(hostname);
      //     struct in_addr in;
      //     in.s_addr = inet_addr(hostname);
      //     hp = gethostbyaddr((char *) &in, sizeof(in), AF_INET);
      //   }
      // if (hp == NULL)
	{
	  Fatal(__FUNCTION__, "host name error");
	  return 0;
	}

      host_info = *hp;    // found it by name, structure copy

      memcpy((char *) &remote_addr.sin_addr,
	     (char *) hp->h_addr,
	     hp->h_length);
    }

  return remote_addr.sin_addr.s_addr;
}


//
// Try to find the IP address of this machine.
// (Result is in network byte order.)
//
wordlong
LookupMachineIPAddress(void)
{
#ifdef WIN32
  char name[255];
  gethostname(name, 255);
  return LookupMachineIPAddress(name);
#else
  struct utsname name;
  SYSTEM_CALL_LESS_ZERO(uname(&name));
  return LookupMachineIPAddress(name.nodename);
#endif
}
*/

//
// Do a connection to a socket
//


bool do_connection(int sockfd, int port, wordlong ip_address)
{
  struct sockaddr_in add;
  memset((char *)&add, 0, sizeof(add));
  add.sin_family = AF_INET;
  add.sin_port = port;
  add.sin_addr.s_addr = ip_address;
  const int ret = connect(sockfd, (struct sockaddr *)&add, sizeof(add));

  if (ret == 0) return true;

#ifdef WIN32
  else if ((errno = WSAGetLastError() == WSAEINPROGRESS) && errno == WSAEWOULDBLOCK)
#else
  else if (errno == EINPROGRESS)
#endif
    {
      fd_set fds;
      
      FD_ZERO(&fds);
      FD_SET((unsigned int)sockfd, &fds);
      
#ifndef NDEBUG
      int result = select(sockfd + 1, (fd_set *) NULL, &fds, 
			  (fd_set *) NULL, NULL);
#else
      select(sockfd + 1, (fd_set *) NULL, &fds, (fd_set *) NULL, NULL);
#endif
      
      assert(result && FD_ISSET(sockfd, &fds));
      return true;
    }
  else
    {
      return false;
    }
}


// No DNS lookup - so use ifcofig to get IP
#ifdef WIN32
void getIPfromifconfig(char* ip)
{
    SOCKET sd = WSASocket(AF_INET, SOCK_DGRAM, 0, 0, 0, 0);
    if ((int)sd == SOCKET_ERROR) {
      fprintf(stderr, "Failed to get a socket. Error %d\n",WSAGetLastError()); 
      return;
    }

    INTERFACE_INFO InterfaceList[20];
    unsigned long nBytesReturned;
    if (WSAIoctl(sd, SIO_GET_INTERFACE_LIST, 0, 0, &InterfaceList,
                 sizeof(InterfaceList), &nBytesReturned, 0, 0) == SOCKET_ERROR) {
      fprintf(stderr, "Failed calling WSAIoctl: error %d\n",WSAGetLastError());
      return;
    }

    int nNumInterfaces = nBytesReturned / sizeof(INTERFACE_INFO);
    for (int i = 0; i < nNumInterfaces; ++i) {
        wordlong nFlags = InterfaceList[i].iiFlags;
        if ((nFlags & IFF_UP) && !(nFlags & IFF_LOOPBACK)) {
          sockaddr_in *pAddress;
          pAddress = (sockaddr_in *) & (InterfaceList[i].iiAddress);
          strcpy(ip, inet_ntoa(pAddress->sin_addr));
          return;
        }                                              
    }

    return;
}



#else
void getIPfromifconfig(char* ip)
{
  struct ifaddrs *ifaddr, *ifa;
  int family, s;
  char host[NI_MAXHOST];
  
  if (getifaddrs(&ifaddr) == -1) {
    perror("getifaddrs");
    exit(EXIT_FAILURE);
  }
  
  for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
    family = ifa->ifa_addr->sa_family;
    
    if ((family == AF_INET) 
        && (ifa->ifa_flags & IFF_UP) 
        && !(ifa->ifa_flags & IFF_LOOPBACK )) {
      //printf("%s", ifa->ifa_name);
      s = getnameinfo(ifa->ifa_addr,
                      (family == AF_INET) ? sizeof(struct sockaddr_in) :
                      sizeof(struct sockaddr_in6),
                      host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
      if (s != 0) {
        printf("getnameinfo() failed: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
      }
      strcpy(ip, host);
      freeifaddrs(ifaddr);
      return;
    }
  }

}
#endif


