// trace.cc - The Qu-Prolog  Abstract Machine Tracer 
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
// email: svrc@cs.uq.oz.au
//
// $Id: trace.cc,v 1.10 2006/03/30 22:50:31 qp Exp $

#include "debug.h"
#ifdef QP_DEBUG

#include	<sys/types.h>
#ifndef WIN32
#include        <unistd.h>
#endif
#include	<stdarg.h>

#include "atom_table.h"
#include "trace_qp.h"
#include "thread_qp.h"
#include "pseudo_instr_arrays.h"

void
trace_thread_info(const ThreadInfo& thread_info,
		  const CodeLoc pc)
{
  if (thread_info.IDSet())
    {
      cerr << thread_info.ID();
    }
  else
    {
      cerr << "    ";
    }
  
  if (thread_info.SymbolSet())
    {
      cerr << thread_info.Symbol().c_str();
    }
  else
    {
      cerr << " ";
    }
  
  cerr << hex << pc << dec;
}

void
Trace::TraceInOut(const word32 mode,
		  const word32 num,
		  const word32 pos)
{
  if (mode & (1 << (num - pos)))
    {
      cerr << "(out)";
    }
  else
    {
      cerr << "(in)";
    }
}

void
Trace::Trace0(const char *s)
{
  cerr << s << endl;
}

void
Trace::Trace1(const char *s, const int32 x)
{
  cerr << s << "(" << x << ")" << endl;
}

void
Trace::Trace2(const char *s, const int32 x, const int32 y)
{
  cerr << s << "(" << x << ", " << y << ")" << endl;
}

void
Trace::Trace3(const char *s, const int32 x, const int32 y, const int32 z)
{
  cerr << s << "(" << x << ", " << y << ", " << z << ")" << endl;
}

void
Trace::Trace4(const char *s, const int32 x, const int32 y, const int32 z,
	      const int32 w)
{
  cerr << s << "(" << x << ", " << y << ", " << z << ", " << w << ")" << endl;
}

void
Trace::Trace5(const char *s, const int32 x, const int32 y, const int32 z,
	      const int32 w, const int32 u)
{
  cerr << s << "(" << x << ", " << y << ", " << z << ", " << w << ", " << u << ")" << endl;
}

void
Trace::TraceConst0(AtomTable& atoms, Heap& heap, const char *s, Object* c)
{
  cerr << s << "(" << hex << reinterpret_cast<wordptr>(c) << dec << ") ";
  heap.displayTerm(cerr, atoms, c, 0);
}

void
Trace::TraceConst1(AtomTable& atoms, Heap& heap,
		   const char *s, Object* c,
		   const int32 x)
{
  cerr << s << "(" << hex << reinterpret_cast<wordptr>(c) << ", " << x << dec << ") ";
  heap.displayTerm(cerr, atoms, c, 0);
}

void
Trace::TraceConst2(AtomTable& atoms, Heap& heap,
		   const char *s, Object* c,
		   const int32 x, const int32 y)
{
  cerr << s << "(" << hex << reinterpret_cast<wordptr>(c) << ", " << x << ", " << y << dec << ") ";
  heap.displayTerm(cerr, atoms, c, 0);
}

void
Trace::TraceInt0(const char *s, const int32 n)
{
  cerr << s << "(" <<  n << ") ";
}
void
Trace::TraceInt1(const char *s, const int32 n, const int32 x)
{
  cerr << s << "(" <<  n  << "' " << x << ") ";
}

void
Trace::TraceString1(const char *s, const char *t)
{
  cerr << s << "(" <<  t << ") ";
}

void
Trace::TraceString2(const char *s, const char *t, const int32 x)
{
  cerr << s << "(" <<  t  << "' " << x << ") ";
}

void
Trace::TraceString3(const char *s, const char *t, const int32 x, const int32 y)
{
  cerr << s << "(" <<  t  << "' " << x << "' " << y << ") ";
}

void
Trace::TraceXReg(Thread& th, AtomTable& atoms, const word32 reg)
{
  if (trace_level & TRACE_REGS)
    {
      cerr << "\tX[" << reg << "]: " << endl;
      th.heap.displayTerm(cerr, atoms, th.X[reg], 2);
    }
}

void
Trace::TraceYReg(Thread& th, AtomTable& atoms, const word32 reg)
{
  if (trace_level & TRACE_REGS)
    {
      cerr << "\tY[" << reg << "]: " << endl;
      th.heap.displayTerm(cerr, atoms, th.envStack.yReg(th.currentEnvironment, reg), 2);
    }
}

void
Trace::TracePseudoRegs(Thread& th, AtomTable& atoms, 
		       const word32 mode, const word32 num, ...)
{
  va_list regs;

  if (num > 0)
    {
      va_start(regs, num);

      cerr << ", ";

      for (word32 i = 1; i <= num; i++)
	{
	  const word32 reg = va_arg(regs, word32);

	  cerr << reg << ' ';

	  TraceInOut(mode, num, i);

	  if (i < num)
	    {
	      cerr << ", ";
	    }
	}
      
      va_end(regs);
    }
  
  cerr << ')' << endl;

  if (num > 0)
    {
      va_start(regs, num);
      
      for (word32 i = 1; i <= num; i++)
	{
	  const word32 reg = va_arg(regs, word32);

	  cerr << "\tX[" << reg << "]: " << endl;
	  th.heap.displayTerm(cerr, atoms, th.PSIGetReg(reg), 2);
	}

      va_end(regs);
    }
}

void
Trace::TracePseudo0(Thread& th, AtomTable& atoms, const word32 n)
{
  cerr << "pseudo_instr0(" << n << " = " << pseudo_instr0_array[n].name;
  TracePseudoRegs(th, atoms, pseudo_instr0_array[n].mode, 0);
}

void
Trace::TracePseudo1(Thread& th, AtomTable& atoms,
		    const word32 n,
		    const word32 reg1)
{
  cerr << "pseudo_instr1(" << n << " = " << pseudo_instr1_array[n].name;
  TracePseudoRegs(th, atoms, pseudo_instr1_array[n].mode, 1,
		  reg1);
}

void
Trace::TracePseudo2(Thread& th, AtomTable& atoms,
		    const word32 n,
		    const word32 reg1,
		    const word32 reg2)
{
  cerr << "pseudo_instr2(" << n << " = " << pseudo_instr2_array[n].name;
  TracePseudoRegs(th, atoms, pseudo_instr2_array[n].mode, 2,
		  reg1, reg2);
}

void
Trace::TracePseudo3(Thread& th, AtomTable& atoms,
		    const word32 n,
		    const word32 reg1,
		    const word32 reg2,
		    const word32 reg3)
{
  cerr << "pseudo_instr3(" << n << " = " << pseudo_instr3_array[n].name;
  TracePseudoRegs(th, atoms, pseudo_instr3_array[n].mode, 3,
		  reg1, reg2, reg3);
}

void
Trace::TracePseudo4(Thread& th, AtomTable& atoms,
		    const word32 n,
		    const word32 reg1, const word32 reg2,
		    const word32 reg3, const word32 reg4)
{
  cerr << "pseudo_instr4(" << n << " = " << pseudo_instr4_array[n].name;
  TracePseudoRegs(th, atoms, pseudo_instr4_array[n].mode, 4,
		  reg1, reg2, reg3, reg4);
}

void
Trace::TracePseudo5(Thread& th, AtomTable& atoms,
		    const word32 n,
		    const word32 reg1, const word32 reg2,
		    const word32 reg3, const word32 reg4,
		    const word32 reg5)
{
  cerr << "pseudo_instr5(" << n << " = " << pseudo_instr5_array[n].name;
  TracePseudoRegs(th, atoms, pseudo_instr5_array[n].mode, 5,
		  reg1, reg2, reg3, reg4, reg5);
}

void
Trace::TraceStart(Thread& th)
{
  if (trace_level & TRACE_ENV)
    {
#if 0
      if (th.envStack.getTop() == th.envStack.firstEnv())
	{
	  trace_init_env = true;
	  trace_current_environment = th.envStack.getTop();
	  trace_top_of_env = th.envStack.getTop();
	}
      else
	{
	  trace_init_env = false;
	  trace_current_environment = th.currentEnvironment;
	  trace_env = *(th.envStack.fetchEnv(th.currentEnvironment));
	  trace_top_of_env = th.envStack.getTop();
	}
#endif	// 0
    }

  if (trace_level & TRACE_CHOICE) 
    {
#if 0
      if (th.currentChoicePoint == th.choiceStack.firstChoice())
	{
	  trace_init_choice = true;
	  trace_current_choice_point = th.currentChoicePoint;
	}
      else
	{
	  trace_init_choice = false;
	  trace_current_choice_point = th.currentChoicePoint;
	  trace_choice = *(th.choiceStack.fetchChoice(th.currentChoicePoint));
	}
#endif	// 0
    }

  if (trace_level & TRACE_CUT)
    {
      trace_cut_point = th.cutPoint;
    }
}

//
// Instruction decoder and printer
//
void
Trace::TraceInstr(Thread& th,
		  AtomTable& atoms,
		  Code& code,
		  PredTab& predicates,
		  CodeLoc pc)
{
  if (trace_level & TRACE_INSTR)
    {
      trace_thread_info(th.TInfo(), pc);

      switch (getInstruction(pc))
	{
	case PUT_X_VARIABLE:	// put_x_variable i, j
	  {
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
      
	    Trace2("put_x_variable", i, j);
	    TraceXReg(th, atoms, i);
	    TraceXReg(th, atoms, j);
	  }
	break;
      
	case PUT_Y_VARIABLE:	// put_y_variable i, j
	  {
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
      
	    Trace2("put_y_variable", i, j);
	    TraceYReg(th, atoms, i);
	    TraceXReg(th, atoms, j);
	  }
	break;
      
	case PUT_X_VALUE:	// put_x_value i, j
	  {
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
      
	    Trace2("put_x_value", i, j);
	    TraceXReg(th, atoms, i);
	    TraceXReg(th, atoms, j);
	  }
	break;
      
	case PUT_Y_VALUE:	// put_y_value i, j
	  {
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
      
	    Trace2("put_y_value", i, j);
	    TraceYReg(th, atoms, i);
	    TraceXReg(th, atoms, j);
	  }
	break;
      
	case PUT_CONSTANT:	// put_constant c, i
	  {
	    Object* c = getConstant(pc);
	    const word32 i = getRegister(pc);
	
	    TraceConst1(atoms, th.heap, "put_constant", c, i);
	    TraceXReg(th, atoms, i);
	  }
	break;

      	case PUT_INTEGER:
	  {
	    int32 c = getInteger(pc);
	    const word32 i = getRegister(pc);
	
	    TraceInt1("put_integer", c, i);
	    TraceXReg(th, atoms, i);
	  }
	break;
      
	case PUT_LIST:		// put_list i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("put_list", i);
	    TraceXReg(th, atoms, i);
	  }
	break;
      
	case PUT_STRUCTURE:	// put_structure n, i
	  {
	    const word32 n = getNumber(pc);
	    const word32 i = getRegister(pc);
      
	    Trace2("put_structure", n, i);
	    TraceXReg(th, atoms, i);
	  }
	break;
      
	case PUT_X_OBJECT_VARIABLE:	// put_x_object_variable i, j
	  {
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
      
	    Trace2("put_x_object_variable", i, j);
	    TraceXReg(th, atoms, i);
	    TraceXReg(th, atoms, j);
	  }
	break;
      
	case PUT_Y_OBJECT_VARIABLE:	// put_y_object_variable i, j
	  {
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
      
	    Trace2("put_y_object_variable", i, j);
	    TraceYReg(th, atoms, i);
	    TraceXReg(th, atoms, j);
	  }
	break;
      
	case PUT_X_OBJECT_VALUE:	// put_x_object_value i, j
	  {
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
      
	    Trace2("put_x_object_value", i, j);
	    TraceXReg(th, atoms, i);
	    TraceXReg(th, atoms, j);
	  }
	break;
      
	case PUT_Y_OBJECT_VALUE:	// put_y_object_value i, j
	  {
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
      
	    Trace2("put_y_object_value", i, j);
	    TraceYReg(th, atoms, i);
	    TraceXReg(th, atoms, j);
	  }
	break;
      
	case PUT_QUANTIFIER:	// put_quantifier i 
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("put_quantifier", i);
	    TraceXReg(th, atoms, i);
	  }
	break;
      
	case CHECK_BINDER:	// check_binder i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("check_binder", i);
	    TraceXReg(th, atoms, i);
	  }
	break;
      
	case PUT_SUBSTITUTION:	// put_substitution n, i
	  {
	    const word32 n = getNumber(pc);
	    const word32 i = getRegister(pc);
      
	    Trace2("put_substitution", n, i);
	    TraceXReg(th, atoms, i);
	  }
	break;
      
	case PUT_X_TERM_SUBSTITUTION:	// put_x_term_substitution i j
	  {
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
      
	    Trace2("put_x_term_substitution", i, j);
	    TraceXReg(th, atoms, i);
	    TraceXReg(th, atoms, j);
	  }
	break;
      
	case PUT_Y_TERM_SUBSTITUTION:	// put_y_term_substitution i j
	  {
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
      
	    Trace2("put_y_term_substitution", i, j);
	    TraceYReg(th, atoms, i);
	    TraceXReg(th, atoms, j);
	  }
	break;
      
	case PUT_INITIAL_EMPTY_SUBSTITUTION: // put_initial_empty_substitution i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("put_initial_empty_substitution", i);
	    TraceXReg(th, atoms, i);
	  }
	break;

	case GET_X_VARIABLE:	// get_x_variable i, j
	  {
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
      
	    Trace2("get_x_variable", i, j);
	    TraceXReg(th, atoms, i);
	    TraceXReg(th, atoms, j);
	  }
	break;
      
	case GET_Y_VARIABLE:	// get_y_variable i, j
	  {
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
      
	    Trace2("get_y_variable", i, j);
	    TraceYReg(th, atoms, i);
	    TraceXReg(th, atoms, j);
	  }
	break;
      
	case GET_X_VALUE:	// get_x_value i, j
	  {
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
      
	    Trace2("get_x_value", i, j);
	    TraceXReg(th, atoms, i);
	    TraceXReg(th, atoms, j);
	  }
	break;
      
	case GET_Y_VALUE:	// get_y_value i, j
	  {
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
      
	    Trace2("get_y_value", i, j);
	    TraceYReg(th, atoms, i);
	    TraceXReg(th, atoms, j);
	  }
	break;

	case GET_CONSTANT:	// get_constant c, i
	  {
	    Object* c = getConstant(pc);
	    const word32 i = getRegister(pc);
      
	    TraceConst1(atoms, th.heap, "get_constant", c, i);
	    TraceXReg(th, atoms, i);
	  }
	break; 

	case GET_INTEGER:
	  {
	    int32 c = getInteger(pc);
	    const word32 i = getRegister(pc);
      
	    TraceInt1("get_integer", c, i);
	    TraceXReg(th, atoms, i);
	  }
	break; 
      
	case GET_LIST:		// get_list i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("get_list", i);
	    TraceXReg(th, atoms, i);
	  }
	break; 
      
	case GET_STRUCTURE:	// get_structure c, n, i
	  {
	    Object* c = getConstant(pc);
	    const word32 n = getNumber(pc);
	    const word32 i = getRegister(pc);
      
	    TraceConst2(atoms, th.heap, "get_structure", c, n, i);
	    TraceXReg(th, atoms, i);
	  }
	break;
      
	case GET_STRUCTURE_FRAME:	// get_structure_frame n, i
	  {
	    const word32 n = getNumber(pc);
	    const word32 i = getRegister(pc);
      
	    Trace2("get_structure_frame", n, i);
	    TraceXReg(th, atoms, i);
	  }
	break;
      
	case GET_X_OBJECT_VARIABLE:	// get_x_object_variable i, j
	  {
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
      
	    Trace2("get_x_object_variable", i, j);
	    TraceXReg(th, atoms, i);
	    TraceXReg(th, atoms, j);
	  }
	break; 
      
	case GET_Y_OBJECT_VARIABLE:	// get_y_object_variable i, j
	  {
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
      
	    Trace2("get_y_object_variable", i, j);
	    TraceYReg(th, atoms, i);
	    TraceXReg(th, atoms, j);
	  }
	break;
      
	case GET_X_OBJECT_VALUE:	// get_x_object_value i, j
	  {
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
      
	    Trace2("get_x_object_value", i, j);
	    TraceXReg(th, atoms, i);
	    TraceXReg(th, atoms, j);
	  }
	break; 
      
	case GET_Y_OBJECT_VALUE:	// get_y_object_value i, j
	  {
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
      
	    Trace2("get_y_object_value", i, j);
	    TraceYReg(th, atoms, i);
	    TraceXReg(th, atoms, j);
	  }
	break; 
      
	case UNIFY_X_VARIABLE:	// unify_x_variable i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("unify_x_variable", i);
	    TraceXReg(th, atoms, i);
	  }
	break;
      
	case UNIFY_Y_VARIABLE:	// unify_y_variable i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("unify_y_variable", i);
	    TraceYReg(th, atoms, i);
	  }
	break;
	case UNIFY_X_REF:	// unify_x_ref i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("unify_x_ref", i);
	    TraceXReg(th, atoms, i);
	  }
	break;
      
	case UNIFY_Y_REF:	// unify_y_ref i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("unify_y_ref", i);
	    TraceYReg(th, atoms, i);
	  }
	break;
      
	case UNIFY_X_VALUE:	// unify_x_value i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("unify_x_value", i);
	    TraceXReg(th, atoms, i);
	  }
	break;
      
	case UNIFY_Y_VALUE:	// unify_y_value i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("unify_y_value", i);
	    TraceYReg(th, atoms, i);
	  }
	break; 
      
	case UNIFY_VOID:	// unify_void n
	  {
	    const word32 n = getNumber(pc);
      
	    Trace1("unify_void", n);
	  }
	break; 
      
	case SET_X_VARIABLE:	// set_x_variable i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("set_x_variable", i);
	    TraceXReg(th, atoms, i);
	  }
	break; 
      
	case SET_Y_VARIABLE:	// set_y_variable i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("set_y_variable", i);
	    TraceYReg(th, atoms, i);
	  }
	break; 
      
	case SET_X_VALUE:	// set_x_value i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("set_x_value", i);
	    TraceXReg(th, atoms, i);
	  }
	break; 
      
	case SET_Y_VALUE:	// set_y_value i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("set_y_value", i);
	    TraceYReg(th, atoms, i);
	  }
	break; 
      
	case SET_X_OBJECT_VARIABLE:	// set_x_object_variable i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("set_x_object_variable", i);
	    TraceXReg(th, atoms, i);
	  }
	break; 
      
	case SET_Y_OBJECT_VARIABLE:	// set_y_object_variable i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("set_y_object_variable", i);
	    TraceYReg(th, atoms, i);
	  }
	break; 
      
	case SET_X_OBJECT_VALUE:	// set_x_object_value i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("set_x_object_value", i);
	    TraceXReg(th, atoms, i);
	  }
	break; 
      
	case SET_Y_OBJECT_VALUE:	// set_y_object_value i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("set_y_object_value", i);
	    TraceYReg(th, atoms, i);
	  }
	break; 
      
	case SET_CONSTANT:	// set_constant c
	  {
	    Object* c = getConstant(pc);
      
	    TraceConst0(atoms, th.heap, "set_constant", c);
	  }
	break; 

	case SET_INTEGER:
	  {
	    int32 c = getInteger(pc);
      
	    TraceInt0("set_integer", c);
	  }
	break; 
      
      
	case SET_VOID:		// set_void n
	  {
	    const word32 n = getNumber(pc);
      
	    Trace1("set_void", n);
	  }
	break; 
      
	case SET_OBJECT_VOID:	// set_object_void n
	  {
	    const word32 n = getNumber(pc);
      
	    Trace1("set_object_void", n);
	  }
	break;

	case ALLOCATE:		// allocate n
	  {
	    const word32 n = getNumber(pc);
      
	    Trace1("allocate", n);
	  }
	break; 
      
	case DEALLOCATE:	// deallocate
	  Trace0("deallocate");
	  break; 
      
	case CALL_PREDICATE:	// call_predicate predicate, arity, n
	  {
	    const char *s = getPredAtom(pc)->getName();
	    const word32 arity = getNumber(pc);
	    const word32 n = getNumber(pc);
      
	    TraceString3("call_predicate", s, arity, n);
	  }
	break; 
      
	case CALL_ADDRESS:	// call_address address, n
	  {
	    const CodeLoc address = getCodeLoc(pc);
	    const word32 n = getNumber(pc);
	
	    CodeLoc loc = address - Code::SIZE_OF_HEADER;
	    Atom* predicate = reinterpret_cast<Atom*>(getAddress(loc));
      
	    const char *s = predicate->getName();
      
	    TraceString2("call_address", s, n);
	  }
	break; 
      
	case CALL_ESCAPE:	// call_escape address, n
	  {
	    const CodeLoc address = getCodeLoc(pc);
	    const word32 n = getNumber(pc);
      
	    Atom* predicate =  predicates.getPredName((wordptr)address, &atoms);
	    const char *s = predicate->getName();
      
	    TraceString2("call_escape", s, n);
	  }
	break;
      
	case EXECUTE_PREDICATE:	// execute_predicate predicate, arity 
	  {
	    Atom* predicate = getPredAtom(pc);
	    const word32 arity = getNumber(pc);
      
	    const char *s = predicate->getName();
      
	    TraceString2("execute_predicate", s, arity);
	  }
	break; 
      
	case EXECUTE_ADDRESS:	// execute_address address
	  {
	    const CodeLoc address = getCodeLoc(pc);
      
	    CodeLoc loc = address - Code::SIZE_OF_HEADER;
	    Atom* predicate = reinterpret_cast<Atom*>(getAddress(loc));
      
	    const char *s = predicate->getName();
      
	    TraceString1("execute_address", s);
	  }
	break;
      
	case EXECUTE_ESCAPE:	// execute_escape address
	  {
	    const CodeLoc address = getCodeLoc(pc);
      
	    Atom* predicate = predicates.getPredName((wordptr)address, &atoms);
	    const char *s = predicate->getName();
      
	    TraceString1("execute_escape", s);
	  }
	break;
      
	case NOOP:		// noop
	  Trace0("noop");
	  break;
      
	case JUMP:		// jump address
	  {
	    const CodeLoc address = getCodeLoc(pc);
      
	    Trace1("jump", (wordptr)address);
	  }
	break;

	case PROCEED:		// proceed
	  Trace0("proceed");
	  break; 
      
	case FAIL:		// fail
	  Trace0("fail");
	  break;
      
	case HALT:		// halt
	  Trace0("halt");
	  break;
      
	case EXIT:		// exit
	  Trace0("exit");
	  break;
      
	case TRY_ME_ELSE:	// try_me_else arity, label
	  {
	    const word32 arity = getNumber(pc);
	    const word32 label = getOffset(pc);
      
	    Trace2("try_me_else", arity, label);
	  }
	break; 
      
	case RETRY_ME_ELSE:	// retry_me_else label
	  {
	    const word32 label = getOffset(pc);
      
	    Trace1("retry_me_else", label);
	  }
	break;
      
	case TRUST_ME_ELSE_FAIL:	// trust_me_else_fail
	  Trace0("trust_me_else_fail");
	  break; 
      
	case TRY:		// try arity, label
	  {
	    const word32 arity = getNumber(pc);
	    const word32 label = getOffset(pc);
      
	    Trace2("try", arity, label);
	  }
	break; 
      
	case RETRY:		// retry label
	  {
	    const word32 label = getOffset(pc);
      
	    Trace1("retry", label);
	  }
	break; 
      
	case TRUST:		// trust label
	  {
	    const word32 label = getOffset(pc);
      
	    Trace1("trust", label);
	  }
	break; 
      
	case NECK_CUT:		// neck_cut
	  Trace0("neck_cut");
	  break; 
      
	case GET_X_LEVEL:		// get_x_level i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("get_x_level", i);
	  }
	break; 
      
	case GET_Y_LEVEL:		// get_y_level i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("get_y_level", i);
	  }
	break; 
      
	case CUT:		// cut i
	  {
	    const word32 i = getRegister(pc);
      
	    Trace1("cut", i);
	  }
	break; 
      
	case SWITCH_ON_TERM:	// switch_on_term i, 
	  {
	    //		  VARIABLE_LABEL,
	    // 		  OB_VARIABLE_LABEL,
	    // 		  LIST_LABEL,
	    //		  STRUCTURE_LABEL,
	    // 		  QUANTIFIER_LABEL,
	    //		  CONSTANT_LABEL
	    const word32 i = getRegister(pc);
      
	    cerr << "switch_on_term(" << i;
      
	    for (word32 j = 0; j < 6; j++)
	      {
		cerr << ", " << getOffset(pc); 
	      }

	    cerr << ")" << endl;

	    TraceXReg(th, atoms, i);
	  }
	break; 
      
	case SWITCH_ON_CONSTANT:	// switch_on_constant i, n
	  {
	    const word32 i = getRegister(pc);
	    const word32 n = getTableSize(pc);
      
	    Trace2("switch_on_constant", i, n);
	    TraceXReg(th, atoms, i);
	  }
	break;
      
	case SWITCH_ON_STRUCTURE:	// switch_on_structure i, n
	  {
	    const word32 i = getRegister(pc);
	    const word32 n = getTableSize(pc);
      
	    Trace2("switch_on_structure", i, n);
	    TraceXReg(th, atoms, i);
	  }
	break;
      
	case SWITCH_ON_QUANTIFIER:	// switch_on_quantifier i, n
	  {
	    const word32 i = getRegister(pc);
	    const word32 n = getTableSize(pc);
      
	    Trace2("switch_on_quantifier", i, n);
	    TraceXReg(th, atoms, i);
	  }
	break;
      
	case PSEUDO_INSTR0: 
	  {
	    const word32 n = getNumber(pc);

	    TracePseudo0(th, atoms, n);
	  }
	break;

	case PSEUDO_INSTR1: 
	  {
	    const word32 n = getNumber(pc);
	    const word32 i = getRegister(pc);

	    TracePseudo1(th, atoms, n, i);
	  }
	break;

	case PSEUDO_INSTR2: 
	  {
	    const word32 n = getNumber(pc);
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);

	    TracePseudo2(th, atoms, n, i, j);
	  }
	break;

	case PSEUDO_INSTR3: 
	  {
	    const word32 n = getNumber(pc);
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
	    const word32 k = getRegister(pc);

	    TracePseudo3(th, atoms, n, i, j, k);
	  }
	break;

	case PSEUDO_INSTR4: 
	  {
	    const word32 n = getNumber(pc);
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
	    const word32 k = getRegister(pc);
	    const word32 m = getRegister(pc);

	    TracePseudo4(th, atoms, n, i, j, k, m);
	  }
	break;

	case PSEUDO_INSTR5: 
	  {
	    const word32 n = getNumber(pc);
	    const word32 i = getRegister(pc);
	    const word32 j = getRegister(pc);
	    const word32 k = getRegister(pc);
	    const word32 m = getRegister(pc);
	    const word32 o = getRegister(pc);

	    TracePseudo5(th, atoms, n, i, j, k, m, o);
	  }
	break;

	case UNIFY_CONSTANT:
	  {
	    Object* c = getConstant(pc);

	    TraceConst0(atoms, th.heap, "unify_constant", c);
	  }
	break;

	case UNIFY_INTEGER:
	  {
	    int32 c = getInteger(pc);

	    TraceInt0("unify_integer", c);
	  }
	break;


        case DB_JUMP:
          {
            (void)getNumber(pc);
            (void)getAddress(pc);
            const CodeLoc jump = getCodeLoc(pc);
	    Trace1("db jump", (wordptr)jump);
          }
          break;
 
	case DB_EXECUTE_PREDICATE:	// execute_predicate predicate, arity 
	  {
	    Atom* predicate = getPredAtom(pc);
	    const word32 arity = getNumber(pc);
      
	    const char *s = predicate->getName();
      
	    TraceString2("db_execute_predicate", s, arity);
	  }
	break; 
      
	case DB_EXECUTE_ADDRESS:	// execute_address address
	  {
	    const CodeLoc address = getCodeLoc(pc);
      
	    CodeLoc loc = address - Code::SIZE_OF_HEADER;
	    Atom* predicate = reinterpret_cast<Atom*>(getAddress(loc));
      
	    const char *s = predicate->getName();
      
	    TraceString1("db_execute_address", s);
	  }
	break;

        case DB_PROCEED:
          {
            Trace0("db_proceed");
          }
          break;  
 
	default:
	  {


	    CodeLoc oldpc = pc - Code::SIZE_OF_INSTRUCTION;
	    cerr << "*** UNKNOWN INSTRUCTION = " << getInstruction(oldpc) << endl;
	  }
	break;
	}
  
      cerr.flush();
    }
}

void
Trace::TraceBacktrack(Thread& th,
		      const CodeLoc pc)
{
  if (trace_level & TRACE_INSTR)
    {
      trace_thread_info(th.TInfo(), pc);
      cerr << "backtrack" << endl;
    }
}

void
Trace::TraceEnd(Thread& th)
{
  if ((trace_level & TRACE_ENV) &&
      (trace_current_environment != th.currentEnvironment ||
       trace_top_of_env != th.envStack.getTop() ||
       (!trace_init_env &&
       !(trace_env == th.envStack.fetchEnv(th.currentEnvironment)))))
    {
#if 0
      cerr.form("%6ld envStack[%ld] (Top = %ld)\n",
		th.TInfo().ID(),
		th.currentEnvironment,
		th.envStack.getTop);

      th.envStack.display(cerr, th.currentEnvironment, 1);
  
      cerr.flush();
#endif	// 0
    }	

  if ((trace_level & TRACE_CHOICE) &&
      (trace_current_choice_point != th.currentChoicePoint ||
       (!trace_init_choice &&
       !(trace_choice == th.choiceStack.fetchChoice(th.currentChoicePoint)))))
    {
#if 0
      cerr.form("%6ld choiceStack[%ld]\n",
		th.TInfo().ID(),
		th.currentChoicePoint);

      th.choiceStack.display(cerr, th.currentChoicePoint, 1);
      
      cerr.flush();
#endif	// 0
    }
  
  if ((trace_level & TRACE_CUT) && trace_cut_point != th.cutPoint)
    {
      cerr << th.TInfo().ID() << " cutPoint=" << th.cutPoint << endl;
  
      cerr.flush();
    }
}

Trace::Trace(const word32 level)
  : trace_level(level),
    trace_init_env(false),
    trace_init_choice(false)
{ }

#endif // QP_DEBUG
