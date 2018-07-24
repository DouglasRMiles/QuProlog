// code_hash.cc - Compiled hash tables for SWITCH_ON instructions.
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
// $Id: code_hash.cc,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifdef	CODE_HASH_H

#include "area_offsets.h"
#include "defs.h"

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
