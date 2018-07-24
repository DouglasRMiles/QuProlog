// timer_escapes.cc - Timer procedures
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

#include <errno.h>

//#include "config.h"

//#include "global.h"
#include "atom_table.h"

#include "thread_qp.h"

#include "timer.h"

extern TimerStack timerStack;

Thread::ReturnValue
Thread::psi_create_timer(Object *& goal_arg, Object *& time_arg, 
			 Object *& one_time_arg, Object *& timer_id)
{
  Object* ga = heap.dereference(goal_arg);
  Object* ta = heap.dereference(time_arg);
  Object* ota = heap.dereference(one_time_arg);
  if (!ta->isNumber())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  if (!ota->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 3);
    }
  bool one_time = (ota == AtomTable::success);
  Object* ga_copy = heap.copyTerm(ga, *(timerStack.getHeap()));
  double time;
  if (ta->isDouble()) time = ta->getDouble();
  else time = ta->getInteger();
  if (time < 0) PSI_ERROR_RETURN(EV_TYPE, 2);
  u_int id = timerStack.create_timer(this, ga_copy, time, one_time);
  if (id == (u_int)(-1))
    return RV_FAIL;
  timer_id = heap.newInteger(id);
  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_delete_timer(Object *& id_arg)
{
  Object* idobj = heap.dereference(id_arg);
  assert(idobj->isInteger());
  u_int id = (u_int)(idobj->getInteger());
  if (timerStack.delete_timer(this, id))
    return RV_SUCCESS;
  else
    return RV_FAIL;
}

Thread::ReturnValue
Thread::psi_timer_goals(Object *& goals)
{
  Object* g;
  if (timerStack.make_timer_goal(g, heap))
    {
      goals = timerStack.getHeap()->copyTerm(g, heap);
      return RV_SUCCESS;
    }
  return RV_FAIL;
}
