// string_map.h - Used for relocation of atoms and numbers during loading.
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
// $Id: string_map.h,v 1.3 2002/11/03 08:37:33 qp Exp $

#ifndef	STRING_MAP_H
#define	STRING_MAP_H

#include <iostream>

#include "area_offsets.h"
#include "atom_table.h"
#include "defs.h"
//#include "heap.h"
#include "stack_qp.h"

//
// Mapping the string offset given in qo files to the location in the atom
// table.  The string offsets in qo files refer the string number in the
// string table in the qo files.  i.e.  Offset 1 refers the first string,
// offset 2 refers to the second string, and so on.  There is no offset 0.
//
class	StringMap : public PrologStack <Atom*>
{

private:

virtual	const char *getAreaName(void) const { return("string map"); }

public:
  StringMap(word32 size, word32 boundary)
    : PrologStack <Atom*> (size, boundary) {}

  //
  // Return the current top of stack.
  //
  StringMapLoc	getTop(void) const	{ return(getTopOfStack()); }
  
  //
  // Read in the strings.
  // Return whether it is successful or not.
  //
  bool loadStrings(istream& istrm, const char *file, AtomTable& atoms);
  
  //
  // Convert an old offset to the new one.
  //
  Atom* convert(const StringMapLoc base, const  word32 old) const
  {
    return *inspectAddr(base + old);
  }
};

//
// The map for numbers.
//
class NumberMap : public PrologStack <Object*>
{

private:

  virtual const char *getAreaName(void) const { return("number map"); }

public:
NumberMap(word32 size, word32 boundary)
    : PrologStack <Object*> (size, boundary) {}

  //
  // Return the current top of stack.
  //
  NumberMapLoc	getTop(void) const	{ return(getTopOfStack()); }
  
  //
  // Read in the numbers.
  // Return whether it is successful or not.
  //
  bool loadNumbers(istream& istrm, Heap& number_heap);
  
  //
  // Convert an old offset to the new one.
  //
  Object* convert(const NumberMapLoc base, const  word32 old) const
  {
    return *inspectAddr(base + old);
  }
};

#endif	// STRING_MAP_H




