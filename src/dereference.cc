// dereference.cc - A few versions of dereference.  
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
// $Id: dereference.cc,v 1.5 2006/01/31 23:17:49 qp Exp $

#include "heap_qp.h"

//extern AtomTable* atoms;

//
// Dereference a substituted term returning the dereferenced object with
// substitutions evaluated as far as possible.
//
Object*
Heap::subDereference(Object* o)
{
  assert(o->isSubstitution());
  assert(o->hasLegalSub());
  Substitution *osub = OBJECT_CAST(Substitution *, o);
  Object* term = osub->getTerm();
  Object* sub  = osub->getSubstitutionBlockList();
  substitutionDereference(sub, term);
  if (osub->getTerm() == term && osub->getSubstitutionBlockList() == sub)
    {
      // nothing is achieved so return original term.
      return (o);
    }
  else
    {
      if (sub->isNil())
	{
	  // no substitution left
	  return (term);
	}
      else
	{
	  return(newSubstitution(sub,term));
	}
    }
}


//
// substitutionDereference dereferences substitution,term pairs.  All the
// top-level substitutions are collected into a single list of
// substitutions and any possible substitution evaluations are carried
// out.  
//
void
Heap::substitutionDereference(Object *& sublist, Object *& term)
{
  while (true)
    {
      term = term->variableDereference(); 
      
      while(term->isSubstitution()) 
	{
	  Substitution *substitution = OBJECT_CAST(Substitution *, term);

	  sublist = appendSubstitutionBlockLists(substitution->getSubstitutionBlockList(), sublist);
	  term = substitution->getTerm()->variableDereference(); 
	} 

      // 
      // At this point all the top-level substitutions have been moved out 
      // of term and into sublist
      //
      assert(! term->isSubstitution()); // implied by while(...)

      if (term->isObjectVariable())
	{
	  if (sublist->isNil())
	    {
	      return;
	    }
          assert(OBJECT_CAST(Cons*, sublist)->getHead()->isSubstitutionBlock());
	  SubstitutionBlock* subblock =
	    OBJECT_CAST(SubstitutionBlock*, 
			OBJECT_CAST(Cons*, sublist)->getHead());

	  assert(subblock->getSize() > 0);

	  if (term->isLocalObjectVariable()) 
	    {
	      if (subblock->getDomain(1)->isLocalObjectVariable())
		{
		  for (size_t i = 1; i <= subblock->getSize(); i++)
		    {
		      if (term == subblock->getDomain(i))
			{
			  //
			  // [t1/v1, ... tk/vk, ... tn/vn] vk => tk
			  //
			  term = subblock->getRange(i);
			  break;
			}
		    }
		}

	      sublist = OBJECT_CAST(Cons*, sublist)->getTail();
	    }
	  else
	    {
	      //
	      // Term is ordinary object variable.
	      // Evaluate substitution.
	      //
	      bool saved = false;
              bool derefed = false;
	      Object* save;
	      for (size_t i = 1; i <= subblock->getSize(); i++)
		{
		  Object* domain = subblock->getDomain(i);
 		  domain = domain->variableDereference();
                  Object* range = subblock->getRange(i)->variableDereference();
		  assert(domain->isObjectVariable());
		  if (term == domain && (!saved || save == range))
		    {
		      //
		      // [t1/x1, ... tk/xk, ... tn/xn] xk => tk
		      //
		      term = range;
                      derefed = true;
		      break;
		    }
		  else if (term->distinctFrom(domain))
		    {
                      if (!saved)
                        {
                          derefed = true;
                        }
		      continue;
		    }
		  else
		    {
                      derefed = false;
                      if (!saved)
                        {
                           saved = true;
			   save = range;
                        }
                      else
                        {
                           if (save == range)
                             {
                               continue;
                             }
                           else
                             {
		               // 
		               // No (more) substitution evaluation possible
		               //
		               return;
                              }
                         }
		    }
		}
              if (!derefed)
                {
                  return;
                }
	      // 
	      // this subblock didn't do anything, so move on 
	      //
	      sublist = OBJECT_CAST(Cons*, sublist)->getTail();
	    }
	}
      else if (term->isAtom() || term->isNumber())
	{
	  sublist = AtomTable::nil;
	  return; // can't be altered by subst
	}
      else
	{
	  return;
	}
    }
  return;
}










