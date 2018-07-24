// free_in.cc -	"free_in" escape test functions.
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
// $Id: free_in.cc,v 1.5 2006/01/31 23:17:50 qp Exp $

#include        "thread_qp.h"
 
//
// psi_not_free_in(object_variable, term)
// Execute the not free in constraint.  The problem can succeed, fail or delay.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_not_free_in(Object *& object1, Object *& object2)
{
  assert(object2->hasLegalSub());
  PrologValue	pval2(object2);
  
  Object* obvar = object1->variableDereference();
  
  if (obvar->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  else if (!obvar->isObjectVariable())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
      
  heap.prologValueDereference(pval2);
  
  assert(obvar->isObjectVariable());

  quick_tidy_check = true;
  bool result = notFreeIn(OBJECT_CAST(ObjectVariable*, obvar), pval2);
  quick_tidy_check = false;
  return (BOOL_TO_RV(result));
}

//
// psi_not_free_in_var_simplify(object_variable, var)
// Simplify the substitution associated with var and apply not free in.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_not_free_in_var_simplify(Object *& object1, Object *& object2)
{
  assert(object2->hasLegalSub());
  PrologValue	pval2(object2);
  
  Object* obvar = object1->variableDereference();
  heap.prologValueDereference(pval2);

#ifndef NDEBUG
  Object *sub_block_list = pval2.getSubstitutionBlockList();
  assert(! sub_block_list->isNil());
  assert(OBJECT_CAST(Cons* , sub_block_list)->getTail()->isNil());
#endif
  assert(obvar->isObjectVariable()); 


  if (pval2.getTerm()->isAnyVariable())
    {
      quick_tidy_check = true;
      bool result = notFreeInVarSimp(OBJECT_CAST(ObjectVariable*, obvar),pval2);
      quick_tidy_check = false;
      return(BOOL_TO_RV(result));
    }
  else
    {
      quick_tidy_check = true;
      bool result = notFreeIn(OBJECT_CAST(ObjectVariable*, obvar), pval2);
      quick_tidy_check = false;
      return(BOOL_TO_RV(result));
    }
}

Thread::ReturnValue
Thread::psi_addExtraInfoToVars(Object*& term)
{
  addExtraInfoToVars(term);
  return RV_SUCCESS;
}

//
// Call notFreeInNFISimp
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_not_free_in_nfi_simp(Object*& obvar, Object*& term)
{
  Object* ov = obvar->variableDereference();
  assert(ov->isObjectVariable());
  assert(term->hasLegalSub());
  PrologValue pv(term);
  quick_tidy_check = true;
  bool result = notFreeInNFISimp(OBJECT_CAST(ObjectVariable*, ov), pv);
  quick_tidy_check = false;
  return(BOOL_TO_RV(result));
}  

//
// is_not_free_in
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_is_not_free_in(Object*& obvar, Object*& term)
{
  Object* ov = obvar->variableDereference();
  assert(ov->isObjectVariable());
  assert(term->hasLegalSub());
  PrologValue pv(term);
  quick_tidy_check = true;
  truth3 result = freeness_test(OBJECT_CAST(ObjectVariable*, ov), pv);
  quick_tidy_check = false;
  return(BOOL_TO_RV(result == false));
}  


//
// is_free_in
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_is_free_in(Object*& obvar, Object*& term)
{
  Object* ov = obvar->variableDereference();
  assert(ov->isObjectVariable());
  assert(term->hasLegalSub());
  PrologValue pv(term);
  quick_tidy_check = true;
  truth3 result = freeness_test(OBJECT_CAST(ObjectVariable*, ov), pv);
  quick_tidy_check = false;
  return(BOOL_TO_RV(result == true));
}  





