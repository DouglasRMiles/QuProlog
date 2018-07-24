// bool.h - Class for handling booleans. Mainly useful for when they have
//	to bre read or written.
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
// $Id: bool.h,v 1.4 2006/01/31 23:17:49 qp Exp $

#ifndef	BOOL_H
#define	BOOL_H

#include <iostream>

#include "int.h"

class Bool: public Int<bool>
{
public:
  explicit Bool(const bool b) : Int<bool>(b) { }
  explicit Bool(istream& istrm) : Int<bool>(istrm) { }
};

// Print out a Bool in a form that can be read by a person.
extern ostream& operator<<(ostream&, const Bool&);

inline ostream&
BoolWrite(ostream& ostrm, const bool b)
{
  if (! ostrm.good())
    {
      SaveFailure(__FUNCTION__, "bool write");
    }

  const Bool B(b);
  B.Save(ostrm);

  if (ostrm.fail())
    {
      SaveFailure(__FUNCTION__, "bool write");
    }

  return ostrm;
}

#endif	// BOOL_H


