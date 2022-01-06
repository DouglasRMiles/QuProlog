// bios.cc - Basic I/O.
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
// $Id: bios.cc,v 1.10 2005/03/08 00:34:59 qp Exp $

#include <errno.h>
#include <iostream>

// For lstat(2) call.
#include <stdio.h>
#include <sys/stat.h>
#ifdef WIN32
        #include <io.h>
#else
        #include <unistd.h>
#endif


#include "config.h"

#include "atom_table.h"
#include "is_ready.h"
#include "thread_qp.h"
#include "scheduler.h"

extern AtomTable *atoms;
extern IOManager *iom;
extern Scheduler *scheduler;

//
// psi_get_char(stream_index, variable)
// Get the next character from the input stream.
//
Thread::ReturnValue
Thread::psi_get_char(Object *& stream_arg, Object *& char_arg)
{
  Object * argS = heap.dereference(stream_arg);
  
  //
  // Check argument.
  //
  QPStream *stream;
  DECODE_STREAM_INPUT_ARG(heap, *iom, argS, 1, stream);
  
  IS_READY_STREAM(stream);

  char c[2] = { '\0', '\0' };

  //
  // Get the character.
  //
  int ch;

  ch = stream->get();

  if (ch == '\n')
    {
      stream->newline();
    }

  if (ch != -1)  // EOF
    {
      c[0] = ch;
    }

  //
  // Return the character.
  //
  char_arg = atoms->add(c);
  return RV_SUCCESS;
}
//
// psi_peek(stream_index, variable)
// Peek the next character from the input stream.
//
Thread::ReturnValue
Thread::psi_peek(Object *& stream_arg, Object *& char_arg)
{
  Object * argS = heap.dereference(stream_arg);
  
  //
  // Check argument.
  //
  QPStream *stream;
  DECODE_STREAM_INPUT_ARG(heap, *iom, argS, 1, stream);
  
  IS_READY_STREAM(stream);

  char c[2] = { '\0', '\0' };

  //
  // Peek the character.
  //
  int ch;

  ch = stream->get();
  stream->unget();
  if (ch != -1)  // EOF
    {
      c[0] = ch;
    }

  //
  // Return the character.
  //
  char_arg = atoms->add(c);
  return RV_SUCCESS;
}

#define CHECK_CHAR_ARG(object, arg_num, c)	        \
  do {							\
    if (object->isVariable())			        \
      {							\
	PSI_ERROR_RETURN(EV_INST, arg_num);		\
      }							\
    if (!object->isAtom())			      	\
      {							\
	PSI_ERROR_RETURN(EV_TYPE, arg_num);		\
      }							\
    c = *(OBJECT_CAST(Atom*, object)->getName());             \
  } while (0)

//
// psi_put_char(stream_index, character)
// Put the character into the output stream.
//
Thread::ReturnValue
Thread::psi_put_char(Object *& stream_arg,
		     Object *& char_arg)
{
  Object * argS = heap.dereference(stream_arg);
  Object * argC = heap.dereference(char_arg);
  
  //
  // Check arguments.
  //
  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, argS, 1, stream);

  //  IS_READY_STREAM(stream, -1);

  char c;
  CHECK_CHAR_ARG(argC, 2, c);

  if (stream->good() && !stream->put(c))
    {
      return RV_FAIL;
    }
  
  return RV_SUCCESS;
}

//
// psi_get_code(stream_index, variable)
// Get the next character from the input stream.
//
Thread::ReturnValue
Thread::psi_get_code(Object *& stream_arg,
		     Object *& code_arg)
{
  Object * argS = heap.dereference(stream_arg);

  //
  // Check argument.
  //
  QPStream *stream;
  DECODE_STREAM_INPUT_ARG(heap, *iom, argS, 1, stream);

  IS_READY_STREAM(stream);

  //
  // Get the character.
  //
  int ch;

  ch = stream->get();

  if (ch == '\n')
    {
      stream->newline();
    }

  //
  // Return the character.
  //
  code_arg = heap.newShort(ch);
  return RV_SUCCESS;
}

#define DECODE_CODE_ARG(object, arg_num, c)		\
  do {							\
    if (object->isVariable())				\
      {							\
	PSI_ERROR_RETURN(EV_INST, arg_num);		\
      }							\
    if (!object->isShort())				\
      {							\
	PSI_ERROR_RETURN(EV_TYPE, arg_num);		\
      }							\
    c = object->getInteger();		       		\
    if (!(0 <= c && c <= 255))				\
      {							\
        PSI_ERROR_RETURN(EV_RANGE, arg_num);	        \
      }							\
  } while (0)

//
// psi_put_code(stream_index, byte)
// Put the byte into the output stream.
//
Thread::ReturnValue
Thread::psi_put_code(Object *& stream_arg,
		     Object *& byte_arg)
{
  Object * argS = heap.dereference(stream_arg);
  Object * argB = heap.dereference(byte_arg);

  //
  // Check argument.
  //
  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, argS, 1, stream);

  int32 c;
  DECODE_CODE_ARG(argB, 2, c);

  // IS_READY_STREAM(stream, -1);

  //
  // Put the byte.
  //

  if (stream->good() && !stream->put(static_cast<char>(c)))
    {
      return RV_FAIL;
    }
  
  return RV_SUCCESS;
}


//
// psi_get_line(stream_index, variable)
// Get the next line from the input stream.
// The newline character is consumed but not added to the return
// value.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_get_line(Object *& stream_arg,
                     Object *& str)
{
  Object* argS = heap.dereference(stream_arg);
  
  //
  // Check argument.
  //
  QPStream *stream;
  DECODE_STREAM_INPUT_ARG(heap, *iom, argS, 1, stream);

  IS_READY_STREAM(stream);
  
  string chars;

  Object**  strPtr = &str;
  
  int c;
  c = stream->get();
  // EOF ?
  // if (c == -1)
  //   {
  //     *strPtr = heap.newInteger((int8)(-1));
  //     return RV_SUCCESS;
  //   }

  while (true)
    {
      if (c == -1)
        {
	  break;
        }
      if (c == '\n')
	{
	  stream->newline();
          chars.push_back(c);
	  break;
	}
      else
	{
	  chars.push_back(c);
	}
      // if (stream->eof())
      //   {
      //     c = -1;
      //   }
      // else
      //   {
          c = stream->get();
          //}
    }
  //  if (chars.length() == 0)
  //  *strPtr = heap.newStringObject(;
  //else
    *strPtr = heap.newStringObject(chars.c_str());
  return RV_SUCCESS;
}


//
// psi_put_line(stream_index, list)
// Put the ASCII list to the stream - add a newline character.
//
// mode(in, in)

Thread::ReturnValue 
Thread::psi_put_line(Object *& stream_arg, Object *& code_list)
{
  Object* argS = heap.dereference(stream_arg);
  
  //
  // Check argument.
  //
  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, argS, 1, stream);
  Object* chars = heap.dereference(code_list);

  if (chars->isList())
    {

      // Check input
      int size = 3;
      Object* list = chars;
      for (;
	   list->isCons();
	   list = OBJECT_CAST(Cons*, list)->getTail()->variableDereference())
	{
          int32 c;
	  DECODE_CODE_ARG(OBJECT_CAST(Cons*, list)->getHead()->variableDereference(), 2, c);
	  size++; 
	}
      if (!list->isNil())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 2);
	}
      
      // Write to stream
      char* buf = new char[size];
      int i = 0;
      for (Cons* list = OBJECT_CAST(Cons*, chars);
	   list->isCons();
	   list = OBJECT_CAST(Cons*, list->getTail()->variableDereference()))
	{
	  int32 c;
	  DECODE_CODE_ARG(list->getHead()->variableDereference(), 2, c);
	  buf[i++] = (char)c;
	}
      buf[i++] = '\n';
      buf[i] = '\0';
      *stream << buf;
      delete buf;
      return RV_SUCCESS;
    }

  if (chars->isString())
    {
      StringObject* chars_string = OBJECT_CAST(StringObject*, chars);
      *stream << chars_string->getChars();
      *stream << '\n';
      return RV_SUCCESS;
    }

  PSI_ERROR_RETURN(EV_TYPE, 2);

}
