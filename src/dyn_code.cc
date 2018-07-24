// dyn_code.cc - Dynamic code area management.
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
// $Id: dyn_code.cc,v 1.13 2006/01/31 23:17:50 qp Exp $

#include "config.h"
#include "global.h"
#include "code.h"
#include "thread_qp.h"
#include "dynamic_code.h"

extern Code *code;
extern PredTab *predicates;

//#include "dynamic_hash_table.cc"

CodeLoc getFirstUnretractedClause(CodeLoc code)
{
  CodeLoc current = code;
  while(current != NULL)
    {
      CodeLoc clloc = current + Code::SIZE_OF_INSTRUCTION 
	+ Code::SIZE_OF_NUMBER + Code::SIZE_OF_ADDRESS;
      CodeLoc cl = getCodeLoc(clloc);
      if (getInstruction(cl) != FAIL)
	{
	  return current;
	}
      CodeLoc next = current + OFFSET_TO_LAST_ADDRESS;
      current = getCodeLoc(next);
    }
  return current;
}

//
// psi_code_top(variable)
// Return the top of the code area.
// mode(out)
//
Thread::ReturnValue
Thread::psi_code_top(Object*& object1)
{
  object1 = heap.newInteger(reinterpret_cast<wordptr>(code->getTop()));
  
  return(RV_SUCCESS);
}


//
// psi_get_opcode(opcode, pc, offset)
// Get an opcode from the code area at offset from pc.
// mode(out,in,in)
//
Thread::ReturnValue
Thread::psi_get_opcode(Object*& object1, Object*& object2, Object*& object3)
{
  CodeLoc	offset;

  Object* val2 = object2->variableDereference();
  Object* val3 = object3->variableDereference();  
  
  assert(val2->isNumber());
  assert(val3->isNumber());
  
  CodeLoc pc = reinterpret_cast<CodeLoc>(val2->getInteger());
  offset = pc + val3->getInteger();
  
  object1 = heap.newInteger(getInstruction(offset));
  
  return(RV_SUCCESS);
}

//
// psi_get_const(constant, buffer, offset)
// Get a constant from the code area at offset from buffer.
// mode(out,in,in)
//
Thread::ReturnValue
Thread::psi_get_const(Object*& object1, Object*& object2, Object*& object3)
{
  CodeLoc	offset;
  Object* val2 = object2->variableDereference();
  Object* val3 = object3->variableDereference();  
  
  assert(val2->isNumber());
  assert(val3->isNumber());
  
  offset = reinterpret_cast<CodeLoc>(val2->getInteger() + val3->getInteger());
  
  object1 = getConstant(offset);
  
  return(RV_SUCCESS);
}

//
// psi_get_integer(constant, buffer, offset)
// Get an integer from the code area at offset from buffer.
// mode(out,in,in)
//
Thread::ReturnValue
Thread::psi_get_integer(Object*& object1, Object*& object2, Object*& object3)
{
  CodeLoc	offset;
  
  Object* val2 = object2->variableDereference();
  Object* val3 = object3->variableDereference();  
    
  assert(val2->isNumber());
  assert(val3->isNumber());
  
  offset = reinterpret_cast<CodeLoc>(val2->getInteger() + val3->getInteger());

  object1 = heap.newInteger(getInteger(offset));
  
  return(RV_SUCCESS);
}

//
// psi_get_double(constant, buffer, offset)
// Get a double from the code area at offset from buffer.
// mode(out,in,in)
//
Thread::ReturnValue
Thread::psi_get_double(Object*& object1, Object*& object2, Object*& object3)
{
  CodeLoc	offset;
  
  Object* val2 = object2->variableDereference();
  Object* val3 = object3->variableDereference();  
    
  assert(val2->isNumber());
  assert(val3->isNumber());
  
  offset = reinterpret_cast<CodeLoc>(val2->getInteger() + val3->getInteger());

  object1 = heap.newDouble(getDouble(offset));
  
  return(RV_SUCCESS);
}


//
// psi_get_number(number, buffer, offset)
// Get a number from the code area at offset from buffer.
// mode(out,in,in)
//
Thread::ReturnValue
Thread::psi_get_number(Object*& object1, Object*& object2, Object*& object3)
{
  CodeLoc	offset;
  Object* val2 = object2->variableDereference();
  Object* val3 = object3->variableDereference();  
    
  assert(val2->isNumber());
  assert(val3->isNumber());
  
  offset = reinterpret_cast<CodeLoc>(val2->getInteger() + val3->getInteger());
   
  object1 = heap.newInteger(getNumber(offset));
  
  return(RV_SUCCESS);
}

//
// psi_get_address(address, buffer, offset)
// Get an address from the code area at offset from buffer.
// mode(out,in,in)
//
Thread::ReturnValue
Thread::psi_get_address(Object*& object1, Object*& object2, Object*& object3)
{
  CodeLoc	offset;
  
  Object* val2 = object2->variableDereference();
  Object* val3 = object3->variableDereference();  
    
  assert(val2->isNumber());
  assert(val3->isNumber());
  
  offset = reinterpret_cast<CodeLoc>(val2->getInteger() + val3->getInteger());

  object1 = heap.newInteger(getAddress(offset));
  
  return(RV_SUCCESS);
}

//
// psi_get_offset(offset, buffer, offset)
// Get an offset from the code area at offset from buffer.
// mode(out,in,in)
//
Thread::ReturnValue
Thread::psi_get_offset(Object*& object1, Object*& object2, Object*& object3)
{
  CodeLoc	offset;
  Object* val2 = object2->variableDereference();
  Object* val3 = object3->variableDereference();  
    
  assert(val2->isNumber());
  assert(val3->isNumber());
  
  offset = reinterpret_cast<CodeLoc>(val2->getInteger() + val3->getInteger());

  object1 = heap.newInteger(getOffset(offset));
  
  return(RV_SUCCESS);
}

//
// psi_get_pred(predicate atom, buffer, offset)
// Get a predicate atom from the code area at offset from buffer.
// mode(out,in,in)
//
Thread::ReturnValue
Thread::psi_get_pred(Object*& object1, Object*& object2, Object*& object3)
{
  CodeLoc	offset;
  Object* val2 = object2->variableDereference();
  Object* val3 = object3->variableDereference();  
    
  assert(val2->isNumber());
  assert(val3->isNumber());
  
  offset = reinterpret_cast<CodeLoc>(val2->getInteger() + val3->getInteger());

  object1 = getPredAtom(offset);
  
  return(RV_SUCCESS);
}

//
// psi_get_entry(pc, linkblock, predtype)
// Get the code for this block.
// mode(out,in, out)
//
Thread::ReturnValue
Thread::psi_get_entry(Object*& object1, Object*& object2, Object*& object3)
{
  Object* val2 = object2->variableDereference();
  assert(val2->isNumber());
  assert(val2->getInteger() != 0);
  LinkedClause* clause = (LinkedClause*)(val2->getInteger());
  CodeLoc pc = clause->getCodeBlock()->getCode();
  
  object1 = heap.newInteger(reinterpret_cast<wordptr>(pc));
  object3 = heap.newInteger(0);
  return(RV_SUCCESS);
}

//
// psi_reset_entry(predicate, arity)
// Abolish the predicate definition. 
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_reset_entry(Object*& object1, Object*& object2)
{
  Object* val1 = object1->variableDereference();
  Object* val2 = object2->variableDereference();  
  
  assert(val1->isAtom());
  assert(val2->isNumber());
  
  predicates->resetEp(OBJECT_CAST(Atom*, val1), val2->getInteger(), atoms, code);
  
  return(RV_SUCCESS);
}

//
// psi_assert(Head, Assembled, FirstLast, Ref).
// mode(in,in,in,out).
//
Thread::ReturnValue
Thread::psi_assert(Object*& object1, Object*& object2, 
		   Object*& object3, Object*& object4)
{
  code->Stamp();
  Object *pred, *indexarg;
  int arity;
  PredLoc loc;
  
  Object* val1 = object1->variableDereference();
  Object* val3 = object3->variableDereference();
  assert(object2->variableDereference()->isInteger());
  //  CodeLoc pc = (CodeLoc)(object4->variableDereference()->getInteger());
  
  if (val1->isAtom())
    {
      arity = 0;
      pred = val1;
      indexarg = val1;
      loc = predicates->lookUp(OBJECT_CAST(Atom*, val1), 0, atoms, code);
      if (loc == EMPTY_LOC)
	{
	  DynamicPredicate* dp = new DynamicPredicate(0);
	  loc = 
	    predicates->addDynamicPredicate(atoms, 
					    OBJECT_CAST(Atom*, val1),
					    0, dp, code);
	}
    }
  else 
    {
      assert(val1->isStructure());
      Structure* str = OBJECT_CAST(Structure*, val1);
      arity = static_cast<int>(str->getArity());
      pred = heap.dereference(str->getFunctor());
      assert(pred->isAtom());
      loc = predicates->lookUp(OBJECT_CAST(Atom*, pred), arity, atoms, code);
      if (loc == EMPTY_LOC)
	{
	  DynamicPredicate* dp = new DynamicPredicate(arity);
	  loc = predicates->addDynamicPredicate(atoms, 
						OBJECT_CAST(Atom*, pred), 
						arity, dp, code);
	}
    }
  assert(val3->isInteger());
  bool asserta = (val3->getInteger() == 0);
  DynamicPredicate* dp =  predicates->getCode(loc).getDynamicPred();
  int index = (int)(dp->getIndexedArg());
  indexarg = NULL;
  if ((arity != 0) && (index != 255))
    {
      indexarg = 
	OBJECT_CAST(Structure*, val1)->getArgument(1 + index);
    }
#ifdef QP_DEBUG_ASSERT
  cerr << "======= assert ==========" << endl;
  dp->display();
#endif
  dp->assertClause(*this, indexarg, object2, asserta); 
  dp->Stamp();
  dp->AssertStamp();
#ifdef QP_DEBUG_ASSERT
  dp->display();
#endif

  object4 = heap.newInteger(0);
  return(RV_SUCCESS);
}

//
// psi_retract(Ref).
// retract clause with reference Ref.
// mode(in).
//
Thread::ReturnValue
Thread::psi_retract(Object*& object1)
{
  code->Stamp();
  Object* val1 = object1->variableDereference();
  assert(val1->isNumber());
  LinkedClause* clause = (LinkedClause*)(val1->getInteger());
  CodeBlock* codeb = clause->getCodeBlock();

  DynamicPredicate* pred = codeb->getThisPred();
  pred->makeDirty();
  pred->Stamp();
  pred->RetractStamp();
  codeb->setDelete(pred->GetStamp());

  return(RV_SUCCESS);
}

// Get the timestamp for a predicate
// mode psi_predicate_stamp(in,in,out)
//
Thread::ReturnValue
Thread::psi_predicate_stamp(Object*& object1, Object*& object2,
                            Object*& object3)
{
  bool is_minus = false;
  bool is_plus = false;
  Object* pred = object1->variableDereference();
  if (pred->isStructure()) {
    Structure* predstr = OBJECT_CAST(Structure*, pred);
    Object* functor = predstr->getFunctor()->variableDereference();
    if (functor == AtomTable::minus) {
      is_minus = true;
    } else {
      is_plus = true;
    }
    pred = predstr->getArgument(1)->variableDereference();
  }
  Object* arityObject = object2->variableDereference();
  
  int arity = arityObject->getInteger();
  
  PredLoc loc = predicates->lookUp(OBJECT_CAST(Atom*, pred), arity,
				   atoms, code);
  if (loc == EMPTY_LOC)
    {
      return(RV_FAIL);
    }
  else if ((predicates->getCode(loc)).type() == PredCode::DYNAMIC_PRED)
    {
      DynamicPredicate* dp =  predicates->getCode(loc).getDynamicPred();
      int s;
      if (is_minus) {
        s = dp->GetRetractStamp();
      } else if (is_plus) {
        s = dp->GetAssertStamp();
      } else {
        s = dp->GetStamp();
      }
      object3 = heap.newInteger(s);
      return(RV_SUCCESS);
    }
  else
    {
      return(RV_FAIL);
    }

}

// Get the P/N info if the timestamps have changed
// mode psi_predicate_stamp_change(in,in,out)
//
Thread::ReturnValue
Thread::psi_predicate_stamp_change(Object*& object1, Object*& object2,
				   Object*& object3)
{
  Object* pred = object1->variableDereference();
  Object* arityObject = object2->variableDereference();
  
  int arity = arityObject->getInteger();
  
  PredLoc loc = predicates->lookUp(OBJECT_CAST(Atom*, pred), arity,
				   atoms, code);
  if (loc == EMPTY_LOC)
    {
      return(RV_FAIL);
    }
  else if ((predicates->getCode(loc)).type() == PredCode::DYNAMIC_PRED)
    {
      DynamicPredicate* dp =  predicates->getCode(loc).getDynamicPred();
      object3 = heap.newInteger(dp->GetStamp());
      return(RV_SUCCESS);
    }
  else
    {
      return(RV_FAIL);
    }

}

//
// psi_dynamic(pred, arity, indexArg, hashtablesize)
// Declare pred/arity as a dynamic predicate with indexArg (default = 1)
// and hashtablesize (default = 4)
// mode(in,in,in,in).
Thread::ReturnValue
Thread::psi_dynamic(Object*& object1, Object*& object2, 
		    Object*& object3, Object*& object4)
{
  Object* pred = object1->variableDereference();
  Object* arityObject = object2->variableDereference();
  Object* indexArgObject = object3->variableDereference();
  Object* tableSizeObject = object4->variableDereference();
  
  if (pred->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  else if (!pred->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  //
  // pred is an atom
  //
  if (arityObject->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  else if (!arityObject->isNumber())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  //
  // arity is a number
  //
  int arity = arityObject->getInteger();
  
  if (indexArgObject->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 3);
    }
  else if (!indexArgObject->isNumber())
    {
      PSI_ERROR_RETURN(EV_TYPE, 3);
    }
  
  int indexArg = indexArgObject->getInteger();
  
  if ((arity > 0) && ((indexArg < 0) || (indexArg > arity)))
    {
      PSI_ERROR_RETURN(EV_RANGE, 3);
    }
  //
  // indexArg is a number in range
  //
  
  if (tableSizeObject->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 4);
    }
  else if (!tableSizeObject->isNumber())
    {
      PSI_ERROR_RETURN(EV_TYPE, 4);
    }
  int tableSize = tableSizeObject->getInteger();
  if (tableSize < 1)
    { 
      PSI_ERROR_RETURN(EV_RANGE, 4);
    }
  //
  // tableSize is a positive int
  //
  
  PredLoc loc = predicates->lookUp(OBJECT_CAST(Atom*, pred), arity,
				   atoms, code);
  if (loc == EMPTY_LOC)
    {
      DynamicPredicate* dp 
	= new DynamicPredicate(arity, indexArg-1, tableSize);
      loc = predicates->addDynamicPredicate(atoms, OBJECT_CAST(Atom*, pred), 
					    arity, dp, code);
      return(RV_SUCCESS);
    }
  else if ((predicates->getCode(loc)).type() == PredCode::DYNAMIC_PRED)
    {
      return(RV_SUCCESS);
    }
  else
    {
      return(RV_FAIL);
    }
}


//
// psi_get_dynamic_chain(predicate, chain)
// Get the entry point to a predicate.
// mode(in, out)
//
Thread::ReturnValue
Thread::psi_get_dynamic_chain(Object*& object1, Object*& object2)
{
#if 0
  int   arity;
  Object* predObject;
  
  Object* val1 = object1->variableDereference();

  if (val1->isAtom())
    {
      predObject = val1;
      arity = 0;
    }
  else
    {
      assert(val1->isStructure());
      Structure* str = OBJECT_CAST(Structure*, val1);
      arity = str->getArity();
      predObject = str->getFunctor();
    }
  
  const PredLoc loc = 
    predicates->lookUp(OBJECT_CAST(Atom*, predObject), arity, atoms, code);
  if (loc == EMPTY_LOC)
    {
      return(RV_FAIL);
    }
  const PredCode pred = predicates->getCode(loc);
  
  if (pred.type() != PredCode::DYNAMIC_PRED)
    {
      return (RV_FAIL);
    }

  Object* argObject;
  
  const word8 arg = pred.getDynamicPred()->getIndexedArg();
  //assert(arity == 0 || arg < arity);
  if ((int)(arg) == 255) {
    argObject = NULL;
  } else if (arity == 0)
    {
      argObject = AtomTable::nil; 
    }
  else
    {
      argObject = OBJECT_CAST(Structure*, val1)->getArgument(arg+1);
    }
  ChainEnds* chain 
    = pred.getDynamicPred()->lookUpClauseChain(*this, argObject);
  if (chain->first() == NULL)
    {
      return RV_FAIL;
    }
  CodeLinkingBlock* start = chain->first()->getNext()->nextUnretractedBlock();
  if (start == NULL)
    {
      return RV_FAIL;
    }
  start->aquire();
  RefObject r(start, NULL);
  refTrail.trail(r);
  object2 = heap.newInteger(reinterpret_cast<wordptr>(start));
#endif
  return RV_SUCCESS;
}

//
// psi_get_first_clause(pred, time, ref, more)
// Get the first linkblock ptr for the predicate
// more is true if there are subsequent clauses
//
Thread::ReturnValue
Thread::psi_get_first_clause(Object*& object1, Object*& object2,
			     Object*& object3, Object*& object4)
{
  int   arity;
  Object* predObject;
  
  Object* val1 = object1->variableDereference();

  if (val1->isAtom())
    {
      predObject = val1;
      arity = 0;
    }
  else
    {
      assert(val1->isStructure());
      Structure* str = OBJECT_CAST(Structure*, val1);
      arity = static_cast<int>(str->getArity());
      predObject = str->getFunctor()->variableDereference();
    }
  
  const PredLoc loc = 
    predicates->lookUp(OBJECT_CAST(Atom*, predObject), arity, atoms, code);
  if (loc == EMPTY_LOC)
    {
      return(RV_FAIL);
    }
  const PredCode pred = predicates->getCode(loc);
  
  if (pred.type() != PredCode::DYNAMIC_PRED)
    {
      return (RV_FAIL);
    }

  Object* argObject = NULL;
  
  const word8 arg = pred.getDynamicPred()->getIndexedArg();
    //assert(arity == 0 || arg < arity);
  if ((int)(arg) == 255) {
    argObject = NULL;
  } else if (arity == 0) {
    argObject = AtomTable::nil; 
  } else {
    argObject = OBJECT_CAST(Structure*, val1)->getArgument(arg+1)->variableDereference();
  }
  DynamicPredicate* dp = pred.getDynamicPred();
  ChainEnds* chain = dp->lookUpClauseChain(*this, argObject);
  assert(object2->variableDereference()->isInteger());
  word32 time = (word32)(object2->variableDereference()->getInteger());

  if (chain->first() == NULL)
    {
      return RV_FAIL;
    }

  LinkedClause* clause = chain->first()->nextAlive(time);
  if (clause == NULL)
    {
      return RV_FAIL;
    }
  object3 = heap.newInteger(reinterpret_cast<wordptr>(clause));
  otherTrail.push(dp);
  dp->aquire();
  LinkedClause* next_clause = clause->nextNextAlive(time); 
  if (next_clause == NULL)
    {
      object4 = AtomTable::failure;
    }
  else
    {
      object4 = AtomTable::success;
    }
  return(RV_SUCCESS);
}


//
// psi_get_next_clause(ptr, time, next, more)
// Get the next linkblock ptr for ptr.
// mode(in, out, out)
//
Thread::ReturnValue
Thread::psi_get_next_clause(Object*& object1, Object*& object2,
			    Object*& object3, Object*& object4)
{
  Object* val1 = object1->variableDereference();

  assert(val1->isNumber());
  assert(val1->getInteger() != 0);

  assert(object2->variableDereference()->isInteger());
  word32 time = (word32)(object2->variableDereference()->getInteger());

  LinkedClause* clause = reinterpret_cast<LinkedClause*>((val1->getInteger()));
  LinkedClause* next = clause->nextNextAlive(time);

  if (next == NULL)
    {
      return RV_FAIL;
    }

  object3 = heap.newInteger(reinterpret_cast<wordptr>(next));
  next = next->nextNextAlive(time);
  if (next == NULL)
    {
      object4 = AtomTable::failure;
    }
  else
    {
      object4 = AtomTable::success;
    }
  return(RV_SUCCESS);
}










