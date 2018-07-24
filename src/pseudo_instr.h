// pseudo_instr.h -  definitions for pseudo-instructions
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
// $Id: pseudo_instr.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	PSEUDO_INSTR_H
#define	PSEUDO_INSTR_H

Object*&
PSIGetReg(const word32 i)
{
  if (i < NUMBER_X_REGISTERS)
    {
      return X[i];
    }
  else
    {
      return envStack.yReg(currentEnvironment, i - NUMBER_X_REGISTERS);
    }
}

//
// Create new variables for objects associated with an arg with out mode
// The modes are bits with 1 meaning out mode.
//
void psi1NewVars(int32, Object *&);
void psi2NewVars(int32, Object *&, Object *&);
void psi3NewVars(int32, Object *&, Object *&, Object *&);
void psi4NewVars(int32, Object *&, Object *&, Object *&, Object *&);
void psi5NewVars(int32, Object *&, Object *&, Object *&, Object *&, Object *&);

//
// Build a call for a pseudo instruction for use in interrupt handling
// and fast retry
//
Object* psi0BuildCall(word32);
Object* psi1BuildCall(word32, Object *);
Object* psi2BuildCall(word32, Object *, Object *);
Object* psi3BuildCall(word32, Object *, Object *, Object *);
Object* psi4BuildCall(word32, Object *, Object *, Object *, Object *);
Object* psi5BuildCall(word32, Object *, Object *, Object *, Object *, Object *);

//
// Pseudo instruction error handlers
// These are executed when a positive error number is returned from
// the pseudo instruction
//
CodeLoc psi0ErrorHandler(word32);
CodeLoc psi1ErrorHandler(word32, Object *);
CodeLoc psi2ErrorHandler(word32, Object *, Object *);
CodeLoc psi3ErrorHandler(word32, Object *, Object *, Object *);
CodeLoc psi4ErrorHandler(word32, Object *, Object *, Object *, Object *);
CodeLoc psi5ErrorHandler(word32, Object *, Object *, Object *, Object *, Object *);

//
// Build a structure to hold the current X registers and PC.
//
Object* psiSaveState(void);

#endif	// PSEUDO_INSTR_H
