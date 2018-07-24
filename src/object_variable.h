// object_variable.h - Routines for manipulating object variables.
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
// $Id: object_variable.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	OBJECT_VARIABLE_H
#define	OBJECT_VARIABLE_H

//
// psi_object_variable(term)
// Succeeds if term is an object variable.
// mode(in)
//
ReturnValue 	psi_object_variable(Object *&);

//
// psi_local_object_variable(term)
// Succeeds if term is a local object variable.
// mode(in)
//
ReturnValue	psi_local_object_variable(Object *&);

//
// psi_new_object_variable(variable)
// Return a new object variable.
// mode(out)
//
ReturnValue	psi_new_object_variable(Object *&);

//
// psi_is_distinct(object_variable1, object_variable2)
// Succeeds iff object_variable1 and object_variable2 are distinct object vars
// mode(in,in)
//
ReturnValue 	psi_is_distinct(Object *&, Object *&);

//
// psi_get_distinct(object_variable, variable)
// Retrieve the distinctness information under object_variable.
// mode(in,out)
//
ReturnValue	psi_get_distinct(Object *&, Object *&);

//
// psi_object_variable_name_to_prefix(atom, atom)
// Strip off an object variable suffix.
// mode(in,out)
//
ReturnValue	psi_object_variable_name_to_prefix(Object *&, Object *&);

//
// psi_valid_object_variable_prefix(atom)
// Returns true if the atom is a valid object_variable prefix.
// mode(in)
//
ReturnValue	psi_valid_object_variable_prefix(Object *&);

#endif	// OBJECT_VARIABLE_H
