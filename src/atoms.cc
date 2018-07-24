// atoms.cc - Predicates maniuplate atoms.
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
// $Id: atoms.cc,v 1.7 2006/01/31 23:17:49 qp Exp $

#include <string.h>
#include <sstream>

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;

//
// psi_atom_length(atom, variable)
// Work out the string length of an atom.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_atom_length(Object *& object1, Object *& object2)
{
  Object * val1 = object1;
  
  val1 = heap.dereference(val1);
  
  if (val1->isAtom())
    {
      object2 = heap.newShort(static_cast<int32>(strlen(OBJECT_CAST(Atom*, val1)->getName())));
      return(RV_SUCCESS);
    }
  else if (val1->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
}

//
// psi_atom_concat2(atomic, atomic, atomic)
// Join the first 2 atomics to get the third.
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_atom_concat2(Object *& object1, Object *& object2, 
			 Object *& object3)
{
  ostringstream	strm;

  Object* a1 = heap.dereference(object1);
  Object* a2 = heap.dereference(object2);

  if (a1->isAtom())
    {
      strm << OBJECT_CAST(Atom*, a1)->getName();
    }
  else if (a1->isNumber())
    {
      strm << a1->getInteger();
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (a2->isAtom())
    {
      strm << OBJECT_CAST(Atom*, a2)->getName();
    }
  else if (a2->isNumber())
    {
      strm << a2->getInteger();
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  strm << ends;
    
  object3 = atoms->add(strm.str().data());
  return(RV_SUCCESS);
}

//
// psi_concat_atom(list of atomic, variable)
// Join a list of atomic together to form a new atom.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_concat_atom(Object *& object1, Object *& object2)
{
  ostringstream	strm;
 
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);

  while (pval1.getTerm()->isCons() && strm.good())
    {
      Cons* clist = OBJECT_CAST(Cons*, pval1.getTerm());
      Object* head = heap.dereference(clist->getHead());

      if (head->isAtom())
	{
	  strm << OBJECT_CAST(Atom*, head)->getName();
	}
      else if (head->isNumber())
	{
	  strm << head->getInteger();
	}
      else if (head->isSubstitution())
	{
	  PrologValue pvhead(pval1.getSubstitutionBlockList(), head);
	  heap.prologValueDereference(pvhead);
	  head = pvhead.getTerm();
	  if (head->isAtom())
	    {
	      strm << OBJECT_CAST(Atom*, head)->getName();
	    }
	  else if (head->isNumber())
	    {
	      strm << head->getInteger();
	    }
	  else
	    {
	      PSI_ERROR_RETURN(EV_TYPE, 1);
	    }
	}
      else
	{
	  PSI_ERROR_RETURN(EV_TYPE, 1);
	}
      pval1.setTerm(clist->getTail());
      heap.prologValueDereference(pval1);
    }
  
  if (pval1.getTerm()->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }

  if (! pval1.getTerm()->isNil())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  
  strm << ends;
  
  object2 = atoms->add(strm.str().data());
  return(RV_SUCCESS);
}

//
// psi_concat_atom3(list of atomic, separator, ariable)
// Join a list of atomic together to form a new atom separating
// each atom with separator
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_concat_atom3(Object *& object1, Object *& object2,
			 Object *& object3)
{
  ostringstream	strm;
  ostringstream	strm1;
  bool		firstatom = true;
  Object* val2 = heap.dereference(object2);
  
  if (val2->isAtom())
    {
      strm1 << OBJECT_CAST(Atom*, val2)->getName();
    }
  else if (val2->isNumber())
    {
      strm1 << val2->getInteger();
    }
  else if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  
  PrologValue pval1(object1);
  heap.prologValueDereference(pval1);

  while (pval1.getTerm()->isCons() && strm.good())
    {
      if (firstatom)
	{
	  firstatom = false;
	}
      else
	{
	  strm << strm1.str();
	}

      Cons* clist = OBJECT_CAST(Cons*, pval1.getTerm());
      Object* head = heap.dereference(clist->getHead());

      if (head->isAtom())
	{
	  strm << OBJECT_CAST(Atom*, head)->getName();
	}
      else if (head->isNumber())
	{
	  strm << head->getInteger();
	}
      else if (head->isSubstitution())
	{
	  PrologValue pvhead(pval1.getSubstitutionBlockList(), head);
	  heap.prologValueDereference(pvhead);
	  head = pvhead.getTerm();
	  if (head->isAtom())
	    {
	      strm << OBJECT_CAST(Atom*, head)->getName();
	    }
	  else if (head->isNumber())
	    {
	      strm << head->getInteger();
	    }
	  else
	    {
	      PSI_ERROR_RETURN(EV_TYPE, 1);
	    }
	}
      else
	{
	  PSI_ERROR_RETURN(EV_TYPE, 1);
	}
      pval1.setTerm(clist->getTail());
      heap.prologValueDereference(pval1);
     }

  if (pval1.getTerm()->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if(! pval1.getTerm()->isNil())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  
  strm << ends;

  object3 = atoms->add(strm.str().data());

  return(RV_SUCCESS);
}

//
// psi_atom_search(atom1, start, atom2, variable)
// Return the location with atom1 where atom2 is located.
// mode(in,in,in,out)
//
Thread::ReturnValue
Thread::psi_atom_search(Object *& object1, Object *& object2, 
			Object *& object3, Object *& object4)
{
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);
  Object* val3 = heap.dereference(object3);
  
  if (val1->isAtom() && val2->isShort() && val3->isAtom())
    {
      const char *string1 = OBJECT_CAST(Atom*, val1)->getName();
      const char *substring = strstr(string1 + val2->getInteger() - 1,
				     OBJECT_CAST(Atom*, val3)->getName());
      if (substring == NULL)
	{
	  return(RV_FAIL);
	}
      else
	{
	  object4 = heap.newInteger(static_cast<long>(strlen(string1) - strlen(substring)+1));
	  return(RV_SUCCESS);
	}
    }
  else if (val1->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  else if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  else if (val3->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 3);
    }
  else if (!val1->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  else if (!val2->isShort())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  else
    {
      PSI_ERROR_RETURN(EV_TYPE, 3);
    }
}

//
// psi_sub_atom(atom, start, length, variable)
// Return a new atom formed from the supplied atom.
// mode(in,in,in,out)
//
Thread::ReturnValue
Thread::psi_sub_atom(Object *& object1, Object *& object2, 
		     Object *& object3, Object *& object4)
{
  int32		length;

  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);
  Object* val3 = heap.dereference(object3);  
  Object* val4 = heap.dereference(object4);  
  
  assert(val1->isAtom());
  assert(val2->isShort());
  assert(val3->isShort());
  
  length = val3->getInteger();
  if (val4->isVariable()) {
    strncpy(atom_buf1,
	    OBJECT_CAST(Atom*, val1)->getName() + val2->getInteger() - 1, 
	    length);
    atom_buf1[length] = '\0';
    
    Object* sub_atom = atoms->add(atom_buf1);
    return BOOL_TO_RV(unify(sub_atom, val4));
  } else {
    const char *string1 = OBJECT_CAST(Atom*, val1)->getName() + 
      val2->getInteger() - 1;
    const char *string2 = OBJECT_CAST(Atom*, val4)->getName();
    return BOOL_TO_RV(strstr(string1, string2) == string1);
  }
}




