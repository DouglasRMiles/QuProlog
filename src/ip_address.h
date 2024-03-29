// ip_address.h - A class for handling IP addresses.
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
// $Id: ip_address.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	IP_ADDRESS_H
#define	IP_ADDRESS_H

#include <sys/types.h>

class IPAddress {
 private:
  const wordlong ip_address;		// Network order.
 public:
  IPAddress(const wordlong ip,		// Address
	    const bool ho = true)	// In host order?
    : ip_address(ho ? htonl(ip) : ip)
    { }

  const wordlong HostOrder(void) const { return ntohl(ip_address); }

  const wordlong NetworkOrder(void) const { return ip_address; }
};

#endif	// IP_ADDRESS_H
