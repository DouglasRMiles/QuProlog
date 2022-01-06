// compare.cc - Contains a function which compares the 2 terms
//              passed to it and returns the result of the
//              comparison in X2.
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
// $Id: compare.cc,v 1.4 2006/01/31 23:17:49 qp Exp $

#include <string.h>

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;

//
// Thread::psi_compare_var(var1, var2, res)
// Return -1 if var1 is more senior than var2.
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_compare_var(Object *& object1, Object *& object2, Object *& object3)
{
  int32		res = 1;
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);
  
  assert(val1->isAnyVariable());
  assert(val2->isAnyVariable());
  assert(val1->tTag() == val2->tTag());
  
  if (reinterpret_cast<void*>(val1) < reinterpret_cast<void*>(val2))
    {
      res = -1;
    }
  object3 = heap.newShort(res);
  return(RV_SUCCESS);
}


//
// psi_compare_atom(atom1, atom2, res)
// Return -1 if atom1 is less than atom2 alphabetically.
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_compare_atom(Object *& object1, Object *& object2, Object *& object3)
{
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  assert(val1->isAtom());
  assert(val2->isAtom());

  char* str1 = OBJECT_CAST(Atom*, val1)->getName();
  char* str2 = OBJECT_CAST(Atom*, val2)->getName();
  object3 = 
    heap.newShort(strcmp(str1, str2));
  return(RV_SUCCESS);
}


//
//  psi_compare_pointers(term1, term2)
//  Return true iff the pointers are identical.
//  mode(in,in)
//
Thread::ReturnValue
Thread::psi_compare_pointers(Object *& object1, Object *& object2)
{
  return(BOOL_TO_RV(object1->variableDereference() == 
		    object2->variableDereference()));
}

#define CrossTag(t1, t2)	((t1) | (t2 >> 4))

//
// Assumes terms have been dereferenced

int
Thread::compareTerms(PrologValue * term1, PrologValue * term2)
{
  Object* val1 = term1->getTerm();
  Object* val2 = term2->getTerm();

  u_int tag1 = val1->getTag() & Object::TypeMask;
  u_int tag2 = val2->getTag() & Object::TypeMask;

  switch (CrossTag(tag1, tag2))
    {

    case CrossTag(Object::TypeVar, Object::TypeVar):
      {
	if (reinterpret_cast<void*>(val1) < reinterpret_cast<void*>(val2))
	  {
	    return -1;
	  }
	else if (reinterpret_cast<void*>(val1) > reinterpret_cast<void*>(val2))
	  {
	    return 1;
	  }
	else // the same var
	  {
	    if (term1->getSubstitutionBlockList()->isNil() &&
		term2->getSubstitutionBlockList()->isNil())
	      return 0;
	    PrologValue sub1(term1->getSubstitutionBlockList());
	    PrologValue sub2(term2->getSubstitutionBlockList());
	    return compareTerms(&sub1, &sub2);
	  }
	    break;
      }
    case CrossTag(Object::TypeVar, Object::TypeShort):
    case CrossTag(Object::TypeVar, Object::TypeLong):
    case CrossTag(Object::TypeVar, Object::TypeDouble):
    case CrossTag(Object::TypeVar, Object::TypeAtom):
    case CrossTag(Object::TypeVar, Object::TypeString):
    case CrossTag(Object::TypeVar, Object::TypeStruct):
    case CrossTag(Object::TypeVar, Object::TypeCons):
    case CrossTag(Object::TypeVar, Object::TypeObjVar):
    case CrossTag(Object::TypeVar, Object::TypeQuant):
    case CrossTag(Object::TypeShort, Object::TypeAtom):
    case CrossTag(Object::TypeShort, Object::TypeString):
    case CrossTag(Object::TypeShort, Object::TypeStruct):
    case CrossTag(Object::TypeShort, Object::TypeCons):
    case CrossTag(Object::TypeShort, Object::TypeObjVar):
    case CrossTag(Object::TypeShort, Object::TypeQuant):
    case CrossTag(Object::TypeLong, Object::TypeAtom):
    case CrossTag(Object::TypeLong, Object::TypeString):
    case CrossTag(Object::TypeLong, Object::TypeStruct):
    case CrossTag(Object::TypeLong, Object::TypeCons):
    case CrossTag(Object::TypeLong, Object::TypeObjVar):
    case CrossTag(Object::TypeLong, Object::TypeQuant):
    case CrossTag(Object::TypeDouble, Object::TypeAtom):
    case CrossTag(Object::TypeDouble, Object::TypeString):
    case CrossTag(Object::TypeDouble, Object::TypeStruct):
    case CrossTag(Object::TypeDouble, Object::TypeCons):
    case CrossTag(Object::TypeDouble, Object::TypeObjVar):
    case CrossTag(Object::TypeDouble, Object::TypeQuant):
    case CrossTag(Object::TypeAtom, Object::TypeString):
    case CrossTag(Object::TypeAtom, Object::TypeStruct):
    case CrossTag(Object::TypeAtom, Object::TypeCons):
    case CrossTag(Object::TypeAtom, Object::TypeObjVar):
    case CrossTag(Object::TypeAtom, Object::TypeQuant):
    case CrossTag(Object::TypeString, Object::TypeStruct):
    case CrossTag(Object::TypeString, Object::TypeCons):
    case CrossTag(Object::TypeString, Object::TypeObjVar):
    case CrossTag(Object::TypeString, Object::TypeQuant):
    case CrossTag(Object::TypeStruct, Object::TypeObjVar):
    case CrossTag(Object::TypeStruct, Object::TypeQuant):
    case CrossTag(Object::TypeCons, Object::TypeObjVar):
    case CrossTag(Object::TypeCons, Object::TypeQuant):
    case CrossTag(Object::TypeObjVar, Object::TypeQuant):
      {
	return -1;
	break;
      }


    case CrossTag(Object::TypeShort, Object::TypeVar):
    case CrossTag(Object::TypeLong, Object::TypeVar):
    case CrossTag(Object::TypeDouble, Object::TypeVar):
    case CrossTag(Object::TypeAtom, Object::TypeVar):
    case CrossTag(Object::TypeAtom, Object::TypeShort):
    case CrossTag(Object::TypeAtom, Object::TypeLong):
    case CrossTag(Object::TypeAtom, Object::TypeDouble):
    case CrossTag(Object::TypeString, Object::TypeVar):
    case CrossTag(Object::TypeString, Object::TypeAtom):
    case CrossTag(Object::TypeString, Object::TypeShort):
    case CrossTag(Object::TypeString, Object::TypeLong):
    case CrossTag(Object::TypeString, Object::TypeDouble):
    case CrossTag(Object::TypeStruct, Object::TypeVar):
    case CrossTag(Object::TypeStruct, Object::TypeShort):
    case CrossTag(Object::TypeStruct, Object::TypeLong):
    case CrossTag(Object::TypeStruct, Object::TypeDouble):
    case CrossTag(Object::TypeStruct, Object::TypeAtom):
    case CrossTag(Object::TypeStruct, Object::TypeString):
    case CrossTag(Object::TypeCons, Object::TypeVar):
    case CrossTag(Object::TypeCons, Object::TypeShort):
    case CrossTag(Object::TypeCons, Object::TypeLong):
    case CrossTag(Object::TypeCons, Object::TypeDouble):
    case CrossTag(Object::TypeCons, Object::TypeAtom):
    case CrossTag(Object::TypeCons, Object::TypeString):
    case CrossTag(Object::TypeObjVar, Object::TypeVar):
    case CrossTag(Object::TypeObjVar, Object::TypeShort):
    case CrossTag(Object::TypeObjVar, Object::TypeLong):
    case CrossTag(Object::TypeObjVar, Object::TypeDouble):
    case CrossTag(Object::TypeObjVar, Object::TypeAtom):
    case CrossTag(Object::TypeObjVar, Object::TypeString):
    case CrossTag(Object::TypeObjVar, Object::TypeStruct):
    case CrossTag(Object::TypeObjVar, Object::TypeCons):
    case CrossTag(Object::TypeQuant, Object::TypeVar):
    case CrossTag(Object::TypeQuant, Object::TypeShort):
    case CrossTag(Object::TypeQuant, Object::TypeLong):
    case CrossTag(Object::TypeQuant, Object::TypeDouble):
    case CrossTag(Object::TypeQuant, Object::TypeAtom):
    case CrossTag(Object::TypeQuant, Object::TypeString):
    case CrossTag(Object::TypeQuant, Object::TypeStruct):
    case CrossTag(Object::TypeQuant, Object::TypeCons):
    case CrossTag(Object::TypeQuant, Object::TypeObjVar):
      {
	return 1;
	break;
      }

    case CrossTag(Object::TypeShort, Object::TypeShort):
    case CrossTag(Object::TypeShort, Object::TypeLong):
    case CrossTag(Object::TypeLong, Object::TypeShort):
    case CrossTag(Object::TypeLong, Object::TypeLong):
      {
	int i1 = val1->getInteger();
	int i2 = val2->getInteger();
	if (i1 < i2) return -1;
	else if (i1 > i2) return 1;
	else return 0;
	break;
      }
    case CrossTag(Object::TypeShort, Object::TypeDouble):
    case CrossTag(Object::TypeLong, Object::TypeDouble):
      {
	int i1 = val1->getInteger();
	double f2 = val2->getDouble();
	if (i1 < f2) return -1;
	else if (i1 > f2) return 1;
	else return 0;
	break;
      }
    case CrossTag(Object::TypeDouble, Object::TypeShort):
    case CrossTag(Object::TypeDouble, Object::TypeLong):
      {
	double f1 = val1->getDouble();
	int i2 = val2->getInteger();
	if (f1 < i2) return -1;
	else if (f1 > i2) return 1;
	else return 0;
	break;
      }
    case CrossTag(Object::TypeDouble, Object::TypeDouble):
      {
	double f1 = val1->getDouble();
	double f2 = val2->getDouble();
	if (f1 < f2) return -1;
	else if (f1 > f2) return 1;
	else return 0;
	break;
      }
    case CrossTag(Object::TypeAtom, Object::TypeAtom):
      {
	char* str1 = OBJECT_CAST(Atom*, val1)->getName();
	char* str2 = OBJECT_CAST(Atom*, val2)->getName();
	int res = strcmp(str1, str2);
	if (res < 0) return -1;
	else if (res > 0) return 1;
	else return 0;
	break;
      }
    case CrossTag(Object::TypeString, Object::TypeString):
      {
	char* str1 = OBJECT_CAST(StringObject*, val1)->getChars();
	char* str2 = OBJECT_CAST(StringObject*, val2)->getChars();
	int res = strcmp(str1, str2);
	if (res < 0) return -1;
	else if (res > 0) return 1;
	else return 0;
	break;
      }


    case CrossTag(Object::TypeStruct, Object::TypeStruct):
      {
	Structure* str1 = OBJECT_CAST(Structure*, val1);
	Structure* str2 = OBJECT_CAST(Structure*, val2);
	int arity1 = str1->getArity();
	int arity2 = str2->getArity();
	if (arity1 < arity2) return -1;
	else if (arity1 > arity2) return 1;
	Object* sub1 = term1->getSubstitutionBlockList();
	Object* sub2 = term2->getSubstitutionBlockList();
	for (int i = 0; i <= arity1; i++) {
	  PrologValue arg1(sub1, str1->getArgument(i)->variableDereference());
	  PrologValue arg2(sub2, str2->getArgument(i)->variableDereference());
	  heap.prologValueDereference(arg1);
	  heap.prologValueDereference(arg2);
	  int ret = compareTerms(&arg1, &arg2);
	  if (ret != 0) return ret;					  
	}
	return 0;
	break;
      }
    case CrossTag(Object::TypeCons, Object::TypeStruct):
      {
	Structure* str2 = OBJECT_CAST(Structure*, val2);
	int arity2 = str2->getArity();
	if (2 < arity2) return -1;
	else if (2 > arity2) return 1;
	Object* sub2 = term2->getSubstitutionBlockList();
	PrologValue arg1(AtomTable::cons);
	PrologValue arg2(sub2, str2->getArgument(0)->variableDereference());
	heap.prologValueDereference(arg1);
	heap.prologValueDereference(arg2);
	return compareTerms(&arg1, &arg2);
	break;
      }
    case CrossTag(Object::TypeStruct, Object::TypeCons):
      {
	Structure* str1 = OBJECT_CAST(Structure*, val1);
	int arity1 = str1->getArity();
	if (2 > arity1) return -1;
	else if (2 < arity1) return 1;
	Object* sub1 = term1->getSubstitutionBlockList();
	PrologValue arg2(AtomTable::cons);
	PrologValue arg1(sub1, str1->getArgument(0)->variableDereference());
	heap.prologValueDereference(arg1);
	heap.prologValueDereference(arg2);
	return compareTerms(&arg2, &arg1);
	break;
      }

    case CrossTag(Object::TypeCons, Object::TypeCons):
      {
	Cons* str1 = OBJECT_CAST(Cons*, val1);
	Cons* str2 = OBJECT_CAST(Cons*, val2);
	Object* sub1 = term1->getSubstitutionBlockList();
	Object* sub2 = term2->getSubstitutionBlockList();
	PrologValue head1(sub1, str1->getHead());
	PrologValue head2(sub2, str2->getHead());
	heap.prologValueDereference(head1);
	heap.prologValueDereference(head2);
	int res = compareTerms(&head1, &head2);
	if (res != 0) return res;
	PrologValue tail1(sub1, str1->getTail());
	PrologValue tail2(sub2, str2->getTail());
	heap.prologValueDereference(tail1);
	heap.prologValueDereference(tail2);
	return compareTerms(&tail1, &tail2);
	break;
      }
	
	


    case CrossTag(Object::TypeObjVar, Object::TypeObjVar):
      {
	if (reinterpret_cast<void*>(val1) < reinterpret_cast<void*>(val2))
	  {
	    return -1;
	  }
	else if (reinterpret_cast<void*>(val1) > reinterpret_cast<void*>(val2))
	  {
	    return 1;
	  }
	else // the same var
	  {
	    if (term1->getSubstitutionBlockList()->isNil() &&
		term2->getSubstitutionBlockList()->isNil())
	      return 0;
	    PrologValue sub1(term1->getSubstitutionBlockList());
	    PrologValue sub2(term2->getSubstitutionBlockList());
	    return compareTerms(&sub1, &sub2);
	  }
	break;
      }

    case CrossTag(Object::TypeQuant, Object::TypeQuant):
      {
	QuantifiedTerm* str1 = OBJECT_CAST(QuantifiedTerm*, val1);
	QuantifiedTerm* str2 = OBJECT_CAST(QuantifiedTerm*, val2);
	Object* sub1 = term1->getSubstitutionBlockList();
	Object* sub2 = term2->getSubstitutionBlockList();
	PrologValue quant1(sub1, str1->getQuantifier()->variableDereference());
	PrologValue quant2(sub2, str2->getQuantifier()->variableDereference());
	heap.prologValueDereference(quant1);
	heap.prologValueDereference(quant2);
	int res = compareTerms(&quant1, &quant2);
	if (res != 0) return res;
	PrologValue body1(sub1, str1->getBody()->variableDereference());
	PrologValue body2(sub2, str2->getBody()->variableDereference());
	heap.prologValueDereference(body1);
	heap.prologValueDereference(body2);
	return compareTerms(&quant1, &quant2);
	break;
      }

    }
  return 1;
}

// object1 @< object2
Thread::ReturnValue
Thread::psi_term_less_than(Object *& object1, Object *& object2)
{
  Object* term1 = object1->variableDereference();
  Object* term2 = object2->variableDereference();
  PrologValue pterm1(term1);
  PrologValue pterm2(term2);
  heap.prologValueDereference(pterm1);
  heap.prologValueDereference(pterm2);

  int res = compareTerms(&pterm1, &pterm2);
  return(BOOL_TO_RV(res == -1)); 
}

// object1 @= object2
Thread::ReturnValue
Thread::psi_term_at_equal(Object *& object1, Object *& object2)
{
  Object* term1 = object1->variableDereference();
  Object* term2 = object2->variableDereference();
  PrologValue pterm1(term1);
  PrologValue pterm2(term2);
  heap.prologValueDereference(pterm1);
  heap.prologValueDereference(pterm2);

  int res = compareTerms(&pterm1, &pterm2);
  return(BOOL_TO_RV(res == 0)); 
}

// object1 @> object2
Thread::ReturnValue
Thread::psi_term_greater_than(Object *& object1, Object *& object2)
{
  Object* term1 = object1->variableDereference();
  Object* term2 = object2->variableDereference();
  PrologValue pterm1(term1);
  PrologValue pterm2(term2);
  heap.prologValueDereference(pterm1);
  heap.prologValueDereference(pterm2);

  int res = compareTerms(&pterm1, &pterm2);
  return(BOOL_TO_RV(res == 1)); 
}
