// thread_condition.h -
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
// $Id: thread_condition.h,v 1.2 2002/11/03 08:37:34 qp Exp $

#ifndef	THREAD_CONDITION_H
#define	THREAD_CONDITION_H

#include <iostream>

// Information about the status of the thread.
class ThreadCondition
{
public:
  enum ThreadConditionValue {
    NEW,	// The thread has been created, but not assigned a goal
    RUNNABLE,	// The thread is now runnable
    SUSPENDED,	// The thread is now suspended
    EXITED	// The thread has exited
  };
private:
  ThreadConditionValue condition;
  bool stopped;

public:
  ThreadCondition(void) : condition(NEW), stopped(false) { }

  ThreadConditionValue Condition(void) const { return condition; }
  void Condition(const ThreadConditionValue tcv) { condition = tcv; }

  bool IsStopped(void) const { return stopped; }
  void SetStopped(void) { stopped = true; }
  void ClearStopped(void) { stopped = false; }
};

using namespace std;
// Print out a ThreadCondition in a form that can be read by a person.
extern ostream& operator<<(ostream&, const ThreadCondition&);

#endif	// THREAD_CONDITION_H
