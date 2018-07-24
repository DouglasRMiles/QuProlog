// port.h - Handling IP ports.
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
// $Id: port.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	PORT_H
#define	PORT_H

#include <sys/types.h>
#include <netinet/in.h>

class Port {
 private:
  const u_short port;		// Network byte order.
 public:
  Port(const u_short p,		// The port.
       const bool ho = true)	// Host byte order.
    : port(ho ? htons(p) : p)
    { }

  const u_short HostOrder(void) const { return htons(port); }
  const u_short NetworkOrder(void) const { return port; }
};

#endif	// PORT_H
