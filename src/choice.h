// choice.h - Definition of a choice point.
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
// $Id: choice.h,v 1.10 2006/01/31 23:17:49 qp Exp $

#ifndef	CHOICE_H
#define	CHOICE_H

#include <iostream>

#include "area_offsets.h"
#include "code.h"
#include "defs.h"
#include "magic.h"
#include "prolog_value.h"
#include "qem_options.h"
#include "record_stack.h"
#include "thread_status.h"

class	Thread;

//
// Record the state of a heap and the trails when a choice point is created.
//
class	HeapAndTrailsChoice
{
private:
  heapobject*		heapTop;
  TrailLoc          bindingTrailTop;
  TrailLoc          otherTrailTop;

public:
  //
  // Save the tops of the heap and the trails.
  //
  void save(heapobject* hloc, const TrailLoc btloc,  const TrailLoc otloc)
  {
    heapTop = hloc;
    bindingTrailTop = btloc;
    otherTrailTop = otloc;
  }

  //
  // Restore the tops of the heap and the trails.
  //
  void restore(heapobject*& hloc, TrailLoc& btloc, TrailLoc& otloc) const
  {
    hloc = heapTop;
    btloc = bindingTrailTop;
    otloc = otherTrailTop;
  }

  heapobject* getSavedTop(void) { return(heapTop); }

  heapobject* getSavedTopAddr(void) 
    { return(reinterpret_cast<heapobject*>(&heapTop)); }

};

class	Choice
{
  
public:
  ThreadStatus	status;
  CodeLoc		nextClause;
  CodeLoc		continuationInstr;
  HeapAndTrailsChoice	heapAndTrailsState;
  EnvLoc		currentEnvironment;
  EnvLoc		envStackTop;
  ChoiceLoc	previousChoicePoint;
  ChoiceLoc	cutPoint;
  word32		metaCounter;
  word32		objectCounter;
  word32		NumArgs;
  int        timestamp;


#ifdef WIN32
  Object*               X[1];
#else
  Object*               X[1] __attribute__ ((aligned));
#endif
  
public:
  //
  // Copy the current state of the thread into a choice point.
  //
//    inline void assign(Thread& th,
//  		     const word32 NumXRegs, 
//  		     const EnvLoc TopEnv)
//    {
//      word32	i;
    
//      status = th.getStatus();
//      continuationInstr = th.ContinuationInstr();
//      th.saveHeapAndTrails(heapAndTrailsState);
//      envStackTop = TopEnv;
//      currentEnvironment = th.CurrentEnvironment();
//      previousChoicePoint = th.CurrentChoicePoint();
//      cutPoint = th.CutPoint();
    
//      metaCounter = th.MetaCounter();
//      objectCounter = th.ObjectCounter();
    
//      NumArgs = NumXRegs;
//      for (i = 0; i < NumArgs; i++)
//        {
//  	X[i] = th.XRegs()[i];
//        }
//    }
  
  //
  // Restore the heap and name table back to the previous state
  // recorded in a choice point.
  //
 void restoreHeapNameTable(Thread& th) const;
  
  //
  // Restore the thread back to the previous state recorded in a
  // choice point.
  //
  void restore(Thread& th) const;
  
  //
  // Get the location of the next clause.
  //
  CodeLoc& getNextClause(void) { return(nextClause); }
  
  CodeLoc inspectNextClause(void) const { return nextClause; }
  
  //
  // Retrieve the old heap state.
  //
  HeapAndTrailsChoice& getHeapAndTrailsState(void) 
  { return(heapAndTrailsState); }
  
  //
  // Check whether the specified environment is protected or
  // not.  That is, check whether a choice point is created after
  // the environment.  If it does, the environment is needed
  // after backtracking.
  //
  bool isEnvProtected(const EnvLoc env) const { return(env < envStackTop); }
  
  //
  // Fetch the current environment at the time when the choice
  // point was created.
  //
  EnvLoc currentEnv(void) const { return(currentEnvironment); }
  
  //
  // Get the location of previous choice point.
  //
  ChoiceLoc getPreviousChoice(void) const { return(previousChoicePoint); }
  
  //
  // Get the location of choice point where to cut back to.
  //
  ChoiceLoc getCutPoint(void) const { return(cutPoint); }
  
  //
  // Get the number of X registers being saved.
  //
  word32 getNumArgs(void) const { return(NumArgs); }
  
  // 
  // Get an X register
  //
  Object* getXreg(word32 i) const 
  {
    assert((i >= 0) && (i < NumArgs));
    return(X[i]); 
  }
  // 
  // Get the address of an X register
  //
  heapobject* getXregAddr(word32 i) 
  {
    assert((i >= 0) && (i < NumArgs));
    return(reinterpret_cast<heapobject*>(X) + i); 
  }
  
  //
  // Get the Top of the environment stack stored in the
  // choice point.
  //
  EnvLoc getEnvTop(void) const { return(envStackTop); }
  
  int getTimestamp() const { return timestamp; }

  void setTimestamp(int t) { timestamp = t; } 
  //
  // Compare two choice points for ``equality''. This
  // is rough and ready and quite possibly unreliable.
  //
  bool operator==(const Choice& c) const
  {
    return(nextClause == c.nextClause &&
	   currentEnvironment == c.currentEnvironment &&
	   previousChoicePoint == c.previousChoicePoint &&
	   cutPoint == c.cutPoint &&
	   NumArgs == c.NumArgs);
  }
  
  bool operator!=(const Choice& c) const
  {
    return ! (*this == c);
  }
};

class	ChoiceStack : public RecordStack
{
  friend  class	Trace;
  
private:
  const Choice *inspectChoice(const ChoiceLoc index) const
  { return (const Choice *)(inspectAddr(index)); }
  
  //
  // Return the name of the area.
  //
  virtual	const char	*getAreaName(void) const
  { return("choice point stack"); }
  
public:
  
  explicit ChoiceStack(word32 size) : RecordStack(size, size / 10) 
  { 
      fetchChoice(0)->envStackTop = 0;
  }
  
  //
  // Work out the size of a choice point.
  //
  word32 size(const word32 NumArgs) const 
  {
    return(sizeof(Choice) + (NumArgs - 1) * sizeof(Object*));
  }


  //
  // Fetch a choice point.
  //
  Choice *fetchChoice(const ChoiceLoc index)
  { return((Choice *)(fetchAddr(index))); }

  //
  // return the env stack top in the given choice point
  //
  EnvLoc getEnvTop(const ChoiceLoc loc) 
  { return(fetchChoice(loc)->getEnvTop()); }

  //
  // Return the location of the first choice point in the stack.
  //
  ChoiceLoc firstChoice(void) const { return(0); }

  ChoiceLoc pushCP(word32 size)
  {
    return pushRecord(size);
  }

  //
  // Push a new choice point onto the stack.  The current state of the
  // thread is saved in the choice point and the location of the
  // alternative is recorded.  The pointer to the newly created choice
  // point is then returned.
  // If ChoiceLoc or StackLoc changes representation, then a bug may
  // occur if this is not changed.
  //
  //  ChoiceLoc push(Thread& th,
  //		 const CodeLoc alternative,
  //		 const word32 NumXRegs);

  //
  // Pop the current choice point and return a pointer to previous
  // choice point.
  //
  ChoiceLoc	pop(const ChoiceLoc loc)
  {
    ChoiceLoc	previous;
    
    previous = fetchChoice(loc)->getPreviousChoice();
    popRecord();
    
    return(previous);
  }
  
  //
  // Upon failure, set the registers up for the execution of the next
  // alternative from a given choice point.
  //
  void getNextAlternative(Thread& th, const ChoiceLoc index);


  //
  // Backtrack to previous state specified by the choice point in 'loc'.
  // Restore the state to the CPU, reset all top of stack pointers, and
  // reclaim the space from the stacks.
  //
  void backtrackTo(Thread& th, const ChoiceLoc loc)
  { fetchChoice(loc)->restore(th); }

  //
  // Backtrack to the beginning of the choice stack.  Only unwind the
  // heap and the name table.
  //
  void	failToBeginning(Thread& th)
  { fetchChoice(firstChoice())->restoreHeapNameTable(th); }

  //
  // Bring the top of the stack down to the cut point.
  //
  void	cut(const ChoiceLoc loc)
  {
    resetTopOfStack(loc, size(fetchChoice(loc)->getNumArgs()));
  }

  //
  // Retreive the field nextClause from a choice point.
  //
  CodeLoc&	nextClause(const ChoiceLoc index)
  { return(fetchChoice(index)->getNextClause()); }

  //
  // Get the previous choice point up in the search path from a choice
  // point.
  //
  ChoiceLoc	previousChoicePoint(const ChoiceLoc index)
  { return(fetchChoice(index)->getPreviousChoice()); }

  //
  // Retrieve the old heap state.
  //
  HeapAndTrailsChoice&	getHeapAndTrailsState(const ChoiceLoc index)
  { return(fetchChoice(index)->getHeapAndTrailsState()); }

  //
  // Check the whether the specified environment is protected or not.
  // That is, check whether a choice point is created after the
  // environment.  If it does, the environment is needed after
  // backtracking.
  //
  bool	isEnvProtected(const ChoiceLoc index,
		       const EnvLoc env)
  { return(fetchChoice(index)->isEnvProtected(env)); }

  //
  // Fetch the current environment at the time when the choice point was
  // created.
  //
  EnvLoc currentEnv(const ChoiceLoc index)
  { return(fetchChoice(index)->currentEnv()); }

  //
  // Save the area.
  //
  void save(ostream& strm) const { saveStack(strm, CHOICE_MAGIC_NUMBER); }

  //
  // Gets the cut point from the specified frame.
  //
  ChoiceLoc cutPoint(const ChoiceLoc index)
  { return(fetchChoice(index)->getCutPoint()); }

  //
  // Get the number of args
  //
  word32 getNumArgs(const ChoiceLoc index)
    { return(fetchChoice(index)->getNumArgs()); }
  
  //
  // Get an x register
  //
  Object*  getXreg(const ChoiceLoc index, word32 i)
    { return(fetchChoice(index)->getXreg(i)); }
  //
  // Get an x register address
  //
  heapobject*  getXregAddr(const ChoiceLoc index, word32 i)
    { return(fetchChoice(index)->getXregAddr(i)); }
  
  
  
  //
  // Restore the area.
  //
  void load(istream& strm) { loadStack(strm); }

  //
  // Debugging display
  //
  ostream& Display(ostream& strm, ChoiceLoc index, const size_t = 0) const;
};

#endif	// CHOICE_H




