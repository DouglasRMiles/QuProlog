// foreign_handle.h - Incremental loading of foreign language functions.
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
// $Id: foreign_handle.h,v 1.2 2005/03/08 00:35:05 qp Exp $

#ifndef	FOREIGN_HANDLE_H
#define	FOREIGN_HANDLE_H

#ifndef WIN32
#include <dlfcn.h>
#endif

class	Handle
{
private:
  void	*handle;
  Handle	*next;

public:
  
  Handle(void *h, Handle *n)
    {
      handle = h;
      next = n;
    }
#if(!defined(WIN32))
  ~Handle(void)         { dlclose(handle); }
#else
   // Windows thing
   ~Handle(void) { FreeLibrary((HMODULE)handle); }
#endif
  
  //
  // Return the handle.
  //
  void	*file(void)	{ return(handle); }
  
};

#endif	// FOREIGN_HANDLE_H

