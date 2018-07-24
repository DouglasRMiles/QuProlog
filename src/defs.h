// defs.h - a collection of useful declarations.
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
// $Id: defs.h,v 1.10 2006/01/31 23:17:49 qp Exp $

#ifndef	DEFS_H
#define	DEFS_H

#include <limits.h>
#include <sys/types.h>
#include <string.h>

// Automatically generated stuff.
#include "config.h"

#include "debug.h"

#ifdef WIN32
typedef unsigned char u_char;
typedef unsigned long u_long;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef char                    int8;
typedef u_char                  word8;
typedef short           int16;
typedef unsigned short  word16;
typedef int             int32;
typedef unsigned int    word32;
typedef unsigned long         	wordlong;
typedef unsigned long         	wordptr;
typedef wordptr                 heapobject;
typedef word8 	*CodeLoc;
#else

typedef char			int8;
typedef u_char			word8;
typedef SHORT_TYPE		int16;
typedef unsigned SHORT_TYPE	word16;
typedef INT_TYPE		int32;
typedef unsigned INT_TYPE	word32;
typedef unsigned long         	wordlong;
typedef unsigned long         	wordptr;
typedef wordptr                 heapobject;
typedef word8 	*CodeLoc;
#endif
//
// Define a K.
//
const	word32	K			= 1024;


const	word32	NUMBER_X_REGISTERS	= 20;

const	word32	PILE_SIZE		= 1;

const word32 WORD32_MAX	= (word32) -1;
const wordptr WORDPTR_MAX = (wordptr) -1L;

const word32 NULL_LOC	= 0;
const word32 EMPTY_LOC	= WORD32_MAX;

//
// Default maximum number of threads.
//
const word32 THREAD_TABLE_SIZE = 100;

const word32 ATOM_LENGTH = 512;
const word32 IO_BUF_LENGTH = 2048;
const word32 NUMBER_OF_BUFFERS = 200;

const word32 ARITY_MAX = 255;

const word32 THREAD_MAX = 100;

const word32 NUM_OPEN_STREAMS = 100;

const word32 NUM_OPEN_SOCKETS = 20;

typedef void (*void_fn_ptr)(void);

// Maximum length of a TCP message.
const word32 TCP_BUF_LEN = 2048;

//
// Maximum arity of a pseudo-instruction.
//
const word32 PSI_ARITY_MAX = 5;

//
// Number representing ``no port''.
//
const u_short PORT_NONE = 0;

//
// String equality.
//
inline bool streq(const char *x, const char *y)
{
  assert(x != NULL && y != NULL);
  return strcmp(x, y) == 0;
}

inline bool streqn(const char *x, const char *y, const size_t len)
{
  assert(x != NULL && y != NULL);
  return strncmp(x, y, len) == 0;
}


enum IOType {
  ISTREAM,
  OSTREAM,
  ISTRSTREAM,
  OSTRSTREAM,
  IFDSTREAM,
  OFDSTREAM,
  IMSTREAM,
  OMSTREAM,
  QPSOCKET
};

enum IODirection {
  INPUT,
  OUTPUT,
  INPUT_OUTPUT
};


#endif	// DEFS_H




