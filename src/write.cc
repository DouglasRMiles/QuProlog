// write.cc - Different specialised versions of write for atoms, integers, and
//	      variables.
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
// $Id: write.cc,v 1.14 2006/03/30 22:50:31 qp Exp $

#include <iostream>
#include <sstream>
#include <string.h>

#include "config.h"

#include "atom_table.h"
#include "is_ready.h"
#include "thread_qp.h"
#include "write_support.h"

extern AtomTable *atoms;
extern IOManager *iom;

//
// Different specialised versions of write for atoms.
//

//
// psi_write_atom(stream, atom)
// Default method for writing atoms->  The string is written without any
// processing.
// mode(in,in)
// 
Thread::ReturnValue
Thread::psi_write_atom(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);
  
  if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if(!val2->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, val1, 1, stream);

  // IS_READY_STREAM(stream, -1);
 
  *stream << OBJECT_CAST(Atom*, val2)->getName();

  return(RV_SUCCESS);
}


void
writeqAtom(const char *s, QPStream *stream)
{
  string atomname(s);
  if (SafeAtom(atomname.c_str(), true))
    {
      *stream << atomname.c_str();
    }
  else
    {
      //
      // The atom is not safe.  Quotes are needed.
      //
      addEscapes(atomname, '\'');
      *stream << '\'';
      *stream << atomname.c_str();
      *stream << '\'';
    }
  return;
}

//
// psi_writeq_atom(stream, atom)
// The string is written with quotes whenever it is needed.  The condition for
// the quotes is when the string consists of characters other than
//	$abcdefghijklmnopqrstuvwxyz_0123456789 .
// mode(in,in)
// 
Thread::ReturnValue
Thread::psi_writeq_atom(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, val1, 1, stream);

  if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if(!val2->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  const char *s = OBJECT_CAST(Atom*, val2)->getName();

  writeqAtom(s, stream);

  return(RV_SUCCESS);
}

//
// psi_write_integer(stream_index, integer)
// Write for integers.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_write_integer(Object *& object1, Object *& object2)
{
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, val1, 1, stream);

  if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!val2->isInteger())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  // IS_READY_STREAM(stream, -1);

  *(stream) << val2->getInteger();

  return(RV_SUCCESS);
}
//
// psi_write_float(stream_index, float)
// Write for floats.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_write_float(Object *& object1, Object *& object2)
{
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, val1, 1, stream);

  if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!val2->isDouble())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  // IS_READY_STREAM(stream, -1);
  double d = val2->getDouble();

  *(stream) << d;

  return(RV_SUCCESS);
}


//
// psi_write_string(stream_index, string)
// Write for strings.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_write_string(Object *& object1, Object *& object2)
{
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, val1, 1, stream);

  if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!val2->isString())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  *(stream) << OBJECT_CAST(StringObject*, val2)->getChars(); 

  return(RV_SUCCESS);
}

Thread::ReturnValue
Thread::psi_writeq_string(Object *& object1, Object *& object2)
{
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);

  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, val1, 1, stream);

  if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!val2->isString())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  string stringchars(OBJECT_CAST(StringObject*, val2)->getChars());
  addEscapes(stringchars, '"');
  *(stream) << "\"";
  *(stream) << stringchars.c_str(); 
  *(stream) << "\"";

  return(RV_SUCCESS);
}

//
// Different specialised versions of write for variables.
//

//
// psi_write_var(stream_index, variable)
// Default method for writing variables.  If the variable has a name, use the
// name.  Otherwise, the location of the variable is written as a base 16
// number with '_' preceding it.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_write_var(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  assert(object2->hasLegalSub());
  PrologValue pval2(object2);
  heap.prologValueDereference(pval2);

  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, val1, 1, stream);

  if (pval2.getTerm()->isVariable() && 
      pval2.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, pval2);
    }  
  if (!pval2.getTerm()->isVariable() ||
      !pval2.getSubstitutionBlockList()->isNil())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }

  // IS_READY_STREAM(stream, -1);

  assert(pval2.getTerm()->isVariable());
  Variable* var = OBJECT_CAST(Variable*, pval2.getTerm());

  if (var->hasExtraInfo() && var->getName() != NULL)
    {
      //
      // Use the existing name.
      //
      *(stream) << var->getName()->getName();
    }
  else
    {
      //
      // No name.
      //
     *(stream) << "_";
     *(stream) << (qint64)(reinterpret_cast<heapobject*>(var) - heap.getBase());
    }
  return(RV_SUCCESS);
}

//
// Write out the variable name of a variable.  The system generates one and
// records the association if none exists.
//
void
Thread::writeVarName(Object* ref, NameGen gen,
		     word32& counter, QPStream *stream)
{
  assert(ref->isAnyVariable());

  Reference* var = OBJECT_CAST(Reference*, ref);

  assert(var->hasExtraInfo());
  
  Atom* varName = var->getName();
  if (varName == NULL)
    {
      //
      // There is no name for the variable.  Generate one.
      //
      varName = (*gen)(this, counter);
      //
      // Link the name and the variable up together.
      //
      names.setNameOldVar(varName, ref, *this);
    }
  *stream << OBJECT_CAST(Atom*, varName)->getName();
}

//
// psi_writeR_var(stream_index, variable)
// Write the assigned name, which is stored in the name table, for the
// variable.
//
// The name is assigned either by the user via readR/1 or generated by
// writeR_var if it does not have one.
//
// This function is used by writeR/1 and portray/1.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_writeR_var(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  assert(object2->hasLegalSub());
  PrologValue pval2(object2);
  heap.prologValueDereference(pval2);

  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, val1, 1, stream);

  if (pval2.getTerm()->isVariable() && 
      pval2.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, pval2);
    }  
  if (!pval2.getTerm()->isVariable() ||
      !pval2.getSubstitutionBlockList()->isNil())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }

  // IS_READY_STREAM(stream, -1);

  assert(pval2.getTerm()->isVariable());
  Variable* var = OBJECT_CAST(Variable*, pval2.getTerm());

  var = addExtraInfo(var);
  writeVarName(var, 
	       &Thread::GenerateVarName,
	       metaCounter,
	       stream);
  return(RV_SUCCESS);
}

//
// Different specialised versions of write for object variables.
//

//
// psi_write_object_variable(stream_index, object_variable)
// Default method for writing object variables.  If the variable has a name,
// use the name.  Otherwise, output a name of the form _x1, _x2, ...
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_write_object_variable(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  assert(object2->hasLegalSub());
  PrologValue pval2(object2);
  heap.prologValueDereference(pval2);

  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, val1, 1, stream);

  if (pval2.getTerm()->isObjectVariable() && 
      pval2.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, pval2);
    }  

  if (!pval2.getTerm()->isObjectVariable() || 
      !pval2.getSubstitutionBlockList()->isNil())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }

  // IS_READY_STREAM(stream, -1);

  ObjectVariable* obvar = OBJECT_CAST(ObjectVariable*, pval2.getTerm());

  assert(obvar->hasExtraInfo());

  if (obvar->getName() != NULL)
    {
      *stream << obvar->getName()->getName();
    }
  else
    {
      writeVarName(obvar, 
		   &Thread::GenerateObjectVariableName,
		   objectCounter, stream);
    }
  return(RV_SUCCESS);
}

//
// psi_writeR_ObjectVariable(stream_index, ObjectVariable)
// Write the assigned name, which is stored in the name table, for the
// object variable.
//
// The name is assigned either by the user via readR/1 or generated by
// writeR_ObjectVariable if it does not have one.
//
// This function is used by writeR/1 and portray/1.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_writeR_object_variable(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  assert(object2->hasLegalSub());
  PrologValue pval2(object2);
  heap.prologValueDereference(pval2);


  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, val1, 1, stream);

  if (pval2.getTerm()->isObjectVariable() && 
      pval2.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, pval2);
    }  

  if (!pval2.getTerm()->isObjectVariable() ||
      !pval2.getSubstitutionBlockList()->isNil())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }

  // IS_READY_STREAM(stream, -1);

  //
  // Get the stream.
  //

  ObjectVariable* obvar = OBJECT_CAST(ObjectVariable*, pval2.getTerm());

  if (obvar->getName() != NULL)
    {
      *stream << obvar->getName()->getName();
    }
  else
    {
      writeVarName(obvar, 
		   &Thread::GenerateRObjectVariableName,
		   objectCounter, stream);
    }
  return(RV_SUCCESS);
}

//
// psi_writeq_ObjectVariable(stream_index, ObjectVariable)
//
// Write the assigned name, which is stored in the name table, for the
// object variable.
//
// The name is assigned either by the user via readR/1 or generated by
// writeR_ObjectVariable if it does not have one.
//
// This function is used by writeq/1 and portray/1.
//
// Funny names are quoted.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_writeq_object_variable(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  assert(object2->hasLegalSub());
  PrologValue pval2(object2);
  heap.prologValueDereference(pval2);

  QPStream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, val1, 1, stream);

  if (pval2.getTerm()->isObjectVariable() && 
      pval2.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, pval2);
    }  

  if (!pval2.getTerm()->isObjectVariable() ||
      !pval2.getSubstitutionBlockList()->isNil())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }

  // IS_READY_STREAM(stream, -1);

  //
  // Get the stream.
  //

  ObjectVariable* obvar = OBJECT_CAST(ObjectVariable*, pval2.getTerm());

  if (obvar->getName() != NULL)
    {
      const char *s = obvar->getName()->getName();
      writeqAtom(s, stream);
    }
  else
    {
      writeVarName(obvar,
		   &Thread::GenerateRObjectVariableName,
		   objectCounter, stream);
    }
  
  return(RV_SUCCESS);
}

//
// A low-level dump of the term
//
Thread::ReturnValue
Thread::psi_debug_write(Object *& object1)
{
  #ifdef QP_DEBUG
  object1->printMe_dispatch(*atoms,false);
  #endif
  return(RV_SUCCESS);
}


