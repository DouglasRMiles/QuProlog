// exception.h - Define low level exception support routines.
//               The idea is evolved from IC-Prolog and made compatible with
//               Quintus Prolog.
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
// $Id: exception.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	EXCEPTION_H
#define	EXCEPTION_H

public:
//
// psi_get_catch(variable)
// Return the current value in the catch register.
// mode(in)
//
ReturnValue psi_get_catch(Object *& );

//
// psi_set_catch(choice point)
// Set the catch register with the given value.
// mode(in)
//
ReturnValue psi_set_catch(Object *& );

//
// psi_failpt_to_catch
// Transfer the value from currentChoicePoint to catch.
//
ReturnValue psi_failpt_to_catch(void);

//
// psi_catch_to_failpt
// Transfer the value from catch to currentChoicePoint.
// mode()
//
ReturnValue psi_catch_to_failpt(void);

//
// psi_psi_resume(state)
// Restore saved X regs and PC
// mode(in)
//
ReturnValue psi_psi_resume(Object *& );

#endif	// EXCEPTION_H

