// regalloc.cc - Register allocation for compiler and all
// the following phases.
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
// $Id: regalloc.cc,v 1.10 2006/01/31 23:17:51 qp Exp $

#include "atom_table.h"
#include "heap_qp.h"
#include "compiler_support.h"

#include "thread_qp.h"
#include "pseudo_instr_arrays.h"

extern AtomTable *atoms;

//
// Equiv. to tempalloc in tempalloc.ql
//
void
Heap::alloc_registers(WordArray& life, xreglife& xregisters, 
		       WordArray& varregisters, bool& excess)
{
  for (int i = 0; i < life.lastEntry(); i++)
    {
      Object* term = reinterpret_cast<Object*>(life.Entries()[i])->variableDereference();

      if (term->isStructure() && OBJECT_CAST(Structure*, term)->getFunctor() == AtomTable::unify_ref)
	{
	  term = OBJECT_CAST(Structure*, term)->getArgument(1);
	}
      if (term->isVariable())
	{
	  Variable* var = OBJECT_CAST(Variable*, term);
	  assert(var->isLifeSet());
	  u_int varoffset = var->getLife();
	  int start = varregisters.Entries()[varoffset-1];
	  int end = varregisters.Entries()[varoffset];
	  if (start == end)
	    {
	      continue;
	    }
	  u_int reg;
	  for (reg = 0; reg < REGISTERSIZE; reg++)
	    {
	      if (reg == NUMBER_X_REGISTERS-1)
		{
		  continue;
		}
	      if (xregisters.addRange(reg, start, end))
		{
		  excess = excess || (reg >= NUMBER_X_REGISTERS);
		  Structure* xr = newStructure(1);
		  xr->setFunctor(AtomTable::xreg);
		  xr->setArgument(1, newInteger(reg));
		  *(var->storage()) = reinterpret_cast<heapobject>(xr);
		  break;
		}
	    }
	  if (reg == REGISTERSIZE)
	    {
	      Fatal(__FUNCTION__, "Cannot allocate a register");
	    }
	}
    }
}

//
// Equiv. to excess in excess.ql
// The arrays xmap and ymap are used for relocation.
//
Object*
Heap::excess_realloc_reg(Object* reg, int& currY, 
			 Object** xmap, Object** ymap)
{
  Object* result = reg;
  if (reg->isStructure())
    {
      qint64 r;
      if (OBJECT_CAST(Structure*, reg)->getFunctor() == AtomTable::unify_ref)
        {
          Structure* tstruct = OBJECT_CAST(Structure*, reg);
          Object* arg = tstruct->getArgument(1)->variableDereference();
          tstruct->setArgument(1, excess_realloc_reg(arg, currY, xmap, ymap));
          return tstruct;
         }
      else if (is_xreg(reg, r))
	{
	  if ((u_int)(r) >= NUMBER_X_REGISTERS)
	    {
	      if (xmap[r] == NULL)
		{
		  result = yreg(currY);
		  xmap[r] = result;
		  currY++;
		}
	      else
		{
		  result = xmap[r];
		}
	    }
	}
      else if (is_yreg(reg))
	{
	  int r = yreg_num(reg);
	  if (ymap[r] == NULL)
	    {
	      result = yreg(currY);
	      ymap[r] = result;
	      currY++;
	    }
	  else
	    {
	      result = ymap[r];
	    }
	}
    }
  return result;
}


void 
Heap::excess_registers(WordArray& instr)
{
  WordArray tmpinstr(WARRAYSIZE);
  Object* xmap[WARRAYSIZE];
  Object* ymap[WARRAYSIZE];
  int currY = 0;

  for (int i = 0; i < REGISTERSIZE; i++)
    {
      xmap[i] = NULL;
      ymap[i] = NULL;
    }
  for (int i = instr.lastEntry()-1; i >= 0; i--)
    {
      Structure* tstruct = OBJECT_CAST(Structure*, reinterpret_cast<Object*>(instr.Entries()[i])->variableDereference());

      for (u_int j = 1; j <= tstruct->getArity(); j++)
	{
	  Object* arg = tstruct->getArgument(j)->variableDereference();
	  tstruct->setArgument(j, excess_realloc_reg(arg, currY, xmap, ymap));
	}
      tmpinstr.addEntry(reinterpret_cast<wordptr>(tstruct));
    }
  // fix for excess xreg - add a put_y_variable(...) at the beginning
  // so all y regs are set before the first call in case garbage
  // collection happens
  Object* lastxreg = xreg(NUMBER_X_REGISTERS-1);
  for (int i = 0; i < REGISTERSIZE; i++) {
    if (xmap[i] != NULL) {
	      Structure* putinstr = newStructure(4);
	      putinstr->setFunctor(AtomTable::put);
	      putinstr->setArgument(1, AtomTable::meta);
	      putinstr->setArgument(2, AtomTable::variable);
	      putinstr->setArgument(3, xmap[i]);
	      putinstr->setArgument(4, lastxreg);
              tmpinstr.addEntry(reinterpret_cast<wordptr>(putinstr));
    }
  }
  instr.resetLast(0);
  for (int i = tmpinstr.lastEntry()-1; i >= 0; i--)
    {
      Structure* tstruct = OBJECT_CAST(Structure*, reinterpret_cast<Object*>(tmpinstr.Entries()[i])->variableDereference());
      Object* targlast = tstruct->getArgument(tstruct->getArity());
      if (!is_yreg(targlast))
	{
	  instr.addEntry(reinterpret_cast<wordptr>(tstruct));
	  continue;
	}
      if (tstruct->getFunctor() == AtomTable::put)
	{
	  if (i > 0)
	    {
	      Structure* nstruct = OBJECT_CAST(Structure*, reinterpret_cast<Object*>(tmpinstr.Entries()[i-1])->variableDereference());
	      if (nstruct->getFunctor() == AtomTable::put)
		{
		  Object* arg1 = nstruct->getArgument(1);
		  if (arg1 == AtomTable::substitution ||
		      arg1 == AtomTable::empty_substitution ||
		      arg1 == AtomTable::sub_term)
		    {
		      Object* narg4 = nstruct->getArgument(4);
		      if (equal_regs(targlast, narg4))
			{
			  tstruct->setArgument(4, lastxreg);
			  nstruct->setArgument(4, lastxreg);
			  instr.addEntry(reinterpret_cast<wordptr>(tstruct));
			  instr.addEntry(reinterpret_cast<wordptr>(nstruct));
			  Structure* getinstr = newStructure(4);
			  getinstr->setFunctor(AtomTable::get);
			  getinstr->setArgument(1, AtomTable::meta);
			  getinstr->setArgument(2, AtomTable::variable);
			  getinstr->setArgument(3, targlast);
			  getinstr->setArgument(4, lastxreg);
			  instr.addEntry(reinterpret_cast<wordptr>(getinstr));
			  i--;
			  continue;
			}
		    }
		}
	    }
	  Object* arg1 = tstruct->getArgument(1);
	  if (arg1 == AtomTable::substitution ||
	      arg1 == AtomTable::empty_substitution ||
	      arg1 == AtomTable::sub_term)
	    {
	      Structure* putinstr = newStructure(4);
	      putinstr->setFunctor(AtomTable::put);
	      putinstr->setArgument(1, AtomTable::meta);
	      putinstr->setArgument(2, AtomTable::value);
	      putinstr->setArgument(3, targlast);
	      putinstr->setArgument(4, lastxreg);
	      instr.addEntry(reinterpret_cast<wordptr>(putinstr));
	      tstruct->setArgument(4, lastxreg);
	      instr.addEntry(reinterpret_cast<wordptr>(tstruct));
	      Structure* getinstr = newStructure(4);
	      getinstr->setFunctor(AtomTable::get);
	      getinstr->setArgument(1, AtomTable::meta);
	      getinstr->setArgument(2, AtomTable::variable);
	      getinstr->setArgument(3, targlast);
	      getinstr->setArgument(4, lastxreg);
	      instr.addEntry(reinterpret_cast<wordptr>(getinstr));
	    }
	  else
	    {
	      tstruct->setArgument(4, lastxreg);
	      instr.addEntry(reinterpret_cast<wordptr>(tstruct));
	      Structure* getinstr = newStructure(4);
	      getinstr->setFunctor(AtomTable::get);
	      getinstr->setArgument(1, AtomTable::meta);
	      getinstr->setArgument(2, AtomTable::variable);
	      getinstr->setArgument(3, targlast);
	      getinstr->setArgument(4, lastxreg);
	      instr.addEntry(reinterpret_cast<wordptr>(getinstr));
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::checkBinder)
	{
	  Structure* putinstr = newStructure(4);
	  putinstr->setFunctor(AtomTable::put);
	  putinstr->setArgument(1, AtomTable::meta);
	  putinstr->setArgument(2, AtomTable::value);
	  putinstr->setArgument(3, targlast);
	  putinstr->setArgument(4, lastxreg);
	  instr.addEntry(reinterpret_cast<wordptr>(putinstr));
	  tstruct->setArgument(1, lastxreg);
	  instr.addEntry(reinterpret_cast<wordptr>(tstruct));
	}
      else if (tstruct->getFunctor() == AtomTable::get)
	{
	  Structure* putinstr = newStructure(4);
	  putinstr->setFunctor(AtomTable::put);
	  putinstr->setArgument(1, AtomTable::meta);
	  putinstr->setArgument(2, AtomTable::value);
	  putinstr->setArgument(3, targlast);
	  putinstr->setArgument(4, lastxreg);
	  instr.addEntry(reinterpret_cast<wordptr>(putinstr));
	  tstruct->setArgument(4, lastxreg);
	  instr.addEntry(reinterpret_cast<wordptr>(tstruct));
	}
      else
	{
	  instr.addEntry(reinterpret_cast<wordptr>(tstruct));
	}
    }
}

//
// Equiv. to envsize in envsize.ql
//
void
Heap::envsize(WordArray& instr, int& size)
{
  size = 0;
  for (int i = instr.lastEntry()-1; i >= 0; i--)
    {
      Structure* tstruct = OBJECT_CAST(Structure*, reinterpret_cast<Object*>(instr.Entries()[i])->variableDereference());
      // overwrite with dereference
      instr.Entries()[i] = reinterpret_cast<wordptr>(tstruct);

      if (tstruct->getFunctor() == AtomTable::call_pred)
	{
	  assert(tstruct->getArgument(3)->variableDereference()->isVariable());
	  tstruct->setArgument(3, newInteger(size));
	}
      else if (tstruct->getFunctor() == AtomTable::ccut ||
	       tstruct->getFunctor() == AtomTable::cut_ancestor)
	{
	  Object* yr = tstruct->getArgument(1)->variableDereference();
	  tstruct->setArgument(1, yr);
	  if (!yr->isVariable())
	    {
	      int n = 
		1+yreg_num(yr);
	      if (n > size) size = n;
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::get ||
	       tstruct->getFunctor() == AtomTable::put)
	{
	  Object* arg = tstruct->getArgument(3)->variableDereference();
	  tstruct->setArgument(3, arg);
	  tstruct->setArgument(4, tstruct->getArgument(4)->variableDereference());
	  if (is_yreg(arg))
	    {
	      int n = 1+yreg_num(arg);
	      if (n > size) size = n;
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::unify ||
	       tstruct->getFunctor() == AtomTable::set)
	{
	  Object* arg = tstruct->getArgument(3)->variableDereference();
	  tstruct->setArgument(3, arg);
	  if (arg->isStructure())
	    {
	      Structure* reg = OBJECT_CAST(Structure*, arg);
	      if (reg->getFunctor() == AtomTable::unify_ref)
		{
		  assert(reg->getArgument(1)->variableDereference()->isStructure());
		  reg = OBJECT_CAST(Structure*, reg->getArgument(1)->variableDereference());
		  Structure* newinstr = newStructure(1);
		  newinstr->setFunctor(AtomTable::unify_ref);
		  newinstr->setArgument(1, reg);
		  instr.Entries()[i] = reinterpret_cast<wordptr>(newinstr);
		}
	      if (is_yreg(arg))
		{
		  int n = 1+yreg_num(reg);
		  if (n > size) size = n;
		}
	    }
	}
    }
}


//
// Equiv to voidalloc in voidalloc.ql
//
void
Heap::voidalloc(WordArray& instr, int size, WordArray& newinstr)
{
  for (int i = 0; i < instr.lastEntry(); i++)
    {
      assert(reinterpret_cast<Object*>(instr.Entries()[i])->isStructure());
      Structure* tstruct = OBJECT_CAST(Structure*, reinterpret_cast<Object*>(instr.Entries()[i]));
      
      if (tstruct->getFunctor() == AtomTable::psi_life)
	{
	  continue;
	}
      else if (tstruct->getFunctor() == AtomTable::get &&
	       tstruct->getArgument(1) == AtomTable::meta &&
	       (tstruct->getArgument(3)->variableDereference()->isVariable() ||
		tstruct->getArgument(4)->variableDereference()->isVariable()))
	{
	  continue;
	}
      else if (tstruct->getFunctor() == AtomTable::unify &&
	       tstruct->getArgument(1) == AtomTable::meta &&
	       tstruct->getArgument(3)->variableDereference()->isVariable())
	{
	  int voids = 1;
	  for (i++; i < instr.lastEntry(); i++)
	    {
	      assert(reinterpret_cast<Object*>(instr.Entries()[i])->isStructure());
	      Structure* vtstruct = OBJECT_CAST(Structure*, reinterpret_cast<Object*>(instr.Entries()[i]));

	      if (vtstruct->getFunctor() == AtomTable::unify &&
		  vtstruct->getArgument(1) == AtomTable::meta &&
		  vtstruct->getArgument(3)->variableDereference()->isVariable())
		{
		  voids++;
		}
	      else
		{
		  break;
		}
	    }
	  Structure* voidstr = newStructure(3);
	  voidstr->setFunctor(AtomTable::unify);
	  voidstr->setArgument(1, AtomTable::meta);
	  voidstr->setArgument(2, atoms->add("void"));
	  voidstr->setArgument(3, newInteger(voids));
	  newinstr.addEntry(reinterpret_cast<wordptr>(voidstr));
	  i--;
	  continue;
	}
      else if (tstruct->getFunctor() == AtomTable::set &&
	       tstruct->getArgument(3)->variableDereference()->isVariable())
	    {
	      Object* type = tstruct->getArgument(1);
	      int voids = 1;
	      for (i++; i < instr.lastEntry(); i++)
		{
		  assert(reinterpret_cast<Object*>(instr.Entries()[i])->isStructure());
		  Structure* vtstruct = OBJECT_CAST(Structure*, reinterpret_cast<Object*>(instr.Entries()[i]));

		  if (vtstruct->getFunctor() == AtomTable::set &&
		      vtstruct->getArgument(1) == type &&
		      vtstruct->getArgument(3)->variableDereference()->isVariable())
		    {
		      voids++;
		    }
		  else
		    {
		      break;
		    }
		}

	      Structure* voidstr = newStructure(3);
	      voidstr->setFunctor(AtomTable::set);
	      voidstr->setArgument(1, type);
	      voidstr->setArgument(2, atoms->add("void"));
	      voidstr->setArgument(3, newInteger(voids));
	      newinstr.addEntry(reinterpret_cast<wordptr>(voidstr));
	      i--;
	      continue;
	    }
	  else if (tstruct->getFunctor() == AtomTable::put &&
		   i < instr.lastEntry()-1 &&
		   OBJECT_CAST(Structure*, reinterpret_cast<Object*>(instr.Entries()[i+1]))->getFunctor() == AtomTable::piarg)
	    {
	      i++;
	      Object* a = tstruct->getArgument(3)->variableDereference();
	      Object* b = tstruct->getArgument(4)->variableDereference();
	      bool somevar = false;
	      if (b->isVariable())
		{
		  *(b->storage()) = reinterpret_cast<heapobject>(a);
		  b = a;
		  somevar = true;
		}
	      else if (a->isVariable())
		{
		  *(a->storage()) = reinterpret_cast<heapobject>(b);
		  a = b;
		  somevar = true;
		}
	      if (somevar || equal_regs(a, b))
		{
		  tstruct->setArgument(4, b);
		  tstruct->setArgument(3, a);
		  if (a->isVariable())
		    {
		      Structure* lastreg = newStructure(1);
		      lastreg->setFunctor(AtomTable::xreg);
		      lastreg->setArgument(1, newInteger(NUMBER_X_REGISTERS-1));
		      tstruct->setArgument(3, lastreg);
		      tstruct->setArgument(4, lastreg);
		      *(a->storage()) = reinterpret_cast<heapobject>(lastreg);
		      continue;
		    }
		  else if (tstruct->getArgument(2) != AtomTable::variable)
		    {
		      continue;
		    }
		}
	    }
       else if (tstruct->getFunctor() == AtomTable::get)
	 {
	   if (tstruct->getArgument(2) == AtomTable::variable)
	     {
	       Object* a = tstruct->getArgument(3)->variableDereference();
	       Object* b = tstruct->getArgument(4)->variableDereference();
	       if (a->isVariable())
		 {
		   *(a->storage()) = reinterpret_cast<heapobject>(b);
		   a = b;
		 }
	       else if (b->isVariable())
		 {
		   *(b->storage()) = reinterpret_cast<heapobject>(a);
		   b = a;
		 }
	       tstruct->setArgument(3, a);
	       tstruct->setArgument(4, b);
	       if (a->isVariable())
		 {
		  Structure* lastreg = newStructure(1);
		  lastreg->setFunctor(AtomTable::xreg);
		  lastreg->setArgument(1, newInteger(NUMBER_X_REGISTERS-1));
		  *(a->storage()) = reinterpret_cast<heapobject>(lastreg);
		  a = lastreg;
		  tstruct->setArgument(3, lastreg);
		  tstruct->setArgument(4, lastreg);
		 }
	     }
	   else if (tstruct->getArgument(4)->variableDereference()->isVariable())
	     {
	       Structure* lastreg = newStructure(1);
	       lastreg->setFunctor(AtomTable::xreg);
	       lastreg->setArgument(1, newInteger(NUMBER_X_REGISTERS-1));
	       *(tstruct->getArgument(4)->variableDereference()->storage()) = reinterpret_cast<heapobject>(lastreg);
	       tstruct->setArgument(4, lastreg);
	     }
	 }
       else if (tstruct->getFunctor() == AtomTable::put)
	 {
	   if (tstruct->getArgument(2) == AtomTable::variable)
	     {
	       Object* a = tstruct->getArgument(3)->variableDereference();
	       Object* b = tstruct->getArgument(4)->variableDereference();
	       if (a->isVariable())
		 {
		   *(a->storage()) = reinterpret_cast<heapobject>(b);
		   a = b;
		 }
	       else if (b->isVariable())
		 {
		   *(b->storage()) = reinterpret_cast<heapobject>(a);
		   b = a;
		 }
	       tstruct->setArgument(3, a);
	       tstruct->setArgument(4, b);
	       if (a->isVariable())
		 {
		  Structure* lastreg = newStructure(1);
		  lastreg->setFunctor(AtomTable::xreg);
		  lastreg->setArgument(1, newInteger(NUMBER_X_REGISTERS-1));
		  *(a->storage()) = reinterpret_cast<heapobject>(lastreg);
		  a = lastreg;
		  tstruct->setArgument(3, a);
		  tstruct->setArgument(4, a);
		 }
	     }
	   else if (tstruct->getArgument(4)->variableDereference()->isVariable())
	     {
	       Structure* lastreg = newStructure(1);
	       lastreg->setFunctor(AtomTable::xreg);
	       lastreg->setArgument(1, newInteger(NUMBER_X_REGISTERS-1));
	       *(tstruct->getArgument(4)->variableDereference()->storage()) = reinterpret_cast<heapobject>(lastreg);
	       tstruct->setArgument(4, lastreg);
	     }
	 }
      newinstr.addEntry(reinterpret_cast<wordptr>(tstruct));
    }
}
	   
//
// Equiv. to assn_elim in assn_elim.ql
//
void
Heap::assn_elim(WordArray& ecode, WordArray& acode)
{
  Object* xreg_life[NUMBER_X_REGISTERS];
  init_live(xreg_life);
  for (int i = 0; i < ecode.lastEntry(); i++)
    {
      assert(reinterpret_cast<Object*>(ecode.Entries()[i])->isStructure());
      Structure* tstruct = OBJECT_CAST(Structure*, reinterpret_cast<Object*>(ecode.Entries()[i]));

      if (tstruct->getFunctor() == AtomTable::call_pred)
	{
	  init_live(xreg_life);
	  acode.addEntry(reinterpret_cast<wordptr>(tstruct));
	}
      else if (tstruct->getFunctor() == AtomTable::get)
	{
	  if (tstruct->getArgument(1) == AtomTable::meta &&
	      tstruct->getArgument(2) == AtomTable::variable)
	    {
	      Object* arg3 = tstruct->getArgument(3)->variableDereference();
	      Object* arg4 = tstruct->getArgument(4)->variableDereference();
	      assert(arg3->isStructure());
	      assert(arg4->isStructure());
	      qint64 regno;
	      if (is_xreg(arg4, regno) && regno != NUMBER_X_REGISTERS-1 &&
		  is_yreg(arg3))
		{
		  make_live(arg4, arg3, xreg_life);
		  acode.addEntry(reinterpret_cast<wordptr>(tstruct));
		}
	      else if (is_xreg(arg3, regno))
		{
                  reverse_make_dead(arg3, xreg_life);
		  make_live(arg3, arg4, xreg_life);
		  if (any_assoc_putset(arg3, i+1, ecode))
		    {
		      acode.addEntry(reinterpret_cast<wordptr>(tstruct));
		    }
		}
	      else
		{
		  make_dead(arg4, xreg_life);
		  acode.addEntry(reinterpret_cast<wordptr>(tstruct));
		} 
	    }
	  else if (tstruct->getArgument(1) == AtomTable::meta)
	    {
	      Object* arg4 = tstruct->getArgument(4)->variableDereference();
	      make_dead(arg4, xreg_life);
	      acode.addEntry(reinterpret_cast<wordptr>(tstruct));
	    }
	  else if (tstruct->getArgument(1) == AtomTable::object)
	    {
	      Object* arg3 = tstruct->getArgument(3)->variableDereference();
	      Object* arg4 = tstruct->getArgument(4)->variableDereference();
	      make_dead(arg3, xreg_life);
	      make_dead(arg4, xreg_life);
	      acode.addEntry(reinterpret_cast<wordptr>(tstruct));
	    }
	  else
	    {     
	      acode.addEntry(reinterpret_cast<wordptr>(tstruct));
	    }

	}
      else if (tstruct->getFunctor() == AtomTable::put)
	{
	  if (tstruct->getArgument(1) == AtomTable::substitution ||
	      tstruct->getArgument(1) == AtomTable::empty_substitution ||
	      tstruct->getArgument(1) == AtomTable::sub_term)
	    {
	      acode.addEntry(reinterpret_cast<wordptr>(tstruct));
	    }
	  else if (tstruct->getArgument(1) == AtomTable::meta &&
	      tstruct->getArgument(2) == AtomTable::variable)
	    {
	      Object* arg3 = tstruct->getArgument(3)->variableDereference();
	      Object* arg4 = tstruct->getArgument(4)->variableDereference();
	      if (equal_regs(arg3, arg4) && i+1 < ecode.lastEntry())
		{
		  assert(reinterpret_cast<Object*>(ecode.Entries()[i+1])->isStructure());
		  Structure* nstruct = OBJECT_CAST(Structure*, reinterpret_cast<Object*>(ecode.Entries()[i+1]));
                  Object* fun = nstruct->getFunctor();
		  if (nstruct->getArity() == 4 &&
                      (fun == AtomTable::put || fun == AtomTable::get) &&
		      equal_regs(arg3, nstruct->getArgument(4)->variableDereference()))
		    {
		      acode.addEntry(reinterpret_cast<wordptr>(tstruct));
		    }
		  else
		    {
		      make_dead(arg3, xreg_life);
		      make_dead(arg4, xreg_life);
		      acode.addEntry(reinterpret_cast<wordptr>(tstruct));
		    }
		}
	      else
		{
		  make_dead(arg3, xreg_life);
		  make_dead(arg4, xreg_life);
		  acode.addEntry(reinterpret_cast<wordptr>(tstruct));
		}
	    } 
	  else if (tstruct->getArgument(1) == AtomTable::meta &&
	      tstruct->getArgument(2) == AtomTable::value)
	    {
	      Object* arg3 = tstruct->getArgument(3)->variableDereference();
	      Object* arg4 = tstruct->getArgument(4)->variableDereference();
	      
	      assert(arg3->isStructure());
	      assert(arg4->isStructure());
	      qint64 reg;
	      if (is_xreg(arg4, reg) && is_yreg(arg3) &&
		  is_live(arg4, arg3, xreg_life))
		{
		  continue;
		}
	      else if (is_xreg(arg4, reg))
		{
		  if (is_live(arg4, AtomTable::failure, xreg_life))
		    {
		      acode.addEntry(reinterpret_cast<wordptr>(tstruct));
		    }
		  else if (is_live(arg4, arg3, xreg_life))
		    {
		      continue;
		    }
		  else if (equal_regs(arg3, arg4))
		    {
		      acode.addEntry(reinterpret_cast<wordptr>(tstruct));
		    }
		  else
		    {
		      make_dead(arg4, xreg_life);
		      acode.addEntry(reinterpret_cast<wordptr>(tstruct));
		    }
		}
	      else
		{
		  make_dead(arg3, xreg_life);
		  make_dead(arg4, xreg_life);
		  acode.addEntry(reinterpret_cast<wordptr>(tstruct));
		}
	    }
	  else
	    {
	      Object* arg3 = tstruct->getArgument(3)->variableDereference();
	      Object* arg4 = tstruct->getArgument(4)->variableDereference();
	      make_dead(arg3, xreg_life);
	      make_dead(arg4, xreg_life);
	      acode.addEntry(reinterpret_cast<wordptr>(tstruct));
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::unify)
	{
	  if (tstruct->getArgument(1) == AtomTable::meta &&
	      tstruct->getArgument(2) == AtomTable::variable)
	    {
	      Object* arg3 = tstruct->getArgument(3)->variableDereference();
	      qint64 reg;
	      if (is_xreg(arg3, reg))
		{
		  Structure* other = newStructure(1);
		  other->setFunctor(AtomTable::xreg);
		  other->setArgument(1, atoms->add("nowhere"));
		  make_live(arg3, other, xreg_life);
		  acode.addEntry(reinterpret_cast<wordptr>(tstruct));
		}
	      else
		{
		  acode.addEntry(reinterpret_cast<wordptr>(tstruct));
		}
	    }
	  else
	    {
	      acode.addEntry(reinterpret_cast<wordptr>(tstruct));
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::set)
	{
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  Object* arg2 = tstruct->getArgument(2)->variableDereference();
	  qint64 reg;
	  if (arg1 == AtomTable::meta &&
	      arg2 == AtomTable::value &&
	      is_xreg(tstruct->getArgument(3)->variableDereference(), reg))
	    {
	      
	      acode.addEntry(reinterpret_cast<wordptr>(tstruct));
	    }
	  else
	    {
	      make_dead(tstruct->getArgument(3)->variableDereference(), 
			xreg_life);
	      acode.addEntry(reinterpret_cast<wordptr>(tstruct));
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::unify_ref)
	{
	  Object* arg = tstruct->getArgument(1)->variableDereference();
	  Structure* other = newStructure(1);
	  other->setFunctor(AtomTable::xreg);
	  other->setArgument(1, atoms->add("nowhere"));
	  make_live(arg, other, xreg_life);
	  acode.addEntry(reinterpret_cast<wordptr>(tstruct));
	}
      else if (tstruct->getFunctor() == AtomTable::cpseudo_instr1)
	{
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  assert(arg1->isInteger());
	  int m = pseudo_instr1_array[arg1->getInteger()].mode;
	  if (m & 1)
	    {
	      make_pseudo_dead(tstruct->getArgument(2)->variableDereference(), 
			xreg_life);
	    }
	  acode.addEntry(reinterpret_cast<wordptr>(tstruct));
	}
      else if (tstruct->getFunctor() == AtomTable::cpseudo_instr2)
	{
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  assert(arg1->isInteger());
	  int m = pseudo_instr2_array[arg1->getInteger()].mode;
	  if (m & 2)
	    {
	      make_pseudo_dead(tstruct->getArgument(2)->variableDereference(), 
			xreg_life);
	    }
	  if (m & 1)
	    {
	      make_pseudo_dead(tstruct->getArgument(3)->variableDereference(), 
			xreg_life);
	    }
	  acode.addEntry(reinterpret_cast<wordptr>(tstruct));
	}
      else if (tstruct->getFunctor() == AtomTable::cpseudo_instr3)
	{
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  assert(arg1->isInteger());
	  int m = pseudo_instr3_array[arg1->getInteger()].mode;
	  if (m & 4)
	    {
	      make_pseudo_dead(tstruct->getArgument(2)->variableDereference(), 
			xreg_life);
	    }
	  if (m & 2)
	    {
	      make_pseudo_dead(tstruct->getArgument(3)->variableDereference(), 
			xreg_life);
	    }
	  if (m & 1)
	    {
	      make_pseudo_dead(tstruct->getArgument(4)->variableDereference(), 
			xreg_life);
	    }
	  acode.addEntry(reinterpret_cast<wordptr>(tstruct));
	}
      else if (tstruct->getFunctor() == AtomTable::cpseudo_instr4)
	{
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  assert(arg1->isInteger());
	  int m = pseudo_instr4_array[arg1->getInteger()].mode;
	  if (m & 8)
	    {
	      make_pseudo_dead(tstruct->getArgument(2)->variableDereference(), 
			xreg_life);
	    }
	  if (m & 4)
	    {
	      make_pseudo_dead(tstruct->getArgument(3)->variableDereference(), 
			xreg_life);
	    }
	  if (m & 2)
	    {
	      make_pseudo_dead(tstruct->getArgument(4)->variableDereference(), 
			xreg_life);
	    }
	  if (m & 1)
	    {
	      make_pseudo_dead(tstruct->getArgument(5)->variableDereference(), 
			xreg_life);
	    }
	  acode.addEntry(reinterpret_cast<wordptr>(tstruct));
	}
      else if (tstruct->getFunctor() == AtomTable::cpseudo_instr5)
	{
	  Object* arg1 = tstruct->getArgument(1)->variableDereference();
	  assert(arg1->isInteger());
	  int m = pseudo_instr5_array[arg1->getInteger()].mode;
	  if (m & 16)
	    {
	      make_pseudo_dead(tstruct->getArgument(2)->variableDereference(), 
			xreg_life);
	    }
	  if (m & 8)
	    {
	      make_pseudo_dead(tstruct->getArgument(3)->variableDereference(), 
			xreg_life);
	    }
	  if (m & 4)
	    {
	      make_pseudo_dead(tstruct->getArgument(4)->variableDereference(), 
			xreg_life);
	    }
	  if (m & 2)
	    {
	      make_pseudo_dead(tstruct->getArgument(5)->variableDereference(), 
			xreg_life);
	    }
	  if (m & 1)
	    {
	      make_pseudo_dead(tstruct->getArgument(6)->variableDereference(), 
			xreg_life);
	    }
	  acode.addEntry(reinterpret_cast<wordptr>(tstruct));
	}
      else
	{
	  acode.addEntry(reinterpret_cast<wordptr>(tstruct));
	}
    }
}

//
// Equiv. to peephole in peephole.ql
//
void
Heap::peephole(WordArray& acode, WordArray& final, int esize, bool isCompiled)
{

  bool alloc = false;
  for (int i = 0; i < acode.lastEntry(); i++)
    {
      assert(reinterpret_cast<Object*>(acode.Entries()[i])->isStructure());
      Structure* tstruct = OBJECT_CAST(Structure*, reinterpret_cast<Object*>(acode.Entries()[i]));
      
      if (tstruct->getFunctor() == AtomTable::call_pred &&
	  i == acode.lastEntry()-1)
	{
	  Structure* expred = newStructure(2);
	  expred->setFunctor(AtomTable::execute_pred);
	  expred->setArgument(1, tstruct->getArgument(1));
	  expred->setArgument(2, tstruct->getArgument(2));
	  if (alloc)
	    {
	      Structure* deall = newStructure(1);
	      deall->setFunctor(atoms->add("deallocate"));
	      deall->setArgument(1, AtomTable::nil);
	      final.addEntry(reinterpret_cast<wordptr>(deall));
	    }
	  final.addEntry(reinterpret_cast<wordptr>(expred));
	  return;
	}
      else if (tstruct->getFunctor() == AtomTable::get_level_ancestor)
	{
	  if (!alloc)
	    {
	      Structure* a = newStructure(1);
	      a->setFunctor(AtomTable::allocate);
	      a->setArgument(1, newInteger(esize));
	      final.addEntry(reinterpret_cast<wordptr>(a));
	      alloc = true;
	    }
	  final.addEntry(reinterpret_cast<wordptr>(tstruct));
	  Structure* nstruct = OBJECT_CAST(Structure*, reinterpret_cast<Object*>(acode.Entries()[i+1]));
	  if (nstruct->getFunctor() == AtomTable::get_level)
	    {
	      Object* a = tstruct->getArgument(1)->variableDereference();
	      Object* b = nstruct->getArgument(1)->variableDereference();
	      if (equal_regs(a, b))
		{
		  i++;
		}
	    }
	  continue;
	}
      else if (tstruct->getFunctor() == AtomTable::get_level &&
	       (i+1 < acode.lastEntry()))
	{
	  Structure* nstruct = OBJECT_CAST(Structure*, reinterpret_cast<Object*>(acode.Entries()[i+1]));
	  if (nstruct->getFunctor() == AtomTable::ccut)
	    {
	      assert(tstruct->getArgument(1)->variableDereference() ==
			   nstruct->getArgument(1)->variableDereference());
	      Structure* nc = newStructure(1);
	      nc->setFunctor(AtomTable::cneck_cut);
	      nc->setArgument(1,AtomTable::nil);
	      final.addEntry(reinterpret_cast<wordptr>(nc));
	      i++;
	    }
	  if (tstruct->getArgument(1)->variableDereference()->isStructure())
	    {
	      bool nomorecuts = true;
	      for (int j = i+1; j < acode.lastEntry(); j++)
		{
		  Structure* inst = OBJECT_CAST(Structure*, reinterpret_cast<Object*>(acode.Entries()[j]));
		  if (inst->getFunctor() == AtomTable::ccut)
		    {
		      nomorecuts = false;
		      break;
		    }
		}
	      if (nomorecuts)
		{
		  continue;
		}
	      if (!alloc)
		{
		  Structure* a = newStructure(1);
		  a->setFunctor(AtomTable::allocate);
		  a->setArgument(1, newInteger(esize));
		  final.addEntry(reinterpret_cast<wordptr>(a));
		  alloc = true;
		}
	      final.addEntry(reinterpret_cast<wordptr>(tstruct));
	      continue;
	    }
	  else
	    {
	      continue;
	    }
	}
      if (!alloc && alloc_needed(tstruct))
	{
	  Structure* a = newStructure(1);
	  a->setFunctor(AtomTable::allocate);
	  a->setArgument(1, newInteger(esize));
	  final.addEntry(reinterpret_cast<wordptr>(a));
	  alloc = true;
	}
      if (tstruct->getFunctor() == AtomTable::failure)
	{
	  final.addEntry(reinterpret_cast<wordptr>(tstruct));
	  return;
        }
      if (tstruct->getFunctor() == AtomTable::put)
	{
	  Object* t1 = tstruct->getArgument(1)->variableDereference();
	  Object* t2 = tstruct->getArgument(2)->variableDereference();
	  Object* reg1 = tstruct->getArgument(3)->variableDereference();
	  Object* reg2 = tstruct->getArgument(4)->variableDereference();
	  if (t1 == AtomTable::meta && t2 == AtomTable::variable &&
	      equal_regs(reg1, reg2) && i+1 < acode.lastEntry())
	    {
	      Structure* gstruct = OBJECT_CAST(Structure*, reinterpret_cast<Object*>(acode.Entries()[i+1]));
	      qint64 reg;
	      Object* nt1 = gstruct->getArgument(1)->variableDereference();
	      if (gstruct->getFunctor() == AtomTable::get &&
                  gstruct->getArgument(1)->variableDereference() 
                     != AtomTable::structure &&
                  gstruct->getArgument(1)->variableDereference() 
                     != AtomTable::list &&
		  equal_regs(gstruct->getArgument(4)->variableDereference(),
			     reg1) &&
		  is_xreg(reg1, reg) &&
		  t1 != AtomTable::structure &&
		  t1 != AtomTable::list)
		{
		  gstruct->setFunctor(AtomTable::put);
		  continue;
		}
	      else if (is_xreg(reg1, reg) &&
		       gstruct->getFunctor() == AtomTable::put &&
		       equal_regs(reg1, gstruct->getArgument(4)->variableDereference()) &&
		       nt1 != AtomTable::substitution &&
		       nt1 != AtomTable::empty_substitution &&
		       nt1 != AtomTable::sub_term &&
		       (nt1 != AtomTable::meta ||
			gstruct->getArgument(2)->variableDereference() != AtomTable::value ||
			!equal_regs(reg1, gstruct->getArgument(3)->variableDereference())))
		{
		  continue;
		}
	      else if (is_yreg(reg1))
		{
		  Structure* lastx = newStructure(1);
		  lastx->setFunctor(AtomTable::xreg);
		  lastx->setArgument(1, newInteger(NUMBER_X_REGISTERS-1));
		  tstruct->setArgument(4, lastx);
		  final.addEntry(reinterpret_cast<wordptr>(tstruct));
		  continue;
		}
	    }
	  else if (t2 == AtomTable::value && equal_regs(reg1, reg2))
	    {
	      continue;
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::checkBinder)
	{
	  Object* arg = tstruct->getArgument(1)->variableDereference();
	  assert(arg->isStructure());
	  if (is_yreg(arg))
	    {
	      Structure* lstr = newStructure(4);
	      Structure* lastx = newStructure(1);
	      lastx->setFunctor(AtomTable::xreg);
	      lastx->setArgument(1, newInteger(NUMBER_X_REGISTERS-1));
	      lstr->setFunctor(AtomTable::put);
	      lstr->setArgument(1, AtomTable::meta);
	      lstr->setArgument(2, AtomTable::value);
	      lstr->setArgument(3, arg);
	      lstr->setArgument(4, lastx);
	      final.addEntry(reinterpret_cast<wordptr>(lstr));
	      tstruct->setArgument(1, lastx);
	      final.addEntry(reinterpret_cast<wordptr>(tstruct));
	      continue;
	    }
	}
      else if (tstruct->getFunctor() == AtomTable::get)
	{
	  Object* t1 = tstruct->getArgument(1)->variableDereference();
	  Object* t2 = tstruct->getArgument(2)->variableDereference();
	  Object* arg1 = tstruct->getArgument(3)->variableDereference();
	  Object* arg2 = tstruct->getArgument(4)->variableDereference();
	  qint64 reg;
	  if ((t2 == AtomTable::value && equal_regs(arg1, arg2)) ||
	      (t1 == AtomTable::meta && t2 == AtomTable::variable &&
	      equal_regs(arg1, arg2) && is_xreg(arg1, reg)))
	    {
	      continue;
	    }
	}
      final.addEntry(reinterpret_cast<wordptr>(tstruct));
    }
  if (alloc)
    {
      Structure* deall = newStructure(1);
      deall->setFunctor(atoms->add("deallocate"));
      deall->setArgument(1, AtomTable::nil);
      final.addEntry(reinterpret_cast<wordptr>(deall));
    }
  Structure* pro = newStructure(1);
  pro->setFunctor(AtomTable::cproceed);
  pro->setArgument(1,AtomTable::nil);
  final.addEntry(reinterpret_cast<wordptr>(pro));
}

















