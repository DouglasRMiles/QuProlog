// state.cc - Save and restore state predicates.
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
// $Id: state.cc,v 1.9 2006/04/04 02:44:32 qp Exp $

#include <iostream>
#include <fstream>

#include "config.h"

#include "atom_table.h"
#include "code.h"
#include "int.h"
#include "io_qp.h"
#include "is_ready.h"
#include "pred_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;
extern Code *code;
extern IOManager *iom;
extern PredTab *predicates;

//
// psi_save(filename)
// Save the state of the execution into the "filename".
//
Thread::ReturnValue
Thread::psi_save(Object *& stream_arg)
{
#if 0
  bool status;

  Object* stream_val = heap.dereference(stream_arg);

  Stream *stream;
  DECODE_STREAM_OUTPUT_ARG(heap, *iom, stream_val, 1, stream);

  //  IS_READY_STREAM(stream, -1);
  
  ostream& ostrm = *stream->getOutput();

  //
  // Write the version identification.
  //
  IntSave<word32>(ostrm, QU_PROLOG_VERSION);

  //
  // Save the areas.
  //
  code->save(ostrm);
  predicates->save(ostrm);
  atoms->saveStringTable(ostrm);
  atoms->save(ostrm);
  record_db->save(ostrm);
  save(ostrm);

  //
  // Close the file.
  //
  status = ostrm.good();

  return BOOL_TO_RV(status);
#endif // 0
  return RV_FAIL;
}

//
// psi_restore(filename)
// Restore the state of the execution from the "filename".
//
Thread::ReturnValue
Thread::psi_restore(Object *& stream_arg)
{
#if 0
  word32 magic = 0;
  const char file[] = "Qu-Prolog";
  bool status;

  Object* stream_val = heap.dereference(stream_arg);

  Stream *stream;
  DECODE_STREAM_INPUT_ARG(heap, *iom, stream_val, 1, stream);

  IS_READY_STREAM(stream, -1);
  
  istream *istrm = stream->getInput();

  //
  // Read the version identification.
  //
  magic = IntLoad<word32>(*istrm);
  if (magic != QU_PROLOG_VERSION)
    {
      Warning(__FUNCTION__, "incompatible version");
      return RV_FAIL;
    }

  //
  // Restore the areas.
  //
  magic = IntLoad<word32>(*istrm);

  while (istrm->good())
    {
      if (magic == CODE_MAGIC_NUMBER)
	{
	  code->load(*istrm);
	}
      else if (magic == PRED_TABLE_MAGIC_NUMBER)
	{
	  predicates->load(*istrm);
	}
      else if (magic == STRING_TABLE_MAGIC_NUMBER)
	{
	  atoms->loadStringTable(*istrm);
	}
      else if (magic == ATOM_TABLE_MAGIC_NUMBER)
	{
	  atoms->load(*istrm);
	}
      else if (magic == RECORD_TABLE_MAGIC_NUMBER)
	{
	  record_db->load(*istrm);
	}
      else if (Magic("th00") <= magic && magic <= Magic("th99"))
	{
	  magic = load(*istrm, magic);
	  continue;
	}
      else
	{
	  ReadFailure(__FUNCTION__, "illegal magic number", file);
	}

      magic = IntLoad<word32>(*istrm);
    }

  //
  // Close the file.
  //
  status = istrm->fail();
  delete istrm;

#if 0
  InstallEscapes(atoms, predicates);
#endif	// 0

  return BOOL_TO_RV(status);
#endif // 0
  return RV_FAIL;
}

// psi_global_state_set(key, value)
// Assign a value for a global state entry.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_global_state_set(Object *& object1, Object *& object2)
{
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);
  
  if (val1->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (! val1->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  if (val2->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (!val2->isConstant())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  if (val2->isAtom())
    {
      OBJECT_CAST(Atom*, val1)->associateAtom(OBJECT_CAST(Atom*, val2));
    }
  else
    {
      OBJECT_CAST(Atom*, val1)->associateInteger(val2->getInteger());
    }
  
  code->Stamp();
  return(RV_SUCCESS);
}

// psi_global_state_lookup(key, value)
// Lookup a value for a global state entry.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_global_state_lookup(Object *& object1, Object *& object2)
{
  Object* val1 = heap.dereference(object1);
  
  if (val1->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (! val1->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  Atom* name = OBJECT_CAST(Atom*, val1);

  if (name->hasAssociatedAtom())
    {
      object2 = name->getAssociatedAtom();

      return RV_SUCCESS;
    }
  else if (name->hasAssociatedInteger())
    {
      object2 = heap.newInteger(name->getAssociatedInteger());

      return RV_SUCCESS;
    }
  else
    {
      return RV_FAIL;
    }

  // Shouldn't ever get here.
  assert(false);
  return(RV_FAIL);
}


// psi_global_state_increment(key, value)
// Increment the value for a global state entry and return the new value.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_global_state_increment(Object *& object1, Object *& object2)
{
  Object* val1 = heap.dereference(object1);
  
  if (val1->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (! val1->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  Atom* name = OBJECT_CAST(Atom*, val1);
  
  if (name->hasAssociatedInteger())
    {
      const qint64 intval = name->getAssociatedInteger() + 1;
      name->associateInteger(intval);
      
      object2 = heap.newInteger(intval);      

      code->Stamp();
      return RV_SUCCESS;
    }
  else
    {
      return RV_FAIL;
    }
  
  // Shouldn't ever get here.
  assert(false);
  return(RV_FAIL);
}

// psi_global_state_decrement(key, value)
// Decrement the value for a global state entry and return the new value.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_global_state_decrement(Object *& object1, Object *& object2)
{
  Object* val1 = heap.dereference(object1);
  
  if (val1->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (! val1->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  Atom* name = OBJECT_CAST(Atom*, val1);
  if (name->hasAssociatedInteger())
    {
      const qint64 intval = name->getAssociatedInteger() - 1;
      
      name->associateInteger(intval);
      object2 = heap.newInteger(intval);

      code->Stamp();
      return RV_SUCCESS;
    }
  else
    {
      return RV_FAIL;
    }

  // Shouldn't ever get here.
  assert(false);
  return(RV_FAIL);
}



