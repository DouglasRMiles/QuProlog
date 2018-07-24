// arithmetic.h -  definitions for pseudo-instructions for arithmetic
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
// $Id: arithmetic.h,v 1.2 2005/03/27 22:07:37 qp Exp $

#ifndef ARITHMETIC_H
#define ARITHMETIC_H




private:
//
// arithEvaluate is an auxilary function used by arithmetical pseudo
//instructions to carry out the evaluation of expressions.
//
//number arithEvaluate(PrologValue& pval);

public:
//
// psi_is(Out, Exp)
// mode(out,in)
//
ReturnValue psi_is(Object *& , Object *& );

//
// psi_less(A, B)
// mode(in,in)
// true iff A < B
//
ReturnValue psi_less(Object *& , Object *& );

//
// psi_lesseq(A, B)
// mode(in,in)
// true iff A <= B
//
ReturnValue psi_lesseq(Object *& , Object *& );

//
// psi_add(A,B,Sum)
// mode(in,in,out)
// Sum = A + B
//
ReturnValue psi_add(Object *& , Object *& , Object *& );

//
// psi_subtract(A,B,Diff)
// mode(in,in,out)
// Diff = A - B
//
ReturnValue psi_subtract(Object *& , Object *& , Object *& );

//
// psi_increment(A,B)
// mode(in,out)
// B = A + 1
//
ReturnValue psi_increment(Object *& , Object *& );

//
// psi_decrement(A,B)
// mode(in,out)
// B = A - 1
//
ReturnValue psi_decrement(Object *& , Object *& );

//
// psi_hash_double(A,B)
// mode(in,out)
//
//
ReturnValue psi_hash_double(Object *& , Object *& );

#endif // ARITHMETIC_H

