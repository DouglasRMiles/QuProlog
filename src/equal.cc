// equal.cc - 
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
// $Id: equal.cc,v 1.10 2006/01/31 23:17:50 qp Exp $

// #include "atom_table.h"
#include "heap_qp.h"
#include "thread_qp.h"
#include "truth3.h"
extern AtomTable *atoms;


//
// C-level implementation of ==
// Assumes terms have been dereferenced
//
// 

bool 
Thread::equalEqual(PrologValue& term1, PrologValue& term2, int& counter)

#ifdef OBJECT_OVERRIDES
{
  Object* o1 = term1.getTerm();
  Object* o2 = term2.getTerm();
  
  bool* result = new bool();
  if(o1->StrictEquals(o2, *result)) {
    return *result;
  }
  if(o2->StrictEquals(o1, *result)) {
    return *result;
  }

  return equalEqual_Original(term1, term2, counter);
}

bool
Object::OverridesStrictEquals(Object* o2, bool &result) 
{
  result = false;
  return false;
}


bool 
Thread::equalEqual_Original(PrologValue& term1, PrologValue& term2, int& counter)
#endif

{
  assert(quick_tidy_check);
  if (term1.getTerm()->tTag() != term2.getTerm()->tTag())
    {
      // different types
      return false;
    }

  if (term1.getTerm() == term2.getTerm() &&
      term1.getSubstitutionBlockList() == term2.getSubstitutionBlockList())
    {
      // identical pointers
      return true;
    }

  assert(term1.getTerm()->tTag() == term2.getTerm()->tTag());
  switch (term1.getTerm()->tTag())
    {
    case Object::tShort:
      return term1.getTerm()->getTag() == term2.getTerm()->getTag();
      break;
    case Object::tLong:
    case Object::tDouble:
    case Object::tString:
      return (term1.getTerm()->equalUninterp(term2.getTerm()));
      break;
    case Object::tAtom:
      return false;
      break;
    case Object::tCons:
      {
	Cons* list1 = OBJECT_CAST(Cons*, term1.getTerm());
	Cons* list2 = OBJECT_CAST(Cons*, term2.getTerm());
	PrologValue head1(term1.getSubstitutionBlockList(), list1->getHead());
	PrologValue head2(term2.getSubstitutionBlockList(), list2->getHead());
	heap.prologValueDereference(head1);
	heap.prologValueDereference(head2);
	if (!equalEqual(head1, head2, counter))
	  {
	    return false;
	  }
	PrologValue tail1(term1.getSubstitutionBlockList(), list1->getTail());
	PrologValue tail2(term2.getSubstitutionBlockList(), list2->getTail());
	heap.prologValueDereference(tail1);
	heap.prologValueDereference(tail2);
	return (equalEqual(tail1, tail2, counter));
	break;
      }
    case Object::tStruct:
      {
	Structure* struct1 = OBJECT_CAST(Structure*, term1.getTerm());
	Structure* struct2 = OBJECT_CAST(Structure*, term2.getTerm());
	if (struct1->getArity() != struct2->getArity())
	  {
	    return false;
	  }
	for (u_int i = 0; i <= struct1->getArity(); i++)
	  {
	    PrologValue arg1(term1.getSubstitutionBlockList(), 
			     struct1->getArgument(i));
	    PrologValue arg2(term2.getSubstitutionBlockList(), 
			     struct2->getArgument(i));
	   
	    heap.prologValueDereference(arg1);
	    heap.prologValueDereference(arg2);
	    if (!equalEqual(arg1, arg2, counter))
	      {
		return false;
	      }
	  }
	return true;
	break;
      }
    case Object::tQuant:
      {
	QuantifiedTerm* quant1 = OBJECT_CAST(QuantifiedTerm*, term1.getTerm());
	QuantifiedTerm* quant2 = OBJECT_CAST(QuantifiedTerm*, term2.getTerm());
	PrologValue q1(term1.getSubstitutionBlockList(), 
		       quant1->getQuantifier());
	PrologValue q2(term2.getSubstitutionBlockList(), 
		       quant2->getQuantifier());
	heap.prologValueDereference(q1);
	heap.prologValueDereference(q2);
	if (!equalEqual(q1, q2, counter))
	  {
	    return false;
	  }
	int old_size = pushDownStack.size();

	Object* boundvars1 = quant1->getBoundVars();
	Object* boundvars2 = quant2->getBoundVars();
	for (boundvars1 = boundvars1->variableDereference(),
	       boundvars2 = boundvars2->variableDereference();
	     boundvars1->isCons() && boundvars2->isCons() ;
	     boundvars1 = OBJECT_CAST(Cons*, boundvars1)->getTail()->variableDereference(),
	       boundvars2 = OBJECT_CAST(Cons*, boundvars2)->getTail()->variableDereference())
	  {
	    Object* head1 = OBJECT_CAST(Cons*, boundvars1)->getHead()->variableDereference();
	    Object* head2 = OBJECT_CAST(Cons*, boundvars2)->getHead()->variableDereference();
	    
	    if (head1->isObjectVariable() && head2->isObjectVariable())
	      {
		pushDownStack.push(head1);
		pushDownStack.push(head2);
	      }    
	    else if (head1->isStructure() && head2->isStructure())
	      {
		assert(OBJECT_CAST(Structure*, head1)->getFunctor()
			     == AtomTable::colon);
		assert(OBJECT_CAST(Structure*, head1)->getArity() == 2);
		assert(OBJECT_CAST(Structure*, head2)->getFunctor()
			     == AtomTable::colon);
		assert(OBJECT_CAST(Structure*, head1)->getArity() == 2);
		
		pushDownStack.push(OBJECT_CAST(Structure*, head1)->getArgument(1)->variableDereference());
		pushDownStack.push(OBJECT_CAST(Structure*, head2)->getArgument(1)->variableDereference());
		PrologValue t1(term1.getSubstitutionBlockList(),
				OBJECT_CAST(Structure*, head1)->getArgument(2));
		PrologValue t2(term2.getSubstitutionBlockList(),
			       OBJECT_CAST(Structure*, head2)->getArgument(2));
		heap.prologValueDereference(t1);
		heap.prologValueDereference(t2);
		if (!equalEqual(t1, t2, counter))
		  {
		    pushDownStack.popNEntries(pushDownStack.size() - old_size);
		    return false;
		  }
	      }
	    else
	      {
		pushDownStack.popNEntries(pushDownStack.size() - old_size);
		return false;
	      }
	  }
	if (boundvars1 != boundvars2)
	  {
	    pushDownStack.popNEntries(pushDownStack.size() - old_size);
	    return false;
	  }
	size_t n = (pushDownStack.size() - old_size)/2;
	if (n == 0)
	  {
	    PrologValue body1(term1.getSubstitutionBlockList(), 
			      quant1->getBody());
	    PrologValue body2(term2.getSubstitutionBlockList(), 
			      quant2->getBody());
	    heap.prologValueDereference(body1);
	    heap.prologValueDereference(body2);
	    return (equalEqual(body1, body2, counter));
	  }
	// Non-empty binding list
	SubstitutionBlock* block1 = heap.newSubstitutionBlock(n);
	SubstitutionBlock* block2 = heap.newSubstitutionBlock(n);
	for (size_t i = 1; i <= n; )
	  {
	    Object* o2 = pushDownStack.pop()->variableDereference();
	    Object* o1 = pushDownStack.pop()->variableDereference();
	    Structure* ranstruct = heap.newStructure(1);
	    ranstruct->setFunctor(atoms->add("$$quant"));
	    ranstruct->setArgument(1, heap.newInteger(counter++));
	    assert(o1->isObjectVariable());
	    assert(o2->isObjectVariable());
	    block2->setDomain(i, OBJECT_CAST(ObjectVariable*, o2));
	    block1->setDomain(i, OBJECT_CAST(ObjectVariable*, o1));
	    block1->setRange(i, ranstruct);
	    block2->setRange(i, ranstruct);
	    i++;     
	  }
	Object* subs1 = heap.newSubstitutionBlockList(block1, term1.getSubstitutionBlockList());
	Object* subs2 = heap.newSubstitutionBlockList(block2, term2.getSubstitutionBlockList());
	PrologValue body1(subs1, quant1->getBody());
	PrologValue body2(subs2, quant2->getBody());
	heap.prologValueDereference(body1);
	heap.prologValueDereference(body2);
	return (equalEqual(body1, body2, counter));
	break;
      }
    case Object::tVar:
      {
	if (term1.getTerm() != term2.getTerm())
	  {
	    return false;
	  }
	if (term1.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term1);
	  }
	if (term2.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term2);
	  }
	if (term1.getSubstitutionBlockList() 
	    == term2.getSubstitutionBlockList())
	  {
	    return true;
	  }
	// At this point we save the state for backtracking - at the end of 
	// test we reset the state.
	heapobject* savesavedtop = heap.getSavedTop();
	heapobject* savedHT = heap.getTop();
        TrailLoc savedBindingTrailTop = bindingTrail.getTop();
        TrailLoc savedOtherTrailTop = otherTrail.getTop();
	heap.setSavedTop(savedHT);

	bool result;
	Object* obvar = heap.newObjectVariable();
	bindAndTrail(term1.getTerm(), obvar);
	(void)retry_delays();
	PrologValue pt1(term1.getSubstitutionBlockList(), term1.getTerm());
	PrologValue pt2(term2.getSubstitutionBlockList(), term2.getTerm());
	heap.prologValueDereference(pt1);
	heap.prologValueDereference(pt2);
	result = equalEqual(pt1, pt2, counter);

	// Restore state
	heap.setTop(savedHT);
	heap.setSavedTop(savesavedtop);
	bindingTrail.backtrackTo(savedBindingTrailTop);
	assert(bindingTrail.check(heap));
	otherTrail.backtrackTo(savedOtherTrailTop);
	assert(otherTrail.check(heap));
	return result;
	break;
      }
    case Object::tObjVar:
      {
	if (term1.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term1);
	  }
	if (term2.getSubstitutionBlockList()->isCons())
	  {
	    heap.dropSubFromTerm(*this, term2);
	  }
	if (term1.getSubstitutionBlockList()->isNil() 
	    && term2.getSubstitutionBlockList()->isNil())
	  {
	    return (term1.getTerm() == term2.getTerm());
	  }
	Object* domain = NULL;
	Object* term;
	if (!term1.getSubstitutionBlockList()->isNil())
	  {
	    Cons *sub_block_list = 
	      OBJECT_CAST(Cons *, term1.getSubstitutionBlockList());
	    SubstitutionBlock *sub_block =
	      OBJECT_CAST(SubstitutionBlock *, sub_block_list->getHead());
	    assert(sub_block->getSize() > 0);
	    term = term1.getTerm();
	    size_t size = sub_block->getSize();
	    for (size_t i = 1; i <= size; i++)
	      {
		domain = sub_block->getDomain(i)->variableDereference();
		assert(term->isObjectVariable());
		if(!OBJECT_CAST(ObjectVariable*, domain)->distinctFrom(OBJECT_CAST(ObjectVariable*, term)))
		  {
		    break;
		  }
	      }
	  }
	else
	  {
	    assert(!term2.getSubstitutionBlockList()->isNil());
	    Cons *sub_block_list = 
	      OBJECT_CAST(Cons *, term2.getSubstitutionBlockList());
	    SubstitutionBlock *sub_block =
	      OBJECT_CAST(SubstitutionBlock *, sub_block_list->getHead());
	    assert(sub_block->getSize() > 0);
	    term = term2.getTerm();
	    size_t size = sub_block->getSize();
	    for (size_t i = 1; i <= size; i++)
	      {
		domain = sub_block->getDomain(i)->variableDereference();
		assert(term->isObjectVariable());
		if(!OBJECT_CAST(ObjectVariable*, domain)->distinctFrom(OBJECT_CAST(ObjectVariable*, term)))
		  {
		    break;
		  }
	      }
	  }
	// At this point we save the state for backtracking - at the end of 
	// test we reset the state.
	heapobject* savesavedtop = heap.getSavedTop();
	heapobject* savedHT = heap.getTop();
        TrailLoc savedBindingTrailTop = bindingTrail.getTop();
        TrailLoc savedOtherTrailTop = otherTrail.getTop();
	heap.setSavedTop(savedHT);
	bool result;
	bindAndTrail(term, domain);
	if (!retry_delays())
	  {
	    result = true;
	  }
	else
	  {
	    PrologValue pt1(term1.getSubstitutionBlockList(), term1.getTerm());
	    PrologValue pt2(term2.getSubstitutionBlockList(), term2.getTerm());
	    heap.prologValueDereference(pt1);
	    heap.prologValueDereference(pt2);
	    result = equalEqual(pt1, pt2, counter);
	  }

	// Restore state
	heap.setTop(savedHT);
	bindingTrail.backtrackTo(savedBindingTrailTop);
	assert(bindingTrail.check(heap));
	otherTrail.backtrackTo(savedOtherTrailTop);
	assert(otherTrail.check(heap));
	
	if (!result)
	  {
	    heap.setSavedTop(savesavedtop);
	    return false;
	  }
	assert(domain->isObjectVariable());
	assert(term->isObjectVariable());
	assert(domain == domain->variableDereference());
	assert(term->isObjectVariable());
	assert(!OBJECT_CAST(ObjectVariable*, domain)->distinctFrom(OBJECT_CAST(ObjectVariable*, term)));
	setDistinct(OBJECT_CAST(ObjectVariable*, domain),
		    OBJECT_CAST(ObjectVariable*, term));
	if (!retry_delays())
	  {
	    result = true;
	  }
	else
	  {
	    PrologValue pt1(term1.getSubstitutionBlockList(), term1.getTerm());
	    PrologValue pt2(term2.getSubstitutionBlockList(), term2.getTerm());
	    heap.prologValueDereference(pt1);
	    heap.prologValueDereference(pt2);
	    result = equalEqual(pt1, pt2, counter);
	  }
	// Restore state
	heap.setTop(savedHT);
	heap.setSavedTop(savesavedtop);
	bindingTrail.backtrackTo(savedBindingTrailTop);
	assert(bindingTrail.check(heap));
	otherTrail.backtrackTo(savedOtherTrailTop);       
	assert(otherTrail.check(heap));

	return result;
	break;
      }
    default:
      assert(false);
      return(false);   
    }
}

//
// C-level version of simplify_term
//

//
// Top-level - returns true iff some simplification was done.
//
bool
Thread::simplify_term(PrologValue& term, Object*& simpterm)
{
  assert(quick_tidy_check);
  heap.prologValueDereference(term);
  switch (term.getTerm()->tTag())
    {
    case Object::tShort:
    case Object::tLong:
    case Object::tDouble:
    case Object::tAtom:
    case Object::tString:
      {
	simpterm = term.getTerm();
	return false;
	break;
      }
    case Object::tCons:
      {
	PrologValue head(term.getSubstitutionBlockList(), OBJECT_CAST(Cons*, term.getTerm())->getHead());
	PrologValue tail(term.getSubstitutionBlockList(), OBJECT_CAST(Cons*, term.getTerm())->getTail());
	Object *simphead, *simptail;
	bool headsimplified = simplify_term(head, simphead);
	bool tailsimplified = simplify_term(tail, simptail);
	if (!term.getSubstitutionBlockList()->isNil()
	    || headsimplified || tailsimplified)
	  {
	    simpterm = heap.newCons(simphead, simptail);
	    return true;
	  }
	else
	  {
	    simpterm = term.getTerm();
	    return false;
	  }
	break;
      }
    case Object::tStruct:
      {
	Structure* termstruct = OBJECT_CAST(Structure*, term.getTerm());
	u_int arity = static_cast<u_int>(termstruct->getArity());
        Object** allargs = new Object*[arity+1];
	bool is_simplified = !term.getSubstitutionBlockList()->isNil();
	for (u_int i = 0; i <= arity; i++)
	  {
	    PrologValue arg(term.getSubstitutionBlockList(), 
			    termstruct->getArgument(i));
	    is_simplified = simplify_term(arg, allargs[i]) || is_simplified;
	  }
	if (is_simplified)
	  {
	assert(arity <= MaxArity);
	    Structure* newstruct = heap.newStructure(arity);
	    for (u_int i = 0; i <= arity; i++)
	      {
		newstruct->setArgument(i, allargs[i]);
	      }
	    simpterm = newstruct;
            delete allargs;
	    return true;
	  }
	else
	  {
	    simpterm = term.getTerm();
            delete allargs;
	    return false;
	  }
	break;
      }
    case Object::tQuant:
      {
	QuantifiedTerm* quant = 
	  OBJECT_CAST(QuantifiedTerm*, term.getTerm());
	bool is_simplified;
	Object *simpq, *simpbound, *simpbody, *simpquant;
	PrologValue q(quant->getQuantifier());
	PrologValue bv(quant->getBoundVars());
	PrologValue body(quant->getBody());
	is_simplified = simplify_term(q, simpq);
	is_simplified =  simplify_term(bv, simpbound) || is_simplified;
	is_simplified =  simplify_term(body, simpbody) || is_simplified;
	if (is_simplified)
	  {
	    QuantifiedTerm* newq = heap.newQuantifiedTerm();
	    newq->setQuantifier(simpq);
	    newq->setBoundVars(simpbound);
	    newq->setBody(simpbody);
	    simpquant = newq;
	  }
	else
	  {
	    simpquant = term.getTerm();
	  }
	if (term.getSubstitutionBlockList()->isNil())
	  {
	    simpterm = simpquant;
	    return is_simplified;
	  }
	else
	  {
	    PrologValue st(term.getSubstitutionBlockList(), simpquant);
	    return (simplify_sub_term(st, simpterm, AtomTable::success) 
		    || is_simplified);
	  }
	break;
      }
    case Object::tVar:
      {
	Object* savedsub = term.getSubstitutionBlockList();
	if (savedsub->isCons())
	  {
	    heap.dropSubFromTerm(*this, term);
	  }
	bool is_simplified = (savedsub != 
			      term.getSubstitutionBlockList());
	if (term.getSubstitutionBlockList()->isNil())
	  {
	    simpterm = term.getTerm();
	    return is_simplified;
	  }
	// Var has a sub so simplify the sub
	return (simplify_sub_term(term, simpterm, AtomTable::success) 
		|| is_simplified);
	break;
      }
    case Object::tObjVar:
      {
	Object* savedsub = term.getSubstitutionBlockList();
	if (savedsub->isCons())
	  {
	    heap.dropSubFromTerm(*this, term);
	  }
	bool is_simplified = (savedsub != 
			      term.getSubstitutionBlockList());
	if (term.getSubstitutionBlockList()->isNil())
	  {
	    simpterm = term.getTerm();
	    return is_simplified;
	  }
	heap.prologValueDereference(term);
	is_simplified = (savedsub != 
			 term.getSubstitutionBlockList());
	if (term.getTerm()->tTag() != Object::tObjVar)
	  {
	    (void)simplify_term(term, simpterm);
	    return true;
	  }
	// ObjVar has a sub so simplify the sub
	return (simplify_sub_term(term, simpterm, AtomTable::success) 
		|| is_simplified);
	break;
      }
    default:
      assert(false);
      return false;
    }
  return true;
}


bool
Thread::simplify_sub_term(PrologValue& term, Object*& simpterm, Object* tester)
{
  assert(quick_tidy_check);
  // allocate buffer
  Object* index = 
    heap.newInteger(buffers.allocate(heap.getTop(), scratchpad.getTop()));
 
  // Save state
  heapobject* savesavedtop = heap.getSavedTop();
  heapobject* savedHT = heap.getTop();
  TrailLoc savedBindingTrailTop = bindingTrail.getTop();
  TrailLoc savedOtherTrailTop = otherTrail.getTop();
  heap.setSavedTop(savedHT);

  // save old top of push down stack
  int old_size = pushDownStack.size();

 assert(quick_tidy_check);
  // process each substitution block
  for (Object* sub = term.getSubstitutionBlockList();
       sub->isCons();
       sub = OBJECT_CAST(Cons*, sub)->getTail())
    {
      SubstitutionBlock* sub_block = 
	OBJECT_CAST(SubstitutionBlock*, OBJECT_CAST(Cons*, sub)->getHead());
      // process each substitution block
      size_t size = sub_block->getSize();
      for (size_t i = 1; i <= size; i++)
	{
	  assert(sub_block->getDomain(i)->variableDereference()->isObjectVariable());

	  ObjectVariable* dom = 
	    OBJECT_CAST(ObjectVariable*, sub_block->getDomain(i)->variableDereference());
	  if (dom->isLocalObjectVariable())
	    {
	      continue;
	    }
	  bool found = false;
	  for (int j = pushDownStack.size(); j > old_size; )
	    {
	      j--;
	      Object* before = pushDownStack.getEntry(j);
	      if (before == dom)
		{
		  found = true;
		  break;
		}
	    }
	  if (found)
	    {
	      continue;
	    }
	  for (int j = pushDownStack.size(); j > old_size; )
	    {
	      j--;
	      assert(pushDownStack.getEntry(j)->isObjectVariable());
	      ObjectVariable* before = 
		OBJECT_CAST(ObjectVariable*, pushDownStack.getEntry(j));
	      assert(dom == dom->variableDereference());
	      if (!dom->distinctFrom(before))
		{
		  setDistinct(dom, before);
		}
	    }
	  pushDownStack.push(dom);
          assert(quick_tidy_check);
	  if (!retry_delays())
	    {
	      heap.setTop(savedHT);
	      bindingTrail.backtrackTo(savedBindingTrailTop);
	      assert(bindingTrail.check(heap));
	      otherTrail.backtrackTo(savedOtherTrailTop);
	      assert(otherTrail.check(heap));
	      continue;
	    } 
          assert(quick_tidy_check);
	  if (term.getTerm()->isObjectVariable())
	    {
	      dom = OBJECT_CAST(ObjectVariable*, dom->variableDereference());
	      if (!dom->distinctFrom(OBJECT_CAST(ObjectVariable*, 
						 term.getTerm()->variableDereference())))
		{
		  bindObjectVariables(dom, OBJECT_CAST(ObjectVariable*, 
						       term.getTerm()->variableDereference()));
		  if (retry_delays())
		    {
		      Object* simpterm;
		      PrologValue newterm(term.getSubstitutionBlockList(), 
					  dom);
		      
		      (void)simplify_term(newterm, simpterm);
		      Object* result;
		      transform_with_tester(simpterm, result, tester);
		      Object* copydom = dom;
		      Object* succ = AtomTable::success;
		      (void)psi_copy_obvar_to_buffer_tail(index, copydom);
		      (void)psi_copy_to_buffer_tail(index, result, succ);
		    }
		}
	    }
	  else if (term.getTerm()->isVariable())
	    {
assert(quick_tidy_check);
	      if (gen_nfi_delays(dom, term.getTerm()) && retry_delays())
		{
		  Object* simpterm;
		  PrologValue newterm(term.getSubstitutionBlockList(), dom);
		  (void)simplify_term(newterm, simpterm);
		  Object* result;
		  transform_with_tester(simpterm, result, tester);
		  Object* copydom = dom->variableDereference();
		  Object* succ = AtomTable::success;
		  (void)psi_copy_obvar_to_buffer_tail(index, copydom);
		  (void)psi_copy_to_buffer_tail(index, result, succ);
		}
	    }
	  else
	    {
	      assert(term.getTerm()->isQuantifiedTerm());
	      assert(!tester->isObjectVariable());
	      PrologValue qterm(term.getTerm());
	      assert(dom == dom->variableDereference());
	      if (freeness_test(dom, qterm) != false)
		{
		  Object* simpterm;
		  PrologValue newterm(term.getSubstitutionBlockList(), dom);
		  (void)simplify_term(newterm, simpterm);
		  Object* copydom = dom;
		  Object* succ = AtomTable::success;
		  (void)psi_copy_obvar_to_buffer_tail(index, copydom);
		  (void)psi_copy_to_buffer_tail(index, simpterm, succ);
		} 
	    }
	  // Restore state
	  heap.setTop(savedHT);
	  bindingTrail.backtrackTo(savedBindingTrailTop);
	  assert(bindingTrail.check(heap));
	  otherTrail.backtrackTo(savedOtherTrailTop);
	  assert(otherTrail.check(heap));
	}	   
    }
  pushDownStack.popNEntries(pushDownStack.size() - old_size);
  heap.setSavedTop(savesavedtop);
  // Collect result
  Object* termterm = term.getTerm();
  (void)psi_make_sub_from_buffer(index, termterm, simpterm);
  (void)psi_dealloc_buffer(index);
  PrologValue psimp(simpterm);
  return (heap.fastEqual(term, psimp) != true);
}

bool
Thread::gen_nfi_delays(ObjectVariable* dom, Object* term)
{
  assert(quick_tidy_check);
  assert(term->isVariable());
  Object* var_delays = OBJECT_CAST(Reference*, term)->getDelays();
  for ( ; var_delays->isCons();
	var_delays = OBJECT_CAST(Cons *, var_delays)->getTail())
    {
      Object* vd =
	OBJECT_CAST(Cons*, var_delays)->getHead()->variableDereference();
      assert(vd->isStructure());
      Structure* vdstruct = OBJECT_CAST(Structure *, vd);
      assert(vdstruct->getArity() == 2);
      Object* vdstatus =
	vdstruct->getArgument(1)->variableDereference();
      assert(vdstatus->isVariable());
      if (!OBJECT_CAST(Variable*,vdstatus)->isFrozen())
	{
	  continue;
	}
      Object* problem =
	vdstruct->getArgument(2)->variableDereference();
      assert(problem->isStructure());
      Structure* pstruct = OBJECT_CAST(Structure*, problem);
      if (pstruct->getArity() != 2 ||
	  pstruct->getFunctor() != AtomTable::nfi)
	{
	  continue;
	}
      // We have an unsolved nfi problem
      Object* obvar = pstruct->getArgument(1)->variableDereference();
      PrologValue pval(pstruct->getArgument(2));
      heap.prologValueDereference(pval);
      assert(pval.getTerm() == term);
      pval.setTerm(dom);
      assert(obvar->isObjectVariable());
      if (!notFreeInNFISimp(OBJECT_CAST(ObjectVariable*, obvar), pval))
	{
	  return false;
	}
    } 
  return true;
}

//
// When tester is an object variable this is used
// to check if tester is free in simpterm
// If it is then result = tester
// If not then result = '$'
// else if UNSURE result = simpterm
// If tester is not an object variable then result = simpterm
//
void
Thread::transform_with_tester(Object* simpterm, Object*& result, 
			      Object* tester)
{
  if (!tester->isObjectVariable())
    {
      result = simpterm;
      return;
    }
  PrologValue term(simpterm);
  tester = tester->variableDereference();

  truth3 free = freeness_test(OBJECT_CAST(ObjectVariable*, tester), term);

  if (free == true)
    {
      result = tester;
    }
  else if (free == false)
    {
      result = AtomTable::dollar;
    }
  else
    {
      result = simpterm;
    }
}




