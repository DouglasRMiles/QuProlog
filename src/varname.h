// varname.h -  Get and set variable names.
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
// $Id: varname.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	VARNAME_H
#define	VARNAME_H

public:

void name_term_vars_sub(Object*, Object*&, bool, bool);
void name_term_vars(Object*, Object*&, bool, bool);

//
// psi_get_var_name(variable, name)
// Return the name of the variable if there is one.  Otherwise, fail.
// mode(in,out)
//
ReturnValue psi_get_var_name(Object *& , Object *& );

//
// psi_set_var_name(var, name)
// Set the name for the given variable using the supplied name as the
// prefix.
// mode(in,in)
//
ReturnValue psi_set_var_name(Object *& , Object *& );

//
// psi_set_object_variable_name(objvar, name)
// Set the name for the given object variable using the supplied name as the
// prefix.
// mode(in,in)
//
ReturnValue psi_set_object_variable_name(Object *& , Object *& );

//
// psi_get_unnamed_vars(term,varlist)
// Get all unnamed (ob)vars in term - return them in varlist.
// mode(in,out)
//
ReturnValue psi_get_unnamed_vars(Object *& , Object *& );

//
//
// psi_name_vars(term,varlist)
// Name all unnamed (ob)vars in term - return them in varlist.
// mode(in,out)
//
ReturnValue psi_name_vars(Object *& , Object *& );

//
// psi_name_vars(term)
// Name all unnamed (ob)vars in term.
// mode(in)
//
ReturnValue psi_name_vars(Object *& );

#endif	// VARNAME_H
