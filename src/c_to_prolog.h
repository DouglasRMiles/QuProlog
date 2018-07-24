// c_to_prolog.h - Support functions for calling Qu-Prolog from C++.
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
// $Id: c_to_prolog.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	C_TO_PROLOG_H
#define	C_TO_PROLOG_H

// #include "atom_table.h"

private:
//
// Save the current state into a choice point.  Then, set up the registers in
// a new thread to be ready for execution.  Return the new thread as an
// identifier.  If query/arity is undefined or unable to create a new thread,
// NULL is returned.
//
Thread& initialise(Object* query, const word32 arity, va_list ap);

//
// Execute the query to obtain the next solution.
// Return:
//	Value	Meaning
//	0	fail
//	1	success
//
word32 QuPNextSolution(void);

public:
//
// Save the current state into a choice point.  Then, set up the registers in
// a new thread to be ready for execution.  Return the new thread as an
// identifier.  If query/arity is undefined or unable to create a new thread,
// NULL is returned.
//
Thread& QuPSetUpQuery(Object* query,
			 const word32 arity, ...);

//
// Restore to the state before SetUpQuery.  Any data, except side effects,
// created after SetUpQuery is lost.
//
bool QuPCutFailQuery(void);

//
// Restore to the state before SetUpQuery.  Keep any data created after
// SetUpQuery.
//
bool QuPCutQuery(void);

//
// Execute the query to obtain the first solution.
// Return:
//      Value   Meaning
//      0       fail
//      1       success
//
word32 QuPQueryCut(Object* query, const word32 arity ...);

//
// Execute the query.  Once the first solution is obtained, clean up the data
// areas and only leave the side effects behind.
// Return:
//      Value   Meaning
//      0       fail
//      1       success
//
word32 QuPQueryCutFail(Object* query,
		       const word32 arity, ...);

#ifdef	DEBUG

void DebugWrite(Object* term)
{
  QuPQueryCut(AtomTable::debug_write, 1, term);
}

#endif	// DEBUG

#endif	// C_TO_PROLOG_H
