
// equal.h
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
// $Id: equal.h,v 1.2 2001/09/20 03:22:06 qp Exp $

#ifndef	EQUAL_H
#define	EQUAL_H

public:

//
// C-level implementation of ==
//
bool equalEqual(PrologValue&, PrologValue&, int&);
bool equalEqual_Original(PrologValue& term1, PrologValue& term2, int& counter);

//
// C-level version of simplify_term
//

//
// Top-level - returns true iff some simplification was done.
//
bool simplify_term(PrologValue&, Object*&);

bool simplify_sub_term(PrologValue&, Object*&, Object*);

bool gen_nfi_delays(ObjectVariable*, Object*);

void transform_with_tester(Object*, Object*&, Object*);

#endif	// EQUAL_H







