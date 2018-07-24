// user_hash_table_escapes.cc - Interface to user hash table.
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
// $Id: user_hash_table_escapes.cc,v 1.1 2006/01/31 23:19:09 qp Exp $

#include "user_hash_table.h"
#include "code.h"
#include "thread_qp.h"

extern Code *code;

extern UserHashState* user_hash;

//
// psi_user_ht_insert(Fst, Snd, Data)
// Insert Data into the user hash table indexed by Fst and Snd
//
// mode(in,in,in)

Thread::ReturnValue 
Thread::psi_user_ht_insert(Object *& fst_obj, Object *& snd_obj, 
			   Object *& data_obj)
{
  Object* fst = fst_obj->variableDereference();
  Object* snd = snd_obj->variableDereference();
  Object* data = data_obj->variableDereference();
  if (!fst->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (!snd->isConstant()) 
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  user_hash->addEntry(fst, snd, data, TheHeap());
  code->Stamp();
  return RV_SUCCESS;

}

//
// psi_user_ht_lookup(Fst, Snd, Data)
// Lookup Data in the user hash table indexed by Fst and Snd
//
// mode(in,in,out)

Thread::ReturnValue 
Thread::psi_user_ht_lookup(Object *& fst_obj, Object *& snd_obj, 
			   Object *& data)
{
  Object* fst = fst_obj->variableDereference();
  Object* snd = snd_obj->variableDereference();
  if (!fst->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (!snd->isConstant()) 
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  bool result = user_hash->lookupEntry(fst, snd, data, TheHeap());
  return BOOL_TO_RV(result);
}

//
// psi_user_ht_remove(Fst, Snd)
// Remove entry in the user hash table indexed by Fst and Snd
//
// mode(in,in)
Thread::ReturnValue 
Thread::psi_user_ht_remove(Object *& fst_obj, Object *& snd_obj)
{
  Object* fst = fst_obj->variableDereference();
  Object* snd = snd_obj->variableDereference();
  if (!fst->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (!snd->isConstant()) 
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  user_hash->removeEntry(fst, snd);
  code->Stamp();
  return RV_SUCCESS;
}


//
// psi_user_ht_search(Fst, Snd, Data)
// Collect together all entries in the hash table that match
// Fst and Snd. Data is a list of elements of the form '$'(F,S,T)
//
// mode(in,in,out)

Thread::ReturnValue 
Thread::psi_user_ht_search(Object *& fst_obj, Object *& snd_obj, 
			   Object *& data)
{
  Object* fst = fst_obj->variableDereference();
  Object* snd = snd_obj->variableDereference();
  if (!fst->isAtom() && !fst->isVariable())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (!snd->isConstant() && !snd->isVariable()) 
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  user_hash->hashIterReset();

  data =  AtomTable::nil;

  Object *fst1, *snd1, *t1; 
  while (user_hash->hashIterNext(fst1, snd1, t1, TheHeap()))
    {
      if ((fst->isVariable() || fst->equalConstants(fst1))
	  &&
	  (snd->isVariable() || snd->equalConstants(snd1)))
	{
 	  Structure* term = TheHeap().newStructure(3);
	  term->setFunctor(AtomTable::dollar);
	  term->setArgument(1, fst1);
	  term->setArgument(2, snd1);
	  term->setArgument(3, t1);

	  Object* tmp = TheHeap().newCons(term, data);
	  data = tmp;
	}
    }
  return RV_SUCCESS;
}
