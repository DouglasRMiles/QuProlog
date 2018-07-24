// scheduler.h -
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
// $Id: scheduler.h,v 1.13 2006/02/14 02:40:09 qp Exp $

#ifndef	SCHEDULER_H
#define	SCHEDULER_H

#include <list>

#include "atom_table.h"
#include "block.h"
#include "code.h"
#include "defs.h"
#include "manager.h"
#include "pred_table.h"
//#include "sched_rec.h"
#include "scheduler_status.h"
#include "signals.h"
#include "status.h"
//#include "string_qp.h"
#include "thread_qp.h"
#include "thread_options.h"
#include "thread_table.h"
#include "timeout.h"

#define SIGTIMESLICE (SIGVTALRM)
#define ITIMER (ITIMER_VIRTUAL)

class Thread;

class Scheduler
{
private:
  SchedulerStatus scheduler_status;

  //
  // Queues
  //
  list<Thread *> run_queue;			// Threads to run

  list<BlockingObject *> blocked_queue;		// Blocked threads

  list <MessageChannel*> message_channels;       // All the message channels

  ThreadOptions& thread_options;

  ThreadTable& thread_table;

  Signals& signals;

  PredTab& predicates;

#ifdef WIN32
  UINT_PTR timerptr;
#endif

  Timeval theTimeouts;           // Calculated in IterQuantum to determine of 
	                         // Sleep is a block or a timeout

  Thread::ReturnValue run_timer_goal(Thread* thread);

  //
  // Perform actions between thread executions.
  // Return true if any threads were woken.
  //
  bool InterQuantum(void);

  //
  // Process all blocked threads.
  // Return true if any threads were woken.
  //
  bool processBlockedThreads(void);
  
  //
  // Set up and execute a signal handling thread.
  //
  Thread::ReturnValue HandleSignal();
  
  // Shuffle all the messages onto thread's message queues
  bool ShuffleAllMessages(void);
  
  // Look for fd's that are ready
  bool poll_fds(Timeval&);

public:
  Scheduler(ThreadOptions& to, ThreadTable& tt, Signals& s, PredTab& p);
	    
  ~Scheduler(void);

  // Do the scheduling.
  int32 Schedule(void);

  list<Thread *>& runQueue(void) { return run_queue; }
  list<BlockingObject *>& blockedQueue(void) { return blocked_queue; }

  SchedulerStatus& Status(void) { return scheduler_status; }

  list <MessageChannel*>& getChannels(void) { return message_channels; }

  // Sleeps waiting for IO or messages to become ready.
  Thread::ReturnValue Sleep();

  void insertThread(Thread*, Thread*);
  void deleteThread(Thread*);
  void resetThread(Thread*);
  Thread::ReturnValue run_scheduler(list<Thread *>);

};

#ifdef WIN32
//void CALLBACK win32_handle_timer_wrapper(HWND hWnd, UINT nMsg,

//                           UINT_PTR nIDEvent, DWORD dwTime);
#endif

#endif	// SCHEDULER_H




