// pseudo_instr_defs.h -
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
// $Id: pseudo_instr_defs.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef PSEUDO_INSTR_DEFS_H
#define PSEUDO_INSTR_DEFS_H

//
// Type definitions for the data used to represent pseudo instructions
//
struct pseudo_instr0_data {
  ReturnValue (*funct)(void); // pointer to function
    int32	mode;			 // bit representation of mode of args
    char *name;			// Used by QuAM tracer
};

struct pseudo_instr1_data {
  ReturnValue (*funct)(Object*&); // pointer to function
  int32	mode;			// bit representation of mode of args
  char *name;			// Used by QuAM tracer
};
  
struct pseudo_instr2_data {
  ReturnValue (*funct)(Object*&, Object*&);
  int32	mode;
  char *name;			// Used by QuAM tracer
};
  
struct pseudo_instr3_data {
  ReturnValue (*funct)(Object*&, Object*&, Object*&);
  int32	mode;
  char *name;			// Used by QuAM tracer
};
  
struct pseudo_instr4_data {
  ReturnValue (*funct)(Object*&, Object*&, Object*&, Object*&);
  int32	mode;
  char *name;			// Used by QuAM tracer
};
  
struct pseudo_instr5_data {
  ReturnValue (*funct)(Object*&, Object*&, Object*&, Object*&, Object*&);
  int32 mode;
  char *name;
};

extern pseudo_instr0_data pseudo_instr0_array[];
extern pseudo_instr1_data pseudo_instr1_array[];
extern pseudo_instr2_data pseudo_instr2_array[];
extern pseudo_instr3_data pseudo_instr3_array[];
extern pseudo_instr4_data pseudo_instr4_array[];
extern pseudo_instr5_data pseudo_instr5_array[];

#endif // PSEUDO_INSTR_DEFS_H
