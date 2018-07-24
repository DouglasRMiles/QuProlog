// status.h - Implementation of status register.
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
// $Id: status.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	STATUS_H
#define	STATUS_H

#include "defs.h"

template <class Size>
class	Status
{
private:
  Size status;

protected:
  
  //
  // Set the flag.
  //
  void set(const Size flag)    { status = status | flag; }
  
  //
  // Reset the flag.
  //
  void reset(const Size flag) { status = status & ~flag; }
  
  //
  // Test the flag.
  //
  bool test(const Size flag) const    
    {
      return ((status & flag) == flag) ? true : false;
    }

  //
  // Clear status completely.
  //
  void clear(void) { status = 0; }

  Status(void) : status(0)	{ }
};

#endif	// STATUS_H
