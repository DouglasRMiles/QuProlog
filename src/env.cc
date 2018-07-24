// env.cc - Contains a set of functions which can be used for
//           assessing the overall tasks such as setting flags
//           call another functions and print out the statistics.
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
// $Id: env.cc,v 1.11 2006/02/05 22:14:55 qp Exp $

#include	<stdlib.h>
#include	<sstream>
#include	<signal.h>
#include	<stdarg.h>

#include "global.h"
#include "atom_table.h"
#include "objects.h"
#include "pred_table.h"
#include "signals.h"
#include "thread_qp.h"
#include "execute.h"

extern AtomTable *atoms;
//extern Object** lib_path;
extern PredTab *predicates;
extern Signals *signals;

Thread::ReturnValue
Thread::call_predicate(int32 noargs, ...)
{
  word32 arity;		// arity of the predicate.
  PredLoc PredCodeLoc;	// Location of predicate code.
  PredCode PredAddr;
  Object *callTerm, *functor;
  char *pred;

  va_list args;
  va_start(args, noargs);

  if (noargs == 0)
    {
      callTerm = va_arg(args, Object*);
    }
  else
    {
      assert(noargs <= MaxArity);
      callTerm = heap.newStructure(noargs);
      OBJECT_CAST(Structure*, callTerm)->setFunctor(va_arg(args, Object*));
      for (int i = 1; i <= noargs; i++)
	{
	  OBJECT_CAST(Structure*, 
		      callTerm)->setArgument(i,va_arg(args, Object*)); 
	}
    }

  callTerm = heap.dereference(callTerm);
  va_end(args);
  arity = 0;
  
  //
  // Get predicate name and arity.
  //
  if (callTerm->isAtom())
    {
      PredCodeLoc = predicates->lookUp(OBJECT_CAST(Atom*, callTerm), arity,
				       atoms, code);
    }
  else if (callTerm->isStructure())
    {
      functor = callTerm;
      do
	{
	  arity += static_cast<word32>(OBJECT_CAST(Structure*, functor)->getArity());
	  functor = OBJECT_CAST(Structure*, functor)->getFunctor()->variableDereference();
	} while (functor->isStructure());
      
      if (! functor->isAtom())
	{
	  PredCodeLoc = predicates->lookUp(AtomTable::call_exception, 1,
					   atoms, code);
	  // "$call_exception"
	  arity = 0;
	}
      else
	{
	  //
	  // Get code location from predicates.
	  //
	  if (arity > NUMBER_X_REGISTERS - 1)
	    {
	      ostringstream ostrm;
	      ostrm << OBJECT_CAST(Atom*, functor)->getName()
		    << "/" << arity << ends;
	      pred = (char*)(ostrm.str().data());
	      PredCodeLoc = 
		predicates->lookUp(atoms->getAtom(atoms->lookUp(pred)),
				   NUMBER_X_REGISTERS - 1, atoms, code);
	    }
	  else
	    {
	      PredCodeLoc = predicates->lookUp(OBJECT_CAST(Atom*, functor), 
					       arity, atoms, code);
	    }
	}
    }
  else if (callTerm->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  
  //
  // Set programCounter to interrupt code.
  //
  if (PredCodeLoc == EMPTY_LOC)
    {
      programCounter = UndefinedPred(callTerm);
      return(RV_SUCCESS);
    }
  
  // Save arity
  int save_arity = arity;

  //
  // Get parameters of the predicate.
  //
  functor = callTerm;
  if (arity > NUMBER_X_REGISTERS - 1)
    {
      int j = arity - NUMBER_X_REGISTERS + 2;
      Structure* shorten = heap.newStructure(j);
      shorten->setFunctor(AtomTable::qup_shorten);  // "$qup_shorten"
      
      int i = static_cast<int>(OBJECT_CAST(Structure*, functor)->getArity());
      while(j > 0)
	{
	  shorten->setArgument(j--, OBJECT_CAST(Structure*, 
						functor)->getArgument(i--));
	  
	  if (i == 0)
	    {
	      functor = OBJECT_CAST(Structure*, functor)->getFunctor()->variableDereference();
	      i = static_cast<int>(OBJECT_CAST(Structure*, functor)->getArity());
	    }
	}
      X[NUMBER_X_REGISTERS - 2] = shorten;
      arity = NUMBER_X_REGISTERS - 2;
      for (; i > 0; i--)
	{
	  arity--;
	  X[arity] = OBJECT_CAST(Structure*, functor)->getArgument(i);
	}
      functor = 
	OBJECT_CAST(Structure*, functor)->getFunctor()->variableDereference();
    }
  while (arity > 0)
    {
      for (int i = static_cast<int>(OBJECT_CAST(Structure*, functor)->getArity()); i > 0; i--)
	{
	  arity--;
	  X[arity] = OBJECT_CAST(Structure*, functor)->getArgument(i);
	}
      functor = 
	OBJECT_CAST(Structure*, functor)->getFunctor()->variableDereference();
    }
  //
  // Set programCounter to predicate code.
  //
  PredAddr = predicates->getCode(PredCodeLoc);
  if (PredAddr.type() == PredCode::ESCAPE_PRED)
    {
      return(PredAddr.getEscape()(getFInter()) ? RV_SUCCESS : RV_FAIL);
    }
  else if (PredAddr.type() == PredCode::DYNAMIC_PRED)
    {
      DynamicPredicate* dp = PredAddr.getDynamicPred();
      if( !initializeDPcall(dp, save_arity, programCounter))
	{
	  return(RV_FAIL);
	}
      return(RV_SUCCESS);
    }
  else
    {
      programCounter = PredAddr.getPredicate(code);
      return(RV_SUCCESS);
    }
}

//
// psi_set_flag(integer, integer).
// Sets internal system flag.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_set_flag(Object *& object1, Object *& object2)
{
  Object* val1 = object1->variableDereference();
  Object* val2 = object2->variableDereference();

  assert(val1->isShort());
  assert(val2->isShort());
  assert((val2->getInteger() == 1) || (val2->getInteger() == 0));

  switch (val1->getInteger())
    {
    case 0: 
      (val2->getInteger() == 1) ? status.setFastRetry() : status.resetFastRetry();
	break;
    case 1: 
      val2->getInteger() == 1 
	? status.setOccursCheck() 
	: status.resetOccursCheck();
	break;
    case 2: 
      (val2->getInteger() == 1) ? status.setHeatWave() : status.resetHeatWave();
	break;
    case 3: 
#if 0
      if (val2->getInteger() == 1)
	{
	  MachStatus.setEnableSignals();
	  for (u_int i = 1; i < NSIG + 1; i++)
	    {
	      if (signals->IsSet(i))
		{
		  MachStatus.setSignals();
		  break;
		}
	    }
	}
      else
	{
	  MachStatus.resetEnableSignals();
	}
#endif //0
      break;
    case 4: 
      val2->getInteger() == 1 
	? status.setDoingRetry() 
	: status.resetDoingRetry();
	break;
    case 5:
      if (val2->getInteger() == 1)
	{
	  if (!status.testTimeslicing())
	    {
	      status.setTimeslicing();
	      scheduler->Status().setEnableTimeslice();
	      TInfo().setForbidThread(false);
	    }
	}
      else
	{
	  if (status.testTimeslicing())
	    {
	      status.resetTimeslicing();
	      scheduler->Status().resetEnableTimeslice();
	      TInfo().setForbidThread(true);
	    }
	}
      break;
      
    default: 
      assert(false);
    }
  return(RV_SUCCESS);
}

//
// psi_get_flag(integer, variable).
// Gets internal system flag.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_get_flag(Object *& object1, Object *& object2)
{
  int32	state = 0;
  Object* val1 = object1->variableDereference();

  assert(val1->isShort());

  switch (val1->getInteger())
    {
    case 0: 
      state	= status.testFastRetry() ? 1 : 0;
      break;
    case 1: 
      state	= status.testOccursCheck() ? 1 : 0;
      break;
    case 2: 
      state	= status.testHeatWave() ? 1 : 0;
      break;
    case 3: 
      //      state	= MachStatus.testEnableSignals() ? 1 : 0;
      break;
    case 4: 
      state	= status.testDoingRetry() ? 1 : 0;
      break;
    case 5: 
      state	= status.testTimeslicing() ? 1 : 0;
      break;
    default: 
      assert(false);
    }
  object2 = heap.newInteger(state);
  return(RV_SUCCESS);
}

//
// psi_call_predicate0(structure)
// This function executes the nonvariable term as the term
// itself in the program text.
// mode(in)
// 
Thread::ReturnValue
Thread::psi_call_predicate0(Object *& object1)
{
  return call_predicate(0, object1);
}

//
// psi_call_predicate1(structure,arg)
// This function executes the nonvariable term as the term
// itself in the program text with argument arg.
// mode(in,in)
// 
Thread::ReturnValue
Thread::psi_call_predicate1(Object *& object1, Object *& object2)
{
  return call_predicate(1, object1, object2);
}
//
// psi_call_predicate2(structure,arg1,arg2)
// This function executes the nonvariable term as the term
// itself in the program text with arguments arg1,arg2.
// mode(in,in,in)
// 
Thread::ReturnValue
Thread::psi_call_predicate2(Object *& object1, Object *& object2, Object *& object3)
{
  return call_predicate(2, object1, object2, object3);
}

//
// psi_call_predicate3(structure,arg1,arg2,arg3)
// This function executes the nonvariable term as the term
// itself in the program text with arguments arg1,arg2,arg3.
// mode(in,in,in,in)
// 
Thread::ReturnValue
Thread::psi_call_predicate3(Object *& object1,
			    Object *& object2, 
			    Object *& object3,
			    Object *& object4)
{
  return call_predicate(3, object1, object2, object3, object4);
}

//
// psi_call_predicate4(structure,arg1,arg2,arg3,arg4)
// This function executes the nonvariable term as the term
// itself in the program text with arguments arg1,arg2,arg3,arg4
// mode(in,in,in,in,in)
// 
Thread::ReturnValue
Thread::psi_call_predicate4(Object *& object1,
			    Object *& object2, 
			    Object *& object3,
			    Object *& object4,
			    Object *& object5)
{
  return call_predicate(4, object1, object2, object3, object4, object5);
}

#if 0
// 
// psi_call_clause(address, term)
// Execute a clause from address and use the term as query.  This is used for
// decompiling a dynamic clause.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_call_clause(Object *& object1, Object *& object2)
{
  Cell            query;
  word32          arity, i;
  PrologValue     pval1, pval2;
  
  pval1.term = object1;
  pval2.term = object2;
  heap.Dereference(pval1);
  heap.Dereference(pval2);
  query = pval2.term;

  assert(pval1.getTerm()->isNumber());

  arity = ((query.isAtom()) ? (0) : (heap.StructArity(query)));
  for (i = 0; i < arity; i++)
    {
      X[i] = heap.StructNthArgument(query, i + 1);
    }

  programCounter = (CodeLoc)heap.NumValue(pval1.term);
  return(RV_SUCCESS);
}
#endif // 0

//
// psi_get_qplibpath(variable).
// This functionn returns the path for 
// files to the variable.
// mode(out)
//
Thread::ReturnValue
Thread::psi_get_qplibpath(Object *& object1)
{
  object1 = atoms->add("."); //*lib_path;
  return(RV_SUCCESS);
}

//
// psi_uncurry(term1, term2).
// Flattens (uncurries) term1 to term2.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_uncurry(Object *& object1, Object *& object2)
{
  int32           i;
  word32          arity;          // arity of the term.

  PrologValue     pval1(object1);

  heap.prologValueDereference(pval1);
  arity = 0;

  //
  // Get predicate name and arity.
  //
  if (!pval1.getTerm()->isStructure())
    {
      object2 = object1;
      return(RV_SUCCESS);
    }
  //
  // pval1 is a structure
  //
  PrologValue 
    functor(pval1.getSubstitutionBlockList(), 
	    OBJECT_CAST(Structure*, pval1.getTerm())->getFunctor());
  heap.prologValueDereference(functor);
  if (!functor.getTerm()->isStructure())
    {
      object2 = object1;
      return(RV_SUCCESS);
    }
  //
  // pval1 is higher order
  //
  PrologValue hi_func(pval1.getSubstitutionBlockList(), pval1.getTerm());

  assert(hi_func.getTerm()->isStructure());
  do
    {
      arity += static_cast<word32>(OBJECT_CAST(Structure*, hi_func.getTerm())->getArity());
      hi_func.setTerm(OBJECT_CAST(Structure*,
				  hi_func.getTerm())->getFunctor());
      heap.prologValueDereference(hi_func);
    } while (hi_func.getTerm()->isStructure());

  Structure* str = heap.newStructure(arity);
  str->setFunctor(heap.prologValueToObject(hi_func));

  PrologValue term(pval1.getSubstitutionBlockList(), pval1.getTerm());
  while (arity > 0)
    {
      heap.prologValueDereference(term);
      for (i = static_cast<int32>(OBJECT_CAST(Structure*, term.getTerm())->getArity()) 
	     ; i > 0; i--)
	{
	  PrologValue arg(term.getSubstitutionBlockList(),
			  OBJECT_CAST(Structure*, 
				      term.getTerm())->getArgument(i));
	  str->setArgument(arity, heap.prologValueToObject(arg));
	  arity--;

	}
      term.setTerm(OBJECT_CAST(Structure*, 
			       term.getTerm())->getFunctor());
    }
  object2 = str;
  return(RV_SUCCESS);
} 

extern CodeLoc failblock;

Thread::ReturnValue 
Thread::psi_make_cleanup_cp(Object *& object1)
{
      otherTrail.push(currentChoicePoint, getCleanupMinCPAddr());
      object1 = heap.newInteger(cutPoint);
      return(RV_SUCCESS);
}


