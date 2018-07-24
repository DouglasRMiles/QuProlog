// string_table.h - The table holds the atoms in C++ string format.  That is,
//		    a sequence of characters terminated by '\0'.  The strings
//		    are stored in the table consecutively.
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
// $Id: string_table.h,v 1.3 2002/11/03 08:37:33 qp Exp $

#ifndef	STRING_TABLE_H
#define	STRING_TABLE_H

#include <iostream>

#include "area_offsets.h"
#include "defs.h"
#include "magic.h"
#include "qem_options.h"
#include "stack_qp.h"

//
// The stack holds '\0' terminating strings.
//	String Table 
//
//	|        |
//	+--------+
//	|   h    | 
//	+--------+
//	|   e    |
//	+--------+
//	|   l    |
//	+--------+
//	|   l    |
//	+--------+
//	|   o    |
//	+--------+
//	|   \0   |
//	+--------+
//	|        |
//


class	StringTab : public PrologStack <char>
{

private:
  
  //
  // Return the name of the area.
  //
  virtual	const char	*getAreaName(void) const
    { return("string table"); }
  
public:
  
  //
  // Allocate space for the table and install default strings.
  //
  StringTab(word32 size, word32 boundary) :
  PrologStack <char> (size, boundary)
    {}
  
  //
  // Retrieve the string from the table.
  // If StringLoc or StackLoc changes representation, then a bug may
  // occur if this is not changed.
  //
  char *getString(const StringLoc loc)
    { return(fetchAddr(loc)); }

  const char *inspectString(const StringLoc loc) const
    { return(inspectAddr(loc)); }

  //
  // Add a new string to the table.
  //
  char*	add(const char *string);
  
  //
  // Size of the string table.
  //
  word32	size(void) const	{ return(allocatedSize()); }
  
  //
  // Save the data.
  //
  void save(std::ostream& ostrm) const
    { saveStack(ostrm, STRING_TABLE_MAGIC_NUMBER); }

  //
  // Restore the data.
  //
  void load(std::istream& istrm)
    { loadStack(istrm); }

};

#endif	// STRING_TABLE_H
