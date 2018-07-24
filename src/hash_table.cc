// hash_table.cc - Fundamental hash table arrangement.  Open addressing is
//		   used.  It requires overloaded operator == for comparison.
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
// $Id: hash_table.cc,v 1.8 2005/07/21 04:43:01 qp Exp $

#include <iostream>
#include <time.h>

#include "hash_table.h"
#include "int.h"

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
