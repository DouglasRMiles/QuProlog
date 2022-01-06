// dynamic_hash_table.h - A hash table template.
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
// $Id: dynamic_hash_table.h,v 1.6 2006/01/31 23:17:50 qp Exp $    
//

#ifndef DYNAMIC_HASH_TABLE_H
#define DYNAMIC_HASH_TABLE_H

#include <stdlib.h>

//
// HashType is the data type stored in the hash table.
// The size of the table must be a power of 2.
//
template <class HashType>
class	DynamicHashTable 
{

private:

	int		tableSize;	// Size of the hash table.
	int		tableSizeMask;	// Size of the hash table - 1.
	int             used;           // Number of used entries.
	HashType	*table;		// The table itself.
        int 		iter_pos;       // iterator position


	//
	// Round up to (the next power of 2)*2.
	//
	int		next_2power(int n) const
			{
				int power = 2;
				n--;
				while (n > 0)
				{
					n >>= 1;
					power <<= 1;
				}
				return(power);
			}

protected:

	//
	// The initial hashing calculation.
	// 
virtual	int		hashFunction(const HashType entry) const = 0;

public:
	//
	// Search through the hash table.  
	// If the entry is found then the position is returned else -1.
	// It requires overloaded operator == for HashType for comparison.
	//
	int		search(const HashType item) const;

	//
	// Insert entry in table.  
	// The table is resized if it becomes more than half full.
	// Returns true if entry exists. Also returns in hashValue the
        // index.
	//
	bool		insert(const HashType item, int& hashValue);

	//
	// Remove entry from table.  
	// Returns 1 if found otherwise 0.
	//
	int		remove(const int position);


	//
	// Resize the table
	//
	void		resize(const int newsize);

        //
        // Given a location, return the entry in the table.
        //
        HashType&       getEntry(const int loc) const
                        { 
			   if ((loc < 0) || (loc >= tableSize))
			   {
			     cerr
                               << "Out of bounds " << loc << endl;
			     abort();
			   }
			   return(table[loc]); 
			}

	//
	// Return the amount of table in use.
	//
	int		sizeOfTable(void)	const   { return(used); }

	//
	// Return the size of the table.
	//
	int		allocatedSize(void)	const	{ return(tableSize); }

	//
	// Reset iterator
	//
        void 		iter_reset(void)		{ iter_pos = 0; }

	//
	// Position of next entry for iterator
	//
	int		iter_next(void);      



	DynamicHashTable(int TabSize);
virtual	~DynamicHashTable(void);
};


//
// Constructor:
//	Allocate the hash table.
//
template <class HashType>
DynamicHashTable<HashType>::DynamicHashTable(int TabSize)
{
  tableSize = next_2power(TabSize);
  table = new HashType[tableSize];
  tableSizeMask = tableSize-1;
  used = 0;
}

//
// Destructor:
//	Clean up the table.
//
template <class HashType>
DynamicHashTable<HashType>::~DynamicHashTable(void)
{
  delete [] table;
}

//
// Search through the hash table.  
// If the entry is found then the position is returned else -1.
//
template <class HashType>
int
DynamicHashTable<HashType>::search(const HashType item) const
{
  int	hashValue, increment;
  HashType* entry;
  
  for (hashValue = hashFunction(item) & tableSizeMask, 
	 increment = 1, entry = &table[hashValue];
       ! entry->isEmpty(); )
    {
      if (!entry->isRemoved() && (item == *entry))
	{
	  return(hashValue);
	}
      else if (increment  == tableSize)
	{
	  return(-1);
	}
      hashValue = (hashValue + increment++) & tableSizeMask;
      entry = &table[hashValue];
    }
  //
  // No matching entry is found.  
  //
  return(-1);
}

//
// Insert entry in table.  
// The table is resized if it becomes more than half full.
// Returns 1 if already there otherwise 0.
//
template <class HashType>
bool
DynamicHashTable<HashType>::insert(const HashType item, int &hashValue)
{
  int	increment;
  HashType* entry;

  for (hashValue = hashFunction(item) & tableSizeMask, 
	 increment = 1, entry = &table[hashValue];
       ! (entry->isEmpty() || entry->isRemoved()); )
    {
      if (item == *entry)
	{
	  return(true);
	}
      else if (increment  == tableSize)
	{

          cerr << "DynamicHashTable: Insert: Table cycled through" << endl;
	  abort();
	}
      hashValue = (hashValue + increment++) & tableSizeMask;
      entry = &table[hashValue];
    }
  //
  // Empty or removed slot found.   
  //
  if ((used << 1) > tableSize)
    {
      // Check if there is a removed slot
      bool is_removed = false;
      for (int i = 0; i < tableSize; i++)
	{
	  if (!table[i].isEmpty() && table[i].isRemoved())
	    {
	      is_removed = true;
	      break;
	    }
	}
      int newTableSize;
      if (is_removed)
	{
	  newTableSize = tableSize;
	}
      else
	{
	  newTableSize = next_2power(tableSize);
	}
      resize(newTableSize);
      insert(item, hashValue);
    }
  else
    {
      used++;
      table[hashValue] = item;
    }
  assert(hashValue == search(item));
  return(false);
}

//
// Remove entry from table.  
// Returns 1 if found -1 if out of range otherwise 0.
//
template <class HashType>
int
DynamicHashTable<HashType>::remove(const int position) 
{
  if ((position < 0) || (position >= tableSize))
    {
      return(-1);
    }
  if (table[position].isEmpty() || table[position].isRemoved())
    {
      return(0);
    }
  used--;
  table[position].makeRemoved();
  return(1);
}

//
// Resize the table
//
template <class HashType>
void
DynamicHashTable<HashType>::resize(const int newsize) 
{
  HashType *oldtable = table;
  int oldtableSize = tableSize;
  
  tableSize = newsize;
  table = new HashType[tableSize]; 
  tableSizeMask = tableSize-1;
  used = 0;

  for (int j = 0; j < newsize; j++) {
    table[j].clearEntry();
  }

  for (int j = 0; j < oldtableSize; j++)
    {
      if (!oldtable[j].isEmpty())
	{
	  if(oldtable[j].isRemoved())
	    {
	      oldtable[j].clearEntry();
	    }
	  else
	    {
	      int dummy;
	      insert(oldtable[j], dummy);
	    }
	}
    }  
  delete [] oldtable;
}

//
// Position of next entry for iterator
// Return -1 if none left.
//
template <class HashType>
int		
DynamicHashTable<HashType>::iter_next(void)      
{
  while (iter_pos < tableSize)
    {
      if (!table[iter_pos].isEmpty() 
	  && !table[iter_pos].isRemoved())
	{
	  return(iter_pos++);
	}
      iter_pos++;
    }
  return(-1);
}







#endif	// DYNAMIC_HASH_TABLE_H

