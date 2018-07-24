// env_var.cc - Interface to environment variables.
//		The name is env_var.cc to avoid clashes with other
//		files that are related to environments.
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
// $Id: env_var.cc,v 1.3 2002/11/08 00:44:15 qp Exp $

#include <stdlib.h>

#include "config.h"

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;

Thread::ReturnValue
Thread::psi_env_getenv(Object *& name_arg, Object *& value_arg)
{
  Object* name = heap.dereference(name_arg);

  if (name->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!name->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  const char *env_value = getenv(OBJECT_CAST(Atom*, name)->getName());
  if (env_value == NULL)
    {
      return RV_FAIL;
    }

  value_arg = atoms->add(env_value);

  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_env_putenv(
	       Object *& name_arg,
	       Object *& value_arg)
{
  Object* name = heap.dereference(name_arg);
  Object* value = heap.dereference(value_arg);

  if (name->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!name->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  if (value->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!value->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  const char *name_string = OBJECT_CAST(Atom*, name)->getName();
  const char *value_string = OBJECT_CAST(Atom*, value)->getName();

  const size_t name_string_len = strlen(name_string);
  const size_t value_string_len = strlen(value_string);

  // The string containing the environment entry has to look like
  // name=value, so we need two extra bytes, one for the '=' and one
  // for the terminating null.
  const size_t total_len = name_string_len + value_string_len + 2;

  char *env_entry_string = new char[total_len];

  (void) strcpy(env_entry_string, name_string);
  (void) strcat(env_entry_string, "=");
  (void) strcat(env_entry_string, value_string);
	 
  const int result = putenv(env_entry_string);

  return result == 0 ? RV_SUCCESS : RV_FAIL;
}








