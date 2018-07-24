// scheduler_status.h -
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
// $Id: scheduler_status.h,v 1.2 2001/12/17 04:27:33 qp Exp $

#ifndef	SCHEDULER_STATUS_H
#define	SCHEDULER_STATUS_H

#include "defs.h"
#include "status.h"

class SchedulerStatus : private Status <word8>
{
private:
  static const word8 ENABLE_TIMESLICE = 0x01;
  static const word8 TIMESLICE = 0x02;
  static const word8 RESTART = 0x04;		// Restart from front of queue

public:
  //
  // Set flags.
  //
  void setEnableTimeslice(void)	{ set(ENABLE_TIMESLICE); }
  void setTimeslice(void)	{ set(TIMESLICE); }
  void setRestart(void)		{ set(RESTART); }
  //
  // Clear flags.
  //
  void resetEnableTimeslice(void)	{ reset(ENABLE_TIMESLICE); }
  void resetTimeslice(void)		{ reset(TIMESLICE); }
  void resetRestart(void)		{ reset(RESTART); }
  //
  // Test flags.
  //
  bool testEnableTimeslice(void) const	{ return test(ENABLE_TIMESLICE); }
  bool testTimeslice(void) const	{ return test(TIMESLICE); }
  bool testRestart(void) const		{ return test(RESTART); }

};
#endif	// SCHEDULER_STATUS_H

