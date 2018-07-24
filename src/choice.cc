// choice.cc - Definition of a choice point.
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
// $Id: choice.cc,v 1.6 2002/11/03 08:37:24 qp Exp $

#include "area_offsets.h"
#include "choice.h"
#include "code.h"
#include "defs.h"
#include "environment.h"
#include "indent.h"
#include "thread_qp.h"



//
// Restore the heap and name table back to the previous state
// recorded in a choice point.
//
inline void Choice::restoreHeapNameTable(Thread& th) const
  {
    th.backtrackTo(heapAndTrailsState);
  }                                                                             
//
// Restore the thread back to the previous state recorded in a
// choice point.
//
void Choice::restore(Thread& th) const
{
  word32 i;

  th.getStatus() = status;
  th.ContinuationInstr() = continuationInstr;
  restoreHeapNameTable(th);
  th.CurrentEnvironment() = currentEnvironment;
  
  th.EnvStack().setTop(envStackTop);
  
  th.MetaCounter() = metaCounter;
  th.ObjectCounter() = objectCounter;
  
  for (i = 0; i < NumArgs; i++)
    {
      th.XRegs()[i] = X[i];
    }
}

//
// Push a new choice point onto the stack.  The current state of the
// thread is saved in the choice point and the location of the
// alternative is recorded.  The pointer to the newly created choice
// point is then returned.
// If ChoiceLoc or StackLoc changes representation, then a bug may
// occur if this is not changed.
//
//  ChoiceLoc ChoiceStack::push(Thread& th,
//  			    const CodeLoc alternative,
//  			    const word32 NumXRegs)
//  {
//    ChoiceLoc	index;
//    EnvLoc	TopEnv;
  
//    index = pushRecord(size(NumXRegs));
  
//    if (isEnvProtected(th.CurrentChoicePoint(), th.CurrentEnvironment()))
//      {
//        TopEnv = getEnvTop(th.CurrentChoicePoint());
//      }
//    else
//      {
//        TopEnv = th.CurrentEnvironment() +
//  	th.EnvStack().envSize(th.CurrentEnvironment());
//      }
    
//    fetchChoice(index)->assign(th, NumXRegs, TopEnv);
//    nextClause(index) = alternative;
  
//    return(index);
//  }

//
// Pop the current choice point and return a pointer to previous
// choice point.
//
//  ChoiceLoc       ChoiceStack::pop(const ChoiceLoc loc)
//    {
//      ChoiceLoc	previous;
    
//      previous = fetchChoice(loc)->getPreviousChoice();
//      popRecord();
    
//      return(previous);
//    }

//
// Upon failure, set the registers up for the execution of the next
// alternative from a given choice point.
//
//void ChoiceStack::getNextAlternative(Thread& th, const ChoiceLoc index)
//{ 
//  th.ProgramCounter() = nextClause(index);
//  th.CutPoint() = fetchChoice(index)->getCutPoint();
//}

//
// Display meaningful fields for debugging
ostream&
ChoiceStack::Display(ostream& ostrm, ChoiceLoc index, const size_t depth) const
{
  const Choice *c = inspectChoice(index);
  
  Indent(ostrm, depth);
  ostrm << "nextClause=" << hex << c->inspectNextClause() << dec << endl;

  Indent(ostrm, depth);
  ostrm << "currentEnvironment=" << hex <<  c->currentEnv() << dec << endl;

  Indent(ostrm, depth);
  ostrm << "envStackTop=" << hex << c->getEnvTop() << dec << endl;

  Indent(ostrm, depth);
  ostrm << "previousChoicePoint=" << hex << c->getPreviousChoice() << dec << endl;
  Indent(ostrm, depth);
  ostrm << "cutPoint=" << hex << c->getCutPoint() << dec << endl;
 
  Indent(ostrm, depth);
  ostrm << "numArgs=" << hex << c->getNumArgs() << dec << endl;

  return ostrm;
}










