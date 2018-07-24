// thread_decode.h - support for decoding thread information.
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
// $Id: thread_decode.h,v 1.6 2006/02/14 02:40:09 qp Exp $

#ifndef	THREAD_DECODE_H
#define	THREAD_DECODE_H

#include "global.h"
#include "thread_qp.h"
#include "thread_table.h"
#include "timeval.h"

#define DECODE_THREAD_DEFAULT_NONNEG_INT(heap, cell, integer, error)	\
  do {									\
    const ErrorValue ev = (heap).decode_nonneg_int(cell, integer);	\
    if (ev != EV_NO_ERROR)						\
      {									\
        return ev;							\
      }									\
  } while (0)

ErrorValue
decode_thread(Heap& heap,
	      Object * thread_cell,
	      ThreadTable& thread_table,
	      Thread **thread);

#define DECODE_THREAD_ARG(heap, cell, thread_table, arg_num, thread)	\
do {									\
  const ErrorValue result = decode_thread(heap, cell, thread_table, &thread);	\
  if (result == EV_INST)                                            \
    {                                                                   \
      PSI_ERROR_RETURN(EV_INST, 1);                                     \
    }                                                                   \
  if (result != EV_NO_ERROR)                                        \
    {                                                                   \
      return RV_FAIL;                                                   \
    }                                                                   \
} while (0)								\

/*
ErrorValue
decode_thread_conditions(Heap& heap, AtomTable& atoms,
			 Object * arg,
			 bool& db,
			 double& wait_time);

#define DECODE_THREAD_CONDITIONS_ARG(heap, atoms, arg, arg_num,		\
				     db, wait_time)			\
do {									\
  const ErrorValue ev = decode_thread_conditions(heap, atoms, arg,	\
						 db, 			\
						 wait_time);		\
  if (ev != EV_NO_ERROR)						\
    {									\
      PSI_ERROR_RETURN(ev, arg_num);					\
    }									\
} while (0)
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
		Object *& ip_table_size);

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
		int& ip_table_size);

#define DECODE_DEFAULTS_ARG(heap, cell, arg_num,	\
			    heap_size,			\
			    scratchpad_size,		\
			    binding_trail_size,	       	\
			    other_trail_size,	       	\
			    env_size,			\
			    choice_size,		\
			    name_table_size,		\
			    ip_table_size)		\
do {							\
  const ErrorValue result =				\
    decode_defaults(heap, cell,				\
		    heap_size,				\
		    scratchpad_size,				\
		    binding_trail_size,				\
		    other_trail_size,				\
		    env_size,				\
		    choice_size,			\
		    name_table_size,			\
		    ip_table_size);			\
  if (result != EV_NO_ERROR)				\
    {							\
      PSI_ERROR_RETURN(result, arg_num);		\
    }							\
} while (0)

#endif	//THREAD_DECODE_H
