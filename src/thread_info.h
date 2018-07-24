// thread_info.h - Thread identification, etc.
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
// $Id: thread_info.h,v 1.7 2006/01/31 23:17:52 qp Exp $

#ifndef THREAD_INFO_H
#define THREAD_INFO_H

#include <iostream>

#include "config.h"

#include "heap_qp.h"
//#include "symbol_info.h"
#include "thread_table_loc.h"

class ThreadInfo
{
private:
  // Location in global thread table.
  bool thread_table_loc_set;
  bool is_forbid_thread;
  bool symbol_set;

  // Is this an initial thread?
  const bool initial;

  // Initial Prolog goal of this thread.
  Object* goal;

  ThreadTableLoc thread_table_loc;
  // Thread symbol
  string symbol;

public:
  explicit ThreadInfo(Thread *pt)
    : thread_table_loc_set(false),
    is_forbid_thread(false),
    symbol_set(false),
    initial(pt == NULL),
    goal(NULL)
  {
  }

  ~ThreadInfo(void)
    { }

  bool IDSet(void) const { return thread_table_loc_set; }
  ThreadTableLoc ID(void) const
  {
    assert(thread_table_loc_set);
    return thread_table_loc;
  }
  void SetID(const ThreadTableLoc ttl)
  {
    thread_table_loc = ttl;
    thread_table_loc_set = true;
  }

  bool Initial(void) const { return initial; }

  Object*& Goal(void) { return goal; }

  void setForbidThread(bool is_forbid) { is_forbid_thread = is_forbid; }

  bool isForbidThread(void) const { return is_forbid_thread; }

  bool SymbolSet(void) const { return symbol_set; }

  const string& Symbol(void) const
  {
    return symbol;
  }

  void SetSymbol(const string& s)
  {
    symbol_set = true;
    symbol = s;
  }

  ostream& Display(ostream& ostrm, AtomTable& atoms, Heap& heap);
};

#endif // THREAD_INFO_H
