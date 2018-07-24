// sub_escape.h - Routines for manipulating substitution and its term.
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
// $Id: sub_escape.h,v 1.2 2003/06/26 00:10:40 qp Exp $

#ifndef	SUB_ESCAPE_H
#define	SUB_ESCAPE_H

public:
//
// psi_sub(term)
// Succeeds if the term has a substitution.
// mode(in)
//
ReturnValue psi_sub(Object *& );

//
// psi_get_substitution(term, subptr)
// Return the substitution of the term.
// mode(in,out)
//
ReturnValue psi_get_substitution(Object *& , Object *& );

//
// psi_sub_term(term, term)
// Return the term without its substitution.
// mode(in,out)
//
ReturnValue psi_sub_term(Object *& , Object *& );

//
// psi_build_sub_term(sub, term, sub_term)
// Join a substitution and a term together to form a new term.
// mode(in,in,out)
//
ReturnValue psi_build_sub_term(Object *& , Object *& , Object *& );

//
// psi_empty_sub(empty_sub)
// Return the representation of an empty substitution as an INTEGER.
// mode(out)
//
ReturnValue psi_empty_sub(Object *& );

//
// psi_new_sub(size, existing_sub, sublist, new_sub)
// Create a new empty substitution block of a given size and link it with
// existing substitutions.
// mode(in, in, in, out)
//
ReturnValue psi_new_sub(Object *&, Object *&, Object *&, Object *&);



//
// psi_next_sub(subptr0, subptr1)
// Return the next substitution from subptr0.
// mode(in,out)
//
ReturnValue psi_next_sub(Object *& , Object *& );

//
// psi_sub_table_size(subptr, size)
// Return the number of entries (size) in a substitution table.
// mode(in,out)
//
ReturnValue psi_sub_table_size(Object *& , Object *& );

//
// psi_set_domain(position, sub, variable)
// Assign the variable to the domain of the specified position of the 
// substitution.
// mode(in,in,in)
//
ReturnValue psi_set_domain(Object *& , Object *& , Object *& );

//
// psi_set_range(position, sub, term)
// Assign the term to the range of the specified position of the substitution.
// mode(in,in,in)
//
ReturnValue psi_set_range(Object *& , Object *& , Object *& );

//
// psi_get_domain(position, sub, variable)
// Return the domain object variable at the specified position of a
// substitution.
// mode(in,in,out)
//
ReturnValue psi_get_domain(Object *& , Object *& , Object *& );

//
// psi_get_range(position, sub, term)
// Return the range at the specified position of a substitution.
// mode(in,in,out)
//
ReturnValue psi_get_range(Object *& , Object *& , Object *& );

//
// psi_compress_sub(T, CompressesT)
//  make a call on dropSub to compress sub.
// mode(in,out)
//
ReturnValue psi_compress_sub_object_variable(Object *& , Object *& );

//
// Copy the substitution part of a term - leaving the term part unchanged.
// Used when a desctructive update of the substitution is required.
// mode(in,out)
//
ReturnValue psi_copy_substitution(Object *& , Object *& );

//
// Test if the term has a substitution and that the sub is a single sub.
// NOTE - dropSub should not be used.
// mode(in)
//
ReturnValue psi_single_sub(Object *& );

//
// Return true if the term needs to be simplified for nfi testing.
// The term should be of the form s*X where X is any variable and
// s is non-empty and not of the form [$/x].
//
ReturnValue psi_require_nfi_simp(Object *&, Object *&);

//
// psi_set_domains_apart(ObjVar, Sub, Pos, SubPos) makes
// ObjVar differnet from all the domain elelents in Sub up to
// but not including domain position Pos in SubPos.
//
ReturnValue psi_set_domains_apart(Object *&, Object *&,
                                  Object *&, Object *&);

#endif // SUB_ESCAPE_H

