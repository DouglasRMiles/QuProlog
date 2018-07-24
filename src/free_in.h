// free_in.h -	"free_in" escape test functions.
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
// $Id: free_in.h,v 1.2 2001/09/20 03:22:06 qp Exp $

#ifndef	FREE_IN_H
#define	FREE_IN_H

public:
//
// psi_not_free_in(object_variable, term)
// Execute the not free in constraint.  The problem can succeed, fail or delay.
// mode(in,in)
//
ReturnValue	psi_not_free_in(Object *& , Object *& );

//
// psi_not_free_in_var_simplify(object_variable, var)
// Simplify the substitution associated with var and apply not free in.
//
ReturnValue	psi_not_free_in_var_simplify(Object *& , Object *& );

ReturnValue psi_addExtraInfoToVars(Object*&);

//
// Call notFreeInNFISimp
// mode(in,in)
//
ReturnValue psi_not_free_in_nfi_simp(Object*&, Object*&);  

//
// is_not_free_in
// mode(in,in)
//
ReturnValue psi_is_not_free_in(Object*&, Object*&);

//
// is_free_in
// mode(in,in)
//
ReturnValue psi_is_free_in(Object*&, Object*&);
      
#endif	// FREE_IN_H
