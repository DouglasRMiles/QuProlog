// asm_string_table.cc -
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
// $Id: asm_string_table.cc,v 1.6 2005/03/08 00:34:59 qp Exp $

#include "asm_string_table.h"
#include "code.h"

template <class EntryType>
ASMTable<EntryType>::ASMTable(int size)
{
  table_size = size;
  
  table = new EntryType[table_size];
  
  table_num_entries = 0;
}

template <class EntryType>
ASMTable<EntryType>::~ASMTable(void)
{
  delete [] table;
}

ostream&
ASMStringTable::save(ostream& ostrm) const
{
  // Count up all the characters
  Code::AddressSizedType num_bytes = 0;
  
  for (ASMLoc i = 0; i < tableNumEntries(); i++)
    {
      // Number of characters + 1 for null byte
      num_bytes += static_cast<Code::AddressSizedType>((getEntry(i).value)->length() + 1);
    }
  
  // Write out the number of bytes
  IntSave<Code::AddressSizedType>(ostrm, num_bytes);
  
  // Write out the strings.
  for (ASMLoc i = 0; i < tableNumEntries(); i++)
    {
      ostrm << *(getEntry(i).value) << ends;
      if (ostrm.fail())
	{
	  SaveFailure(__FUNCTION__, "strings");
	}
    }
  
  return ostrm;
}


template class ASMTable <ASMStringPointer>;













