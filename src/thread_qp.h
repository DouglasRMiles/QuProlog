// thread_qp.h - Define the components of a thread.
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
// $Id: thread_qp.h,v 1.14 2006/04/04 02:33:20 qp Exp $

#ifndef	THREAD_QP_H
#define	THREAD_QP_H

//#include <iostream>
#include <list>
#include <stdarg.h>

#include "area_offsets.h"
#include "block.h"
#include "objects.h"
#include "choice.h"
#include "compiler_support.h"
//#include "decompile.h"
#include "defs.h"
#include "encode.h"
#include "environment.h"
#include "error_value.h"
#include "foreign_handle.h"
#include "heap_qp.h"
#include "heap_buffer.h"
#include "messages.h"
#include "indexing.h"
#include "name_table.h"
#include "obj_index.h"
#include "pile.h"
//#include "pred_table.h"
#include "prolog_value.h"
#include "thread_condition.h"
#include "thread_info.h"
#include "thread_options.h"
#include "trace_qp.h"
#include "trail.h"
#include "foreign_interface.h"

//
// Was the thread interrupted? If so, what sort of interruption was
// it?
//
class RestartStatus: public Status <word8>
{
private:
  static const word8 RESTART_BLOCK	= 0x01;
  static const word8 RESTART_SIGNAL	= 0x02;
  static const word8 RESTART_TIMESLICE	= 0x04;
public:
  bool testRestartBlock(void) const { return test(RESTART_BLOCK); }
  bool testRestartSignal(void) const { return test(RESTART_SIGNAL); }
  bool testRestartTimeslice(void) const { return test(RESTART_TIMESLICE); }
  
  bool IsRestart(void) const
  {
    return (testRestartBlock() ||
	    testRestartSignal() ||
	    testRestartTimeslice());
  }
  
  void setRestartBlock(void) { set(RESTART_BLOCK); }
  void setRestartSignal(void) { set(RESTART_SIGNAL); }
  void setRestartTimeslice(void) { set(RESTART_TIMESLICE); }
  
  void resetRestartBlock(void) { reset(RESTART_BLOCK); }
  void resetRestartSignal(void) { reset(RESTART_SIGNAL); }
  void resetRestartTimeslice(void) { reset(RESTART_TIMESLICE); }
  
  void Clear(void) { clear(); }
};



//
// Qu-Prolog thread
//
class Thread
{
#ifdef QP_DEBUG
  // The Trace class may gaze into a Thread's soul.
  friend class Trace;
#endif // QP_DEBUG
  friend class Scheduler;

private:
  ThreadCondition thread_condition;
  CodeLoc programCounter;		// PC
  BlockStatus block_status;
  RestartStatus restart_status;
  word32 minCleanupCP;
  bool suspend_gc;

  void InitThread(void);

  // Execution environment information.
  ThreadInfo thread_info;

  static const word32 maxXRegs = NUMBER_X_REGISTERS;
  
  Object* X[NUMBER_X_REGISTERS];		// X registers
  Object* SavedX[NUMBER_X_REGISTERS];	// Saved value of X registers
  
  PushDownStack	pushDownStack;
  
  bool localAreas;
  bool quick_tidy_check;
  NameTable& names;
  IPTable& ipTable;

  HeapBufferManager& buffers;
  Heap& heap;
  Heap& scratchpad;
  ObjectsStack& gcstack;
  GCBits& gcbits;

  BindingTrail& bindingTrail;
  OtherTrail& otherTrail;
  
  CodeLoc continuationInstr;	// CP
  EnvLoc currentEnvironment;	// CE
  
  EnvironmentStack envStack;

  ChoiceLoc currentChoicePoint;		// B
  ChoiceLoc cutPoint;			// B0
  ChoiceLoc catchPoint;			// exception

  ChoiceStack choiceStack;

  // Messages that are pending.
  list<Message *> message_queue;

  // Number of active message queue scans in progress. 
  size_t queue_level;

  CodeLoc savedPC;

  // Counts of numbers of sorts of variables created.
  word32	metaCounter;
  word32	objectCounter;

  //
  // For manipulating strings on the fly.
  //
  // XXX It's definitely possible to use the same buffer for 
  // XXX strings, io and encoding BUT each of these sets of operations
  // XXX operate under different constraints e.g. maximum length of
  // XXX strings. It probably isn't a good idea to merge their uses.
  //
  char atom_buf1[ATOM_LENGTH];
  char atom_buf2[ATOM_LENGTH];

  //
  // I/O (including TCP).
  //
  // XXX It's definitely possible to use the same buffer for 
  // XXX strings, io and encoding BUT each of these sets of operations
  // XXX operate under different constraints e.g. maximum length of
  // XXX strings. It probably isn't a good idea to merge their uses.
  //
  char io_buf[IO_BUF_LENGTH];

  // Foreign function interface file.
  Handle *ForeignFile;
  ForeignInterface *finter;

  // Used for passing back information about failed pseudo-instructions.
  ErrorValue error_value;
  word32 error_arg;

  ThreadStatus status;
#ifdef QP_DEBUG
  // Trace class used for following the actions of the WAM.
  Trace trace;
#endif // QP_DEBUG

  // Save the X registers in SavedX
  void SaveXRegisters(void);

  // Restore the X registers in SavedX
  void RestoreXRegisters(void);

public:
  
  word32 getCleanupMinCP() const { return minCleanupCP; }

  void resetCleanupMinCP() { minCleanupCP = 0xFFFF; }

  word32*  getCleanupMinCPAddr() { return &minCleanupCP; }

  void setSuspendGC(bool v) { suspend_gc = v; }

  bool isSuspendedGC(void) { return suspend_gc; }

  ThreadCondition::ThreadConditionValue Condition() const 
  { return thread_condition.Condition(); }

 void Condition(const ThreadCondition::ThreadConditionValue tcv) 
 { thread_condition.Condition(tcv); }

 ThreadCondition& getThreadCondition() { return thread_condition; }

  // Pending IPC messages.
  list<Message *>& MessageQueue(void) { return message_queue; }

  // Get the IP table
  IPTable& getIPTable(void) { return ipTable; }
  
  // Status of this thread.
  ThreadStatus& getStatus(void) { return status; }

  char* getAtomBuf1(void) { return atom_buf1; }

  // Thread identification, etc.
  ThreadInfo& TInfo(void) { return thread_info; }
  const ThreadInfo& InspectTInfo(void) const { return thread_info; }
#ifdef QP_DEBUG
  // Trace information.
  Trace& GetTrace(void) { return trace; }
#endif // QP_DEBUG
  // Save the state of the heap and trails for choice pointes.
  void saveHeapAndTrails(HeapAndTrailsChoice& state)
    {
      state.save(heap.getTop(), bindingTrail.getTop(), otherTrail.getTop());
      heap.setSavedTop(heap.getTop());
    }


  bool is_quick_tidy_check() { return quick_tidy_check; }

  void set_quick_tidy_check(bool f) { quick_tidy_check = f; }

  // Backtrack - reset tops of heap and trails and backtrack trails.
  void backtrackTo(const HeapAndTrailsChoice& state)
    {
      heapobject* savedHT;
      TrailLoc savedBindingTrailTop;
      TrailLoc savedOtherTrailTop;
      state.restore(savedHT, savedBindingTrailTop, savedOtherTrailTop); 
      heap.setSavedTop(savedHT);
      heap.setTop(savedHT);
      bindingTrail.backtrackTo(savedBindingTrailTop);
      otherTrail.backtrackTo(savedOtherTrailTop);
    }

  void changeTimeslice(bool makeSet);

  void backtrackTo(Choice* cp)
  {
    word32 i;
    
    ThreadStatus& curr_status = getStatus();
    if (cp->status.testTimeslicing() != curr_status.testTimeslicing())
      {
	changeTimeslice(cp->status.testTimeslicing());
      }
    curr_status = cp->status;
    continuationInstr = cp->continuationInstr;
    backtrackTo(cp->heapAndTrailsState);
    currentEnvironment = cp->currentEnvironment;
    
    envStack.setTop(cp->envStackTop);
    
    metaCounter = cp->metaCounter;
    objectCounter = cp->objectCounter;
    
    word32 nargs = cp->NumArgs;
    for (i = 0; i < nargs; i++)
      {
	X[i] = cp->X[i];
      }
  }

  // Tidy up the trails.
  void tidyTrails(const HeapAndTrailsChoice& state)
    {
      heapobject* savedHT;
      TrailLoc savedBindingTrailTop;
      TrailLoc savedOtherTrailTop;

      state.restore(savedHT, savedBindingTrailTop, savedOtherTrailTop); 
      bindingTrail.tidyUpTrail(savedBindingTrailTop, savedHT);
      otherTrail.tidyUpTrail(savedOtherTrailTop, savedHT, heap);
      heap.setSavedTop(savedHT);
    }

  //
  // Copy the current state of the thread into a choice point.
  //
  inline void assignChoicePoint(Choice* choice,
		     const word32 NumXRegs, 
		     const EnvLoc TopEnv)
  {
    word32	i;
    
    choice->status = getStatus();
    choice->continuationInstr = continuationInstr;
    saveHeapAndTrails(choice->heapAndTrailsState);
    choice->envStackTop = TopEnv;
    choice->currentEnvironment = currentEnvironment;
    choice->previousChoicePoint = currentChoicePoint;
    choice->cutPoint = cutPoint;
    
    choice->metaCounter = metaCounter;
    choice->objectCounter = objectCounter;
    
    choice->NumArgs = NumXRegs;
    for (i = 0; i < NumXRegs; i++)
      {
	choice->X[i] = X[i];
      }
    choice->setTimestamp(0);
  }

  //
  // Push a new choice point onto the choice point stack.  
  // The current state of the
  // thread is saved in the choice point and the location of the
  // alternative is recorded.  The pointer to the newly created choice
  // point is then returned.
  // If ChoiceLoc or StackLoc changes representation, then a bug may
  // occur if this is not changed.
  //
  ChoiceLoc pushChoicePoint(const CodeLoc alternative, const word32 NumXRegs)
  {
    ChoiceLoc	index;
    EnvLoc	TopEnv;
    
    index = choiceStack.pushCP(choiceStack.size(NumXRegs));
    
    if (choiceStack.isEnvProtected(currentChoicePoint, currentEnvironment))
      {
	TopEnv = choiceStack.getEnvTop(currentChoicePoint);
      }
    else
      {
	TopEnv = currentEnvironment +
	  envStack.envSize(currentEnvironment);
      }
    assignChoicePoint(choiceStack.fetchChoice(index), NumXRegs, TopEnv);
    choiceStack.nextClause(index) = alternative;
    
    return(index);
  }

  ForeignInterface* getFInter()
    {
      if (finter == NULL)
	finter = new ForeignInterface(this);
      return finter;
    }

  // Declarations for many of the thread methods, most notably, the
  // pseudo-instructions.

#include "return.h"

#include "arithmetic.h"
#include "atoms.h"
#include "bind.h"
#include "bios.h"
#include "buffers.h"
#include "c_to_prolog.h"
#include "compare.h"
#include "compile_qp.h"
#include "cut.h"
#include "decompile.h"
#include "delay_qp.h"
#include "delay_escape.h"
#include "distinction.h"
#include "dyn_code.h"
#include "encode_stream.h"
#include "env.h"
#include "env_var.h"
#include "equal.h"
#include "equal_escape.h"
#include "esc_init.h"
#include "examine_term.h"
#include "exception.h"
#include "execute.h"
#include "foreign.h"
#include "free_in.h"
#include "freeness.h"
#include "gc_escapes.h"
#include "generate_var_names.h"
#include "get_args.h"
#include "interrupt_qp.h"
#include "ip_qp.h"
#include "pedro_escapes.h"
#include "ipc_escapes.h"
#include "load.h"
#include "name.h"
#include "object_variable.h"
#include "occurs_check.h"
#include "pipe.h"
#include "process.h"
#include "pseudo_instr.h"
#include "quantifier.h"
#include "random.h"
#include "read_qp.h"
#include "signal_escapes.h"
#include "state.h"
#include "statistics.h"
#include "stream_escapes.h"
#include "string_escapes.h"
#include "structure.h"
#include "sub_escape.h"
#include "symbols.h"
#include "system_qp.h"
#include "tcp_escapes.h"
#include "temperature.h"
#include "thread_escapes.h"
#include "timer_escapes.h"
#include "token.h"
#include "trace_escapes.h"
#include "trail.h"
#include "unify.h"
#include "user_hash_table_escapes.h"
#include "varname.h"
#include "write.h"

  //
  // Set the cpu up for the execution of the next alternative from the current 
  // choice point. If there is no choice point an appropriate fatal error message 
  // is given.
  // NOTE: The state is not reset.
  //
  void Backtrack(CodeLoc& PC)
  {
    Choice* currChoice = choiceStack.fetchChoice(currentChoicePoint);
    int time = currChoice->getTimestamp();
    if (time <= 0)
    {
       PC = choiceStack.nextClause(currentChoicePoint);
       cutPoint = currChoice->getCutPoint();
    }
    else
    {
      DBBacktrack(PC, currChoice, time);
    }
  }

  void DBBacktrack(CodeLoc& PC, Choice* currChoice, int time)
  {
    LinkedClause* nextClause = (LinkedClause*)(currChoice->getNextClause());
    LinkedClause* nextNextClause = nextClause->nextNextAlive(time);
    assert(nextClause != NULL);
    if (nextNextClause == NULL)
      { 
	PC = nextClause->getCodeBlock()->getCode();
	backtrackTo(choiceStack.fetchChoice(currentChoicePoint)); 
	currentChoicePoint = choiceStack.pop(currentChoicePoint); 
	//tidyTrails(choiceStack.getHeapAndTrailsState(currentChoicePoint));
	cutPoint = choiceStack.fetchChoice(currentChoicePoint)->getCutPoint();
      }
    else
      {
	currChoice->getNextClause() = (CodeLoc)nextNextClause;
	PC = nextClause->getCodeBlock()->getCode();
	backtrackTo(choiceStack.fetchChoice(currentChoicePoint));
	cutPoint = choiceStack.fetchChoice(currentChoicePoint)->getCutPoint();
      } 
  }               

  Thread(Thread *parent,
	 const word32 ScratchpadSize,
	 const word32 HeapSize,
	 const word32 BindingTrailSize,
	 const word32 OtherTrailSize,
	 const word32 EnvSize,
	 const word32 ChoiceSize,
	 const word32 NameSize,
	 const word32 IPSize);

  Thread(Thread *parent,
	 ThreadOptions& thread_options);
  
  Thread(Thread *parent,
	 HeapBufferManager& SharedBuffers,
	 Heap& SharedScratchpad,
	 Heap& SharedHeap,
         ObjectsStack& SharedGCstack,
         GCBits& SharedGCBits,
	 NameTable& SharedNames,
	 IPTable& SharedIPTable,
	 BindingTrail& SharedBindingTrail,
	 OtherTrail& SharedOtherTrail,
	 const word32 EnvSize,
	 const word32 ChoiceSize);
 
  ~Thread(void);

  bool operator==(const Thread& th) const
  {
    return this == &th;
  }

  //
  //
  // Save the data area and registers.
  //
  void save(ostream&);

  //
  // Load the data area and registers.
  //
  word32 load(istream& strm, word32 magic);

  CodeLoc& ProgramCounter(void) { return programCounter; }
  Heap& TheHeap(void) { return heap; }
  Heap& TheScratchpad(void) { return scratchpad; }
  BindingTrail& TheBindingTrail(void) { return bindingTrail; }
  OtherTrail& TheOtherTrail(void) { return otherTrail; }
  ChoiceStack& TheChoiceStack(void) { return choiceStack; }


  const Heap& InspectHeap(void) const { return heap; }
  CodeLoc& ContinuationInstr(void) { return continuationInstr; }
  EnvLoc& CurrentEnvironment(void) { return currentEnvironment; }
  EnvironmentStack& EnvStack(void) { return envStack; }
  word32& MetaCounter(void) { return metaCounter; }
  word32& ObjectCounter(void) { return objectCounter; }
  Object **XRegs(void) { return X; }
  ChoiceLoc& CurrentChoicePoint(void) { return currentChoicePoint; }
  ChoiceLoc& CutPoint(void) { return cutPoint; }

  NameTable& getNames(void) { return names; }

  BlockStatus& getBlockStatus(void) { return block_status; }
  RestartStatus& getRestartStatus(void) { return restart_status; }
};

// Print out some information about the thread in a human readable form.
extern ostream& operator<<(ostream&, Thread&);

#endif	// THREAD_QP_H
