// timestamp.h -
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
// $Id: timestamp.h,v 1.3 2002/12/03 04:55:00 qp Exp $

#ifndef	TIMESTAMP_H
#define	TIMESTAMP_H

#include "defs.h"

class Timestamp
{
private:
  word32 count;
public:
  Timestamp(void) : count(1) { }

  void Stamp(void) { count++; }
  
  const word32 GetStamp(void) const { return count; }
};

inline std::ostream&
operator<<(std::ostream& ostrm, const Timestamp& ts)
{
  ostrm << " count = " << ts.GetStamp();

  return ostrm;
}

#endif	// TIMESTAMP_H
