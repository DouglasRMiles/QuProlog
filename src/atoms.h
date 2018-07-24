// atoms.h - Predicates for maniuplating atoms.
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
// $Id: atoms.h,v 1.2 2001/06/04 01:22:54 qp Exp $

#ifndef	ATOMS_H
#define	ATOMS_H

public:
//
// psi_atom_length(atom, variable)
// Work out the string length of an atom.
// mode(in,out)
//
ReturnValue psi_atom_length(Object *& , Object *& );

//
// psi_atom_concat2(atomic, atomic, atomic)
// Join the first 2 atomics to get the third.
// mode(in,in,out)
//
ReturnValue psi_atom_concat2(Object *& object1, Object *& object2, 
			     Object *& object3);
//
// psi_concat_atom(list of atomic, variable)
// Join a list of atomic together to form a new atom.
// mode(in,out)
//
ReturnValue psi_concat_atom(Object *& , Object *& );

//
// psi_concat_atom3(list of atomic, separator, ariable)
// Join a list of atomic together to form a new atom separating
// each atom with separator
// mode(in,in,out)
//
ReturnValue psi_concat_atom3(Object *& , Object *& , Object *& );

//
// psi_atom_search(atom1, start, atom2, variable)
// Return the location with atom1 where atom2 is located.
// mode(in,in,in,out)
//
ReturnValue psi_atom_search(Object *& , Object *& , Object *& , Object *& );

//
// psi_sub_atom(atom, start, length, variable)
// Return a new atom formed from the supplied atom.
// mode(in,in,in,out)
//
ReturnValue psi_sub_atom(Object *& , Object *& , Object *& , Object *& );

#endif	// ATOMS_H







