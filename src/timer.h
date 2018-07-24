// timer.h - Managment of timers
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

#ifndef	TIMER_H
#define	TIMER_H

#include "heap_qp.h"
#include "objects.h"
#include "timeval.h"

#define TIMER_HEAP_SIZE 5000
#define TIMER_NUM 100

class Timer
{
 public:
  Thread* thread;
  Object* goal;
  heapobject* next;
  Timeval time;
  u_int id;
  double delta;
  bool one_time;
  
 Timer(Thread* th, Object* g, heapobject* n, double t, u_int i, bool ot) 
   : thread(th), goal(g), next(n), time(t), id(i), delta(t), one_time(ot) 
  {}
  
  void resetTimer(void)
  {
    time = Timeval(delta);
  }

};

class TimerStack
{
 private:
  Timer* timers[TIMER_NUM];
  u_int next_id;
  Heap* current_heap;
  Heap* other_heap;
  int tos;

 public:
  TimerStack(void)
    {
      next_id = 0;
      tos = 0;
      current_heap = new Heap("Timer Heap", TIMER_HEAP_SIZE, false);
      other_heap = new Heap("Timer Heap", TIMER_HEAP_SIZE, false);
    }

  ~TimerStack(void)
    {
      for (int i = 0; i < tos; i++) delete timers[i];
      delete current_heap;
      delete other_heap;
    }
       
  Heap* getHeap(void) { return current_heap; }

  u_int create_timer(Thread* th, Object* goal, double time, 
		     bool one_time);

  bool insert_timer(Timer* t);

  bool delete_timer(Thread* th, u_int id);
  
  void delete_all_timers(Thread* th);

  bool make_timer_goal(Object*&, Heap&);

  void copy_compress_heap(void);

  bool timer_ready(void);
  
  void update_timeout(Timeval& timeout);
};
  
#endif	// TIMER_H
