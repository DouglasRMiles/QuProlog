// equal_escape.h - an escape function to call FastEqual.
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
// $Id: equal_escape.h,v 1.3 2002/03/27 23:23:47 qp Exp $

#ifndef EQUAL_ESCAPE_H
#define EQUAL_ESCAPE_H

public:
//
// psi_fast_equal(term1,term2,status)
// returns true iff term1 and term2 have the same structure.
// mode(in,in,out)
//
ReturnValue psi_fast_equal(Object *& , Object *& , Object *& );

//
// psi_equal_equal(term1,term2)
// returns true iff term1 == term2 .
// mode(in,in)
//
ReturnValue psi_equal_equal(Object *& , Object *&);

//
// psi_simplify_term(term1,term2)
// mode(in,out)
//
ReturnValue psi_simplify_term(Object *&, Object *&);

//
// psi_simplify_term3(term1,term2, issimp)
// mode(in,out,out)
//
ReturnValue psi_simplify_term3(Object *&, Object *&, Object *&);

//
// test for term1 \= term2
//
// mode(in, in)
//
ReturnValue psi_not_equal(Object *&, Object *&);

#endif	// EQUAL_ESCAPE_H










