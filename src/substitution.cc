// substitution.cc - Contains a set of functions for dealing 
//		    with Qu-Prolog substitution. 
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
// $Id: substitution.cc,v 1.14 2006/03/13 00:10:25 qp Exp $

//#include "atom_table.h"
#include "heap_qp.h"
#include "thread_qp.h"

//
// Copy the first n substitutions
//
Object*
Heap::copySubSpineN(Object *input_list, int n)
{
  assert(input_list != NULL);
  assert((input_list->isNil() && (n == 0)) ||
	(input_list->isCons() && 
	 OBJECT_CAST(Cons*, input_list)->isSubstitutionBlockList()));
  if (n == 0)
    return AtomTable::nil;

  // Copy the rest of substitution.
  Object *copy_list = 
    copySubSpineN(OBJECT_CAST(Cons *, input_list)->getTail(), n - 1); 
  
  assert(OBJECT_CAST(Cons*, input_list)->getHead()->isSubstitutionBlock());
  return newSubstitutionBlockList(OBJECT_CAST(SubstitutionBlock*, OBJECT_CAST(Cons *, input_list)->getHead()), copy_list);
}

//
// Copy the spine of a list of substitutions up to the stop point.
// tail_list specifies the new tail of copied version.
//
Object *
Heap::copySubSpine(Object *input_list,
		   Object *stop_list,
		   Object *tail_list)
{
  assert(input_list != NULL);
  assert(stop_list != NULL);
  assert(tail_list != NULL);
  assert(input_list->isNil() ||
	       (input_list->isCons() && 
		OBJECT_CAST(Cons*, input_list)->isSubstitutionBlockList()));
  assert(stop_list->isNil() ||
	       (stop_list->isCons() && 
		OBJECT_CAST(Cons*,stop_list)->isSubstitutionBlockList()));
  assert(tail_list->isNil() ||
	       (tail_list->isCons() && 
		OBJECT_CAST(Cons*, tail_list)->isSubstitutionBlockList()));

  if (input_list == stop_list)
    {
      //
      // Stop point has been reached, return the specified tail.
      // 
      return tail_list;
    }
  else if (input_list->isNil())
    {
      // Should not really get here if stop_list is there
      assert(false);
      return AtomTable::nil;
    }
  else
    {
      // Copy the rest of substitution.
      Object *copy_list = 
	copySubSpine(OBJECT_CAST(Cons *, input_list)->getTail(), 
		     stop_list,
		     tail_list);
      
      assert(OBJECT_CAST(Cons*, input_list)->getHead()->isSubstitutionBlock());
      return newSubstitutionBlockList(OBJECT_CAST(SubstitutionBlock*, OBJECT_CAST(Cons *, input_list)->getHead()), copy_list);
    }
}

//
// This function is called from unify. It is to simplify unification problem.
// Example 1.
//	If the unification problem is:
//		[v3/z] * [x/v2] * [v2/y] * [v1/w] * X = t
//
//	Invert will make:
//		X = [w/v1] * [y/v2] * [v2/x] * [z/v3] * t,
//
//	and generate not_free_in problems:
//
//		[v3/z] * [x/v2] * [v2/y] * w not_free_in t
//			 [v3/z] * [x/v2] * y not_free_in t
//					   z not_free_in t
//		
//
// Example 2.
//	If the unification problem is:
//		[v1/y1, v2/y2] * [w1/v3, w2/v4] * [v5/z1, v6/z2] * X = t
//
//	Invert will make:
//		X = [z1/v5, z2/v6] * [v3/w1, v4/w2] * [y1/v1, y2/v2] * t
//
//	and generate not_free_in problems:
//
//			[v1/y1, v2/y2] * [w1/v3, w2/v4] * z1 not_free_in t
//			[v1/y1, v2/y2] * [w1/v3, w2/v4] * z2 not_free_in t
//							  y1 not_free_in t
//							  y2 not_free_in t
//
// NOTE: The order of the inverted substitution is IMPORTANT.
//	 If the original domain is an object variable, a free_in 
//	 test must be done.
//	
bool
Heap::invert(Thread& th, Object *sub_list, PrologValue& term)
{
  assert(sub_list->isNil() ||
	       (sub_list->isCons() && 
		OBJECT_CAST(Cons*, sub_list)->isSubstitutionBlockList() &&
		OBJECT_CAST(Cons*, sub_list)->isInvertible()));

  Object *inverted_sub_list = AtomTable::nil;
  
  // Swap domains and ranges, and swap pointers in substitution 'sub'.
  for (Object *list = sub_list;
       list->isCons();
       list = OBJECT_CAST(Cons *, list)->getTail())
    {
      assert(OBJECT_CAST(Cons *, list)->getHead()->isSubstitutionBlock());
      SubstitutionBlock *sub = 
	OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, list)->getHead());
      
      assert(sub->getSize() > 0);
      
      // Set up the inverted substitution block
      SubstitutionBlock *inverted_sub = 
	newSubstitutionBlock(sub->getSize());
      inverted_sub->makeInvertible();
      
      // Check whether the first domain is local object variable.
      // If it is the case then all the other domains are local
      // object variables, and there is no need to check them all.
      const bool do_freeness = ! sub->getDomain(1)->isLocalObjectVariable();
      
      for (size_t i = 1; i <= sub->getSize(); i++)
	{
	  // Invert domains and ranges.
          assert(sub->getRange(i)->isObjectVariable());
	  inverted_sub->setDomain(i, sub->getRange(i));
	  inverted_sub->setRange(i, sub->getDomain(i));
	  if (do_freeness)
	    {
	      // Do free in test for ordinary object variable.
	      PrologValue object_variable(OBJECT_CAST(Cons*, list)->getTail(),
					  sub->getDomain(i));
              th.set_quick_tidy_check(true);
              bool result = th.internalNotFreeIn(object_variable, term);
              th.set_quick_tidy_check(false);
	      if (! result)
		{
		  return false;
		}
	    }
	  inverted_sub_list = newSubstitutionBlockList(inverted_sub,
						       inverted_sub_list);
	}
    }
  // Add term substitution to the right of inverted substitution - 'sub'.
  term.setSubstitutionBlockList(
         appendSubstitutionBlockLists(term.getSubstitutionBlockList(), 
				      inverted_sub_list));
  return true;
}

//
// Used to invert sub to transform sub * x not_free_in term into
// x not_free_in sub-1 * term .
//
// NOTE: no extra not_free_in conditions are added.
//	
void
Heap::invertWithoutNFI(Object *sub, PrologValue& term)
{
  assert(sub->isNil() ||
	       (sub->isCons() && 
		OBJECT_CAST(Cons*, sub)->isSubstitutionBlockList()));

  Object *inverted_sub_list = AtomTable::nil;
  
  // Swap domains and ranges, and swap pointers in substitution 'sub'.
  for (Object *list = sub;
       list->isCons();
       list = OBJECT_CAST(Cons *, list)->getTail())
    {
      assert(OBJECT_CAST(Cons *, list)->getHead()->isSubstitutionBlock());
      SubstitutionBlock *sub = 
	OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, list)->getHead());
      
      assert(sub->getSize() > 0);
      
      // Set up the inverted substitution block
      SubstitutionBlock *inverted_sub = newSubstitutionBlock(sub->getSize());
      inverted_sub->makeInvertible();
      
      for (size_t i = 1; i <= sub->getSize(); i++) 
	{
	  // Invert domains and ranges.
          assert(sub->getRange(i)->isObjectVariable());
	  inverted_sub->setDomain(i, sub->getRange(i));
	  inverted_sub->setRange(i, sub->getDomain(i));
	}
      
      inverted_sub_list = newSubstitutionBlockList(inverted_sub,
						   inverted_sub_list);
    }
  
  
  // Add term substitution to the right of inverted substitution - 'sub'.
  term.setSubstitutionBlockList(appendSubstitutionBlockLists(term.getSubstitutionBlockList(), inverted_sub_list));
}

//
// If a term has a non-empty substitution, create a new SUBSTITUTION_OPERATOR
// and assign substitution and term. If term has an empty substitution then 
// just return the term part.
// 
Object *
Heap::prologValueToObject(PrologValue& term)
{
  if (term.getSubstitutionBlockList()->isNil())
    {
      return term.getTerm();
    }
  else
    {
      Substitution *sub = newSubstitution();
      
      sub->setSubstitutionBlockList(term.getSubstitutionBlockList());
      sub->setTerm(term.getTerm());
      
      return sub;
    }
}

//
// Check whether the local object variable occurs in a range position
// of any substitution from the composition of substitutions. 
//	
bool
Heap::isLocalInRange(Object *local_object_variable,
		     Object *sub_list)
{
  assert(local_object_variable->isLocalObjectVariable());
  assert(sub_list->isNil() ||
	       (sub_list->isCons() && 
		OBJECT_CAST(Cons*, sub_list)->isSubstitutionBlockList()));
  
  for (Object *list = sub_list;
       list->isCons();
       list = OBJECT_CAST(Cons *, list)->getTail())
    {
      assert(OBJECT_CAST(Cons *, list)->getHead()->isSubstitutionBlock());
      SubstitutionBlock *sub = 
	OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, list)->getHead());
      assert(sub->getSize() > 0);
      
      // Check whether the first range is a local object variable.
      // If it is the case then all the other ranges are local
      // object variables, so search for the local object variable
      // among ranges, otherwise skip to the next substitution.
      if (sub->getRange(1)->isLocalObjectVariable())
	{
	  // Search for the local object variable as a range. 
	  for (size_t i = 1; i <= sub->getSize(); i++)
	    {
	      if (local_object_variable == sub->getRange(i)) 
		{
		  return true;
		}
	    }
	}
    } 
  return false;
}

//
// Copy the substitution block before any destructive processing is
// performed.  The range elements are replaced by $'s.
// Only the part of the substitution up to size is copied.
//
Object *
Heap::copySubstitutionBlockWithDollars(Object *sub_list, size_t size)
{
  assert(sub_list->isNil() ||
	       (sub_list->isCons() &&
		OBJECT_CAST(Cons*, sub_list)->isSubstitutionBlockList()));
  
  if (size == 0)
    {
      return (OBJECT_CAST(Cons*, sub_list)->getTail());
    }
  assert(OBJECT_CAST(Cons*, sub_list)->getHead()->isSubstitutionBlock());
  SubstitutionBlock *sub = OBJECT_CAST(SubstitutionBlock*,
				       OBJECT_CAST(Cons*, sub_list)->getHead());
  
  SubstitutionBlock *new_sub = newSubstitutionBlock(size);
  
  for (size_t i = 1; i <= size; i++)
    {
      new_sub->setDomain(i, sub->getDomain(i)); 
      new_sub->setRange(i, AtomTable::dollar);
    }
  
  return newSubstitutionBlockList(new_sub, 
				  OBJECT_CAST(Cons*, sub_list)->getTail());
}



//
// Test to see if an object variable is NFI in the ranges of inner subs
// or term part of a substituted term
//
bool
Heap::canRemove(Thread& th, Object* obvar, int index, 
		SubstitutionBlock** subarray, Object* term)
{
  obvar = obvar->variableDereference();
  assert(obvar->isObjectVariable());
  ObjectVariable* ov = OBJECT_CAST(ObjectVariable*, obvar);
  for (int i = index; i >= 0; i--)
    {
      if (subarray[i] == NULL)
        {
          continue;
        }
      size_t size = subarray[i]->getSize();
      bool found = false;
      for (size_t j = 1; j <= size; j++)
	{
	  if (!th.fastNFITerm(ov, subarray[i]->getRange(j)->variableDereference()))
	    {
	      return false;
	    }
	  if (subarray[i]->getDomain(j) == ov)
	    {
	      found = true;
	    }
	}
      if (found)
	{
	  return true;
	}
    }
  return th.fastNFITerm(ov, term->variableDereference());
}

//
// Remove useless entry from a substitution wherever it is possible.
// Assumed to be (Prolog) dereferenced and the term part is either
// a variable or object variable.

void
Heap::dropSubFromTerm(Thread& th, PrologValue& pterm)
{
#ifndef NDEBUG
    Object* remterm = pterm.getTerm();
    Object* remsub = pterm.getSubstitutionBlockList();
    prologValueDereference(pterm);
    assert(remterm == pterm.getTerm());
    assert(remsub == pterm.getSubstitutionBlockList());
#endif
  Object* term = pterm.getTerm();
  Object *sub = pterm.getSubstitutionBlockList();

  bool changed = false;

  assert(!sub->isNil());

  // get the number of sub blocks
  int size = 0;
  for (Object* tmp = sub;
       tmp->isCons();
       tmp = OBJECT_CAST(Cons *, tmp)->getTail())
    {
      size++;
    }

  SubstitutionBlock** subarray = new SubstitutionBlock*[size];

  // Fill subarray with blocks
  int index = 0;
  for (;
       sub->isCons();
       sub = OBJECT_CAST(Cons *, sub)->getTail())
    {
      assert(OBJECT_CAST(Cons*, sub)->getHead()->isSubstitutionBlock());
      subarray[index++] = 
	OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, sub)->getHead());
    }

  // Process the sub blocks
  for (int i = 0; i < size; i++)
    {
      if (subarray[i]->getDomain(1)->isLocalObjectVariable())
	{
	  // check if matching sub
	  bool found = false;
	  for (int j = i-1; j >= 0; j--)
	    {
	      if ((subarray[j] != NULL)
		  && (subarray[j]->getRange(1) == subarray[i]->getDomain(1)))
		{
		  found = true;
		  break;
		}
	    }
	  // If there is no matching sub then this sub can be removed
	  if (!found)
	    {
	      subarray[i] = NULL;
	      changed = true;
	    }
	}
      else if (subarray[i]->getRange(1)->isLocalObjectVariable())
	{
	  //
	  // To preserve the invariant that substitutions with
	  // locals as a single unit.  Entries within a
	  // substitution cannot be removed one by one.
	  // This is an attempt to remove the whole block for
	  // s*A.  s*x is handled by dereference as part of the
	  // substitution evaluation process.
	  //
	  
	  bool remove = true;
	  for (int k = static_cast<int>(subarray[i]->getSize()); k > 0; k--)
	    {
	      if (!canRemove(th, subarray[i]->getDomain(k), i-1, 
			     subarray, term))
		{
		  remove = false;
		  break;
		}
	    }
	  if (remove)
	    {
	      subarray[i] = NULL;
	      changed = true;
	    }
	}
      else
	{
	  // try to remove individual components of a sub
	  int blocksize = static_cast<int>(subarray[i]->getSize());
          Object** doms = new Object*[blocksize];
          Object** rans = new Object*[blocksize];
	  for (int k = 0; k < blocksize; k++)
	    {
	      doms[k] = subarray[i]->getDomain(k+1)->variableDereference();
	      rans[k] = subarray[i]->getRange(k+1)->variableDereference();
	    }
	  int finalsize = blocksize;
	  // Remove entries which have no effect - i.e. they are
	  // NFI in inner sub and term
	  for (int k = 0; k < blocksize; k++)
	    {
	      if (canRemove(th, doms[k], i-1, subarray, term))
		{
		  doms[k] = NULL;
		  finalsize--;
		  changed = true;
		}
	    }
	  // Now try and remove entries of the form x/x
	  for (int k = 0; k < blocksize; k++)
	    {
	      if (doms[k] == rans[k])
		{
		  assert(doms[k] != NULL);
		  bool del = true;
		  for (int p = k+1; p < blocksize; p++)
		  //for (int p = k-1; p >= 0; p--)
		    {
		      assert(doms[k] == doms[k]->variableDereference());
		      assert(doms[p]->isObjectVariable());
		      if (doms[p] == NULL)
			{
			  continue;
			}
		      if (!OBJECT_CAST(ObjectVariable*, doms[k])->distinctFrom(doms[p]))
			{
			  del = false;
			  break;
			}
		    }
		  if (del)
		    {
		      doms[k] = NULL;
		      finalsize--;
		      changed = true;
		    }
		}
	    }
	  if (finalsize == 0)
	    {
	      subarray[i] = NULL;
	    }
	  else
	    {
	      assert(finalsize > 0);
	      subarray[i] = newSubstitutionBlock(finalsize);
	      int pos = 1;
	      for (int k = 0; k < blocksize; k++)
		{
		  if (doms[k] != NULL)
		    {
		      subarray[i]->setDomain(pos, doms[k]);
		      subarray[i]->setRange(pos, rans[k]);
		      pos++;
		    }
		}
	    }
          delete doms;
          delete rans;
	}
    }
	  
  if (changed)
    {
      // Rebuild sub
      Object* subst = AtomTable::nil;
      for (int i = size-1; i >= 0; i--)
	{
	  if (subarray[i] != NULL)
	    {
	      subst = newSubstitutionBlockList(subarray[i], subst);
	    }
	}
      pterm.setSubstitutionBlockList(subst);
      th.TheHeap().prologValueDereference(pterm);
      if (term != pterm.getTerm() &&
	  pterm.getSubstitutionBlockList()->isCons())
	{
	  dropSubFromTerm(th, pterm);
	}
      assert(pterm.getTerm() == pterm.getTerm()->variableDereference());
    }
  delete subarray;
}

