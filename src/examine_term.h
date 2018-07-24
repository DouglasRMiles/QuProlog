// examine_term.h - The QU-Prolog functions which have to do with examining
//                  or testing a term.
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
// $Id: examine_term.h,v 1.4 2006/02/06 00:51:38 qp Exp $

#ifndef EXAMINE_TERM_H
#define EXAMINE_TERM_H

//
// psi_collect_vars(term, list)
// Collect all the variables (and object_variables) in term into list
// mode(in,out)
//
ReturnValue	psi_collect_vars(Object *& , Object *& );

//
// psi_var(term)
// True if term is a variable, false otherwise
// mode(in)
//
ReturnValue	 psi_var(Object *& );

//
// psi_atom(term)
// True if term X0 is an atom, false otherwise
// mode(in)
//
ReturnValue 	psi_atom(Object *& );

//
// psi_integer(term)
// True if term is an integer, false otherwise
// mode(in)
//
ReturnValue psi_integer(Object *& );

//
// psi_float(term)
// True if term is a float, false otherwise
// mode(in)
//
ReturnValue psi_float(Object *& );

//
// psi_atomic(term)
// True if term is atomic, false otherwise
// mode(in)
//
ReturnValue psi_atomic(Object *& );

//
// psi_any_variable(term)
// True if term is a variable or object variable, false otherwise
// mode(in)
//
ReturnValue psi_any_variable(Object *& );

//
// psi_simple(term)
// True if term is any variable or atomic, false otherwise
// mode(in)
//
ReturnValue psi_simple(Object *& );

//
// psi_nonvar(term)
// True if term is not a variable, false otherwise
// mode(in)
//
ReturnValue psi_nonvar(Object *& );

//
// psi_std_var(term)
// True if term is a variable with no subs, false otherwise
// mode(in)
//
ReturnValue psi_std_var(Object *& );

//
// psi_std_compound(term)
// True if term is compound with an atom functor, false otherwise
// mode(in)
//
ReturnValue psi_std_compound(Object *& );

//
// psi_std_nonvar(term)
// True if term is atomic or std_compound, false otherwise
// mode(in)
//
ReturnValue psi_std_nonvar(Object *& );

//
// psi_list(term)
// True if term is a list, false otherwise
// mode(in)
//
ReturnValue psi_list(Object *& );

// psi_string(term)
// True if term is a string, false otherwise
// mode(in)
//
ReturnValue psi_string(Object *& object1);

//
// psi_fast_simplify(term, simpterm)
// do a simple term simplification
// mode(in, out)
//
ReturnValue psi_fast_simplify(Object *& , Object *& );

ReturnValue psi_hash_variable(Object *& , Object *& );

#endif // EXAMINE_TERM_H
