// objvar.cc - Object variable manipulations.
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
// $Id: object_variable.cc,v 1.5 2006/01/31 23:17:51 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;

//
// psi_object_variable(term)
// Succeeds if term is an object variable.
// mode(in)
//
Thread::ReturnValue
Thread::psi_object_variable(Object *& object)
{
  assert(object->hasLegalSub());
  PrologValue pval(object);

  heap.prologValueDereference(pval);

  return BOOL_TO_RV(pval.getTerm()->isObjectVariable());
}

//
// psi_local_object_variable(term)
// Succeeds if X0 is a local object variable.
// mode(in)
//
Thread::ReturnValue
Thread::psi_local_object_variable(Object *& object)
{
  assert(object->variableDereference()->hasLegalSub());
  Object* term = heap.dereference(object);

  return BOOL_TO_RV(term->isLocalObjectVariable());
}

//
// psi_new_ObjectVariable(variable)
// Return a new object variable.
// mode(out)
//
Thread::ReturnValue
Thread::psi_new_object_variable(Object *& object)
{
  object = heap.newObjectVariable();

  return RV_SUCCESS;
}

//
// psi_is_distinct(ObjectVariable1, ObjectVariable2)
// Succeeds iff ObjectVariable1 and ObjectVariable2 are distinct object vars
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_is_distinct(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  return BOOL_TO_RV(val1->isObjectVariable() &&
		    val2->isObjectVariable() &&
		    val1->distinctFrom(val2));
}

//
// psi_get_distinct(ObjectVariable, variable)
// Retrieve the distinctness information under ObjectVariable.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_get_distinct(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  if (! val1->isObjectVariable())
    {
      return RV_FAIL;
    }
  else
    {
      assert(val1->isObjectVariable());

      ObjectVariable *object_variable =
	OBJECT_CAST(ObjectVariable *, val1);

      object2 = object_variable->getDistinctness();

      return RV_SUCCESS;
    }
}

static inline bool
object_variable_suffix_char(char c)
{
  return ('0' <= c && c <= '9') || c == '_';
}

//
// psi_object_variable_name_to_prefix(atom, atom)
// Strip off an object variable suffix.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_object_variable_name_to_prefix(Object *& object1,
					   Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  assert(val1->isAtom());

  const char *s = OBJECT_CAST(Atom*, val1)->getName();

  int i;

  if (strlen(s) ==  0)    // The empty atom
    {
      return RV_FAIL;
    }

  // Search backwards for first non-suffix character
  for (i = static_cast<int>(strlen(s) - 1);
       i >= 0 && object_variable_suffix_char(s[i]);
       i--)
    ;

  if (i < 0) 
    {
      return RV_FAIL;
    } 
  else if (s[i] < 'a' || s[i] > 'z') 
    {
      return RV_FAIL;
    } 
  else 
    {
      if (s[0] == '_') 
	{
	  strncpy(atom_buf1, s+1, i);
	  atom_buf1[i] = '\0';
	} 
      else 
	{
	  strncpy(atom_buf1, s, i+1);
	  atom_buf1[i+1] = '\0';
	}
      
      object2 = atoms->add(atom_buf1);
      
      return RV_SUCCESS;
    }
}

//
// psi_valid_object_variable_prefix(atom)
// Returns true if the atom is a valid ObjectVariable prefix.
// mode(in)
//
Thread::ReturnValue
Thread::psi_valid_object_variable_prefix(Object *& object1)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
 
  assert(val1->isAtom());
  
  const char *s = OBJECT_CAST(Atom*, val1)->getName();

  size_t i;

  for (i = strlen(s); i > 0 && 'a' <= s[i-1] && s[i-1] <= 'z'; i--)
    ;
  
  return BOOL_TO_RV(i == 0);
}


















