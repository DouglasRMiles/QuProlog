// yield.cc -	The Qu-Prolog yield procedures. 
//		A substitution can yield a specified term if one of the 
//		following is true:
//		   1. The specified term is in the range.
//		   2. A variable is in the range.
//		   3. An thawed object variable is in the range and its 
//		      substitution yields the specified term.
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
// $Id: yield.cc,v 1.5 2006/01/31 23:17:52 qp Exp $

#include        "heap_qp.h"

//
// Check whether the substitution yields the term.
//
bool
Heap::yield(Object *term,
	    Object *sub_block_list,
	    YieldCond cond,
	    ThreadStatus& status)
{
  assert(sub_block_list->isNil() ||
	       (sub_block_list->isCons() && 
		OBJECT_CAST(Cons *,sub_block_list)->isSubstitutionBlockList()));

  for (Object *s = sub_block_list;
       s->isCons();
       s = OBJECT_CAST(Cons *, s)->getTail())
    {
      assert(OBJECT_CAST(Cons*, s)->getHead()->isSubstitutionBlock());
      SubstitutionBlock *sub_block = 
	OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, s)->getHead());

      if (sub_block->isInvertible())
	{
	  //
	  // All ranges are object variables, so the 
	  // substitution cannot yield the term.
	  // 
	  continue;
	}
      else
	{
	  assert(sub_block->getSize() > 0);

	  for (size_t i = 1; i <= sub_block->getSize(); i++)
	    {
              assert(sub_block->getRange(i)->hasLegalSub());
	      PrologValue range(sub_block->getRange(i));
	      prologValueDereference(range);

	      if ((range.getTerm()->isVariable() && 
		   (status.testHeatWave() ||
		    ! OBJECT_CAST(Variable*, range.getTerm())->isFrozen())) || 
		  (*cond)(this, range, term) ||
		  (range.getTerm()->isObjectVariable() &&
		   yield(term, range.getSubstitutionBlockList(), cond, status)))
		{
		  //
		  // Frozen variable is like a constant 
		  // which is always different from any 
		  // other. Object variable cannot be 
		  // bound to other then object variable,
		  // so only substitution can yield the
		  // term.
		  //
		  return true;
		}
	    }
	}
    }
  return false;
}

//
// Extra condition for yield structure.
//
bool
Heap::yieldStructureCond(Heap* heapPtr, PrologValue& range,
			 Object *str)
{
  assert(str->isStructure());
  Structure* structure = OBJECT_CAST(Structure*, str);
  if (! (range.getTerm()->isStructure() &&
	 OBJECT_CAST(Structure *, range.getTerm())->getArity() == structure->getArity())) 
    {
      return false;
    }
  else
    {
      Structure *range_structure = OBJECT_CAST(Structure *, range.getTerm());

      PrologValue range_fn(range.getSubstitutionBlockList(),
			   range_structure->getFunctor());
  
      heapPtr->prologValueDereference(range_fn);
      PrologValue struct_fn(heapPtr->dereference(structure->getFunctor()));

      return (! range_fn.getTerm()->isAtom() || 
	      ! struct_fn.getTerm()->isAtom() || 
	      range_fn.getTerm() == struct_fn.getTerm());
    }
}

//
// Extra condition for yield quantifier.
//
bool
Heap::yieldQuantifierCond(Heap* heapPtr, PrologValue& range,
			  Object *q)
{
  assert(q->isQuantifiedTerm());
  QuantifiedTerm* quantified_term = OBJECT_CAST(QuantifiedTerm*, q);
  if (! range.getTerm()->isQuantifiedTerm())
    {
      return false;
    }
  else
    {
      QuantifiedTerm *range_quantified_term =
	OBJECT_CAST(QuantifiedTerm *, range.getTerm());

      PrologValue range_q(range.getSubstitutionBlockList(),
			  range_quantified_term->getQuantifier());
      heapPtr->prologValueDereference(range_q);

      PrologValue quant_q(quantified_term->getQuantifier());

      return (! range_q.getTerm()->isAtom() || 
	      ! quant_q.getTerm()->isAtom() || 
	      range_q.getTerm() == quant_q.getTerm());
    }
}

//
// Check whether the substitution yields the object variable.
//
bool
Heap::yieldObjectVariable(Object *object_variable,
			  Object *sub_block_list,
			  ThreadStatus& status)
{
  assert(object_variable->isObjectVariable());
  for (Object *s = sub_block_list;
       s->isCons();
       s = OBJECT_CAST(Cons *, s)->getTail())
    {
      assert(OBJECT_CAST(Cons*, s)->getHead()->isSubstitutionBlock());
      SubstitutionBlock *sub = 
	OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, s)->getHead());
      assert(sub->getSize() > 0);

      for (size_t i = 1; i <= sub->getSize(); i++)
	{
          assert(sub->getRange(i)->variableDereference()->hasLegalSub());
	  PrologValue range(dereference(sub->getRange(i)));

	  if ((range.getTerm()->isVariable() && 
	       (status.testHeatWave() || 
		! OBJECT_CAST(Variable*, range.getTerm())->isFrozen())) || 
	      (range.getTerm()->isObjectVariable() &&
	       (! range.getTerm()->distinctFrom(object_variable) ||
		yieldObjectVariable(object_variable,
				    range.getSubstitutionBlockList(),
				    status))))
	    {
	      return true;
	    }
	}
    }

  return false;
}


