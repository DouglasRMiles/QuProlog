// examine_term.cc - The QU-Prolog functions which have to do with examining
//		     or testing the type of a term. 
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
// $Id: examine_term.cc,v 1.7 2006/02/06 00:51:38 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"

extern heapobject var_id_counter;
//
// psi_collect_vars(term, list)
// Collect all the variables (and object_variables) in term into list
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_collect_vars(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* varlist = AtomTable::nil;

  heap.collect_term_vars(val1, varlist);
  heap.resetCollectedVarList(varlist);
  object2 = varlist;

  return(RV_SUCCESS);
}

//
// psi_var(term)
// True if term is a variable, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_var(Object *& object1)
{
  Object* val1 = object1->variableDereference();
  if (val1->isVariable())
    {
      return RV_SUCCESS;
    }
  else if (!val1->isSubstitution())
    {
      return RV_FAIL;
    }
  assert(val1->hasLegalSub());
  PrologValue pval1(val1);
  heap.prologValueDereference(pval1);
  return(BOOL_TO_RV(pval1.getTerm()->isVariable()));
}

//
// psi_atom(term)
// True if term is an atom, false otherwise
// mode(in)
//
Thread::ReturnValue 
Thread::psi_atom(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  
  return (BOOL_TO_RV(val1->isAtom()));
}

//
// psi_integer(term)
// True if term is an integer, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_integer(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  return(BOOL_TO_RV(val1->isInteger()));
}

//
// psi_float(term)
// True if term is a float, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_float(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  return(BOOL_TO_RV(val1->isDouble()));
}

//
// psi_atomic(term)
// True if term is atomic, false otherwise
// mode(in)
//
Thread::ReturnValue 
Thread::psi_atomic(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  return (BOOL_TO_RV(val1->isAtom() || val1->isNumber()));
}

// psi_any_variable(term)
// True if term is a variable or object variable, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_any_variable(Object *& object1)
{
  Object* val1 = object1->variableDereference();
  if (val1->isAnyVariable())
    {
      return RV_SUCCESS;
    }
  else if (!val1->isSubstitution())
    {
      return RV_FAIL;
    }
  assert(val1->hasLegalSub());
  PrologValue pval1(val1);
  heap.prologValueDereference(pval1);
  return(BOOL_TO_RV(pval1.getTerm()->isAnyVariable()));
}

//
// psi_simple(term)
// True if term is any variable or atomic, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_simple(Object *& object1)
{
  Object* val1 = object1->variableDereference();
  if (val1->isAnyVariable() || val1->isConstant())
    {
      return RV_SUCCESS;
    }
  else if (!val1->isSubstitution())
    {
      return RV_FAIL;
    }
  assert(val1->hasLegalSub());
  PrologValue pval1(val1);
  heap.prologValueDereference(pval1);
  return(BOOL_TO_RV(pval1.getTerm()->isAnyVariable()));
}

//
// psi_nonvar(term)
// True if term is not a variable, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_nonvar(Object *& object1)
{
  Object* val1 = object1->variableDereference();
  if (val1->isVariable())
    {
      return RV_FAIL;
    }
  else if (!val1->isSubstitution())
    {
      return RV_SUCCESS;
    }
  assert(val1->hasLegalSub());
  PrologValue pval1(val1);
  heap.prologValueDereference(pval1);
  return(BOOL_TO_RV(!pval1.getTerm()->isVariable()));
}

//
// psi_std_var(term)
// True if term is a variable with no subs, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_std_var(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  return(BOOL_TO_RV(val1->isVariable()));
}

//
// psi_std_compound(term)
// True if term is compound with an atom functor, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_std_compound(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1); 

  if (val1->isStructure())
    {
      Structure* str = OBJECT_CAST(Structure*, val1);
      return(BOOL_TO_RV(str->getFunctor()->isAtom()));
    }
  else
    {
      return (BOOL_TO_RV(val1->isCons()));
    }
}


//
// psi_std_nonvar(term)
// True if term is atomic or std_compound, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_std_nonvar(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1); 

  
  if (val1->isAtom() || val1->isNumber())
    {
      return(RV_SUCCESS);
    }
  else if (val1->isStructure())
    {
      Structure* str = OBJECT_CAST(Structure*, val1);
      return(BOOL_TO_RV(str->getFunctor()->isAtom()));
    }
  else
    {
      return (BOOL_TO_RV(val1->isList()));
    }
}

//
// psi_list(term)
// True if term is a list, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_list(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  if (val1->isList())
    {
      return RV_SUCCESS;
    }
  else if (!val1->isSubstitution())
    {
      return RV_FAIL;
    }
  assert(val1->hasLegalSub());
  PrologValue pval1(val1);
  heap.prologValueDereference(pval1);
  return(BOOL_TO_RV(pval1.getTerm()->isList()));
}

// psi_string(term)
// True if term is a string, false otherwise
// mode(in)
//
Thread::ReturnValue
Thread::psi_string(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  return(BOOL_TO_RV(val1->isString()));
}

//
// psi_fast_simplify(term, simpterm)
// do a simple term simplification
// mode(in, out)
//
Thread::ReturnValue
Thread::psi_fast_simplify(Object *& object1, Object *& object2)
{
  PrologValue pv(object1);
  (void)occursCheckAndSimplify(ALL_CHECK, pv, object2, NULL);
  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_hash_variable(Object *& object1, Object *& object2)
{
  Object* val1 = heap.dereference(object1);

  if (!val1->isVariable()) return RV_FAIL;

  Variable* variable = OBJECT_CAST(Variable*, val1);

  variable = addExtraInfo(variable);

  heapobject id = variable->getID();

  if (id == 0)
    {
      var_id_counter++;
      variable->setID(var_id_counter);
      id = var_id_counter;
    }

  object2 = heap.newInteger((int)id);
  return RV_SUCCESS;
}






