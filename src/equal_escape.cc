// equal_escape.cc - an escape function to call fastEqual.
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
// $Id: equal_escape.cc,v 1.6 2006/01/31 23:17:50 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"
#include "truth3.h"

//
// psi_fast_equal(term1,term2,status)
// returns true iff term1 and term2 have the same structure.
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_fast_equal(Object *& object1, Object *& object2, Object *& object3)
{
  truth3		res;
  assert(object1->hasLegalSub());
  assert(object2->hasLegalSub());
  PrologValue  pval1(object1);
  PrologValue  pval2(object2);

  res = heap.fastEqual(pval1, pval2);
  if (res == false)
    {
      return(RV_FAIL);
    }
  else if (res == true)
    {
      object3 = AtomTable::success;
    }
  else
    {
      object3 = AtomTable::unsure;
    }
  
  return(RV_SUCCESS);
}


//
// psi_equal_equal(term1,term2)
// returns true iff term1 == term2 .
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_equal_equal(Object *& term1, Object *& term2)
{
  PrologValue  pval1(term1);
  PrologValue  pval2(term2);
  heap.prologValueDereference(pval1);
  heap.prologValueDereference(pval2);

  int counter = 0;
  quick_tidy_check = true;
  bool result = equalEqual(pval1, pval2, counter);
  quick_tidy_check = false;
  return BOOL_TO_RV(result);
}


//
// psi_simplify_term(term1,term2)
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_simplify_term(Object *& term1, Object *& term2)
{
  PrologValue pterm(term1);
  quick_tidy_check = true;
  (void)simplify_term(pterm, term2);
  quick_tidy_check = false;
  return RV_SUCCESS;
}


//
// psi_simplify_term3(term1,term2, issimp)
// mode(in,out,out)
//
Thread::ReturnValue
Thread::psi_simplify_term3(Object *& term1, Object *& term2, Object *& issimp)
{
  PrologValue pterm(term1);
  quick_tidy_check = true;
  bool result = simplify_term(pterm, term2);
  quick_tidy_check = false;
  if (result)
    {
      issimp = AtomTable::success;
    }
  else
    {
      issimp = AtomTable::failure;
    }
  return RV_SUCCESS;
}

//
// test for term1 \= term2
//
// mode(in, in)
//
Thread::ReturnValue
Thread::psi_not_equal(Object *& term1, Object *& term2)
{
  // Save state
  heapobject* savesavedtop = heap.getSavedTop();
  heapobject* savedHT = heap.getTop();
  TrailLoc savedBindingTrailTop = bindingTrail.getTop();
  TrailLoc savedOtherTrailTop = otherTrail.getTop();
  heap.setSavedTop(savedHT);

  bool result = unify(term1, term2);

  // Restore state
  heap.setTop(savedHT);
  bindingTrail.backtrackTo(savedBindingTrailTop);
  assert(bindingTrail.check(heap));
  otherTrail.backtrackTo(savedOtherTrailTop);
  assert(otherTrail.check(heap));

  if (result) return RV_FAIL;
  else return RV_SUCCESS;
}
