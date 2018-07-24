// quantifier.cc - routines for manipulating quantified term.
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
// $Id: quantifier.cc,v 1.5 2006/02/06 00:51:38 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"

//
// Check if object is a list of object variables
//
//
// psi_quant(term)
// Succeeds if term is a quantified term.
// mode(in)
//
Thread::ReturnValue
Thread::psi_quant(Object *& object1)
{
  assert(object1->hasLegalSub());
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);
  return BOOL_TO_RV(pval1.getTerm()->isQuantifiedTerm());
}

//
// psi_quantifier(term, quantifier)
// Return the quantifier of a quantified term.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_quantifier(Object *& object1, Object *& object2)
{
  assert(object1->hasLegalSub());
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);

  if (pval1.getTerm()->isQuantifiedTerm())
    {
      if (! pval1.getSubstitutionBlockList()->isNil())
	{
	  return RV_FAIL;
	}

      object2 = 
	OBJECT_CAST(QuantifiedTerm *, pval1.getTerm())->getQuantifier();
      
      return RV_SUCCESS;
    }
  else if (pval1.getTerm()->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
}

//
// psi_bound_var(term, variables)
// Return the bound variables of a quantified term.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_bound_var(Object *& object1, Object *& object2)
{
  assert(object1->hasLegalSub());
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);

  if (pval1.getTerm()->isQuantifiedTerm())
    {
      if (! pval1.getSubstitutionBlockList()->isNil())
	{
	  return RV_FAIL;
	}

      object2 =
	OBJECT_CAST(QuantifiedTerm *, pval1.getTerm())->getBoundVars();

      return RV_SUCCESS;
    }
  else if (pval1.getTerm()->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
}

//
// psi_body(term, body)
// Return the body of a quantified term.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_body(Object *& object1, Object *& object2)
{
  assert(object1->hasLegalSub());
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);

  if (pval1.getTerm()->isQuantifiedTerm())
    {
      if (! pval1.getSubstitutionBlockList()->isNil())
	{
	  return RV_FAIL;
	}
      
      object2 = 
	OBJECT_CAST(QuantifiedTerm *, pval1.getTerm())->getBody();

      return RV_SUCCESS;
    }
  else if (pval1.getTerm()->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
}

//
//
// psi_quantify(term, quantifier, variables, body)
// term is the quantified term made up from quantifier, variables and body.
// mode(in,in,in,in)
//
Thread::ReturnValue
Thread::psi_quantify(Object *& object1,
		     Object *& object2,
		     Object *& object3,
		     Object *& object4)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  if (val1->isQuantifiedTerm())
    {
      QuantifiedTerm *quantified_term =
	OBJECT_CAST(QuantifiedTerm *, val1);
      Object* quant = quantified_term->getQuantifier();
      Object* bvars = quantified_term->getBoundVars();
      Object* body = quantified_term->getBody();

      return BOOL_TO_RV(unify(object2, quant) &&
			unify(object3, bvars) &&
			unify(object4, body));
    }
  else
    {
  assert(object2->variableDereference()->hasLegalSub());
  assert(object3->variableDereference()->hasLegalSub());
  assert(object4->variableDereference()->hasLegalSub());
      Object* val2 = heap.dereference(object2);
      Object* val3 = heap.dereference(object3);
      Object* val4 = heap.dereference(object4);

      if (!heap.isBindingList(val3))
	{
	  PSI_ERROR_RETURN(EV_TYPE, 3);
	}
      
      QuantifiedTerm *quantified_term = heap.newQuantifiedTerm();

      if (val2->isVariable())
	{
	  OBJECT_CAST(Variable *, val2)->setOccursCheck();
	}
      if (val3->isVariable())
	{
	  OBJECT_CAST(Variable *, val3)->setOccursCheck();
		}
      if (val4->isVariable())
	{
	  OBJECT_CAST(Variable *, val4)->setOccursCheck();
	}

      if (! checkBinder(val3, AtomTable::nil))
	{
	  return RV_FAIL;
	}

      quantified_term->setQuantifier(val2);
      quantified_term->setBoundVars(val3);
      quantified_term->setBody(val4);
      return BOOL_TO_RV(unify(quantified_term, val1));
    }
}

//
// psi_check_binder(bound_list, object variables list)
// Ensure the object variables in the bound list mutually distinct and the
// object variables in object variables list are distinct from those in bound
// list.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_check_binder(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* ovlist1 = heap.dereference(object1);
  Object* ovlist2 = heap.dereference(object2);

  if (! heap.isBindingList(ovlist2))
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  
  if (! ovlist2->isList())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  return BOOL_TO_RV(checkBinder(ovlist1, ovlist2));
}



