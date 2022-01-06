// ip.cc - Routines for manipulating implicit parameters, which must be an atom.
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
// $Id: ip.cc,v 1.11 2006/01/31 23:17:50 qp Exp $


#include "atom_table.h"
#include "thread_qp.h"
extern AtomTable *atoms;
//
// The IP array size is a power of 2
//
const size_t ip_array_size = 128;

//
// We use the following idea from BinProlog to minimize trail usage.
// The data structures used are as follows
//
//  IPtable                  heap
//
//  |       |                  |        |
//  |       |                  |        |
//  |Ref:   |-----+            |        |
//  |       |     +----------->|value(*)|
//  |       |                  |        |
//  |       |                  |        |
//  |       |                  |        |
//
//  After each ip_set the value at (*) is above the saved top of stack
//  I.E. above the last choice point.
//  This means that at the start of each ip_set we can determine when
//  trailing needs to take place by simply comparing the pointer from the IP
//  and the saved top of heap. If the pointer is below saved TOH
//  then trailing is required, otherwise it is not required.
//  If trailing is required, a reference is created, that replaces
//  the value in the IPtable (and is trailed).
//  The value is placed in the heap at the place pointed to by the 
//  new reference.
//  If no trailing is required the value at (*) is replaced by 
//  the new value (not trailed).
//
//  The structures used for IP arrays are as follows
//
//  IPtable                  heap
//
//  |       |                  | ...    |
//  |       |            (arg1)| Ref    | --> list (on heap)
//  |Struct |-----+            | arity  |
//  |       |     +----------->|$iparray|
//  |       |                  |        |
//  |       |                  |        |
//  |       |                  |        |
//
//  The lists on the heap are of the form [$iparray(Val,Hash)...]
//  where Hash is the atomic value input as an offset into the array
//  Val is the value of this entry and has the same properties as the
//  Val of a simple IP (in terms of trail optimization).
//
// Note: There are three possibilities for the value of in the IPtable
// (before dereferencing)
// 1. NULL          - no value present
// 2. A variable*   - an ordinary IP
// 3. A structure*  - an array IP


// psi_ip_set(key, value)
// Assign a value for an implicit parameter.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_ip_set(Object *& object1, Object *& object2)
{
  Object *name_object = heap.dereference(object1);

  if (name_object->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (! name_object->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  
  Object *current_value = ipTable.getImplicitPara(name_object);
  if (current_value != NULL && current_value->isStructure() && 
      OBJECT_CAST(Structure *, current_value)->getFunctor() 
      == AtomTable::arrayIP)
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  Object *new_value = object2->variableDereference();
  if (current_value == NULL ||
      (heap.getSavedTop() > reinterpret_cast<heapobject*>(current_value)))
    {
      Variable *var = heap.newVariable();
      var->setReference(new_value);
      ipTable.setImplicitPara(name_object, var, *this);
    }
  else
    {
      assert(current_value->isVariable());
      OBJECT_CAST(Variable*, current_value)->setReference(new_value);
    }

  return RV_SUCCESS;
}

// psi_ip_setA(key, hashVal, value)
// Assign a value for an array implicit parameter.
// mode(in,in,in)
//
Thread::ReturnValue
Thread::psi_ip_setA(Object *& object1, Object *& object2, Object *& object3)
{
  Object *name_object = heap.dereference(object1);
  
  if (name_object->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (! name_object->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  Object *hash_val = heap.dereference(object2);

  /* get IP offset */
  if (hash_val->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (! hash_val->isConstant())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  
    /* set value */
  Object *new_value = object3->variableDereference();
  Object *current_value = ipTable.getImplicitPara(name_object);
  
  size_t array_size;
  if (current_value == NULL) 
    {
	  assert(ip_array_size <= MaxArity);
      current_value = heap.newStructure(ip_array_size);
      OBJECT_CAST(Structure*, current_value)->setFunctor(AtomTable::arrayIP);
      
      array_size = ip_array_size;
      for (size_t i = 1; i <= ip_array_size; i++)
	{
	  OBJECT_CAST(Structure*, current_value)->setArgument(i, AtomTable::nil);
	}

      ipTable.setImplicitPara(name_object, current_value, *this);
    }
  else
    {
      if (! current_value->isStructure() || 
	  OBJECT_CAST(Structure *, current_value)->getFunctor() 
	  != AtomTable::arrayIP)
	{
	  PSI_ERROR_RETURN(EV_TYPE, 1);
	}
      array_size = OBJECT_CAST(Structure *, current_value)->getArity();
    }
  
  const qint64 offset = 1 +
    static_cast<qint64>((hash_val->isNumber() ?
      (hash_val->getInteger() & (array_size-1))
    : ((reinterpret_cast<wordptr>(hash_val) >> 2) & (array_size-1))));

  Object *array_val_list = 
    OBJECT_CAST(Structure*, current_value)->getArgument(offset)->variableDereference();

  Object *array_ptr = array_val_list;

  for (;
       array_ptr->isCons();
       array_ptr = OBJECT_CAST(Cons *, array_ptr)->getTail()
       )
    {
      assert(OBJECT_CAST(Cons *, array_ptr)->getHead()->isStructure());
      
      Structure *array_val_head = 
	OBJECT_CAST(Structure *, OBJECT_CAST(Cons *, array_ptr)->getHead());

      Object *list_hash = array_val_head->getArgument(2);

      if (list_hash == hash_val ||
	  (hash_val->isNumber() && list_hash->isNumber() &&
	   hash_val->getInteger() == list_hash->getInteger()))
	{
	  break;
	}
    }

  if (array_ptr->isNil())
    {
      // no value for this offset
      Structure *new_array_val_head = heap.newStructure(2);
      
      new_array_val_head->setFunctor(AtomTable::arrayIP);
      new_array_val_head->setArgument(2, hash_val);

      Variable* ipvar = heap.newVariable();
      ipvar->setReference(new_value);

      new_array_val_head->setArgument(1, ipvar);

      Object *new_array_val_list = heap.newCons(new_array_val_head,
						array_val_list);

      assert(current_value->isStructure());
      updateAndTrailIP(reinterpret_cast<heapobject*>(current_value), 
		       new_array_val_list, offset+1);
    }
  else
    {
      assert(array_ptr->isCons());
      Structure *array_val_head = 
	OBJECT_CAST(Structure *, 
		    OBJECT_CAST(Cons *, array_ptr)->getHead());

      if (heap.getSavedTop() >
	  reinterpret_cast<heapobject*>(array_val_head->getArgument(1)))
	{
	  Variable* ipvar = heap.newVariable();
	  ipvar->setReference(new_value);
	  // The 2 below is the offset to the first arg of the struct
	  updateAndTrailIP(reinterpret_cast<heapobject*>(array_val_head), 
			   ipvar, 2);
	}
      else
	{
	  Object* old = array_val_head->getArgument(1);
	  assert(old->isVariable());
	  OBJECT_CAST(Variable*, old)->setReference(new_value);
	}
    }
  
  return RV_SUCCESS;
}


//
// psi_ip_lookup(key, value)
// Look up the value of an implicit parameter.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_ip_lookup(Object *& object1, Object *& object2)
{
  Object *name_object = heap.dereference(object1);

  if (name_object->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (! name_object->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  Object *current_value = ipTable.getImplicitPara(name_object);
  if (current_value != NULL &&
      current_value->isStructure() && 
      OBJECT_CAST(Structure*, current_value)->getFunctor()
      == AtomTable::arrayIP)
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (current_value == NULL)
    {
      Variable* ip_var = heap.newVariable();
      Variable* new_ref = heap.newVariable();
      ip_var->setReference(new_ref);
      
      ipTable.setImplicitPara(name_object, ip_var, *this);

      current_value = new_ref;
    }

  object2 = current_value->variableDereference();

  return RV_SUCCESS;
}

// psi_ip_lookupA(key, hash_val, value)
// Lookup a value for an array implicit parameter.
// mode(in,in,out)
//
Thread::ReturnValue
Thread::psi_ip_lookupA(Object *& object1, Object *& object2, Object *& object3)
{
  Object *name_object = heap.dereference(object1);
  Object *hash_val = heap.dereference(object2);
  Object *current_ip_val;

  /* get IP array name */
  if (name_object->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (! name_object->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  /* get IP offset */
  if (hash_val->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (! hash_val->isConstant())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  /* lookup value */
  Object *current_value = ipTable.getImplicitPara(name_object);
  
  size_t array_size;
  if (current_value == NULL)
    {
	  assert(ip_array_size <= MaxArity);
      current_value = heap.newStructure(ip_array_size);
      OBJECT_CAST(Structure*, current_value)->setFunctor(AtomTable::arrayIP);
      
      for (size_t i = 1; i <= ip_array_size; i++)
	{
	  OBJECT_CAST(Structure*, current_value)->setArgument(i, AtomTable::nil);
	}

      array_size = ip_array_size;
      ipTable.setImplicitPara(name_object, current_value, *this);
    }
  else
    {
      if (! current_value->isStructure() || 
	  OBJECT_CAST(Structure*, current_value)->getFunctor() 
	  != AtomTable::arrayIP)
	{
	  PSI_ERROR_RETURN(EV_TYPE, 1);
	}
      array_size = OBJECT_CAST(Structure*, current_value)->getArity();
    }
  
  const int32 offset = 1 +
    static_cast<int32>((hash_val->isNumber()
     ? hash_val->getInteger() & (array_size-1) 
     : (reinterpret_cast<wordptr>(hash_val) >> 2) & (array_size-1)));
  
  Object *array_val_list = 
    OBJECT_CAST(Structure*, current_value)->getArgument(offset)->variableDereference();
  Object *array_ptr = array_val_list;

  assert(array_ptr->isList());

  for (;
       array_ptr->isCons();
       array_ptr = OBJECT_CAST(Cons*, array_ptr)->getTail()->variableDereference())
    {
      Object *array_val_head =  
	OBJECT_CAST(Cons*, array_ptr)->getHead()->variableDereference();

      assert(array_val_head->isStructure());

      Object *list_hash = 
	OBJECT_CAST(Structure*, array_val_head)->getArgument(2)->variableDereference();

      if (list_hash == hash_val ||
	  (hash_val->isNumber() && list_hash->isNumber() &&
	   hash_val->getInteger() == list_hash->getInteger()))
	{
	  object3 = OBJECT_CAST(Structure*, array_val_head)->getArgument(1)->variableDereference();
	  return RV_SUCCESS;
	}
    }

  assert(array_ptr->isNil());

  // no value for this offset
  Structure* array_val_head = heap.newStructure(2);
  array_val_head->setFunctor(AtomTable::arrayIP);
  array_val_head->setArgument(2, hash_val);
      
  Variable *new_ref = heap.newVariable();
  Variable *ip_var = heap.newVariable(new_ref);
  ip_var->setReference(new_ref);
  array_val_head->setArgument(1, ip_var);
  
  current_ip_val = ip_var;
  
  Cons *new_array_val_list = heap.newCons(array_val_head, array_val_list);
  
  assert(current_value->isStructure());

  updateAndTrailIP(reinterpret_cast<heapobject*>(current_value), 
		   new_array_val_list, offset+1);
  object3 = new_ref;
  return(RV_SUCCESS);
}

// psi_ip_get_array_keys(name, values)
// return all the keys for the IP array name
// mode(in, out)
//
Thread::ReturnValue
Thread::psi_ip_get_array_entries(Object *& object1, Object *& object2)
{
  Object *name_object = heap.dereference(object1);
  if (name_object->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (! name_object->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  Object *current_value = ipTable.getImplicitPara(name_object);
  Object *result = AtomTable::nil;
  size_t array_size;

  if (current_value == NULL)
    {
      object2 = result;
      return RV_SUCCESS;
    }
  if (! current_value->isStructure() || 
      OBJECT_CAST(Structure*, current_value)->getFunctor() 
      != AtomTable::arrayIP)
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  array_size = OBJECT_CAST(Structure*, current_value)->getArity();
  for (size_t i = 1; i <= array_size; i++)
    {
      Object* entry = OBJECT_CAST(Structure*, current_value)->getArgument(i);
      if (!entry->isNil())
        {
          Object *array_ptr = entry;
          for (;
               array_ptr->isCons();
               array_ptr = OBJECT_CAST(Cons*, array_ptr)->getTail()->variableDereference())
            {
              Object *array_val_head =  
                OBJECT_CAST(Cons*, array_ptr)->getHead()->variableDereference();
              
              assert(array_val_head->isStructure());
              
              Object *list_hash = 
                OBJECT_CAST(Structure*, array_val_head)->getArgument(2)->variableDereference();
              result = heap.newCons(list_hash, result);
            }
        }
    }
  object2 = result;
  return RV_SUCCESS;;
}

// psi_ip_array_clear(key)
// Clear (initilize) an IP array.
// mode(in)
//
Thread::ReturnValue
Thread::psi_ip_array_clear(Object *& object1)
{
  Object *name_object = heap.dereference(object1);
  
  /* get IP array name */
  if (name_object->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (! name_object->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  /* clear (init) array */

  // check if IP is not already in use as an non-array IP
  Object* old = ipTable.getImplicitPara(name_object);
  if (old != NULL && !old->isStructure())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  size_t array_size;
  if (old == NULL)
    {
      array_size = ip_array_size;
    }
  else
    {
      array_size = OBJECT_CAST(Structure*, old)->getArity();
    }
	  assert(ip_array_size <= MaxArity);
  Structure *ip_array_struct = heap.newStructure(array_size);
  ip_array_struct->setFunctor(AtomTable::arrayIP);
  
  for (size_t i = 1; i <= array_size; i++)
    {
      ip_array_struct->setArgument(i, AtomTable::nil);
    }
  
  ipTable.setImplicitPara(name_object, ip_array_struct, *this);

  return RV_SUCCESS;
}

// psi_ip_array_init(key, size)
// Initilize an IP array to size.
// mode(in, in)
//
Thread::ReturnValue 
Thread::psi_ip_array_init(Object *& object1, Object *& object2)
{
  Object *name_object = heap.dereference(object1);
  
  /* get IP array name */
  if (name_object->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (! name_object->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  Object *size_object = heap.dereference(object2);
  
  /* get IP array size */
  if (size_object->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (! size_object->isNumber())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  int size = size_object->getInteger();
  if (size <= 0)
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  // Calculate power of 2 >= size
  size_t array_size = 1;
  size--;
  while (size > 0)
    {
      size >>= 1;
      array_size <<= 1;
    } 

  // Create new IP array
	  assert(ip_array_size <= MaxArity);
  Structure *ip_array_struct = heap.newStructure(array_size);
  ip_array_struct->setFunctor(AtomTable::arrayIP);
  
  for (size_t i = 1; i <= array_size; i++)
    {
      ip_array_struct->setArgument(i, AtomTable::nil);
    }
  
  ipTable.setImplicitPara(name_object, ip_array_struct, *this);

  return RV_SUCCESS;
}

//
// psi_ip_lookup_default(key, value,default)
// Look up the value of an implicit parameter.
// mode(in,out,in)
//
Thread::ReturnValue
Thread::psi_ip_lookup_default(Object *& object1, Object *& object2, Object *& object3)
{
  Object *name_object = heap.dereference(object1);
  Object *default_val = heap.dereference(object3);
  if (name_object->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (! name_object->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  Object *current_value = ipTable.getImplicitPara(name_object);
  if (current_value != NULL &&
      current_value->isStructure() && 
      OBJECT_CAST(Structure*, current_value)->getFunctor()
      == AtomTable::arrayIP)
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (current_value == NULL)
    {
      Variable* ip_var = heap.newVariable();
      ip_var->setReference(default_val);
      
      ipTable.setImplicitPara(name_object, ip_var, *this);

      current_value = default_val;
    }

  object2 = current_value->variableDereference();

  return RV_SUCCESS;
}

// psi_ip_lookupA_default(key, hash_val, value, default)
// Lookup a value for an array implicit parameter.
// mode(in,in,out, in)
//
Thread::ReturnValue
Thread::psi_ip_lookupA_default(Object *& object1, Object *& object2, 
                               Object *& object3, Object *& object4)
{
  Object *name_object = heap.dereference(object1);
  Object *hash_val = heap.dereference(object2);
  Object *current_ip_val;
  Object *default_val = heap.dereference(object4);


  /* get IP array name */
  if (name_object->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (! name_object->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }

  /* get IP offset */
  if (hash_val->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  if (! hash_val->isConstant())
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  /* lookup value */
  Object *current_value = ipTable.getImplicitPara(name_object);
  
  size_t array_size;
  if (current_value == NULL)
    {
	  assert(ip_array_size <= MaxArity);
      current_value = heap.newStructure(ip_array_size);
      OBJECT_CAST(Structure*, current_value)->setFunctor(AtomTable::arrayIP);
      
      for (size_t i = 1; i <= ip_array_size; i++)
	{
	  OBJECT_CAST(Structure*, current_value)->setArgument(i, AtomTable::nil);
	}

      array_size = ip_array_size;
      ipTable.setImplicitPara(name_object, current_value, *this);
    }
  else
    {
      if (! current_value->isStructure() || 
	  OBJECT_CAST(Structure*, current_value)->getFunctor() 
	  != AtomTable::arrayIP)
	{
	  PSI_ERROR_RETURN(EV_TYPE, 1);
	}
      array_size = OBJECT_CAST(Structure*, current_value)->getArity();
    }
  
  const int32 offset = 1 +
    static_cast<int32>((hash_val->isNumber()
     ? hash_val->getInteger() & (array_size-1) 
     : (reinterpret_cast<wordptr>(hash_val) >> 2) & (array_size-1)));
  
  Object *array_val_list = 
    OBJECT_CAST(Structure*, current_value)->getArgument(offset)->variableDereference();
  Object *array_ptr = array_val_list;

  assert(array_ptr->isList());

  for (;
       array_ptr->isCons();
       array_ptr = OBJECT_CAST(Cons*, array_ptr)->getTail()->variableDereference())
    {
      Object *array_val_head =  
	OBJECT_CAST(Cons*, array_ptr)->getHead()->variableDereference();

      assert(array_val_head->isStructure());

      Object *list_hash = 
	OBJECT_CAST(Structure*, array_val_head)->getArgument(2)->variableDereference();

      if (list_hash == hash_val ||
	  (hash_val->isNumber() && list_hash->isNumber() &&
	   hash_val->getInteger() == list_hash->getInteger()))
	{
	  object3 = OBJECT_CAST(Structure*, array_val_head)->getArgument(1)->variableDereference();
	  return RV_SUCCESS;
	}
    }

  assert(array_ptr->isNil());

  // no value for this offset
  Structure* array_val_head = heap.newStructure(2);
  array_val_head->setFunctor(AtomTable::arrayIP);
  array_val_head->setArgument(2, hash_val);
      
  Variable *ip_var = heap.newVariable();
  ip_var->setReference(default_val);
  array_val_head->setArgument(1, ip_var);
  
  current_ip_val = ip_var;
  
  Cons *new_array_val_list = heap.newCons(array_val_head, array_val_list);
  
  assert(current_value->isStructure());

  updateAndTrailIP(reinterpret_cast<heapobject*>(current_value), 
		   new_array_val_list, offset+1);
  object3 = default_val;
  return(RV_SUCCESS);
}






