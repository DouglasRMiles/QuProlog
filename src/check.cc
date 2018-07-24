// check.cc -
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
// $Id: check.cc,v 1.14 2006/01/31 23:17:49 qp Exp $

#include "atom_table.h"
//#include "dereference.h"
#include "error_value.h"
#include "heap_qp.h"

/* This stupid thing is for VC++ - it has trouble
 * with parens around pointers: eg (char*)
 */
typedef char* charptr;

extern AtomTable *atoms;

ErrorValue
Heap::decode_stream(IOManager& iom,
		    Object* stream_cell,
		    QPStream **stream_handle,
		    const IODirection dir)
{
  assert(dir == INPUT || dir == OUTPUT);

  QPStream *strmptr = NULL;

  if (stream_cell->isInteger())
    {
      const int stream_number = stream_cell->getInteger();
      if (stream_number < 0 || stream_number >= (int)NUM_OPEN_STREAMS)
	{
	  return EV_TYPE;
	}
      strmptr = iom.GetStream(stream_number);
      if (strmptr == NULL)
	{
	  return EV_TYPE;
	}
    }
  else if (stream_cell->isAtom())
    {
          
      if (stream_cell == AtomTable::stream_stdin ||
	  stream_cell == AtomTable::stream_user ||
	  stream_cell == AtomTable::stream_user_input)
	{
	  if (dir == INPUT)
	    {
	      strmptr = iom.StdIn();
	    }
	  else
	    {
	      return EV_NOT_PERMITTED;
	    }
	}
      else if (stream_cell == AtomTable::stream_stdout ||
	       stream_cell == AtomTable::stream_user ||
	       stream_cell == AtomTable::stream_user_output)
	{
	  if (dir == OUTPUT)
	    {
	      strmptr = iom.StdOut();
	    }
	  else
	    {
	      return EV_NOT_PERMITTED;
	    }
	}
      else if (stream_cell == AtomTable::stream_stderr ||
	       stream_cell == AtomTable::stream_user_error)
	{
	  if (dir == OUTPUT)
	    {
	     strmptr = iom.StdErr();
	    }
	  else
	    {
	      return EV_NOT_PERMITTED;
	    }
	}
      else
	{
	  return EV_VALUE;
	}
    }
  else if (stream_cell->isVariable())
    {
      return EV_INST;
    }
  else
    {
      return EV_TYPE;
    }
  
  if (strmptr == NULL)
    {
      return EV_VALUE;
    }
  else if (strmptr->Type() == QPSOCKET)
    {
      return EV_TYPE;
    }

  *stream_handle = strmptr;
  
  return EV_NO_ERROR;
}

ErrorValue
Heap::decode_stream_output(IOManager& iom,
			   Object* stream_cell,
			   QPStream **stream_handle)
{
  const ErrorValue ev = decode_stream(iom, stream_cell, stream_handle, OUTPUT);
  if (ev == EV_NO_ERROR)
    {
      if ((*stream_handle)->getDirection() != INPUT)
	{
	  return EV_NO_ERROR;
	}
      else 
	{
	  return EV_NOT_PERMITTED;
	}
    }
  else
    {
      return ev;
    }
}

ErrorValue
Heap::decode_stream_input(IOManager& iom,
			  Object* stream_cell,
			  QPStream **stream_handle)
{
  const ErrorValue ev = decode_stream(iom, stream_cell, stream_handle, INPUT);
  if (ev == EV_NO_ERROR)
    {
      if ((*stream_handle)->getDirection() != OUTPUT)
	{
	  return EV_NO_ERROR;
	}
      else 
	{
	  return EV_NOT_PERMITTED;
	}
    }
  else
    {
      return ev;
    }
}

ErrorValue
Heap::decode_nonneg_int(Object* integer_cell, int& integer)
{
  if (integer_cell->isVariable())
    {
      return EV_INST;
    }
  else if (integer_cell->isInteger())
    {
      integer = integer_cell->getInteger();
      if (integer < 0)
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

bool
Heap::check_functor(Object* structure,
		    Atom* name, const word32 arity)
{
  if (structure->isStructure() &&
      arity == OBJECT_CAST(Structure*, structure)->getArity())
    {
      return name == OBJECT_CAST(Structure*, structure)->getFunctor();
    }
  else
    {
      return false;
    }
}

bool
Heap::decode_send_options(Object* options,
			  bool& remember_names,
			  bool& encode)
{
  if (options->isVariable())
    {
      return false;
    }
  remember_names = true;
  encode = true;
  if (options == AtomTable::nil)
    {
      return true;
    }
  while(options->isCons())
    {
      Cons* l = OBJECT_CAST(Cons*, options);
      Object* head = l->getHead()->variableDereference();
      options = l->getTail()->variableDereference();
      if (!head->isStructure())
	{
	  return false;
	}
      Structure* st = OBJECT_CAST(Structure*, head);
      Object* func = st->getFunctor()->variableDereference();
      if (func == atoms->add("remember_names"))
	{
	  remember_names = (st->getArgument(1)->variableDereference() 
			    == AtomTable::success);
	}
      else if (func == atoms->add("encode"))
	{
	  encode = (st->getArgument(1)->variableDereference() 
			    == AtomTable::success);
	}
      else
	{
	  return false;
	}
    }

  if (options == AtomTable::nil)
    {
      return true;
    }
  else
    {
      return false;
    }
}

bool
Heap::decode_recv_options(Object* options,
			  Object*& remember_names,
			  Object*& peek,
			  Object*& encode)
{
  if (check_functor(options, AtomTable::tcp_recv_options, 3))
    {
      Structure* str = OBJECT_CAST(Structure*, options);
      
      remember_names = str->getArgument(1)->variableDereference();
      peek = str->getArgument(2)->variableDereference();
      encode = str->getArgument(3)->variableDereference();

      return true;
    }
  else
    {
      return false;
    }
}

ErrorValue
Heap::decode_recv_options(Object* options_object,
			  bool& remember_names,
			  bool& peek,
			  bool& encode)
{
  Object* remember_names_object;
  Object* peek_object;
  Object* encode_object;

  if (options_object->isVariable())
    {
      return EV_INST;
    }
  else if (decode_recv_options(options_object,
			       remember_names_object,
			       peek_object,
			       encode_object))
    {
      if (remember_names_object->isVariable())
	{
	  return EV_INST;
	}
      else if (remember_names_object->isAtom())
	{
	  remember_names = atoms->atomToBool(remember_names_object);
	}
      else
	{
	  return EV_TYPE;
	}

      if (peek_object->isVariable())
	{
	  return EV_INST;
	}
      else if (peek_object->isAtom())
	{
	  peek = atoms->atomToBool(peek_object);
	}
      else
	{
	  return EV_TYPE;
	}

      if (encode_object->isVariable())
	{
	  return EV_INST;
	}
      else if (encode_object->isAtom())
	{
	  encode = atoms->atomToBool(peek_object);
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


bool
Heap::check_atom_list(Object* atom_list_object,
		      size_t& length)
{
  length = 0;

  atom_list_object = atom_list_object->variableDereference();
  for (;atom_list_object->isNil() || atom_list_object->isCons();)
    {
      if (atom_list_object->isNil())
	{
	  return true;
	}
      else if (atom_list_object->isCons())
	{
	  if (! OBJECT_CAST(Cons*, atom_list_object)->getHead()->variableDereference()->isAtom())
	    {
	      return false;
	    }
	  length++;
	  atom_list_object = OBJECT_CAST(Cons*, atom_list_object)->getTail()->variableDereference();
	}
    }

  return false;
}






