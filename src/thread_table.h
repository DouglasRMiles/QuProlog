// thread_table.h -
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
// $Id: thread_table.h,v 1.11 2006/01/31 23:17:52 qp Exp $

#ifndef	THREAD_TABLE_H
#define	THREAD_TABLE_H

#include <sys/types.h>
#include <string>

#include "defs.h"
#include "hash_qp.h"
#include "dynamic_hash_table.h"
//#include "string_qp.h"
#include "thread_table_loc.h"

class Thread;

class ThreadHashTableEntry
{
 private:
  bool removed;		// Has the entry been removed?
  ThreadTableLoc loc;	// Location of thread.
  string *symbol;		// The symbol.
 public:
  ThreadHashTableEntry(void) : removed(false), loc(0), symbol(NULL) { }
  
  ThreadHashTableEntry(string* s) : removed(false), loc(0), symbol(s) { }
  
  
  bool isEmpty(void) const { return (symbol == NULL); }
  
  bool isRemoved(void) const { return removed; }

  void makeRemoved(void) { removed = true; }  

  ThreadTableLoc Loc(void) const
    {
      assert(! removed);
      return loc;
    }
  string& Symbol(void)
    {
      assert(! removed);
      assert(symbol != NULL);
      return *symbol;
    }
  const string& InspectSymbol(void) const
    {
      assert(! removed);
      assert(symbol != NULL);
      return *symbol;
    }
  
  void clearEntry(void)
    {
      removed = false;
      delete symbol;
      symbol = NULL;
    }
  
  void setSymbol(string* s)
    {
      symbol = s;
    }
  
  void Assign(const ThreadTableLoc l,
	      const string& s)
    {
      removed = false;
      loc = l;
      symbol = new string(s);
    }
  
  bool operator==(const ThreadHashTableEntry& tte) const
    {
      if (symbol == tte.symbol) return true;
      if ((symbol == NULL) || (tte.symbol == NULL)) return false;
      return (*symbol == (*tte.symbol));
    }
  
  int hashFn(void) const
    {
      assert(symbol != NULL);
      return Hash(symbol->c_str(), symbol->length());
    }
};

/*
  class HashTableKey
    {
    private:
      const string symbol;
    public:
      HashTableKey(const string& s) : symbol(s) { }
      
      const string& InspectSymbol(void) const
	{
	  return symbol;
	}

      bool operator==(const HashTableEntry& t) const
      {
	if (t.isEmpty())
	{
	  return false;
	}
	else
	{
	  return InspectSymbol() == t.InspectSymbol();
	}
      }

      word32 hashFn(void) const
      {
	return Hash(symbol.c_str(), symbol.length());
      }
    };
*/

class ThreadTableHashTable : public DynamicHashTable<ThreadHashTableEntry>
{
 public:
  explicit ThreadTableHashTable(const word32 size) :
    DynamicHashTable<ThreadHashTableEntry>(size) 
    { }
  
  const char *getAreaName(void) const { return "Thread Table"; }
  
  int hashFunction(const ThreadHashTableEntry key) const
    {
      return key.hashFn();
    }
};

class ThreadTable
{
  //
  // Hash table for associating thread names with thread id's.
  //


private:
  // Hash table from name to thread id.
  ThreadTableHashTable hash_table;
  
  // Array from thread id to thread.
  Thread **array;
  
  // Number of live threads.
  word32 live;
  
  // Next thread id.
  word32 next_id;

  // Size of the hash table and the array.
  const word32 size;

  // String to hold thread name
  string symbol;

  // String to hold default message thread
  string default_thread;

 public:
  typedef Thread* ThreadPtr;
  explicit ThreadTable(const word32 TableSize = THREAD_TABLE_SIZE)
    : hash_table(TableSize),
      live(0),
      next_id(0),
      size(TableSize)
    {
      array = new ThreadPtr[size];
      
      for (size_t i = 0; i < size; i++)
	{
	  array[i] = NULL;
	}
      
      default_thread = "thread0";
    }

  //
  // Operations on the thread name->thread id hash table.
  // A thread must have a slot in the thread array before these
  // operations can have meaning.
  //

  // Create a name of the form threadN for the given thread
  string& MakeName(const ThreadTableLoc loc);
  string& MakeName(const ThreadTableLoc loc, const char * rootname);

  // Add a thread's name.
  bool AddName(const string&,	        	// Name of thread
	       const ThreadTableLoc);	// Thread id

  // Lookup a thread given its name. Returns (ThreadTableLoc) -1 when
  // the name can't be found.
  ThreadTableLoc LookupName(const string&) const;

  // Remove a thread's name.
  void RemoveName(const string&);

  //
  // Operations on the thread id array.
  //
  
  bool IsValid(const ThreadTableLoc loc) const
    {
      return loc < size;
    }
  
  // Return the size of the hash table.
  word32 Size(void) const { return size; }

  // Reserve a slot in the thread id array for the thread.
  ThreadTableLoc AddID(Thread *);

  // Look up the thread.
  Thread *LookupID(const ThreadTableLoc);

  const Thread *operator[](const ThreadTableLoc) const;

  // Remove the thread.
  void RemoveID(const ThreadTableLoc);

  size_t Live(void) const { return live; }
  void IncLive(void) { live++; }
  void DecLive(void) { live--; }

  void setDefaultThread(string name) { default_thread = name; }

  string getDefaultThread(void) { return default_thread; }
};

// Print out some information about a thread table in
// a form that can be read by a person.
extern ostream& operator<<(ostream& ostrm, ThreadTable&);

#endif	// THREAD_TABLE_H







