// distinction.cc - Contains a set of functions for dealing with distinctness 
//		    information associated with the object variable.
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
// $Id: distinction.cc,v 1.5 2006/01/31 23:17:50 qp Exp $

// #include "atom_table.h"
#include "thread_qp.h"

//
// Set two object variables to be distinct from each other.
//
void
Thread::setDistinctObjectVariable(ObjectVariable *object_variable1,
				  ObjectVariable *object_variable2)
{
  assert(object_variable1->getReference() == object_variable1);
  assert(object_variable2->getReference() == object_variable2);

 updateAndTrailObject(reinterpret_cast<heapobject*>(object_variable1),
		       heap.newCons(object_variable2, 
				    object_variable1->getDistinctness()),
		       ObjectVariable::DistinctnessOffset);
}

void
Thread::setDistinct(ObjectVariable *object_variable1,
		    ObjectVariable *object_variable2)
{
  setDistinctObjectVariable(object_variable1, object_variable2);
  setDistinctObjectVariable(object_variable2, object_variable1);
}



//
// Set all the range elements to be mutually disjoint from each other.
// Assume the range are newly created object variables.
//
void
Thread::setMutualDistinctRanges(SubstitutionBlock *sub_block)
{
  for (size_t i = 2; i <= sub_block->getSize(); i++)
    {
      assert(sub_block->getRange(i)->isObjectVariable());

      ObjectVariable *irange 
	= OBJECT_CAST(ObjectVariable* , sub_block->getRange(i)); 

      assert(irange->getReference() == irange);

      for (size_t j = 1; j < i; j++)
	{
	  assert(sub_block->getRange(j)->isObjectVariable());
   
	  ObjectVariable *jrange 
	    = OBJECT_CAST(ObjectVariable*, sub_block->getRange(j));

	  assert(jrange->getReference() == jrange);
	  
	  setDistinct(irange, jrange);
	}
    }
}

//
// If there is no distinctness information between the object variable
// and a domain, set the object variable to be distinct from the domain.
// Fail, if the object variable is equal to any domain.
// NOTE:
//	ObjectVariable should be dereferenced before this function is called.
//
bool 
Thread::generateDistinction(ObjectVariable *object_variable,
			    Object *sub_block_list)
{
  assert(sub_block_list->isNil() ||
	       (sub_block_list->isCons() &&
		OBJECT_CAST(Cons*, sub_block_list)->isSubstitutionBlockList()));
  assert(object_variable->getReference() == object_variable);
  
  for (Object *s = sub_block_list;
       s->isCons();
       s = OBJECT_CAST(Cons *, s)->getTail())
    {
      assert(OBJECT_CAST(Cons*, s)->getHead()->isSubstitutionBlock());
      SubstitutionBlock *sub_block 
	= OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, s)->getHead());

      for (size_t i = 1; i <= sub_block->getSize(); i++)
	{
	  assert(sub_block->getDomain(i)->isObjectVariable());

	  ObjectVariable *domain 
	    = OBJECT_CAST(ObjectVariable*, 
			  sub_block->getDomain(i)->variableDereference());
	  assert(domain->isObjectVariable());
	  if (object_variable == domain)
	    {
	      return false;
	    }
	  else if (! object_variable->distinctFrom(domain)) 
	    {
	      setDistinct(object_variable, domain);
	    }
	}
    }
  return true;
}


//
// Check objvar is distinct from all the bound variables.
//
bool
Thread::distinctBoundList(ObjectVariable *object_variable, Object *bound_list)
{
  assert(object_variable->variableDereference() == object_variable);
  for (bound_list = bound_list->variableDereference();
       bound_list->isCons();
       bound_list 
	 = OBJECT_CAST(Cons *, bound_list)->getTail()->variableDereference())
    {
      Object *bound
	= OBJECT_CAST(Cons *, bound_list)->getHead()->variableDereference();
  
      assert(bound->isObjectVariable());
      
      ObjectVariable *bound_object_variable = 
	OBJECT_CAST(ObjectVariable *, bound);
      if (object_variable == bound_object_variable)
	{
	  return false;
	}
      else if (! object_variable->distinctFrom(bound_object_variable)) 
	{
	  //
	  // Set them distinct.
	  //
	  setDistinct(object_variable, bound_object_variable);
	}
    }
  
  return true;
}

//
// Ensure the object variables in the bound variable list are mutually
// distinct.
//
bool
Thread::checkBinder(Object *bound_list, Object* so_far)
{
  for (bound_list = bound_list->variableDereference();
       bound_list->isCons();
       bound_list 
	 = OBJECT_CAST(Cons*, bound_list)->getTail()->variableDereference()
       )
    {
      Object *object
	= OBJECT_CAST(Cons*, bound_list)->getHead()->variableDereference();
      
      if (object->isStructure())
	{
	  //
	  // The binder is ObjVar:Term.
	  //
	  assert(OBJECT_CAST(Structure*, object)->getArity() == 2);
	  assert(OBJECT_CAST(Structure*, object)->getFunctor() 
		       == AtomTable::colon);
	  
	  object = OBJECT_CAST(Structure*, object)->getArgument(1)->variableDereference();
	}
	  
      if(!object->isObjectVariable())
	{
          return false;
        }

      
      ObjectVariable *object_variable = 
	OBJECT_CAST(ObjectVariable *, object);
      if (! distinctBoundList(object_variable, so_far))
	{
	  return false;
	}
      
      so_far = heap.newCons(object_variable, so_far);
    }
  if (bound_list->isVariable())
    {
      //
      // Impose the constraint for bound variables.
      //
      Structure *problem = heap.newStructure(2);
      
      problem->setFunctor(AtomTable::checkBinder);
      problem->setArgument(1, bound_list);
      problem->setArgument(2, so_far);
      
      delayProblem(problem, OBJECT_CAST(Reference*, bound_list));
    }
  
  return true;
}











