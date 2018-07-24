// unravel.cc - The unravel phase of the compiler
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
// $Id: unravel.cc,v 1.7 2006/01/31 23:17:52 qp Exp $

#include "atom_table.h"
#include "heap_qp.h"
#include "compiler_support.h"

extern AtomTable *atoms; 

//
// Assign Y registers to the perm vars.
//
void
Heap::setyregs(WordArray& perms, int num)
{
  num--;
  for (int i = 0; i < perms.lastEntry(); i++)
    {
      if (perms.Entries()[i] == 0)
	{
	  continue;
	}
      Object* head = reinterpret_cast<Object*>(perms.Entries()[i]);
      if (head->isVariable())
	{
	  *(head->storage()) = reinterpret_cast<heapobject>(yreg(num));
	}
      else
	{
	  assert(head->isObjectVariable());
	  assert(OBJECT_CAST(Reference*, head)->getName() != NULL);
	  Object* ref = reinterpret_cast<Object*>(*(OBJECT_CAST(Reference*, head)->getNameAddress()));
	  assert(ref->isVariable());
	  *(ref->storage()) = reinterpret_cast<heapobject>(yreg(num));
	}
      num--;
    }
}

//
// Create a Y register data structure  - the first arg is the
// register number, the second argument (init to fail) is used
// for lifetime calculations in assn_elim.
//
Object*
Heap::yreg(int i)
{
  Structure* xr = newStructure(2);
  xr->setFunctor(AtomTable::yreg);
  xr->setArgument(1, newInteger(i));
  xr->setArgument(2, AtomTable::failure);
  return (xr);
}

//
// Create a new x register structure and set the reg number.
//
Object*
Heap::xreg(int i)
{
  Structure* xr = newStructure(1);
  xr->setFunctor(AtomTable::xreg);
  xr->setArgument(1, newInteger(i));
  return (xr);
}

//
// Create a call_predicate data structure.
// call_predicate(Pred, Arity, Dealloc)
//
wordptr
Heap::callpred(Object* t1, int arity)
{
  Structure* s = newStructure(3);
  s->setFunctor(AtomTable::call_pred);
  s->setArgument(1, t1);
  s->setArgument(2, newInteger(arity));
  s->setArgument(3, newVariable());
  return(reinterpret_cast<wordptr>(s));
}

//
// Create a get of put data structure.
// put(meta, variable, R1, R2)
// put(meta, value, R1, R2)
// put(object, variable, R1, R2)
// put(object, value, R1, R2)
// put(constant, noarg, c, R)
// put(structure, ...)
// etc.
// and same with get
// NOTE: all structures have 4 args - some structures do not need 
// all args and in this case 'noarg' is used as a filler.
//
wordptr 
Heap::getput(Object* t1, Object* t2, bool get, WordArray& life)
{
  t1 = t1->variableDereference();
  t2 = t2->variableDereference();
  Structure* s = newStructure(4);
  if (get)
    {
      if (t1->isConstant())
	{
	  s->setFunctor(AtomTable::get);
	  s->setArgument(1, AtomTable::constant);
	  s->setArgument(2, AtomTable::noarg);
	  s->setArgument(3, t1);
	  if (t2->isVariable())
	    {
	      OBJECT_CAST(Reference*, t2)->setCollectedFlag();
	    }
	  s->setArgument(4, t2);
	  updateLife(life, t2);
	}
      else if (t1->isVariable())
	{
	  if (OBJECT_CAST(Reference*, t1)->isCollected())
	    {
	      if (OBJECT_CAST(Reference*, t1)->isPerm() && 
		  !OBJECT_CAST(Reference*, t2)->isCollected())
		{
		  OBJECT_CAST(Reference*, t2)->setCollectedFlag();
		  s->setFunctor(AtomTable::put);
		  s->setArgument(1, AtomTable::meta);
		  s->setArgument(2, AtomTable::value);
		  s->setArgument(3, t1);
		  s->setArgument(4, t2);
		  updateLife(life, t1);
		  updateLife(life, t2);
		}
	      else if (!OBJECT_CAST(Reference*, t2)->isCollected())
		{
		  OBJECT_CAST(Reference*, t2)->setCollectedFlag();
		  s->setFunctor(AtomTable::get);
		  s->setArgument(1,AtomTable::meta);
		  s->setArgument(2,AtomTable::variable);
		  s->setArgument(3, t2);
		  s->setArgument(4, t1);
		  updateLife(life, t1);
		  updateLife(life, t2);
		}
	      else
		{
		  s->setFunctor(AtomTable::get);
		  s->setArgument(1,AtomTable::meta);
		  s->setArgument(2,AtomTable::value);
		  s->setArgument(3, t1);
		  s->setArgument(4, t2);
		  updateLife(life, t2);
		  updateLife(life, t1);
		}
	    }
	  else
	    {
	      if (!OBJECT_CAST(Reference*, t2)->isCollected())
		{		 
		  s->setFunctor(AtomTable::put);
		  s->setArgument(1,AtomTable::meta);
		  s->setArgument(2,AtomTable::variable);
		  OBJECT_CAST(Reference*, t2)->setCollectedFlag();
		  updateLife(life, t1);
		  updateLife(life, t2);
		}
	      else
		{
		  s->setFunctor(AtomTable::get);
		  s->setArgument(1,AtomTable::meta);
		  s->setArgument(2,AtomTable::variable);
		  updateLife(life, t2);
		  updateLife(life, t1);
		}
	      OBJECT_CAST(Reference*, t1)->setCollectedFlag();
	      s->setArgument(3, t1);
	      s->setArgument(4, t2);
	    }
	}
      else if (t1->isObjectVariable())
	{
	  if (OBJECT_CAST(Reference*, t1)->getName() == NULL)
	    {
	      Object* newvar = newVariable();
	      OBJECT_CAST(Reference*, newvar)->setCollectedFlag();
	      *(OBJECT_CAST(Reference*, t1)->getNameAddress()) = 
		reinterpret_cast<heapobject>(newvar);

	      if (!OBJECT_CAST(Reference*, t2)->isCollected())
		{
		  s->setFunctor(AtomTable::put);
		  s->setArgument(1,AtomTable::object);
		  s->setArgument(2,AtomTable::variable);
		  OBJECT_CAST(Reference*, t2)->setCollectedFlag();
		  updateLife(life, newvar);
		  updateLife(life, t2);
		}
	      else
		{
		  s->setFunctor(AtomTable::get);
		  s->setArgument(1,AtomTable::object);
		  s->setArgument(2,AtomTable::variable);
		  updateLife(life, t2);
		  updateLife(life, newvar);
		}
	      s->setArgument(3, newvar);
	      s->setArgument(4, t2);
	    }
	  else
	    {
	      if (OBJECT_CAST(Reference*, t1)->isPerm() && 
		  !OBJECT_CAST(Reference*, t2)->isCollected())
		{
		  OBJECT_CAST(Reference*, t2)->setCollectedFlag();
		  s->setFunctor(AtomTable::put);
		  s->setArgument(1,AtomTable::object);
		  s->setArgument(2,AtomTable::value);
		  s->setArgument(3, reinterpret_cast<Object*>(*(OBJECT_CAST(Reference*, t1)->getNameAddress())));
		  s->setArgument(4, t2);
		  updateLife(life, reinterpret_cast<Object*>(*(OBJECT_CAST(Reference*, t1)->getNameAddress())));
		  updateLife(life, t2);
		}
	      else if (!OBJECT_CAST(Reference*, t2)->isCollected())
		{
		  OBJECT_CAST(Reference*, t2)->setCollectedFlag();
		  s->setFunctor(AtomTable::get);
		  s->setArgument(1,AtomTable::object);
		  s->setArgument(2,AtomTable::variable);
		  s->setArgument(3, t2);
		  s->setArgument(4, reinterpret_cast<Object*>(*(OBJECT_CAST(Reference*, t1)->getNameAddress())));
		  updateLife(life, reinterpret_cast<Object*>(*(OBJECT_CAST(Reference*, t1)->getNameAddress())));
		  updateLife(life, t2);
		}
	      else
		{
		  s->setFunctor(AtomTable::get);
		  s->setArgument(1,AtomTable::object);
		  s->setArgument(2,AtomTable::value);
		  s->setArgument(3, reinterpret_cast<Object*>(*(OBJECT_CAST(Reference*, t1)->getNameAddress())));
		  s->setArgument(4, t2);
		  updateLife(life, t2);
		  updateLife(life, reinterpret_cast<Object*>(*(OBJECT_CAST(Reference*, t1)->getNameAddress())));
		}
	    }
	}
      else
	{
	  assert(false);
	}
    }
  else
    {
      if (t1->isConstant())
	{
	  s->setFunctor(AtomTable::put);
	  s->setArgument(1, AtomTable::constant);
	  s->setArgument(2, AtomTable::noarg);
	  assert(t2->isVariable());
	  OBJECT_CAST(Reference*, t2)->setCollectedFlag();
	  s->setArgument(3, t1);
	  s->setArgument(4, t2);
	  updateLife(life, t2);
	}
      else if (t1->isVariable())
	{
	  assert(t2->isVariable());
	  if (OBJECT_CAST(Reference*, t1)->isCollected())
	    {
	      s->setFunctor(AtomTable::put);
	      s->setArgument(1, AtomTable::meta);
	      s->setArgument(2, AtomTable::value);
	    }
	  else
	    {
	      s->setFunctor(AtomTable::put);
	      s->setArgument(1, AtomTable::meta);
	      s->setArgument(2, AtomTable::variable);
	      OBJECT_CAST(Reference*, t1)->setCollectedFlag();
	    }
	  OBJECT_CAST(Reference*, t2)->setCollectedFlag();
	  s->setArgument(3, t1);
	  s->setArgument(4, t2);
	  updateLife(life, t1);
	  updateLife(life, t2);
	}
      else if (t1->isObjectVariable())
	{
	  assert(t2->isVariable());
	  if (OBJECT_CAST(Reference*, t1)->getName() == NULL)
	    {	     
	      s->setFunctor(AtomTable::put);
	      s->setArgument(1, AtomTable::object);
	      s->setArgument(2, AtomTable::variable);
	      Object* newvar = newVariable();
	      OBJECT_CAST(Reference*, newvar)->setCollectedFlag();
	      *(OBJECT_CAST(Reference*, t1)->getNameAddress()) = 
		reinterpret_cast<heapobject>(newvar);
	      s->setArgument(3, newvar);
	      s->setArgument(4, t2);
	      updateLife(life, newvar);
	      updateLife(life, t2);
	    }
	  else
	    {
	      s->setFunctor(AtomTable::put);
	      s->setArgument(1, AtomTable::object);
	      s->setArgument(2, AtomTable::value);
	      s->setArgument(3, reinterpret_cast<Object*>(*(OBJECT_CAST(Reference*, t1)->getNameAddress())));
	      s->setArgument(4, t2);
	      updateLife(life, reinterpret_cast<Object*>(*(OBJECT_CAST(Reference*, t1)->getNameAddress())));
	      updateLife(life, t2);
	    }
	  OBJECT_CAST(Reference*, t2)->setCollectedFlag();
	}
      else
	{
	  assert(false);
	}
    }
  return(reinterpret_cast<wordptr>(s));
}

//
// Create a unify or set structure.
// Similar to put/get.
//
wordptr 
Heap::unifyset(Object* t1, bool get, WordArray& life)
{
  t1 = t1->variableDereference();
  Structure* s = newStructure(3);
  if (get)
    {
      if (t1->isConstant())
	{
	  s->setFunctor(AtomTable::unify);
	  s->setArgument(1, AtomTable::constant);
	  s->setArgument(2, AtomTable::noarg);
	  s->setArgument(3, t1);
	}
      else if (t1->isVariable())
	{
	  if (OBJECT_CAST(Reference*, t1)->isCollected())
	    {
	      s->setFunctor(AtomTable::unify);
	      s->setArgument(1, AtomTable::meta);
	      s->setArgument(2, AtomTable::value);
	    }
	  else
	    {
	      s->setFunctor(AtomTable::unify);
	      s->setArgument(1, AtomTable::meta);
	      s->setArgument(2, AtomTable::variable);
	      OBJECT_CAST(Reference*, t1)->setCollectedFlag();
	    }
	  s->setArgument(3, t1);
	  updateLife(life, t1);
	}
      else if (t1->isObjectVariable())
	{
	  if (OBJECT_CAST(Reference*, t1)->getName() == NULL)
	    {
	      s->setFunctor(AtomTable::unify);
	      s->setArgument(1, AtomTable::object);
	      s->setArgument(2, AtomTable::variable);
	      Object* newvar = newVariable();
	      OBJECT_CAST(Reference*, newvar)->setCollectedFlag();
	      *(OBJECT_CAST(Reference*, t1)->getNameAddress()) = 
		reinterpret_cast<heapobject>(newvar);
	      s->setArgument(3, newvar);
	      updateLife(life, newvar);
	    }
	  else
	    {
	      s->setFunctor(AtomTable::unify);
	      s->setArgument(1, AtomTable::object);
	      s->setArgument(2, AtomTable::value);
	      s->setArgument(3, reinterpret_cast<Object*>(*(OBJECT_CAST(Reference*, t1)->getNameAddress())));
	      updateLife(life, reinterpret_cast<Object*>(*(OBJECT_CAST(Reference*, t1)->getNameAddress())));
	    }
	}
      else
	{
	  assert(false);
	}
    }
  else
    {
      if (t1->isConstant())
	{
	  s->setFunctor(AtomTable::set);
	  s->setArgument(1, AtomTable::constant);
	  s->setArgument(2, AtomTable::noarg);
	  s->setArgument(3, t1);
	}
      else if (t1->isVariable())
	{
	  if (OBJECT_CAST(Reference*, t1)->isCollected())
	    {	
	      s->setFunctor(AtomTable::set);
	      s->setArgument(1, AtomTable::meta);
	      s->setArgument(2, AtomTable::value);
	    }
	  else
	    {
	      s->setFunctor(AtomTable::set);
	      s->setArgument(1, AtomTable::meta);
	      s->setArgument(2, AtomTable::variable);
	      OBJECT_CAST(Reference*, t1)->setCollectedFlag();
	    }
	  s->setArgument(3, t1);
	  updateLife(life, t1);
	}
      else if (t1->isObjectVariable())
	{
	  if (OBJECT_CAST(Reference*, t1)->getName() == NULL)
	    {
	      s->setFunctor(AtomTable::set);
	      s->setArgument(1, AtomTable::object);
	      s->setArgument(2, AtomTable::variable);
	      Object* newvar = newVariable();
	      OBJECT_CAST(Reference*, newvar)->setCollectedFlag();
	      *(OBJECT_CAST(Reference*, t1)->getNameAddress()) = 
		reinterpret_cast<heapobject>(newvar);
	      s->setArgument(3, newvar);
	      updateLife(life, newvar);
	    }
	  else
	    {	     
	      s->setFunctor(AtomTable::set);
	      s->setArgument(1, AtomTable::object);
	      s->setArgument(2, AtomTable::value);
	      s->setArgument(3, reinterpret_cast<Object*>( *(OBJECT_CAST(Reference*, t1)->getNameAddress())));
	      updateLife(life, reinterpret_cast<Object*>( *(OBJECT_CAST(Reference*, t1)->getNameAddress())));
	    }
	}
      else
	{
	  assert(false);
	}
    }
  return(reinterpret_cast<wordptr>(s));
}

//
// Create a get/put list structure.
// Same as for get/put.
//
wordptr 
Heap::getputlist(Object* t1, bool get, WordArray& life)
{
  Structure* s = newStructure(4);
  if (get)
    {
      s->setFunctor(AtomTable::get);
      s->setArgument(1, AtomTable::list);
      s->setArgument(2, AtomTable::noarg);
      s->setArgument(3, AtomTable::noarg);
    }
  else
    {
      assert(t1->isVariable());
      OBJECT_CAST(Reference*, t1)->setCollectedFlag();
      s->setFunctor(AtomTable::put);
      s->setArgument(1, AtomTable::list);
      s->setArgument(2, AtomTable::noarg);
      s->setArgument(3, AtomTable::noarg);
    }
  s->setArgument(4, t1);
  updateLife(life, t1);
  return(reinterpret_cast<wordptr>(s));
}

//
// Create a get/put structure structure.
//
wordptr 
Heap::getputstruct(Object* t1, int arity, Object* t2, bool get, WordArray& life)
{
  if (get)
    {
      Structure* s = newStructure(4);
      s->setFunctor(AtomTable::get);
      s->setArgument(1, AtomTable::structure);
      s->setArgument(2, t1);
      s->setArgument(3, newInteger(arity));
      s->setArgument(4, t2);
      updateLife(life, t2);
      return(reinterpret_cast<wordptr>(s));
    }
  else
    {
      Structure* s = newStructure(4);
      s->setFunctor(AtomTable::put);
      s->setArgument(1, AtomTable::structure);
      s->setArgument(2, AtomTable::noarg);
      s->setArgument(3, newInteger(arity));
      s->setArgument(4, t2);
      assert(t2->isVariable());
      OBJECT_CAST(Reference*, t2)->setCollectedFlag();
      updateLife(life, t2);
      return(reinterpret_cast<wordptr>(s));
    }
}

//
// Create a get structure_frame structure
//
wordptr 
Heap::getstructframe(Object* t1, int arity, WordArray& life)
{
  Structure* s = newStructure(4);
  s->setFunctor(AtomTable::get);
  s->setArgument(1, AtomTable::structure_frame);
  s->setArgument(2, AtomTable::noarg);
  s->setArgument(3, newInteger(arity));
  s->setArgument(4, t1);
  updateLife(life, t1);
  return(reinterpret_cast<wordptr>(s));
}

//
// Create a put quant structure.
//
wordptr 
Heap::putquant(Object* t1, WordArray& life)
{
  Structure* s = newStructure(4);
  s->setFunctor(AtomTable::put);
  s->setArgument(1, AtomTable::quantifier);
  s->setArgument(2, AtomTable::noarg);
  s->setArgument(3, AtomTable::noarg);
  s->setArgument(4, t1);
  assert(t1->isVariable());
  OBJECT_CAST(Reference*, t1)->setCollectedFlag();
  updateLife(life, t1);
  return(reinterpret_cast<wordptr>(s));
}

// 
// Create a put sub structure.
//
wordptr 
Heap::putsub(Object* t1, int size, WordArray& life)
{
  Structure* s = newStructure(4);
  s->setFunctor(AtomTable::put);
  s->setArgument(1, AtomTable::substitution);
  s->setArgument(2, AtomTable::noarg);
  s->setArgument(3, newInteger(size));
  s->setArgument(4, t1);
  assert(t1->isVariable());
  OBJECT_CAST(Reference*, t1)->setCollectedFlag();
  updateLife(life, t1);
  return(reinterpret_cast<wordptr>(s));
}

//
// Create a put empty sub structure.
//
wordptr
Heap::putemptysub(Object* t1, WordArray& life)
{
  Structure* s = newStructure(4);
  s->setFunctor(AtomTable::put);
  s->setArgument(1, AtomTable::empty_substitution);
  s->setArgument(2, AtomTable::noarg);
  s->setArgument(3, AtomTable::noarg);
  s->setArgument(4, t1);
  assert(t1->isVariable());
  OBJECT_CAST(Reference*, t1)->setCollectedFlag();
  updateLife(life, t1);
  return(reinterpret_cast<wordptr>(s));
}

//
// Create a put sub term structure.
//
wordptr
Heap::putsubterm(Object* t1, Object* t2, WordArray& life)
{
  Structure* s = newStructure(4);
  s->setFunctor(AtomTable::put);
  s->setArgument(1, AtomTable::sub_term);
  s->setArgument(2, AtomTable::noarg);
  s->setArgument(3, t2);
  s->setArgument(4, t1);
  assert(t1->isVariable());
  OBJECT_CAST(Reference*, t1)->setCollectedFlag();
  assert(t2->isVariable());
  OBJECT_CAST(Reference*, t2)->setCollectedFlag();
  updateLife(life, t2);
  updateLife(life, t1);
  return(reinterpret_cast<wordptr>(s));
}

// 
// Test to see if Prolog conjunct is a unification and
// if it is return the LHS and RHS.
//
bool
isUnif(Object* goal, Object*& lt, Object*& rt)
{
  goal = goal->variableDereference();
  if (!goal->isStructure())
    {
      return false;
    }
  Structure* goalstr = OBJECT_CAST(Structure*, goal);
  if (goalstr->getArity() == 2 && goalstr->getFunctor() == AtomTable::equal)
    {
      lt = goalstr->getArgument(1);
      rt = goalstr->getArgument(2);
      return true;
    }
  return false;
}

//
// Test if Prolog code is a '$piarg' structure and if so
// return arguments.
//
bool
is_piarg(Object* goal, Object*& x, Object*& y)
{
  goal = goal->variableDereference();
  if (!goal->isStructure())
    {
      return false;
    }
  Structure* goalstr = OBJECT_CAST(Structure*, goal);
  if (goalstr->getArity() == 2 && 
      goalstr->getFunctor() == AtomTable::piarg)
    {
      x = goalstr->getArgument(1);
      y = goalstr->getArgument(2);
      return true;
    }
  return false;
}

//
// DITTO '$pieq' 
//
bool
is_pieq(Object* goal, Object*& x)
{
  goal = goal->variableDereference();
  if (!goal->isStructure())
    {
      return false;
    }
  Structure* goalstr = OBJECT_CAST(Structure*, goal);
  if (goalstr->getArity() == 1 && goalstr->getFunctor() == AtomTable::pieq)
    {
      x = goalstr->getArgument(1);
      return true;
    }
  return false;
}

//
// Test if goal is an "escape_builtin"
//
bool
escape_builtin(Object* goal, WordArray& life)
{
  goal = goal->variableDereference();
  if (goal == AtomTable::success || goal == AtomTable::failure)
    {
      return true;
    }
  if (!goal->isStructure())
    {
      return false;
    }
  if (OBJECT_CAST(Structure*, goal)->getArity() == 1)
    {
      Object* functor = OBJECT_CAST(Structure*, goal)->getFunctor();
      if (functor == AtomTable::get_level ||
	  functor == AtomTable::get_level_ancestor ||
	  functor == AtomTable::checkBinder ||
	  functor == AtomTable::psi_life)
	{
	  Object* t = OBJECT_CAST(Structure*, goal)->getArgument(1)->variableDereference();
	    assert(t->isVariable());
	    OBJECT_CAST(Reference*, t)->setCollectedFlag();
	    updateLife(life, t);
	    return true; 
	}
      return (functor == AtomTable::ccut ||
	      functor == AtomTable::cut_ancestor ||
	      functor == AtomTable::cpseudo_instr0 ||
	      functor == AtomTable::pieq);
    }
  if (OBJECT_CAST(Structure*, goal)->getArity() == 2)
    {
      Object* functor = OBJECT_CAST(Structure*, goal)->getFunctor();
      if (functor == AtomTable::cpseudo_instr1)
	{
	  Object* t = OBJECT_CAST(Structure*, goal)->getArgument(2)->variableDereference();
	  assert(t->isVariable());
	  OBJECT_CAST(Reference*, t)->setCollectedFlag();
	  return true;
	}
      return (functor == AtomTable::piarg);
    }
  if (OBJECT_CAST(Structure*, goal)->getArity() == 3 &&
      OBJECT_CAST(Structure*, goal)->getFunctor() == AtomTable::cpseudo_instr2)
    {
      for (int i = 2; i < 4; i++)
	{
      	  Object* t = OBJECT_CAST(Structure*, goal)->getArgument(i)->variableDereference();
	  assert(t->isVariable());
	  OBJECT_CAST(Reference*, t)->setCollectedFlag();
	}	 
      return true;
    }
  if (OBJECT_CAST(Structure*, goal)->getArity() == 4 &&
      OBJECT_CAST(Structure*, goal)->getFunctor() == AtomTable::cpseudo_instr3)
    {
      for (int i = 2; i < 5; i++)
	{
      	  Object* t = OBJECT_CAST(Structure*, goal)->getArgument(i)->variableDereference();
	  assert(t->isVariable());
	  OBJECT_CAST(Reference*, t)->setCollectedFlag();
	}	 
      return true;
    }

	  if (OBJECT_CAST(Structure*, goal)->getArity() == 5 &&
      OBJECT_CAST(Structure*, goal)->getFunctor() == AtomTable::cpseudo_instr4)
    {
      for (int i = 2; i < 6; i++)
	{
      	  Object* t = OBJECT_CAST(Structure*, goal)->getArgument(i)->variableDereference();
	  assert(t->isVariable());
	  OBJECT_CAST(Reference*, t)->setCollectedFlag();
	}	 
      return true;
    }
  if (OBJECT_CAST(Structure*, goal)->getArity() == 6 &&
      OBJECT_CAST(Structure*, goal)->getFunctor() == AtomTable::cpseudo_instr5)
    {
      for (int i = 2; i < 7; i++)
	{
      	  Object* t = OBJECT_CAST(Structure*, goal)->getArgument(i)->variableDereference();
	  assert(t->isVariable());
	  OBJECT_CAST(Reference*, t)->setCollectedFlag();
	}	 
      return true;
    }
  return false;
}

//
// Equiv to xputget in unravel.ql
//
void 
Heap::xputget(Object* put, Object* get, WordArray& unravelArray, WordArray& life)
{
  if (put->isConstant())
    {
      Object* tmp = newVariable();
      unravelArray.addEntry(getput(put, tmp, false, life));
      headArgSpread(get, tmp, unravelArray, life);
    }
  else if (get->isConstant())
    {
      Object* tmp = newVariable();
      unravelArray.addEntry(getput(put, tmp, false, life));
      unravelArray.addEntry(getput(get, tmp, true, life));
    }
  else
    {
      Object* tmp = newVariable();
      goalArgSpread(put, tmp, unravelArray, life);
      headArgSpread(get, tmp, unravelArray, life);
    }
}

//
// Equiv to varunify in unravel.ql
//
void
Heap::varunify(Object* a, Object* b, WordArray& unravelArray, WordArray& life)
{
  a = dereference(a);
  b = dereference(b);
  if (a == b)
    {
      return;
    }
  if (a->isVariable() && b->isVariable())
    {   
      if (OBJECT_CAST(Reference*, b)->isPerm())
	{
	  if (OBJECT_CAST(Reference*, a)->isPerm())
	    {
	      xputget(a, b, unravelArray, life);
	      return;
	    }
	  else
	    {
	      headArgSpread(b, a, unravelArray, life);
	      return;
	    }
	}
      else
	{
	  headArgSpread(a, b, unravelArray, life);
	  return;
	}
    }
  if (a->isVariable())
    {
      if ((b->isStructure() && OBJECT_CAST(Structure*, b)->getFunctor()->variableDereference()->isConstant()) || b->isCons())
	{
	  xputget(a, b, unravelArray, life);
          return;
	}
      if (b->isConstant() || b->isObjectVariable())
        {
	  if (OBJECT_CAST(Reference*,a)->isPerm())
	    {
	      xputget(a, b, unravelArray, life);
	    }
	  else
            {
              xputget(b, a, unravelArray, life);
	    }           
	  return;
	}
    }
  if (b->isVariable())
    {
      if ((a->isStructure() && OBJECT_CAST(Structure*, a)->getFunctor()->variableDereference()->isConstant()) || a->isCons())
	{
	  xputget(b, a, unravelArray, life);
          return;
	}
      if (a->isConstant() || a->isObjectVariable())
        {
          if (OBJECT_CAST(Reference*,b)->isPerm())
            {
              xputget(b, a, unravelArray, life);
            }
          else
            {
              xputget(a, b, unravelArray, life);
            }
          return;
        }                     
    }
  if (a->isStructure() && b->isStructure())
    {
      Structure* astruct = OBJECT_CAST(Structure*, a);
      Structure* bstruct = OBJECT_CAST(Structure*, b);
      Object* afun = astruct->getFunctor()->variableDereference();
      Object* bfun = bstruct->getFunctor()->variableDereference();
      u_int arity = static_cast<u_int>(astruct->getArity());
      if (arity != bstruct->getArity() ||
	  (afun->isAtom() && bfun->isAtom() && afun != bfun))
	{
          Structure* fstr = newStructure(1);
          fstr->setFunctor(AtomTable::failure);
          fstr->setArgument(1, AtomTable::failure);
	  unravelArray.addEntry(reinterpret_cast<wordptr>(fstr));
	  return;
	}
      varunify(afun, bfun, unravelArray, life);
      for (u_int i = 1; i <= arity; i++)
	{
	  varunify(astruct->getArgument(i),
		   bstruct->getArgument(i),
		   unravelArray, life);
	}
      return;
    }
  if (a->isCons() && b->isCons())
    {
      Cons* acons = OBJECT_CAST(Cons*, a);
      Cons* bcons = OBJECT_CAST(Cons*, b);
      varunify(acons->getHead(), bcons->getHead(), unravelArray, life);
      varunify(acons->getTail(), bcons->getTail(), unravelArray, life);
      return;
    }
  Object* tmp = newVariable();
  goalArgSpread(a, tmp, unravelArray, life);
  xputget(b, tmp, unravelArray, life);
}

//
// Equiv to sub_spread in unravel.ql
//
void
Heap::goalSubSpread(Object* oldarg, Object* newarg, WordArray& unravelArray, WordArray& life)
{
  Cons* sub = 
    OBJECT_CAST(Cons*,
		OBJECT_CAST(Substitution*, 
			    oldarg)->getSubstitutionBlockList());
  Object* term = OBJECT_CAST(Substitution*, oldarg)->getTerm();
  Object* zvar = newVariable();
  bool first = true;
  for(;sub->isCons();
      sub = OBJECT_CAST(Cons*, sub->getTail()->variableDereference()))
    {
      assert(sub->getHead()->isSubstitutionBlock());
      SubstitutionBlock* sblock = 
	OBJECT_CAST(SubstitutionBlock*, sub->getHead());
      int size = (int)(sblock->getSize());
      Object** args = new Object*[2*size+1];
      for (int i = 1; i <= size; i++)
	{
	  Object* newdom = newVariable();
	  goalStructSpread(sblock->getDomain(i), newdom, unravelArray, life);
	  Object* newran = newVariable();
	  goalStructSpread(sblock->getRange(i), newran, unravelArray, life);
	  args[2*i-1] = newdom;
	  args[2*i] = newran;
	}
      if (first)
	{
	  unravelArray.addEntry(putemptysub(zvar, life));
	  first = false;
	}
      unravelArray.addEntry(putsub(zvar, size, life));
      for (int i = 1; i <= size; i++)
	{
	  unravelArray.addEntry(unifyset(args[2*i-1], false, life));
	  unravelArray.addEntry(unifyset(args[2*i], false, life));
	}
      delete args;
    }
  if (term->isConstant() || term->isAnyVariable())
    {
      unravelArray.addEntry(getput(term, newarg, false, life));
      unravelArray.addEntry(putsubterm(newarg, zvar, life));
    }
  else
    {
      goalStructSpread(term, newarg, unravelArray, life);
      unravelArray.addEntry(putsubterm(newarg, zvar, life));
    }
}

//
// Equiv to goal_struct_spread in unravel.ql
//
void
Heap::goalStructSpread(Object* oldarg, Object* newarg, WordArray& unravelArray, WordArray& life)
{
  switch (oldarg->tTag())
    {
    case Object::tVar:
    case Object::tShort:
    case Object::tLong:
    case Object::tDouble:
    case Object::tAtom:
    case Object::tString:
    case Object::tObjVar:
      *(newarg->storage()) =
	reinterpret_cast<heapobject>(oldarg);
      break;
    case Object::tCons:
      {
	Cons* list = OBJECT_CAST(Cons*, oldarg);
	Object* head = newVariable();
	Object* tail = newVariable();
	goalStructSpread(list->getTail()->variableDereference(), 
			 tail, unravelArray, life);
	goalStructSpread(list->getHead()->variableDereference(), 
			 head, unravelArray, life);
	unravelArray.addEntry(getput(newarg, newarg, false, life));
	unravelArray.addEntry(getputlist(newarg, false, life));
	unravelArray.addEntry(unifyset(head, false, life));
	unravelArray.addEntry(unifyset(tail, false, life));
      }
      break;
    case Object::tStruct:
      {
	Structure* oldstr = OBJECT_CAST(Structure*, oldarg);
	u_int arity = static_cast<u_int>(oldstr->getArity());
	Object* newf = newVariable();
	Object* functor = oldstr->getFunctor()->variableDereference();
	
	goalStructSpread(functor, newf, unravelArray, life);
	Object** args = new Object*[arity];
	for (u_int i = 1; i <= arity; i++)
	  {
	    args[i-1] = newVariable();
	    goalStructSpread(oldstr->getArgument(i)->variableDereference(), 
			     args[i-1], unravelArray, life);
	  }
	unravelArray.addEntry(getput(newarg, newarg, false, life));
	unravelArray.addEntry(getputstruct(functor, arity, newarg, false, life));
	unravelArray.addEntry(unifyset(newf, false, life));
	for (u_int i = 1; i <= arity; i++)
	  {
	    unravelArray.addEntry(unifyset(args[i-1], false, life));
	  }
        delete args;
      }
      break;
    case Object::tQuant:
      {
	QuantifiedTerm* oldquant = OBJECT_CAST(QuantifiedTerm*, oldarg);
	Object* q = newVariable();
	Object* b = newVariable();
	goalStructSpread(oldquant->getQuantifier()->variableDereference(),
			 q, unravelArray, life);
	Object* bv = oldquant->getBoundVars()->variableDereference();
	if (bv->isNil())
	  {
	    goalStructSpread(oldquant->getBody()->variableDereference(),
			     b, unravelArray, life);
	    unravelArray.addEntry(getput(newarg, newarg, false, life));
	    unravelArray.addEntry(putquant(newarg, life));
	    unravelArray.addEntry(unifyset(q, false, life));
	    unravelArray.addEntry(unifyset(AtomTable::nil, false, life));
	    unravelArray.addEntry(unifyset(b, false, life));
	  }
	else
	  {
	    Object* newbv = newVariable();
	    goalStructSpread(bv, newbv, unravelArray, life);
	    goalStructSpread(oldquant->getBody()->variableDereference(),
			     b, unravelArray, life);
	    unravelArray.addEntry(getput(newarg, newarg, false, life));
	    unravelArray.addEntry(putquant(newarg, life));
	    unravelArray.addEntry(unifyset(q, false, life));
	    unravelArray.addEntry(unifyset(newbv, false, life));
	    unravelArray.addEntry(unifyset(b, false, life));

	    Structure* checkb = newStructure(1);
	    checkb->setFunctor(AtomTable::checkBinder);
	    checkb->setArgument(1, newbv);
	    unravelArray.addEntry(reinterpret_cast<wordptr>(checkb));
	    updateLife(life, newbv);
	  }
	    
      }
      break;
    case Object::tSubst:
      goalSubSpread(oldarg, newarg, unravelArray, life);
      break;
    default:
      assert(false);
      break;
    }
}

//
// Equiv to goal_arg_spread in unravel.ql
//
void
Heap::goalArgSpread(Object* oldarg, Object* newarg, WordArray& unravelArray, WordArray& life)
{
  switch (oldarg->tTag())
    {
    case Object::tShort:
    case Object::tLong:
    case Object::tDouble:
    case Object::tAtom:
    case Object::tString:
      *(newarg->storage()) =
	reinterpret_cast<heapobject>(oldarg);
      break;
    case Object::tVar:
    case Object::tObjVar:
      unravelArray.addEntry(getput(oldarg, newarg, false, life));
      break;
    case Object::tCons:
    case Object::tStruct:
    case Object::tQuant:
      goalStructSpread(oldarg, newarg, unravelArray, life);
      break;
    case Object::tSubst:
      goalSubSpread(oldarg, newarg, unravelArray, life);
      break;
    default:
      assert(false);
      break;
    }
}

//
// Equiv to head_struct_spread in unravel.ql
//
void
Heap::headStructSpread(Object* oldarg, Object* newarg, 
		       WordArray& unravelArray, bool atTop, WordArray& life)
{
  switch (oldarg->tTag())
    {
    case Object::tShort:
    case Object::tLong:
    case Object::tDouble:
    case Object::tAtom:
    case Object::tString:
    case Object::tVar:	   
      if (OBJECT_CAST(Reference*, newarg)->isCollected())
	{
	  OBJECT_CAST(Reference*, oldarg)->setCollectedFlag();
	}
      *(newarg->storage()) =
	reinterpret_cast<heapobject>(oldarg);
      break;
    case Object::tSubst:
      {
	Object* tmparg = newVariable();
	goalArgSpread(oldarg, tmparg, unravelArray, life);
	unravelArray.addEntry(getput(tmparg, newarg, true, life));
      }
      break;
    case Object::tObjVar:
      unravelArray.addEntry(getput(oldarg, newarg, true, life));
      break;
    case Object::tQuant:
      {
	Object* tmparg = newVariable();
	goalArgSpread(oldarg, tmparg, unravelArray, life);
	unravelArray.addEntry(getput(tmparg, newarg, true, life));
      }
      break;
    case Object::tCons:
      {
	Cons* oldlist = OBJECT_CAST(Cons*, oldarg);
	Object* tmparg = newVariable();
	if (atTop)
	  {
	    if (OBJECT_CAST(Reference*, newarg)->isCollected())
	      {
		OBJECT_CAST(Reference*, tmparg)->setCollectedFlag();
	      }
	    *(newarg->storage()) =
	      reinterpret_cast<heapobject>(tmparg);
	  }
	else
	  {
	    Structure* ur = newStructure(1);
	    ur->setFunctor(AtomTable::unify_ref);
	    ur->setArgument(1, tmparg);
	    *(newarg->storage()) =
	      reinterpret_cast<heapobject>(ur);
	  }
	Object* oldhead = oldlist->getHead()->variableDereference();
	Object* oldtail = oldlist->getTail()->variableDereference();
	Object* head = newVariable();
	Object* tail = newVariable();
	unravelArray.addEntry(getputlist(tmparg, true, life));
	if (oldhead->isConstant() || oldhead->isVariable())
	  {
	    unravelArray.addEntry(unifyset(oldhead, true, life));
	  }
	else
	  {
	    unravelArray.addEntry(unifyset(head, true, life));
	  }
	if (oldtail->isConstant() || oldtail->isVariable())
	  {
	    unravelArray.addEntry(unifyset(oldtail, true, life));
	  }
	else
	  {
	    unravelArray.addEntry(unifyset(tail, true, life));
	  }

	headStructSpread(oldhead, head, unravelArray, false, life);
	headStructSpread(oldtail, tail, unravelArray, false, life);
      }
      break;
    case Object::tStruct:
      {
	Structure* oldstruct = OBJECT_CAST(Structure*, oldarg);
	Object* tmparg = newVariable();
	if (atTop)
	  {
	    if (OBJECT_CAST(Reference*, newarg)->isCollected())
	      {
		OBJECT_CAST(Reference*, tmparg)->setCollectedFlag();
	      }
	    *(newarg->storage()) =
	      reinterpret_cast<heapobject>(tmparg);
	  }
	else
	  {
	    Structure* ur = newStructure(1);
	    ur->setFunctor(AtomTable::unify_ref);
	    ur->setArgument(1, tmparg);
	    *(newarg->storage()) =
	      reinterpret_cast<heapobject>(ur);
	  }
	int arity = static_cast<int>(oldstruct->getArity());
	Object* functor = oldstruct->getFunctor()->variableDereference();
	Object** args = new Object*[arity];
	Object* newf = newVariable();
	if (functor->isAtom())
	  {
	    unravelArray.addEntry(getputstruct(functor, arity, tmparg, true, life));
	  }
	else
	  {
	    unravelArray.addEntry(getstructframe(tmparg, arity, life));
	    if (functor->isVariable() || functor->isNumber())
	      {
		 unravelArray.addEntry(unifyset(functor, true, life));
	      }
	    else
	      {
		unravelArray.addEntry(unifyset(newf, true, life));
	      }
	  }
	
	for (int i = 1; i <= arity; i++)
	  {
	    args[i-1] = newVariable();
	    Object* old = oldstruct->getArgument(i)->variableDereference();
	    if (old->isConstant() || old->isVariable())
	      {
		unravelArray.addEntry(unifyset(old, true, life));
	      }
	    else
	      {
		unravelArray.addEntry(unifyset(args[i-1], true, life));
	      }
	  }
	if (!functor->isConstant())
	  {
	    headStructSpread(functor, newf, unravelArray, true, life);
	  }
	for (int i = 0; i < arity; i++)
	  {
	    headStructSpread(oldstruct->getArgument(i+1)->variableDereference(), args[i], unravelArray, false, life);
	  }
        delete args;
      }
      break;
    default:
      assert(false);
      break;
    }
}

//
// Equiv. to head_arg_spread in unravel.ql
//
void 
Heap::headArgSpread(Object* arg, Object* newarg, 
		    WordArray& wordArray, WordArray& life)
{
  if (arg->isVariable())
    {
      wordArray.addEntry(getput(arg, newarg, true, life));
    }
  else
    {
      headStructSpread(arg, newarg, wordArray, true, life);
    }
}

//
// Equiv. to unravel_head in unravel.ql
//
void
Heap::unravelHead(Object* head, WordArray& unravelArray, WordArray& life)
{
  if (head->isAtom())
    {
      Structure* start = newStructure(1);
      start->setFunctor(AtomTable::start);
      start->setArgument(1, newInteger(0));
      life.addEntry(reinterpret_cast<wordptr>(start));
      return;
    }

  assert(head->isStructure());

  Structure* headStr = OBJECT_CAST(Structure*, head);

  int arity = static_cast<int>(headStr->getArity());
  Structure* start = newStructure(1);
  start->setFunctor(AtomTable::start);
  start->setArgument(1, newInteger(arity));
  life.addEntry(reinterpret_cast<wordptr>(start));

  for (int i = 1; i <= arity; i++)
    { 
      Object* oldarg = headStr->getArgument(i)->variableDereference();
      if (oldarg->isConstant())
	{
	  unravelArray.addEntry(getput(oldarg, xreg(i-1), true, life));
	}
    }
  for (int i = 1; i <= arity; i++)
    { 
      Object* oldarg = headStr->getArgument(i)->variableDereference();
      if (!oldarg->isConstant())
	{
	  Object* newarg = newVariable();
	  OBJECT_CAST(Reference*, newarg)->setCollectedFlag();
	  headArgSpread(oldarg, newarg, unravelArray, life);
	  newarg = newarg->variableDereference();
	  *(newarg->storage()) =
	    reinterpret_cast<heapobject>(xreg(i-1));
	}
    }
}

//
// Equiv. to goal_spread in unravel.ql
//
void
Heap::goalSpread(Object* goal, WordArray& unravelArray, WordArray& life)
{
  Object *x, *y;
  if (is_piarg(goal, x, y))
    {
      unravelArray.addEntry(getput(x, y, false, life));
      unravelArray.addEntry(reinterpret_cast<wordptr>(goal));
    }
  else if (is_pieq(goal, x))
    {
      unravelArray.addEntry(getput(x, x, false, life));
    }
  else if (goal == AtomTable::failure)
    {
      Structure* fstr = newStructure(1);
      fstr->setFunctor(AtomTable::failure);
      fstr->setArgument(1, AtomTable::failure);
      unravelArray.addEntry(reinterpret_cast<wordptr>(fstr)); 
    }
  else if (escape_builtin(goal, life))
    {
      unravelArray.addEntry(reinterpret_cast<wordptr>(goal));
    }
  else if (goal->isConstant())
    {
      unravelArray.addEntry(callpred(goal, 0));
      life.addEntry(reinterpret_cast<wordptr>(newInteger(0)));
    }
  else
    {
      assert(goal->isStructure());
      Structure* goalstr = OBJECT_CAST(Structure*, goal);
      int arity = static_cast<int>(goalstr->getArity());
      for (int i = 1; i <= arity; i++)
	{
	  Object* oldarg = goalstr->getArgument(i)->variableDereference();
	  Object* arg = newVariable();
	  if (oldarg->isConstant())
	    {
	      continue;
	    }
	  else
	    {
	      goalArgSpread(oldarg, arg, unravelArray, life);
	    }
	  arg = arg->variableDereference();
	  *(arg->storage()) =
	    reinterpret_cast<heapobject>(xreg(i-1));
	}
      for (int i = 1; i <= arity; i++)
	{
	  Object* oldarg = goalstr->getArgument(i)->variableDereference();
	  Object* arg = newVariable();
	  if (oldarg->isConstant())
	    {
	      unravelArray.addEntry(getput(oldarg, arg, false, life));
	      arg = arg->variableDereference();
	      *(arg->storage()) =
		reinterpret_cast<heapobject>(xreg(i-1));
	    }
	}
      unravelArray.addEntry(callpred(goalstr->getFunctor(), arity));
      life.addEntry(reinterpret_cast<wordptr>(newInteger(arity)));
    }
}

//
// Equiv. to unravel_body in unravel.ql
//
void
Heap::unravelBody(Object* body, WordArray& unravelArray, WordArray& life)
{
  for (; body->isCons(); 
       body = OBJECT_CAST(Cons*, body)->getTail()->variableDereference())
    {
      Object* goal = 
	OBJECT_CAST(Cons*, body)->getHead()->variableDereference();

      if (goal == AtomTable::success)
	{
	  continue;
	}
      Object *lt, *rt;
      if (isUnif(goal, lt, rt))
	{
	  lt = dereference(lt);
	  rt = dereference(rt);
	  if (lt->isConstant() && rt->isSubstitution() &&
	      OBJECT_CAST(Substitution*, rt)->getTerm()->isAnyVariable())
	    {
	      Object* tmp = newVariable();
	      varunify(tmp, lt, unravelArray, life);
	      varunify(tmp, rt, unravelArray, life);
	    }
	  else if (rt->isConstant() && lt->isSubstitution() &&
	      OBJECT_CAST(Substitution*, lt)->getTerm()->isAnyVariable())
	    {
	      Object* tmp = newVariable();
	      varunify(tmp, rt, unravelArray, life);
	      varunify(tmp, lt, unravelArray, life);
	    }
	  else
	    {
	      varunify(lt, rt, unravelArray, life);
	    }
	}
      else
	{
	  goalSpread(goal, unravelArray, life);
	}
    }
}

//
// Equiv. to unravel in unravel.ql
//
void
Heap::unravel(Object* clause, WordArray& unravelArray, WordArray& life, 
	      int& bodystart)
{
  clause = clause->variableDereference();
  assert(clause->isCons());
  Object* head = OBJECT_CAST(Cons*, clause)->getHead()->variableDereference();
  unravelHead(head, unravelArray, life);
  Object* body = OBJECT_CAST(Cons*, clause)->getTail()->variableDereference();
  bodystart = unravelArray.lastEntry();
  unravelBody(body, unravelArray, life);
}






