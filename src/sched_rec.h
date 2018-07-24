// sched_rec.h - Scheduler records.
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
// $Id: sched_rec.h,v 1.2 2000/12/12 03:36:21 qp Exp $

#ifndef	SCHED_REC_H
#define	SCHED_REC_H

#include <time.h>

#include "defs.h"

class Thread;

class SchedRec
{
private:
  Thread& thread;
  time_t timeout;
  bool blocked;
  bool removed;
public:
  SchedRec(Thread& t, const word32 p = 0)
    : thread(t), timeout(p), blocked(false), removed(false) { }
  
  Thread& Thr(void) { return thread; }
  time_t Timeout(void) const { return timeout; }
  
  void Block(void) { blocked = true; }
  void Unblock(void) { blocked = false; }
  bool Blocked(void) const { return blocked; }

  void Remove(void) { removed = true; }
  bool Removed(void) const { return removed; }

  bool operator==(const SchedRec& sr) { return &thread == &sr.thread; }
};

#endif	// SCHED_REC_H
