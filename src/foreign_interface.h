// foreign_interface.h - A class for connectiong foreign functions to 
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
// $Id: foreign_interface.h,v 1.2 2006/02/14 02:40:09 qp Exp $

#ifndef FOREIGN_INTERFACE_H
#define FOREIGN_INTERFACE_H

#include "atom_table.h"
//#include "thread_qp.h"

class Object;
class Structure;
class Thread;

extern AtomTable *atoms;

class ForeignInterfaceBase 
{
 public:
  virtual ~ForeignInterfaceBase() {}
  virtual Object* getXReg(int i) = 0;
  virtual Object* makeAtom(const char* s) = 0;
  virtual Object* makeInteger(const qint64 i) = 0;
  virtual Object* makeString(const char* s) = 0;
  virtual Object* makeDouble(const double d) = 0;
  virtual Structure* makeStructure(const int n) = 0;
  virtual Object* makeCons(Object* h, Object* t) = 0;
  virtual char* getAtomString(Object* a) = 0;
  virtual char* getString(Object* a) = 0;
  virtual bool unify(Object* o1, Object* o2) = 0;
  virtual bool push_message(const char * msg) = 0;
};

class ForeignInterface : public ForeignInterfaceBase
{
 public:
  explicit ForeignInterface(Thread* th) : threadptr(th) {}
    
    Object* getXReg(int i); 
    Object* makeAtom(const char* s); 
    Object* makeInteger(const qint64 i); 
    Object* makeString(const char* s); 
    Object* makeDouble(const double d);
    Structure* makeStructure(const int n);
    Object* makeCons(Object* h, Object* t);

    char* getAtomString(Object* a);
    char* getString(Object* a);
    bool unify(Object* o1, Object* o2);
    bool push_message(const char * msg);
    private:
      Thread* threadptr;
 };

#endif //FOREIGN_INTERFACE_H


