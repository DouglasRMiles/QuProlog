// occurs_check.cc - 	Performing occurs check.
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
// $Id: occurs_check.cc,v 1.9 2006/02/06 00:51:38 qp Exp $

#include "atom_table.h"
#include "thread_qp.h" 
#include "truth3.h"

// 
// Do OC on sub and produce a simplified sub.
//
truth3
Thread::occursCheckSubAndSimplify(const CheckType type,
				  Object *sub_block_list,
				  Object*& simp_list, Object* var)
{
  assert(sub_block_list != NULL);
  assert(sub_block_list->isNil() ||
	       (sub_block_list->isCons() && 
		OBJECT_CAST(Cons *, 
			    sub_block_list)->isSubstitutionBlockList()));
  simp_list = heap.copySubSpine(sub_block_list, 
				AtomTable::nil, AtomTable::nil) ;
  Object* new_sub_block_list = simp_list;
  
  for (Object *list = sub_block_list;
       list->isCons();
       list = OBJECT_CAST(Cons *, list)->getTail(),
	 new_sub_block_list = 
	 OBJECT_CAST(Cons *, new_sub_block_list)->getTail())
    {
      assert(OBJECT_CAST(Cons *, list)->getHead()->isSubstitutionBlock());
      
      SubstitutionBlock *sub_block = 
	OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, list)->getHead());
      SubstitutionBlock *new_sub_block = 
	heap.newSubstitutionBlock(sub_block->getSize());
      if (sub_block->isInvertible())
	{
	  new_sub_block->makeInvertible();
	}
      for (size_t i = 1; i <= sub_block->getSize(); i++)
	{
	  PrologValue t(sub_block->getRange(i));
	  Object* newt;
	  if (occursCheckAndSimplify(type, t, newt, var) != false)
	    {
#ifdef QP_DEBUG
for (size_t j = i; j <= sub_block->getSize(); j++)
{
  new_sub_block->setDomain(i, sub_block->getDomain(i));
  new_sub_block->setRange(i, sub_block->getRange(i));
}
#endif // QP_DEBUG
	      return(truth3::UNSURE);
	    }
	  new_sub_block->setDomain(i, sub_block->getDomain(i));
	  new_sub_block->setRange(i, newt);
	}
      OBJECT_CAST(Cons*, new_sub_block_list)->setHead(new_sub_block);
    }
  return false;
}


//
// Do a simple OC on the substitution block.
//
bool
Thread::simpleOccursCheckSub(Object* subblock, Object* var) 
{
  assert(subblock->isSubstitutionBlock());
  SubstitutionBlock *sub = OBJECT_CAST(SubstitutionBlock*, subblock);
  for (size_t i = 1; i <= sub->getSize(); i++)
    {
      if (simpleOccursCheck(sub->getRange(i), var) != false)
	{
	  return true;
	}
    }
  return false;
}

//
// A simplified occurs check that looks for any occurrence of the supplied
// variable.
//
truth3
Thread::simpleOccursCheck(Object* term, Object* var)
{
  assert(var == var->variableDereference());
  assert(var->isVariable());

  Object* t = term->variableDereference();

  switch (t->tTag())
    {
    case Object::tShort:
    case Object::tLong:
    case Object::tDouble:
    case Object::tAtom:
    case Object::tString:
      return false;
      break;
    case Object::tVar:
      return (var == t);
      break;
    case Object::tObjVar:
      return false;
      break;
    case Object::tStruct:
      {
	Structure* s = OBJECT_CAST(Structure*, t);
	truth3 flag = false;
	for (size_t i = 0; i <= s->getArity(); i++)
	  {
	    truth3 f = simpleOccursCheck(s->getArgument(i), var);
	    if (f == true)
	      {
		return true;
	      }
            flag = flag || f;
	  }
	return flag;
      }
      break;
    case Object::tCons:
      {
	truth3 flag = false;
	for ( ; t->isCons(); 
	      t = OBJECT_CAST(Cons*, t)->getTail()->variableDereference())
	  {
	    truth3 f = simpleOccursCheck(OBJECT_CAST(Cons*, t)->getHead(), var);
	    if (f == true)
	      {
		return true;
	      }
	    flag = flag || f;
	  }
	return (simpleOccursCheck(t, var) || flag);
      }
      break;
    case Object::tQuant:
      {
	QuantifiedTerm* q = OBJECT_CAST(QuantifiedTerm*, t);
	return ( simpleOccursCheck(q->getBody(), var) ||
		 simpleOccursCheck(q->getBoundVars(), var) ||
		 simpleOccursCheck(q->getQuantifier(), var));
      }
      break;
    case Object::tSubst:
      {
	Substitution* s = OBJECT_CAST(Substitution*, t);
	truth3 flag = simpleOccursCheck(s->getTerm(), var);
	if (flag != false)
	  {
	    return flag;
	  }
	Object* sub = s->getSubstitutionBlockList();
	for ( ; sub->isCons(); sub = OBJECT_CAST(Cons*, sub)->getTail())
	  {
	    assert(sub == sub->variableDereference());
	    if (simpleOccursCheckSub(OBJECT_CAST(Cons*, sub)->getHead(), var)
		!= false)
	      {
		return truth3::UNSURE;
	      }
	  }
	assert(sub->isNil());
	return false;
      }
      break;
    default:
      assert(false);
      return false;
    }
}

//
// A "full" occurs check with the term simplified (if check succeeds).
//
truth3
Thread::occursCheckAndSimplify(const CheckType type, 
			       PrologValue& term, Object*& simpterm, 
			       Object* var)
{
  PrologValue tmpterm(term.getSubstitutionBlockList(), term.getTerm());
  heap.prologValueDereference(tmpterm);
  switch (tmpterm.getTerm()->tTag())
    {
    case Object::tShort:
    case Object::tLong:
    case Object::tDouble:
    case Object::tAtom:
    case Object::tString:
      simpterm = tmpterm.getTerm();
      return false;
      break;
    case Object::tStruct:
      {
	Structure* s = OBJECT_CAST(Structure*, tmpterm.getTerm());
	assert(s->getArity() <= MaxArity);
	Structure* news = heap.newStructure(s->getArity());
	truth3 flag = false;
	for (size_t i = 0; i <= s->getArity(); i++)
	  {
	    PrologValue t(tmpterm.getSubstitutionBlockList(), s->getArgument(i));
	    Object* arg;
	    truth3 f = occursCheckAndSimplify(type, t, arg, var);
	    if (f == true)
	      {
		return true;
	      }
	    flag = flag || f;
	    news->setArgument(i, arg);
	  }
	simpterm = news;
	return flag;
      }
      break;
    case Object::tCons:
      {
	Cons* c = OBJECT_CAST(Cons*, tmpterm.getTerm());
	Object* head;
	Object* tail;
	PrologValue h(tmpterm.getSubstitutionBlockList(), c->getHead());
	PrologValue t(tmpterm.getSubstitutionBlockList(), c->getTail());
	truth3 flag = 
	  occursCheckAndSimplify(type, h, head, var) ||
	  occursCheckAndSimplify(type, t, tail, var);
	simpterm = heap.newCons(head, tail);
	return flag;
      }
      break;
    case Object::tVar:
      if (var == tmpterm.getTerm())
	{
	  return true;
	}
      else if (type == DIRECT)
	{
	  if (tmpterm.getSubstitutionBlockList()->isCons())
	    {
	      heap.dropSubFromTerm(*this, tmpterm);
	    }
	  simpterm = heap.prologValueToObject(tmpterm);
	  return false;
	}
      else
	{
	  if (tmpterm.getSubstitutionBlockList()->isCons())
	    {
	      heap.dropSubFromTerm(*this, tmpterm);
	    }
	  if (tmpterm.getSubstitutionBlockList()->isNil())
	    {
	      simpterm = tmpterm.getTerm();
	      return false;
	    }
	  Object* simpsub;
	  truth3 flag = 
	    occursCheckSubAndSimplify(type, 
				      tmpterm.getSubstitutionBlockList(),
				      simpsub, var);
          assert(simpsub->isCons());
	  simpterm = heap.newSubstitution(simpsub, tmpterm.getTerm());
	  return flag;
	}
      break;
    case Object::tObjVar:
      if (type == DIRECT) 
	{
	  if (tmpterm.getSubstitutionBlockList()->isCons())
	    {
	      heap.dropSubFromTerm(*this, tmpterm);
	    }
	  simpterm = heap.prologValueToObject(tmpterm);
	  return false;
	}
      else
	{
	  if (tmpterm.getSubstitutionBlockList()->isCons())
	    {
	      heap.dropSubFromTerm(*this, tmpterm);
	    }
	  if (tmpterm.getSubstitutionBlockList()->isNil())
	    {
	      simpterm = tmpterm.getTerm();
	      return false;
	    }
	  Object* simpsub;
	  truth3 flag = 
	    occursCheckSubAndSimplify(type, 
				      tmpterm.getSubstitutionBlockList(),
				      simpsub, var);
          assert(simpsub->isCons());
	  simpterm = heap.newSubstitution(simpsub, tmpterm.getTerm());
	  return flag;
	}
      break;
    case Object::tQuant:
      {
	QuantifiedTerm* q = OBJECT_CAST(QuantifiedTerm*, tmpterm.getTerm());
	PrologValue pvq(q->getQuantifier());
	PrologValue pvv(q->getBoundVars());
	PrologValue pvb(q->getBody());
	Object* newquant;
	Object* newbv;
	Object* newbody;
	
	truth3 flag = 
	  occursCheckAndSimplify(type, pvq, newquant, var) ||
	  occursCheckAndSimplify(type, pvv, newbv, var) ||
	  occursCheckAndSimplify(type, pvb, newbody, var);
	QuantifiedTerm* newt = heap.newQuantifiedTerm();
	newt->setQuantifier(newquant);
	newt->setBoundVars(newbv);
	newt->setBody(newbody);
	
	if (flag == false)
	  {
	    if (tmpterm.getSubstitutionBlockList()->isCons())
	      {
		heap.dropSubFromTerm(*this, tmpterm);
	      }
	    if (tmpterm.getSubstitutionBlockList()->isNil())
	      {
		simpterm = tmpterm.getTerm();
		return false;
	      }
	    Object* simpsub;
	    flag = 
	      occursCheckSubAndSimplify(type, 
					tmpterm.getSubstitutionBlockList(),
					simpsub, var);
            assert(simpsub->isCons());
	    simpterm = heap.newSubstitution(simpsub, newt);
	  }
	return flag; 
      }
    default:
      assert(false);
      return true;
    }
}




