// pred_table.h - The predicate table is a hash table providing the link
//		  between the predicate name and its code.  Each entry is
//		  hashed on the predicate name and its arity.  Rather using
//		  the string of the predicate name, the atom is used.
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
// $Id: pred_table.cc,v 1.4 2002/12/05 03:39:32 qp Exp $

#include "area_offsets.h"
#include "atom_table.h"
#include "code.h"
#include "defs.h"
#include "global.h"
#include "hash_table.h"
#include "pred_table.h"

//
// Constructor:
//	Initialise the table with escape functions.
//
PredTab::PredTab(AtomTable* atoms, word32 TableSize) :
  HashTable <PredEntry, PredEntry> (TableSize)
{
#define DefEscape(escape, arity, fn)	\
	insertEscape((escape), (arity), atoms)
#include "escapes.h"
#undef DefEscape
}

//
// Add a new entry to the predicate table.
//
PredLoc
PredTab::add(AtomTable* atoms,
	     Atom* PredName, const word32 arity, const PredCode code,
	     Code* codePtr)
{
  PredEntry	input;
  input.assign(PredName, arity, code, atoms);
  const PredLoc	index = search(input);
  PredEntry& entry = getEntry(index);
  if (! entry.isEmpty())
    {
      //
      // Redefined the predicate.
      //
      ostringstream os;
      os << "new definition for " << PredName->getName() 
	 << "/" << arity << " is ignored";
      Warning(__FUNCTION__, os.str().c_str()); 
      return(index);
    }
  
  //
  // Add/overwrite with the new entry.
  //
  entry.assign(PredName, arity, code, atoms);
  
  //
  // Return the location of string in the atom table.
  // 
  return(index);
}

//
// Reset the code location (Entry point) to NULL.
// This is used by the buffer code and is a spin-off from sbprolog.
//
void
PredTab::resetEp(Atom* PredName, const word32 arity, AtomTable* atoms, 
		 Code* code)
{
  PredCode        pred;
  pred.makePredicate(PredCode::STATIC_PRED, NULL, code);
  
  PredEntry       input;
  input.assign(PredName, arity, pred, atoms);
  
  const PredLoc index = search(input);
  PredEntry& entry = getEntry(index);
  
  //
  // Overwrite with NULL 
  //
  entry.assign(NULL, 0, pred, atoms);
}

//
// Link an escape function with its name.
//
void
PredTab::linkEscape(AtomTable* atoms, 
		    const char *name, const word32 arity, const EscFn f)
{
  PredCode        escape;
  PredLoc		index;
  
  escape.makeEscape(f);
  index = lookUp(atoms->getAtom(atoms->lookUp(name)), arity, atoms, code);
  if (index == EMPTY_LOC)
    {
      ostringstream os;
      os << "escape function " << name << 
	"/" << arity << " is not installed";
      Warning(__FUNCTION__, os.str().c_str());
    }
  else
    {
      getCode(index) = escape;
    }
}







