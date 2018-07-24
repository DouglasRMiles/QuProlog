// collect.cc -
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
// $Id: collect.cc,v 1.5 2006/01/31 23:17:49 qp Exp $

#include "heap_qp.h"

//
// Collect all (ob)vars from sub into varlist
//
void
Heap::collect_sub_vars(Object* sub, Object*& varlist)
{
  assert(sub->isCons());

  Object* sublist = sub;

  while (sublist->isCons())
    {
      assert(OBJECT_CAST(Cons*, sublist)->getHead()->isSubstitutionBlock());
      SubstitutionBlock* subblock
	= OBJECT_CAST(SubstitutionBlock*, 
		      OBJECT_CAST(Cons*, sublist)->getHead());
      u_int size = static_cast<u_int>(subblock->getSize());

      for (u_int i = 1; i <= size; i++)
	{
	  collect_term_vars(subblock->getRange(i), varlist);
	  collect_term_vars(subblock->getDomain(i), varlist);
	}
      sublist = OBJECT_CAST(Cons*, sublist)->getTail();
    }
  return;
}

//
// Collect all (ob)vars from term into varlist
//
void
Heap::collect_term_vars(Object* term, Object*& varlist)
{
  assert(term->variableDereference()->hasLegalSub());
  term = dereference(term);

  switch (term->tTag())
    {
    case Object::tVar:
    case Object::tObjVar:
      if (!OBJECT_CAST(Reference*, term)->isCollected() &&
	  !term->isLocalObjectVariable())
	{
	  OBJECT_CAST(Reference*, term)->setCollectedFlag();
	  Cons* newlist = newCons(term, varlist);
	  varlist = newlist;
	}
      break;
    case Object::tCons:
      while (term->isCons())
	{
	  collect_term_vars(OBJECT_CAST(Cons*, term)->getHead(), varlist);
  assert(OBJECT_CAST(Cons*, term)->getTail()->variableDereference()->hasLegalSub());
	  term = dereference(OBJECT_CAST(Cons*, term)->getTail());
	}
      collect_term_vars(term, varlist);
      break;
    case Object::tStruct:
      {
	Structure* str = OBJECT_CAST(Structure*, term);
	u_int arity = static_cast<u_int>(str->getArity());
	collect_term_vars(str->getFunctor(), varlist);
	for (u_int i = 1; i <= arity; i++)
	  {
	    collect_term_vars(str->getArgument(i), varlist);
	  }
      }
      break;
    case Object::tQuant:
      {
	QuantifiedTerm* quant = OBJECT_CAST(QuantifiedTerm*, term);
	collect_term_vars(quant->getQuantifier(), varlist);
	collect_term_vars(quant->getBoundVars(), varlist);
	collect_term_vars(quant->getBody(), varlist);
      } 
     break;
    case Object::tShort:
    case Object::tLong:
    case Object::tDouble:
    case Object::tAtom:
    case Object::tString:
      break;
    case Object::tSubst:
      collect_sub_vars(OBJECT_CAST(Substitution*, term)->getSubstitutionBlockList(), varlist);
      collect_term_vars(OBJECT_CAST(Substitution*, term)->getTerm(), varlist);
      break;
    default:
      assert(false);
      break;
    }
  return;
}

//
// Reset collected flag on all variables in list.
//
void
Heap::resetCollectedVarList(Object* varlist)
{
  while (varlist->isCons())
    {
      Object* head = OBJECT_CAST(Cons*, varlist)->getHead();
      assert(head->isAnyVariable());
      assert(OBJECT_CAST(Reference*, head)->isCollected());
      OBJECT_CAST(Reference*, head)->unsetCollectedFlag();
      varlist = OBJECT_CAST(Cons*, varlist)->getTail();
    }
  assert(varlist->isNil());
  return;
}








