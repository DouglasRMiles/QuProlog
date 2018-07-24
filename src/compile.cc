// compile.cc - A C++ version of the QP compiler
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
// $Id: compile.cc,v 1.10 2006/01/31 23:17:49 qp Exp $

#include "thread_qp.h"
#include "io_qp.h"
#include "check.h"
extern IOManager *iom;  
extern AtomTable *atoms;

//
// Add the vars in the tmp list to the word array containing perms
// and update the number of perms.
//
void addPerms(Object* tmp, WordArray& perms, int& numys)
{
  for (; tmp->isCons(); tmp = OBJECT_CAST(Cons*, tmp)->getTail())
    {
      Reference* arg = 
	OBJECT_CAST(Reference*, OBJECT_CAST(Cons*, tmp)->getHead());
      if (!arg->isPerm())
	{
	  numys++;
	  perms.addEntry(reinterpret_cast<wordptr>(arg));
	  arg->setPermFlag();
	}
      else
	{
	  for (int i = 0; i < perms.lastEntry(); i++)
	    {
	      if (reinterpret_cast<wordptr>(arg) == perms.Entries()[i])
		{
		  perms.Entries()[i] = 0;
		  break;
		}
	    }
	  perms.addEntry(reinterpret_cast<wordptr>(arg));
	}
    }
}

bool in_neck_vars(Object* perm_var, Object* neck_vars)
{
  perm_var = perm_var->variableDereference();
  while(true)
    {
      assert(neck_vars != NULL);
      neck_vars = neck_vars->variableDereference();
      if (!neck_vars->isCons()) return false;
      Cons* listptr = OBJECT_CAST(Cons*, neck_vars);
      if (perm_var == listptr->getHead()->variableDereference()) return true;
      neck_vars = listptr->getTail();
    }
  return false;
}

//
// Calculate the perm vars - a C++ version of permvars.ql
//
// As part of this calculation we need to make sure all y registers will get 
// initialised before the first goal. This is because the garbage collector
// requires this.
// To do this we find all the permanent variables that are not mentioned
// between the head and first "real" body goal (inclusively). For those
// variables we add unifications of those variables to new variables just
// before the first goal. These unifications will be compiled into
// PUT_Y_VARIABLE instructions by later phases of the compiler.
//
void
Thread::permvars(Object* clause, WordArray& perms, int& numys)
{
  Object* half = AtomTable::nil;
  Object* vars = AtomTable::nil;
  Object* neck_vars = AtomTable::nil;
  bool body_goal_found = false;
  Object* previous;
  Object* goal_ptr;
  Object* rest_ptr;

  numys = 0;
  assert(clause->isCons());
  Object* head = OBJECT_CAST(Cons*, clause)->getHead()->variableDereference();
  clause = OBJECT_CAST(Cons*, clause)->getTail()->variableDereference();
  heap.collect_term_vars(head, vars);

  for (previous = clause; clause->isCons(); 
       previous = clause, clause = OBJECT_CAST(Cons*, clause)->getTail()->variableDereference())
    {
      Object* a = OBJECT_CAST(Cons*, clause)->getHead()->variableDereference();
      if (a->isStructure() && 
	  (OBJECT_CAST(Structure*, a)->getFunctor() == AtomTable::get_level_ancestor ||
	  OBJECT_CAST(Structure*, a)->getFunctor() == AtomTable::cut_ancestor))
	{
	  assert(OBJECT_CAST(Structure*, a)->getArgument(1)->variableDereference()->isAnyVariable());
	  Reference* arg = 
	    OBJECT_CAST(Reference*, OBJECT_CAST(Structure*, a)->getArgument(1)->variableDereference());

	  heap.collect_term_vars(a, vars);
	  if (!arg->isPerm())
	    {
	      numys++;
	      perms.addEntry(reinterpret_cast<wordptr>(arg));
	      arg->setPermFlag();
	    }
	  else
	    {
	      for (int i = 0; i < perms.lastEntry(); i++)
		{
		  if (reinterpret_cast<wordptr>(arg) == perms.Entries()[i])
		    {
		      perms.Entries()[i] = 0;
		      break;
		    }
		}
	      perms.addEntry(reinterpret_cast<wordptr>(arg));
	    }
	}
      else
	{
	  Object* tmp = AtomTable::nil;
	  freeze_thaw_term(a, tmp, true, false);
	  tmp = AtomTable::nil;
	  freeze_thaw_term(half, tmp, false, true);
	  addPerms(tmp, perms, numys);

	  tmp = AtomTable::nil;
	  freeze_thaw_term(a, tmp, false, false);
	  heap.collect_term_vars(a, vars);
	  
	  if (a->isStructure())
	    {
	      Object* functor = OBJECT_CAST(Structure*, a)->getFunctor();
	      if (functor == AtomTable::get_level ||
		  functor == AtomTable::get_level_ancestor ||
		  functor == AtomTable::checkBinder ||
		  functor == AtomTable::psi_life ||
		  functor == AtomTable::ccut ||
		  functor == AtomTable::cut_ancestor ||
		  functor == AtomTable::cpseudo_instr0 ||
		  functor == AtomTable::cpseudo_instr1 ||
		  functor == AtomTable::cpseudo_instr2 ||
		  functor == AtomTable::cpseudo_instr3 ||
		  functor == AtomTable::cpseudo_instr4 ||
		  functor == AtomTable::cpseudo_instr5 ||
		  functor == AtomTable::pieq ||
		  functor == AtomTable::piarg ||
		  functor == AtomTable::equal)
		{
		  continue;
		}
	    }
	  if (a == AtomTable::success || a == AtomTable::failure)
	    {
	      continue;
	    }
	  half = vars;
	  if (!body_goal_found)
	    {
	      neck_vars = vars;
	      body_goal_found = true;
	      goal_ptr = previous;
	      rest_ptr = clause;
	    }
	}
    }
  heap.resetCollectedVarList(vars);

  if (body_goal_found)
    {
      for (int i = perms.lastEntry()-1; i >= 0; i--)
	{
	  if (perms.Entries()[i] == 0)
	    {
	      continue;
	    }	  
	  Object* perm_var = reinterpret_cast<Object*>(perms.Entries()[i]);
	  assert(perm_var != NULL);
	  if (!in_neck_vars(perm_var, neck_vars))
	    {
	      Structure* unif_struct = heap.newStructure(2);
	      unif_struct->setFunctor(AtomTable::equal);
	      unif_struct->setArgument(1, perm_var);
	      unif_struct->setArgument(2, heap.newVariable());
	      Cons* list_entry = heap.newCons(unif_struct, rest_ptr);
	      rest_ptr = list_entry;
	    }
	}
      Cons* goal_cons = OBJECT_CAST(Cons*, goal_ptr);
      goal_cons->setTail(rest_ptr);
    }

}

#if 0
Object*
Thread::build_list(WordArray& warray)
{
  Object* tail = AtomTable::nil;

  for (int i = warray.lastEntry()-1; i >= 0; i--)
    {
      tail = heap.newCons(reinterpret_cast<Object*>(warray.Entries()[i]), tail);
    }
  return tail;
}
void
dump_list(WordArray& warray)
{

  for (int i = 0; i < warray.lastEntry(); i++)
    {
      reinterpret_cast<Object*>(warray.Entries()[i])->printMe_dispatch(*atoms);
      cerr << endl << endl;
    }
}
#endif // 0

//
// The pseudo instruction for compiling.
// If the type is 'compile' then str contains a stream ID
// in which to write the WAM code (A .qs file).
// Otherwise the code is assembled into a code block and
// a pointer to that block is returned.
//
Thread::ReturnValue
Thread::psi_ccompile(Object*& clause, Object*& type, 
		Object*& str, Object*& codeptr)
{
  heapobject* heap_top = heap.getTop();
  QPStream *stream;
  bool ctype = (type->variableDereference() == atoms->add("compile"));
  if (ctype)
    {
      Object* val1 = heap.dereference(str);
      DECODE_STREAM_OUTPUT_ARG(heap, *iom, val1, 1, stream); 
    }

  // Word arrays for processing - these arrays are reused for the different
  // compiler phases.
  WordArray array1(WARRAYSIZE);
  WordArray array2(WARRAYSIZE);
  WordArray array3(WARRAYSIZE);
  WordArray perms(REGISTERSIZE);
  // Information about lifetimes of x registers.
  xreglife xregisters(REGISTERSIZE);

  clause = clause->variableDereference();
  int numys;
  permvars(clause, array3, numys);
  
  int body;
  //
  // C++ version of unravel.ql + partobj.ql
  //
  heap.unravel(clause, array1, array2, body);
  heap.setyregs(array3, numys);
 
  array3.resetLast(0);

  // Equiv to lifetime.ql
  build_lifetime(array2, xregisters, array3);

  // Equiv to prefer.ql
  prefer_registers(array1, xregisters, array3, body);
  bool excess = false;
  // Equiv to tempalloc.ql
  heap.alloc_registers(array2, xregisters, array3, excess);

  if (excess)
    {
      // Equiv. to excess.ql
      heap.excess_registers(array1);
    }
  int esize;
  // Equiv. to envsize.ql
  heap.envsize(array1, esize);

  array2.resetLast(0);
  // Equiv. to voidalloc.ql
  heap.voidalloc(array1, esize, array2);

  array1.resetLast(0);

  // Equiv. to assn_elim.ql
  heap.assn_elim(array2, array1);

  array2.resetLast(0);
  // Equiv. to peephole.ql
  heap.peephole(array1, array2, esize, ctype);
  if (ctype)
    {
      writeInstructions(array2, stream);
      heap.setTop(heap_top);
      codeptr = heap.newInteger(0);
    }
  else
    {
      wordptr cp = reinterpret_cast<wordptr>(dumpInstructions(array2));
      heap.setTop(heap_top);
      codeptr = heap.newInteger(cp);
    }
  return RV_SUCCESS;
}








