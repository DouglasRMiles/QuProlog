// thread_decode.cc - support for decoding thread info.
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
// $Id: thread_decode.cc,v 1.8 2006/02/14 02:40:09 qp Exp $

#include "thread_decode.h"


ErrorValue
decode_thread(Heap& heap,
	      Object * thread_cell,
	      ThreadTable& thread_table,
	      Thread **thread)
{
  if (thread_cell->isVariable())
    {
      return EV_INST;
    }
  else if (thread_cell->isNumber())
    {
      const ThreadTableLoc loc = (ThreadTableLoc) (thread_cell->getInteger());

      if (thread_table.IsValid(loc))
	{
	  *thread = thread_table.LookupID(loc);
	  if (*thread == NULL)
	    {
	      return EV_VALUE;
	    }
	  else
	    {
	      return EV_NO_ERROR;
	    }
	}
      else
	{
	  return EV_VALUE;
	}
    }
  else if (thread_cell->isAtom())
    {
      const char *symbol = OBJECT_CAST(Atom*, thread_cell)->getName();
      ThreadTableLoc id = thread_table.LookupName(symbol);
      if (id == (ThreadTableLoc) -1)
        {
          return EV_VALUE;
        }
      *thread = thread_table.LookupID(id);
      if (*thread == NULL)
        {
          return EV_VALUE;
        }
      else
        {
          return EV_NO_ERROR;
        }
    }
  else
    {
      return EV_TYPE;
    }
}

/*
ErrorValue
decode_thread_conditions(Heap& heap, AtomTable& atoms,
			 Object * arg,
			 bool& db,
			 double& wait_time)
{
  if (heap.check_functor(arg, AtomTable::thread_wait_conditions, 2))
    {
      Structure* str = OBJECT_CAST(Structure*, arg);
      Object* db_cell 
	= str->getArgument(1)->variableDereference();
      Object* wait_time_cell 
	= str->getArgument(2)->variableDereference();

      if (db_cell->isVariable() ||
	  wait_time_cell->isVariable())
	{
	  return EV_INST;
	}

      if (db_cell->isAtom() &&
	  heap.IsTimeout(wait_time_cell))
	{
	  db = atoms.atomToBool(db_cell);
	  wait_time = heap.DecodeTimeout(wait_time_cell);

	  return EV_NO_ERROR;
	}
      else
	{
	  return EV_TYPE;
	}
    }
  else
    {
      return EV_TYPE;
    }
}

*/

bool
decode_defaults(Heap& heap, Object * sizes,
		Object *& heap_size,
		Object *& scratchpad_size,
		Object *& binding_trail_size,
		Object *& other_trail_size,
		Object *& env_size,
		Object *& choice_size,
		Object *& name_table_size,
		Object *& ip_table_size)
{
  if (heap.check_functor(sizes, AtomTable::thread_defaults, 8))
    {
      Structure* str = OBJECT_CAST(Structure*, sizes);
      heap_size = str->getArgument(1)->variableDereference();
      scratchpad_size = str->getArgument(2)->variableDereference();
      binding_trail_size = str->getArgument(3)->variableDereference();
      other_trail_size = str->getArgument(4)->variableDereference();
      env_size = str->getArgument(5)->variableDereference(); 
      choice_size = str->getArgument(6)->variableDereference();
      name_table_size = str->getArgument(7)->variableDereference();
      ip_table_size = str->getArgument(8)->variableDereference();

      return true;
    }
  else
    {
      return false;
    }
}

ErrorValue
decode_defaults(Heap& heap,
		Object * sizes,
		int& heap_size,
		int& scratchpad_size,
		int& binding_trail_size,
		int& other_trail_size,
		int& env_size,
		int& choice_size,
		int& name_table_size,
		int& ip_table_size)
{
  Object* heap_size_cell;
  Object* scratchpad_size_cell;
  Object* binding_trail_size_cell;
  Object* other_trail_size_cell;
  Object* env_size_cell;
  Object* choice_size_cell;
  Object* name_table_size_cell;
  Object* ip_table_size_cell;
  
  if (sizes->isVariable())
    {
      return EV_INST;
    }
  else if (decode_defaults(heap, sizes,
			   heap_size_cell,
			   scratchpad_size_cell,
			   binding_trail_size_cell,
			   other_trail_size_cell,
			   env_size_cell,
			   choice_size_cell,
			   name_table_size_cell,
			   ip_table_size_cell))
    {
      DECODE_THREAD_DEFAULT_NONNEG_INT(heap, heap_size_cell,
				       heap_size, error);
      DECODE_THREAD_DEFAULT_NONNEG_INT(heap, scratchpad_size_cell,
				       scratchpad_size, error);
      DECODE_THREAD_DEFAULT_NONNEG_INT(heap, binding_trail_size_cell,
				       binding_trail_size, error);
      DECODE_THREAD_DEFAULT_NONNEG_INT(heap, other_trail_size_cell,
				       other_trail_size, error);
      DECODE_THREAD_DEFAULT_NONNEG_INT(heap, env_size_cell,
				       env_size, error);
      DECODE_THREAD_DEFAULT_NONNEG_INT(heap, choice_size_cell,
				       choice_size, error);
      DECODE_THREAD_DEFAULT_NONNEG_INT(heap, name_table_size_cell,
				       name_table_size, error);
      DECODE_THREAD_DEFAULT_NONNEG_INT(heap, ip_table_size_cell,
				       ip_table_size, error);
		    
      return EV_NO_ERROR;
    }
  else
    {
      return EV_TYPE;
    }
}

