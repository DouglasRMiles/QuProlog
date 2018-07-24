// execute.cc - The Qu-Prolog  Abstract Machine emulator 
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
// $Id: execute.cc,v 1.22 2006/03/30 22:50:30 qp Exp $

#include "debug.h"

#include <sys/types.h>
#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include <signal.h>

#include "config.h"

#ifndef WIN32
extern "C" int kill(pid_t, int);
#endif

#include "atom_table.h"
#include "code.h"
#include "dynamic_code.h"
#include "pred_table.h"
#include "qem_options.h"
#include "scheduler.h"
#include "signals.h"
#include "thread_qp.h"

#include "pseudo_instr_arrays.h"

extern AtomTable *atoms;
extern Code *code;
extern PredTab *predicates;
extern QemOptions *qem_options;
extern Scheduler *scheduler;
extern Signals *signals;
extern int errorno;

bool in_sigint = false;

// Helps to label the opcodes for proceesing via MkOpcodes

#define	OPCODE(x, y)		x

#define UT(x) (((x) & Object::UnifyMask) >> 1)

#define BACKTRACK				\
  do {						\
    Backtrack(PC);				\
  } while (0)

#define HANDLE_ESCAPE(fn)			\
  do {						\
    const bool result = (fn);			\
    if (!result)				\
      {						\
	BACKTRACK;				\
      }						\
  } while (0)

#define HANDLE_PSI(rv, pc_off)						\
  do {									\
    switch (rv)								\
      {									\
      case RV_FAIL:							\
	block_status.setRunnable();					\
	restart_status.Clear();						\
	BACKTRACK;							\
	break;								\
      case RV_SUCCESS:							\
	block_status.setRunnable();					\
	restart_status.Clear(); 					\
	break;								\
      case RV_YIELD:							\
	block_status.setRunnable();     				\
	restart_status.Clear();						\
	return RV_YIELD;						\
	break;								\
      case RV_BLOCK:							\
	restart_status.setRestartBlock();				\
	programCounter -= pc_off;					\
	return RV_BLOCK;						\
	break;								\
      case RV_SIGNAL:							\
        if (in_sigint){                                                 \
            block_status.setRunnable();					\
	    restart_status.Clear(); 					\
        } else {                                                        \
	    restart_status.setRestartSignal();				\
	    programCounter -= pc_off;					\
	    return RV_SIGNAL;						\
        }                                                               \
	break;								\
      case RV_TIMESLICE:						\
	restart_status.setRestartTimeslice();				\
	programCounter -= pc_off;					\
	return RV_TIMESLICE;						\
	break;								\
      case RV_ERROR:							\
	Fatal(__FUNCTION__, "RV_ERROR should be handled separately!");	\
	break;								\
      case RV_EXIT:							\
	return RV_EXIT;							\
	break;								\
      case RV_HALT:							\
	return RV_HALT;							\
	break;								\
      }									\
  } while (0)

//
// This macro is essential when we don't have POSIX threads.
//
// It is possible for an instruction to be interrupted. Normally,
// this only happens to instructions involving escapes (C++ code).
// The sorts of interruption are: a signal was received; a timeslice
// ended or a library operation (would have) blocked.
//
// When the instruction is restarted,
// we don't want to redo the operations that were done the first time
// the instruction was tried, so we leave information about the 
// restart in the thread. When the instruction is being executed
// we check whether or not the instruction is being restarted and
// act accordingly.
//
// Macro: ONCE_ONLY(actions)
//
// Ensure that the actions specified are only performed the first
// time an instruction is tried. The actions take the form of a bracketed
// block of C++ code.
//
#define ONCE_ONLY(actions)				\
  do {							\
    if (restart_status.IsRestart())			\
      {							\
	if (restart_status.testRestartSignal())		\
	  {						\
	    restart_status.resetRestartSignal();	\
	  }						\
	else if (restart_status.testRestartTimeslice())	\
	  {						\
	    restart_status.resetRestartTimeslice();	\
	  }						\
      }							\
    else						\
      {							\
	actions						\
	  }						\
  } while (0)

#define HANDLE_SIGNAL(pc_off)			\
  do {						\
    restart_status.setRestartSignal();		\
    programCounter = PC - pc_off;		\
    return RV_SIGNAL;				\
  } while (0)

#define HANDLE_TIMESLICE(pc_off)		\
  do {						\
    restart_status.setRestartTimeslice();	\
    programCounter = PC - pc_off;		\
    return RV_TIMESLICE;			\
  } while (0)

#if defined(__GNUC__)
#define VMBREAK	__asm__("");break
#else
#define VMBREAK break
#endif

extern CodeLoc failblock;


bool Thread::initializeDPcall(DynamicPredicate* dp, int arity, CodeLoc& PC)
{
  ChainEnds* chain;
  assert(dp != NULL);
  const word8 arg = dp->getIndexedArg();
  if (arg == (word8)(-1)) { // -1 as word8 - no indexing - treat as variable
    chain = dp->lookUpClauseChain(*this, NULL);
  } else {
    assert(X[arg] != NULL);
    chain = dp->lookUpClauseChain(*this, X[arg]);
  }
  assert(chain != NULL);
  LinkedClause* block = chain->first();
  if (block == NULL)
    {
      return false;
    }
  else
    {
      word32 time = dp->GetStamp();
      block = block->nextAlive(time);
      if (block == NULL)
	{
	  return false;
	}
      currentChoicePoint = pushChoicePoint(failblock, arity);
      choiceStack.fetchChoice(currentChoicePoint)->setTimestamp(-1);
      dp->aquire();
      otherTrail.push(dp);
      LinkedClause* nextClause = block->nextNextAlive(time);
      if( nextClause != NULL)
	{
	  currentChoicePoint = 
	    pushChoicePoint((CodeLoc)nextClause, arity);
	  choiceStack.fetchChoice(currentChoicePoint)->setTimestamp(time);
	}
      PC = block->getCodeBlock()->getCode();     
      return true;
    }
}
 
//
// Fetch-execute cycle for the Qu-Prolog Abstract Machine.
//
Thread::ReturnValue
Thread::Execute(void)
{
  if (Condition() == ThreadCondition::EXITED)
    {
      return RV_EXIT;
    }
  //
  // Used to carry information across instructions.
  //
  heapobject*	StructurePointer = NULL;
  bool		ReadMode = true;
  Object*	saveTerm;

#ifndef NDEBUG
  if (qem_options->Debugging())
    {
      cerr << "Turning on QuAM debugging" << endl;
      trace.TraceLevel() = Trace::TRACE_ALL;
    }
#endif

#if 0
  // TO DO: Complete the jump table implementation.
  const void *jumptable[] =
    { &&err, 
      &&put_x_variable, &&put_y_variable,
      &&put_x_value, &&put_y_value,
      &&put_constant, &&put_list, &&put_structure, 
      &&put_x_object_variable, &&put_y_object_variable,
      &&put_x_object_value, &&put_y_object_value,
      &&put_apply_structure, &&put_quantifier,
      &&check_binder,
      &&put_substitution,
      &&put_x_term_substitution, &&put_y_term_substitution,
      &&put_initial_empty_substitution, &&put_empty_substitution,
      &&put_substitution_operator, 
      &&get_x_variable, &&get_y_variable,
      &&get_x_value, &&get_y_value,
      &&get_constant, &&get_list, &&get_structure, &&get_structure_frame,
      &&get_x_object_variable, &&get_y_object_variable,
      &&get_x_object_value, &&get_y_object_value,
      &&get_apply_structure, 
      &&unify_x_variable, &&unify_y_variable,
      &&unify_x_value, &&unify_y_value, &&unify_void,
      &&set_x_variable, &&set_y_variable,
      &&set_x_value, &&set_y_value,
      &&set_x_object_variable, &&set_y_object_variable,
      &&set_x_object_value, &&set_y_object_value,
      &&set_constant, &&set_void, &&set_object_void, 
      &&allocate, &&deallocate,
      &&call_predicate, &&call_address, &&call_escape,
      &&execute_predicate, &&execute_address, &&execute_escape,
      &&noop, &&jump, &&proceed, &&fail, &&halt, &&exit,
      &&try_me_else, &&retry_me_else, &&trust_me_else_fail,
      &&try, &&retry, &&trust,
      &&neck_cut, &&get_x_level, &&get_y_level, &&cut,
      &&switch_on_term, &&switch_on_constant, &&switch_on_structure,
      &&switch_on_quantifier,
      &&pseudo_instr0, &&pseudo_instr1, &&pseudo_instr2, &&pseuod_instr3,
      &&pseudo_instr5,
      &&unify_constant
    };
#endif

  CodeLoc PC = programCounter;
  while (true)
    {
#ifndef NDEBUG
      CodeLoc trace_pc = PC;
      trace.TraceStart(*this);
#endif
      assert(!quick_tidy_check);
      switch(getInstruction(PC))
	{
	  //
	  // The purpose of the "put" instructions is to create
	  // the data object specified by the instruction.
	  // They are mainly used in setting up the arguments
	  // for the goals in a clause.
	  //
	case OPCODE(PUT_X_VARIABLE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(PC);
	    const word32 j = getRegister(PC);
	    //
	    // Create an unbound variable on the heap and
	    // place a REFERENCE cell pointing to it into
	    // registers Xi and Xj.
	    //
	    X[i] = heap.newVariable();
	    X[j]= X[i];
	  }
	  VMBREAK;

	case OPCODE(PUT_Y_VARIABLE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(PC);
	    const word32 j = getRegister(PC);
	    //
	    // Create an unbound variable on the heap and
	    // place a  REFERENCE cell pointing to it into
	    // Yi and register Xj.
	    //
	    X[j] = heap.newVariable();
	    envStack.yReg(currentEnvironment, i) = X[j];
	  }
	  VMBREAK;

	case OPCODE(PUT_X_VALUE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(PC);
	    const word32 j = getRegister(PC);
	    //
	    // The value in Xi is transferred to Xj.
	    //
	    X[j]= X[i];
	  }
	  VMBREAK;

	case OPCODE(PUT_Y_VALUE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(PC);
	    const word32 j = getRegister(PC);
	    //
	    // The value in Yi is transferred to Xj.
	    //
	    X[j]= envStack.yReg(currentEnvironment, i);
	  }
	  VMBREAK;

	case OPCODE(PUT_CONSTANT, ARGS(constant, register)):
	  {
	    Object* c = getConstant(PC);
	    const word32 i = getRegister(PC);
	    //
	    // Place an atom cell with constant c into
	    // register Xi.
	    //
	    X[i]= c;
	  }
	  VMBREAK;

	case OPCODE(PUT_INTEGER, ARGS(integer, register)):
	  {
	    Object* c = heap.newInteger(getInteger(PC));
	    const word32 i = getRegister(PC);
	    //
	    // Place a number cell c into
	    // register Xi.
	    //
	    X[i]= c;
	  }
	  VMBREAK;


	case OPCODE(PUT_LIST, ARGS(register)):
	  {
	    const word32 i = getRegister(PC);
	    //
	    // Push a cons object onto the heap 
	    //
	    X[i] = heap.newCons();
	    StructurePointer = X[i]->storage();
	  }
	  VMBREAK;

	case OPCODE(PUT_STRUCTURE, ARGS(number, register)):
	  {
	    const word32 n = getNumber(PC);
	    const word32 i = getRegister(PC);
	    //
	    // Push a struct object of arity n onto the heap
	    //
	    assert(n <= MaxArity);
	    X[i] = heap.newStructure(n);
	    StructurePointer = X[i]->storage();
	  }
	  VMBREAK;

	case OPCODE(PUT_X_OBJECT_VARIABLE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(PC);
	    const word32 j = getRegister(PC);
	    //
	    // Create an object variable on the heap and
	    // place an OB_REFERENCE cell pointing to it into
	    // register Xi.
	    //
	    X[i] = heap.newObjectVariable();
	    X[j]= X[i];
	  }
	  VMBREAK;

	case OPCODE(PUT_Y_OBJECT_VARIABLE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(PC);
	    const word32 j = getRegister(PC);
	    //
	    // Create an object variable on the heap and
	    // place an OB_REFERENCE cell pointing to it into
	    // Yi.
	    //
	    X[j] = heap.newObjectVariable();
	    envStack.yReg(currentEnvironment, i) = X[j];
	  }
	  VMBREAK;

	case OPCODE(PUT_X_OBJECT_VALUE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(PC);
	    const word32 j = getRegister(PC);
	    //
	    // The value in Xi which contains an object
	    // variable is transferred to Xj.
	    //
	    X[j] = X[i];
	  }
	  VMBREAK;

	case OPCODE(PUT_Y_OBJECT_VALUE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(PC);
	    const word32 j = getRegister(PC);
	    //
	    // The value in Yi which has an object variable
	    // is transferred to Xj.
	    //
	    X[j] = envStack.yReg(currentEnvironment, i);
	  }
	  VMBREAK;

	case OPCODE(PUT_QUANTIFIER, ARGS(register)):
	  {
	    const word32 i = getRegister(PC);
	    //
	    // Push a quant object onto the heap
	    //
	    X[i] = heap.newQuantifiedTerm();
	    StructurePointer = X[i]->storage();
	  }
	  VMBREAK;
	  
	case OPCODE(CHECK_BINDER, ARGS(register)):
	  {
	    const word32 i = getRegister(PC);
	    //
	    // Check the bound variables list in Xi are distinct
	    // from each other.
	    //
	    if (! checkBinder(X[i], AtomTable::nil))
	      {
		BACKTRACK;
	      }
	  }
	  VMBREAK;
	  
	case OPCODE(PUT_SUBSTITUTION, ARGS(number, register)):
	  {
	    const word32 n = getNumber(PC);
	    const word32 i = getRegister(PC);
	    //
	    // Put a parallel substitution of size "n" into 
	    // term of Xi.
	    // Any substitution already existed in Xi is added
	    // to the left of the new one.
	    // The substitution pointer is set to point to the
	    // beginning so that the substitution pairs will be 
	    // filled in.
	    //
	    SubstitutionBlock* sub = heap.newSubstitutionBlock(n);
	    X[i] = heap.newSubstitutionBlockList(sub, X[i]);
	    StructurePointer = sub->storage();
	  }
	  VMBREAK;
	  
	case OPCODE(PUT_X_TERM_SUBSTITUTION, ARGS(register, register)):
	  {
	    const word32 i = getRegister(PC);
	    const word32 j = getRegister(PC);
	    //
	    // Transfer the term of Xi to the substitution of Xj.
	    //
	    assert(!X[i]->isNil());
	    X[j] = heap.newSubstitution(X[i], X[j]);
	    assert(X[j]->hasLegalSub());
	  }
	  VMBREAK;
	  
	case OPCODE(PUT_Y_TERM_SUBSTITUTION, ARGS(register, register)):
	  {
	    const word32 i = getRegister(PC);
	    const word32 j = getRegister(PC);
	    //
	    // Transfer Yi to the substitution of Xj.
	    //
	    assert(!envStack.yReg(currentEnvironment, i)->isNil());
	    X[j] = heap.newSubstitution(envStack.yReg(currentEnvironment, i),
					X[j]);
	  }
	  VMBREAK;
	  
	case OPCODE(PUT_INITIAL_EMPTY_SUBSTITUTION, ARGS(register)):
	  {
	    const word32 i = getRegister(PC);
	    //
	    // Set the term of Xi to empty.
	    //
	    X[i] = AtomTable::nil;
	  }
	  VMBREAK;

	  //
	  // The "get" instructions unify the head arguments 
	  // with the ones in the query. 
	  //    
	case OPCODE(GET_X_VARIABLE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(PC);
	    const word32 j = getRegister(PC);
	    // 
	    // The instruction is used for unifying an 
	    // unbound variable in the head with argument
	    // in the query. Because a variable can unify 
	    // with any data object, the value in register 
	    // Xj is simply transferred to register Xi.
	    // 
	    X[i] = X[j];
	  }
	  VMBREAK;
	  
	case OPCODE(GET_Y_VARIABLE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(PC);
	    const word32 j = getRegister(PC);
	    // 
	    // The instruction is used for unifying an 
	    // unbound variable in the head with an  
	    // argument in the query. Because a variable
	    // can unify with any data object the value
	    // in register Xj is simply transferred to 
	    // Yi.
	    // 
	    envStack.yReg(currentEnvironment, i) = X[j];
	  }
	  VMBREAK;

	case OPCODE(GET_X_VALUE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(PC);
	    const word32 j = getRegister(PC);

	    // 
	    // The  register Xi is bound to some data object 
	    // by the previous "get_x_variable" instruction. 
	    // This instruction unifies the data objects in 
	    // registers Xi and Xj. Backtrack on failure. 
	    // 
	    if (! unify(X[i], X[j]))
	      {
		BACKTRACK;
	      }
	  }
	  VMBREAK;
	  
	case OPCODE(GET_Y_VALUE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(PC);
	    const word32 j = getRegister(PC);
	    // 
	    // Yi is bound to some data object by the previous 
	    // "get_y_variable" instruction. This instruction 
	    // unifies the data objects in Yi and register Xj. 
	    // Backtrack on failure. 
	    // 
	    assert(envStack.yReg(currentEnvironment, i)->variableDereference()->hasLegalSub());
	    assert(X[j]->variableDereference()->hasLegalSub());

	    if (! unify(envStack.yReg(currentEnvironment, i), X[j]))
	      {
		BACKTRACK;
	      }
	  }
	  VMBREAK;
	  
	case OPCODE(GET_CONSTANT, ARGS(constant, register)):
	  {
	    Object* c = getConstant(PC);
	    const word32 i = getRegister(PC);
	    // 
	    // Dereference register Xi.
	    // Check the argument from the query against the
	    // expected constant.
	    //
	    assert(X[i]->variableDereference()->hasLegalSub());
	    Object* xval = heap.dereference(X[i]);
	    switch (UT(xval->getTag()))
	      {
	      case UT(Object::UVar):
	      case UT(Object::UVarOC):
		bindAndTrail(xval, c);
		break;
	      case UT(Object::UNumber):
	      case UT(Object::UString):
	      case UT(Object::UStruct):
	      case UT(Object::UCons):
		BACKTRACK;
		break;
	      case UT(Object::UAtom):
		if (xval != c) BACKTRACK;
		break;
	      case UT(Object::UOther):
		if (!unifyOtherConst(xval, c, true)) BACKTRACK;
		break;
	      default:
		assert(false);
		break;
	      }
	    VMBREAK;
	  }

	case OPCODE(GET_INTEGER, ARGS(integer, register)):
	  {
	    long n = getInteger(PC);
	    const word32 i = getRegister(PC);
	    // 
	    // Dereference register Xi.
	    // Check the argument from the query against the
	    // expected constant.
	    //
	    assert(X[i]->variableDereference()->hasLegalSub());
	    Object* xval = heap.dereference(X[i]);

	    switch (UT(xval->getTag()))
	      {
	      case UT(Object::UVar):
	      case UT(Object::UVarOC):
		{
		  Object* c = heap.newInteger(n);
		  bindAndTrail(xval, c);
		  break;
		}
	      case UT(Object::UNumber):
		if (!xval->isInteger() || xval->getInteger() != n) BACKTRACK;
		break;
	      case UT(Object::UAtom):
	      case UT(Object::UString):
	      case UT(Object::UStruct):
	      case UT(Object::UCons):
		BACKTRACK;
		break;
	      case UT(Object::UOther):
		{
		  Object* c = heap.newInteger(n);
		  if (!unifyOtherConst(xval, c, true)) BACKTRACK;
		  break;
		}
	      default:
		assert(false);
		break;
	      }
	    VMBREAK;
	  }
 
	case OPCODE(GET_LIST, ARGS(register)):
	  {
	    const word32 i =getRegister(PC);
	    // 
	    // Dereference register Xi.
	    // The expected data object is a list.
	    // Operation to be carried out depends on the value
	    // of the argument from the query.
	    // 
	    assert(X[i]->variableDereference()->hasLegalSub());
	    Object* xval = heap.dereference(X[i]);
	    if (xval->isRefTag())
	      {
		Cons* cons = heap.newCons();
		*(reinterpret_cast<heapobject*>(xval)) = 
		  reinterpret_cast<heapobject>(cons);
		ReadMode = false;
		StructurePointer = cons->storage();
	      }
	    else
	      {
		switch (UT(xval->getTag()))
		  {
		  case UT(Object::UVar):
		    {
		      Cons* newlist = heap.newCons();
		      bindAndTrail(xval, newlist);
		      ReadMode = false;
		      saveTerm = newlist;
		      StructurePointer = newlist->storage();
		      break;
		    }
		  case UT(Object::UVarOC):
		    {
		      Variable* newhead = heap.newVariable();
		      Variable* newtail = heap.newVariable();
		      newhead->setOccursCheck();      
		      newtail->setOccursCheck();    
		      Cons* newlist = heap.newCons(newhead, newtail);
		      bindAndTrail(xval, newlist);
		      ReadMode = true;
		      StructurePointer = newlist->storage();
		      break;
		    }
		  case UT(Object::UNumber):
		  case UT(Object::UAtom):
		  case UT(Object::UStruct):
		  case UT(Object::UString):
		    BACKTRACK;
		    break;
		  case UT(Object::UCons):
		    {
		      StructurePointer = xval->storage();
		      ReadMode = true;
		      break;
		    }
		  case UT(Object::UOther):
		    {
		      Variable* newhead = heap.newVariable();
		      Variable* newtail = heap.newVariable();
		      newhead->setOccursCheck();       
		      newtail->setOccursCheck();      
		      Cons* newlist = heap.newCons(newhead, newtail);
		      if (!unify(xval, newlist))
			{
			  BACKTRACK;
			}
		      else
			{
			  ReadMode = true;
			  StructurePointer = newlist->storage();
			}	
		      break;
		    }
		  default:
		    assert(false);
		    break;
		  }
	      }
	    VMBREAK;
	  }
	case OPCODE(GET_STRUCTURE, ARGS(constant, number, register)):
	  {
	    Object* c = getConstant(PC);
	    const word32 n = getNumber(PC);
	    const word32 i =getRegister(PC);
	    // 
	    // Dereference register Xi.
	    // The expected object is a structure with an atom as
	    // its functor.
	    // Th operation of the instruction depends on the
	    // value of the argument in the query.
	    //

	    assert(X[i]->variableDereference()->hasLegalSub());
	    Object* xval = heap.dereference(X[i]);
	    if (xval->isRefTag())
	      {
		assert(n <= MaxArity);
		Structure* newstruct = heap.newStructure(n);
		newstruct->setFunctor(c);
		*(reinterpret_cast<heapobject*>(xval)) = 
		  reinterpret_cast<heapobject>(newstruct);
		ReadMode = false;
		StructurePointer = newstruct->storage() + 1;
	      }
	    else
	      {
		switch (UT(xval->getTag()))
		  {
		  case UT(Object::UVar):
		    {           
		      assert(n <= MaxArity);
		      Structure* newstruct = heap.newStructure(n);
		      newstruct->setFunctor(c);
		      assert(!OBJECT_CAST(Reference*, xval)->hasExtraInfo());
		      bindAndTrail(xval, newstruct);
		      ReadMode = false;
		      saveTerm = newstruct;
		      StructurePointer = newstruct->storage() + 1;
		      break;
		    }
		  case UT(Object::UVarOC):
		    {
		      assert(n <= MaxArity);
		      Structure* newstruct = heap.newStructure(n);
		      newstruct->setFunctor(c);
		      for (u_int i = 1; i <= n; i++)
			{
			  Variable* arg = heap.newVariable();
			  arg->setOccursCheck();       
			  newstruct->setArgument(i, arg);
			}
		      assert(!OBJECT_CAST(Reference*, xval)->hasExtraInfo());
		      bindAndTrail(xval, newstruct);
		      ReadMode = true;
		      StructurePointer = newstruct->storage() + 1;
		      break;
		  }
		  case UT(Object::UNumber):
		  case UT(Object::UAtom):
		  case UT(Object::UString):
		  case UT(Object::UCons):
		    BACKTRACK;
		    break;
		  case UT(Object::UStruct):
		    {
		      Structure* xstruct = OBJECT_CAST(Structure*, xval);
		      if (xstruct->getArity() != n)
			{
			  BACKTRACK;
			}
		      else
			{
			  Object* funct = heap.dereference(xstruct->getFunctor());
			  if (funct->isAtom() && funct != c)
			    {
			      BACKTRACK;
			    }
			  else if (!unify(funct, c))
			    {
			      BACKTRACK;
			    }
			  StructurePointer = xval->storage() + 1;
			  ReadMode = true;
			}
		      break;
		    }
		  case UT(Object::UOther):
		    {
		      assert(n <= MaxArity);
		      Structure* newstruct = heap.newStructure(n);
		      newstruct->setFunctor(c);
		      for (u_int i = 1; i <= n; i++)
			{
			  Variable* arg = heap.newVariable();
			  arg->setOccursCheck();     
			  newstruct->setArgument(i, arg);
			}
		      if (!unify(xval, newstruct))
			{
			  BACKTRACK;
			}
		      else
			{
			  ReadMode = true;
			  StructurePointer = newstruct->storage() + 1;
			}
		      break;
		    }
		    
		  default:
		    assert(false);
		    break;
		  }
	      }
	    VMBREAK;
	  }
  
	case OPCODE(GET_STRUCTURE_FRAME, ARGS(number, register)):
	  {
	    const word32 n = getNumber(PC);
	    const word32 i =getRegister(PC);
	    // 
	    // Dereference register Xi.
	    // The expected data object is a structure.
	    // The functor of the structure is a term other than
	    // an atom.  The matching of the functor is carried
	    // out by other instructions.
	    // 
	    assert(X[i]->variableDereference()->hasLegalSub());
	    Object* xval = heap.dereference(X[i]);
	    if (xval->isRefTag())
	      {
		      assert(n <= MaxArity);
		Structure* newstruct = heap.newStructure(n);
		*(reinterpret_cast<heapobject*>(xval)) = 
		  reinterpret_cast<heapobject>(newstruct);
		ReadMode = false;
		StructurePointer = newstruct->storage();
	      }
	    else
	      {
		switch (UT(xval->getTag()))
		  {
		  case UT(Object::UVar):
		    {
		      assert(n <= MaxArity);
		      Structure* newstruct = heap.newStructure(n);
		      bindAndTrail(xval, newstruct);
		      ReadMode = false;
		      saveTerm = newstruct;
		      StructurePointer = newstruct->storage();
		      break;
		    }
		  case UT(Object::UVarOC):
		    {
		      assert(n <= MaxArity);
		      Structure* newstruct = heap.newStructure(n);
		      Variable* funct = heap.newVariable();
		      funct->setOccursCheck();
		      newstruct->setFunctor(funct);
		      for (u_int i = 1; i <= n; i++)
			{
			  Variable* arg = heap.newVariable();
			  arg->setOccursCheck();       
			  newstruct->setArgument(i, arg);
			}
		      bindAndTrail(xval, newstruct);
		      ReadMode = true;
		      StructurePointer = newstruct->storage();
		      break;
		  }
		  case UT(Object::UNumber):
		  case UT(Object::UAtom):
		  case UT(Object::UString):
		  case UT(Object::UCons):
		    BACKTRACK;
		    break;
		  case UT(Object::UStruct):
		    {
		      Structure* xstruct = OBJECT_CAST(Structure*, xval);
		      if (xstruct->getArity() != n)
			{
			  BACKTRACK;
			}
		      else
			{
			  StructurePointer = xval->storage();
			  ReadMode = true;
			}
		      break;
		    }
		  case UT(Object::UOther):
		    {
		      assert(n <= MaxArity);
		      Structure* newstruct = heap.newStructure(n);
		      Variable* funct = heap.newVariable();
		      funct->setOccursCheck();
		      newstruct->setFunctor(funct);
		      for (u_int i = 1; i <= n; i++)
			{
			  Variable* arg = heap.newVariable();
			  arg->setOccursCheck();     
			  newstruct->setArgument(i, arg);
			}
		      if (!unify(xval, newstruct))
			{
			  BACKTRACK;
			}
		      else
			{
			  ReadMode = true;
			  StructurePointer = newstruct->storage();
			}
		      break;
		    }
		    
		  default:
		    assert(false);
		    break;
		  }
	      }
	    VMBREAK;
	  }
  
	case OPCODE(GET_X_OBJECT_VARIABLE, ARGS(register, register)):
	  {
	    const word32 i =getRegister(PC);
	    const word32 j = getRegister(PC);
	    //
	    // The expected (new) object variable from Xi is
	    // unified with Xj from the query.
	    //
	    assert(X[j]->variableDereference()->hasLegalSub());
	    Object* xval = heap.dereference(X[j]);
	    X[i] = heap.newObjectVariable();
	    if (!unify(xval, X[i]))
	      {
		BACKTRACK;
	      }
	    VMBREAK;
	  }
	  
	case OPCODE(GET_Y_OBJECT_VARIABLE, ARGS(register, register)):
	  {
	    const word32 i = getRegister(PC);
	    const word32 j = getRegister(PC);
	    //
	    // The expected (new) object variable from Yi is
	    // unified with Xj from the query.
	    //
	    assert(X[j]->variableDereference()->hasLegalSub());
	    Object* xval = heap.dereference(X[j]);
	    ObjectVariable* ov = heap.newObjectVariable();
	    envStack.yReg(currentEnvironment, i) = ov;
	    if (!unify(ov, xval))
	      {
		BACKTRACK;
	      }
	    VMBREAK;
	  }

	case OPCODE(GET_X_OBJECT_VALUE, ARGS(register, register)):
	  {
	    const word32 i =getRegister(PC);
	    const word32 j = getRegister(PC);
	    //
	    // The register Xi is bound to an object variable
	    // by the previous "get_x_object_variable" instruction.
	    // This instruction unifies the object variable in
	    // Xi and data object in Xj.  It is not possible to
	    // have substitution associated with Xi.
	    //
	    assert(i != j);
	    assert(X[i]->isObjectVariable());
	    
	    if (!unify(X[i], X[j]))
	      {
		BACKTRACK;
	      }
	    VMBREAK;
	  }

	case OPCODE(GET_Y_OBJECT_VALUE, ARGS(register, register)):
	  {
	    const word32 i =getRegister(PC);
	    const word32 j = getRegister(PC);
	    //
	    // The register Yi is bound to an object variable
	    // by the previous "get_y_object_variable" instruction.
	    // This instruction unifies the object variable in Yi
	    // and data object in Xj.
	    //
	    assert(envStack.yReg(currentEnvironment, i)
		   ->isObjectVariable());
	    
	    if (!unify(envStack.yReg(currentEnvironment, i), X[j]))
	      {
		BACKTRACK;
	      }
	    VMBREAK;
	  }
	  
	  //
	  // The "unify" instructions are similar to the "get"  
	  // instructions. They are used for transferring terms in and
	  // out of the arguments of a term matched previously by a
	  // "get" instruction.
	  //
	case OPCODE(UNIFY_X_VARIABLE, ARGS(register)):
	  {
	    const word32 i =getRegister(PC);
	    //
	    // In WRITE mode, create a new variable and place 
	    // a reference in Xi and the location pointed by
	    // structure pointer.
	    // In READ mode, place value of structure pointer
	    // into register Xi.
	    //
	    if (ReadMode)
	      {
		X[i] = reinterpret_cast<Object*>(*StructurePointer);
		StructurePointer++;
	      }
	    else
	      {
		Variable* newvar = heap.newVariable();
		newvar->setOccursCheck();
		*StructurePointer = reinterpret_cast<heapobject>(newvar);
		X[i] = newvar;	
		StructurePointer++;
	      }
	  }
	  VMBREAK;
	  
	case OPCODE(UNIFY_Y_VARIABLE, ARGS(register)):
	  {
	    const word32 i =getRegister(PC);
	    //
	    // Similar operation to "unify_x_variable".  Instead
	    // of Xi, Yi is used.
	    //
	    if (ReadMode)
	      {
		envStack.yReg(currentEnvironment, i) 
		  = reinterpret_cast<Object*>(*StructurePointer);
		StructurePointer++;
	      }
	    else
	      {
		Variable* newvar = heap.newVariable();
		newvar->setOccursCheck();
		*StructurePointer = reinterpret_cast<heapobject>(newvar);
		envStack.yReg(currentEnvironment, i) = newvar;
		StructurePointer++;
	      }
	  }
	  VMBREAK;
	  
	case OPCODE(UNIFY_X_VALUE, ARGS(register)):
	  {
	    const word32 i =getRegister(PC);
	    //
	    // In WRITE mode, the value in X[i] is transferred to
	    // the location pointed by structure pointer.
	    // In READ mode, unify register Xi and the value
	    // in the location pointed by structure pointer.
	    //
	    if (ReadMode)
	      {
		if (!unify(X[i], reinterpret_cast<Object*>(*StructurePointer)))
		  {
		    BACKTRACK;
		  }
		StructurePointer++;
		VMBREAK;
	      }
	    else
	      {
		Object* xval = X[i]->variableDereference();
		if (xval == saveTerm) // Occurs check failure
		  {
		    BACKTRACK;
		  }
		else if (xval->isVariable() && 
			 !OBJECT_CAST(Variable*, xval)->isOccursChecked() && 
                         status.testOccursCheck())
		  {
		    Variable* var = OBJECT_CAST(Variable*, xval);
		    trailTag(var);
		    var->setOccursCheck();
		    *StructurePointer = reinterpret_cast<heapobject>(var);
		  }
		else
		  {
		    *StructurePointer = reinterpret_cast<heapobject>(xval);
		  }
		StructurePointer++;
	      }
	    VMBREAK;
	  }

	case OPCODE(UNIFY_Y_VALUE, ARGS(register)):
	  {
	    const word32 i =getRegister(PC);
	    //
	    // The operation performed is the same as
	    // "unify_x_value", but Yi is used instead of Xi.
	    //
	    if (ReadMode)
	      {	
		if (!unify(envStack.yReg(currentEnvironment, i),
			   reinterpret_cast<Object*>(*StructurePointer)))
		  {
		    BACKTRACK;
		  }
		StructurePointer++;
		VMBREAK;
	      }
	    else
	      {
                Object* xval = 
		  envStack.yReg(currentEnvironment, i)->variableDereference();
		if (xval == saveTerm) // Occurs check failure
		  {
		    BACKTRACK;
		  }
		else if (xval->isVariable() &&
			 !OBJECT_CAST(Variable*, xval)->isOccursChecked() &&
                         status.testOccursCheck())
		  {
		    Variable* var = OBJECT_CAST(Variable*, xval);
		    trailTag(var);
		    var->setOccursCheck();
		    *StructurePointer = reinterpret_cast<heapobject>(var);
		  }
		else
		  {
		    *StructurePointer = reinterpret_cast<heapobject>(xval);
		  }
		StructurePointer++;
	      }
	    VMBREAK;
	  }

	case OPCODE(UNIFY_VOID, ARGS(number)):
	  {
	    const word32 n = getNumber(PC);
	    //
	    // In READ mode, skip n heap object pointerss starting at 
	    // location from structure pointer. In WRITE 
	    // mode, create n new unbound variables on 
	    // the heap and place variable objects pointing 
	    // to them into values of structure pointer.
	    //
	  
	    if (ReadMode)
	      {
		StructurePointer = StructurePointer + n;
	      }
	    else
	      {
		for (u_int count = 1; count <= n; count++) 
		  {
		    Variable* var = heap.newVariable();
		    var->setOccursCheck();
		    *StructurePointer = reinterpret_cast<heapobject>(var);
		    StructurePointer++;
		  }
	      }
	    VMBREAK; 
	  }
	  
	  //
	  // Set Instructions are the same as "unify" instructions in
	  // WRITE mode. The use of them after "put" instructions is
	  // more efficient and natural then use of "unify" instructions.
	  //
	case OPCODE(SET_X_VARIABLE, ARGS(register)):
	  {
	    const word32 i =getRegister(PC);
	    //
	    // Create an unbound variable on the heap and 
	    // place a REFERENCE cell pointing to it into 
	    // the value of structure pointer and into
	    // register Xi. Increment structure pointer by   
	    // one.
	    //
	    Variable* var = heap.newVariable();
	    var->setOccursCheck();
	    X[i] = var;
	    *StructurePointer = reinterpret_cast<heapobject>(var);
	    StructurePointer++;
	  }
	  VMBREAK; 

	case OPCODE(SET_Y_VARIABLE, ARGS(register)):
	  {
	    const word32 i =getRegister(PC);
	    //
	    // Create an unbound variable on the heap and 
	    // place a REFERENCE cell pointing to it into 
	    // the value of structure pointer and into Yi.
	    // Increment structure pointer by one.   
	    //
	    Variable* var = heap.newVariable();
	    var->setOccursCheck();
	    envStack.yReg(currentEnvironment, i) = var;
	    *StructurePointer = reinterpret_cast<heapobject>(var);
	    StructurePointer++;
	  }
	  VMBREAK; 
	  
	case OPCODE(SET_X_VALUE, ARGS(register)):
	  {
	    const word32 i =getRegister(PC);
	    //
	    // Place the value in register Xi into the value
	    // of structure pointer. Increment structure 
	    // pointer by one.
	    //
	    Object* xval = X[i]->variableDereference();
	    if(xval->isVariable()&&
	       !OBJECT_CAST(Variable*, xval)->isOccursChecked() &&
               status.testOccursCheck())
	      {
		Variable* var = OBJECT_CAST(Variable*, xval);
		trailTag(var);
		var->setOccursCheck();
	      }
	    else if (xval->isSubstitution())
	      { 
		Substitution* sval = OBJECT_CAST(Substitution*, xval);
		if (sval->getTerm()->isVariable()&&
		    !OBJECT_CAST(Variable*, sval->getTerm())->isOccursChecked()
                    && status.testOccursCheck())
		  {
		    Variable* var = OBJECT_CAST(Variable*, sval->getTerm());
		    trailTag(var);
		    var->setOccursCheck();
		  }
	      }
	    *StructurePointer = reinterpret_cast<heapobject>(xval);
	    StructurePointer++;
	  }
	  VMBREAK; 
	  
	case OPCODE(SET_Y_VALUE, ARGS(register)):
	  {
	    const word32 i =getRegister(PC);
	    //
	    // Place the value in Yi into the value of structure
	    // pointer. Increment structure pointer by one.
	    //
	    Object* xval = envStack.yReg(currentEnvironment, i)->variableDereference();
	    if(xval->isVariable() &&
	       !OBJECT_CAST(Variable*, xval)->isOccursChecked() &&
               status.testOccursCheck())
	      {
		Variable* var = OBJECT_CAST(Variable*, xval);
		trailTag(var);
		var->setOccursCheck();
	      }
	    else if (xval->isSubstitution())
	      { 
		Substitution* sval = OBJECT_CAST(Substitution*, xval);
		if (sval->getTerm()->isVariable() &&
		    !OBJECT_CAST(Variable*, sval->getTerm())->isOccursChecked()
                    && status.testOccursCheck())
		  {
		    Variable* var = OBJECT_CAST(Variable*, sval->getTerm());
		    trailTag(var);
		    var->setOccursCheck();
		  }
	      }
	    *StructurePointer = reinterpret_cast<heapobject>(xval);
	    StructurePointer++;
	  }
	  VMBREAK; 
	  
	case OPCODE(SET_X_OBJECT_VARIABLE, ARGS(register)):
	  {
	    const word32 i =getRegister(PC);
	    //
	    // Create an unbound object variable on the heap and 
	    // place a reference into 
	    // the value of structure pointer and into
	    // register Xi. Increment structure pointer by   
	    // one.
	    //
	    X[i] = heap.newObjectVariable();
	    *StructurePointer = reinterpret_cast<heapobject>(X[i]);
	    StructurePointer++;
	  }
	  VMBREAK; 
	  
	case OPCODE(SET_Y_OBJECT_VARIABLE, ARGS(register)):
	  {
	    const word32 i =getRegister(PC);
	    //
	    // Create an unbound object variable on the heap and 
	    // place a reference into 
	    // the value of structure pointer and into Yi.
	    // Increment structure pointer by one.   
	    //
	    envStack.yReg(currentEnvironment, i) = heap.newObjectVariable();
	    *StructurePointer  = reinterpret_cast<heapobject>(envStack.yReg(currentEnvironment, i));
	    StructurePointer++;
	  }
	  VMBREAK; 
	  
	case OPCODE(SET_X_OBJECT_VALUE, ARGS(register)):
	  {
	    const word32 i =getRegister(PC);
	    //
	    // Place the object variable in register Xi into the
	    // value of structure pointer. Increment structure 
	    // pointer by one.
	    // 
	    assert(X[i]->isObjectVariable());
	    *StructurePointer = reinterpret_cast<heapobject>(X[i]);
	    StructurePointer++;
	  }
	  VMBREAK; 
	  
	case OPCODE(SET_Y_OBJECT_VALUE, ARGS(register)):
	  {
	    const word32 i =getRegister(PC);
	    //
	    // Place the object variable in Yi into the value of
	    // structure pointer. Increment structure pointer by
	    // one.
	    // 
	    *StructurePointer = reinterpret_cast<heapobject>(envStack.yReg(currentEnvironment, i));
	    StructurePointer++;
	  }
	  VMBREAK; 
	  
	case OPCODE(SET_CONSTANT, ARGS(constant)):
	  {
	    Object* c = getConstant(PC);
	    //
	    // Create the constant c on the heap. Increment 
	    // structure pointer by one.
	    // 
	    *StructurePointer = reinterpret_cast<heapobject>(c); 
	    StructurePointer++;
	  }
	  VMBREAK; 

	case OPCODE(SET_INTEGER, ARGS(integer)):
	  {
	    Object* c = heap.newInteger(getInteger(PC));
	    //
	    // Create the constant c on the heap. Increment 
	    // structure pointer by one.
	    // 
	    *StructurePointer = reinterpret_cast<heapobject>(c); 
	    StructurePointer++;
	  }
	  VMBREAK; 

	  
	case OPCODE(SET_VOID, ARGS(number)):
	  {
	    const word32 n = getNumber(PC);
	    //
	    // Create n unbound variables on the heap and
	    // place REFERENCE cell pointing to them into
	    // values of structure pointer.
	    // 
	    for (u_int count = 1; count <= n; count++) 
	      {
		Variable* var = heap.newVariable();
		var->setOccursCheck();
		*StructurePointer = reinterpret_cast<heapobject>(var);
		StructurePointer++;
	      }
	  }
	  VMBREAK; 
	  
	case OPCODE(SET_OBJECT_VOID, ARGS(number)):
	  {
	    const word32 n = getNumber(PC);
	    //
	    // Create n unbound object variables on the heap and
	    // place OBJECT_REFERENCE cell pointing to them into
	    // values of structure pointer.
	    // 
	    for (u_int count = 1; count <= n; count++) 
	      {
		ObjectVariable* var = heap.newObjectVariable();
		*StructurePointer = reinterpret_cast<heapobject>(var);
		StructurePointer++;
	      }
	  }
	  VMBREAK;

	  //
	  // The "control" instructions handle the procedural side of
	  // a program.  They switch the execution flow between
	  // procedures.
	  //
	case OPCODE(ALLOCATE, ARGS(number)):
	  {
	    //
	    // Create a new environment on the stack, set its  
	    // continuation environment field to the current 
	    // environment and its continuation point field
	    // the current continuation point.
	    //
	    const word32 n = getNumber(PC);


	    if (choiceStack.isEnvProtected(currentChoicePoint,
					   currentEnvironment))
	      {
		envStack.setTop(choiceStack.getEnvTop(currentChoicePoint));
	      }
	    else
	      {
		envStack.setTop(currentEnvironment +
				envStack.envSize(currentEnvironment));
	      }
	    currentEnvironment = envStack.push(currentEnvironment,
					       continuationInstr, n);
	  }
	  VMBREAK; 
	  
	case OPCODE(DEALLOCATE, ARGS()):
	  {
	    //
	    // The current environment is set to the 
	    // previous environment.
	    // 
	    const EnvLoc PrevEnv = currentEnvironment;
	    envStack.retrieve(PrevEnv, currentEnvironment, continuationInstr);
	  }
	  VMBREAK; 
	  
	case OPCODE(CALL_PREDICATE, ARGS(predatom, number, number)):
	  {
  	    //
	    // This instruction is used for all the predicate 
	    // calls in the clause except the last one. If the
	    // predicate is defined, set the cut register to
	    // the current choice point's address and the 
	    // continuation pointer to the value of current  
	    // continuation. Execution is continued with 
	    // instruction labeled "predicate". The instruction
	    // is overwritten for the appropriate one according
	    // to the type of the predicate. Exception will
	    // occur if there is an interrupt or the predicate
	    // is undefined.
	    //
	    static const word32 SIZE_OF_CALL_PREDICATE_INSTR =
	      Code::SIZE_OF_INSTRUCTION + Code::SIZE_OF_PRED +
	      Code::SIZE_OF_NUMBER + Code::SIZE_OF_NUMBER;

	    Atom* predicate = getPredAtom(PC);
	    const word32 arity = getNumber(PC);
	    const word32 n = getNumber(PC);

	    ONCE_ONLY(
		      {
			continuationInstr = PC;
			cutPoint = currentChoicePoint;  
			if (envStack.isTopEnv(currentEnvironment) &&
			    (!choiceStack.isEnvProtected(currentChoicePoint,
							 currentEnvironment)))
			  {
			    envStack.trim(currentEnvironment, n);
			  }
		      }
		      );

	    //      assert(check_cps(currentChoicePoint,choiceStack,envStack,heap ));

	    const PredLoc start = predicates->lookUp(predicate, arity, 
						     atoms, code); 

	    if (signals->Status().testSignals() && !in_sigint)
	      {
		HANDLE_SIGNAL(SIZE_OF_CALL_PREDICATE_INSTR);
	      }
	    else if (scheduler->Status().testEnableTimeslice() &&
		     scheduler->Status().testTimeslice())
	      {
		HANDLE_TIMESLICE(SIZE_OF_CALL_PREDICATE_INSTR);
	      }
	    else if (status.testFastRetry() &&
		     !status.testDoingRetry())
	      {
                programCounter = PC;
		status.resetFastRetry();
		status.setDoingRetry();
		Object* problem = BuildCall(predicate, arity);
		PC = HandleFastRetry(problem);
	      }
	    else if (start == EMPTY_LOC)
	      {
                programCounter = PC;
		Object* problem = BuildCall(predicate, arity);
		PC = UndefinedPred(problem);
	      }
	    else if ( getCleanupMinCP() != 0xFFFF)
	      {
                programCounter = PC;
		word32 cleanupCP = getCleanupMinCP();
		resetCleanupMinCP();
		Object* problem = BuildCall(predicate, arity);
		PC = HandleCleanup(problem, cleanupCP);
	      }
	    else
	      {
                bool gc_ok = true;
                if ((heap.doGarbageCollection() || status.testDoGC())
		    && buffers.isEmpty() && !status.testNeckCutRetry())
                  {
		    if (!gc(arity))
                      {
                        gc_ok = false;
                        PC = FailedGC();
                      }
                  }
                if (gc_ok) {
                  const PredCode PredAddr = predicates->getCode(start);
                  if (PredAddr.type() == PredCode::DYNAMIC_PRED)
                    {
                      DynamicPredicate* dp = PredAddr.getDynamicPred();
                      if (!initializeDPcall(dp, arity, PC))
                        {
                          BACKTRACK;
                        }
                    }
                  else if (PredAddr.type() == PredCode::ESCAPE_PRED)
                    {
                      code->updateCallInstruction(PC -
                                                  SIZE_OF_CALL_PREDICATE_INSTR,
                                                  CALL_ESCAPE, (CodeLoc)start);
                      
                      HANDLE_ESCAPE(PredAddr.getEscape()(getFInter()));
                    }
                  else
                    {
                      assert(PredAddr.type() == PredCode::STATIC_PRED);
                      const CodeLoc loc = PredAddr.getPredicate(code); 
                      code->updateCallInstruction(PC -
                                                  SIZE_OF_CALL_PREDICATE_INSTR,
                                                  CALL_ADDRESS, loc);
                      PC = loc;
                    }
                }
	      }
	  }
	  VMBREAK; 
	  
	case OPCODE(CALL_ADDRESS, ARGS(address, number)):
	  {
	    //
	    // This instruction is used for all the predicate 
	    // calls in the clause except the last one. If the
	    // predicate is defined, set the cut register to
	    // the current choice point's address and the 
	    // continuation pointer to the value of current  
	    // continuation. Execution is continued with 
	    // instruction labeled "address". Exception will
	    // occur if there is an interrupt.
	    //

	    static const word32 SIZE_OF_CALL_ADDRESS_INSTR =
	      Code::SIZE_OF_INSTRUCTION + Code::SIZE_OF_ADDRESS +
	      Code::SIZE_OF_NUMBER;

	    const CodeLoc address = getCodeLoc(PC);
	    const word32 n = getNumber(PC);
	    
	    ONCE_ONLY(
		      {
			continuationInstr = PC; 
			cutPoint = currentChoicePoint;  
			if (envStack.isTopEnv(currentEnvironment) &&
			    (!choiceStack.isEnvProtected(currentChoicePoint,
							 currentEnvironment)))
			  {
			    envStack.trim(currentEnvironment, n);
			  }
		      }
		      );

	    if (signals->Status().testSignals() && !in_sigint)
	      {
		HANDLE_SIGNAL(SIZE_OF_CALL_ADDRESS_INSTR);
	      }
	    else if (scheduler->Status().testEnableTimeslice() &&
		     scheduler->Status().testTimeslice())
	      {
		HANDLE_TIMESLICE(SIZE_OF_CALL_ADDRESS_INSTR);
	      }
	    else if (status.testFastRetry() &&
		     !status.testDoingRetry())
	      {
                programCounter = PC;
		status.resetFastRetry();
		status.setDoingRetry();
		CodeLoc loc = address - Code::SIZE_OF_HEADER;
		Atom* predicate = getPredAtom(loc);
		const word32 arity = getNumber(loc);
		Object* problem = BuildCall(predicate, arity);
		PC = HandleFastRetry(problem);
	      }
	    else if ( getCleanupMinCP() != 0xFFFF)
	      {
                programCounter = PC;
		word32 cleanupCP = getCleanupMinCP();
		resetCleanupMinCP();
		CodeLoc loc = address - Code::SIZE_OF_HEADER;
		Atom* predicate = getPredAtom(loc);
		const word32 arity = getNumber(loc);
		Object* problem = BuildCall(predicate, arity);
		PC = HandleCleanup(problem, cleanupCP);
	      }
	    else
	      {
                bool gc_ok = true;
                if ((heap.doGarbageCollection() || status.testDoGC())
		    && buffers.isEmpty() && !status.testNeckCutRetry())
                  {
		    CodeLoc loc = address - Code::SIZE_OF_HEADER;
		    getPredAtom(loc);
		    const word32 arity = getNumber(loc);
		    if (!gc(arity))
                      {
                        gc_ok = false;
                        PC = FailedGC();
                      }
                  }
		if (gc_ok) PC = address;
	      }
	  }
	  VMBREAK; 
	  
	case OPCODE(CALL_ESCAPE, ARGS(address, number)):
	  {
	    //
	    // This instruction is used for all escape functions.
	    // After the escape function is called, the execution
	    // with the following predicate. Exception will
	    // occur if there is an interrupt.
	    //

	    static const word32 SIZE_OF_CALL_ESCAPE_INSTR =
	      Code::SIZE_OF_INSTRUCTION + Code::SIZE_OF_ADDRESS +
	      Code::SIZE_OF_NUMBER;

	    const PredLoc address = getAddress(PC);
	    const word32 n = getNumber(PC);

	    ONCE_ONLY(
		      {
			continuationInstr = PC; 
			cutPoint = currentChoicePoint;  
			if (envStack.isTopEnv(currentEnvironment) &&
			    (!choiceStack.isEnvProtected(currentChoicePoint,
							 currentEnvironment)))
			  {
			    envStack.trim(currentEnvironment, n);
			  }
		      }
		      );

	    if (signals->Status().testSignals() && !in_sigint)
	      {
		HANDLE_SIGNAL(SIZE_OF_CALL_ESCAPE_INSTR);
	      }
	    else if (scheduler->Status().testEnableTimeslice() &&
		     scheduler->Status().testTimeslice())
	      {
		HANDLE_TIMESLICE(SIZE_OF_CALL_ESCAPE_INSTR);
	      }
	    else if (status.testFastRetry() && !status.testDoingRetry())
	      {
                programCounter = PC;
		status.resetFastRetry();
		status.setDoingRetry();
		Atom* predicate = predicates->getPredName(address, atoms);
		const word32 arity = predicates->getArity(address);
		Object* problem = BuildCall(predicate, arity);
		PC = HandleFastRetry(problem);
	      }
	    else if ( getCleanupMinCP() != 0xFFFF)
	      {
                programCounter = PC;
		word32 cleanupCP = getCleanupMinCP();
		resetCleanupMinCP();		
		Atom* predicate = predicates->getPredName(address, atoms);
		const word32 arity = predicates->getArity(address);
		Object* problem = BuildCall(predicate, arity);
		PC = HandleCleanup(problem, cleanupCP);
	      }
	    else
	      { 
		HANDLE_ESCAPE(predicates->getCode(address).getEscape()(getFInter()));
	      }
	  }
	  VMBREAK;
	  
	case OPCODE(EXECUTE_PREDICATE, ARGS(predatom, number)):
	  {
	    //
	    // If the predicate is defined, set the cut register
	    // to the current choice point's address. Continue
	    // execution with instruction labeled "predicate".
	    // Exception will occur if there is an interrupt or
	    // the predicate is undefined.
	    //
	    static const word32 SIZE_OF_EXECUTE_PREDICATE_INSTR =
	      Code::SIZE_OF_INSTRUCTION + Code::SIZE_OF_PRED +
	      Code::SIZE_OF_NUMBER;
  
	    Atom* predicate = getPredAtom(PC);
	    const word32 arity = getNumber(PC);

	    ONCE_ONLY(
		      {
			cutPoint = currentChoicePoint;
		      }
		      );

	    const PredLoc start = predicates->lookUp(predicate, arity,
						     atoms, code);

	    if (signals->Status().testSignals() && !in_sigint)
	      {
		HANDLE_SIGNAL(SIZE_OF_EXECUTE_PREDICATE_INSTR);
	      }
	    else if (scheduler->Status().testEnableTimeslice() &&
		     scheduler->Status().testTimeslice())
	      {
		HANDLE_TIMESLICE(SIZE_OF_EXECUTE_PREDICATE_INSTR);
	      }
	    else if (status.testFastRetry() && !status.testDoingRetry())
	      {
                programCounter = PC;
		status.resetFastRetry();
		status.setDoingRetry();
		Object* problem = BuildCall(predicate, arity);
		PC = HandleFastRetry(problem);
	      }
	    else if (start == EMPTY_LOC)
	      {
                programCounter = PC;
		Object* problem = BuildCall(predicate, arity);
		PC = UndefinedPred(problem);
	      }
	    else if ( getCleanupMinCP() != 0xFFFF)
	      {
                programCounter = PC;
		word32 cleanupCP = getCleanupMinCP();
		resetCleanupMinCP();
		Object* problem = BuildCall(predicate, arity);
		PC = HandleCleanup(problem, cleanupCP);
	      }
	    else
	      {
                bool gc_ok = true;
                if ((heap.doGarbageCollection() || status.testDoGC())
		    && buffers.isEmpty() && !status.testNeckCutRetry())
                  {
		    if (!gc(arity))
                      {
                        gc_ok = false;
                        PC = FailedGC();
                      }
                  }
                if (gc_ok) {
                  const CodeLoc oldpc = PC;
                  const PredCode PredAddr = predicates->getCode(start);
                  if (PredAddr.type() == PredCode::DYNAMIC_PRED)
                    {
                      DynamicPredicate* dp = PredAddr.getDynamicPred();
                      if (!initializeDPcall(dp, arity, PC))
                        {
                          BACKTRACK;
                        }
                    }
                  else if (PredAddr.type() == PredCode::ESCAPE_PRED)
                    {
                      PC = continuationInstr;
                      
                      code->updateCallInstruction(oldpc -
                                                  SIZE_OF_EXECUTE_PREDICATE_INSTR,
                                                  EXECUTE_ESCAPE, (CodeLoc)start); 
                      
                      HANDLE_ESCAPE(PredAddr.getEscape()(getFInter()));
                    }
                  else
                    {
                      assert(PredAddr.type() == PredCode::STATIC_PRED);
                      const CodeLoc loc = PredAddr.getPredicate(code);
                      code->updateCallInstruction(PC -
                                                  SIZE_OF_EXECUTE_PREDICATE_INSTR,
                                                  EXECUTE_ADDRESS, loc);
                      
                      PC = loc;
                    }
                }
	      }
	  }
	  VMBREAK; 
	    
	case OPCODE(EXECUTE_ADDRESS, ARGS(address)):
	  {
	    //
	    // If the predicate is defined, set the cut register
	    // to the current choice point's address. Continue
	    // execution with instruction labeled "address".
	    // Exception will occur if there is an interrupt.
	    //

	    static const word32 SIZE_OF_EXECUTE_ADDRESS_INSTR =
	      Code::SIZE_OF_INSTRUCTION + Code::SIZE_OF_ADDRESS;

	    const CodeLoc address = getCodeLoc(PC);

	    ONCE_ONLY(
		      {
			cutPoint = currentChoicePoint;
		      }
		      );

	    if (signals->Status().testSignals() && !in_sigint)
	      {
		HANDLE_SIGNAL(SIZE_OF_EXECUTE_ADDRESS_INSTR);
	      }
	    else if (scheduler->Status().testEnableTimeslice() &&
		     scheduler->Status().testTimeslice())
	      {
		HANDLE_TIMESLICE(SIZE_OF_EXECUTE_ADDRESS_INSTR);
	      }
	    else if (status.testFastRetry() && !status.testDoingRetry())
	      {
                programCounter = PC;
		status.resetFastRetry();
		status.setDoingRetry();
		CodeLoc loc = address - Code::SIZE_OF_HEADER;
		Atom* predicate = getPredAtom(loc);
		const word32 arity = getNumber(loc);
		Object* problem = BuildCall(predicate, arity);
		PC = HandleFastRetry(problem);
	      }
	    else if ( getCleanupMinCP() != 0xFFFF)
	      {
                programCounter = PC;
		word32 cleanupCP = getCleanupMinCP();
		resetCleanupMinCP();
		CodeLoc loc = address - Code::SIZE_OF_HEADER;
		Atom* predicate = getPredAtom(loc);
		const word32 arity = getNumber(loc);
		Object* problem = BuildCall(predicate, arity);
		PC = HandleCleanup(problem, cleanupCP);
	      }
	    else
	      {
                bool gc_ok = true;
                if ((heap.doGarbageCollection() || status.testDoGC())
		    && buffers.isEmpty() && !status.testNeckCutRetry())
                  {
		    CodeLoc loc = address - Code::SIZE_OF_HEADER;
		    getPredAtom(loc);
		    const word32 arity = getNumber(loc);
		    if (!gc(arity))
                      {
                        gc_ok = false;
                        PC = FailedGC();
                      }
                  }
                if (gc_ok) PC = address;
	      }
	  }
	  VMBREAK;
	  
	case OPCODE(EXECUTE_ESCAPE, ARGS(address)):
	  {
	    //
	    // This instruction is used for all escape functions.
	    // After the escape function is called, the execution
	    // continues with the parent predicate. Exception will
	    // occur if there is an interrupt.
	    //

	    static const word32 SIZE_OF_EXECUTE_ESCAPE_INSTR =
	      Code::SIZE_OF_INSTRUCTION + Code::SIZE_OF_ADDRESS;

	    const PredLoc address = getAddress(PC);

	    ONCE_ONLY(
		      {
			cutPoint = currentChoicePoint;
		      }
		      );

	    if (signals->Status().testSignals() && !in_sigint)
	      {
		HANDLE_SIGNAL(SIZE_OF_EXECUTE_ESCAPE_INSTR);
	      }
	    else if (scheduler->Status().testEnableTimeslice() &&
		     scheduler->Status().testTimeslice())
	      {
		HANDLE_TIMESLICE(SIZE_OF_EXECUTE_ESCAPE_INSTR);
	      }
	    else if (status.testFastRetry() &&
		     !status.testDoingRetry())
	      {
                programCounter = PC;
		status.resetFastRetry();
		status.setDoingRetry();
		Atom* predicate = predicates->getPredName(address, atoms);
		const word32 arity = predicates->getArity(address);
		Object* problem = BuildCall(predicate, arity);
		PC = HandleFastRetry(problem);
	      }
	    else if ( getCleanupMinCP() != 0xFFFF)
	      {
                programCounter = PC;
		word32 cleanupCP = getCleanupMinCP();
		resetCleanupMinCP();
		Atom* predicate = predicates->getPredName(address, atoms);
		const word32 arity = predicates->getArity(address);
		Object* problem = BuildCall(predicate, arity);
		PC = HandleCleanup(problem, cleanupCP);
	      }
	    else
	      {
		PC = continuationInstr; // Simulate PROCEED.

		HANDLE_ESCAPE(predicates->getCode(address).getEscape()(getFInter()));
	      }
	  }
	  VMBREAK;
	  
	case OPCODE(NOOP, ARGS()):
	  //
	  // Do nothing.
	  //
	  VMBREAK;
	  
	case OPCODE(JUMP, ARGS(address)):
	  {
	    //
	    // Jump to the specified address (absolute jump).
	    //
	    const CodeLoc address = getCodeLoc(PC);

	    PC = address;
	  }
	  VMBREAK;

	case OPCODE(PROCEED, ARGS()):
	  //
	  // This instruction indicates the end of a unit 
	  // clause. Execution is continued at instruction 
	  // whose address is in the continuation register. 
	  // 
	  PC = continuationInstr; 
	  VMBREAK; 
  
	case OPCODE(FAIL, ARGS()):
	  //
	  // Initiate backtracking.
	  //
	  BACKTRACK;
	  VMBREAK;
  
	case OPCODE(HALT, ARGS()):
	  //
	  // Halt the execution and exit with 0.
	  //
	  assert(X[0]->variableDereference()->isNumber());
          errorno = X[0]->variableDereference()->getInteger();
	  return RV_HALT;
	  VMBREAK;
	  
	case OPCODE(EXIT, ARGS()):
          programCounter = PC;
	  return RV_EXIT;
	  VMBREAK;
	  
	  // 
	  // The "choice" instructions manipulate with the choice points.
	  // Choice points are 
	  //	 created by: "try_me_else" or "try",
	  //	 removed by: "trust_me" or "trust",
	  //	 updated by: "retry_me_else" or "retry".
	  // 
	case OPCODE(TRY_ME_ELSE, ARGS(number, offset)):
	  {
	    //
	    // Create a new choice point on the stack, set its
	    // next clause field to "label" and other fields to 
	    // the values of corresponding special purpose 
	    // registers. Set current choice point register to
	    // point to the new choice point.  
	    //
	    const word32 arity = getNumber(PC);
	    const word32 label = getOffset(PC);

	    currentChoicePoint =
	      pushChoicePoint(PC + label, arity);
	  }
	  VMBREAK; 
	  
	case OPCODE(RETRY_ME_ELSE, ARGS(offset)):
	  {
	    //
	    // Backtrack to the current choice point. Reset 
	    // all special purpose registers to the values 
	    // from corresponding fields of the current choice 
	    // point. Reset next clause field in the current 
	    // choice point to "label". 
	    //
	    const word32 label = getOffset(PC);

            backtrackTo(choiceStack.fetchChoice(currentChoicePoint));
	    choiceStack.nextClause(currentChoicePoint) =
	      PC + label;
	  }
	  VMBREAK;
	  
	case OPCODE(TRUST_ME_ELSE_FAIL, ARGS()):
	  //
	  // Backtrack to the current choice point. Reset all 
	  // special purpose registers to the values from 
	  // corresponding fields of the current choice point, 
	  // then reset current choice point register to its 
	  // previous value.
	  //
          backtrackTo(choiceStack.fetchChoice(currentChoicePoint));
	  currentChoicePoint = choiceStack.pop(currentChoicePoint);
	  tidyTrails(choiceStack.getHeapAndTrailsState(currentChoicePoint));
	  VMBREAK; 
	  
	case OPCODE(TRY, ARGS(number, offset)):
	  {
	    //
	    // Create a new choice point on the stack, set its 
	    // next clause field to the following instruction 
	    // and the other fields to the values of corresponding 
	    // special purpose registers. Execution is continued 
	    // with instruction labeled "label".
	    // 
	    const word32 arity = getNumber(PC);
	    const word32 label = getOffset(PC);

	    currentChoicePoint = pushChoicePoint(PC, arity);
	    PC += label;
	  }
	  VMBREAK; 
	  
	case OPCODE(RETRY, ARGS(offset)):
	  {
	    //
	    // Backtrack to the current choice point, reset 
	    // all special purpose registers to the values 
	    // from corresponding fields of the current choice 
	    // point, reset next clause field in the current 
	    // choice point to following instruction. Execution 
	    // is continued with instruction labeled "label".
	    //
	    const word32 label = getOffset(PC);

            backtrackTo(choiceStack.fetchChoice(currentChoicePoint));
	    choiceStack.nextClause(currentChoicePoint) = PC;
	    PC += label;
	  }
	  VMBREAK; 
	  
	case OPCODE(TRUST, ARGS(offset)):
	  {
	    //
	    // Backtrack to the current choice point, reset
	    // all special purpose registers to the values  
	    // from corresponding fields of the current choice
	    // point, then reset choice point to its previous
	    // value. Execution is continued with instruction 
	    // labeled "label".
	    // 
	    const word32 label = getOffset(PC);

            backtrackTo(choiceStack.fetchChoice(currentChoicePoint));
	    currentChoicePoint = choiceStack.pop(currentChoicePoint);
	    tidyTrails(choiceStack.getHeapAndTrailsState(currentChoicePoint));
	    PC += label;
	  }
	  VMBREAK; 
	  
	case OPCODE(NECK_CUT, ARGS()):
	  {
	    //
	    // If there is a choice point which was created after 
	    // the choice point from the cut point register set
	    // the current choice point register and tidy the 
	    // trail up to that point. 
	    //
	    if (status.testFastRetry() && !status.testDoingRetry())
	      {
		Structure* problem = heap.newStructure(1);
		Object* result;
		savedPC = PC;
		status.resetFastRetry();
		status.setDoingRetry();
		status.setNeckCutRetry();
		SaveXRegisters();
		problem->setFunctor(AtomTable::delayneckcut);
		result = heap.newInteger(cutPoint);
		problem->setArgument(1, result);
		PC = HandleFastRetry(problem);
	      }
	    else if (currentChoicePoint > cutPoint)
              {
                currentChoicePoint = cutPoint; 
                choiceStack.cut(cutPoint);
                tidyTrails(choiceStack.getHeapAndTrailsState(currentChoicePoint));
              }
	  }
	  VMBREAK; 
	  
	case OPCODE(GET_X_LEVEL, ARGS(register)):
	  {
	    // 
	    // Set Xi to the current value of cut point register. 
	    // 
	    const word32 i = getRegister(PC);
	    assert(false);
	    X[i] = reinterpret_cast<Object*>(cutPoint);
	  }
	  VMBREAK; 
	  
	case OPCODE(GET_Y_LEVEL, ARGS(register)):
	  {
	    // 
	    // Set Yi to the current value of cut point register. 
	    // 
	    const word32 i = getRegister(PC);

	    envStack.yReg(currentEnvironment, i) = 
	      heap.newInteger(cutPoint);
	  }
	  VMBREAK; 
	  
	case OPCODE(CUT, ARGS(register)):
	  {
	    //
	    // If there are some choice points after the choice
	    // point indicated by i-th environment variable,
	    // discard all such and tidy the trail up to that 
	    // point. 
	    // 
	    const word32 i = getRegister(PC);
	    assert(envStack.yReg(currentEnvironment, i)->isNumber());
	    if (status.testFastRetry() && !status.testDoingRetry())
	      {
		Structure* problem = heap.newStructure(1);
		Object* result;
		status.resetFastRetry();
		status.setDoingRetry();
		problem->setFunctor(AtomTable::cut_atom);
		result = envStack.yReg(currentEnvironment, i);
		problem->setArgument(1, result);
		PC = HandleFastRetry(problem);
	      }
	    else
	      {

		const ChoiceLoc cutY =
		  (word32)(envStack.yReg(currentEnvironment, i)->getInteger());

		if (currentChoicePoint > cutY)
		  {
		    currentChoicePoint = cutY;
		    choiceStack.cut(cutY);
                    tidyTrails(choiceStack.getHeapAndTrailsState(cutY));
		  }
	      }
	  }
	  VMBREAK; 
	  
	  //
	  // The purpose of the indexing instructions is to filter 
	  // out clauses which cannot unify with a goal, and link 
	  // the candidate clauses together.
	  // The jump provided by the instructions is relative to 
	  // the program counter.
	  //
	case OPCODE(SWITCH_ON_TERM, ARGS(register)):
	  {
	    // switch_on_term i, 
	    //		  VARIABLE_LABEL,
	    // 		  OB_VARIABLE_LABEL,
	    // 		  LIST_LABEL,
	    //		  STRUCTURE_LABEL,
	    // 		  QUANTIFIER_LABEL,
	    //		  CONSTANT_LABEL
	    // 
	    // Dereference the register Xi. If the dereferenced
	    // value is a variable, a constant, a non-empty list 
	    // or a structure, go to labeled instructions.
	    // 
	    const word32 i = getRegister(PC);

            assert(X[i]->hasLegalSub());
	    PrologValue pval1(X[i]);

	    heap.prologValueDereference(pval1);
	    //
	    // The indices for the table is based on utag.
	    //
	    CodeLoc loc =
	      PC + Code::SIZE_OF_OFFSET * pval1.getTerm()->switchOffset();
	    const word32 offset = getOffset(loc); 
	    if (offset == Code::FAIL)
	      {
		BACKTRACK;
	      }
	    else
	      {
		//
		// The offset is relative to the end of
		// the table.  So the table, which has 6
		// entries, must be jumped over first.
		//

		PC += 6 * Code::SIZE_OF_OFFSET + offset;
	      }
	  }
	  VMBREAK; 
	  
	case OPCODE(SWITCH_ON_CONSTANT, ARGS(register, tablesize)):
	  {
	    // 
	    // Dereference the register Xi, go to the instruction
	    // associated to the constant in the hash table "table"
	    // of size n. If the constant is not in the table, 
	    // backtrack.
	    // 
	    const word32 i = getRegister(PC);
	    const word32 n = getTableSize(PC);
	    
	    ConstantTable CodeConstTable(*code, PC, n);
	    
	    assert(X[i]->variableDereference()->hasLegalSub());
	    Object* val = heap.dereference(X[i]);
	    
	    ConstEntry constant; 
            if (val->isAtom())
	      {
		constant.assign(reinterpret_cast<wordptr>(val), 
				ConstEntry::ATOM_TYPE);
	      }
            else if (val->isString())
              {
                constant.assign((long)(Hash(OBJECT_CAST(StringObject*, val)->getChars())),
                                ConstEntry::INTEGER_TYPE);
              }
	    else
	      {
		assert(val->isNumber());
                if (val->isInteger())
                  {
		    constant.assign((long)(val->getInteger()),
				    ConstEntry::INTEGER_TYPE);
                  }
                else
                  {
                    double d = val->getDouble();
                    u_int x[2];
                    memcpy(x, &d, sizeof(double));
                    word32 v = (x[0] | x[1]) & ~(x[0] & x[1]);
                    constant.assign(v, ConstEntry::INTEGER_TYPE);
                  }
	      }
	    
	    const word32 label = CodeConstTable.lookUp(constant);
	    if (label == Code::FAIL)
	      {
		BACKTRACK;
	      }
	    else
	      {
		//
		// The offset is relative to the beginning of
		// the table.
		//
		PC += label;
	      }
	  }
	  VMBREAK;
	  
	case OPCODE(SWITCH_ON_STRUCTURE, ARGS(register, tablesize)):
	  {
	    // 
	    // Dereference the register Xi, go to the instruction 
	    // associated to the structure in the hash table 
	    // "table" of size n. If the functor is not in the 
	    // table, backtrack.
	    // 

	    const word32 i = getRegister(PC);
	    const word32 n = getTableSize(PC);
	    
	    StructureTable CodeStructTable(*code, PC, n);
	    
	    assert(X[i]->variableDereference()->hasLegalSub());
	    Object* val = heap.dereference(X[i]);
	    word32 arity;
	    Object* func;

	    if (val->isStructure())
	      {
		Structure* str = OBJECT_CAST(Structure*, val);
		arity = static_cast<word32>(str->getArity());
		func = heap.dereference(str->getFunctor());
		if (!func->isAtom())
		  {
		    func = AtomTable::dollar;
		    arity = 0;
		  }
	      }
	    else
	      {
		assert(val->isSubstitution());
                assert(val->hasLegalSub());
		PrologValue pval(val);

		heap.prologValueDereference(pval);
		assert(pval.getTerm()->isStructure());
		Structure* str = OBJECT_CAST(Structure*,pval.getTerm());
		arity = static_cast<word32>(str->getArity());
		PrologValue pfunc(pval.getSubstitutionBlockList(), 
				  str->getFunctor());
		heap.prologValueDereference(pfunc);
		func = pfunc.getTerm();
		if (!func->isAtom())
		  {
		    func = AtomTable::dollar;
		    arity = 0;
		  }
	      }
			    
	    StructEntry structure(reinterpret_cast<wordptr>(func), arity);
	    
	    const word32 label = CodeStructTable.lookUp(structure);

	    if (label == Code::FAIL)
	      {
		BACKTRACK;
	      }
	    else
	      {
		//
		// The offset is relative to the beginning of
		// the table.
		//
		PC += label;
	      }
	  }
	  VMBREAK;
	  
	case OPCODE(SWITCH_ON_QUANTIFIER, ARGS(register, tablesize)):
	  {
	    // 
	    // Dereference the register Xi, go to the instruction 
	    // associated to the quantifier in the hash table 
	    // "table" of size n. If the quantifier is not in the 
	    // table, backtrack.
	    // 

	    const word32 i = getRegister(PC);
	    const word32 n = getTableSize(PC);
	    
	    const StructureTable CodeQuantTable(*code, PC, n);
	    
            assert(X[i]->hasLegalSub());
	    PrologValue pval(X[i]);

	    heap.prologValueDereference(pval);

	    assert(pval.getTerm()->isQuantifiedTerm());

	    QuantifiedTerm* quantterm 
	      = OBJECT_CAST(QuantifiedTerm*, pval.getTerm());
	    word32 arity 
	      = static_cast<word32>(quantterm->getBoundVars()->boundListLength());
	    
	   
	    PrologValue quant(pval.getSubstitutionBlockList(), 
			      quantterm->getQuantifier());

	    heap.prologValueDereference(quant);
	    Object* q = quant.getTerm();

	    if (!q->isAtom() || arity == WORD32_MAX)
	      {
		q = AtomTable::dollar;
		arity = 0;
	      }
	    
	    StructEntry structure(reinterpret_cast<wordptr>(q), arity);
	    
	    const word32 label = CodeQuantTable.lookUp(structure);
	    if (label == Code::FAIL)
	      {
		BACKTRACK;
	      }
	    else
	      {
		//
		// The offset is relative to the beginning of
		// the table.
		//
		PC += label;
	      }
	  }
	  VMBREAK;

	  //
	  // The pseudo-instructions are intended to be a long term replacement
	  // for the old escape functions.
	  //
	case OPCODE(PSEUDO_INSTR0, ARGS(number)):
	  {
	    //
	    // An instruction with no arguments.
	    //

	    static const word32 SIZE_OF_PSEUDO_INSTR0 =
	      Code::SIZE_OF_INSTRUCTION + Code::SIZE_OF_NUMBER;

	    const word32 n = getNumber(PC);

	    if (status.testFastRetry() &&
		!status.testDoingRetry())
	      {
                programCounter = PC;
		status.resetFastRetry();
		status.setDoingRetry();
		Object* problem = psi0BuildCall(n);
		PC = HandleFastRetry(problem);
	      }
	    else
	      {
                programCounter = PC;
		const ReturnValue rv = (this->*pseudo_instr0_array[n].funct)();
                PC = programCounter;
		
		if (rv == RV_ERROR)
		  {
		    PC = psi0ErrorHandler(n);
		  }
		else
		  {
		    HANDLE_PSI(rv, SIZE_OF_PSEUDO_INSTR0);
		  }
	      }
	  }
	  VMBREAK;

	case OPCODE(PSEUDO_INSTR1, ARGS(number, register)):
	  {
	    //
	    // An instruction with 1 argument.
	    //

	    static const word32 SIZE_OF_PSEUDO_INSTR1 = 
	      Code::SIZE_OF_INSTRUCTION + Code::SIZE_OF_NUMBER +
	      Code::SIZE_OF_REGISTER;

	    const word32 n = getNumber(PC);
	    const word32 i = getRegister(PC);
	    Object*& arg1 = PSIGetReg(i);

	    if (status.testFastRetry() &&
		!status.testDoingRetry())
	      {
                programCounter = PC;
		status.resetFastRetry();
		status.setDoingRetry();
		psi1NewVars(pseudo_instr1_array[n].mode, 
			    arg1);
		Object* problem = psi1BuildCall(n, arg1);
		PC = HandleFastRetry(problem);
	      }
	    else
	      {
                programCounter = PC;
		const ReturnValue rv 
		  = (this->*pseudo_instr1_array[n].funct)(arg1);
                PC = programCounter;
		if (rv == RV_ERROR)
		  {
		    psi1NewVars(pseudo_instr1_array[n].mode, arg1);
		    PC = psi1ErrorHandler(n, arg1);
		  }
		else
		  {
		    HANDLE_PSI(rv, SIZE_OF_PSEUDO_INSTR1);
		  }
	      }
	  }
	  VMBREAK;

	case OPCODE(PSEUDO_INSTR2, ARGS(number, register, register)):
	  {
	    //
	    // An instruction with 2 arguments.
	    //
	    static const word32 SIZE_OF_PSEUDO_INSTR2 = 
	      Code::SIZE_OF_INSTRUCTION + Code::SIZE_OF_NUMBER +
	      2 * Code::SIZE_OF_REGISTER;

	    const word32 n = getNumber(PC);
	    const word32 i = getRegister(PC);
	    const word32 j = getRegister(PC);

	    Object*& arg1 = PSIGetReg(i);
	    Object*& arg2 = PSIGetReg(j);

	    if (status.testFastRetry() &&
		!status.testDoingRetry())
	      {
                programCounter = PC;
		status.resetFastRetry();
		status.setDoingRetry();
		psi2NewVars(pseudo_instr2_array[n].mode,
			    arg1, arg2);
		Object* problem =  psi2BuildCall(n, arg1, arg2);
		PC = HandleFastRetry(problem);
	      }
	    else
	      {
                programCounter = PC;
		const ReturnValue rv = 
		  (this->*pseudo_instr2_array[n].funct)(arg1, arg2);
                PC = programCounter;

		if (rv == RV_ERROR)
		  {
		    psi2NewVars(pseudo_instr2_array[n].mode,
				arg1, arg2);
		    PC = psi2ErrorHandler(n, arg1, arg2);
		  }
		else
		  {
		    HANDLE_PSI(rv, SIZE_OF_PSEUDO_INSTR2);
		  }
	      }
	  }
	  VMBREAK;

	case OPCODE(PSEUDO_INSTR3, ARGS(number, register, register, register)):
	  {
	    // 
	    // An instruction with 3 arguments.
	    //
	    static const word32 SIZE_OF_PSEUDO_INSTR3 = 
	      Code::SIZE_OF_INSTRUCTION + Code::SIZE_OF_NUMBER +
	      3 * Code::SIZE_OF_REGISTER;

	    const word32 n = getNumber(PC);
	    const word32 i = getRegister(PC);
	    const word32 j = getRegister(PC);
	    const word32 k = getRegister(PC);

	    Object*& arg1 = PSIGetReg(i);
	    Object*& arg2 = PSIGetReg(j);
	    Object*& arg3 = PSIGetReg(k);

	    if (status.testFastRetry() &&
		!status.testDoingRetry())
	      {
                programCounter = PC;
		status.resetFastRetry();
		status.setDoingRetry();
		psi3NewVars(pseudo_instr3_array[n].mode,
			    arg1, arg2, arg3);
		Object* problem = psi3BuildCall(n, arg1, arg2, arg3);
		PC = HandleFastRetry(problem);
	      }
	    else
	      {
                programCounter = PC;
		const ReturnValue rv =
		  (this->*pseudo_instr3_array[n].funct)(arg1, arg2, arg3);
                PC = programCounter;

		if (rv == RV_ERROR)
		  {
		    psi3NewVars(pseudo_instr3_array[n].mode,
				arg1, arg2, arg3);
		    PC = 
		      psi3ErrorHandler(n, arg1, arg2, arg3);
		  }
		else
		  {
		    HANDLE_PSI(rv, SIZE_OF_PSEUDO_INSTR3);
		  }
	      }
	  }
	  VMBREAK;

	case OPCODE(PSEUDO_INSTR4, ARGS(number, register, register, register, register)):
	  {
	    //
	    // An instruction with 4 arguments.
	    //
	    static const word32 SIZE_OF_PSEUDO_INSTR4 = 
	      Code::SIZE_OF_INSTRUCTION + Code::SIZE_OF_NUMBER +
	      4 * Code::SIZE_OF_REGISTER;

	    const word32 n = getNumber(PC);
	    const word32 i = getRegister(PC);
	    const word32 j = getRegister(PC);
	    const word32 k = getRegister(PC);
	    const word32 m = getRegister(PC);

	    Object*& arg1 = PSIGetReg(i);
	    Object*& arg2 = PSIGetReg(j);
	    Object*& arg3 = PSIGetReg(k);
	    Object*& arg4 = PSIGetReg(m);

	    if (status.testFastRetry() &&
		!status.testDoingRetry())
	      {
                programCounter = PC;
		status.resetFastRetry();
		status.setDoingRetry();
		psi4NewVars(pseudo_instr4_array[n].mode,
			    arg1, arg2, arg3, arg4);
		Object* problem = 
		  psi4BuildCall(n, arg1, arg2, arg3, arg4);
		PC = HandleFastRetry(problem);
	      }
	    else
	      {
                programCounter = PC;
		const ReturnValue rv =
		  (this->*pseudo_instr4_array[n].funct)(arg1, arg2, arg3,
							arg4);
                PC = programCounter;
		if (rv == RV_ERROR)
		  {
		    psi4NewVars(pseudo_instr4_array[n].mode,
				arg1, arg2, arg3, arg4);
		    PC = 
		      psi4ErrorHandler(n, arg1, arg2, arg3, arg4);
		  }
		else
		  {
		    HANDLE_PSI(rv, SIZE_OF_PSEUDO_INSTR4);
		  }
	      }
	  }
	  VMBREAK;

	case OPCODE(PSEUDO_INSTR5, ARGS(number, register, register, register, register, register)):
	  {
	    //
	    // An instruction with 5 arguments.
	    //
	    static const word32 SIZE_OF_PSEUDO_INSTR5 = 
	      Code::SIZE_OF_INSTRUCTION + Code::SIZE_OF_NUMBER +
	      5 * Code::SIZE_OF_REGISTER;

	    const word32 n = getNumber(PC);
	    const word32 i = getRegister(PC);
	    const word32 j = getRegister(PC);
	    const word32 k = getRegister(PC);
	    const word32 m = getRegister(PC);
	    const word32 o = getRegister(PC);

	    Object*& arg1 = PSIGetReg(i);
	    Object*& arg2 = PSIGetReg(j);
	    Object*& arg3 = PSIGetReg(k);
	    Object*& arg4 = PSIGetReg(m);
	    Object*& arg5 = PSIGetReg(o);

	    if (status.testFastRetry() &&
		!status.testDoingRetry())
	      {
                programCounter = PC;
		status.resetFastRetry();
		status.setDoingRetry();
		psi5NewVars(pseudo_instr5_array[n].mode,
			    arg1, arg2, arg3, arg4, arg5);
		Object* problem = 
		  psi5BuildCall(n, arg1, arg2, arg3, arg4, arg5);
		PC = HandleFastRetry(problem);
	      }
	    else
	      {
                programCounter = PC;
		const ReturnValue rv = 
		  (this->*pseudo_instr5_array[n].funct)(arg1, arg2, arg3,
							arg4, arg5);
                PC = programCounter;
		if (rv == RV_ERROR)
		  {
		    psi5NewVars(pseudo_instr5_array[n].mode,
				arg1, arg2, arg3, arg4,	arg5);
		    PC = 
		      psi5ErrorHandler(n, arg1, arg2, arg3, arg4, arg5);
		  }
		else
		  {
		    HANDLE_PSI(rv, SIZE_OF_PSEUDO_INSTR5);
		  }
	      }
	  }
	  VMBREAK;

	case OPCODE(UNIFY_CONSTANT, ARGS(constant)):
	  {
	    Object* c = getConstant(PC);
	    if (ReadMode)
	      {
		Object* val = heap.dereference(reinterpret_cast<Object*>(*StructurePointer));
	
		if (val->isConstant())
		  {
		    if (c != val)
		      {
			BACKTRACK;
		      }
		  }
		else if (val->isVariable())
		  {
		    Variable* v = OBJECT_CAST(Variable*, val);
		    if (v->isFrozen() && !status.testHeatWave())
		      {
			BACKTRACK;
		      }
		    else
		      {
			bind(v, c);
		      }
		  }
		else if (!(val->isSubstitution() && unify(val, c)))
		  {
		    BACKTRACK;
		  }
		StructurePointer++;
	      }
	    else
	      {
		*StructurePointer = reinterpret_cast<heapobject>(c);
		StructurePointer++;
	      }
	  }
	  VMBREAK;

	case OPCODE(UNIFY_INTEGER, ARGS(integer)):
	  {
	    int32 n = getInteger(PC);
	    if (ReadMode)
	      {
		Object* xval = heap.dereference(reinterpret_cast<Object*>(*StructurePointer));
	
		switch (UT(xval->getTag()))
		  {
		  case UT(Object::UVar):
		  case UT(Object::UVarOC):
		    {
		      Object* c = heap.newInteger(n);
		      bindAndTrail(xval, c);
		      break;
		    }
		  case UT(Object::UNumber):
		    if (!xval->isInteger() || xval->getInteger() != n) BACKTRACK;
		    break;
		  case UT(Object::UAtom):
		  case UT(Object::UString):
		  case UT(Object::UStruct):
		  case UT(Object::UCons):
		    BACKTRACK;
		    break;
		  case UT(Object::UOther):
		    {
		      Object* c = heap.newInteger(n);
		      if (!unifyOtherConst(xval, c, true)) BACKTRACK;
		      break;
		    }
		  default:
		    assert(false);
		    break;
		  }
		
		StructurePointer++;
	      }
	    else
	      {
		Object* c = heap.newInteger(n);
		*StructurePointer = reinterpret_cast<heapobject>(c);
		StructurePointer++;
	      }
	  }
	  VMBREAK;

	case OPCODE(UNIFY_X_REF, ARGS(register)):
	  {
	    const word32 i =getRegister(PC);
	    //
	    // In WRITE mode, adda ref tag word to the
	    // structure pointer location.
	    // In READ mode, place value of structure pointer
	    // into register Xi.
	    //
	    if (ReadMode)
	      {
		X[i] = reinterpret_cast<Object*>(*StructurePointer);
		StructurePointer++;
	      }
	    else
	      {
		*StructurePointer = Object::RefTag;
		X[i] = reinterpret_cast<Object*>(StructurePointer);	
		StructurePointer++;
	      }
	  }
	  VMBREAK;
	  
	case OPCODE(UNIFY_Y_REF, ARGS(register)):
	  {
	    const word32 i =getRegister(PC);
	    //
	    // Similar operation to "unify_x_ref".  Instead
	    // of Xi, Yi is used.
	    //
	    if (ReadMode)
	      {
		envStack.yReg(currentEnvironment, i) 
		  = reinterpret_cast<Object*>(*StructurePointer);
		StructurePointer++;
	      }
	    else
	      {		
		*StructurePointer = Object::RefTag;

		envStack.yReg(currentEnvironment, i) = 
		  reinterpret_cast<Object*>(StructurePointer);	
		StructurePointer++;
	      }
	  }
	  VMBREAK;

	case OPCODE(DB_JUMP, ARGS(number, address, address, address)):
	  {
	    assert(false);
#if 0
	    (void)getNumber(PC);
	    DynamicPredicate* pred = 
	      reinterpret_cast<DynamicPredicate*>(getAddress(PC));
	    CodeLoc first = getCodeLoc(PC);
	    PC = first;
	    RefObject r(REF_CLAUSE, pred); 
	    pred->aquire();
	    refTrail.trail(r);
#endif
	  }
	  VMBREAK;


	case OPCODE(DB_EXECUTE_PREDICATE, ARGS(predatom, number)):
	  {
	    //
	    // Similar to EXECUTE_PREDICATE but for last call of
	    // dynamic clause
	    //
	    static const word32 SIZE_OF_DB_EXECUTE_PREDICATE_INSTR =
	      Code::SIZE_OF_INSTRUCTION + Code::SIZE_OF_PRED +
	      Code::SIZE_OF_NUMBER;
  
	    Atom* predicate = getPredAtom(PC);
	    const word32 arity = getNumber(PC);

	    ONCE_ONLY(
		      {
			cutPoint = currentChoicePoint;
		      }
		      );

	    const PredLoc start = predicates->lookUp(predicate, arity,
						     atoms, code);

	    if (signals->Status().testSignals() && !in_sigint)
	      {
		HANDLE_SIGNAL(SIZE_OF_DB_EXECUTE_PREDICATE_INSTR);
	      }
	    else if (scheduler->Status().testEnableTimeslice() &&
		     scheduler->Status().testTimeslice())
	      {
		HANDLE_TIMESLICE(SIZE_OF_DB_EXECUTE_PREDICATE_INSTR);
	      }
	    else if (status.testFastRetry() && !status.testDoingRetry())
	      {
                programCounter = PC;
		status.resetFastRetry();
		status.setDoingRetry();
		Object* problem = BuildCall(predicate, arity);
		PC = HandleFastRetry(problem);
	      }
	    else if (start == EMPTY_LOC)
	      {
                programCounter = PC;
		Object* problem = BuildCall(predicate, arity);
		PC = UndefinedPred(problem);
	      }
	    else if ( getCleanupMinCP() != 0xFFFF)
	      {
                programCounter = PC;
		word32 cleanupCP = getCleanupMinCP();
		resetCleanupMinCP();
		Object* problem = BuildCall(predicate, arity);
		PC = HandleCleanup(problem, cleanupCP);
	      }
	    else
	      {
                bool gc_ok = true;
                if ((heap.doGarbageCollection() || status.testDoGC())
		    && buffers.isEmpty() && !status.testNeckCutRetry())
                  {		    
                    if (!gc(arity))
                      {
                        gc_ok = false;
                        PC = FailedGC();
                      }
                  }
                if (gc_ok) {
                  Choice* currChoice 
                    = choiceStack.fetchChoice(currentChoicePoint);
                  int time = currChoice->getTimestamp();
                  if (time == -1)
                    {
                      currentChoicePoint = choiceStack.pop(currentChoicePoint);
                      tidyTrails(choiceStack.getHeapAndTrailsState(currentChoicePoint));
                      cutPoint = currentChoicePoint;
                    }
                  const PredCode PredAddr = predicates->getCode(start);
                  if (PredAddr.type() == PredCode::DYNAMIC_PRED)
                    {
                      DynamicPredicate* dp = PredAddr.getDynamicPred();
                      if (!initializeDPcall(dp, arity, PC))
                        {
                          BACKTRACK;
                        }
                    }
                  else if (PredAddr.type() == PredCode::ESCAPE_PRED)
                    {
                      PC = continuationInstr;

                      HANDLE_ESCAPE(PredAddr.getEscape()(getFInter()));
                    }
                  else
                    {
                      assert(PredAddr.type() == PredCode::STATIC_PRED);
                      const CodeLoc loc = PredAddr.getPredicate(code);
                      code->updateCallInstruction(PC - SIZE_OF_DB_EXECUTE_PREDICATE_INSTR,
                                                  DB_EXECUTE_ADDRESS, loc);
                      PC = loc;
                    }
                }
	      }
	  }
	  VMBREAK; 

	case OPCODE(DB_EXECUTE_ADDRESS, ARGS(address)):
	  {
	    //
	    // Similar to EXECUTE_ADDRESS but for last call of
	    // dynamic clause
	    //

	    static const word32 SIZE_OF_DB_EXECUTE_ADDRESS_INSTR =
	      Code::SIZE_OF_INSTRUCTION + Code::SIZE_OF_ADDRESS;

	    const CodeLoc address = getCodeLoc(PC);

	    ONCE_ONLY(
		      {
			cutPoint = currentChoicePoint;
		      }
		      );

	    if (signals->Status().testSignals() && !in_sigint)
	      {
		HANDLE_SIGNAL(SIZE_OF_DB_EXECUTE_ADDRESS_INSTR);
	      }
	    else if (scheduler->Status().testEnableTimeslice() &&
		     scheduler->Status().testTimeslice())
	      {
		HANDLE_TIMESLICE(SIZE_OF_DB_EXECUTE_ADDRESS_INSTR);
	      }
	    else if (status.testFastRetry() && !status.testDoingRetry())
	      {
                programCounter = PC;
		status.resetFastRetry();
		status.setDoingRetry();
		CodeLoc loc = address - Code::SIZE_OF_HEADER;
		Atom* predicate = getPredAtom(loc);
		const word32 arity = getNumber(loc);
		Object* problem = BuildCall(predicate, arity);
		PC = HandleFastRetry(problem);
	      }
	    else if ( getCleanupMinCP() != 0xFFFF)
	      {
                programCounter = PC;
		word32 cleanupCP = getCleanupMinCP();
		resetCleanupMinCP();
		CodeLoc loc = address - Code::SIZE_OF_HEADER;
		Atom* predicate = getPredAtom(loc);
		const word32 arity = getNumber(loc);
		Object* problem = BuildCall(predicate, arity);
		PC = HandleCleanup(problem, cleanupCP);
	      }
	    else
	      {
                bool gc_ok = true;
                if ((heap.doGarbageCollection() || status.testDoGC())
		    && buffers.isEmpty() && !status.testNeckCutRetry())
                  {
		    CodeLoc loc = address - Code::SIZE_OF_HEADER;
		    getPredAtom(loc);
		    const word32 arity = getNumber(loc);
                    if (!gc(arity))
                      {
                        gc_ok = false;
                        PC = FailedGC();
                      }
                  }
                if (gc_ok) {
                  Choice* currChoice 
                    = choiceStack.fetchChoice(currentChoicePoint);
                  int time = currChoice->getTimestamp();
                  if (time == -1)
                    {
                      currentChoicePoint = choiceStack.pop(currentChoicePoint);
                      tidyTrails(choiceStack.getHeapAndTrailsState(currentChoicePoint));
                      cutPoint = currentChoicePoint;
                    }
                  PC = address;
                }
              }
	  }
	  VMBREAK;

	case OPCODE(DB_PROCEED, ARGS()):
          {
	    Choice* currChoice = choiceStack.fetchChoice(currentChoicePoint);
	    int time = currChoice->getTimestamp();
	    if (time == -1)
	      {
		currentChoicePoint = choiceStack.pop(currentChoicePoint);
		tidyTrails(choiceStack.getHeapAndTrailsState(currentChoicePoint));
	      }
	    PC = continuationInstr; 
          }
          VMBREAK;

	case OPCODE(PUT_DOUBLE, ARGS(double, register)):
	  {
	    Object* c = heap.newDouble(getDouble(PC));
	    const word32 i = getRegister(PC);
	    //
	    // Place a number cell c into
	    // register Xi.
	    //
	    X[i]= c;
	  }
	  VMBREAK;


	case OPCODE(GET_DOUBLE, ARGS(double, register)):
	  {
	    double n = getDouble(PC);
	    const word32 i = getRegister(PC);
	    // 
	    // Dereference register Xi.
	    // Check the argument from the query against the
	    // expected constant.
	    //
	    assert(X[i]->variableDereference()->hasLegalSub());
	    Object* xval = heap.dereference(X[i]);

	    switch (UT(xval->getTag()))
	      {
	      case UT(Object::UVar):
	      case UT(Object::UVarOC):
		{
		  Object* c = heap.newDouble(n);
		  bindAndTrail(xval, c);
		  break;
		}
	      case UT(Object::UNumber):
		if (!xval->isDouble() || xval->getDouble() != n) BACKTRACK;
		break;
	      case UT(Object::UAtom):
	      case UT(Object::UString):
	      case UT(Object::UStruct):
	      case UT(Object::UCons):
		BACKTRACK;
		break;
	      case UT(Object::UOther):
		{
		  Object* c = heap.newDouble(n);
		  if (!unifyOtherConst(xval, c, true)) BACKTRACK;
		  break;
		}
	      default:
		assert(false);
		break;
	      }
	    VMBREAK;
	  }
 
	case OPCODE(SET_DOUBLE, ARGS(double)):
	  {
	    Object* c = heap.newDouble(getDouble(PC));
	    //
	    // Create the constant c on the heap. Increment 
	    // structure pointer by one.
	    // 
	    *StructurePointer = reinterpret_cast<heapobject>(c); 
	    StructurePointer++;
	  }
	  VMBREAK; 


	case OPCODE(UNIFY_DOUBLE, ARGS(double)):
	  {
	    double n = getDouble(PC);
	    if (ReadMode)
	      {
		Object* xval = heap.dereference(reinterpret_cast<Object*>(*StructurePointer));

		switch (UT(xval->getTag()))
		  {
		  case UT(Object::UVar):
		  case UT(Object::UVarOC):
		    {
		      Object* c = heap.newDouble(n);
		      bindAndTrail(xval, c);
		      break;
		    }
		  case UT(Object::UNumber):
		    if (!xval->isDouble() || xval->getDouble() != n) BACKTRACK;
		    break;
		  case UT(Object::UAtom):
		  case UT(Object::UString):
		  case UT(Object::UStruct):
		  case UT(Object::UCons):
		    BACKTRACK;
		    break;
		  case UT(Object::UOther):
		    {
		      Object* c = heap.newDouble(n);
		      if (!unifyOtherConst(xval, c, true)) BACKTRACK;
		      break;
		    }
		  default:
		    assert(false);
		    break;
		  }
		StructurePointer++;
	      }
	    else
	      {
		Object* c = heap.newDouble(n);
		*StructurePointer = reinterpret_cast<heapobject>(c);
		StructurePointer++;
	      }
	  }
	  VMBREAK;

	case OPCODE(PUT_STRING, ARGS(register)):
	  {
	    const word32 i = getRegister(PC);
	    char* c = (char*)PC;
	    int size = strlen(c);
	    
	    Object* str = heap.newStringObject(c);
	    PC += size+1;

	    X[i]= str;
	  }
	  VMBREAK;

	case OPCODE(GET_STRING, ARGS(register)):
	  {
	    const word32 i = getRegister(PC);
	    char* c = (char*)PC;
	    int size = strlen(c);
	    
	    Object* str = heap.newStringObject(c);
	    PC += size+1;

	    if (!unify(X[i], str))
	      BACKTRACK;

	    VMBREAK;
	  }
 
	case OPCODE(SET_STRING, ARGS()):
	  {
	    char* c = (char*)PC;
	    int size = strlen(c);
	    
	    Object* str = heap.newStringObject(c);
	    PC += size+1;

	    *StructurePointer = reinterpret_cast<heapobject>(str); 
	    StructurePointer++;
	  }
	  VMBREAK; 


	case OPCODE(UNIFY_STRING, ARGS()):
	  {
	    char* c = (char*)PC;
	    int size = strlen(c);
	    
	    Object* str = heap.newStringObject(c);
	    PC += size+1;

	    if (ReadMode)
	      {
		Object* xval = heap.dereference(reinterpret_cast<Object*>(*StructurePointer));
		if (!unify(str, xval))
		  BACKTRACK;

		StructurePointer++;
	      }
	    else
	      {
		*StructurePointer = reinterpret_cast<heapobject>(str);
		StructurePointer++;
	      }
	  }
	  VMBREAK;

	default:
#ifdef WIN32
          TerminateProcess(GetCurrentProcess(),SIGILL);
#else
          (void)(kill(getpid(), SIGILL));
#endif
          VMBREAK;
	}
#ifndef NDEBUG
      trace.TraceInstr(*this, *atoms, *code,
		       *predicates, trace_pc);
      trace.TraceEnd(*this);
#endif
    }

  programCounter = PC;
  return RV_EXIT;
}

