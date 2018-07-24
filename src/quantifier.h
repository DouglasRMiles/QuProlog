// quantifier.h - routines for manipulating quantified term.
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
// $Id: quantifier.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	QUANTIFIER_H
#define	QUANTIFIER_H

public:
//
// psi_quant(term)
// Succeeds if term is a quantified term.
// mode(in)
//
ReturnValue psi_quant(Object *&);

//
// psi_quantifier(term, quantifier)
// Return the quantifier of a quantified term.
// mode(in,out)
//
ReturnValue	psi_quantifier(Object *&, Object *&);

//
// psi_bound_var(term, variables)
// Return the bound variables of a quantified term.
// mode(in,out)
//
ReturnValue	psi_bound_var(Object *&, Object *&);

//
// psi_body(term, body)
// Return the body of a quantified term.
// mode(in,out)
//
ReturnValue	psi_body(Object *&, Object *&);

//
// psi_quantify(term, quantifier, variables, body)
// term is the quantified term made up from quantifier, variables and body.
// mode(in,in,in,in)
//
ReturnValue	psi_quantify(Object *&, Object *&, Object *&, Object *&);

//
// psi_check_binder(bound_list, object variables list)
// Ensure the object variables in the bound list mutually distinct and the 
// object variables in object variables list are distinct from those in bound
// list.
// mode(in,in)
//
ReturnValue	psi_check_binder(Object *&, Object *&);

#endif	// QUANTIFIER_H
