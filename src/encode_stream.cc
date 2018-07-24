// encode_stream.cc - Term encoding and decoding.
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
// $Id: encode_stream.cc,v 1.5 2002/11/13 04:04:15 qp Exp $

#include <iostream>
#include <string.h>

#include "config.h"

#include "atom_table.h"
#include "is_ready.h"
#include "thread_qp.h"
#include "scheduler.h"

extern AtomTable *atoms;
extern IOManager *iom;
extern Scheduler *scheduler;

//
// psi_encoded_write(stream, term, atom)
// Encode the term and write the result to the stream.
//
Thread::ReturnValue
Thread::psi_encoded_write(Object *& stream_arg,
			  Object *& term_arg,
			  Object *& remember_names_arg)
{
  Object* argS = heap.dereference(stream_arg);
  Object* argT = term_arg;
  Object* argRN = heap.dereference(remember_names_arg);

  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, argS, 1, stream);

  if (argRN->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 3);
    }
  if (!argRN->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 3);
    }

  // IS_READY_STREAM(stream, -1);
  
  EncodeWrite ew(*this,
		 heap,
		 *stream,
		 argT,
		 *atoms,
		 atoms->atomToBool(argRN),
		 names);

  return BOOL_TO_RV(ew.Success());
}

//
// psi_encoded_read(stream, variable, variable, atom)
// Encode the term and write the result to the stream.
//
Thread::ReturnValue
Thread::psi_encoded_read(Object *& stream_arg, Object *& term_arg,
			 Object *& object_variable_names_arg, 
			 Object *& remember_names_arg)
{
  Object* argS = heap.dereference(stream_arg);
  Object* argRN = heap.dereference(remember_names_arg);
 
  QPStream *stream;
  DECODE_STREAM_INPUT_ARG(heap, *iom, argS, 1, stream);

  if (argRN->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 3);
    }
  if (!argRN->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 3);
    }

  IS_READY_STREAM(stream);

  EncodeRead er(*this,
		heap,
		*stream,
		term_arg,
		*atoms,
		atoms->atomToBool(argRN),
		names,
		object_variable_names_arg);
  return BOOL_TO_RV(er.Success());
}









