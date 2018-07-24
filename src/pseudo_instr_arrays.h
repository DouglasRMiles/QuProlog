// pseudo_instr_arrays.h -
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
// $Id: pseudo_instr_arrays.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef PSEUDO_INSTR_ARRAYS_H
#define PSEUDO_INSTR_ARRAYS_H

//
// Type definitions for the data used to represent pseudo instructions
//
struct pseudo_instr0_data {
  Thread::ReturnValue (Thread::*funct)(void); // pointer to function
  int32	mode;			 // bit representation of mode of args
  const char *name;			// Used by QuAM tracer
};

struct pseudo_instr1_data {
  Thread::ReturnValue (Thread::*funct)(Object*&); // pointer to function
  int32	mode;			// bit representation of mode of args
  const char *name;			// Used by QuAM tracer
};
  
struct pseudo_instr2_data {
  Thread::ReturnValue (Thread::*funct)(Object*&, Object*&);
  int32	mode;
  const char *name;			// Used by QuAM tracer
};
  
struct pseudo_instr3_data {
  Thread::ReturnValue (Thread::*funct)(Object*&, Object*&, Object*&);
  int32	mode;
  const char *name;			// Used by QuAM tracer
};
  
struct pseudo_instr4_data {
  Thread::ReturnValue (Thread::*funct)(Object*&, Object*&, Object*&, Object*&);
  int32	mode;
  const char *name;			// Used by QuAM tracer
};
  
struct pseudo_instr5_data {
  Thread::ReturnValue (Thread::*funct)(Object*&, Object*&, Object*&, 
				       Object*&, Object*&);
  int32 mode;
  const char *name;
};

extern pseudo_instr0_data pseudo_instr0_array[];
extern pseudo_instr1_data pseudo_instr1_array[];
extern pseudo_instr2_data pseudo_instr2_array[];
extern pseudo_instr3_data pseudo_instr3_array[];
extern pseudo_instr4_data pseudo_instr4_array[];
extern pseudo_instr5_data pseudo_instr5_array[];

#endif // PSEUDO_INSTR_ARRAYS_H
