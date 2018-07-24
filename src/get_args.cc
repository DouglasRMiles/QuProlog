// get_args.cc - Put the list of atoms onto the heap in WAM format.
//		 argv is the list of atoms on the mainline call.
//
//
// Also manages initial goal passed in with -g switch
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
// $Id: get_args.cc,v 1.2 2000/12/13 23:10:01 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;
extern QemOptions *qem_options;
extern char *initial_goal;

//
// Put the list of atoms onto the heap in WAM format. 
// argv is the array of atoms on the mainline call.
// mode(out)
//
Thread::ReturnValue
Thread::psi_get_args(Object *& object1)
{
  Object* tail = AtomTable::nil;
  for (word32 i = qem_options->PrologArgc(); i > 0; i--)
    {
      char* arg = qem_options->PrologArgv()[i - 1];
      if (strcmp(arg, "--") == 0) continue;
      Object* head = atoms->add(arg);
      Cons* temp = heap.newCons(head,tail);
      tail = temp;
    }
  
  object1 = tail;
  return(RV_SUCCESS);
}


//
// Extract the initial goal as a string - fails if no initial goal
//
Thread::ReturnValue 
Thread::psi_initial_goal(Object *& object1)
{
  if (initial_goal == NULL) {
    return(RV_FAIL);
  }
  object1 = heap.newStringObject(initial_goal);
  return(RV_SUCCESS);
}









