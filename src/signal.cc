// signals.cc -
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
// $Id: signal.cc,v 1.2 2002/11/03 08:37:32 qp Exp $

#include <iostream>

#include "config.h"

#include "signals.h"

Signals::Signals(void)
{
  signals[SIGINT].init("SIGINT");
#if 0
  signals[SIGHUP].init("SIGHUP");
  signals[SIGINT].init("SIGINT");
  signals[SIGQUIT].init("SIGQUIT");
  signals[SIGILL].init("SIGILL");
  signals[SIGTRAP].init("SIGTRAP");
  signals[SIGIOT].init("SIGIOT");
  signals[SIGABRT].init("SIGABRT");
#ifdef SIGEMT
  signals[SIGEMT].init("SIGEMT");
#endif	// SIGEMT
  signals[SIGBUS].init("SIGBUS");
  signals[SIGFPE].init("SIGFPE");
  signals[SIGKILL].init("SIGKILL");
  signals[SIGSEGV].init("SIGSEGV");
#ifdef SIGSYS
  signals[SIGSYS].init("SIGSYS");
#endif	// SIGSYS
  signals[SIGPIPE].init("SIGPIPE");
  signals[SIGALRM].init("SIGALRM");
  signals[SIGTERM].init("SIGTERM");
  signals[SIGSTKFLT].init("SIGSTKFLT");
  signals[SIGUSR1].init("SIGUSR1");
  signals[SIGUSR2].init("SIGUSR2");
  signals[SIGCLD].init("SIGCLD");
  signals[SIGCHLD].init("SIGCHLD");
  signals[SIGCONT].init("SIGCONT");
  signals[SIGSTOP].init("SIGSTOP");
  signals[SIGTSTP].init("SIGTSTP");
  signals[SIGPWR].init("SIGPWR");
  signals[SIGWINCH].init("SIGWINCH");
  signals[SIGURG].init("SIGURG");
  signals[SIGPOLL].init("SIGPOLL");
  signals[SIGIO].init("SIGIO");
  signals[SIGTTIN].init("SIGTTIN");
  signals[SIGTTOU].init("SIGTTOU");
  signals[SIGVTALRM].init("SIGVTALRM");
  signals[SIGPROF].init("SIGPROF");
  signals[SIGXCPU].init("SIGXCPU");
  signals[SIGXFSZ].init("SIGXFSZ");
#ifdef SIGWAITING
  signals[SIGWAITING].init("SIGWAITING");
#endif	// SIGWAITING
#ifdef SIGLWP
  signals[SIGLWP].init("SIGLWP");
#endif        // SIGLWP
#ifdef SIGFREEZE
  signals[SIGFREEZE].init("SIGFREEZE");
#endif        // SIGFREEZE
#ifdef SIGTHAW
  signals[SIGTHAW].init("SIGTHAW");
#endif        // SIGTHAW
#endif // 0

}




