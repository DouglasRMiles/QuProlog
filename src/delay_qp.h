// delay_qp.h - Routines for placing different types of problem in delay queue.
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
// $Id: delay_qp.h,v 1.4 2002/03/22 02:48:41 qp Exp $

#ifndef	DELAY_QP_H
#define	DELAY_QP_H

public:

enum  delaytype      { NOSIMPNFI , NFI, BOTH };

//
// Given a unification problem
// [tm/xm,...,t1/x1]A = [un/yn,.../u1/y1]A
// make xi nfi A if [[un/yn,.../u1/y1] does not yield ti 
// 
bool stripUnmatchedSubsFirst(PrologValue& var1, PrologValue& var2);

inline void stripUnmatchedSubs(PrologValue& var1, PrologValue& var2)
{
  if (stripUnmatchedSubsFirst(var1, var2) ||
      stripUnmatchedSubsFirst(var2, var1))
    {
      heap.prologValueDereference(var1);
      heap.prologValueDereference(var2);
      if (var1.getSubstitutionBlockList()->isCons())
	{
	  heap.dropSubFromTerm(*this, var1);
	}
      if (var2.getSubstitutionBlockList()->isCons())
	{
	  heap.dropSubFromTerm(*this, var2);
	}
    }
}

//
// Generate not_free_in constraints for the ranges and term.
//
void generateNFIConstraints(ObjectVariable *, PrologValue&);

//
// Remove any sub of the form [vm/xm, ..., v1/x1] from term1 or term2 that is
// not cancelled  by a later sub or does not have a corresponding (uncancelled)
// sub in the other term.
// Add subs of the form [ym/vm, ..., y1/v1] to both sides for any uncancelled
// subs.
bool balanceLocals(PrologValue&, PrologValue&);

//
// Check if delayed problem is associated with variable.
//
bool isDelayProblem(Object *, Object *);

//
// Add the delayed problem to the delayed queue associated with the variable.
//
void delayProblem(Object *, Object *);

//
// Delay an unification problem.
//
void delayUnify(PrologValue&, PrologValue&, Object *);

//
// Delay a not free in problem.
//
void delayNFI(ObjectVariable *,
	      PrologValue&,
	      Object *);

//
// Check for a not free in problem.
//
bool isDelayNFI(Object *, Object *);

//
// Wake up any delayed problems associated with the given (object) reference.
//
void wakeUpDelayedProblems(Object *);


//
// Retry the delayed problems - 
// type = NOSIMPNFI then retry only NFI problems but don't simplify 
// type = NFI then retry NFI problems 
// type = BOTH then retry NFI and = problems
//
bool retry_delays(delaytype type = NOSIMPNFI);

#endif	// DELAY_QP_H


