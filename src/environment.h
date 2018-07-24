// environment.h - Each environment records the state of computation within a
//		   clause.  It enables the computation to continue after the
//		   current subgoal has been solved.
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
// $Id: environment.h,v 1.6 2006/01/31 23:17:50 qp Exp $

#ifndef	ENVIRONMENT_H
#define	ENVIRONMENT_H

#include <iostream>

#include "area_offsets.h"
#include "code.h"
#include "objects.h"
#include "defs.h"
#include "magic.h"
#include "qem_options.h"
#include "record_stack.h"

class Thread;

class 	EnvironmentStack : public RecordStack
{
friend	class	Trace;

private:
  class	Environment
  {
  private:
    static const word32 GC_Mark =    0x80000000UL;
  public:
    EnvLoc	previousEnvironment;
    CodeLoc	continuationInstruction;
    word32  NumYRegs;
#ifdef WIN32
    Object*     y[1];
#else
        Object* y[1] __attribute__ ((aligned));
#endif
    
    Environment(void) : NumYRegs(0) { }

    //
    // Set all the Yregs to NULL
    //
    inline void zeroYRegs(void)
      {
	for (u_int i = 0; i < NumYRegs; i++)
	  {
	    y[i] = NULL;
	  }
      }

    // 
    // Compare two environments for ``equality''. This
    // is rough and ready and quite probably unreliable.
    //
    bool operator==(const Environment& e) const
    {
      return (previousEnvironment == e.previousEnvironment &&
	      continuationInstruction == e.continuationInstruction);
    }

    bool operator!=(const Environment& e) const
    {
      return ! (*this == e);
    }

    //
    // Work out the size of the environment.
    //
    word32 size(void) const
    { return(sizeof(Environment) + (NumYRegs - 1) * sizeof(Object*)); }

    //
    // Set the Mark bit for garbage collection
    //
    void gc_markEnv(void)
    { NumYRegs |= GC_Mark; }

    //
    // Unset the Mark bit.
    //
    void gc_unmarkEnv(void)
    { NumYRegs &= ~GC_Mark; }

    //
    // Test the mark bit.
    //
    bool gc_isMarkedEnv(void)
    { return ((NumYRegs & GC_Mark) == GC_Mark); }
  };
  
  //
  // Fetch the address of an environment.
  // If EnvLoc or StackLoc changes representation, then a bug may
  // occur if this is not changed.
  //
  Environment *fetchEnv(const EnvLoc env)
  { assert(fetchAddr(env) != NULL); return((Environment *)(fetchAddr(env))); }
  
  //
  // Return the name of the area.
  //
  virtual const char *getAreaName(void) const { return("environment stack"); }

public:

  explicit EnvironmentStack(word32 size)
    : RecordStack(size, size / 10) { }

  EnvLoc firstEnv(void)	const { return(0); }

  //
  // Get the top of the environment.
  // If EnvLoc or StackLoc changes representation, then a bug may
  // occur if this is not changed.
  //
  EnvLoc getTop(void) const { return(getTopOfStack()); }

  //
  // Set the top of the environment.
  // If EnvLoc or StackLoc changes representation, then a bug may
  // occur if this is not changed.
  //
  void setTop(const EnvLoc top) { setTopOfStack(top); }
  
  //
  // Push a new environment onto the stack.
  // If EnvLoc or StackLoc changes representation, then a bug may
  // occur if this is not changed.
  //
  EnvLoc push(const EnvLoc PrevEnv, const CodeLoc ContInst,
	      const word32 NumYs)
{
	EnvLoc	env;

	//
	// Allocate environment.
	//
	env = pushRecord(sizeof(Environment) + (NumYs - 1) * sizeof(Object*));
	//
	// Initialise fixed fields.
	//
	fetchEnv(env)->previousEnvironment = PrevEnv;
	fetchEnv(env)->continuationInstruction = ContInst;
	fetchEnv(env)->NumYRegs = NumYs;
	fetchEnv(env)->zeroYRegs();

	return(env);
}
  
  // Test if environment is top environment
  //
  bool		isTopEnv(const EnvLoc env) const
  {
    return(previousTop(getTop()) == env);
  }
  
  //
  // Work out the size of the given environment in StackWords.
  //
  word32 envSize(const EnvLoc env)
  {
    return(numberOfStackWords(fetchEnv(env)->size()));
  }

  //
  // Work out the size of the environment given the number of Yregs.
  //
  word32 size(const word32 NumYs) const
  {
    return(sizeof(Environment) + NumYs * sizeof(Object*));
  }
  
  // Bring the top of stack down.  Thus, reclaim all the space between
  // the current top and the new top.  This is used for environment
  // trimming.
  //
  void trim(const EnvLoc env, const word32 NumYs)
  {
    assert(previousTop(getTop()) == env);

    if(fetchEnv(env)->NumYRegs != NumYs)
      {
	trimRecord(env, size(NumYs));
	fetchEnv(env)->NumYRegs = NumYs;
      }
  }
  
  //
  // Fetch the previousEnvironment and continuationInstruction fields
  // from an environment.
  //
  void retrieve(const EnvLoc prev, EnvLoc& env, CodeLoc& code)
  {
    code = fetchEnv(prev)->continuationInstruction;
    env = fetchEnv(prev)->previousEnvironment;
  }
  
  //
  // Get the previous env
  //
  EnvLoc getPreviousEnv(const EnvLoc env)
    {  return(fetchEnv(env)->previousEnvironment); }

  //
  // Get a Y register.
  //
  Object*&		yReg(const EnvLoc env, const word32 RegNum)
    { return(fetchEnv(env)->y[RegNum]); }

  //
  // Get a y reg address
  //
  heapobject*           yRegAddr(const EnvLoc env, const word32 RegNum)
    { return (reinterpret_cast<heapobject*>(fetchEnv(env)->y + RegNum)); }

  //
  // Check if given Env is GC marked
  //
  bool gc_isMarkedEnv(const EnvLoc env)
    { return(fetchEnv(env)->gc_isMarkedEnv()); }

  //
  // GC mark given env
  //
  void gc_markEnv(const EnvLoc env)
    { fetchEnv(env)->gc_markEnv(); }

  //
  // GC unmark given env
  //
  void gc_unmarkEnv(const EnvLoc env)
    { fetchEnv(env)->gc_unmarkEnv(); }
  
  //
  // Get the number of Y regs for a given env
  //
  word32 getNumYRegs(const EnvLoc env)
    { return(fetchEnv(env)->NumYRegs); }

  //
  // Save the area.
  //
  void save(ostream& strm) const { saveStack(strm, ENVIRONMENT_MAGIC_NUMBER); }
  
  //
  // Restore the area.
  //
  void		load(istream& strm)
  { loadStack(strm); }
  
  //
  // Debugging display
  //
  ostream& Display(ostream& strm, EnvLoc index, const size_t = 0);

#ifdef QP_DEBUG
void printMe(AtomTable&, EnvLoc);
#endif //QP_DEBUG

};

#endif	// ENVIRONMENT_H
