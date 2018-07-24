// varname.cc - Get and set variable names.
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
// $Id: varname.cc,v 1.8 2006/03/30 22:50:31 qp Exp $

#include <iostream>
#include <sstream>

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;

//
// Name(get) unnamed vars in sub adding these vars to varlist.
// If do_name is true then unnamed vars are given names.
// If get_vars is true then unnamed vars are collected into varlist.
//

void
Thread::name_term_vars_sub(Object* sub, Object*& varlist, 
			   bool do_name, bool get_vars)
{
  assert(sub->isNil() || (sub->isCons() && OBJECT_CAST(Cons*, sub)->isSubstitutionBlockList()));

  for (;sub->isCons();sub = OBJECT_CAST(Cons*, sub)->getTail() )
    {
      assert(OBJECT_CAST(Cons*, sub)->getHead()->isSubstitutionBlock());
      SubstitutionBlock* subblock 
	= OBJECT_CAST(SubstitutionBlock*, OBJECT_CAST(Cons*, sub)->getHead());
      
      for (size_t i = 1; i <= subblock->getSize(); i++)
        {
	  name_term_vars(subblock->getRange(i), varlist, 
			 do_name, get_vars);
          name_term_vars(subblock->getDomain(i), varlist,
			 do_name, get_vars);
	}
    }
  return;
}

//
// Name(get) unnamed vars in term adding these vars to varlist.
// If do_name is true then unnamed vars are given names.
// If get_vars is true then unnamed vars are collected into varlist.
//

void
Thread::name_term_vars(Object* term, Object*& varlist, 
		       bool do_name, bool get_vars)
{
  assert(term->variableDereference()->hasLegalSub());
  term = heap.dereference(term);
  switch (term->tTag())
    {
    case Object::tVar:
      if (OBJECT_CAST(Reference*, term)->getName() == NULL)
	{
	  if (get_vars)
            {
	      Cons* temp = heap.newCons(term, varlist);
	      varlist = temp;
	    }
	  if (do_name)
	    {
	      Atom* name = GenerateVarName(this, metaCounter);
              term = addExtraInfo(OBJECT_CAST(Variable*, term));
	      names.setNameOldVar(name, term, *this);
	    }
	}
      break;

    case Object::tObjVar:
      if (!term->isLocalObjectVariable() &&
	  OBJECT_CAST(Reference*, term)->getName() == NULL)
	{
	  if (get_vars)
            {
	      Cons* temp = heap.newCons(term, varlist);
	      varlist = temp;
	    }
	  if (do_name)
	    {
	      Atom* name = GenerateRObjectVariableName(this, objectCounter);
	      names.setNameOldVar(name, term, *this);
	    }
	}
      break;

    case Object::tCons:
      {
	Object* list = term;
	for (; list->isCons();
	     list = heap.dereference(OBJECT_CAST(Cons*, list)->getTail()))
	  {
	    name_term_vars(OBJECT_CAST(Cons*, list)->getHead(), 
			   varlist, do_name, get_vars);
	  }
	if (!list->isConstant())
	  {
	    name_term_vars(list, varlist, do_name, get_vars);
	  }
      }
      break;

    case Object::tStruct:
      {
	Structure* str = OBJECT_CAST(Structure*, term);
	if (!str->getFunctor()->isConstant())
	  {
	    name_term_vars(str->getFunctor(), varlist, 
			   do_name, get_vars);
	  }

	for (size_t i = 1; i <= str->getArity(); i++)
	  {
	    name_term_vars(str->getArgument(i), varlist, 
			   do_name, get_vars);
	  }
      }
      break;

    case Object::tQuant:
      {
	QuantifiedTerm* quant = OBJECT_CAST(QuantifiedTerm*, term);
	if (!quant->getQuantifier()->isConstant())
	  {
	    name_term_vars(quant->getQuantifier(), varlist, 
			   do_name, get_vars);
	  }
	name_term_vars(quant->getBoundVars(), varlist, 
		       do_name, get_vars);
	name_term_vars(quant->getBody(), varlist, do_name, get_vars);
      }
      break;

    case Object::tShort:
    case Object::tLong:
    case Object::tDouble:
    case Object::tAtom:
    case Object::tString:
      break;

    case Object::tSubst:
      name_term_vars_sub(OBJECT_CAST(Substitution*, 
				     term)->getSubstitutionBlockList(), 
			 varlist, do_name, get_vars);
      name_term_vars(OBJECT_CAST(Substitution*, term)->getTerm(), 
		     varlist, do_name, get_vars);
      break;
      
    default:
      assert(false);
      break;
    }
}


//
// psi_get_var_name(variable, name)
// Return the name of the variable if there is one. Otherwise, fail.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_get_var_name(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);

  if (! val1->isAnyVariable())
    {
      return(RV_FAIL);
    }
  else
    {
      Reference* var = OBJECT_CAST(Reference*, val1);
      Object* name = var->getName();

      if (name == NULL)
	{
	  return(RV_FAIL);
	}
      else
	{
	  object2 = name;
	  return(RV_SUCCESS);
	}
    }
}

//
// psi_set_var_name(var, name)
// Set the name for the given variable using the supplied name as the
// prefix.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_set_var_name(Object *& object1, Object *& object2)
{
  int32 counter = 0;

  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  if (!val1->isVariable())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!val2->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  Variable* var = OBJECT_CAST(Variable*, val1);
  if (var->getName() != NULL)
    {
      return(RV_FAIL);
    }
  //
  // else no name
  //
  var = addExtraInfo(var);
   
  //
  // Generate the variable name for the variable.
  //

  //
  // first char of name should be in A..Z
  //
  char* str = OBJECT_CAST(Atom*, val2)->getName();
  if (*str < 'A' || *str > 'Z')
    {
      return(RV_SUCCESS); //PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  //
  // Find a suitable suffix.
  //
  AtomLoc name_loc;
  ostringstream strm;
  string strm_string;
  do
    {
      strm.str("");
      strm << OBJECT_CAST(Atom*, val2)->getName();
      strm << counter;
  //    strm << ends;
      counter++;
      strm_string = strm.str();
      name_loc = atoms->lookUp(strm_string.c_str());
    } while (name_loc != EMPTY_LOC && 
	     names.getVariable(atoms->getAtom(name_loc)) != NULL);

  //
  // Add to the tables.
  //
  Atom* name = atoms->add(strm_string.c_str());
  names.setNameOldVar(name, var, *this);

  return(RV_SUCCESS);
}

//
// psi_set_ObjectVariable_name(objvar, name)
// Set the name for the given object variable using the supplied name as the
// prefix.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_set_object_variable_name(Object *& object1, Object *& object2)
{

  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  if (val1->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!val1->isObjectVariable())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!val2->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  ObjectVariable* var = OBJECT_CAST(ObjectVariable*, val1);
  if (var->getName() != NULL)
    {
      return(RV_FAIL);
    }
  //
  // else no name
  //
  ObjectVariable* newvar = heap.newObjectVariable();
  
  //
  // Generate the variable name for the object variable.
  //
  
  //
  // Find a suitable suffix.
  //
  AtomLoc name_loc;
  ostringstream strm;
  string strm_string;
  do
    {
      strm.str("");
      strm << OBJECT_CAST(Atom*, val2)->getName();
      strm << objectCounter;
      //strm << ends;
      objectCounter++;
      strm_string = strm.str();
      name_loc = atoms->lookUp(strm_string.c_str());
    } while (name_loc != EMPTY_LOC && 
	     names.getVariable(atoms->getAtom(name_loc)) != NULL);

  //
  // Add to the tables.
  //
  Atom* name = atoms->add(strm_string.c_str());

  names.setNameOldVar(name, newvar, *this);
  bindObjectVariables(var, newvar);

  return(RV_SUCCESS);
}

//
// psi_get_unnamed_vars(term,varlist)
// Get all unnamed (ob)vars in term - return them in varlist.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_get_unnamed_vars(Object *& object1, Object *& object2)
{
  Object* varlist = AtomTable::nil;

  name_term_vars(object1, varlist, false, true);

  object2 = varlist;

  return(RV_SUCCESS);
}
//
//
// psi_name_vars(term,varlist)
// Name all unnamed (ob)vars in term - return them in varlist.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_name_vars(Object *& object1, Object *& object2)
{
  Object* varlist = AtomTable::nil;

  name_term_vars(object1, varlist, true, true);

  object2 = varlist;

  return(RV_SUCCESS);
}
//
// psi_name_vars(term)
// Name all unnamed (ob)vars in term.
// mode(in)
//
Thread::ReturnValue
Thread::psi_name_vars(Object *& object1)
{
  Object* varlist = AtomTable::nil;

  name_term_vars(object1, varlist, true, false);

  return(RV_SUCCESS);
}





