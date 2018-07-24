// cut.cc - Cut support routines for interpreter.
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
// $Id: cut.cc,v 1.4 2006/01/31 23:17:49 qp Exp $

#include "thread_qp.h"

//
// psi_get_level(variable)
// Return the current choice point as an integer.
// mode(out)
//
Thread::ReturnValue
Thread::psi_get_level(Object *& object1)
{
  object1 = heap.newInteger(cutPoint);
  return(RV_SUCCESS);
}

//
// psi_delayneckcut(choicepoint)
// Cut the choice back to the specified position.
// Restore X registers - needed to recover from delay handling at neck
// cut.
// mode(in)
//
Thread::ReturnValue
Thread::psi_delayneckcut(Object *& object1)
{
  ChoiceLoc	cut;
  Object* val1 = heap.dereference(object1);
  
  assert(val1->isNumber());
  
  cut = (ChoiceLoc)(val1->getInteger()); 
  if (currentChoicePoint > cut)
    {
      currentChoicePoint = cut;
      choiceStack.cut(cut);
      tidyTrails(choiceStack.getHeapAndTrailsState(cut));
    }
  
  status.resetNeckCutRetry();
  RestoreXRegisters();
  programCounter = savedPC;
  return(RV_SUCCESS);
}

//
// psi_cut(choicepoint)
// Cut the choice back to the specified position.
// mode(in)
//
Thread::ReturnValue
Thread::psi_cut(Object *& object1)
{
  ChoiceLoc	cut;
  Object* val1 = heap.dereference(object1);
  assert(val1->isNumber());
  
  cut = (ChoiceLoc)(val1->getInteger());  
  if (currentChoicePoint > cut)
    {
      currentChoicePoint = cut;
      choiceStack.cut(cut);
      tidyTrails(choiceStack.getHeapAndTrailsState(cut));
    }
  
  return(RV_SUCCESS);
}

