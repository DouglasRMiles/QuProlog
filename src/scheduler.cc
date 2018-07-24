// scheduler.cc - Schedule execution of threads.
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
// $Id: scheduler.cc,v 1.38 2006/03/30 22:50:31 qp Exp $

#include <algorithm>

#include <time.h>
#include <sys/types.h>
#ifndef WIN32
        #include <sys/time.h>
#endif
#include <signal.h>

#include "global.h"
#include "atom_table.h"
#include "code.h"
#include "defs.h"
#include "errors.h"
#include "io_qp.h"
#include "manager.h"
#include "pred_table.h"
#include "protos.h"
#include "scheduler.h"
#include "thread_qp.h"
#include "thread_condition.h"
#include "thread_table.h"
#include "timer.h"

#ifdef WIN32
        #define _WINSOCKAPI_
        #include <windows.h>
        #include <io.h>
#endif
static void
handle_timeslice(int)
{
  #ifdef DEBUG_SCHED
  cerr << __FUNCTION__ << "\n";
  #endif

  extern Scheduler *scheduler;
  scheduler->Status().setTimeslice();
}


#ifdef WIN32
static VOID CALLBACK win32_handle_timer_wrapper(UINT, UINT, DWORD_PTR, 
                                                DWORD_PTR, DWORD_PTR)
{
  handle_timeslice(0);
}
#endif

//
// Determine the length of the scheduler quantum.
//

#ifdef DEBUG_SCHED
static const int32 TIME_SLICE_SECS = 1L;
static const int32 TIME_SLICE_USECS = 1000000L;
#else
static const int32 TIME_SLICE_SECS = 0L;
#ifdef WIN32
static const int32 TIME_SLICE_USECS = 1L;
#else
static const int32 TIME_SLICE_USECS = 1000L;
#endif
#endif

//
// Maximum length to sleep when all threads are blocked.
//
#if defined(DEBUG_SCHED) || defined(DEBUG_IO)
static const int32 SLEEP_USECS = 1000000L;
#else
static const int32 SLEEP_USECS = TIME_SLICE_USECS;
#endif

static void handle_timeslice(int);

extern TimerStack timerStack;

Scheduler::Scheduler(ThreadOptions& to, ThreadTable& tt, 
		     Signals& s, PredTab& p)
  : thread_options(to), thread_table(tt), signals(s), 
    predicates(p),theTimeouts((time_t) -1, 0)
{
  //
  // Allow time slicing.
  //
  scheduler_status.setEnableTimeslice();
}

Scheduler::~Scheduler(void) { }

#ifdef WIN32
extern SOCKET PipeInSock;
#else
extern int* sigint_pipe;
#endif
extern bool in_sigint;


static bool running_sub_scheduler;

Thread::ReturnValue
Scheduler::run_timer_goal(Thread* thread)
{
  Object* SavedX[NUMBER_X_REGISTERS];
  word32 i;
  for (i = 0; i < NUMBER_X_REGISTERS; i++)
    {
      SavedX[i] = thread->X[i];
    }
  heapobject* saved_heap_top = thread->heap.getTop();
  CodeLoc savedPC = thread->programCounter;
  EnvLoc saved_current_env = thread->currentEnvironment;
  ChoiceLoc saved_current_cp = thread->currentChoicePoint;
  CodeLoc saved_continuation_instr = thread->continuationInstr;
  ChoiceLoc saved_cutpoint = thread->cutPoint;
  BlockStatus bs = thread->getBlockStatus();
  Object* goal;
  timerStack.make_timer_goal(goal, thread->heap);
  thread->programCounter =
    predicates.getCode(predicates.lookUp(atoms->add("$call_timer_goals"), 1, atoms, code)).getPredicate(code);
  thread->XRegs()[0] = goal;
  thread->setSuspendGC(true);
  scheduler_status.resetTimeslice();
  const Thread::ReturnValue result = thread->Execute();
  thread->setSuspendGC(false);
  for (i = 0; i < NUMBER_X_REGISTERS; i++)
    {
      thread->X[i] = SavedX[i];
    }
  thread->heap.setTop(saved_heap_top);
  thread->programCounter = savedPC;
  thread->currentEnvironment = saved_current_env;
  thread->currentChoicePoint = saved_current_cp;
  thread->continuationInstr = saved_continuation_instr;
  thread->cutPoint = saved_cutpoint;
  thread->getBlockStatus() = bs;
  return result;
} 


bool Scheduler::poll_fds(Timeval& poll_timeout)
{
  fd_set rfds, wfds;
  FD_ZERO(&rfds);
  FD_ZERO(&wfds);
#ifdef WIN32
  int max_fd = PipeInSock;
  FD_SET((unsigned int)PipeInSock, &rfds);
#else
  int max_fd = sigint_pipe[0];
  FD_SET((unsigned int)sigint_pipe[0], &rfds);
#endif
  for(list<BlockingObject *>::iterator iter = blocked_queue.begin();
	   iter != blocked_queue.end();
	   iter++)
    {
      (*iter)->updateFDSETS(&rfds, &wfds, max_fd);
    }

  for (list <MessageChannel*>::iterator iter = message_channels.begin();
       iter != message_channels.end();
       iter++)
    {
      (*iter)->updateFDSETS(&rfds, &wfds, max_fd);
      (*iter)->processTimeouts(poll_timeout);
    }
  timerStack.update_timeout(poll_timeout);
  int result;
  if (poll_timeout.isForever())
    {
      result = select(max_fd + 1, &rfds, &wfds, NULL, NULL);
    }
  else
    {
      struct timeval timeout = {poll_timeout.Sec(), poll_timeout.MicroSec()};
      result = select(max_fd + 1, &rfds, &wfds, NULL, &timeout);
    }
  return (result > 0) || ((result == 0) && timerStack.timer_ready());

}


Thread::ReturnValue
Scheduler::Sleep()
{
  #ifdef DEBUG_BLOCK
  cerr << __FUNCTION__ << " Sleeping" << "\n";
  #endif
  while (! InterQuantum())
    {
      // Were there any signals while we were napping?
      if (signals.Status().testSignals() && !in_sigint)
	{
          #ifdef DEBUG_SCHED
	  cerr << __FUNCTION__ << " Start signal handler" << "\n";
          #endif
	  const Thread::ReturnValue result = HandleSignal();
          #ifdef DEBUG_SCHED
	  cerr << __FUNCTION__ << " Stop signal handler" << "\n";
          #endif
	  return result;
	}
      if (poll_fds(theTimeouts))
	{
          (void) InterQuantum();
	  break;
	}
      #ifdef DEBUG_SCHED
      cerr << "End poll" << "\n";
      #endif
    }
  #ifdef DEBUG_BLOCK
  cerr << __FUNCTION__ << " Finished sleeping" << "\n";
  #endif
  return Thread::RV_SUCCESS;
}

//
// Perform all the inter quantum actions:
//	Process messages
// 	Check on threads blocked on IO
//	Check on threads blocked on messages
//	Check on threads blocked on waits
//	Check on threads waiting on timeouts
//
bool
Scheduler::InterQuantum(void)
{
  #ifdef DEBUG_SCHED
  cerr << "InterQuantum" << "\n";
  #endif
  // First shuffle any new messages
  (void)ShuffleAllMessages();

  // 
  // Was anything actually done?
  //
  theTimeouts.setTime((time_t) -1, 0);
  return processBlockedThreads();
}


int32
Scheduler::Schedule(void)
{
  running_sub_scheduler = false;
  Thread *thread = new Thread(NULL, thread_options);
  thread->programCounter =
    predicates.getCode(predicates.lookUp(atoms->getAtom(atoms->lookUp("$start")), 0, atoms, code)).getPredicate(code);

  const ThreadTableLoc first = thread_table.AddID(thread);
  if (first == (ThreadTableLoc) -1)
    {
      Fatal(__FUNCTION__, "Couldn't add initial thread to thread table");
    }

  thread_table.IncLive();
  thread->TInfo().SetID(first);

  thread->Condition(ThreadCondition::RUNNABLE);

  const char *symbol = thread_table.MakeName(first).c_str();
  atoms->add(symbol);
  thread->TInfo().SetSymbol(symbol);

  run_queue.push_back(thread);

#ifdef WIN32
  MMRESULT wintimerid;
  //  timerptr = SetTimer(NULL, NULL, 500, &win32_handle_timer_wrapper);
  //  cerr << "timerptr = " << timerptr << endl;
#else
  // Who'd have thought it?! Here's a case where
  // Windows > Unix for C++. Unlike Unix, in
  // Windows you don't need to create the timer
  // ahead of time - you create it and set it
  // simultaneously.

  // Search for "SetTimer" to see where this
  // is done. (Or setitimer for some unices).

  //
  // Get the timeslicing signal happening.
  //
#ifdef SOLARIS
  timer_t timerid;
  struct sigevent se;
  se.sigev_notify = SIGEV_SIGNAL;
  se.sigev_signo = SIGTIMESLICE;
  se.sigev_value.sival_int = 0;
#endif // SOLARIS

  sigset_t sigs;
  sigemptyset(&sigs);
  sigaddset(&sigs, SIGTIMESLICE);

  struct sigaction sa;
  sa.sa_handler = handle_timeslice;
  sa.sa_mask = sigs;
  sa.sa_flags = SA_RESTART;
#if !(defined(SOLARIS) || defined(FREEBSD) || defined(MACOSX))
  sa.sa_restorer = NULL;
#endif // !(defined(SOLARIS) || defined(FREEBSD) || defined(MACOSX))

  SYSTEM_CALL_LESS_ZERO(sigaction(SIGTIMESLICE, &sa, NULL));
#ifdef SOLARIS
  SYSTEM_CALL_LESS_ZERO(timer_create(CLOCK_REALTIME, &se, &timerid));
#endif // SOLARIS
#endif


  while (! run_queue.empty())		// Something to run?
    {
      #ifdef DEBUG_SCHED
      cerr << __FUNCTION__ << "  Threads in run_queue = [";
      for (list<Thread *>::iterator iter = run_queue.begin();
	   iter != run_queue.end();
	   iter++)
	{
	  cerr << (*iter)->TInfo().ID() << " ";
	}
      cerr << ']' << "\n";
      #endif

      size_t blocked = 0;	// Number of threads that have blocked so far

      if (timerStack.timer_ready())
        {
          if (run_timer_goal(thread_table.LookupID(0)) == Thread::RV_HALT)
            {
              return 0;
            }
        }

      //
      // Walk down the run queue, attempting to execute threads as we go...
      //
      for (list<Thread *>::iterator iter = run_queue.begin();
	   iter != run_queue.end();
	   // iterator is incremented at the end of the loop
	   )
	{
	  Thread& thread = **iter;
	  if (thread.Condition() == ThreadCondition::EXITED)
	    {
	      // remove from blocked queue
	      for (list<BlockingObject *>::iterator biter 
		     = blocked_queue.begin();
		   biter != blocked_queue.end();
		   // iterator is advanced in loop
		   )
		{
		  if ((*biter)->getThread() == &thread)
		    {
		      delete *biter;
		      biter = blocked_queue.erase(biter);
		    }
		  else
		    {
		      biter++;
		    }
		}

	      thread_table.RemoveID(thread.TInfo().ID());
	      thread_table.DecLive();
	      delete &thread;
	      
	      // Did it exit while executing in a forbid/permit section?
	      if (scheduler_status.testEnableTimeslice())
		{
		  // No. It's exited nicely.
	          iter = run_queue.erase(iter);
		}
	      else
		{
		  // Yes. It's exited unwisely.
		  Fatal(__FUNCTION__, "Thread exited during forbid/permit section");
		}
	      continue;
	    }

          (void) InterQuantum();

	  BlockStatus& bs = thread.getBlockStatus();

          #ifdef DEBUG_SCHED
	  cerr << __FUNCTION__ << " Trying thread: " 
	       << thread.TInfo().ID() << "\n";
          #endif	// DEBUG_SCHED

	  // Can we run the thread?
	  if (bs.isBlocked())
	    {
              #ifdef DEBUG_BLOCK
	      cerr << __FUNCTION__ << "... previously blocked";
              #endif	// DEBUG_BLOCK

	      // No, try another
              // Are we in a forbid/permit section?
              if (scheduler_status.testEnableTimeslice())
		{
                  #ifdef DEBUG_BLOCK
		  cerr << "\n";
                  #endif

	          blocked++;
	          iter++;
		}
	      else
		{
                  #ifdef DEBUG_BLOCK
		  cerr << " in forbid/permit section" << "\n";
                  #endif

		  const Thread::ReturnValue result = Sleep();
		  if (result == Thread::RV_HALT)
		    {
		      return 0;
		    }
		}
	      continue;
	    }
	  //
	  // Enable the timer for timeslicing
	  //
	  if (1) //scheduler_status.testEnableTimeslice())
	    {
	      scheduler_status.resetTimeslice();
	      
	      //
	      // Initialise the timer.
	      //
#ifndef WIN32
#ifdef SOLARIS
	      struct itimerspec set_timerval =
	      {
		{ 0, 0 },
		{ TIME_SLICE_SECS, TIME_SLICE_USECS }
	      };
#else
	      itimerval set_timerval = 
	      {
		{ 0, 0 },
		{ TIME_SLICE_SECS, TIME_SLICE_USECS }
	      };
#endif // SOLARIS
#endif //WIN32

#ifdef DEBUG_SCHED	      
	      cerr << __FUNCTION__ 
		   << " Initialising the timer ("
		   << TIME_SLICE_SECS
		   << " secs, "
		   << TIME_SLICE_USECS
		   << " usecs)" << "\n";
#endif
#ifdef WIN32 //Alright, let's create AND set the timer CHEESE
              wintimerid = timeSetEvent(TIME_SLICE_USECS, 5, 
                                        &win32_handle_timer_wrapper,
                                        NULL, TIME_ONESHOT);

#else
#ifdef SOLARIS
	      SYSTEM_CALL_LESS_ZERO(timer_settime(timerid, 0, &set_timerval,
	      				  (itimerspec *)NULL));
#else
	      SYSTEM_CALL_LESS_ZERO(setitimer(ITIMER,
					      &set_timerval,
					      (itimerval *) NULL));
#endif // SOLARIS
#endif // WIN32
	    }

	  //
	  // Run the thread until it drops out, for whatever reason
	  //
          #ifdef DEBUG_SCHED
	  cerr << __FUNCTION__
	       << " Start execution of thread " 
	       << thread.TInfo().ID() << "\n";
          #endif // DEBUG_SCHED
	  const Thread::ReturnValue result = thread.Execute();
          #ifdef DEBUG_SCHED 

	  cerr << __FUNCTION__
	       << " Exit execution of thread "
	       << thread.TInfo().ID() << "\n";
          #endif // DEBUG_SCHED

	  {
#ifdef WIN32 //Now we need to kill the timer
            timeKillEvent(wintimerid);
#else
#ifdef SOLARIS
	    struct itimerspec unset_timerval =
	    { 
	      { 0, 0 },
	      { 0, 0 }
	    };

	    SYSTEM_CALL_LESS_ZERO(timer_settime(timerid, 0, &unset_timerval,
						(itimerspec *)NULL));
#else
	    itimerval clear_timerval = 
	    { 
	      { 0, 0 },
	      { 0, 0 }
	    };
	    
	    	    SYSTEM_CALL_LESS_ZERO(setitimer(ITIMER,
	    			    &clear_timerval,
	    			    (itimerval *) NULL));
#endif // SOLARIS
#endif
		    
	  }
	  
	  //
	  // Figure out why execute() exited and take appropriate action.
	  //
	  switch (result)
	    {
	    case Thread::RV_TIMESLICE:
	      //
	      // The timer expired during the thread's execute loop.
	      // This is the normal case ... simply go to the next thread.
	      //
              #ifdef DEBUG_SCHED
	      cerr << "RV_TIMESLICE" << "\n";
              #endif
	      break;
	    case Thread::RV_EXIT:
	      //
	      // The thread exited via a call to thread_exit.
	      //
              #ifdef DEBUG_SCHED
	      cerr << "RV_EXIT" << "\n";
              #endif
	      {
		// Clobber the thread.
		thread_table.RemoveID(thread.TInfo().ID());
		thread_table.DecLive();
		delete &thread;
		break;
	      }
	    case Thread::RV_HALT:
              #ifdef DEBUG_SCHED
	      cerr << "RV_HALT" << "\n";
              #endif
	      // TO DO: Extract exit status from thread's X registers.
	      // TO DO: Mustn't just exit here! (Remember the ICM CS.)
	      return 0;
	      break;
	    case Thread::RV_BLOCK:
              #ifdef DEBUG_SCHED
	      cerr << "RV_BLOCK" << "\n";
              #endif
	      //
	      // The thread attempted an operation that would have blocked.
	      //
	      {
		//
		// Another blocked thread.
		//
		blocked++;
		break;
	      }
	    case Thread::RV_SIGNAL:
	      {
                #ifdef DEBUG_SCHED
		cerr << "RV_SIGNAL" << "\n";
                #endif
		//
		// Set up and execute a thread that executes the appropriate
		// signal handler. Then, continue with the thread that was
		// being executed.
		//
		const Thread::ReturnValue result = HandleSignal();
		if (result == Thread::RV_HALT)
		  {
		    return 0;
		  }
	      }
	      break;
	    case Thread::RV_YIELD:
              #ifdef DEBUG_SCHED
	      cerr << "RV_YIELD" << "\n";
              #endif
	      // Nothing really needs to happen here.
	      break;
	    default:
              #ifdef DEBUG_SCHED
	      cerr << __FUNCTION__ << " Exit with result " << result << "\n";
              #endif	// DEBUG_SCHED
	      
	      return(result);
	      break;
	    }

          // run the timer goals after execution of thread
          if (timerStack.timer_ready())
            {
              if (run_timer_goal(thread_table.LookupID(0)) == Thread::RV_HALT)
                {
                  return 0;
                }
            }

	  // Advance the iterator if appropriate.

	  // Did the thread exit?
	  if (result == Thread::RV_EXIT)
	    {
	      // Did it exit while executing in a forbid/permit section?
	      if (scheduler_status.testEnableTimeslice())
		{
		  // No. It's exited nicely.
		  // delete *iter;
	          iter = run_queue.erase(iter);
		}
	      else
		{
		  // Yes. It's exited unwisely.
		  Fatal(__FUNCTION__, "Thread exited during forbid/permit section");
		}
	    }
	  // Was the thread in a forbid/permit block?
	  else if (scheduler_status.testEnableTimeslice())
	    {
	      // No. It's ok to go to another thread.
	      iter++;
              //(void) InterQuantum();
	    }
          // Thread was executing in a forbid/permit section.
	  // Did it block?
	  else if (result == Thread::RV_BLOCK)
	    {
              #ifdef DEBUG_BLOCK
	      cerr << __FUNCTION__ 
		   << " Thread " << thread.TInfo().ID()
		   << " blocked in forbid/permit section" << "\n";
              #endif

	      // Sleep until something useful happens (maybe).
		  const Thread::ReturnValue result = Sleep();
		  if (result == Thread::RV_HALT)
		    {
		      return 0;
		    }
	      // Iterator isn't advanced.
	    }
          // If anything else happened...
	  else
	    {
	      // Do the inter-quantum actions anyway.
	      //(void) InterQuantum();
	      // Iterator isn't advanced.

	    }
	  //(void)ShuffleAllMessages(); // XXXXXX
	}

      #ifdef DEBUG_SCHED
      cerr << __FUNCTION__ << "  blocked = " << blocked
	   << "(" << run_queue.size() << " in run_queue)" << "\n";
      #endif

      // If none of the threads was runnable...
      if (! run_queue.empty() && blocked_queue.size() == run_queue.size())
	{
          const Thread::ReturnValue result = Sleep();
          if (result == Thread::RV_HALT)
            {
              return 0;
            }
	}
      //
      // Set up for next traversal of the run time queue
      //
      //(void) InterQuantum();

    }

  return 0;
}

bool
Scheduler::processBlockedThreads(void)
{
  int woken = 0;	// Keep track of number of woken threads
      
  for (list<BlockingObject *>::iterator iter = blocked_queue.begin();
       iter != blocked_queue.end();
       // iterator is advanced in loop
       )
    {
      if ((*iter)->unblock(theTimeouts))
	{
	  woken++;
	  if (!(*iter)->isWaitObject())
	    {
	      delete *iter;
	    }
	  iter = blocked_queue.erase(iter);
	}
      else
	{
	  iter++;
	}
    }
  return woken > 0;
}

bool
Scheduler::ShuffleAllMessages(void)
{
  //
  // Distribute the messages that are waiting.
  //

  bool msg_found = false;
  for (list <MessageChannel*>::iterator iter = message_channels.begin();
       iter != message_channels.end();
       iter++)
    {
      if ((*iter)->ShuffleMessages())
	{
	  msg_found = true;
	}
    }
  return msg_found;
}

Thread::ReturnValue
Scheduler::HandleSignal(void)
{
  in_sigint = true;
#ifndef WIN32 // This doesn't do ANYTHING
  char buff[128];
  int ret = read(sigint_pipe[0], buff, 120);
  if (ret == 120) {
	cerr << "HandleSignal: read too much" << "\n";
  }
#else
  char buff[128];
  int ret = recv(PipeInSock, buff, 120, 0);
  if (ret == 120) {
	cerr << "HandleSignal: read too much" << "\n";
  }
#endif
  
  
  Thread *thread = new Thread(NULL, thread_options);
  
  const ThreadTableLoc loc = thread_table.AddID(thread);
  if (loc == (ThreadTableLoc) -1)
    {
      delete thread;
      Fatal(__FUNCTION__, "Couldn't create signal handler thread\n");
    }
  
  thread->TInfo().SetID(loc);
  
  Atom* sig_atom = atoms->add("handle_signal");
  Atom* predicate = atoms->add("$signal_thread_exit");
  Object* problem = thread->BuildCall(predicate, 0);
  thread->programCounter = thread->HandleInterrupt(problem);
  thread->TInfo().Goal() =  sig_atom;
  thread_table.IncLive();
  thread->Condition(ThreadCondition::RUNNABLE);
  
#ifdef DEBUG_SCHED
  cerr << __FUNCTION__ << "  Start execution of signal handler" << "\n";
#endif
  
  Thread::ReturnValue result;
  
  while (true)
    {
      result = thread->Execute();
      if (result == Thread::RV_BLOCK)
	{
	  Sleep();
	}
      else
	{
	  break;
	}
    }
  
#ifdef DEBUG_SCHED
  cerr << __FUNCTION__ << "  Stop execution of signal handler" << "\n";
#endif
  
  thread_table.RemoveID(thread->TInfo().ID());
  thread_table.DecLive();
  delete thread;
  in_sigint = false;
  signals.Status().resetSignals();
  return result;
}

//
// Insert new thread's record before thread in run queue
//
void Scheduler::insertThread(Thread* th, Thread* newth)
{
  for (list<Thread *>::iterator iter = run_queue.begin();
       iter != run_queue.end();
       iter++
       )
    {
      if (**iter == *th)
	{
	  // this makes it insert after parent iter++;
	  (void) run_queue.insert(iter, newth);
	  return;
	}
    }
  assert(false);
}

void Scheduler::deleteThread(Thread *th)
{
  for (list<Thread *>::iterator iter = run_queue.begin();
       iter != run_queue.end();
       // iterator is incremented at the end of the loop
       )
    {
      if (**iter == *th)
	{	  
	  assert(th->Condition() == ThreadCondition::EXITED);
	  // remove from blocked queue
	  for (list<BlockingObject *>::iterator biter 
		 = blocked_queue.begin();
	       biter != blocked_queue.end();
	       // iterator is advanced in loop
	       )
	    {
	      if ((*biter)->getThread() == th)
		{
		  delete *biter;
		  biter = blocked_queue.erase(biter);
		}
	      else
		{
		  biter++;
		}
	    }

	  thread_table.RemoveID(th->TInfo().ID());
	  thread_table.DecLive();
	  delete th;
	      
	  iter = run_queue.erase(iter);
	  break;
	}
      iter++;
    }
}

//
// Reset the thread by removing the thread from the
// blocked queue and clear block status.
//
void Scheduler::resetThread(Thread* th)
{
  // Remove from blocked queue
  //
  for (list<BlockingObject *>::iterator iter = blocked_queue.begin();
       iter != blocked_queue.end();
       )
    {
      BlockingObject& blockingObj = **iter;
      if (blockingObj.getThread() == th)
	{	  
          if (!(*iter)->isWaitObject())
	    {
	      delete *iter;
	    }
	  iter = blocked_queue.erase(iter);
	  break;
	}
      else
        {
          iter++;
        }
    }
  th->getBlockStatus().setRunnable();
}


Thread::ReturnValue
 Scheduler::run_scheduler(list<Thread *> thread_queue)
{
  if (running_sub_scheduler) return Thread::RV_FAIL;
  running_sub_scheduler = true;
#ifdef WIN32
  MMRESULT wintimerid;
#else

#ifdef SOLARIS
  timer_t timerid;
  struct sigevent se;
  se.sigev_notify = SIGEV_SIGNAL;
  se.sigev_signo = SIGTIMESLICE;
  se.sigev_value.sival_int = 0;
#endif // SOLARIS
  sigset_t sigs;
  sigemptyset(&sigs);
  sigaddset(&sigs, SIGTIMESLICE);

  struct sigaction sa;
  sa.sa_handler = handle_timeslice;
  sa.sa_mask = sigs;
  sa.sa_flags = SA_RESTART;
#if !(defined(SOLARIS) || defined(FREEBSD) || defined(MACOSX))
  sa.sa_restorer = NULL;
#endif // !(defined(SOLARIS) || defined(FREEBSD) || defined(MACOSX))

  SYSTEM_CALL_LESS_ZERO(sigaction(SIGTIMESLICE, &sa, NULL));
#ifdef SOLARIS
  SYSTEM_CALL_LESS_ZERO(timer_create(CLOCK_REALTIME, &se, &timerid));
#endif // SOLARIS
#endif

  bool save_enable_timeslice = scheduler_status.testEnableTimeslice();
  bool save_timeslice = scheduler_status.testTimeslice();
  scheduler_status.setTimeslice();
  scheduler_status.setEnableTimeslice();

  #ifdef DEBUG_SCHED
  cerr << __FUNCTION__ << "  Threads in thread_queue = [";
  for (list<Thread *>::iterator iter = thread_queue.begin();
       iter != thread_queue.end();
       iter++)
    {
      cerr << (*iter)->TInfo().ID() << " ";
    }
  cerr << ']' << "\n";
  #endif
  for (list<Thread *>::iterator iter = thread_queue.begin();
       iter != thread_queue.end();
       iter++
       )
    {

      Thread& thread = **iter;
      if (thread.Condition() == ThreadCondition::EXITED)
        {
          // remove from blocked queue
          for (list<BlockingObject *>::iterator biter 
                 = blocked_queue.begin();
               biter != blocked_queue.end();
               // iterator is advanced in loop
               )
            {
              if ((*biter)->getThread() == &thread)
                {
                  delete *biter;
                  biter = blocked_queue.erase(biter);
                }
              else
                {
                  biter++;
                }
            }
          
          thread_table.RemoveID(thread.TInfo().ID());
          thread_table.DecLive();
          delete &thread;
	  
          // Did it exit while executing in a forbid/permit section?
          if (scheduler_status.testEnableTimeslice())
            {
              // No. It's exited nicely.
              iter = run_queue.erase(iter);
            }
          else
            {
              // Yes. It's exited unwisely.
              Fatal(__FUNCTION__, "Thread exited during forbid/permit section");
            }
          continue;
        }
      

      (void) InterQuantum(); // try to unblock
      
      BlockStatus& bs = thread.getBlockStatus();
      if (bs.isBlocked()) continue;  // ignore blocked threads
      
      //
      // Enable the timer for timeslicing
      //
      scheduler_status.resetTimeslice();
      
      //
      // Initialise the timer.
      //
#ifndef WIN32
#ifdef SOLARIS
      struct itimerspec set_timerval =
        {
          { 0, 0 },
          { TIME_SLICE_SECS, TIME_SLICE_USECS }
        };
#else
      itimerval set_timerval = 
        {
          { 0, 0 },
          { TIME_SLICE_SECS, TIME_SLICE_USECS }
        };
#endif // SOLARIS
#endif //WIN32
      
      #ifdef DEBUG_SCHED	      
      cerr << __FUNCTION__ 
           << " Initialising the timer ("
           << TIME_SLICE_SECS
           << " secs, "
           << TIME_SLICE_USECS
           << " usecs)" << "\n";
      #endif
#ifdef WIN32 //Alright, let's create AND set the timer CHEESE
      wintimerid = timeSetEvent(TIME_SLICE_USECS, 5, 
                                &win32_handle_timer_wrapper,
                                NULL, TIME_ONESHOT);
      
#else
#ifdef SOLARIS
      SYSTEM_CALL_LESS_ZERO(timer_settime(timerid, 0, &set_timerval,
                                          (itimerspec *)NULL));
#else
      SYSTEM_CALL_LESS_ZERO(setitimer(ITIMER,
                                      &set_timerval,
                                      (itimerval *) NULL));
#endif // SOLARIS
#endif // WIN32
      
      //
      // Run the thread until it drops out, for whatever reason
      //
      #ifdef DEBUG_SCHED
      cerr << __FUNCTION__
           << " Start execution of thread " 
           << thread.TInfo().ID() << "\n";
      #endif // DEBUG_SCHED
      const Thread::ReturnValue result = thread.Execute();
      #ifdef DEBUG_SCHED 
      
      cerr << __FUNCTION__
           << " Exit execution of thread "
           << thread.TInfo().ID() << "\n";
      #endif // DEBUG_SCHED
      
      {
#ifdef WIN32 //Now we need to kill the timer
        timeKillEvent(wintimerid);
#else
#ifdef SOLARIS
        struct itimerspec unset_timerval =
          { 
            { 0, 0 },
            { 0, 0 }
          };
        
        SYSTEM_CALL_LESS_ZERO(timer_settime(timerid, 0, &unset_timerval,
                                            (itimerspec *)NULL));
#else
        itimerval clear_timerval = 
          { 
            { 0, 0 },
            { 0, 0 }
          };
        
        SYSTEM_CALL_LESS_ZERO(setitimer(ITIMER,
                                        &clear_timerval,
                                        (itimerval *) NULL));
#endif // SOLARIS
#endif
        
      }
      
      //
      // Figure out why execute() exited and take appropriate action.
      //
      switch (result)
        {
        case Thread::RV_TIMESLICE:
          //
          // The timer expired during the thread's execute loop.
          // This is the normal case ... simply go to the next thread.
          //
          #ifdef DEBUG_SCHED
          cerr << "RV_TIMESLICE" << "\n";
          #endif
          break;
        case Thread::RV_EXIT:
          //
          // The thread exited via a call to thread_exit.
          //
          #ifdef DEBUG_SCHED
          cerr << "RV_EXIT" << "\n";
          #endif
          {
            thread.Condition(ThreadCondition::EXITED);
            // Clobber the thread.
            //thread_table.RemoveID(thread.TInfo().ID());
            //thread_table.DecLive();
            //delete &thread;
            break;
          }
        case Thread::RV_HALT:
          #ifdef DEBUG_SCHED
          cerr << "RV_HALT" << "\n";
          #endif
          return Thread::RV_HALT;
          break;
        case Thread::RV_BLOCK:
          #ifdef DEBUG_SCHED
          cerr << "RV_BLOCK" << "\n";
          #endif
          break;
        case Thread::RV_SIGNAL:
          {
            #ifdef DEBUG_SCHED
            cerr << "RV_SIGNAL" << "\n";
            #endif
            //
            // Set up and execute a thread that executes the appropriate
            // signal handler. Then, continue with the thread that was
            // being executed.
            //
            const Thread::ReturnValue result = HandleSignal();
            if (result == Thread::RV_HALT)
              {
                return Thread::RV_HALT;
              }
          }
          break;
        case Thread::RV_YIELD:
          #ifdef DEBUG_SCHED
          cerr << "RV_YIELD" << "\n";
          #endif
          // Nothing really needs to happen here.
          break;
        default:
          #ifdef DEBUG_SCHED
          cerr << __FUNCTION__ << " Exit with result " << result << "\n";
          #endif	// DEBUG_SCHED
	  
          //return(result);
          break;
        }
      
      
    }
  if (save_enable_timeslice)
    scheduler_status.setEnableTimeslice();
  else
    scheduler_status.resetEnableTimeslice();
  if (save_timeslice)
    scheduler_status.setTimeslice();
  else
    scheduler_status.resetTimeslice();
  running_sub_scheduler = false;
  return Thread::RV_SUCCESS;
}
