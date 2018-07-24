// gc_escapes.h - Garbage collector for threads.
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
// $Id: gc_escapes.h,v 1.5 2005/03/08 00:35:06 qp Exp $

#ifndef	GC_ESCAPES_H
#define	GC_ESCAPES_H

public: 

#ifdef QP_DEBUG
bool check_env(EnvLoc env);

bool check_choice(ChoiceLoc choiceloc);

bool check_trail();

bool check_ips();

bool check_name();

bool check_heap2(Heap& heap);

//
// Check heap for correct pointers
//
bool check_heap(Heap&, AtomTable*, GCBits&);
#endif // DEBUG

// Mark the registers

void gc_mark_registers(word32);

// Mark the environmants
void gc_mark_environments(EnvLoc);

// Mark the choicepoints
void gc_mark_choicepoints(ChoiceLoc);

// Mark the trail
void gc_mark_trail();

// Mark the implicit parameters
void gc_mark_ips();

// Mark the variable names
void gc_mark_names();

// Mark the heap

void gc_marking_phase(word32);

void gc_sweep_registers(word32);

void gc_sweep_trail(void);

void gc_sweep_names(void);

void gc_sweep_ips(void);

void gc_sweep_environments(EnvLoc);

void gc_sweep_choicepoints(ChoiceLoc);

void gc_compaction_phase(word32);


// Do garbage collection

bool gc(word32);

// Trigger garbage collection

ReturnValue psi_gc(void);

ReturnValue psi_suspend_gc(void);
ReturnValue psi_unsuspend_gc(void);

#ifdef QP_DEBUG
void dump_choices(ChoiceLoc);

void dump_areas(word32);

#endif // QP_DEBUG

#endif	// GC_ESCAPES_H
