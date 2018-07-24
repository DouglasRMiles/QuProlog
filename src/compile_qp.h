// compile_qp.h -
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
// $Id: compile_qp.h,v 1.1 2000/12/13 23:10:01 qp Exp $

#ifndef	COMPILE_QP_H
#define	COMPILE_QP_H


public:

void permvars(Object*, WordArray&, int&);

Object* build_list(WordArray&);

ReturnValue psi_ccompile(Object*&, Object*&, Object*&, Object*&);

#endif	// COMPILE_QP_H

