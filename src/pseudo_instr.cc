// pseudo_instr.cc -  pseudo-instructions
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
// $Id: pseudo_instr.cc,v 1.6 2006/01/31 23:17:51 qp Exp $

#include "global.h"
#include "atom_table.h"
#include "pred_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;
extern PredTab *predicates;

//
// The functions that define pseudo instructions have the following
// return values:
//   -1    fail
//    0    succeed
//   > 0   error number
//

//
// Create new variables for objectss associated with an arg with out mode
// The modes are bits with 1 meaning out mode.
//
void
Thread::psi1NewVars(int32 mode, Object *& object1)
{
  if (mode)
    {
      object1 = heap.newVariable();
    }
}

void
Thread::psi2NewVars(int32 mode, Object *& object1, Object *& object2)
{
  if (mode & 2)
    {
      object1 = heap.newVariable();
    }
  if (mode & 1)
    {
      object2 = heap.newVariable();
    }
}

void
Thread::psi3NewVars(int32 mode, 
		    Object *& object1, Object *& object2, Object *& object3)
{
  if (mode & 4)
    {
      object1 = heap.newVariable();
    }
  if (mode & 2)
    {
      object2 = heap.newVariable();
    }
  if (mode & 1)
    {
      object3 = heap.newVariable();
    }
}

void
Thread::psi4NewVars(int32 mode, 
		    Object *& object1, Object *& object2, 
		    Object *& object3, Object *& object4)
{
  if (mode & 8)
    {
      object1 = heap.newVariable();
    }
  if (mode & 4)
    {
      object2 = heap.newVariable();
    }
  if (mode & 2)
    {
      object3 = heap.newVariable();
    }
  if (mode & 1)
    {
      object4 = heap.newVariable();
    }
}

void
Thread::psi5NewVars(int32 mode, 
		    Object *& object1, Object *& object2, Object *& object3, 
		    Object *& object4, Object *& object5)
{
  if (mode & 16)
    {
      object1 = heap.newVariable();
    }
  if (mode & 8)
    {
      object2 = heap.newVariable();
    }
  if (mode & 4)
    {
      object3 = heap.newVariable();
    }
  if (mode & 2)
    {
      object4 = heap.newVariable();
    }
  if (mode & 1)
    {
      object5 = heap.newVariable();
    }
}

//
// Build a structure to hold the current X registers and PC.
//
Object*
Thread::psiSaveState(void)
{
  Object* pc = heap.newInteger(reinterpret_cast<wordptr>(programCounter));
  Structure* state = heap.newStructure(NUMBER_X_REGISTERS + 1);

  state->setFunctor(AtomTable::dollar);

  for (u_int i = 0; i < NUMBER_X_REGISTERS; i++)
    {
      assert(X[i] != NULL);
      if (X[i] == NULL) 
	{
	  //X[i] = heap.newVariable();
          X[i] = AtomTable::nil;
	}
      state->setArgument(i+1, X[i]);
    }
  state->setArgument(NUMBER_X_REGISTERS + 1, pc);
  return(state);
}

//
// Build a call for a pseudo instruction for use in interrupt handling
// and fast retry
//
Object*
Thread::psi0BuildCall(word32 n)
{
  Object* instr = heap.newInteger(n);
  Structure* problem = heap.newStructure(2);

  problem->setFunctor(AtomTable::psi0_resume);   // "$psi0_resume"

  problem->setArgument(1, psiSaveState());
  problem->setArgument(2, instr);

  return(problem);
}

Object*
Thread::psi1BuildCall(word32 n, Object * object1)
{
  Object* instr = heap.newInteger(n);
  Structure* problem = heap.newStructure(3);

  problem->setFunctor(AtomTable::psi1_resume);   // "$psi1_resume"

  problem->setArgument(1, psiSaveState());
  problem->setArgument(2, instr);
  problem->setArgument(3, object1);
 
  return(problem);
}

Object*
Thread::psi2BuildCall(word32 n, Object * object1, Object * object2)
{
  Object* instr = heap.newInteger(n);
  Structure* problem = heap.newStructure(4);

  problem->setFunctor(AtomTable::psi2_resume);   // "$psi2_resume"
  problem->setArgument(1, psiSaveState());
  problem->setArgument(2, instr);
  problem->setArgument(3, object1);
  problem->setArgument(4, object2);

  return(problem);
}

Object*
Thread::psi3BuildCall(word32 n, Object * object1, Object * object2, 
		      Object * object3)
{
  Object* instr = heap.newInteger(n);
  Structure* problem = heap.newStructure(5);

  problem->setFunctor(AtomTable::psi3_resume);   // "$psi3_resume"

  problem->setArgument(1, psiSaveState());
  problem->setArgument(2, instr);
  problem->setArgument(3, object1);
  problem->setArgument(4, object2);
  problem->setArgument(5, object3);

  return(problem);
}

Object*
Thread::psi4BuildCall(word32 n,
		      Object * object1, Object * object2, Object * object3,
		      Object * object4)
{
  Object* instr = heap.newInteger(n);
  Structure* problem = heap.newStructure(6);

  problem->setFunctor(AtomTable::psi4_resume);   // "$psi4_resume"

  problem->setArgument(1, psiSaveState());
  problem->setArgument(2, instr);
  problem->setArgument(3, object1);
  problem->setArgument(4, object2);
  problem->setArgument(5, object3);
  problem->setArgument(6, object4);

  return(problem);
}

Object*
Thread::psi5BuildCall(word32 n,
		      Object * object1, Object * object2, Object * object3,
		      Object * object4, Object * object5)
{
  Object* instr = heap.newInteger(n);
  Structure* problem = heap.newStructure(7);

  problem->setFunctor(AtomTable::psi5_resume);   // "$psi5_resume"

  problem->setArgument(1, psiSaveState());
  problem->setArgument(2, instr);
  problem->setArgument(3, object1);
  problem->setArgument(4, object2);
  problem->setArgument(5, object3);
  problem->setArgument(6, object4);
  problem->setArgument(7, object5);

  return(problem);
}

//
// Pseudo instruction error handlers
//
CodeLoc
Thread::psi0ErrorHandler(word32 n)
{
  X[0] = psiSaveState();
  X[1] = heap.newInteger(error_value);
  X[2] = heap.newInteger(error_arg);
  X[3] = heap.newInteger(n);
  return
    predicates->getCode(predicates->lookUp(AtomTable::psi0_error_handler,
			4, atoms, code)).getPredicate(code);
                                               // "$psi0_error_handler"
}

CodeLoc
Thread::psi1ErrorHandler(word32 n, Object * object1)
{
  X[0] = psiSaveState();
  X[1] = heap.newInteger(error_value);
  X[2] = heap.newInteger(error_arg);
  X[3] = heap.newInteger(n);
  X[4] = object1;
  return
    predicates->getCode(predicates->lookUp(AtomTable::psi1_error_handler,
			5, atoms, code)).getPredicate(code);
                                               // "$psi1_error_handler"
}

CodeLoc
Thread::psi2ErrorHandler(word32 n, Object * object1, Object * object2)
{
  X[0] = psiSaveState();
  X[1] = heap.newInteger(error_value);
  X[2] = heap.newInteger(error_arg);
  X[3] = heap.newInteger(n);
  X[4] = object1;
  X[5] = object2;
  return
    predicates->getCode(predicates->lookUp(AtomTable::psi2_error_handler,
			6, atoms, code)).getPredicate(code);
                                               // "$psi2_error_handler"
}

CodeLoc
Thread::psi3ErrorHandler(word32 n, Object * object1, Object * object2, 
			 Object * object3)
{
  X[0] = psiSaveState();
  X[1] = heap.newInteger(error_value);
  X[2] = heap.newInteger(error_arg);
  X[3] = heap.newInteger(n);
  X[4] = object1;
  X[5] = object2;
  X[6] = object3;
  return
    predicates->getCode(predicates->lookUp(AtomTable::psi3_error_handler,
			7, atoms, code)).getPredicate(code);
                                               // "$psi3_error_handler"
}

CodeLoc
Thread::psi4ErrorHandler(word32 n, Object * object1, Object * object2, 
			 Object * object3, Object * object4)
{
  X[0] = psiSaveState();
  X[1] = heap.newInteger(error_value);
  X[2] = heap.newInteger(error_arg);
  X[3] = heap.newInteger(n);
  X[4] = object1;
  X[5] = object2;
  X[6] = object3;
  X[7] = object4;
  return
    predicates->getCode(predicates->lookUp(AtomTable::psi4_error_handler,
			8, atoms, code)).getPredicate(code);
                                               // "$psi4_error_handler"
}

CodeLoc
Thread::psi5ErrorHandler(word32 n, Object * object1, Object * object2, 
			 Object * object3, Object * object4, 
			 Object * object5 )
{
  X[0] = psiSaveState();
  X[1] = heap.newInteger(error_value);
  X[2] = heap.newInteger(error_arg);
  X[3] = heap.newInteger(n);
  X[4] = object1;
  X[5] = object2;
  X[6] = object3;
  X[7] = object4;
  X[8] = object5;
  return
    predicates->getCode(predicates->lookUp(AtomTable::psi5_error_handler,
			9, atoms, code)).getPredicate(code);
                                               // "$psi5_error_handler"
}














