// symbols.cc - Contains a function which can be used to manage the access to
//		symbol tables.
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
// $Id: symbols.cc,v 1.5 2006/01/31 23:17:51 qp Exp $

#include "global.h"
#include "atom_table.h"
#include "pred_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;
extern PredTab *predicates;

//
// psi_get_atom_from_atom_table(integer, atom, integer)
// Return the next atom in the atom table.
// mode(in,out,out)
//
Thread::ReturnValue
Thread::psi_get_atom_from_atom_table(Object *& object1, Object *& object2, 
				     Object *& object3)
{
  int32		i;
  Object* val1 = heap.dereference(object1);
  assert(val1->isNumber());

  i = val1->getInteger();

  while (++i < (signed) atoms->size())
    {
      if (! atoms->isEntryEmpty((AtomLoc)(i))) 
	{
	  object2 = atoms->getAtom((AtomLoc)(i));
	  object3 = heap.newInteger(i);
	  return(RV_SUCCESS);
	}
    }
  return(RV_FAIL);
}

//
// psi_get_pred_from_pred_table(integer, atom, integer, integer)
// Return the next predicate in the predicate table.
// mode(in,out,out,out)
//
Thread::ReturnValue
Thread::psi_get_pred_from_pred_table(Object *& object1, Object *& object2, 
				     Object *& object3, Object *& object4)
{
  int32		i;
  Object* val1 = heap.dereference(object1);
  assert(val1->isInteger());

  i = val1->getInteger();

  while (++i < (signed) predicates->size())
    {
      if (! predicates->isEmpty((PredLoc)(i))) 
	{
	  object2 = predicates->getPredName((PredLoc)(i), atoms);
	  object3 = heap.newInteger(predicates->getArity((PredLoc)(i)));
	  object4 = heap.newInteger(i);
	  return(RV_SUCCESS);
	}
    }
  return(RV_FAIL);
}

//
// symtype outputs into object3 :
//  (0)	If the predicate has no entry point defined.
//  (1) If the predicate is a dynamic predicate.
//  (2) If the predicate is a compiled predicate.
//  (3) If the predicate is an escape predicate.
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_symtype(Object *& object1, Object *& object2, Object *& object3)
{
    Object* val1 = heap.dereference(object1);
    Object* val2 = heap.dereference(object2);

    assert(val1->isAtom());
    assert(val2->isShort());

    PredLoc loc = predicates->lookUp(OBJECT_CAST(Atom*, val1), 
				     val2->getInteger(), atoms, code);
    if (loc == EMPTY_LOC) 
      {
	//
	// It does not have an entry point defined.
	//
	object3 = heap.newInteger(0);
      }
    else
      {
	PredCode pred = predicates->getCode(loc);
	switch (pred.type())
	  {
	  case PredCode::ESCAPE_PRED:
	    object3 = heap.newInteger(3);
	    break;
	  case PredCode::STATIC_PRED:
	    object3 = heap.newInteger(2);
	    break;
	  case PredCode::DYNAMIC_PRED:
	    object3 = heap.newInteger(1);
	    break;
	  }
      }
    return(RV_SUCCESS);
}








