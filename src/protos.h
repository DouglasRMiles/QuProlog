// protos.h - Prototypes for older systems (or systems that don't have
//		enough information in their header files to keep g++ happy!)
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
// $Id: protos.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	PROTOS_H
#define	PROTOS_H

// #if !defined(sun) && !defined(__linux__)
#if 0
#include <sys/time.h>
#include <sys/types.h>

extern "C" int socket();
extern "C" int getsockopt();
extern "C" int setsockopt();
extern "C" int endhostent();
extern "C" int bind();
extern "C" int listen();
extern "C" int accept();
extern "C" int connect();
extern "C" int getsockname();
extern "C" int getpeername();
extern "C" int endservent();
extern "C" int ioctl();
extern "C" int poll();
extern "C" int recv();
extern "C" int recvfrom();
extern "C" int send();
extern "C" int sendto();
extern "C" void bzero();
extern "C" int select();
extern "C" void *sbrk();	// caddr_t on POSIX systems
extern "C" int setitimer();
#endif	// 0

#endif	// PROTOS_H


