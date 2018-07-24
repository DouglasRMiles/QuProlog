// read.cc - Different specialised version of read for variables.
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
// $Id: read.cc,v 1.4 2006/01/31 23:17:51 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;

//
// psi_readR_var(variable, name)
// Return the variable associated with the name.  Otherwise, associate the
// given variable with the name.  No association is made for any name starting
// with '_'.
// mode(out,in)
//
Thread::ReturnValue
Thread::psi_readR_var(Object *& object1, Object *& object2)
{
  Object* val2 = heap.dereference(object2);

  assert(val2->isAtom());
  
  if (*(OBJECT_CAST(Atom*, val2)->getName()) == '_')
    {
      //
      // Do not generate a name.
      //
      object1 =  heap.newVariable();
      return(RV_SUCCESS);
    }

  //
  // Obtain existing variable associates with the name.
  //
  Atom* a = OBJECT_CAST(Atom*, val2);
  Object* v = names.getVariable(a);
  if (v != NULL)
    {
      //
      // Use the existing variable.
      //
      object1 = v;
    }
  else
    {
      //
      // Associated the given variable with the name.
      //
      
      object1 = heap.newVariable(true);
      names.setNameNewVar(a, object1, *this);
    }
  return(RV_SUCCESS);
}

//
// psi_readR_object_variable(variable, name)
// Return the object variable associated with the name.  If none exists,
// create a new object variable and establish the association before returning
// the object variable.  No association is made for any name starting with '_'.
// mode(out,in)
//
Thread::ReturnValue
Thread::psi_readR_object_variable(Object *& object1, Object *& object2)
{
  Object* val2 = heap.dereference(object2);

  assert(val2->isAtom());
  
  //
  // Obtain existing variable associates with the name.
  //
  Object* object_variable = names.getVariable(OBJECT_CAST(Atom*, val2));
  
  if (object_variable == NULL)
    {
      object_variable = heap.newObjectVariable();
      if (*(OBJECT_CAST(Atom*, val2)->getName()) != '_')
	{
	  names.setNameNewVar(OBJECT_CAST(Atom*, val2), 
			      object_variable, *this);
	}
    }
  
  //
  // Return the object variable.
  //
  object1 = object_variable;
  return(RV_SUCCESS);
}



