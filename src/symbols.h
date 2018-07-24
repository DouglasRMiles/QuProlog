// symbols.h - Contains a function which can be used to manage the access to
//	       symbol tables.
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
// $Id: symbols.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef SYMBOLS_H
#define SYMBOLS_H

//
// psi_get_atom_from_atom_table(integer, atom, integer)
// Return the next atom in the atom table.
// mode(in,out,out)
//
ReturnValue psi_get_atom_from_atom_table(Object *& , Object *& , Object *& );

//
// psi_get_pred_from_pred_table(integer, atom, integer)
// Return the next predicate in the predicate table.
// mode(in,out,out,out)
//
ReturnValue  psi_get_pred_from_pred_table(Object *& , Object *& , 
					  Object *& , Object *& );

//
// symtype outputs into  :
//  (0) If the predicate has no entry point defined.
//  (1) If the predicate is a dynamic predicate.
//  (2) If the predicate is a compiled predicate.
//  (3) If the predicate is an escape predicate.
// mode(in,in,out)
//
ReturnValue	psi_symtype(Object *& , Object *& , Object *& );

#endif // SYMBOLS_H
