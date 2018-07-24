// exception.cc - Define low level exception support routines.
//                The idea evolved from IC-Prolog and made compatible with
//                Quintus Prolog.
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
// $Id: exception.cc,v 1.4 2006/01/31 23:17:50 qp Exp $

#include "thread_qp.h"

//
// psi_get_catch(variable)
// Return the current value in the catch register.
// mode(out)
//
Thread::ReturnValue
Thread::psi_get_catch(Object *& object1)
{
  object1 = heap.newInteger(catchPoint);
  return(RV_SUCCESS);
}

//
// psi_set_catch(choice point)
// Set the catch register with the given value.
// mode(in)
//
Thread::ReturnValue
Thread::psi_set_catch(Object *& object1)
{  
  // If the throw was by garbage collection failure then suspendedGC
  // will be set to true and subsequent GCs will not work
  setSuspendGC(false);

  Object* val1 = heap.dereference(object1);
  
  assert(val1->isNumber());
  
  catchPoint = val1->getInteger();
  return(RV_SUCCESS);
}

//
// psi_failpt_to_catch
// Transfer the value from currentChoicePoint to catch.
// mode()
//
Thread::ReturnValue
Thread::psi_failpt_to_catch(void)
{
  catchPoint = currentChoicePoint;
  return(RV_SUCCESS);
}

//
// psi_catch_to_failpt
// Transfer the value from catch to currentChoicePoint.
// mode()
//
Thread::ReturnValue
Thread::psi_catch_to_failpt(void)
{
  currentChoicePoint = catchPoint;
  return(RV_SUCCESS);
}

//
// psi_psi_resume(state)
// Restore saved X regs and PC
// mode(in)
//
Thread::ReturnValue
Thread::psi_psi_resume(Object *& object1)
{
  //
  // !!! NOTE !!!
  //
  // In all the uses of psi_resume this pseudo-instruction
  // is immediately followed by a DEALLOCATE instruction.
  // BUT psi_resume resets the PC and so this DEALLOCATE is
  // never called. To compensate the DEALLOCATE code is
  // included below.
  //
  // !!! POSSIBLE PROBLEM !!!
  // 
  // If psi_resume is ever used in a predicate that does not
  //  ALLOCATE or DEALLOCATEs before the call then there will be
  //  trouble.
  
  EnvLoc PrevEnv = currentEnvironment;
  envStack.retrieve(PrevEnv, currentEnvironment,
		       continuationInstr);
  
  Object* state = heap.dereference(object1);

  assert(state->isStructure());
  assert(OBJECT_CAST(Structure*, state)->getArity() 
	       == NUMBER_X_REGISTERS+1);
  
  for (u_int i = 0; i < NUMBER_X_REGISTERS; i++)
    {
      X[i] = OBJECT_CAST(Structure*, state)->getArgument(i+1);
    }
  Object* pc = 
    OBJECT_CAST(Structure*, state)->getArgument(NUMBER_X_REGISTERS+1);
  assert(pc->isNumber());
  programCounter = reinterpret_cast<CodeLoc>(pc->getInteger());
  return(RV_SUCCESS);
}



