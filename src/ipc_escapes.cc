// ipc_escapes.cc - Interprocess communication.
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
// $Id: ipc_escapes.cc,v 1.30 2006/04/04 01:56:36 qp Exp $

#include <algorithm>

#include <sys/types.h>
#include <sys/types.h>
#ifdef WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif

#include "config.h"

#include "atom_table.h"
#include "global.h"
#include "is_ready.h"
#include "thread_qp.h"
#include "thread_table.h"
#include "timeval.h"
#include "tcp_qp.h"
#include "pedro_env.h"

extern AtomTable *atoms;
extern const char *Program;
extern char *process_symbol;

#define DECODE_REFERENCE_ARG(heap, object, arg_num, reference)		  \
  do {									  \
    if (object->isVariable())						  \
      {									  \
	PSI_ERROR_RETURN(EV_INST, arg_num);				  \
      }									  \
    if (!object->isNumber())						  \
      {									  \
	PSI_ERROR_RETURN(EV_TYPE, arg_num);				  \
      }									  \
    reference = reinterpret_cast<list<Message *>::iterator *> (object->getInteger()); \
  } while (0)

#define DECODE_NONNEG_INT_ARG(heap, object, arg_num, val)	\
  do {							\
    if (object->isVariable())				\
      {							\
	PSI_ERROR_RETURN(EV_INST, arg_num);		\
      }							\
    else if (!object->isNumber())			\
      {							\
	PSI_ERROR_RETURN(EV_TYPE, arg_num);		\
      }							\
    else if (object->getInteger() < 0)			\
      {							\
	PSI_ERROR_RETURN(EV_TYPE, arg_num);		\
      }							\
    val = object->getInteger();  			\
  } while (0)

// --------------------------------------------------------------------------
//
// PSEUDO INSTRUCTIONS
//
// --------------------------------------------------------------------------


//
// ipc_make_iterator(reference_out)
//
// Create an iterator for use with ipc_first and ipc_next
//
// mode(out)
//
//
Thread::ReturnValue 
Thread::psi_make_iterator(Object *& reference_cell)
{
  list<Message *>::iterator *iter = new list<Message *>::iterator;

  Structure* iterstr = heap.newStructure(1);
  iterstr->setFunctor(AtomTable::dollar);
  iterstr->setArgument(1, heap.newInteger(reinterpret_cast<wordptr> (iter)));
  reference_cell = iterstr;

  return RV_SUCCESS;
}

//
// Get the first thing on the message queue for this thread.
//
Thread::ReturnValue
Thread::psi_ipc_first(Object *& reference0_cell,
		      Object *& timeout_cell,
                      Object *& reference1_cell)
{
  Object* reference0_str = heap.dereference(reference0_cell);
  Object* timeout_arg = heap.dereference(timeout_cell);

  assert(reference0_str->isStructure());
  Object* reference0_arg = 
     OBJECT_CAST(Structure*, reference0_str)->getArgument(1);

  list<Message *>::iterator *iter = NULL;
  DECODE_REFERENCE_ARG(heap, reference0_arg, 1, iter);

  if (iter == NULL)
    {
      Fatal(__FUNCTION__, "Null iterator");
    }

  double timeout;
  DECODE_TIMEOUT_ARG(heap, timeout_arg, 2, timeout);

  *iter = message_queue.begin();

  IS_READY_MESSAGE(*atoms, message_queue, *iter, timeout);

  (**iter)->IncReferences();

  reference1_cell = reference0_str;
  
  return RV_SUCCESS;
}

// Get the next thing on the message queue for this thread.
Thread::ReturnValue
Thread::psi_ipc_next(Object *& reference0_cell,
		     Object *& reference1_cell,
		     Object *& timeout_cell)
{
  Object* reference0_str = heap.dereference(reference0_cell);
  Object* timeout_arg = heap.dereference(timeout_cell);
 
  assert(reference0_str->isStructure());
  Object* reference0_arg = 
     OBJECT_CAST(Structure*, reference0_str)->getArgument(1);
  if (reference0_arg == AtomTable::dollar) return RV_FAIL;

  list<Message *>::iterator *iter = NULL;
  DECODE_REFERENCE_ARG(heap, reference0_arg, 1, iter);

  if (iter == NULL)
    {
      Fatal(__FUNCTION__, "Null iterator");
    }

  double timeout;
  DECODE_TIMEOUT_ARG(heap, timeout_arg, 2, timeout);

  // Save the current position
  Message& message = ***iter;

  // Advance to the next message
  (*iter)++;

  IS_READY_MESSAGE(heap, message_queue, *iter, timeout);

  message.DecReferences();
  
  (**iter)->IncReferences();
  
  reference1_cell =  reference0_str;
  
  return RV_SUCCESS;
}
		   
Thread::ReturnValue
Thread::psi_ipc_get_message(Object *& message_cell,
			    Object *& reference_cell,
			    Object *& from_handle_cell,
			    Object *& remember_names_cell)
{
  Object* reference_str = heap.dereference(reference_cell);
  Object* remember_names_arg = heap.dereference(remember_names_cell);

  assert(reference_str->isStructure());
  Object* reference_arg = 
     OBJECT_CAST(Structure*, reference_str)->getArgument(1);

  list<Message *>::iterator *iter = NULL;
  DECODE_REFERENCE_ARG(heap, reference_arg, 2, iter);

  if (iter == NULL)
    {
      Fatal(__FUNCTION__, "Null iterator");
    }

  bool remember_names;
  DECODE_BOOLEAN_ARG(*atoms, remember_names_arg, 5, remember_names);
  
  Message& message = ***iter;

  message.constructMessage(from_handle_cell, 
			   message_cell, *this, *atoms, remember_names);

  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_ipc_commit(Object *& reference_cell)
{
  Object* reference_str = heap.dereference(reference_cell);
  assert(reference_str->isStructure());
  Object* reference_arg = 
    OBJECT_CAST(Structure*, reference_str)->getArgument(1);


  OBJECT_CAST(Structure*, reference_str)->setArgument(1, AtomTable::dollar);

  list<Message *>::iterator *iter;
  DECODE_REFERENCE_ARG(heap, reference_arg, 1, iter);

  if (iter == NULL)
    {
      Fatal(__FUNCTION__, "Null iterator");
    }

  Message *message = **iter;

  message->Commit();
  message->DecReferences();

  if (message->References() == 0)
    {
      delete message;
      (void)message_queue.erase(*iter);
    }
  delete iter;

  return RV_SUCCESS;
}




//
// Broadcast message to all current local threads
// mode(in)
//
Thread::ReturnValue
Thread::psi_broadcast(Object *& message_cell)
{


  Object* msg_obj = heap.dereference(message_cell);

  string m = pedro_write(msg_obj);
  m.append("\n");

  for (ThreadTableLoc loc = 0; loc < thread_table->Size(); loc++)
    {
      if ((*thread_table)[loc] != NULL)
	{
	  Thread& thread = *(thread_table->LookupID(loc));
	  thread.MessageQueue().push_back(new PedroMessage(m));
	}
    }
  return RV_SUCCESS;
}


