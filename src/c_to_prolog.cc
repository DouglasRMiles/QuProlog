// c_to_prolog.cc - Support functions for calling Qu-Prolog from C++.
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
// $Id: c_to_prolog.cc,v 1.9 2006/01/31 23:17:49 qp Exp $

#include <stdarg.h>

#include "global.h"
#include "atom_table.h"
#include "code.h"
#include "pred_table.h"
#include "qem_options.h"
#include "thread_qp.h"

extern AtomTable *atoms;
extern PredTab *predicates;
extern QemOptions *qem_options;

//
// Save the current state into a choice point.  Then, set up the registers in
// a new thread to be ready for execution.  Return the new thread as an
// identifier.  If query/arity is undefined or unable to create a new thread,
// NULL is returned.
//
Thread&
Thread::initialise(Object* query, const word32 arity, va_list ap)
{
  static const CodeLoc success =
    predicates->getCode(predicates->lookUp(atoms->add("$succ_return_to_c"),
					   0, atoms, code)).getPredicate(code);
  static const CodeLoc failure =
    predicates->getCode(predicates->lookUp(atoms->add("$fail_return_to_c"),
					   0, atoms, code)).getPredicate(code);

  //
  // Look up the location for query.
  //
  assert(query->isAtom());
  const PredLoc loc =
    predicates->lookUp(OBJECT_CAST(Atom*, query), arity, atoms, code);
  if (loc == EMPTY_LOC)
    {
      Fatal(__FUNCTION__, "Unknown query");
    }

  //
  // Create a new thread to execute the query.
  //
  Thread *th = new Thread(this,
			  buffers,
			  scratchpad,
			  heap,
			  gcstack,
			  gcbits,
			  names,
			  ipTable,
			  bindingTrail,
			  otherTrail,
			  qem_options->EnvironmentStackSize(),
			  qem_options->ChoiceStackSize());


  // Create a choice point to hold the state and the alternative is set
  // to the predicate that handles failure from the query.
  //
  th->currentChoicePoint = pushChoicePoint(failure, 0);
  
  //
  // Set up registers.
  //
  th->programCounter = predicates->getCode(loc).getPredicate(code);
  th->continuationInstr = success;
  for (u_int i = 0; i < arity; i++)
    {
      th->X[i] = va_arg(ap, Object*);
    }
  
  //
  // Return the new thread as an identifier.
  //
  return(*th);
}

//
// Save the current state into a choice point.  Then, set up the registers in
// a new thread to be ready for execution.  Return the new thread as an
// identifier.  If query/arity is undefined or unable to create a new thread,
// NULL is returned.
//
Thread&
Thread::QuPSetUpQuery(Object* query, const word32 arity, ...)
{
  va_list ap;

  va_start(ap, arity);
  Thread& th = initialise(query, arity, ap);
  va_end(ap);
  return(th);
}

//
// Execute the query to obtain the next solution.
// Return:
//	Value	Meaning
//	0	fail
//	1	success
//
word32
Thread::QuPNextSolution(void)
{
  const word32 result = Execute() == 0 ? 1 : 0;

  return(result);
}

//
// Restore to the state before SetUpQuery.  Any data, except side effects,
// created after SetUpQuery is lost.
//
bool
Thread::QuPCutFailQuery(void)
{
  //
  // Backtrack to the state before QuPSetUpQuery.
  //
  choiceStack.failToBeginning(*this);
  
  return(true);
}

//
// Restore to the state before SetUpQuery.  Keep any data created after
// SetUpQuery.
//
bool
Thread::QuPCutQuery(void)
{
  //
  // Cut back to the state before QuPSetUpQuery.
  //
  tidyTrails(choiceStack.getHeapAndTrailsState(choiceStack.firstChoice()));

  return(true);
}

//
// Execute the query to obtain the first solution.
// Return:
//	Value	Meaning
//	0	fail
//	1	success
//
word32
Thread::QuPQueryCut(Object* query, const word32 arity ...)
{
  va_list		ap;
  
  //
  // Set up the query.
  //
  va_start(ap, arity);
  Thread& th = initialise(query, arity, ap);
  assert(&th != NULL);
  va_end(ap);
  
  //
  // Obtain the first solution.
  //
  const word32 result = th.QuPNextSolution();
  
  //
  // Clean up after the execution.
  //
  th.QuPCutQuery();

  //
  // Delete the thread.
  //
  delete &th;
  
  //
  // Return the result.
  //
  return(result);
}

//
// Execute the query.  Once the first solution is obtained, clean up the data
// areas and only leave the side effects behind.
// Return:
//	Value	Meaning
//	0	fail
//	1	success
//
word32
Thread::QuPQueryCutFail(Object* query, const word32 arity ...)
{
  va_list ap;
  
  //
  // Set up the query.
  //
  va_start(ap, arity);
  Thread& th = initialise(query, arity, ap);
  assert(&th != NULL);
  va_end(ap);
  
  //
  // Obtain the first solution.
  //
  const word32 result = th.QuPNextSolution();
  
  //
  // Clean up the result except side effects after the execution.
  //
  th.QuPCutFailQuery();
  
  //
  // Delete the thread.
  //
  delete &th;

  //
  // Return the result.
  //
  return(result);
}



