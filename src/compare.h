// compare.h - Contains a function which compares the 2 terms
//             passed to it and returns the result of the 
//             comparison in X2.
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
// $Id: compare.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef COMPARE_H
#define COMPARE_H

public:
//
// psi_compare_var(var1, var2, res)
// Return -1 if var1 is senior than var2.
// mode(in,in,out)
//
ReturnValue psi_compare_var(Object *& , Object *& , Object *& );

//
// psi_compare_atom(atom1, atom2, res)
// Return -1 if atom1 is less than atom2 alphabetically.
// mode(in,in,out)
//
ReturnValue psi_compare_atom(Object *& , Object *& , Object *& );

//
//  psi_compare_pointers(term1, term2)
//  Return true iff the pointers are identical.
//  mode(in,in)
//
ReturnValue psi_compare_pointers(Object *& , Object *& );

int compareTerms(PrologValue * term1, PrologValue * term2);

ReturnValue psi_term_less_than(Object *& object1, Object *& object2);
ReturnValue psi_term_at_equal(Object *& object1, Object *& object2);
ReturnValue psi_term_greater_than(Object *& object1, Object *& object2);
#endif // COMPARE_H






