// process.cc - Pseudo-instructions for handling the process attributes 
// associated with a QuProlog invocation.
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
// $Id: process.cc,v 1.3 2005/03/08 00:35:12 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;
extern char *process_symbol;

#ifdef WIN32
#define _WINSOCKAPI_
#include <windows.h>
#endif

// @doc
// @pred process_pid(ProcessID)
// @mode process_pid(-) is det
// @type process_pid(process_id)
// @description
// Return the process-id of the current process.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_process_pid(Object *& pid_arg)
{
#ifdef WIN32
  pid_arg = heap.newInteger(reinterpret_cast<qint64>(GetCurrentProcess()));
#else 
  pid_arg = heap.newInteger(getpid());
#endif
  return RV_SUCCESS;
}

// @doc
// @pred process_symbol(Name)
// @mode process_symbol(-) is det
// @type process_symbol(atom)
// @description
// Return the symbolic name of this process.
// @end pred
// @end doc
Thread::ReturnValue
Thread::psi_process_symbol(Object *& name_cell)
{
  if (process_symbol == NULL)
    {
      return RV_FAIL;
    }
  else
    {
      name_cell = atoms->add(process_symbol);
      return RV_SUCCESS;
    }
}

