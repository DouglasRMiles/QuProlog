// sub_escape.cc - Routines for manipulating substitution and its term.
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
// $Id: sub_escape.cc,v 1.8 2006/01/31 23:17:51 qp Exp $

#include "thread_qp.h"

//
// psi_sub(term)
// Succeeds if the term has a substitution.
// mode(in)
//
Thread::ReturnValue
Thread::psi_sub(Object *& object1)
{
  Object* val = object1->variableDereference();
  if (!val->isSubstitution())
    {
      return RV_FAIL;
    }
  assert(val->hasLegalSub());
  PrologValue pval1(val);
  heap.prologValueDereference(pval1);

  if (pval1.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, pval1);
    }

  return BOOL_TO_RV(!pval1.getSubstitutionBlockList()->isNil());
}

//
// psi_get_substitution(term, sub)
// Return the substitution of the term.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_get_substitution(Object *& object1, Object *& object2)
{
  assert(object1->hasLegalSub());
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);

  assert(pval1.getSubstitutionBlockList()->isLegalSub());
  if (pval1.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, pval1);
    }

  object2 = pval1.getSubstitutionBlockList();

  return RV_SUCCESS;
}

//
// psi_sub_term(term, term)
// Return the term without its substitution.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_sub_term(Object *& object1, Object *& object2)
{
  assert(object1->hasLegalSub());
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);

  object2 = pval1.getTerm();

  return RV_SUCCESS;
}

//
// psi_build_sub_term(sub, term, sub_term)
// Join a substitution and a term together to form a new term.
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_build_sub_term(Object *& object1, Object *& object2, Object *& object3)
{
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  if (val1->isNil())
    {
      object3 = val2;
    }
  else if (val1->isCons())
    {
      object3 = heap.newSubstitution(val1, val2);
    }
  else
    {
      assert(false);
    }
  
  return RV_SUCCESS;
}

//
// psi_empty_sub(empty_sub)
// Return the representation of an empty substitution - i.e. [].
// mode(out)
// 
Thread::ReturnValue
Thread::psi_empty_sub(Object *& object1)
{
  object1 = AtomTable::nil;

  return RV_SUCCESS;
}

//
// psi_new_sub(size, existing_sub, sublist, new_sub)
// Create a new empty substitution block of a given size and link it with
// existing substitutions.
// mode(in, in, in, out)
//
Thread::ReturnValue
Thread::psi_new_sub(Object *& object1,
                         Object *& object2,
                         Object *& object3,
                         Object *& object4)
{
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);
  Object* val3 = heap.dereference(object3);

  assert(val1->isShort());
  assert(0 <= val1->getInteger() &&
               (u_int)(val1->getInteger()) <= ARITY_MAX);
  assert(val2->isNil() ||(val2->isCons() && OBJECT_CAST(Cons*, val2)->isSubstitutionBlockList()));

  assert(val3->isCons());
  //
  // Link the new substitution to the existing substitutions.
  //
  int size = val1->getInteger();
  SubstitutionBlock* new_block = 
    heap.newSubstitutionBlock(size);

  Object* list = val3;
  for (int i = size; i != 0; i--)
    {
      assert(list->isCons());
      Object* entry = OBJECT_CAST(Cons*, list)->getHead()->variableDereference();
      list = OBJECT_CAST(Cons*, list)->getTail()->variableDereference();
      if (!entry->isStructure())
	{
	  return RV_FAIL;
	}
      Structure* entry_struct = OBJECT_CAST(Structure*, entry);
      if (entry_struct->getArity() != 2 || entry_struct->getFunctor()->variableDereference() != AtomTable::divide)
	{
	  return RV_FAIL;
	}
      Object* dom = entry_struct->getArgument(2)->variableDereference();
      if (!dom->isObjectVariable())
	{
	  return RV_FAIL;
	}
      new_block->setDomain(i, dom);
      new_block->setRange(i, entry_struct->getArgument(1)->variableDereference());
    }
  object4 =
    heap.newSubstitutionBlockList(new_block, val2);

  return RV_SUCCESS;
}

//
// psi_next_sub(subptr0, subptr1)
// Return the next substitution from subptr0.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_next_sub(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  
  assert(val1->isCons());

  Cons* list = OBJECT_CAST(Cons*, val1);

  assert(list->isSubstitutionBlockList());

  object2 = list->getTail();

  return RV_SUCCESS;
}

//
// psi_sub_table_size(subptr, size)
// Return the number of entries (size) in a substitution table.
// mode(in,out)
//
// XXX Assume that it's ok to think in terms of the sub block
// XXX at the head of a list that's been passed in. RAH 8 September 1999
Thread::ReturnValue
Thread::psi_sub_table_size(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  assert(val1->isCons());

  Cons *sub_block_list = OBJECT_CAST(Cons *, val1);

  assert(sub_block_list->getHead()->isSubstitutionBlock());

  SubstitutionBlock *sub_block = 
    OBJECT_CAST(SubstitutionBlock *, sub_block_list->getHead());

  //
  // Get the size and return it.
  //
  object2 = heap.newInteger(static_cast<qint64>(sub_block->getSize()));
  
  return RV_SUCCESS;
}

//
// psi_set_domain(position, sub, variable)
// Assign the variable to the domain of the specified position of the 
// substitution.
// mode(in,in,in)
//
Thread::ReturnValue
Thread::psi_set_domain(Object *& object1, Object *& object2, Object *& object3)
{
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  assert(object3->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2); 
  Object* val3 = heap.dereference(object3);

  assert(val1->isInteger());
  
  u_int index = (u_int)(val1->getInteger());

  assert(val2->isCons());

  Cons *sub_block_list = OBJECT_CAST(Cons *, val2);

  assert(sub_block_list->getHead()->isSubstitutionBlock());

  SubstitutionBlock *sub_block = 
    OBJECT_CAST(SubstitutionBlock *, sub_block_list->getHead());

  assert(1 <= index && index <= sub_block->getSize());

  assert(val3->isObjectVariable());

  sub_block->setDomain(index, val3);

  return RV_SUCCESS;
}

//
// psi_set_range(position, sub, term)
// Assign the term to the range of the specified position of the substitution.
// mode(in,in,in)
//
Thread::ReturnValue
Thread::psi_set_range(Object *& object1, Object *& object2, Object *& object3)
{
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  assert(object3->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2); 
  Object* val3 = heap.dereference(object3);

  assert(val1->isInteger());
  
  u_int index = (u_int)(val1->getInteger());

  assert(val2->isCons());

  Cons *sub_block_list = OBJECT_CAST(Cons *, val2);

  assert(sub_block_list->getHead()->isSubstitutionBlock());

  SubstitutionBlock *sub_block = 
    OBJECT_CAST(SubstitutionBlock *, sub_block_list->getHead());

  assert(1 <= index && index <= sub_block->getSize());

  //
  // Assign the term into the specified range.
  //
  sub_block->setRange(index, val3);

  return RV_SUCCESS;
}

//
// psi_get_domain(position, sub, variable)
// Return the domain object variable at the specified position of a
// substitution.
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_get_domain(Object *& object1, Object *& object2, Object *& object3)
{
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2); 

  assert(val1->isInteger());
  
  u_int index = (u_int)(val1->getInteger());

  assert(val2->isCons());

  Cons *sub_block_list = OBJECT_CAST(Cons *, val2);

  assert(sub_block_list->getHead()->isSubstitutionBlock());

  SubstitutionBlock *sub_block = 
    OBJECT_CAST(SubstitutionBlock *, sub_block_list->getHead());

  // If the index is legal, do the right thing, otherwise fail.
  if (1 <= index && index <= sub_block->getSize())
    {
      object3 = sub_block->getDomain(index);
  
      return RV_SUCCESS;
    }
  else
    {
      return RV_FAIL;
    }
}

//
// psi_get_range(position, sub, term)
// Return the range at the specified position of a substitution.
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_get_range(Object *& object1, Object *& object2, Object *& object3)
{
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2); 

  assert(val1->isInteger());
  
  u_int index = (u_int)(val1->getInteger());

  assert(val2->isCons());

  Cons *sub_block_list = OBJECT_CAST(Cons *, val2);

  assert(sub_block_list->getHead()->isSubstitutionBlock());

  SubstitutionBlock *sub_block = 
    OBJECT_CAST(SubstitutionBlock *, sub_block_list->getHead());

  // If the index is legal, do the right thing, otherwise fail.
  if (1 <= index && index <= sub_block->getSize())
    {
      object3 = sub_block->getRange(index);
  
      return RV_SUCCESS;
    }
  else
    {
      return RV_FAIL;
    }
}


//
// psi_compress_sub_object_variable(T, CompressesT)
// Make a call on dropSub to compress sub.  This is used as a special case
// in $equal_ObjectVariable3/3 to force a dropSubFromTerm so that 
// the $equal_ObjectVariable3/3 terminates.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_compress_sub_object_variable(Object *& object1, Object *& object2)

{
  assert(object1->hasLegalSub());
  PrologValue pval1(object1);

  heap.prologValueDereference(pval1);
  assert(pval1.getTerm()->isObjectVariable());
  
  if (pval1.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, pval1);
    }

  object2 = heap.prologValueToObject(pval1);

  return RV_SUCCESS;
}

//
// Copy the substitution part of a term - leaving the term part unchanged.
// Used when a desctructive update of the substitution is required.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_copy_substitution(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->isSubstitution());
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);
  
  assert(pval1.getSubstitutionBlockList()->isCons());

  Object* newsub;
  Object** newsubptr = &newsub;
  Object* sub = pval1.getSubstitutionBlockList();
  for( ; sub->isCons() ; sub = OBJECT_CAST(Cons *, sub)->getTail())
    {
      assert(OBJECT_CAST(Cons *, sub)->getHead()->isSubstitutionBlock());
      SubstitutionBlock* block =
	heap.copySubstitutionBlock(OBJECT_CAST(SubstitutionBlock*, OBJECT_CAST(Cons *, sub)->getHead()));

      *newsubptr = heap.newCons();
      OBJECT_CAST(Cons *, *newsubptr)->makeSubstitutionBlockList();
      OBJECT_CAST(Cons *, *newsubptr)->setHead(block);
      newsubptr = OBJECT_CAST(Cons *, *newsubptr)->getTailAddress();
    }
  assert(sub->isNil());
  *newsubptr = AtomTable::nil;
  assert(newsub->isCons());
  object2 = heap.newSubstitution(newsub, pval1.getTerm());
  return RV_SUCCESS;
}


//
// Test if the term has a substitution and that the sub is a single sub.
// NOTE - dropSub should not be used.
// mode(in)
//
Thread::ReturnValue
Thread::psi_single_sub(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* t = heap.dereference(object1);

  if (!t->isSubstitution())
    {
      return RV_FAIL;
    }

  assert(OBJECT_CAST(Substitution*, t)->getSubstitutionBlockList()->isCons());

  Object* sub = OBJECT_CAST(Substitution*, t)->getSubstitutionBlockList();
  if (OBJECT_CAST(Cons *, sub)->getTail()->isNil())
    {
      return RV_SUCCESS;
    }
  else
    { 
      return RV_FAIL; 
    } 
}


//
// Return true if the term needs to be simplified for nfi testing.
// The term should be of the form s*X where X is any variable and
// s is non-empty and not of the form [$/x] where x is the same or
// different from the obvar in the first arg.
//
Thread::ReturnValue
Thread::psi_require_nfi_simp(Object *& object1, Object *& object2)
{
  Object* obvar = object1->variableDereference();
  assert(obvar->isObjectVariable());

  assert(object2->hasLegalSub());
  PrologValue term(object2);
  heap.prologValueDereference(term);
  if (!term.getTerm()->isAnyVariable())
    {
      return RV_SUCCESS;
    }

  if (term.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, term);
    }

  if (!term.getSubstitutionBlockList()->isCons())
    {
      return RV_FAIL;
    }

  Cons* sub = OBJECT_CAST(Cons*, term.getSubstitutionBlockList());
  
  if (!sub->getTail()->isNil())
    {
      return RV_SUCCESS;
    }

  assert(sub->getHead()->isSubstitutionBlock());
  SubstitutionBlock *sub_block =
    OBJECT_CAST(SubstitutionBlock *, sub->getHead()); 

  if (sub_block->getSize() != 1 ||
      sub_block->getRange(1) != AtomTable::dollar)
    {
      return RV_SUCCESS;
    }
  
  Object* dom = sub_block->getDomain(1)->variableDereference();  
  return BOOL_TO_RV(dom == obvar || dom->distinctFrom(obvar));   
}

//
// psi_set_domains_apart(ObjVar, Sub, Pos, SubPos) makes
// ObjVar differnet from all the domain elelents in Sub up to
// but not including domain position Pos in SubPos.
//
Thread::ReturnValue
Thread::psi_set_domains_apart(Object *& object1, Object *& object2,
                              Object *& object3, Object *& object4)
{
   Object* ov = object1->variableDereference();
   assert(ov->isObjectVariable());
   Object* sub = object2->variableDereference();
   assert(sub->isNil() ||
                OBJECT_CAST(Cons*, sub)->isSubstitutionBlockList());
   Object* pos = object3->variableDereference();
   assert(pos->isInteger());
   int dompos = pos->getInteger();
   Object* subpos = object4->variableDereference();
   assert(OBJECT_CAST(Cons*, subpos)->isSubstitutionBlockList() ||
                ((dompos == 1) && subpos->isNil()));

   ObjectVariable* objvar = OBJECT_CAST(ObjectVariable*, ov);
   for ( ; sub->isCons() ; sub = OBJECT_CAST(Cons*, sub)->getTail())
     {
       assert(OBJECT_CAST(Cons*, sub)->getHead()->isSubstitutionBlock());
       SubstitutionBlock* subblock = OBJECT_CAST(SubstitutionBlock*, OBJECT_CAST(Cons*, sub)->getHead());

       if (sub == subpos)
         {
           assert(dompos <= (int)(subblock->getSize()));
           for (int i = 1; i < dompos; i++)
             {
                Object* dom = subblock->getDomain(i)->variableDereference();
                assert(dom->isObjectVariable());
                if (dom == objvar)
                  {
                    return RV_FAIL;
                  }
                else if (!objvar->distinctFrom(OBJECT_CAST(ObjectVariable*, dom)))
                  {
                    setDistinct(objvar, OBJECT_CAST(ObjectVariable*, dom));
                  }
             } 
           break;
         }
       else
         {
           for (size_t i = 1; i <= subblock->getSize(); i++)
             {
                Object* dom = subblock->getDomain(i)->variableDereference();
          
		assert(dom->isObjectVariable());
                assert(objvar == objvar->variableDereference());
		if (dom == objvar)
                  {
                    return RV_FAIL;
                  }
                else if (!objvar->distinctFrom(OBJECT_CAST(ObjectVariable*, dom)))
                  {
                    setDistinct(objvar, OBJECT_CAST(ObjectVariable*, dom));
                  }
             } 
         }
     }
   assert(sub == subpos);
   return RV_SUCCESS;
}
