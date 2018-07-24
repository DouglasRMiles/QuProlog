// thread_escapes.h - Primitives for the support of concurrent execution.
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
// $Id: thread_escapes.h,v 1.4 2002/07/09 02:00:51 qp Exp $

#ifndef	THREAD_ESCAPES_H
#define	THREAD_ESCAPES_H

public:
// @internaldoc
// @pred '$thread_fork'(Name, Goal, RootName, ThreadSizes)
// @mode '$thread_fork'(?, +, +, +) is semidet
// @type '$thread_fork'(atom, goal, atom, ThreadSizes)
// @description
// Create a new thread, with the given goal and whose data areas are the 
// specified sizes.
// If Rootname is not fail then the name generated for the thread
// is based on this name (with an integer extension).
//
// ThreadSizes is a structure:
//   '$thread_sizes'(HeapSize, ScratchpadSize, BindingTrailSize, 
//                   ObjectTrailSize, IPTrailSize, TagTrailSize, 
//                   RefTrailSize, EnvSize, ChoiceSize, NameSize, IPSize)
// where all the sizes are integers and the units they describe can be 
// found in the description of thread_new/3.
//
// The call will fail if a thread cannot be created.
// @end pred
ReturnValue psi_thread_fork(Object *&, Object *&, Object *&, Object *&);

// @doc
// @pred thread_symbol(Thread, Name)
// @mode thread_symbol(+, -) is det
// @type thread_symbol(thread_id, atom)
// @description
// Return the symbolic name of the specified thread.
// @end pred
// @end doc
ReturnValue psi_thread_symbol(Object *&, Object *&);

// @doc
// @pred thread_set_symbol(Name)
// @mode thread_set_symbol(+) is det
// @type thread_set_symbol(atom)
// @description
// Set the symbolic name for this thread to Name.
// @end pred
// @end doc
ReturnValue psi_thread_set_symbol(Object *&);

// @doc
// @pred thread_goal(Goal)
// @mode thread_goal(-) is semidet
// @type thread_goal(gcomp)
// @description
// Get the starting goal of the current thread.
//
// Fails if no starting goal has been specified for the thread.
// @end pred
// @end doc
ReturnValue psi_thread_goal(Object *&);

// @doc
// @pred thread_is_thread(Thread)
// @mode thread_is_thread(+) is semidet
// @type thread_is_thread(thread_id)
// @description
// Succeeds if Thread is a valid thread id and the thread that it refers
// to is an existing thread.
// @end pred
// @end doc
ReturnValue psi_thread_is_thread(Object *&);

// @doc
// @pred thread_is_runnable(Thread)
// @type thread_is_runnable(thread_id)
// @mode thread_is_runnable(+) is semidet
// @description
// Succeeds iff the Thread is runnable.
// @end pred
// @end doc
ReturnValue psi_thread_is_runnable(Object *&);

// @doc
// @pred thread_is_suspended(Thread)
// @mode thread_is_suspended(+) is semidet
// @type thread_is_suspended(thread_id)
// @description
// Succeeds iff the Thread is suspended.
// @end pred
// @end doc
ReturnValue psi_thread_is_suspended(Object *&);

// @doc
// @pred thread_tid(Thread)
// @type thread_tid(thread_id)
// @mode thread_tid(-) is det
// @description
// Thread is the identifier of the current thread.
// @end pred
// @end doc
ReturnValue psi_thread_tid(Object *&);

// @internaldoc
// @pred '$thread_exit'(Code)
// @mode '$thread_exit'(+) is no-return
// @type '$thread_exit'(integer)
// @description
// End execution of the current thread.
// @end pred
// @end internaldoc
ReturnValue psi_thread_exit(void);

// @internaldoc
// @pred signal_thread_exit
// @mode signal_thread_exit is no-return
// @type signal_thread_exit
// @description
// End execution of the signal processing thread.
// @end pred
// @end internaldoc
ReturnValue psi_signal_thread_exit(void);

// @doc
// @pred thread_suspend(Thread)
// @mode thread_suspend(+) is det
// @type thread_suspend(thread_id)
// @description
// Remove the specified thread from the runnable queue and place it on the
// suspended queue
//
// A suspended thread needs to be explicitly resumed in order to run again.
// @end pred
// @end doc
ReturnValue psi_thread_suspend(Object *&);

// @doc
// @pred thread_resume(Thread)
// @mode thread_resume(+) is det
// @type thread_resume(thread_id)
// @description
// Resume the specified thread.
// @end pred
// @end doc
ReturnValue psi_thread_resume(Object *&);

ReturnValue psi_thread_wait_timeout(Object *&);

// @internaldoc
// @pred '$thread_defaults'(ThreadSizes)
// @mode '$thread_defaults'(-) is det
// @type '$thread_defaults'(ThreadSizes)
// @description
// Get the current default sizes for the data areas of a newly created thread.
//
// ThreadSizes is described in '$thread_new'/3.
//
// Implemented directly by pseudo-instruction.
// @end pred
// @end doc


ReturnValue psi_thread_setup_wait(Object *&, Object *&, Object *&, Object *&);
ReturnValue psi_thread_wait_free_ptr(Object *&);
ReturnValue psi_thread_wait_ptr(Object *&);
ReturnValue psi_thread_wait_update(Object *&);
ReturnValue psi_thread_wait_extract_preds(Object *&, Object *&);

ReturnValue psi_thread_defaults(Object *&);

// @internaldoc
// @pred '$thread_set_defaults'(ThreadSizes)
// @mode '$thread_set_defaults'(+) is det
// @type '$thread_set_defaults'(thread_sizes)
// @description
// Set the default sizes for the code areas of a newly created thread.
//
// ThreadSizes is described in '$thread_new'/3.
//
// Implemented direcly by pseudo-instruction.
// @end pred
// @end internaldoc
ReturnValue psi_thread_set_defaults(Object *&);

// @user
// @pred thread_errno(Errno)
// @type thread_errno(integer)
// @mode thread_errno(-) is det
// @description
// Returns the current errno for this thread.
// @internal
// Implemented directly by pseduo-instruction.
// @end pred
// @end user
ReturnValue psi_thread_errno(Object *&);

// Gives up the processor.
ReturnValue psi_thread_yield(void);

// Tells whether the executing thread is an intial thread.
ReturnValue psi_thread_is_initial_thread(void);

//
// Get the list of current thread ID's.
// mode (out)
//
ReturnValue psi_current_threads(Object*&);

// @doc
// @pred threadID_goal(ThreadID, Goal)
// @mode threadID_goal(+, -) is semidet
// @type threadID_goal(thread, gcomp)
// @description
// Get the starting goal of the current thread.
//
// The initial thread returns the atom initial.
// A thread without a goal returns the atom none.
// @end pred
// @end doc
ReturnValue psi_threadID_goal(Object*& , Object *& );  

// @doc
// @pred thread_exit(Thread)
// @mode thread_exit(+) is det
// @description
// Exit the given thread.
// @end pred
// @end doc
ReturnValue psi_thread_exit(Object *&);

// @doc
// @pred thread_throw(Thread, ThrowPattern)
// @type thread_throw(thread, term)
// @mode thread_throw(+, +) is semidet
// @description
// Throw the pattern in the thread.
//
// @end pred
// @end doc
ReturnValue psi_thread_throw(Object *&, Object *&);

// @doc
// @pred thread_push_goal(Thread, Goal)
// @type thread_push_goal(thread, term)
// @mode thread_push_goal(+, +) is semidet
// @description
// Push call(Goal) to the front of the current goal conjunct of
// the given thread.
//
// @end pred
// @end doc
ReturnValue psi_thread_push_goal(Object *&, Object *&);

ReturnValue psi_gettimeofday(Object *&);

ReturnValue psi_schedule_threads_now(Object *&);


#endif	// THREAD_ESCAPES_H
