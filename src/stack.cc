// stack.cc - Fundamental stack arrangement.
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
// $Id: stack.cc,v 1.6 2005/03/08 00:35:14 qp Exp $

#ifndef STACK_CC
#define STACK_CC

#include <iostream>

#include "area_offsets.h"
#include "defs.h"
#include "errors.h"
#include "int.h"
#include "stack_qp.h"

template <class StoredType>
PrologStack<StoredType>::~PrologStack(void)
{
        top = 0;
}

//
// Write the stack to a stream.
//
template <class StoredType>
void
PrologStack<StoredType>::saveStack(ostream& ostrm, const wordlong magic) const
{
  this->saveArea(ostrm, magic, 0, top);
  //
  // Write the top of stack.
  //
  IntSave<StackLoc>(ostrm, top);
}

//
// Load the stack from a stream.
//
template <class StoredType>
void
PrologStack<StoredType>::loadStack(istream& istrm)
{
  this->loadArea(istrm, 0);
  //
  // Read the top of stack.
  //
  top = IntLoad<StackLoc>(istrm);
}

#endif	// STACK_CC
