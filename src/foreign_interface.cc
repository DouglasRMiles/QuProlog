// foreign_interface.cc - A class for connectiong foreign functions to 
// thread methods.
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
// $Id: foreign_interface.cc,v 1.2 2006/02/14 02:40:09 qp Exp $

#include "thread_qp.h"
#include "pedro_env.h"
#include "global.h"

//class PedroMessage;

Object* 
ForeignInterface::getXReg(int i) 
{ return threadptr->XRegs()[i]->variableDereference(); }

Object* 
ForeignInterface::makeAtom(const char* s)
{return atoms->add(s); }

Object* 
ForeignInterface::makeInteger(const qint64 i) 
{ return threadptr->TheHeap().newInteger(i); }

Object* 
ForeignInterface::makeString(const char * s) 
{ return threadptr->TheHeap().newStringObject(s); }

Object* 
ForeignInterface::makeDouble(const double d)
{ return threadptr->TheHeap().newDouble(d); }

Structure* 
ForeignInterface::makeStructure(const int n)
{ return  threadptr->TheHeap().newStructure(n); }

Object* 
ForeignInterface::makeCons(Object* h, Object* t)
{ return  threadptr->TheHeap().newCons(h, t); }

char*
ForeignInterface::getAtomString(Object* a)
{ return OBJECT_CAST(Atom*, a)->getName(); }

char*
ForeignInterface::getString(Object* a)
{ return OBJECT_CAST(StringObject*, a)->getChars(); }

bool 
ForeignInterface::unify(Object* o1, Object* o2)
{ return threadptr->unify(o1 , o2); }
      
bool 
ForeignInterface::push_message(const char * msg)
{
  threadptr->MessageQueue().push_back(new PedroMessage(msg)); 
  return true;

}
      
