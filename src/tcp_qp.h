// tcp_qp.h -
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
// $Id: tcp_qp.h,v 1.2 2002/11/10 07:54:54 qp Exp $

#ifndef	TCP_QP_H
#define	TCP_QP_H

#include <sys/types.h>
#include <string>

//#include "string_qp.h"

//
// Convert from ip address to network order number for the IP
//
extern int ip_to_ipnum(char* ip, u_long& ipnum);
//
// Inverse of above
//
extern int ipnum_to_ip(u_long ipnum, char* ip);
//
// Opens and binds a socket and returns it, as well as the port that
// the socket was bound to. The port is chosen by the operating system.
// The returned value is in network byte order.
//
extern int open_socket_any_port(u_short&);

//
// Opens and binds a socket and returns it. The port is chosen by the
// operating system.
//
extern int open_socket_any_port(void);

//
// Same as above, except that the port is supplied by the caller.
// The argument is in network byte order.
//
extern int open_socket(const u_short);

//
// Close the socket.
//
extern void close_socket(const int);
/*
//
// Given a machine's name, try to find its IP address.
// (The result is in network byte order.)
//
extern u_long LookupMachineIPAddress(const std::string&);
extern u_long LookupMachineIPAddress(const char *);
//
// Find the IP address of this machine. 
// (The result is in network byte order.)
//
extern u_long LookupMachineIPAddress(void);
*/

//
// Do a connection to a socket
//
bool do_connection(int sockfd, int port, u_long ip_address);


void getIPfromifconfig(char* ip);

#endif	// TCP_QP_H
