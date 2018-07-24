// errors.cc - Error messages handlers.
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
// $Id: errors.cc,v 1.6 2005/03/08 00:35:04 qp Exp $

#include <iostream>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>
#ifdef WIN32
#include <io.h>
#define _WINSOCKAPI_
#include <windows.h>
#define getpid() GetCurrentProcess()
#else
#include <unistd.h>
#endif
#include <stdio.h>

#include "config.h"

#include "area_offsets.h"
#include "defs.h"

using namespace std;

extern const char *Program;

//
// Remember AreaName.
//
const	char    *ErrArea = NULL;

//
// General error message handlers.
//

void
Fatal(const char *where, const char *message)
{
   cerr << Program << "(" << (long)(getpid()) << ") : " 
	<< where << ": Fatal : " << message << endl;
   exit(EXIT_FAILURE);
}

void
FatalS(const char *where, const char *message, const char *extra_message)
{
   cerr << Program << "(" << (long)(getpid()) << ") : " 
	<< where << ": Fatal : " << message
	<< " : " << extra_message << endl;
   exit(EXIT_FAILURE);
}

void
Warning(const char *where, const char *message)
{
   cerr << Program << "(" << (long)(getpid()) << ") : " 
	<< where << ": Warning : " << message << endl;
}

void
WarningS(const char *where, const char *message, const char *extra_message)
{
   cerr << Program << "(" << (long)(getpid()) << ") : " 
	<< where << ": Warning : " << message 
	<< " : " << extra_message << endl;
}

//
// Print out usage information and exit with an error code.
//
void
Usage(const char *program, const char *usage)
{
  cerr << "Usage: " << program << " " << usage << endl;

  exit(EXIT_FAILURE);
}

//
// Commonly used error message handlers.
//
void
SegmentTooLarge(const char *where, const char* which)
{
  cerr << Program << "(" << (long)(getpid()) << ") : " << where
       << ": Fatal : too large segment request in " << which;
  cerr << endl;
  exit(EXIT_FAILURE);
}

void
OutOfPage(const char *where, const char *which, const word32 size)
{
  cerr << Program << "(" << (long)(getpid()) << ") : " << where
       << ": Fatal : out of memory in " << which
       << "(" << size << "K)";
  cerr << endl;
  exit(EXIT_FAILURE);
}

void
OutOfHashTable(const char *where, const char *which, const word32 size)
{
  cerr << Program << "(" << (long)(getpid()) << ") : " << where
       << ": Fatal : out of memory in " << which
       << "(" << size << " entries)";
  cerr << endl;
  exit(EXIT_FAILURE);
}

void
EmptyStack(const char *where, const char *which)
{
  cerr << Program << "(" << (long)(getpid()) << ") : " << where
       << ": Fatal : empty stack in " << which;
  cerr << endl;
  exit(EXIT_FAILURE);
}

void
BadReset(const char *where, const char *which, const StackLoc loc)
{
  cerr << Program << "(" << (long)(getpid()) << ") : " << where
       << ": Fatal : bad reset to location " 
       << hex << loc << dec
       << " in " << which;
  cerr << endl;
  exit(EXIT_FAILURE);
}

void
BadReference(const char *where, const char *which, const StackLoc loc)
{
  cerr << Program << "(" << (long)(getpid()) << ") : " << where
       << ": Fatal : bad reference to location " 
       << hex << loc << dec
       << " in " << which;
  cerr << endl;
  exit(EXIT_FAILURE);
}

void
WrongFileFormat(const char *where, const char *which)
{
  cerr << Program << "(" << (long)(getpid()) << ") : " << where
       << ": Fatal : wrong format for file " << which;
  cerr << endl;
  exit(EXIT_FAILURE);
}

void
SaveFailure(const char *where, const char *data, const char *which)
{
  if (which == NULL)
    {
      cerr << Program << "(" << (long)(getpid()) << ") : " << where
	   << ": Fatal : failed to save " << which;
      cerr << endl;
      exit(EXIT_FAILURE);
    }
  else
    {
      cerr << Program << "(" << (long)(getpid()) << ") : " << where
	   << ": Fatal : failed to save " << data << " (" << which << ")";
      cerr << endl;
      exit(EXIT_FAILURE);
    }
}

void
ReadFailure(const char *where, const char *data, const char *which)
{
  if (which == NULL)
    {
      cerr << Program << "(" << (long)(getpid()) << ") : " << where
	   << ": Fatal : failed to read " << which;
      cerr << endl;
      exit(EXIT_FAILURE);
    }
  else
    {
      cerr << Program << "(" << (long)(getpid()) << ") : " << where
	   << ": Fatal : failed to read " << data << " (" << which << ")";
      cerr << endl;
      exit(EXIT_FAILURE);
    }
}
void OutOfHeapSpace(const char *where, char *which, const word32 size)
{
  cerr << Program << "(" << (long)(getpid()) << ") : " << where
       << ": Fatal : out of heap space in  " << which
       << "(" << size << "K)";
  cerr << endl;
  exit(EXIT_FAILURE);
}



