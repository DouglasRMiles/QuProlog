// thread_table.cc -
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
// $Id: thread_table.cc,v 1.8 2006/01/31 23:17:52 qp Exp $

#include <sys/types.h>
#include <sstream>

#include "config.h"

#include "thread_qp.h"
#include "thread_info.h"
#include "thread_table.h"

//
// Hash table for mapping from thread names to thread ids.
//
string&
ThreadTable::MakeName(const ThreadTableLoc loc)
{
  ostringstream strm;
  ThreadHashTableEntry entry;
  entry.setSymbol(&symbol);

  while (true)
    {
      strm.str("");
      strm << "thread" <<  next_id;
      symbol = strm.str();
      int index = hash_table.search(entry);
      next_id++;
      if (index == -1)
	{
          ThreadHashTableEntry* new_entry = new ThreadHashTableEntry;
	  new_entry->Assign(loc, symbol);
          hash_table.insert(*new_entry, index);
          return (symbol);
	}
    }
  assert(false);
  return (symbol);
}
//
// Hash table for mapping from thread names to thread ids.
//
string&
ThreadTable::MakeName(const ThreadTableLoc loc, const char * rootname)
{
  ostringstream strm;
  ThreadHashTableEntry entry;
  entry.setSymbol(&symbol);

  int id = 0;
  while (true)
    {
      strm.str("");
      strm << rootname <<  id;
      symbol = strm.str();
      int index = hash_table.search(entry);
      if (index == -1)
	{
          ThreadHashTableEntry* new_entry = new ThreadHashTableEntry;
	  new_entry->Assign(loc, symbol);
          hash_table.insert(*new_entry, index);
          return (symbol);
	}
      id++;
    }
  assert(false);
  return (symbol);
}

bool
ThreadTable::AddName(const string& symbol,	// Name of the thread
		     const ThreadTableLoc loc)	// Thread id
{
  string sym(symbol);
  ThreadHashTableEntry entry;
  entry.setSymbol(&sym);

  int index = hash_table.search(entry);
  if (index == -1)
    {
      ThreadHashTableEntry* new_entry = new ThreadHashTableEntry;
      new_entry->Assign(loc, symbol);
      hash_table.insert(*new_entry, index);

      return true;
    }
  else
    {
      return false;
    }
}

ThreadTableLoc
ThreadTable::LookupName(const string& str) const
{
  string sym(str);
  ThreadHashTableEntry entry;
  entry.setSymbol(&sym);

  const int index = hash_table.search(entry);
  if (index == -1)
    {
      return (ThreadTableLoc) -1;
    }
  return hash_table.getEntry(index).Loc();
}

void
ThreadTable::RemoveName(const string& symbol)
{ 
  string sym(symbol);
  ThreadHashTableEntry entry;
  entry.setSymbol(&sym);

  const int index = hash_table.search(entry);
  if (index != -1)
    {
      hash_table.getEntry(index).makeRemoved();
    }
}

ThreadTableLoc
ThreadTable::AddID(Thread *thread)
{
  assert(thread != NULL);

  if (live < size)
    {
      ThreadTableLoc loc;

      for (loc = 0;
	   array[loc] != NULL;
	   loc++)
	;

      array[loc] = thread;

      return loc;
    }
  else
    {
      return (ThreadTableLoc) -1;
    }
}

Thread *
ThreadTable::LookupID(const ThreadTableLoc loc)
{
  assert(IsValid(loc));

  return array[loc];
}

const Thread *
ThreadTable::operator[](const ThreadTableLoc loc) const
{
  assert(IsValid(loc));

  return array[loc];
}

void
ThreadTable::RemoveID(const ThreadTableLoc loc)
{
  assert(IsValid(loc) && array[loc] != NULL);

  array[loc] = NULL;
}

ostream&
operator<<(ostream& ostrm, ThreadTable& thread_table)
{
  ostrm << "QPID\tSYMBOL\tGOAL" << endl;

  for (ThreadTableLoc loc = 0;
       loc < thread_table.Size();
       loc++)
    {
      if (thread_table[loc] != NULL)
	{
	  Thread& thread = *(thread_table.LookupID(loc));

	  ostrm << loc << "\t";
	  ostrm << thread << endl;
	}
    }

  return ostrm;
}

