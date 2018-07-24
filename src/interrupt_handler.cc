// interrupt_handler.cc -
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
// $Id: interrupt_handler.cc,v 1.7 2006/01/31 23:17:50 qp Exp $

#include <signal.h>
#include <stdlib.h>
#include <time.h>
#ifdef WIN32
#include <io.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif
#include <iostream>

#include "errors.h"
#include "interrupt_handler.h"
#include "signals.h"

#ifdef _POSIX_THREAD_IS_GNU_PTH
#define sigwait __pthread_sigwait
#endif // _POSIX_THREAD_IS_GNU_PTH

extern const char *Program;

void *
interrupt_handler(void *s)
{
  if (s == NULL)
    {
      Fatal(__FUNCTION__, "Null signals argument");
    }

  Signals& signals = *(Signals *) s;
  
  sigset_t sigm;
  int sig;

  sigfillset(&sigm);
  SYSTEM_CALL_NON_ZERO(pthread_sigmask(SIG_SETMASK, &sigm, NULL));

  sigset_t sigs;
  sigemptyset(&sigs);
  sigaddset(&sigs, SIGINT);
 
  for (;;)
    {
      (void) sigwait(&sigs, &sig);


#ifdef DEBUG_SCHED
      cerr << __FUNCTION__ << " received " << sig << endl;
#endif

      signals.Increment(sig);
      signals.Status().setSignals();

    }

  assert(false);

  return NULL;
}


