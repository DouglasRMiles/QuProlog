// string_table.cc - The table holds the atoms in C++ string format.  That is,
//		     a sequence of characters terminated by '\0'.  The strings
//		     are stored in the table consecutively.
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
// $Id: string_table.cc,v 1.3 2005/03/08 00:35:15 qp Exp $

#include <string.h>

#include "area_offsets.h"
#include "defs.h"
#include "string_table.h"

//
// Add a new string to the table.
//
char*
StringTab::add(const char *string)
{
  StringLoc   start = allocateBlock(static_cast<word32>(strlen(string) + 1));

  if (start == EMPTY_LOC)
    {
      //
      // Hopefully we should never get here, so we return an
      // "arbitrary" value.  OutOfPage in allocateBlock
      // should recover the program in the appropriate manner.
      //
      return(NULL);
    }
  else
    {
      //
      // Save the string in the string table.
      //
      strcpy(fetchAddr(start), string);
      return(fetchAddr(start));
    }
}











