// is_ready.h - Handy macros
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
// $Id: is_ready.h,v 1.16 2006/02/14 02:40:09 qp Exp $

#ifndef	IS_READY_H
#define	IS_READY_H

// IS_READY_IO(FD *s,
//	       const time_t timeout)
//
// This macro is used to simplify the coding required when we're checking
// whether an IO operation on a socket or stream is about to be attempted,
// and we're worried that the operation might cause blocking.
#define IS_READY_IO(s)				                        \
do {									\
 /* Ready for action? */						\
 if ((s)->isReady())				                        \
   {									\
     /* Do nothing - we're ready to rock! */				\
   }                                                                    \
 else /* Block */							\
   {									\
     BlockingIOObject* blockobj = new BlockingIOObject(this, (s)->getFD(), (s)->Type(), iom);							\
     scheduler->blockedQueue().push_back(blockobj); 	        	\
     block_status.setBlocked();                                         \
     return RV_BLOCK;							\
   }									\
} while (0)

// IS_READY_MESSAGE(Heap& heap,
//              listist<Message *> queue,
//	        listist<Message *>::iterator iter, int timeout)
//
// This macro is used to simplify the coding required when we're checking
// whether a message operation is about to be attempted,
// and we're worried that the operation might cause blocking.
#define IS_READY_MESSAGE(heap, queue, iter, timeout)			\
do {									\
  /* Timed out? */							\
  if (block_status.isRestartTime())					\
    {									\
      delete &(iter);                                                   \
      return RV_FAIL;							\
    }									\
  /* Skip commited messages.*/						\
  for (;								\
       (iter) != (queue).end() && (*(iter))->Committed();		\
       (iter)++)							\
    ;									\
  /* End of queue? */							\
  if ((iter) == (queue).end())						\
    {									\
      /* Just a poll? */						\
      if ((timeout) == 0)						\
	{								\
          delete &(iter);                                               \
	  return RV_FAIL;						\
	}								\
      else /* Block the thread. */					\
	{								\
          BlockingMessageObject* blockobj = new BlockingMessageObject(this, (timeout), &iter);							\
          scheduler->blockedQueue().push_back(blockobj); 	       	\
          block_status.setBlocked();                                    \
          return RV_BLOCK;						\
	}								\
    }									\
  else /* There's a message to read. Yippee! */				\
    {									\
    }									\
} while (0)


//
// This macro is used to simplify the coding required when we're checking
// whether an IMSTREAM operation is about to be attempted,
// and we're worried that the operation might cause blocking.
#define IS_READY_IMSTREAM(s)	                                \
do {									\
 /* Ready for action? */						\
 if ((s)->isReady())				        \
   {									\
     /* Do nothing - we're ready to rock! */				\
   }                                                                    \
 else /* Block */					\
   {									\
     BlockingIOObject* blockobj = new BlockingIOObject(this, (s)->getFD(), (s)->Type(), iom);							\
     scheduler->blockedQueue().push_back(blockobj); 	        	\
     block_status.setBlocked();                                    \
     return RV_BLOCK;							\
   }									\
} while (0)


#define IS_READY_STREAM(s)                                                  \
do {                                                                        \
     if ((s)->Type() == IMSTREAM)                                           \
       {                                                                    \
         IS_READY_IMSTREAM((s));              \
       }                                                                    \
     else                                                                   \
       {                                                                    \
         IS_READY_IO((s));                                                  \
       }                                                                    \
} while (0)


#define IS_READY_SOCKET(socket)                                             \
do {                                                                        \
      if (scheduler->Status().testEnableTimeslice())                        \
        {                                                                   \
           if (is_ready((socket)->getFD(), QPSOCKET))                         \
             {                                                              \
             }                                                              \
           else /* Block */						\
             {								\
               BlockingIOObject* blockobj = new BlockingIOObject(this, (socket)->getFD(), QPSOCKET, iom);							\
               scheduler->blockedQueue().push_back(blockobj); 	       	\
               block_status.setBlocked();                                    \
               return RV_BLOCK;                                             \
              }                                                             \
        }                                                                   \
} while (0)
               


#endif	// IS_READY_H














