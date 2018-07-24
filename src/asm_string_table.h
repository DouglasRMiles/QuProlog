// asm_string_table.h - 
//
// Tables used by the assembler to store atom strings and numbers.
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
// $Id: asm_string_table.h,v 1.9 2006/01/31 23:17:49 qp Exp $

#ifndef	ASM_STRING_TABLE_H
#define	ASM_STRING_TABLE_H

#include <iostream>

#include "asm_int.h"
#include "code.h"
#include "defs.h"
//#include "string_qp.h"

typedef u_int ASMLoc;

template <class EntryType>
class ASMTable
{
private:
  EntryType *table;             // Table of entries

  ASMLoc table_size;		// Total size of lookup array
  ASMLoc table_num_entries;	// Number of entries in use

  void expandTable(void)
  {
    ASMLoc new_size = 2 * table_size;
    
    EntryType *tmp = new EntryType[new_size];

    for (u_int i = 0; i < table_size; i++)
      {
	tmp[i] = table[i];
      }
    
    delete [] table;
    
    table = tmp;
    
    table_size = new_size;
  }
  
public:
  ASMTable(int size = 512);
  
  virtual ~ASMTable(void);

  ASMLoc tableNumEntries(void) const { return table_num_entries; }
  
  const EntryType& getEntry(const ASMLoc i) const
  {
    assert(i < table_num_entries);
    
    return table[i];
  }
  
  ASMLoc lookup(const EntryType& s)
  { 
    ASMLoc i;
    
    for (i = 0; i < table_num_entries; i++)
      {
	if (s == table[i])
	  {
	    break;
	  }
      }
    if (i < table_num_entries)
      {
	return i;
      }
    else
      {
	if (table_num_entries == table_size)
	  {
	    expandTable();
	  }
	
	ASMLoc index = table_num_entries;
	
	table[index] = EntryType(s);
	
	table_num_entries++;
	return index;
      }
  }

  virtual ostream& save(ostream&) const = 0;
};

//
// String pointers are used as the entries of ASMStringTable
//
class ASMStringPointer
{
public:
  string* value;

  bool operator==(const ASMStringPointer s) const
    { return (*value == *s.value); }

   ASMStringPointer(void)
    {
      value = NULL;
    }

  ASMStringPointer(string* s)
    {
      value = new string(*s);
    }

  ~ASMStringPointer(void)
    {
      //    delete value;
    }
};

//
// The string table for relocation of atoms
//
class ASMStringTable : public ASMTable <ASMStringPointer>
{
public:
  ASMStringTable(void) : ASMTable <ASMStringPointer>() {}

  const string& operator[](const ASMLoc i) const
  {
    assert(i < tableNumEntries());
    
    return *(getEntry(i).value);
  }

  ostream& save(ostream& ostrm) const;
};


#endif	// ASM_STRING_TABLE_H


