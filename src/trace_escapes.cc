// trace_escapes.cc - Set the level of the QuAM trace.
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
// $Id: trace_escapes.cc,v 1.8 2006/03/30 22:50:31 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"
#include "trace_qp.h"
#include "assert.h"
#ifdef QP_DEBUG
//
// A wrapper for decode_trace_flag() calls.
//
#define DECODE_TRACE_FLAG_ARG(arg, arg_num, flag)	\
do {							\
  const ErrorValue ev = decode_trace_flag(arg, flag);	\
  if (ev != EV_NO_ERROR)				\
    {							\
      PSI_ERROR_RETURN(ev, arg_num);			\
    }							\
} while (0)
		
static ErrorValue
decode_trace_flag(Object *& flag_cell,
		  word32& flag)
{
  if (flag_cell->isVariable())
    {
      return EV_INST;
    }
  else if (flag_cell->isAtom())
    {
      if (flag_cell == AtomTable::trace_instr)
	{
	  flag = Trace::TRACE_INSTR;
	  return EV_NO_ERROR;
	}
      else if (flag_cell == AtomTable::trace_backtrack)
	{
	  flag = Trace::TRACE_BACKTRACK;
	  return EV_NO_ERROR;
	}
      else if (flag_cell == AtomTable::trace_env)
	{
	  flag = Trace::TRACE_ENV;
	  return EV_NO_ERROR;
	}
      else if (flag_cell == AtomTable::trace_choice)
	{
	  flag = Trace::TRACE_CHOICE;
	  return EV_NO_ERROR;
	}
      else if (flag_cell == AtomTable::trace_cut)
	{
	  flag = Trace::TRACE_CUT;
	  return EV_NO_ERROR;
	}
      else if (flag_cell == AtomTable::trace_heap)
	{
	  flag = Trace::TRACE_HEAP;
	  return EV_NO_ERROR;
	}
      else if (flag_cell == AtomTable::trace_regs)
	{
	  flag = Trace::TRACE_REGS;
	  return EV_NO_ERROR;
	}
      else if (flag_cell == AtomTable::trace_all)
	{
	  flag = Trace::TRACE_ALL;
	  return EV_NO_ERROR;
	}
      else
	{
	  return EV_VALUE;
	}
    }
  else
    {
      return EV_TYPE;
    }
}

#endif // QP_DEBUG

Thread::ReturnValue
Thread::psi_set_trace_level(Object *& object1)
{
#ifdef QP_DEBUG
  Object* val1 = heap.dereference(object1);
  
  assert(val1->isNumber());
	
  trace.TraceLevel() = (word32)(val1->getInteger());
#endif // QP_DEBUG
  return(RV_SUCCESS);
}

Thread::ReturnValue
Thread::psi_set_trace_flag(Object *& flag_arg)
{
#ifdef QP_DEBUG
  Object* argF = heap.dereference(flag_arg);

  word32 flag;
  DECODE_TRACE_FLAG_ARG(argF, 1, flag);

  trace.SetTraceFlag(flag);
#endif // QP_DEBUG
  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_clear_trace_flag(Object *& flag_arg)
{
#ifdef QP_DEBUG
  Object* argF = heap.dereference(flag_arg);

  word32 flag;
  DECODE_TRACE_FLAG_ARG(argF, 1, flag);

  trace.ClearTraceFlag(flag);
#endif // QP_DEBUG
  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_test_trace_flag(Object *& flag_arg)
{
#ifdef QP_DEBUG
  Object* argF = heap.dereference(flag_arg);

  word32 flag;
  DECODE_TRACE_FLAG_ARG(argF, 1, flag);

  return BOOL_TO_RV(trace.TestTraceFlag(flag));
#else
  return RV_SUCCESS;
#endif //QP_DEBUG
}






