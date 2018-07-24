// unravel.h -
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
// $Id: unravel.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	UNRAVEL_H
#define	UNRAVEL_H

#include "compiler_support.h"

public: 

void setyregs(WordArray&, int);

Object* yreg(int);

Object* xreg(int);

wordptr callpred(Object*, int);

wordptr getput(Object*, Object*, bool, WordArray&);

wordptr unifyset(Object*, bool, WordArray&);

wordptr getputlist(Object*, bool, WordArray&);

wordptr getputstruct(Object*, int, Object*, bool, WordArray&);

wordptr getstructframe(Object*, int, WordArray&);

wordptr putquant(Object*, WordArray&);

wordptr putsub(Object*, int, WordArray&);

wordptr putemptysub(Object*, WordArray&);


wordptr putsubterm(Object*, Object*, WordArray&);


void xputget(Object*, Object*, WordArray&, WordArray&);

void varunify(Object*, Object*, WordArray&, WordArray&);

void goalSubSpread(Object*, Object*, WordArray&, WordArray&);

void goalStructSpread(Object*, Object*, WordArray&, WordArray&);

void goalArgSpread(Object*, Object*, WordArray&, WordArray&);

void headStructSpread(Object*, Object*, WordArray&, bool, WordArray&);

void headArgSpread(Object*, Object*, WordArray&, WordArray&);

void unravelHead(Object*, WordArray&, WordArray&);

void goalSpread(Object*, WordArray&, WordArray&);

void unravelBody(Object*, WordArray&, WordArray&);

void unravel(Object*,  WordArray&, WordArray&, int&);

#endif	// UNRAVEL_H



