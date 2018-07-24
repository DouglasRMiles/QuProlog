// hash_table.h - Fundamental hash table arrangement.  Open addressing is
//		  used.  It requires overloaded operator == for comparison.
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
// $Id: hash_table.h,v 1.7 2006/01/31 23:17:50 qp Exp $

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>

#include "area_offsets.h"
#include "defs.h"
#include "timestamp.h"
#include <time.h>
#include "int.h"

//
// This is primary used for table inspection by statistics.
//
class	FixedSizeHashTable
{
public:
  
  //
  // Return the number of entries in use.  The size is defined as the
  // number of HashType in the table.
  //
  virtual word32 sizeOfTable(void) const { return 0; }
  
  //
  // Return the size allocated to the table.  The size is defined as the
  // number of HashType in the table.
  //
  virtual word32 allocatedSize(void) const { return 0; }

  virtual ~FixedSizeHashTable() {}
};

//
// HashType is the data type stored in the hash table.
// HashKey is the data type for hashing into the table.
// It requires overloaded operator == for HashKey for comparison.  Rehashing
// is used to solve the collision problem.  
// The size of the table must be a power of 2.
// Error messages that can be reported:
//	OutOfHashTable.
//
template <class HashType, class HashKey>
class HashTable : public FixedSizeHashTable
{
  
private:
  word32 tableSize;	// Size of the hash table.
  word32 tableSizeMask;	// Size of the hash table - 1.
  HashType *table;		// The table itself.
  
  //
  // Return the name of the table.
  //
  virtual const char *getAreaName(void) const = 0;
  
  //
  // Round up to the next next power of 2.
  //
  word32 next_2power(word32 n) const
  {
    word32 power = 2;
    while (n > 0)
      {
	n >>= 1;
	power <<= 1;
      }
    return(power);
  }

protected:
  
  //
  // Hash into the table by the string.
  //
  HashLoc hashString(const char *string) const;
  
  //
  // The initial hashing calculation.
  // 
  virtual HashLoc hashFunction(const HashKey entry) const = 0;
  
  //
  // Search through the hash table.  Either it locates the matching
  // entry or an empty location is found.  When one of these situations
  // becomes true, the location of the entry is returned.
  // It requires overloaded operator == for HashKey for comparison.
  // OutOfHashTable is reported if the table has cycled through once and
  // unable to allocate an empty entry.
  //
  HashLoc search(const HashKey key) const;
  
  const HashType& inspectEntry(const HashLoc loc) const
    { return table[loc]; }

  //
  // Look up an existing entry.  If it does not exist, EMPTY_LOC is
  // returned.
  //
  HashLoc lookUpTable(const HashKey key) const
  {
    const word32 index = search(key);
    return(((inspectEntry(index).isEmpty()) ?
	    (EMPTY_LOC) : (index)));
  }
  
  //
  // Return the size of the table in use.
  //
  virtual word32 sizeOfTable(void) const;
  
  //
  // Write the table to a stream.
  //
  void saveTable(std::ostream& ostrm, const u_long magic) const;
  
  //
  // Load the table from a stream.
  //
  void loadTable(std::istream& istrm);
  
public:

  //
  // Return the size of the table.
  //
  virtual word32 allocatedSize(void) const { return(tableSize); }

  //
  // Given a location, return the entry in the table.
  //
  HashType& getEntry(const HashLoc loc) { return(table[loc]); }

  //
  // Turn a pointer into the table into an offset
  //
  HashLoc getOffset(const HashType* e)
  {
    assert(e >= table && e <= table + tableSize);
    return static_cast<HashLoc>((e - table));
  }

  //
  // Turn an offset into a pointer
   //
  HashType* getAddress(const HashLoc loc)
    {
      assert(loc >= 0 && loc <= tableSize);
      return(table + loc);
    }

  //
  // The supplied location is valid.
  //
  virtual bool IsValid(const HashLoc loc) const
  {
    return loc <= allocatedSize();
  }

  HashTable(word32 TabSize);
  virtual ~HashTable(void);

};



//
// Constructor:
//	Allocate the hash table.
//
template <class HashType, class HashKey>
HashTable<HashType, HashKey>::HashTable(word32 TabSize)
{
  tableSize = next_2power(TabSize);
  table = new HashType[tableSize];
  tableSizeMask = tableSize-1;
}

//
// Destructor:
//	Clean up the table.
//
template <class HashType, class HashKey>
HashTable<HashType, HashKey>::~HashTable(void)
{
  if (table != NULL)
    {
      delete [] table;
    }
}

//
// Hash into the table by the string.
//
template <class HashType, class HashKey>
HashLoc
HashTable<HashType, HashKey>::hashString(const char *string) const
{
  word32 value = 5381;
  int c;
  while ((c = *string++))
    {
      value = ((value << 5) + value) + c; /* hash * 33 + c */
    }
  return value;
}

//
// Search through the hash table.  Either it locates the matching entry or an
// empty location is found.  When one of these situations becomes true, the
// location of the entry is returned.
//
template <class HashType, class HashKey>
HashLoc
HashTable<HashType, HashKey>::search(const HashKey key) const
{
  HashLoc loc = hashFunction(key) & tableSizeMask;
  for (word32 increment = 1;
       ! inspectEntry(loc).isEmpty();
       loc = (loc + increment) & tableSizeMask, increment++)
    {
      if (key == inspectEntry(loc))
	{
	  return(loc);
	}
      else if (increment  == tableSize)
	{
	  //
	  // The table has been cycled through.
	  //
	  OutOfHashTable(__FUNCTION__, getAreaName(), tableSize);
	}
    }
  //
  // No matching entry is found.  Return this empty entry for possible
  // insertion.
  //
  return(loc);
}

//
// Return the size of the table in use.
//
template <class HashType, class HashKey>
word32
HashTable<HashType, HashKey>::sizeOfTable(void) const
{
  word32 size = 0, i;
  
  for (i = 0; i < allocatedSize(); i++)
    {
      if (! inspectEntry(i).isEmpty())
	{
	  size++;
	}
    }
  return(size);
}

//
// Write the table to a stream.
//
template <class HashType, class HashKey>
void
HashTable<HashType, HashKey>::saveTable(ostream& ostrm, const u_long magic) const
{
  IntSave<word32>(ostrm, magic);
  IntSave<word32>(ostrm, tableSize);

  // XXX Endian problem
  if (ostrm.good() &&
      ostrm.write((char*)table, tableSize * sizeof(HashType)).fail())
    {
      SaveFailure(__FUNCTION__, "data", getAreaName());
    }
}

//
// Load the table from a stream.
//
template <class HashType, class HashKey>
void
HashTable<HashType, HashKey>::loadTable(istream& istrm)
{
  const word32	ReadSize = IntLoad<word32>(istrm);
  if (ReadSize != tableSize)
    {
      FatalS(__FUNCTION__, "wrong size for ", getAreaName());
    }

  //
  // Read in the table.
  //
  // XXX Endian problem
#if defined(MACOSX)
    istrm.read((char*)table, tableSize * sizeof(HashType));
#else
  if (istrm.good() &&
      istrm.read((char*)table, tableSize * sizeof(HashType)).fail())
    {
      ReadFailure(__FUNCTION__,
		  "data",
		  getAreaName());
    }
#endif //defined(MACOSX)
}
#endif	// HASH_TABLE_H

