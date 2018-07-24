// check.h - Useful argument checking macros. Used in pseudo-instructions.
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
// $Id: check.h,v 1.5 2005/03/08 00:35:00 qp Exp $

#ifndef	CHECK_H
#define	CHECK_H

// #include "atom_table.h"


#define DECODE_STREAM_ARG(heap, iom, cell, arg_num, stream, dir)	\
  do {									\
    const ErrorValue ev_input =						\
      (heap).decode_stream_input(iom, cell, &stream);			\
    if (ev_input == EV_NO_ERROR)					\
      {									\
	dir = INPUT;							\
      }									\
    else if (ev_input == EV_NOT_PERMITTED)				\
      {									\
	const ErrorValue ev_output =					\
          (heap).decode_stream_output(iom, cell, &stream);		\
	if (ev_output == EV_NO_ERROR)					\
	  {								\
	    dir = OUTPUT;						\
	  }								\
	else								\
	  {								\
	    PSI_ERROR_RETURN(ev_output, arg_num);			\
	  }								\
      }									\
    else								\
      {									\
	PSI_ERROR_RETURN(ev_input, arg_num);				\
      }									\
  } while (0)

#define DECODE_STREAM_OUTPUT_ARG(heap, iom, cell, arg_num, stream)	   \
  do {									   \
    const ErrorValue ev = (heap).decode_stream_output(iom, cell, &stream); \
    if (ev != EV_NO_ERROR)						   \
      {									   \
	PSI_ERROR_RETURN(ev, arg_num);					   \
      }									   \
  } while (0)

#define DECODE_STREAM_INPUT_ARG(heap, iom, cell, arg_num, stream)	  \
  do {									  \
    const ErrorValue ev = (heap).decode_stream_input(iom, cell, &stream); \
    if (ev != EV_NO_ERROR)						  \
      {									  \
	PSI_ERROR_RETURN(ev, arg_num);					  \
      }									  \
  } while (0)

#define CHECK_NUMBER_ARG(cell, arg_num)		\
  do {						\
    if ((cell)->isVariable())			\
      {						\
	PSI_ERROR_RETURN(EV_INST,		\
			 arg_num);		\
      }						\
    if (!(cell)->isNumber())			\
      {						\
	PSI_ERROR_RETURN(EV_TYPE,		\
			 arg_num);		\
      }						\
  } while (0)

#define CHECK_ATOM_ARG(cell, arg_num)		\
  do {						\
    if ((cell)->isVariable())			\
      {						\
	PSI_ERROR_RETURN(EV_INST, arg_num);	\
      }						\
    else if (!(cell)->isAtom())			\
      {						\
	PSI_ERROR_RETURN(EV_TYPE, arg_num);	\
      }						\
  } while (0)

#define CHECK_ATOMIC_ARG(cell, arg_num)			\
  do {							\
    if ((cell)->isVariable())				\
      {							\
	PSI_ERROR_RETURN(EV_INST, arg_num);		\
      }							\
    else if (!(cell)->isAtom() && !(cell)->isNumber())	\
      {							\
	PSI_ERROR_RETURN(EV_TYPE, arg_num);		\
      }							\
  } while (0)

#define CHECK_VARIABLE_ARG(heap, prolog_value, arg_num, var)	\
do {								\
  PrologValue prolog_value(var);				\
  (heap).prologValueDereference(prolog_value);				\
  if (!(prolog_value).getTerm()->isVariable())			\
    {								\
      PSI_ERROR_RETURN(EV_INST, arg_num);			\
    }								\
} while (0)

#define DECODE_SEND_OPTIONS_ARG(heap, cell, arg_num,		\
				remember_names, encode)		\
  do {								\
    const bool result =					\
      (heap).decode_send_options(cell,				\
				 remember_names, encode);	\
    if (!result)					\
      {								\
        PSI_ERROR_RETURN(EV_TYPE, arg_num);			\
      }								\
  } while (0)

#define DECODE_RECV_OPTIONS_ARG(heap, cell, arg_num,			\
			       remember_names, peek, encode)		\
  do {									\
    const ErrorValue result =						\
      (heap).decode_recv_options(cell, remember_names, peek, encode);	\
    if (result != EV_NO_ERROR)						\
      {									\
        PSI_ERROR_RETURN(result, arg_num);				\
      }									\
  } while (0)

#define CHECK_ATOM_LIST_ARG(heap, cell, arg_num)	\
  do {							\
    size_t length = 0;					\
    if ((cell)->isVariable())				\
      {							\
	PSI_ERROR_RETURN(EV_INST, arg_num);		\
      }							\
    else if (! (heap).check_atom_list(cell, length))	\
      {							\
	PSI_ERROR_RETURN(EV_TYPE, arg_num);		\
      }							\
  } while (0)

#define DECODE_BOOLEAN_ARG(atoms, cell, arg_num, b)	\
  do {							\
    if ((cell)->isVariable())				\
      {							\
	PSI_ERROR_RETURN(EV_INST, arg_num);		\
      }							\
    else if (! (cell)->isAtom())				\
      {							\
	PSI_ERROR_RETURN(EV_TYPE, arg_num);		\
      }							\
    b = (atoms).atomToBool(cell);			\
  } while (0)

public:
ErrorValue decode_stream(IOManager&, Object*, QPStream **,
			 const IODirection);

bool check_functor(Object*, Atom*, const word32);

ErrorValue decode_stream_output(IOManager&, Object*, QPStream **);
ErrorValue decode_stream_input(IOManager&, Object*, QPStream **);

ErrorValue decode_nonneg_int(Object*, int&);

//
// Check the options associated with outgoing 
// TCP and IPC communication.
//
bool decode_send_options(Object*, bool&, bool&);

//
// Decode the options associated with incoming
// TCP and IPC/ICM communication.
//
bool decode_recv_options(Object*, Object*&, Object*&, Object*&);

//
// Decode the options associated with incoming
// TCP and IPC/ICM communications.
//
ErrorValue decode_recv_options(Object*, bool&, bool&, bool&);


bool check_atom_list(Object*, size_t&);

#endif	// CHECK_H
