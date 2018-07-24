// structure.h - Contains functions which retrieve information from and
//                build up structures.
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
// $Id: structure.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef STRUCTURE_H
#define STRUCTURE_H

public:
// psi_compound(term)
// Succeed if term is a structure or a list.
// mode(in)
//
ReturnValue 	psi_compound(Object *& );

// psi_functor(Structure, Functor, Arity)
// Structure has functor Functor and arity Arity
// mode(in,in,in)
//
ReturnValue 	psi_functor(
			    Object *& , Object *& , Object *& );

//
// psi_arg(N, Str, Arg)
// Extract the N'th arg from Str
// mode(in,in,out)
//
ReturnValue 	psi_arg(Object *& , Object *& , Object *& );

//
// psi_put_structure(F, N, Str)
// mode(in,in,out)
//
ReturnValue psi_put_structure(Object *& , Object *& , 
					      Object *& );
//
// psi_set_argument(F, N, Str)
// mode(in,in,in)
//
ReturnValue psi_set_argument(Object *& , Object *& , 
					      Object *& );


//
// psi_setarg(N, F, Arg)
// mode(in,in,in)
//
// A backtrackabe destructive update to the N'th arg of F
ReturnValue psi_setarg(Object *&, Object *&, Object *&);

#endif // STRUCTURE_H
