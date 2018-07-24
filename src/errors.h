// errors.h - Error messages handlers.
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
// $Id: errors.h,v 1.5 2005/03/08 00:35:05 qp Exp $

#ifndef	ERRORS_H
#define	ERRORS_H

#include <errno.h>
//#include <pthread.h>
#include <stdio.h>
#include <string.h>

#include "area_offsets.h"
#include "defs.h"

// Optimisations for functions which do not return.  This will
// necessarily vary from compiler to compiler.
 
#ifdef __GNUC__
#define NO_RETURN __attribute__ ((noreturn))
#else
#define NO_RETURN
#endif // __GNUC__

//
// Remember the name of the overflow area.
//
extern	const char	*ErrArea;

//
// General error message handlers.
//

//
// Just print out the message and continue the execution.
//

void Warning(const char *where, const char *message);
void WarningS(const char *where, const char *message, 
	      const char *extra_message);
//
// Print out the message and exit with an error code.
//
//
// Print out the message and exit with an error code.
//
extern  void    Fatal(const char *where,
                      const char *message) NO_RETURN;

extern  void    FatalS(const char *where,
		       const char *message,
		       const char *extra_message) NO_RETURN;

//
// Print out the usage message.
//
extern void Usage(const char *program,
		  const char *usage) NO_RETURN;

//
// Commonly used error message handlers.
//

//
// Fatal ones:
//
extern	void	SegmentTooLarge(const char *where,
				const char *which
				) NO_RETURN;
extern	void	OutOfPage(const char *where,
			  const char *which,
			  const word32 size) NO_RETURN;
extern	void	OutOfHashTable(const char *where,
			       const char *which,
			       const word32 size) NO_RETURN;
extern	void	EmptyStack(const char *where,
			   const char *which
			   ) NO_RETURN;
extern	void	BadReset(const char *where,
			 const char *which,
			 const StackLoc loc) NO_RETURN;
extern	void	BadReference(const char *where,
			     const char *which,
			     const StackLoc loc) NO_RETURN;
extern	void	WrongFileFormat(const char *where,
				const char *which
				) NO_RETURN;
extern	void	SaveFailure(const char *where,
			    const char *name,
			    const char *which = NULL) NO_RETURN;
extern	void	ReadFailure(const char *where,
			    const char *name,
			    const char *which = NULL) NO_RETURN;

extern void OutOfHeapSpace(const char *where, char *which,
                    const word32 size) NO_RETURN;

//
// A system call that indicates failure by returning a non-0 value.
// In this case, the error is indicated by the return value.
//
#define SYSTEM_CALL_NON_ZERO(f)				               \
do {							               \
  const int result = (f);				               \
  if (result != 0)					               \
    {                                                                  \
      FatalS(#f, " failed: ", strerror(result));  	       \
    }							               \
} while (0)

//
// A system call that indicates an error by returning a value less than zero.
// In this case, the error is indicated by the value in errno.
//
#define SYSTEM_CALL_LESS_ZERO(f)					\
do {									\
  if ((f) < 0)								\
    {									\
      perror(__FUNCTION__);						\
      Fatal(#f, " failed");	                                \
    }									\
} while (0)

//
// A system call that indicates failure by returning a non-0 value,
// but also has an error value that indicates that the operation failed
// for some reason that isn't catastrophic, e.g. a timeout or some such
// (c.f. pthread_mutex_trylock(), pthread_cond_timedwait()).
// 
// This macro returns from the calling function. It's mainly intended
// to be used in wrapper functions.
//
#define SYSTEM_CALL_NON_ZERO_RETURN_BOOL(f, val)			\
do {									\
  const int result = (f);						\
  if (result == 0)							\
    {									\
      return true;							\
    }									\
  else if (result == val)						\
    {									\
      return false;							\
    }									\
  else									\
    {									\
      FatalS(#f,  " failed: ", strerror(result)); \
      return false;							\
    }									\
} while (0)

#endif	// ERRORS_H
