// timer.cc - Managment of timers
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

#include "timer.h"
#include "copy_term.h"
#include "thread_qp.h"

u_int
TimerStack::create_timer(Thread* th, Object* goal, double time, 
			 bool one_time)
{
  Object* copy = th->TheHeap().copyTerm(goal, *current_heap);
  heapobject* toh = current_heap->getTop();
  Timer* t = new Timer(th, copy, toh, time, next_id, one_time);
  if (insert_timer(t))
    {
      return next_id++;
    }
  else
    {
      Fatal(__FUNCTION__, "Out of timer space");
      return (u_int)(-1);
    }

}

bool
TimerStack::insert_timer(Timer* it)
{
  int i = tos-1;
  
  for (; i >= 0; i--) 
    {
      Timer* t = timers[i];
      if ((t == NULL) || (it->time < t->time))
	{
	  timers[i+1] = t;
	}
      else
	{
	  break;
	}
    }
  timers[i+1] = it;
  tos++;
  return (tos < TIMER_NUM-1);
}

bool
TimerStack::delete_timer(Thread* th, u_int id)
{
  bool found = false;
  for (int i = 0; i < tos; i++)
    {
      if (found)
	{
	  timers[i] = timers[i+1];
	}
      else
	{
	  Timer* t = timers[i];
	  if ((t != NULL) && (t->thread == th) && (t->id == id))
	    {
	      found = true;
	      delete t;
	      timers[i] = NULL;
	    }
	}
    }
  if (found) tos--;

  return found;
}

void
TimerStack::delete_all_timers(Thread* th)
{
  int count = 0;
  for (int i = 0; i < tos; i++)
    {
      Timer* t = timers[i];
      if ((t != NULL) && (t->thread == th))
	{
	  count++;
	  delete t;
	  timers[i] = NULL;
	}
    }
  // compress
  int next = 0;
  for (int i = 0; i < tos; i++)
    {
      Timer* t = timers[i];
      timers[next] = t;
      if (t != NULL)
	{
	  next++;
	}
    }
  tos -= count;

}

bool
TimerStack::make_timer_goal(Object*& goal, Heap& dest)
{
  Timeval now = Timeval();
  int i = tos-1;
  Timer* t = NULL;
  bool found = false;
  for (; i >= 0; i--)
    {
      t = timers[i];
      if (t->time <= now)
	{
	  found = true;
	  break;
	}
    }
  if (!found) return false;

  int ind = i+1;
  goal = AtomTable::nil;
  for (; i >= 0; i--)
    {
      t = timers[i];
      Cons* lst = dest.newCons(t->goal, goal);
      goal = OBJECT_CAST(Object*, lst);
      if (!t->one_time)
	{
	  t->resetTimer();
	  insert_timer(t);
	  timers[i] = NULL;
	}
      else
	{
	  delete t;
	  timers[i] = NULL;
	}
    }
  // compress
  int next = 0;
  for (int i = ind; i < tos; i++)
    {
      Timer* t = timers[i];
      timers[next] = t;
      if (t != NULL)
	{
	  next++;
	}
    }
  tos = next;
  copy_compress_heap();
  return true;
}

void 
TimerStack::copy_compress_heap(void)
{
  other_heap->setTop( other_heap->getBase());
  for (int i = 0; i < tos; i++)
    {
      Timer* t = timers[i];
      Object* copy = current_heap->copyTerm(t->goal, *other_heap);
      t->goal = copy;
    }
  Heap* tmp = current_heap;
  current_heap = other_heap;
  other_heap = tmp;
}

bool 
TimerStack::timer_ready(void)
{
  Timeval now;
  return ((tos > 0) && (timers[0]->time <= now));
}

void  
TimerStack::update_timeout(Timeval& tout)
{
  if (tos > 0)
    {
      Timeval now;
      Timeval delta(timers[0]->time, now);
      if (delta < tout) tout = delta;
    }
}
