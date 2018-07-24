// thread_info.cc -
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
// $Id: thread_info.cc,v 1.3 2002/11/10 07:54:54 qp Exp $

#include <iostream>

#include "thread_info.h"

ostream&
ThreadInfo::Display(ostream& ostrm, AtomTable& atoms, Heap& heap)
{
  ostrm << (SymbolSet() ? Symbol().c_str() : "");
  
  ostrm << ' ';
  
  if (Initial())
    {
      ostrm << "<Initial Thread>";
    }
  else if (goal != NULL)
    {
      heap.quickDisplayTerm(ostrm, atoms, goal);
    }

  return ostrm;
}

