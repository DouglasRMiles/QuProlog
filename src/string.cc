// string.cc -
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
// $Id: string.cc,v 1.4 2002/11/08 00:44:21 qp Exp $

#include <ctype.h>
#include <string.h>
#include <iostream>

#include "int.h"
#include "string_qp.h"


//String::String(istream& istrm)
//{
//  length = IntLoad<size_t>(istrm);
//
//  string = new char[length + 1];
//
//  for (word32 i = 0; i <= length; i++)
//    {
//      char c;
//      if (istrm.good() &&
//	  istrm.get(c))
//	{
//	  string[i] = c;
//	}
//      else
//	{
//	  ReadFailure(__FUNCTION__, "buffer contents");
//	  delete [] string;
//	}
//    }
//}

//ostream&
//String::Save(ostream& ostrm) const
//{
//  IntSave<size_t>(ostrm, Length());
//
//  const char *string = Str();
//
//  for (word32 i = 0; i <= Length(); i++)
//    {
//      ostrm.put(string[i]);
//      if (ostrm.fail())
//	{
//	  SaveFailure(__FUNCTION__, "content");
//	}
//    }
// 
//  return ostrm;
//}

ostream&
operator<<(ostream& ostrm, const String& string)
{
  return ostrm << string.Str();
}

