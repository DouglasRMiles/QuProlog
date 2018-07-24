// signal.cc - Support predicates for signal.
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
// $Id: signal_escapes.cc,v 1.6 2006/01/31 23:17:51 qp Exp $

#include <sys/types.h>
#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include <signal.h>
#include "scheduler.h"
#include "signals.h"

#ifndef WIN32
extern "C" int kill(pid_t, int);
#endif


#include "thread_qp.h"

extern Signals *signals;

//
// psi_clear_signal(signal number)
// Remove any waiting signal for a given signal number.
// mode(in)
//
Thread::ReturnValue
Thread::psi_clear_signal(Object *& object1)
{
  Object* val1 = heap.dereference(object1);

  assert(val1->isShort());

  signals->Clear(val1->getInteger());

  return(RV_SUCCESS);
}

//
// psi_clear_all_signals
// Remove all waiting signals.
// mode()
//
Thread::ReturnValue
Thread::psi_clear_all_signals(void)
{
  for (int i = 1; i < NSIG + 1; i++)
    {
      signals->Clear(i);
    }

  return(RV_SUCCESS);
}

//
// psi_default_signal_handler(signal number)
// Call the default signal handler.
// mode(in)
//
Thread::ReturnValue
Thread::psi_default_signal_handler(Object *& object1)
{
  Object* val1 = heap.dereference(object1);

  assert(val1->isShort());

  int sig = val1->getInteger();

#ifdef WIN32
  TerminateProcess(GetCurrentProcess(), 0);
#else
  kill(getpid(), sig);
#endif

  return(RV_SUCCESS);
}









