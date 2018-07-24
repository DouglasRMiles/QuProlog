// bind.h - Qu-Prolog bindings. 
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
// $Id: bind.h,v 1.4 2006/01/31 23:17:49 qp Exp $

//#include "thread.h"
//#include "trail.h"

#ifndef BIND_H
#define BIND_H

public:

//
// Bind two variables based on age.
//
void bindVariables(Variable *, Variable *);

//
// Bind two object variables based on age.
//
void bindObjectVariables(ObjectVariable *, ObjectVariable *);

//
// Some thread methods involving trailing.
//

inline void bindVarVar(Object* var1, Object* var2)
{
  assert(var1 != var2);
  assert(var1->isVariable());
  assert(var2->isVariable());
  assert(!OBJECT_CAST(Reference*, var1)->hasExtraInfo());
  assert(!OBJECT_CAST(Reference*, var2)->hasExtraInfo());
  assert(!OBJECT_CAST(Variable*, var1)->isFrozen());
  assert(!OBJECT_CAST(Variable*, var2)->isFrozen());
  if (reinterpret_cast<heapobject*>(var1) >= heap.getSavedTop())
    {
      *(var1->storage()) = reinterpret_cast<heapobject>(var2);
    }
  else if (reinterpret_cast<heapobject*>(var2) >= heap.getSavedTop())
    {
      *(var2->storage()) = reinterpret_cast<heapobject>(var1);
    }
  else
    {
      bindingTrail.push(reinterpret_cast<heapobject*>(var1));
      *(var1->storage()) = reinterpret_cast<heapobject>(var2);
    }

}

inline void bindAndTrail(Object* var, Object* value)
{
  assert(var != NULL);
  assert(value != NULL);
  assert(var->isAnyVariable());
  //
  // Trail only if var is before saved top
  //

  if (reinterpret_cast<heapobject*>(var) < heap.getSavedTop() &&
      reinterpret_cast<heapobject*>(var) >= heap.getBase())
    {
      bindingTrail.push(reinterpret_cast<heapobject*>(var));
    }
  *(var->storage()) = 
    reinterpret_cast<heapobject>(value); 
}

inline void updateAndTrailObject(heapobject* ptr, Object* value, u_int offset)
{
  assert(ptr != NULL);
  assert(value != NULL);
  //
  // Don't trail only if ptr is after saved top on the heap
  //
  if (quick_tidy_check) {
    if ((ptr < heap.getSavedTop()) || (ptr >=  heap.getTop())) {
      heapobject* ptroffval = (heapobject*)(*(ptr+offset));
      assert((ptroffval == NULL) || !reinterpret_cast<Object*>(ptroffval)->isSubstitutionBlock());
      otherTrail.push(ptr, reinterpret_cast<Object*>(ptroffval), offset);
    }
  } else {
    UpdatableObjectEntry entry(ptr, value, offset);
    HeapAndTrailsChoice state = 
      choiceStack.getHeapAndTrailsState(currentChoicePoint);
    heapobject* savedHT;
    TrailLoc savedBindingTrailTop;
    TrailLoc savedOtherTrailTop;
    
    state.restore(savedHT, savedBindingTrailTop, savedOtherTrailTop); 

    if (!entry.tidy(otherTrail.getTop(), savedOtherTrailTop, savedHT, heap))
      {
        heapobject* ptroffval = (heapobject*)(*(ptr+offset));
        assert((ptroffval == NULL) || !reinterpret_cast<Object*>(ptroffval)->isSubstitutionBlock());
        otherTrail.push(ptr, reinterpret_cast<Object*>(ptroffval), offset);
      }
  }
  *(ptr+offset) = reinterpret_cast<heapobject>(value); 
}

//
// Update and trail an implicit parameter entry
//
inline void updateAndTrailIP(heapobject* ptr, Object* value,
                             u_int offset = 0)
{
  assert(ptr != NULL);
  assert(value != NULL);
  //
  // Don't trail only if ptr is after saved top on the heap
  //
  if (quick_tidy_check) {
    if (ptr < heap.getSavedTop() || ptr >= heap.getTop())
      {
        otherTrail.push(ptr, reinterpret_cast<Object*>(*(ptr+offset)), offset);
      }
  } else {
    UpdatableObjectEntry entry(ptr, value, offset);
    HeapAndTrailsChoice state = 
      choiceStack.getHeapAndTrailsState(currentChoicePoint);
    heapobject* savedHT;
    TrailLoc savedBindingTrailTop;
    TrailLoc savedOtherTrailTop;
    
    state.restore(savedHT, savedBindingTrailTop, savedOtherTrailTop); 
    
    if (!entry.tidy(otherTrail.getTop(), savedOtherTrailTop, savedHT, heap))
      {
        otherTrail.push(ptr, reinterpret_cast<Object*>(*(ptr+offset)), offset);
      }
  }
  *(ptr+offset) = reinterpret_cast<heapobject>(value); 
}

inline void trailTag(Object* o)
{
  assert(o != NULL);
  //
  // Don't trail only if o is after saved top on the heap
  //
  if (quick_tidy_check) {
    if (reinterpret_cast<heapobject*>(o) < heap.getSavedTop() ||
        reinterpret_cast<heapobject*>(o) >= heap.getTop())
      {
        otherTrail.push(reinterpret_cast<heapobject*>(o), 
                        *(reinterpret_cast<heapobject*>(o)));
      }
  } else {
    UpdatableTagEntry entry(reinterpret_cast<heapobject*>(o), 
                            *(reinterpret_cast<heapobject*>(o)));
    HeapAndTrailsChoice state = 
      choiceStack.getHeapAndTrailsState(currentChoicePoint);
    heapobject* savedHT;
    TrailLoc savedBindingTrailTop;
    TrailLoc savedOtherTrailTop;
    
    state.restore(savedHT, savedBindingTrailTop, savedOtherTrailTop); 
    
    if (!entry.tidy(otherTrail.getTop(), savedOtherTrailTop, savedHT, heap))
      {        
        otherTrail.push(reinterpret_cast<heapobject*>(o), 
                        *(reinterpret_cast<heapobject*>(o)));
      }
  }
}

//
// var is an unbound variable. Bind var to object.
// Assumes var is dereferenced.
//
inline void bind(Variable *var , Object *object)
{
  assert(var == var->variableDereference());
  assert(var->isAnyVariable());
  //
  // Wake up any delayed problems associated with cell1.
  //
  
  if (var->getDelays()->isCons())
    {
      wakeUpDelayedProblems(var);
    }
  bindAndTrail(var, object);
}

//
// If the variable does not have extra info then
// create a new variable (with extra info) that has
// the same tags as the given variable and bind the given
// var to the new var.
//
inline Variable* addExtraInfo(Variable* oldvar)
{
  assert(oldvar == oldvar->variableDereference());
  if (!oldvar->hasExtraInfo())
    {
      Variable* newvar = heap.newVariable(true);
      newvar->copyTag(oldvar);
      bind(oldvar, newvar);
      return newvar;
    }
  else
    {
      return oldvar;
    }
}

#endif  // BIND_H







