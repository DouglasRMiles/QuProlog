// bool.cc -
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
// $Id: bool.cc,v 1.2 2005/03/08 00:34:59 qp Exp $

#include "bool.h"

ostream&
operator<<(ostream& ostrm, const Bool& qpbool)
{
  switch ((bool) qpbool.Value())
    {
    case false:
      ostrm << "false";
      break;
    case true:
	ostrm << "true";
	break;
    }
  
  return ostrm;
}

