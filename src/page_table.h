// page_table.h - Basic operations for a page table with a singe page.
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
// $Id: page_table.h,v 1.5 2006/01/31 23:17:51 qp Exp $

#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <iostream>

#include "area_offsets.h"
#include "defs.h"
#include "errors.h"

#include "int.h"
#include "magic.h"

template <class StoredType>
class	PageTable
{

private:

  StoredType	*index;			// Index table to the page.
  word32		allocatedSize;		// Allocated size.
  
  //
  // Allocate a new page to the index table if it is required.
  // OutOfPage is reported if the index table is run out; or
  //
  void		allocateEntries(const word32 EndLoc)
    {
      if (EndLoc > allocatedSize)
	{
	  OutOfPage(__FUNCTION__,
		    getAreaName(),
		    allocatedSize / K);
	}
    }
  
protected:
  
  //
  // Return the name of the table.
  //
  virtual	const char	*getAreaName(void) const = 0;
  
  //
  // Given an index of a word in the stack, get the address.
  //
  StoredType	*offsetToAddress(const PageLoc loc) const
    { return(index + loc); }
  
  //
  // Given an index of a word in the stack, return the item at that
  // location.
  //
  StoredType&	getItem(const PageLoc loc) const
    { return(index[loc]); }

  //
  // Allocate 'n' items of StoredType starting at the specified location.
  // OutOfPage is reported if the index table is run out; or
  //
  void		allocateItems(const PageLoc loc, const word32 n)
    {
      allocateEntries(loc + n);
    }
  
  //
  // Allocate a segment of 'n' items of StoredType within one page and
  // return a pointer to this space.  The segment may start at the given
  // location or the beginning of next page.
  // OutOfPage is reported if the index table is run out; or
  //
  PageLoc		allocateSegment(const PageLoc loc, const word32 n)
    {
      allocateEntries(loc + n);
      return(loc);
    }
  
  //
  // Return the size of the area allocated.
  //
  word32		areaSize(void) const
    { return(allocatedSize); }
  
  //
  // Write the area bounded by "begin" and "end" to a stream.
  //
  void		saveArea(std::ostream& ostrm, const u_long magic,
			 const PageLoc begin, const PageLoc end) const;
  
  //
  // Read the "ReadSize" entries of data from a stream into the memory
  // starting at "start".
  //
  void		readData(std::istream& istrm, const char *file,
			 const word32 ReadSize, const PageLoc start);
  
  //
  // Load the area from a stream.  "start" marks the start of the area
  // in memory.
  //
  void		loadArea(std::istream& istrm, const PageLoc start);
  
public:
  
  explicit PageTable(word32 size);
  virtual	~PageTable(void);
};



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
PageTable<StoredType>::saveArea(ostream& ostrm, const u_long magic,
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

#endif	// PAGE_TABLE_H
