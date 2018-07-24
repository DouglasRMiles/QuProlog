// stream_escapes.cc - I/O stream manipulations.
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
// $Id: stream_escapes.cc,v 1.15 2006/01/31 23:17:51 qp Exp $

#include <errno.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "atom_table.h"
#include "io_qp.h"
#include "system_support.h"
#include "thread_qp.h"
#include "unify.h"
#include "pedro_env.h"



extern AtomTable *atoms;
extern IOManager *iom;
extern PedroMessageChannel *pedro_channel;
//
// psi_get_open_streams(StreamList)
// Make a list of all the open stream nums.
// mode psi_get_open_streams(out)
//
Thread::ReturnValue
Thread::psi_get_open_streams(Object *& result)
{
  result = AtomTable::nil;
  for (u_int i = 0; i < NUM_OPEN_STREAMS; i++)
    {
      if (iom->GetStream(i) != NULL)
	{
	  Cons* list = heap.newCons(heap.newInteger(i), result);
	  result = list;
	}
    }
  return RV_SUCCESS;
}

//
// psi_open(file, iomode, var)
// Open the file for the specified mode.
//
Thread::ReturnValue
Thread::psi_open(Object *& filename_arg,
		 Object *& access_mode_arg,
		 Object *& stream_arg)
{
  Object* argF = heap.dereference(filename_arg);
  Object* argAM = heap.dereference(access_mode_arg);
  
  if (argF->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!argF->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  if (argAM->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!argAM->isShort())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  const wordptr mode = argAM->getInteger();
  
  if (!(mode <= AM_APPEND))
    {
      PSI_ERROR_RETURN(EV_VALUE, 2);
    }
  
  //
  // Open the file.
  //
//PORT
//#ifdef WIN32
  // See comments in io.cc
//  string tempstr = wordexp(atoms->getAtomString(OBJECT_CAST(Atom*, argF)));
//  const char *file = tempstr.c_str();
//#else
//  const char *file = wordexp(atoms->getAtomString(OBJECT_CAST(Atom*, argF))).c_str();
//#endif
  string filename = OBJECT_CAST(Atom*, argF)->getName();
  wordexp(filename);
  char file[1024];
  strcpy(file, filename.c_str());


  switch (mode)
    {
    case AM_READ:
      {
	QPistream *stream = new QPistream(file);

	if (stream->bad())
	  {
	    delete stream;
	    PSI_ERROR_RETURN(EV_VALUE, 0);
	  }

	//
	// Return index of the stream.
	//
	stream_arg = heap.newInteger(iom->OpenStream(stream));
	return RV_SUCCESS;
      }
      break;
    case AM_WRITE:
      {
	QPostream *stream = new QPostream(file, ios::out|ios::trunc);

	if (stream->bad())
	  {
	    delete stream;
	    PSI_ERROR_RETURN(EV_VALUE, 0);
	  }

	//
	// Return index of the stream.
	//
	stream_arg = heap.newInteger(iom->OpenStream(stream));
	return RV_SUCCESS;
      }
      break;
    case AM_APPEND:
      {
	QPostream *stream = new QPostream(file, ios::out|ios::app);

	if (stream->bad())
	  {
	    delete stream;
	    PSI_ERROR_RETURN(EV_VALUE, 0);
	  }

	//
	// Return index of the stream.
	//
	stream_arg = heap.newInteger(iom->OpenStream(stream));
	return RV_SUCCESS;
	break;
      }
    }

  return RV_FAIL;
}

//
// psi_open_string(string, iomode, type, variable)
// Open a string stream.
//
Thread::ReturnValue
Thread::psi_open_string(Object *& string_arg,
			Object *& access_mode_arg,
			Object *& type_arg,
			Object *& stream_arg)
{
  Object* argS = heap.dereference(string_arg);
  Object* argAM = heap.dereference(access_mode_arg);
  Object* argT = heap.dereference(type_arg);

  if (argAM->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!argAM->isShort())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  wordptr mode = argAM->getInteger();
  
  if (!(mode <= AM_APPEND))
    {
      PSI_ERROR_RETURN(EV_VALUE, 2);
    }
  
  switch (mode)
    {
    case AM_READ:
      {
	//
	// Check the string type and the string.
	//
	
	if (argS->isVariable())
	  {
	    PSI_ERROR_RETURN(EV_INST, 1);
	  }
	if (!argS->isAtom() && !argS->isCons() && !argS->isString())
	  {
	    PSI_ERROR_RETURN(EV_TYPE, 1);
	  }
	
	if (argT->isVariable())
	  {
	    PSI_ERROR_RETURN(EV_INST, 3);
	  }
	if (!argT->isShort())
	  {
	    PSI_ERROR_RETURN(EV_TYPE, 3);
	  }
	
	if (argT->getInteger() == 0)
	  {
	    QPistringstream *stream = new QPistringstream(OBJECT_CAST(Atom*, argS)->getName());
	    
	    //
	    // Return the index of the stream.
	    //
	    stream_arg = heap.newInteger(iom->OpenStream(stream));
	    return RV_SUCCESS;
	  }
	else if (argT->getInteger() == 1)
	  {
	    //
	    // Open strstream for converting a list of characters
	    // to an array, and then for reading.
	    //
	    ostringstream *strstr = new ostringstream;

	    //
	    // Converting a list of characters to an array.
	    //
	    while (argS->isCons())
	      {
		Cons* list = OBJECT_CAST(Cons*, argS);
		Object* head = heap.dereference(list->getHead());
		
		if (!head->isShort())
		  {
		    PSI_ERROR_RETURN(EV_VALUE, 1);
		  }
		
		if (strstr->good() &&
		    strstr->put(head->getInteger()).fail())
		  {
		    delete strstr;
		    return RV_FAIL;
		  }
		argS = heap.dereference(list->getTail());
	      }

	    if (argS->isString())
	      {
		*strstr << OBJECT_CAST(StringObject*, argS)->getChars();
	      }
	    QPistringstream *stream = new QPistringstream(strstr->str());
	    delete strstr;
	    //
	    // Return the index of the stream.
	    //
	    stream_arg = heap.newInteger(iom->OpenStream(stream));
	    return RV_SUCCESS;
	  }

	else if (argT->getInteger() == 2)
	  {
	    assert(argS->isString());
	    QPistringstream *stream = 
	      new QPistringstream(OBJECT_CAST(StringObject*, argS)->getChars());
            //  Return the index of the stream.
	    stream_arg = heap.newInteger(iom->OpenStream(stream));
	    return RV_SUCCESS;
          }
	else
	  {
	    PSI_ERROR_RETURN(EV_VALUE, 3);
	  }
      }
    break;
    case AM_WRITE:
      {
	QPostringstream *stream = new QPostringstream;
	//
	// Return the index of the stream.
	//
	stream_arg = heap.newInteger(iom->OpenStream(stream));
	return RV_SUCCESS;
      }
    break;
    }
  
  return RV_FAIL;
}

//
// psi_close(stream_index, force)
// Close the specified stream.
//
Thread::ReturnValue
Thread::psi_close(Object *& stream_arg,
		  Object *& force_arg)
{
  Object* strm = heap.dereference(stream_arg);
  Object* force = heap.dereference(force_arg);
  //
  // Check arguments.
  //
  QPStream *stream;
  IODirection dir;
  DECODE_STREAM_ARG(heap, *iom, strm, 1, stream, dir);

  if (force->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!force->isShort())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  
  const wordptr force_val = force->getInteger();     // PJR used??
  if (!(force_val <= 1))
    {
      PSI_ERROR_RETURN(EV_VALUE, 2);
    }
  
  //stream->close();
  return BOOL_TO_RV(iom->CloseStream(strm->getInteger()));
}

//
// psi_current_input(variable)
// Return the current input stream index.
//
Thread::ReturnValue
Thread::psi_current_input(Object *& stream_arg)
{
  stream_arg = heap.newInteger(iom->CurrentInput());
  return RV_SUCCESS;
}

//
// psi_current_output(variable)
// Return the current output stream index.
//
Thread::ReturnValue
Thread::psi_current_output(Object *& stream_arg)
{
  stream_arg = heap.newInteger((wordptr) iom->CurrentOutput());
  return RV_SUCCESS;
}

//
// psi_set_input(stream_index)
// Switch current input stream to the new index.
//
Thread::ReturnValue
Thread::psi_set_input(Object *& stream_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  
  QPStream *stream;
  DECODE_STREAM_INPUT_ARG(heap, *iom, stream_object, 1, stream);
  
  //
  // Change stream.
  //
  iom->SetCurrentInput(stream_object->getInteger());
  
  return RV_SUCCESS;
}

//
// psi_set_output(stream_index)
// Switch current output stream to the new index.
//
Thread::ReturnValue
Thread::psi_set_output(Object *& stream_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  //
  // Check argument.
  //
  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, stream_object, 1, stream);
  
  //
  // Change stream.
  //
  iom->SetCurrentOutput(stream_object->getInteger());
  
  return RV_SUCCESS;
}

//
// psi_flush_output(stream_index)
// Flush the output stream.
//
Thread::ReturnValue
Thread::psi_flush_output(Object *& stream_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  //
  // Check argument.
  //
  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, stream_object, 1, stream);
  
  //
  // Flush the output stream.
  //
  stream->flush();

  
  return RV_SUCCESS;
}

//
// psi_set_autoflush(stream)
// Set the output stream to be unbuffered - i.e. flushes at each output.
//
Thread::ReturnValue
Thread::psi_set_autoflush(Object *& stream_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  //
  // Check argument.
  //
  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, stream_object, 1, stream);
  
  //
  // Set auto flush - fails if not an QPofdstream or an QPomstream
  //
  return BOOL_TO_RV(stream->set_autoflush());
}

//
// psi_at_end_of_stream(stream_index)
// Succeed if the input stream reaches the end of the stream.
//
Thread::ReturnValue
Thread::psi_at_end_of_stream(Object *& stream_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  //
  // Check argument.
  //
  QPStream *stream;
  IODirection dir;
  DECODE_STREAM_ARG(heap, *iom, stream_object, 1, stream, dir);
  
  //
  // Check the input stream.
  //
  errno = 0;

  if (stream->isOutput())
    {
      return RV_FAIL;
    }
  else if (! stream->isReady())
    {
      return RV_FAIL;
    }
  else if (stream->eof() && errno == 0)
    {
      stream->clear(ios::failbit);
      return RV_SUCCESS;
    }

  if (errno == 4)
   {
     stream->clear();
   }
  return RV_FAIL;
}

//
// psi_past_end_of_stream(stream_index)
// Succeed if the input stream passes the end of the stream.
//
Thread::ReturnValue
Thread::psi_past_end_of_stream(Object *& stream_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  //
  // Check argument.
  //
  QPStream *stream;
  IODirection dir;
  DECODE_STREAM_ARG(heap, *iom, stream_object, 1, stream, dir);
  
  //
  // Check the input stream.
  //
  if (stream->isOutput())
    {
      return RV_FAIL;
    }
  else
    {
      return BOOL_TO_RV(stream->fail());
    }
}

//
// psi_reset_stream(stream_index)
// Reset the input stream.
//
Thread::ReturnValue
Thread::psi_reset_stream(Object *& stream_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  //
  // Check argument.
  //
  QPStream *stream;
  DECODE_STREAM_INPUT_ARG(heap, *iom, stream_object, 1, stream);

  //
  // Reset the input stream.
  //
  stream->clear();

  return RV_SUCCESS;
}

//
// psi_stream_position(stream_index, variable)
// Get the stream position.
//
Thread::ReturnValue
Thread::psi_stream_position(Object *& stream_arg, Object *& pos_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  //
  // Check argument.
  //
  QPStream *stream;
  IODirection dir;
  DECODE_STREAM_ARG(heap, *iom, stream_object, 1, stream, dir);

  //
  // Get position.
  //
  int32 pos = 0;

  pos = stream->tell();
  
  //
  // Return the position.
  //
  pos_arg = heap.newInteger(pos);
  return RV_SUCCESS;
}

//
// psi_set_stream_position(stream_index, position)
// Set the stream to the specified absolute position.
//
Thread::ReturnValue
Thread::psi_set_stream_position(Object *& stream_arg, Object *& pos_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  Object* pos_object = heap.dereference(pos_arg);
  //
  // Check argument.
  //
  QPStream *stream;
  IODirection dir;
  DECODE_STREAM_ARG(heap, *iom, stream_object, 1, stream, dir);

  CHECK_NUMBER_ARG(pos_object, 2);

  int32 pos = pos_object->getInteger();
  if (pos < 0)
    {
      PSI_ERROR_RETURN(EV_RANGE, 2);
    }
  
  //
  // Change position.
  //
  if (stream->isInput())
    {
      stream->seekg(pos);
    }
  else
    {
      stream->seekp(pos);
    }
  
  return RV_SUCCESS;
}

//
// psi_line_number(stream_index, variable)
// Get the line number.
//
Thread::ReturnValue
Thread::psi_line_number(Object *& stream_arg, Object *& line_num_arg)
{
  Object* stream_object = heap.dereference(stream_arg);
  //
  // Check argument.
  //
  QPStream *stream;
  IODirection dir;
  DECODE_STREAM_ARG(heap, *iom, stream_object, 1, stream, dir);

  //
  // Get position and return the position.
  //
  line_num_arg = heap.newInteger(stream->lineNumber());
  return RV_SUCCESS;
}


//
// psi_stdin(stream)
// Gets the stream associated with standard input.
//
Thread::ReturnValue 
Thread::psi_stdin(Object *& stream_object)
{
  stream_object = heap.newInteger(reinterpret_cast<wordptr>(iom->StdIn()));

  return RV_SUCCESS;
}

//
// psi_stdout(stream)
// Gets the stream associated with standard output.
//
Thread::ReturnValue 
Thread::psi_stdout(Object *& stream_object)
{
  stream_object = heap.newInteger(reinterpret_cast<wordptr>(iom->StdOut()));

  return RV_SUCCESS;
}

//
// psi_stderr(stream)
// Gets the stream associated with standard error.
//
Thread::ReturnValue 
Thread::psi_stderr(Object *& stream_object)
{
  stream_object = heap.newInteger(reinterpret_cast<wordptr>(iom->StdErr()));

  return RV_SUCCESS;
}


//
// psi_open_msgstream(address, iomode, variable)
// Open a message stream.
//
Thread::ReturnValue
Thread::psi_open_msgstream(Object *& address,
			   Object *& access_mode_arg,
			   Object *& stream_arg)
{
  Object* argS = heap.dereference(address);
  Object* argAM = heap.dereference(access_mode_arg);

  if (argAM->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!argAM->isShort())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  wordptr mode = argAM->getInteger();
  
  if (!(mode < AM_APPEND))
    {
      PSI_ERROR_RETURN(EV_VALUE, 2);
    }
  
  switch (mode)
    {
    case AM_READ:
      {
	string addr = pedro_write(argS);
	string addrs;
	
	// remove spaces
	for (string::size_type i = 0; i < addr.length(); i++) {
	  if (addr.at(i) != ' ') addrs.push_back(addr.at(i));
	}
	QPimstream *stream = new QPimstream(addrs, pedro_channel);
	//
	// Return the index of the stream.
	//
	int iom_fd = iom->OpenStream(stream);
	stream->setFD(iom_fd);
	stream_arg = heap.newInteger(iom_fd);
	return RV_SUCCESS;
      }
    break;
    case AM_WRITE:
      {
	assert(argS->isStructure());
	Structure* addr = OBJECT_CAST(Structure*, argS);
	assert(addr->getArity() == 2);
	Structure* caddr = OBJECT_CAST(Structure*, addr->getArgument(1)->variableDereference());
	assert(caddr->getArity() == 2);
	QPomstream *stream 
	  = new QPomstream(caddr->getArgument(1)->variableDereference(),
			   caddr->getArgument(2)->variableDereference(),
			   addr->getArgument(2)->variableDereference(),
			   pedro_channel);
	//
	// Return the index of the stream.
	//
	stream_arg = heap.newInteger(iom->OpenStream(stream));
	return RV_SUCCESS;
      }
    break;
    }
  
  return RV_FAIL;
}

//
// psi_set_stream_properties(stream, properties)
// Set the stream properties.
// mode (in,in)
//
Thread::ReturnValue 
Thread::psi_set_stream_properties(Object *& stream_num, Object *& prop)
{
  Object* strnum = heap.dereference(stream_num);
  int dir;
  QPStream* stream;
  DECODE_STREAM_ARG(heap, *iom, strnum, 1, stream, dir);
  Object* props = heap.dereference(prop);

  assert(props->isStructure() && 
	       OBJECT_CAST(Structure*, props)->getArity() == 7);
#ifndef NDEBUG
    for (u_int i = 1; i <= 7; i++)
      {
	assert(OBJECT_CAST(Structure*, props)->getArgument(i)->variableDereference()->isConstant());
      }
#endif
  stream->setProperties(props);
  return RV_SUCCESS;
}

//
// psi_get_stream_properties(stream, properties)
// Get the stream properties.
// mode (in,out)
//
Thread::ReturnValue 
Thread::psi_get_stream_properties(Object *& stream_num, Object *& prop)
{
  Object* strnum = heap.dereference(stream_num);

  assert(strnum->isNumber());

  u_int snum = strnum->getInteger();

  if (snum >= NUM_OPEN_STREAMS || iom->GetStream(snum) == NULL)
    {
      return RV_FAIL;
    }

  prop = iom->GetStream(snum)->getProperties();
  return RV_SUCCESS;
}

//
// set_std_stream(stdstream, newstream)
// replace the stream with number stdstream (0,1,2) with newstream.
// mode (in,in)
//
Thread::ReturnValue
Thread::psi_set_std_stream(Object *& std_stream_num, Object *& new_stream_num)
{
  Object* std_num = heap.dereference(std_stream_num);
  Object* new_num = heap.dereference(new_stream_num);
  
  if (std_num->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (new_num->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!std_num->isNumber())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (!new_num->isNumber())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  if (iom->set_std_stream(std_num->getInteger(), new_num->getInteger()))
    {
      return RV_SUCCESS;
    }
   PSI_ERROR_RETURN(EV_VALUE, 1);
}


//
// reset_std_stream(stdstream)
// reset the stream with number stdstream (0,1,2).
// mode (in,in)
//
Thread::ReturnValue
Thread::psi_reset_std_stream(Object *& std_stream_num)
{
  Object* std_num = heap.dereference(std_stream_num);
  
  if (std_num->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!std_num->isNumber())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (iom->reset_std_stream(std_num->getInteger()))
    {
      return RV_SUCCESS;
    }
   PSI_ERROR_RETURN(EV_VALUE, 1);
}









