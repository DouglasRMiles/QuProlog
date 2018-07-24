// interrupt.cc - Contains a set of functions for interrupt handling.
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
// $Id: interrupt.cc,v 1.9 2006/02/20 03:18:51 qp Exp $

#include	<iostream>
#include	<signal.h>

#include "global.h"
#include "atom_table.h"
#include "pred_table.h"
#include "signals.h"
#include "thread_qp.h"

#include "pseudo_instr_arrays.h" 

extern AtomTable *atoms;
extern PredTab *predicates;
extern Signals *signals;

//
// Build the required data for signal and set up to call exception/1.
//
CodeLoc
Thread::HandleInterrupt(Object* goal)
{
  int sig;

  //
  // Change the priority level.
  //
  signals->Status().resetEnableSignals();
  signals->Status().resetSignals();

  for (sig = 1; sig < NSIG + 1; sig++)
    {
      if (signals->IsSet(sig))
	{
	  break;
	}
    }
  signals->Decrement(sig);
  
  //
  // Build argument.
  //
  X[0] = atoms->add(signals->Name(sig));
  X[1] = ErrArea == NULL ? AtomTable::default_atom : atoms->add(ErrArea);
  X[2] = goal;
  
  //
  // Set up argument and call '$signal_exception'/3
  //
  return predicates->getCode(predicates->lookUp(AtomTable::signal_exception, 3, atoms, code)).getPredicate(code);
}

//
// Construct the current call as a structure.
//
Object*
Thread::BuildCall(Atom* pred, const word32 n)
{
  assert(pred != NULL);
  
  word32  i;

  if (n == 0)
    {
      //
      // Zero argument predicate.
      //
      return(pred);
    }
  
  //
  // Build the call as a structure.
  //
  Structure* str = heap.newStructure(n);
  str->setFunctor(pred);
  for (i = 1; i <= n; i++)
    {
      str->setArgument(i, X[i-1]);
    }
  
  //
  // Return the call.
  //
  return(str);
}

//
// Set up the arguments to call exception/1 in Qu-Prolog.
//
CodeLoc
Thread::Exception(Object* data)
{
  X[0] = data;
  return(predicates->getCode(predicates->lookUp(AtomTable::exception,
					   1, atoms, code)).getPredicate(code));
                                               // "exception"
}

//
// Build the required data for undefined predicate and set up to call
// exception/1.
//
CodeLoc
Thread::UndefinedPred(Object* goal)
{
  //
  // Build argument for exception/1.
  //
  Structure* str = heap.newStructure(3);
  str->setFunctor(AtomTable::undefined_predicate); // "undefined_predicate"
  str->setArgument(1, AtomTable::recoverable);     // "recoverable"
  str->setArgument(2, goal);
  str->setArgument(3, AtomTable::default_atom);                  // "default"
  
  //
  // Set up argument and call exception/1.
  //
  return(Exception(str));
}

//
// Create the call throw(out_of_heap)
//
CodeLoc
Thread::FailedGC(void)
{
  X[0] = AtomTable::out_of_heap;
  return(predicates->getCode(predicates->lookUp(AtomTable::throw_call,
                                1, atoms, code)).getPredicate(code));

}

//
// Build a call to fast_retry_delays
//
CodeLoc
Thread::HandleFastRetry(Object* goal)
{
  //
  // Build argument.
  //
  X[0] = goal;

  //
  // Set up argument and call 'retry_woken_delays'/3
  //
  return(predicates->getCode(predicates->lookUp(AtomTable::retry_woken_delays,
					   1, atoms, code)).getPredicate(code));
                                               //  "retry_woken_delays"
}


CodeLoc 
Thread::HandleCleanup(Object* goal, word32 cp )
{
  X[0] = goal;
  X[1] = heap.newInteger(cp);
  return(predicates->getCode(predicates->lookUp(AtomTable::do_cleanup,
                              2, atoms, code)).getPredicate(code));
}

//
// Build the goal to be executed at the current PC.
// Fails if PC not at {CALL,EXECUTE}_{PREDICATE,ADDRESS,ESCAPE}
// or a pseudo-instruction.
//
bool
Thread::getCurrentGoal(Object*& goal)
{
  switch (getInstruction(programCounter))
    {
    case CALL_PREDICATE:
      {
	Atom* predicate = getPredAtom(programCounter);
	const word32 arity = getNumber(programCounter);
	goal = BuildCall(predicate, arity);
	return true;
      }
    case CALL_ADDRESS:
      {
	const CodeLoc address = getCodeLoc(programCounter);
	CodeLoc loc = address - Code::SIZE_OF_HEADER;
	Atom* predicate = getPredAtom(loc);
	const word32 arity = getNumber(loc);
	goal = BuildCall(predicate, arity);
	return true;
      }
    case CALL_ESCAPE:
      {
	const PredLoc address = getAddress(programCounter);
	Atom* predicate = predicates->getPredName(address, atoms);
	const word32 arity = predicates->getArity(address);
	goal = BuildCall(predicate, arity);
	return true;
      }
    case EXECUTE_PREDICATE:
      {
	Atom* predicate = getPredAtom(programCounter);
	const word32 arity = getNumber(programCounter);
	goal = BuildCall(predicate, arity);
	return true;
      }
    case EXECUTE_ADDRESS:
      {
	const CodeLoc address = getCodeLoc(programCounter);
	CodeLoc loc = address - Code::SIZE_OF_HEADER;
	Atom* predicate = getPredAtom(loc);
	const word32 arity = getNumber(loc);
	goal = BuildCall(predicate, arity);
	return true;
      }
    case EXECUTE_ESCAPE:
      { 
	const PredLoc address = getAddress(programCounter);
	Atom* predicate = predicates->getPredName(address, atoms);
	const word32 arity = predicates->getArity(address);
	goal = BuildCall(predicate, arity);
	return true;
      }
    case PSEUDO_INSTR0:
      {
	const word32 n = getNumber(programCounter);
	goal = psi0BuildCall(n);
	return true;
      }
    case PSEUDO_INSTR1:
      {
	const word32 n = getNumber(programCounter);
	const word32 i = getRegister(programCounter);
	Object*& arg1 = PSIGetReg(i);
	psi1NewVars(pseudo_instr1_array[n].mode, arg1);
	goal = psi1BuildCall(n, arg1);
	return true;
      }
    case PSEUDO_INSTR2:
      {
	const word32 n = getNumber(programCounter);
	const word32 i = getRegister(programCounter);
	const word32 j = getRegister(programCounter);
	Object*& arg1 = PSIGetReg(i);
	Object*& arg2 = PSIGetReg(j);
	psi2NewVars(pseudo_instr2_array[n].mode,
		    arg1, arg2);
	goal = psi2BuildCall(n, arg1, arg2);
	return true;
      }
    case PSEUDO_INSTR3:
      {
	const word32 n = getNumber(programCounter);
	const word32 i = getRegister(programCounter);
	const word32 j = getRegister(programCounter);
	const word32 k = getRegister(programCounter);
	
	Object*& arg1 = PSIGetReg(i);
	Object*& arg2 = PSIGetReg(j);
	Object*& arg3 = PSIGetReg(k);
	psi3NewVars(pseudo_instr3_array[n].mode,
		    arg1, arg2, arg3);
	goal = psi3BuildCall(n, arg1, arg2, arg3);
	return true;
      }
    case PSEUDO_INSTR4:
      {
	const word32 n = getNumber(programCounter);
	const word32 i = getRegister(programCounter);
	const word32 j = getRegister(programCounter);
	const word32 k = getRegister(programCounter);
	const word32 m = getRegister(programCounter);
	
	Object*& arg1 = PSIGetReg(i);
	Object*& arg2 = PSIGetReg(j);
	Object*& arg3 = PSIGetReg(k);
	Object*& arg4 = PSIGetReg(m);
	psi4NewVars(pseudo_instr4_array[n].mode,
		    arg1, arg2, arg3, arg4);
	goal = psi4BuildCall(n, arg1, arg2, arg3, arg4);
	return true;
      }
    case PSEUDO_INSTR5:
      {
	const word32 n = getNumber(programCounter);
	const word32 i = getRegister(programCounter);
	const word32 j = getRegister(programCounter);
	const word32 k = getRegister(programCounter);
	const word32 m = getRegister(programCounter);
	const word32 o = getRegister(programCounter);
	
	Object*& arg1 = PSIGetReg(i);
	Object*& arg2 = PSIGetReg(j);
	Object*& arg3 = PSIGetReg(k);
	Object*& arg4 = PSIGetReg(m);
	Object*& arg5 = PSIGetReg(o);
	psi5NewVars(pseudo_instr5_array[n].mode,
		    arg1, arg2, arg3, arg4, arg5);
	goal = psi5BuildCall(n, arg1, arg2, arg3, arg4, arg5);
	return true;
      }
    default:
      return false;
    }
  return false;
}





