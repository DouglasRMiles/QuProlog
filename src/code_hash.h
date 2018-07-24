// code_hash.h - Compiled hash tables for SWITCH_ON instructions.
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
// $Id: code_hash.h,v 1.4 2006/01/31 23:17:49 qp Exp $

#ifndef	CODE_HASH_H
#define	CODE_HASH_H

#include "area_offsets.h"
#include "code.h"
#include "defs.h"


//
// Generic compiled hash table.
// The size of the table must be a power of 2 in order to obtain the best
// performance.
//
template <class HashEntry>
class	CodeHashTable
{
  
private:
  
  Code& code;		// Code area.
  CodeLoc base;		// Base of the table.
  word32 tableSize;	// Size of the table.
  word32 tableSizeMask;	// Size of the table - 1.
  
  //
  // Convert a hash index to an address.
  //
  CodeLoc		offsetToAddr(const word32 index) const
    { return(base + index * HashEntry::SIZE); }
  
protected:
  
  //
  // Initial hashing calculation.
  //
  virtual	wordptr		hashFunction(const HashEntry entry) const = 0;
  
  //
  // Search for the entry in the hash table.
  //
  word32		search(const HashEntry entry) const;
  
public:
  
  //
  // Size of the hash table.
  //
  word32  	size(void) const	{ return(tableSize); }
  
  //
  // Add a new entry into the table.
  // 
  void		add(HashEntry entry)
    { entry.store(code, offsetToAddr(search(entry))); }
  
  //
  // Look up for an existing entry and return the offset (the label
  // where to jump to).
  //
  word32		lookUp(const HashEntry existing) const
    {
      CodeLoc		OffsetLoc;
      
      OffsetLoc = offsetToAddr(search(existing)) + HashEntry::OFFSET_LOCATION;
      return(getOffset(OffsetLoc));
    }
  
  CodeHashTable(Code& area, const CodeLoc start, const word32 TabSize)
    : code(area),
      base(start),
      tableSize(TabSize),
      tableSizeMask(tableSize - 1)
    { }

    virtual ~CodeHashTable() {}
};


//
// Search for the entry in the hash table.
//
template <class HashEntry>
word32
CodeHashTable<HashEntry>::search(const HashEntry entry) const
{
  word32		hash, increment;
  HashEntry	current;
  CodeLoc		cptr;
  
  hash = hashFunction(entry) & tableSizeMask;
  increment = 1;
  while (true)
    {
      cptr = offsetToAddr(hash);
      current.load(code, cptr);
      if (current.isEmpty() || current == entry)
	{
	  return(hash);
	}
      else if (increment ==  tableSize)
	{
	  //
	  // The table has been cycled through.
	  //
	  OutOfHashTable(__FUNCTION__,
			 "code hash table", tableSize);
	}
      else
	{
	  hash = (hash + increment) & tableSizeMask;
	  increment ++;
	}
    }
}

#endif	// CODE_HASH_H
