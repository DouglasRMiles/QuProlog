// defaults.h - Global default size constants for
//		all the C++ components of the QP
//		suite. #include this file whenever
//		global default values are needed.
//		This should only be necessary when
//		command line arguments are being
//		processed.
//		Otherwise, extract the correct value
//		from the *_options object.
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
// $Id: defaults.h,v 1.5 2001/12/17 04:27:32 qp Exp $

#ifndef DEFAULTS_H
#define DEFAULTS_H

#include <sys/types.h>

#include "defs.h"
#include "tcp_qp.h"

//
// Default size in K for different global areas.
//
// SIZE_MULTIPLIER is used to double all sizes for 64-bit systems.
const word32 SIZE_MULTIPLIER = (sizeof(void *) / sizeof(word32));
const word32 CODE_SIZE = 400 * SIZE_MULTIPLIER;
const word32 STRING_TABLE_SIZE = 64;

//
// Default size in entries for different global hash tables.
//
const word32 PREDICATE_TABLE_SIZE  = 10009;
const word32 ATOM_TABLE_SIZE  = 10009;

//
// Default size for different areas local to each thread.
//
const word32 NAME_TABLE_SIZE  = 10000;
const word32 HEAP_SIZE  = 400;			// K
const word32 ENVIRONMENT_STACK_SIZE = 64;	// K
const word32 CHOICE_STACK_SIZE  = 64;		// K
const word32 BINDING_TRAIL_SIZE  = 32;	       	// K
const word32 OTHER_TRAIL_SIZE = 32;		// K
const word32 SCRATCHPAD_SIZE = 100;             // K
const word32 IP_TABLE_SIZE = 10000;                 

//
// Default size in K for area used in linking.
//
const word32 STRING_MAP_SIZE  = 64;
//
// Default size in K entries for the record database reference table.
//
const word32 RECORD_DB_SIZE  = 64;

//
// Default qx file.
//
char *QX_FILE = NULL;

//
// Default stand alone setting. If true, qem won't try to register itself
// with the nameserver. Otherwise, it will.
//
const bool STAND_ALONE = false;


//
// Default nameserver port.
//
const u_short PEDRO_PORT = 4550;

//
// Default process symbol.
//
char *PROCESS_SYMBOL = NULL;


//
// Default initial goal
//
char* INITIAL_GOAL = NULL;

//
// Default initial file
//
char* INITIAL_FILE = NULL;

//
// Default debugging value.
//
const bool DEBUGGING = false;

#endif // DEFAULTS_H

