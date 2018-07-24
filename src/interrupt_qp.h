// interrupt_qp.h - Contains a set of functions for interrupt handling.
//	Members of class Thread.
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
// $Id: interrupt_qp.h,v 1.1 2000/12/13 23:10:01 qp Exp $

#ifndef INTERRUPT_QP_H
#define INTERRUPT_QP_H

//
// Build the required data for signal and set up to call exception/1.
//
CodeLoc HandleInterrupt(Object*);

//
// Construct the current call as a structure.
//
Object* BuildCall(Atom* pred, const word32 n);

//
// Build the required data for undefined predicate and set up to call
// exception/1.
//
CodeLoc UndefinedPred(Object* goal);

//
// Create the call throw(out_of_heap)
//
CodeLoc FailedGC(void);

//
// Build a call to fast_retry_delays
//
CodeLoc HandleFastRetry(Object* goal);

CodeLoc HandleCleanup(Object* goal, word32 cp );

//
// Set up the arguments to call exception/1 in Qu-Prolog.
//
CodeLoc Exception(Object* data);

//
// Build the goal to be executed at the current PC.
// Fails if PC not at {CALL,EXECUTE}_{PREDICATE,ADDRESS,ESCAPE}
// or a pseudo-instruction.
//
bool getCurrentGoal(Object*& goal);

#endif // INTERRUPT_QP_H
