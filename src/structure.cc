// structrure.cc - Contains functions which retrieve information from and
//                 build up structures.
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
// $Id: structure.cc,v 1.6 2006/02/06 00:51:38 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"
 
// psi_compound(term)
// Succeed if term is a structure or a list.
// mode(in)
//
Thread::ReturnValue
Thread::psi_compound(Object *& object1)
{
  assert(object1->hasLegalSub());
  PrologValue	pval1(object1);
  
  heap.prologValueDereference(pval1);
  
  return(pval1.getTerm()->isAnyStructure()? RV_SUCCESS : RV_FAIL);
}

// psi_functor(Structure, Functor, Arity)
// mode(in,in,in)
//
Thread::ReturnValue 
Thread::psi_functor(Object *& object1, Object *& object2, Object *& object3)
{
  int 		arity = 0, i;

  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  assert(object3->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);
  Object* val3 = heap.dereference(object3);
  
  if (val1->isStructure())
    {
      Structure* str = OBJECT_CAST(Structure*, val1);
      Object* arity_object = heap.newInteger(static_cast<long>(str->getArity()));
      return BOOL_TO_RV(unify(val2, str->getFunctor()) && 
		        unify(val3, arity_object));
    }   
  else if (val1->isCons())
    {
       Object* arity_object = heap.newInteger(2);
       return BOOL_TO_RV(unify(val2, AtomTable::cons) && 
			 unify(val3, arity_object));
    } 
  else if (val3->isNumber())
    {
      arity =  val3->getInteger();
      if ((arity < 0) || (arity > (signed) ARITY_MAX))
	{
	  PSI_ERROR_RETURN(EV_RANGE, 3);
	}
      else if (arity == 0)
	{
	  //
	  // a zero arity structure
	  //
	  return BOOL_TO_RV(unify(val1, val2));
	}
      else if (arity == 2 && val2 == AtomTable::cons)
	{
	  //
	  // a list
	  //
	  Variable* head = heap.newVariable();
	  head->setOccursCheck();
	  Variable* tail = heap.newVariable();
	  tail->setOccursCheck();
	  Cons* list = heap.newCons(head, tail);
	  return BOOL_TO_RV(unify(val1, list));
	}
      else
	{
	  if (val2->isVariable())
	    {
	      OBJECT_CAST(Variable*, val2)->setOccursCheck();
	    }
	  assert(arity <= MaxArity);
	  Structure* str = heap.newStructure(arity);
	  str->setFunctor(val2);
	  //
	  // initialise all arguments in the structure.
	  //
	  for (i = 1; i <= arity; i++)
	    {
	      Variable* arg = heap.newVariable();
	      arg->setOccursCheck();
	      str->setArgument(i, arg);
	    }
	  return BOOL_TO_RV(unify(val1, str));
	}
    }
  else if (val1->isConstant())
    {
      Object* arity_object = heap.newInteger(0);
      return BOOL_TO_RV(unify(val2, val1) && 
			unify(val3, arity_object));
    }   
  else if (val1->isSubstitution())
    {
      assert(val1->hasLegalSub());
      PrologValue pval(val1);
      heap.prologValueDereference(pval);
      if (pval.getTerm()->isStructure())
	{     
	  Structure* str = OBJECT_CAST(Structure*, pval.getTerm());
	  Object* arity_object = heap.newInteger(static_cast<long>(str->getArity()));
          assert(pval.getSubstitutionBlockList()->isCons());
	  Object* funct 
	    = heap.newSubstitution(pval.getSubstitutionBlockList(),
				   str->getFunctor());
	  return 
	    BOOL_TO_RV(unify(val2, funct) && 
		       unify(val3, arity_object));
	}
      else if (pval.getTerm()->isCons())
	{
	  Object* arity_object = heap.newInteger(2);
	  return 
	    BOOL_TO_RV(unify(val2, AtomTable::cons) &&
		       unify(val3, arity_object));
	}
      else if (pval.getTerm()->isVariable())
	{
	  PSI_ERROR_RETURN(EV_INST, 3);
	}	 
      else
	{
	  PSI_ERROR_RETURN(EV_TYPE, 3);
	}
    }     
  else // instantiation or type error
    {
      if (val1->isVariable() && val3->isVariable())
	{
	  PSI_ERROR_RETURN(EV_INST, 3);
	}
      else
	{
	  PSI_ERROR_RETURN(EV_TYPE, 3);
	}
      
    }
}

//
// psi_arg(N, Str, Arg)
// mode(in,in,out)
//
Thread::ReturnValue 
Thread::psi_arg(Object *& object1, Object *& object2, Object *& object3)
{
  int32 arity, i;
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  if (val1->isShort())
    {
      i = val1->getInteger();
      if (val2->isStructure())
	{
	  Structure* str = OBJECT_CAST(Structure*, val2);
	  arity = static_cast<int32>(str->getArity());
	  if ((i <= 0) || (i > arity))
	    {
	      PSI_ERROR_RETURN(EV_RANGE, 1);
	    }
	  object3 = str->getArgument(i);
	  return RV_SUCCESS;
	}
      else if (val2->isCons())
	{
	  Cons* list = OBJECT_CAST(Cons*, val2);
	  if (i == 1) 
	    {
	      object3 = list->getHead();
	      return RV_SUCCESS;
	    }
	  else if (i == 2)
	    {
	      object3 = list->getTail();
	      return RV_SUCCESS;
	    }
	  else
	    {
	      PSI_ERROR_RETURN(EV_RANGE, 1);
	    }
	}
      else if (val2->isSubstitution())
	{
          assert(val2->hasLegalSub());
	  PrologValue pval(val2);
	  heap.prologValueDereference(pval);
	  if (pval.getTerm()->isStructure())
	    {
	      Structure* str = OBJECT_CAST(Structure*, pval.getTerm());
	      arity = static_cast<int32>(str->getArity());
	      if ((i <= 0) || (i > arity))
		{
		  PSI_ERROR_RETURN(EV_RANGE, 1);
		}
              assert(pval.getSubstitutionBlockList()->isCons());
	      object3 = heap.newSubstitution(pval.getSubstitutionBlockList(),
					     str->getArgument(i));
	      return RV_SUCCESS;
	    }
	  else if(pval.getTerm()->isCons())
	    {
	      Cons* list = OBJECT_CAST(Cons*, pval.getTerm());
	      if (i == 1) 
		{
                  assert(pval.getSubstitutionBlockList()->isCons());
		  object3
		    = heap.newSubstitution(pval.getSubstitutionBlockList(),
					   list->getHead());
		  return RV_SUCCESS;
		}
	      else if (i == 2)
		{
                  assert(pval.getSubstitutionBlockList()->isCons());
		  object3 
		    = heap.newSubstitution(pval.getSubstitutionBlockList(),
					   list->getTail());
		  return RV_SUCCESS;
		}
	      else
		{
		  PSI_ERROR_RETURN(EV_RANGE, 1);
		} 
	    }
	  else if(pval.getTerm()->isVariable())
	    {
	      PSI_ERROR_RETURN(EV_INST, 2);
	    }
	  else
	    {
	      PSI_ERROR_RETURN(EV_TYPE, 2);
	    }
	}
      else
	{
	  if (val2->isVariable())
	    {
	      PSI_ERROR_RETURN(EV_INST, 2);
	    }
	  else
	    {
	      PSI_ERROR_RETURN(EV_TYPE, 2);
	    }
	}
    }
  else
    {
      if (val1->isVariable())
	{
	  PSI_ERROR_RETURN(EV_INST, 1);
	}
      else
	{
	  PSI_ERROR_RETURN(EV_TYPE, 1);
	}
    }
}


//
// psi_put_structure(F, N, Str)
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_put_structure(Object *& object1, Object *& object2, 
			  Object *& object3)
{
  int32 		arity, i;
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);
  
  if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!val2->isShort())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  
  arity =  val2->getInteger();
  
  if((arity <= 0) || (arity > (signed) ARITY_MAX))
    {
      PSI_ERROR_RETURN(EV_RANGE, 2);
    }
  
  if (arity == 2 && val1 == AtomTable::cons)
    {
      //
      // a list
      //
      Cons* list = heap.newCons(AtomTable::nil, AtomTable::nil);
      object3 = list;
      return(RV_SUCCESS);
    }
  else
    {
      if (val1->isVariable())
	{
	  OBJECT_CAST(Variable*, val1)->setOccursCheck();
	}
	  assert(arity <= MaxArity);
      Structure* str = heap.newStructure(arity);
      str->setFunctor(val1);
      //
      // zero all arguments in the structure.
      //
      for (i = 1; i <= arity; i++)
	{
	  str->setArgument(i, AtomTable::nil);
	}
      object3 = str;
      return(RV_SUCCESS);
    }
}
//
// psi_set_argument(F, N, Arg)
// mode(in,in,in)
//
Thread::ReturnValue 
Thread::psi_set_argument(Object *& object1, Object *& object2, Object *& object3)
{
  int32 		arity, i;
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  assert(object3->variableDereference()->hasLegalSub());
  Object* funct = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);
  Object* val3 = heap.dereference(object3);

  assert(val2->isShort());
  
  i = val2->getInteger();

  if (funct->isStructure())
    {
      Structure* str = OBJECT_CAST(Structure*, funct);
      arity = static_cast<int32>(str->getArity());
      
      assert((i > 0) && (i <= arity));
      
      if(val3->isVariable())
	{
	  OBJECT_CAST(Variable*, val3)->setOccursCheck();
	}
      str->setArgument(i, val3);
    }
  else if (funct->isCons())
    {
      Cons* list = OBJECT_CAST(Cons*, funct);
      assert((i > 0) && (i <= 2));
      if (i == 1)
	{
	  if(val3->isVariable())
	    {
	      OBJECT_CAST(Variable*, val3)->setOccursCheck();
	    }
	  list->setHead(val3);
	}
      else // i == 2
	{
	  if(val3->isVariable())
	    {
	      OBJECT_CAST(Variable*, val3)->setOccursCheck();
	    }
	  list->setTail(val3);
	}
    }
  else
    {
      assert(false);
    }
  return(RV_SUCCESS);
}









//
// psi_setarg(N, F, Arg)
// mode(in,in,in)
//
// A backtrackabe destructive update to the N'th arg of F
Thread::ReturnValue 
Thread::psi_setarg(Object *& object1, Object *& object2, Object *& object3)
{
  int32 		arity, i;
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  assert(object3->variableDereference()->hasLegalSub());
  Object* funct = heap.dereference(object2);
  Object* val1 = heap.dereference(object1);
  Object* val3 = heap.dereference(object3);

  if (!val1->isShort()) {
    if (val1->isVariable())
      {
        PSI_ERROR_RETURN(EV_INST, 1);
      }
    else
      {
        PSI_ERROR_RETURN(EV_TYPE, 1);
      }
  }
  i = val1->getInteger();

  if (funct->isStructure())
    {
      Structure* str = OBJECT_CAST(Structure*, funct);
      arity = static_cast<int32>(str->getArity());
      
      if ((i <= 0) || (i > arity)) {
        PSI_ERROR_RETURN(EV_RANGE, 1);
      }
      
      if(val3->isVariable())
	{
	  OBJECT_CAST(Variable*, val3)->setOccursCheck();
	}
      updateAndTrailObject(reinterpret_cast<heapobject*>(funct), val3, i+1);
    }
  else if (funct->isCons())
    {
      if ((i > 0) && (i <= 2)) {
        PSI_ERROR_RETURN(EV_RANGE, 1);
      }
      if(val3->isVariable())
        {
          OBJECT_CAST(Variable*, val3)->setOccursCheck();
        }
      updateAndTrailObject(reinterpret_cast<heapobject*>(funct), val3, i); 
    }	
  else {
    if (funct->isVariable())
      {
        PSI_ERROR_RETURN(EV_INST, 2);
      }
    else
      {
        PSI_ERROR_RETURN(EV_TYPE, 2);
      }
  }
  
  return(RV_SUCCESS);
}









