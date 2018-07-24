// timeout.cc - 
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
// $Id: timeout.cc,v 1.6 2006/02/14 02:40:09 qp Exp $

// #include "atom_table.h"
#include "heap_qp.h"

bool
Heap::IsTimeout(Object* cell)
{
  if (cell->isAtom())
    {
      return (cell == AtomTable::block);
    }
  else if (cell->isInteger())
    {
      return cell->getInteger() >= 0;
    }
  else 
    {
      return (cell->isDouble() && (cell->getDouble() >= 0));
    }
}

double
Heap::DecodeTimeout(Object* cell)
{
  if (cell->isAtom())
    {
      if (cell == AtomTable::block)
	{
	  return -1;
	}
      else
	{
	  assert(false);
	}
    }
  else if (cell->isInteger() && cell->getInteger() >= 0)
    {
      return (cell->getInteger());
    }
  else if (cell->isDouble() && cell->getDouble() >= 0)
    {
      return (cell->getDouble());
    }

  // Should never get here!
  assert(false);

  return 0;
}







