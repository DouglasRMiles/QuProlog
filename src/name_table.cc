// name_table.h - Definitions of the name table for storing variable names
// and the implicit parameter table for storing implicit parameters.
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
// $Id: name_table.cc,v 1.4 2006/01/31 23:17:51 qp Exp $

#include "area_offsets.h"
#include "atom_table.h"
#include "objects.h"
//#include "heap.h"
#include "name_table.h"
#include "thread_qp.h"
#include "trail.h"

//
// Add a new entry or update an entry in the name table.
//
void
NameTable::set(NameEntry key, Thread& th)
{
  NameEntry&	entry = getEntry(search(key));
  Atom*&     	name = entry.getName();
  heapobject*   valuePtr = entry.getValueAddr();

  assert(entry.isEmpty());
      //
      // Add a new entry.
      //
  assert(! key.getValue()->isSubstitutionBlock());
  th.updateAndTrailObject(valuePtr, key.getValue(), 0);
  name = key.getName();
}

void
NameTable::setNameNewVar(Atom* index, Object* var, Thread& th)
{
  assert(var->isAnyVariable());
  setVariableName(index, var, th);
  OBJECT_CAST(Reference*, var)->setName(index);
}

void
NameTable::setNameOldVar(Atom* index, Object* var, Thread& th)
{
  assert(var->isAnyVariable());
  assert(OBJECT_CAST(Reference*, var)->hasExtraInfo());
  setVariableName(index, var, th);
  th.updateAndTrailObject(reinterpret_cast<heapobject*>(var), index, 
			  Reference::NameOffset);
}
  

//
// Add a new entry or update an entry in the IP table.
//
void
IPTable::set(IPEntry key, Thread& th)
{
  IPEntry&	entry = getEntry(search(key));
  
  assert(!key.getValue()->isSubstitutionBlock());
  if (entry.isEmpty())
    {
      //
      // Add a new entry.
      //
      th.updateAndTrailIP(entry.getNameAddress(), key.getName());
      th.updateAndTrailIP(entry.getValueAddr(), key.getValue());
    }
  else
    {
      //
      // Overwrite the value of an existing entry.
      //
      th.updateAndTrailIP(entry.getValueAddr(), key.getValue());
    }
}








