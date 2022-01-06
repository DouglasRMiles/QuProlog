// page_table.cc - Basic operations for a page table with a single page.
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
// $Id: page_table.cc,v 1.9 2006/01/31 23:17:51 qp Exp $

#ifndef PAGE_TABLE_CC
#define PAGE_TABLE_CC

#include <iostream>

#include "area_offsets.h"
#include "defs.h"
#include "int.h"
#include "magic.h"
#include "page_table.h"

//
// Constructor:
//	Allocate the index table and initialise it NULL.  There is no need to
//	allocate the first page because it is handled by pushElement.
//
template <class StoredType>
PageTable<StoredType>::PageTable(word32 size)
{
  word32	FullSize;
  
  FullSize = size * K;
  index = new StoredType [FullSize];
  //
  // Initialise the page table.
  //
  allocatedSize = FullSize;
}

//
// Destructor:
//	Clean up the index table.
//
template <class StoredType>
PageTable<StoredType>::~PageTable(void)
{
  if (index != NULL)
    {
      delete [] index;		// Delete the index table.
    }
  
  allocatedSize = 0;
}

//
// Write the area bounded by "begin" and "end" to a stream.
//
template <class StoredType>
void
PageTable<StoredType>::saveArea(ostream& ostrm, const wordlong magic,
				const PageLoc begin, const PageLoc end) const
{
  assert(end >= begin);

  const size_t size = end - begin;

  //
  // Write out the magic number.
  //
  IntSave<word32>(ostrm, magic);

  //
  // Write out the size (i.e. the number of entries of "StoredType").
  //
  IntSave<word32>(ostrm, static_cast<word32>(size));

  //
  // Write out the page.
  //
  ostrm.write((char*)(offsetToAddress(begin)), static_cast<std::streamsize>(size * sizeof(StoredType)));
  if (ostrm.fail())
    {
      SaveFailure(__FUNCTION__, "data segment", getAreaName());
    }
}

//
// Read the "ReadSize" entries of data from a stream into the memory starting
// at "start".
//
template <class StoredType>
void
PageTable<StoredType>::readData(istream& istrm, const char *AreaName,
				const word32 ReadSize, const PageLoc start)
{
  //
  // Read in a segment into the page.
  //
  allocateEntries(start + ReadSize);
#if defined(MACOSX)
    istrm.read((char*)offsetToAddress(start), ReadSize * sizeof(StoredType));
#else
  if (istrm.good() &&
      istrm.read((char*)offsetToAddress(start), ReadSize * sizeof(StoredType)).fail())
    {
      ReadFailure(__FUNCTION__, "data segment", AreaName);
    }
#endif //defined(MACOSX)
}

//
// Load the area from a stream.  "start" marks the start of the area in memory.
//
template <class StoredType>
void
PageTable<StoredType>::loadArea(istream& istrm, const PageLoc start)
{
  const word32 ReadSize = IntLoad<word32>(istrm);
  if (ReadSize > allocatedSize)
    {
      //
      // Wrong size.
      //
      FatalS(__FUNCTION__, "wrong size for ", getAreaName());
    }

  readData(istrm, getAreaName(), ReadSize, start);
}

#endif	// PAGE_TABLE_CC
