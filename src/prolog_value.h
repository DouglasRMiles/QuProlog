// prolog_value.h - Define the class for holding substitution and term as
//		    a pair.
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
// $Id: prolog_value.h,v 1.4 2006/03/30 22:50:31 qp Exp $

#ifndef	PROLOG_VALUE_H
#define	PROLOG_VALUE_H

#include "defs.h"
#include "debug.h"
#include "objects.h"

class PrologValue
{
 private:
  Object *sub;		// List of substitutions
  Object *term;		// The term

 public:
  PrologValue(void) : sub(AtomTable::nil), term(NULL) { }
    PrologValue(Object *t)
      {
	if (t->isSubstitution())
	  {
	    Substitution *s = OBJECT_CAST(Substitution*, t);
	    sub = s->getSubstitutionBlockList();
	    term = s->getTerm();
	    assert(sub->isLegalSub());
	  }
	else
	  {
	    sub = AtomTable::nil;
	    term = t;
	  }
      }
    PrologValue(Object *s, Object *t)
      : sub(s), term(t)
      {
	assert(s->isLegalSub());
      }
  
      Object *getSubstitutionBlockList(void) { return sub; }
      Object *getTerm(void) { return term; }
      void setTerm(Object *t)
      {
	term = t;
      }

      Object **getSubstitutionBlockListAddress(void) 
	{ 
	  return &sub;
	}

      void setSubstitutionBlockList(Object *list)
      {
	assert(list->isLegalSub());

	sub = list;
      }

  
};

#endif	// PROLOG_VALUE_H











