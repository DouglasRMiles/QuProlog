// temperature.h - routines for handling freeze and thaw.
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
// $Id: temperature.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	TEMPERATURE_H
#define	TEMPERATURE_H

public:

void freeze_thaw_sub(Object*, Object*&,  bool, bool);

void freeze_thaw_term(Object*, Object*&, bool, bool);

//
// psi_freeze_term(term)
// Set the temperature tag of all variables in term  to freeze.
// mode(in)
//
ReturnValue psi_freeze_term(Object *&);

//
// psi_freeze_term(term,list)
// Set the temperature tag of all variables in term  to freeze.
// All variables that are frozen by this operation are returned in list.
// mode(in,out)
//
ReturnValue psi_freeze_term(Object *&, Object *&);


//
// psi_thaw_term(term)
// Set the temperature tag of all variables in term  to thaw.
// mode(in)
//
ReturnValue psi_thaw_term(Object *&);

//
// psi_thaw_term(term,list)
// Set the temperature tag of all variables in term  to thaw.
// All variables that are frozen by this operation are returned in list.
// mode(in,out)
//
ReturnValue psi_thaw_term(Object *&, Object *&);

//
// psi_freeze_var(term)
// Set the temperature tag of a (object) variable to freeze.
// mode(in)
//
ReturnValue psi_freeze_var(Object *&);

//
// psi_thaw_var(term)
// Set the temperature tag of a (object) variable to thaw.
// mode(in)
//
ReturnValue psi_thaw_var(Object *&);

//
// psi_frozen_var(term)
// Succeed if the (object) variable is frozen.
// mode(in)
//
ReturnValue psi_frozen_var(Object *&);

//
// psi_thawed_var(term)
// Succeed if the (object) variable is thawed.
// mode(in)
//
ReturnValue psi_thawed_var(Object *&);

#endif	// TEMPERATURE_H
