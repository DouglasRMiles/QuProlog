// bind.cc - Qu-Prolog bindings. 
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
// $Id: bind.cc,v 1.6 2006/01/31 23:17:49 qp Exp $


#include        "thread_qp.h"
//#include        "trail.h"

//
// Bind variable1 to variable2 or variable2 to variable1.
// Assumes both variables are dereferenced.
//
void
Thread::bindVariables(Variable *variable1, Variable *variable2)
{
  assert(variable1 == variable1->variableDereference());
  assert(variable2 == variable2->variableDereference());
  assert(variable1->isVariable());
  assert(variable2->isVariable());
  Variable *junior;
  Variable *senior;
  
  //
  // Find which variable is "younger", and which is "older".
  //

  assert(variable1->isThawed() || variable2->isThawed() || !status.testHeatWave());
  if (variable1->isFrozen())
    {
      junior = variable2;
      senior = variable1;
      if (junior->getName() != NULL && senior->getName() == NULL)
        {
          senior = addExtraInfo(senior);
          updateAndTrailObject(reinterpret_cast<heapobject*>(senior),
                               junior->getName(), Reference::NameOffset);
        }
    }
  else if (variable2->isFrozen())
    {
      junior = variable1;
      senior = variable2;
      if (junior->getName() != NULL && senior->getName() == NULL)
        {
          senior = addExtraInfo(senior);
          updateAndTrailObject(reinterpret_cast<heapobject*>(senior),
                               junior->getName(), Reference::NameOffset);
        }
    }
  else if ((reinterpret_cast<void*>(variable1) < reinterpret_cast<void*>(variable2)))
    {
      junior = variable2;
      senior = variable1;
    }
  else
    {
      junior = variable1;
      senior = variable2;
    }

  if (junior->hasExtraInfo() && !senior->hasExtraInfo())
    {
      Variable* tmp = junior;
      junior = senior;
      senior = tmp;
    }

  if (junior->getDelays()->isCons())
    {
      wakeUpDelayedProblems(junior);
    }

  if (junior->isOccursChecked() && !senior->isOccursChecked())
    {
      trailTag(senior);
      senior->setOccursCheck();
    }
  bindAndTrail(junior, senior);
}

//
// Bind object_variable1 to object_variable2 or object_variable2 to 
// object_variable1 based on age.
//
void
Thread::bindObjectVariables(ObjectVariable *object_variable1, 
			  ObjectVariable *object_variable2)
{
  ObjectVariable *junior;
  ObjectVariable *senior;
  assert(object_variable1->isObjectVariable() 
	       && object_variable1 == object_variable1->variableDereference());
  assert(object_variable2->isObjectVariable() 
	       && object_variable2 == object_variable2->variableDereference());
  
  assert(! object_variable1->isLocalObjectVariable());
  assert(! object_variable2->isLocalObjectVariable());

  //
  // Find which variable is "younger", and which is "older".
  //
  if (object_variable1->isFrozen())
    {
      junior = object_variable2;
      senior = object_variable1;
    }
  else if (object_variable2->isFrozen())
    {
      junior = object_variable1;
      senior = object_variable2;
    }
  else if ((reinterpret_cast<void*>(object_variable1) < reinterpret_cast<void*>(object_variable2)))
    {
      junior = object_variable2;
      senior = object_variable1;
    }
  else
    {
      junior = object_variable1;
      senior = object_variable2;
    }

  //
  // Pass on the name if necessary
  //
  if (junior->getName() != NULL && senior->getName() == NULL)
    {
      updateAndTrailObject(reinterpret_cast<heapobject*>(senior), 
			   junior->getName(), Reference::NameOffset);
    }
  //
  // wake up delays for junior
  //
  if (junior->getDelays()->isCons())
    {
      wakeUpDelayedProblems(junior);
    }

  //
  // Transfer distinctness information from junior to senior.
  //
  if (junior->getDistinctness()->isCons())
    {
      Object* merged = heap.copyDistinctnessList(junior->getDistinctness(), 
						 senior);
      updateAndTrailObject(reinterpret_cast<heapobject*>(senior), 
			   merged, ObjectVariable::DistinctnessOffset);
    }
  bindAndTrail(junior, senior);
}










