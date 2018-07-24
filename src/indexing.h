// indexing.h - Compiled indexing tables for predicates.
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
// $Id: indexing.h,v 1.7 2006/01/31 23:17:50 qp Exp $

#ifndef INDEXING_H
#define INDEXING_H

#include "area_offsets.h"
#include "atom_table.h"
#include "objects.h"
#include "code.h"
#include "code_hash.h"
#include "defs.h"
#include "string_map.h"

//
// The value stored in atomic when the entry is empty.
//
const wordptr EMPTY_ENTRY = WORDPTR_MAX;


//
// A record for constant table.
//
class ConstEntry
{

private:

  wordptr atomic;
  word8 type;
  word16 offset;

public:
  ConstEntry(void) { }

  ConstEntry(const wordptr constant, const word16 t) 
    : atomic(constant), type(static_cast<word8>(t)) { }

  //
  // Location of the offset and the size of each entry in the hash
  // table in the code area.
  //
  static const word32 OFFSET_LOCATION = 
        Code::SIZE_OF_CONSTANT + Code::SIZE_OF_NUMBER;
  static const word32 SIZE = OFFSET_LOCATION + Code::SIZE_OF_OFFSET;
  static const word16 EMPTY = 0;
  static const word16 INTEGER_TYPE = 1;
  static const word16 ATOM_TYPE = 2;
  static const word16 STRING_TYPE = 3;
  
  //
  // Check whether the entry is empty or not.
  //
  bool isEmpty(void) const { return(type == EMPTY); }

  bool isAtom(void) const { return(type == ATOM_TYPE); }
  
  //
  // Compare two entries.
  //
  bool operator==(const ConstEntry& entry) const
    {
      return ((type == entry.type) && (atomic == entry.atomic));
    }
  
  //
  // Hash on the constant.
  //
  wordptr hashFn(void) const 
    { 
      return atomic;
    }
  
  //
  // Store the data in the hash table in the code area.
  //
  void store(Code& code, const CodeLoc loc) const
    {
      updateAddress(loc, atomic);
      updateNumber(loc + Code::SIZE_OF_CONSTANT, type);
      updateOffset(loc + Code::SIZE_OF_CONSTANT + Code::SIZE_OF_NUMBER, offset);
    }
  
  //
  // Load the data from the hash table in the code area.
  //
  void load(Code& code, CodeLoc& loc)
    {
      atomic = getAddress(loc);
      type = getNumber(loc);
      offset = getOffset(loc);
    }

  //
  // change constant pointer to tagged offset
  //
  void pointerToOffset(AtomTable& atoms)
    {
      assert(type == ATOM_TYPE);
      AtomLoc loc = atoms.getOffset(reinterpret_cast<Atom*>(atomic));
      atomic = static_cast<wordptr>(loc);
    }

  //
  // change tagged offset to constant pointer
  //
  void offsetToPointer(AtomTable& atoms)
    {
      assert(type == ATOM_TYPE);
      atomic = reinterpret_cast<wordptr>(atoms.getAddress(atomic));
    }


  
  //
  // Convert to new offset if it is a constant.
  //
  void relocate(const StringMap& string_map, const StringMapLoc string_base)
    {
      if (type == ATOM_TYPE)
	{
	  atomic = reinterpret_cast<wordptr>(string_map.convert(string_base, 
                                                                atomic));
	}
    }
  
  //
  // Initialise the record.
  //
  void assign(const wordptr constant, const word16 t) 
    { 
      atomic = constant; 
      type = static_cast<word8>(t);
    }
};

//
// Constant table for SWITCH_ON_CONSTANT.
//
class ConstantTable : public CodeHashTable <ConstEntry>
{
  
private:
  
  wordptr hashFunction(const ConstEntry entry) const
    { return(entry.hashFn()); }

public:
  
  ConstantTable(Code& area, const CodeLoc start, const word32 TabSize) : 
    CodeHashTable <ConstEntry> (area, start, TabSize)
    {}

    virtual ~ConstantTable() {}
};



//
// A record for structure table.
//
class StructEntry
{
  
private:
  
  wordptr atomic;
  word32 arity;
  word32 offset;
  
public:
  StructEntry(void) { }
  StructEntry(const wordptr structure, const word32 a) :
    atomic(structure), arity(a)
    { }
  
  //
  // Location of the offset and the size of each entry in the hash
  // table in the code area.
  //
  static const word32 OFFSET_LOCATION = Code::SIZE_OF_CONSTANT + Code::SIZE_OF_NUMBER;
  static const word32 SIZE = OFFSET_LOCATION + Code::SIZE_OF_OFFSET;
  
  //
  // Check whether the entry is empty or not.
  //
  bool isEmpty(void) const { return(atomic == EMPTY_ENTRY); }
  
  //
  // Compare two entries.
  //
  bool operator==(const StructEntry& entry) const
    {
      return ((arity == entry.arity) && (atomic == entry.atomic));
    }
  
  
  //
  // Hash on the constant.
  //
  wordptr hashFn(void) const
    {
      return((atomic) ^ arity); 
    }
  
  //
  // Store the data in the hash table in the code area.
  //
  void store(Code& code, const CodeLoc loc) const
    {
      updateAddress(loc, atomic);
      updateNumber(loc + Code::SIZE_OF_CONSTANT,
		   (word8) arity);
      updateOffset(loc + Code::SIZE_OF_CONSTANT + Code::SIZE_OF_NUMBER,
		   (word16) offset);
    }

  //
  // Load the data from the hash table in the code area.
  //
  void load(Code& code, CodeLoc& loc)
  {
    atomic = getAddress(loc);
    arity = getNumber(loc);
    offset = getOffset(loc);
  }
 
  //
  // Convert to new offset if it is a constant.
  //
  void relocate(const StringMap& string_map, const StringMapLoc string_base)
  {
    atomic = reinterpret_cast<wordptr>(string_map.convert(string_base, atomic));
  }

  //
  // Initialise the record.
  //
  void assign(const wordptr constant, const word32 n)
  {
    atomic = constant;
    arity = n;
  }
  //
  // change constant pointer to tagged offset
  //
  void pointerToOffset(AtomTable& atoms)
    {
      assert(reinterpret_cast<Object*>(atomic)->isAtom());
      AtomLoc loc = atoms.getOffset(reinterpret_cast<Atom*>(atomic));
      atomic = static_cast<word32>(loc);
    }

  //
  // change tagged offset to constant pointer
  //
  void offsetToPointer(AtomTable& atoms)
    {
      atomic = reinterpret_cast<wordptr>(atoms.getAddress(atomic));
    }
};

//
// Structure table for SWITCH_ON_STRUCTURE, and SWITCH_ON_QUANTIFIER.
//
class StructureTable : public CodeHashTable <StructEntry>
{

private:

  wordptr hashFunction(const StructEntry entry) const
  { return(entry.hashFn()); }

public:

  StructureTable(Code& area, const CodeLoc start, const word32 TabSize) : 
    CodeHashTable <StructEntry> (area, start, TabSize)
  {}
};

#endif // INDEXING_H














