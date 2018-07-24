// regalloc.h - Register allocation for compiler
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
// $Id: regalloc.h,v 1.4 2002/11/13 04:04:16 qp Exp $

#ifndef	REGALLOC_H
#define	REGALLOC_H

#include "compiler_support.h"
//#include "io_qp.h"

void alloc_registers(WordArray&, xreglife&, WordArray&, bool&);
Object* excess_realloc_reg(Object*, int&, Object**, Object**);
void excess_registers(WordArray&);
void envsize(WordArray&, int&);
void voidalloc(WordArray&, int, WordArray&);
void assn_elim(WordArray&, WordArray&);
void peephole(WordArray&, WordArray&, int, bool);
#endif	// REGALLOC_H

