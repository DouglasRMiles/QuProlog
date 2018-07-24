// esc_init.cc - Call the initialisation procedure for different escape
//		 functions.
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
// $Id: esc_init.cc,v 1.2 2000/12/13 23:10:01 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;

//
// Escape functions' headers.
//
void
Thread::InstallEscapes(void)
{
#define	DefEscape(escape, arity, fn)	\
	predicates.linkEscape((escape), (arity), (fn), atoms)
#include "escapes.h"
#undef	DefEscape
}

void
Thread::EscapeInit(void)
{
  // This function intentially left blank!
  // It's only here for historical reasons.
}
