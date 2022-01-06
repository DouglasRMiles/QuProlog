// heap.cc
//
// Non-inlined functions for the representation of the heap in the
// Qu-Prolog Abstract Machine (QuAM)
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
// $Id: heap.cc,v 1.12 2006/01/31 23:17:50 qp Exp $

// Standard C++ header files


#include <iostream>
#include <stdlib.h>

// Qu-Prolog debugging
#include "debug.h"
#include "int.h"
#include "objects.h"
#include "heap_qp.h"

void Heap::outOfSpace(void)
{
    
      cerr << "Out of " << heapname << " space ("
           << static_cast<qint64>((top - data) * sizeof (heapobject) / K)
           << ")" << endl;
}

//
// Append substitution lists - 'list1' to the right of the
// substitution 'list2'.
// New properties are set.
//
// For example:
//	'first_list' = s1 * s2 * ... * sn 
//	'second_list'  = u1 * u2 * ... * un
//	appendSubstitutionBlockLists = u1 * u2 * ... * un * s1 * s2 * ... * sn
//
Object *
Heap::appendSubstitutionBlockLists(Object *list1,
				   Object *list2)
{
  assert(list1->isNil() ||
	       (list1->isCons() && 
		OBJECT_CAST(Cons*, list1)->isSubstitutionBlockList()));
  assert(list2->isNil() ||
	       (list2->isCons() && 
		OBJECT_CAST(Cons*, list2)->isSubstitutionBlockList()));

  if (list1->isNil()) 
    {
      return list2;
    }
  else if (list2->isNil())
    {
      return list1;
    }
  else
    {
      // Add the rest of substitution.
      Object *copy_list = 
	appendSubstitutionBlockLists(OBJECT_CAST(Cons *, list1)->getTail(),
				     list2);
      
      assert(OBJECT_CAST(Cons*, list1)->getHead()->isSubstitutionBlock());
      return newSubstitutionBlockList(OBJECT_CAST(SubstitutionBlock*, OBJECT_CAST(Cons *, list1)->getHead()), copy_list);
    }
}


//
// copyDistinctnessList merges the distinctness list with the distinctness list
// of the object variable.
//
Object*
Heap::copyDistinctnessList(Object* dist_list, ObjectVariable* obvar)
{
  assert(dist_list->isCons());
  
  Object* dist = obvar->getDistinctness();

  for (; dist_list->isCons(); 
       dist_list = OBJECT_CAST(Cons*, dist_list)->getTail())
    {
      assert(OBJECT_CAST(Cons*, dist_list)->getHead()->variableDereference()->isObjectVariable());
      ObjectVariable* object_variable = OBJECT_CAST(ObjectVariable*, OBJECT_CAST(Cons*, dist_list)->getHead()->variableDereference());

      if (!object_variable->isObjectVariableInDistinctList(obvar))
	{
	  Object* temp = newCons(object_variable, dist);
	  dist = temp;
	}
    }
  assert(dist_list->isNil());
  return(dist);
}


//
// Test if an object is a binding list
//
bool
Heap::isBindingList(Object* o) const
{
  Object* list = o->variableDereference();

  for (;list->isCons();
      list =  OBJECT_CAST(Cons*, list)->getTail()->variableDereference())
    {
      Object* head = 
	OBJECT_CAST(Cons*, list)->getHead()->variableDereference();
      if (!(head->isObjectVariable() || 
	    (head->isStructure() && 
	    OBJECT_CAST(Structure*, head)->getArity() == 2 &&
	    OBJECT_CAST(Structure*, head)->getFunctor() == AtomTable::colon &&
	    OBJECT_CAST(Structure*, head)->getArgument(1)->variableDereference()->isObjectVariable())))
	{
	  return false;
	}
    }
  return (list->isVariable() || list->isNil());
}

//
// newDelay takes a term and a list builds a delay structure and adds the
// new structure to the head of the supplied list. 
// This function has two uses - add a delayed problem to the list of delays
// associated with a variable; and add a new variable to the list of
// variables that have delays.
//
Object *
Heap::newDelay(Object *problem, Object *tail)
{
  assert(tail->isList());

  // Create the status variable, and set to frozen.
  Variable *status = newVariable();
  status->freeze();

  // Create the structure part.
  Structure *structure = newStructure(2);
  structure->setFunctor(AtomTable::comma);
  structure->setArgument(1, status);
  structure->setArgument(2, problem);
  
  return newCons(structure, tail);
}



#ifdef QP_DEBUG
void Heap::printMe(AtomTable& atoms)
{
  const heapobject *pho = data;
  cerr << "---- Heap contents: ----" << endl;
  while (pho < next)
    {
      cerr << "size: " << ((Object *) pho)->size_dispatch() << endl;
      ((Object *) pho)->printMe_dispatch(atoms);
      cerr << endl;
      pho += ((Object *) pho)->size_dispatch();
    }
  assert(pho == next);
  cerr << "----" << endl;
}
#endif


void 
Heap::save(ostream& ostrm) const
{
    const size_t size = next - data;
    //
    // Write out the magic number.
    //
    IntSave<word32>(ostrm,HEAP_MAGIC_NUMBER);
    //
    // Write out the size.
    //
    IntSave<word32>(ostrm, static_cast<const word32>(size));
    //
    // Write out the heap.
    //
    ostrm.write((char*)data, static_cast<std::streamsize>(size * sizeof(heapobject)));
    if (ostrm.fail())
    {
      SaveFailure(__FUNCTION__, "data segment", getAreaName());
    }
}

void 
Heap::load(istream& istrm)
{
    const word32 ReadSize = IntLoad<word32>(istrm);
    if (ReadSize == 0)
      {
	return;
      }

#if 0
    if (ReadSize > allocatedSize())
      {
	//
	// Wrong size.
	//
	FatalS(__FUNCTION__, "wrong size for ", getAreaName());
      }
#endif // 0

    //
    // Read in a segment into the page.
    //

    heapobject* here = next;
    allocateHeapSpace(ReadSize);
#if defined(MACOSX)
    istrm.read((char*)here, ReadSize * sizeof(heapobject));
#else
    if (istrm.good() &&
	istrm.read((char*)here, static_cast<std::streamsize>(ReadSize * sizeof(heapobject))).fail())
      {
	ReadFailure(__FUNCTION__, "data segment", getAreaName());
      }
#endif //defined(MACOSX)

}


//
// Test if this sub block is equal to another.
// Check the domains and ranges in a sub-table.
//
// false and unsure are treated as one group.
//
bool
Heap::fastEqualSubstitutionBlock(SubstitutionBlock *sub_block1,
				 SubstitutionBlock *sub_block2)
{
  if (sub_block1->getSize() != sub_block2->getSize()) 
    {
      return false;
    }

  //
  // Go through the SubstitutionBlock checking both domain and range.
  //	
  for (size_t i = 1; i <= sub_block1->getSize(); i++)
    {
      //
      // Check the domain.
      //
      Object *v1 = sub_block1->getDomain(i)->variableDereference();
      Object *v2 = sub_block2->getDomain(i)->variableDereference();
      if (v1 != v2) 
	{
	  return false;
	}
      
      //
      // Check the range.
      //
      assert(sub_block1->getRange(i)->hasLegalSub());
      assert(sub_block2->getRange(i)->hasLegalSub());
      PrologValue term1(sub_block1->getRange(i));
      PrologValue term2(sub_block2->getRange(i));
      
      if (fastEqual(term1, term2) != true)
	{
	  return false;
	}
    }
  
  return true;
}

//
// fastEqualSubstitution looks at the subsitution, checking the List of subs
// (ie. s1*s2*s3..) are the same length, then traversing down this list again, 
// and calling fastEqualSubstitutionBlock to check each sub.
//
// false and unsure are treated as one group.
// 
bool
Heap::fastEqualSubstitution(Object *sub_block_list1, Object *sub_block_list2)
{
  assert(sub_block_list1->isNil() ||
	       (sub_block_list1->isCons() &&
		OBJECT_CAST(Cons*, sub_block_list1)->isSubstitutionBlockList()));
  assert(sub_block_list2->isNil() ||
	       (sub_block_list2->isCons() &&
		OBJECT_CAST(Cons*, sub_block_list2)->isSubstitutionBlockList()));

  //
  // Quickly run down the list of SubstitutionBlocks, checking we have the same
  // number of them.
  //	
  {
    Object *sbl1;
    Object *sbl2;
    for (sbl1 = sub_block_list1,
	   sbl2 = sub_block_list2;
	 sbl1->isCons() && sbl2->isCons();
	 sbl1 = OBJECT_CAST(Cons *, sbl1)->getTail(),
	   sbl2 = OBJECT_CAST(Cons *, sbl2)->getTail()
	 )
      ;
    
    if (! sbl1->isNil() || ! sbl2->isNil())
      {
	return false;
      } 
  }
  
  //
  // Traverse down the substitution block lists and check each sub block.
  //
  {
    Object *sbl1;
    Object *sbl2;
    for (sbl1 = sub_block_list1,
	   sbl2 = sub_block_list2;
	 sbl1->isCons();
	 sbl1 = OBJECT_CAST(Cons *, sbl1)->getTail(),
	   sbl2 = OBJECT_CAST(Cons *, sbl2)->getTail()
	 )
      {
	assert(OBJECT_CAST(Cons *, sbl1)->getHead()->isSubstitutionBlock());
	assert(OBJECT_CAST(Cons *, sbl2)->getHead()->isSubstitutionBlock());

	SubstitutionBlock *sub_block1 = 
	  OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, sbl1)->getHead());
	SubstitutionBlock *sub_block2 =
	  OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, sbl2)->getHead());
	
	if(! fastEqualSubstitutionBlock(sub_block1, sub_block2))
	  {
	    return false;
	  }
      }
  }
  
  return true;
}

//
// Check the bound variables lists.  If the lists pair up and have the same
// termination, it is true.  Otherwise, it is false.
//
truth3
Heap::fastEqualBoundVariables(Object *bound_var_list1, Object *bound_var_list2)
{
  truth3 result = true;

  Object *bvl1 = bound_var_list1->variableDereference();
  Object *bvl2 = bound_var_list2->variableDereference();
  
  for (;
       bvl1->isCons() && bvl2->isCons();
       bvl1 = OBJECT_CAST(Cons *, bvl1)->getTail()->variableDereference(), 
	 bvl2 = OBJECT_CAST(Cons *, bvl2)->getTail()->variableDereference()
       )
    {
      assert(isBindingList(bvl1));
      assert(isBindingList(bvl2));

      //
      // Get the bound variable.
      //
      Object *bv1 = 
	OBJECT_CAST(Cons *, bvl1)->getHead()->variableDereference();
      Object *bv2 =
	OBJECT_CAST(Cons *, bvl2)->getHead()->variableDereference();
      
      //
      // Match them up.
      //
      if (bv1->isObjectVariable() && bv2->isObjectVariable())
	{
	  if (bv1 != bv2)
	    {
	      result = truth3::UNSURE;
	    }
	  continue;
	}
      else if (bv1->isStructure() && bv2->isStructure())
	{
	  result = result && fastEqualTerm(bv1, bv2);
	}
      else
	{
	  return false;
	}
    }
  
  //
  // Handle the termination of the list.
  //
  return result && (bvl1 == bvl2);
}

//
// Call fastEqual on each part of a quantifier, q x t.
// Recursively calling fastEqual for the quantifiers, bodies and bound
// variables lists.
//
truth3
Heap::fastEqualQuant(Object *quantified_term1, Object *quantified_term2)
{
  assert(quantified_term1->isQuantifiedTerm());
  assert(quantified_term2->isQuantifiedTerm());
  truth3 result = true;

  {
    // Check the quantifiers
    PrologValue 
      quantifier1(OBJECT_CAST(QuantifiedTerm*, quantified_term1)->getQuantifier());
    PrologValue 
      quantifier2(OBJECT_CAST(QuantifiedTerm*, quantified_term2)->getQuantifier());

    result = result && fastEqual(quantifier1, quantifier2);
    if (result == false)
      {
	return false;      
      }
  }
  
  {
    // Body part.
    PrologValue 
      body1(OBJECT_CAST(QuantifiedTerm*,quantified_term1)->getBody());
    PrologValue 
      body2(OBJECT_CAST(QuantifiedTerm*,quantified_term2)->getBody());
    result = result && fastEqual(body1, body2);
    if (result == false)
      {
	return false;      
      }
  }

  //
  // Bound variables lists.
  //
  return(result &&
	 fastEqualBoundVariables(OBJECT_CAST(QuantifiedTerm*,quantified_term1)->getBoundVars(),  OBJECT_CAST(QuantifiedTerm*,quantified_term2)->getBoundVars()));
}

//
// Recursively calling fastEqual for the functors and arguments.
//
truth3
Heap::fastEqualStruct(Object *structure1, Object *structure2)
{
  assert(structure1->isStructure());
  assert(structure2->isStructure());
  //
  // Check arities.
  //
  if (OBJECT_CAST(Structure*, structure1)->getArity() != 
      OBJECT_CAST(Structure*, structure2)->getArity())
    {
      return false;
    }
  
  truth3 result = true;

  {
    //
    // Do a fastEqual on functors.
    //
    PrologValue functor1(OBJECT_CAST(Structure*, structure1)->getFunctor());
    PrologValue functor2(OBJECT_CAST(Structure*, structure2)->getFunctor());
    
    result = result && fastEqual(functor1, functor2);
    
    if (result == false)
      {
	return false;
      }
  }
  
  //
  // Work down arguments, doing fastEqual on each.
  //
  for (size_t n = 1; n <= OBJECT_CAST(Structure*,structure1)->getArity(); n++)
    {
      PrologValue 
	argument1(OBJECT_CAST(Structure*,structure1)->getArgument(n));
      PrologValue 
	argument2(OBJECT_CAST(Structure*,structure2)->getArgument(n));
      result = result && fastEqual(argument1, argument2);

      if (result == false)
	{
	  return false;
	}
    }		

  return(result);
}

//
// Recursively calling fastEqual for the head and tail.
//
truth3
Heap::fastEqualCons(Object *list1, Object *list2)
{
  assert(list1->isCons());
  assert(list2->isCons());

  truth3 result = true;

  {
    //
    // fastEqual for heads.
    //
    PrologValue head1(OBJECT_CAST(Cons*, list1)->getHead());
    PrologValue head2(OBJECT_CAST(Cons*, list2)->getHead());
    result = result && fastEqual(head1, head2);
    
    if (result == false) 
      {
	return false;
      }
  }
  
  //
  // fastEqual for tails.
  //
  {
    PrologValue tail1(OBJECT_CAST(Cons*, list1)->getTail());
    PrologValue tail2(OBJECT_CAST(Cons*, list2)->getTail());

    return(result && fastEqual(tail1, tail2));
  }
}

//
// fastEqualTerm does a pointer comparison of two terms.
//
truth3
Heap::fastEqualTerm(Object *t1, Object *t2)
{
  if (t1 == t2)
    {
      return true;
    }
  
  if (t1->isObjectVariable() || t2->isObjectVariable())
    {
      return(truth3::UNSURE);
    }
  
  if (t1->tTag() != t2->tTag())
    {
      return false;
    }
  
  //
  // The terms are the same type but the pointers are still not equal.
  //
  switch(t1->tTag())
    {
    case Object::tVar:
      //
      // If the previous test didnt work, then fastEqual has failed.
      //
      assert(t1 != t2);
      return false;
      break;
      
    case Object::tStruct:
      //
      // Use fastEqualStruct to test the structures.
      //
      return(fastEqualStruct(t1, t2));
      break; 
      
    case Object::tCons:
      //
      // Use fastEqualList to test the lists.
      //
      return(fastEqualCons(t1, t2));
      break; 
      
    case Object::tQuant:
      //
      // Use fastEqualQuant to test the quantifiers.
      //
      return(fastEqualQuant(t1, t2));
      break;
    case Object::tShort:
    case Object::tAtom:
	{
	  assert(t1 != t2);
	  return(false);
	}
    case Object::tLong:
    case Object::tDouble:
    case Object::tString:
      {
	size_t size = t1->size_dispatch();
	heapobject* ptr1 = reinterpret_cast<heapobject*>(t1);
	heapobject* ptr2 = reinterpret_cast<heapobject*>(t2);
	for (u_int i = 0; i < size; i++)
	  {
	    ptr1++;
	    ptr2++;
	    if (*ptr1 != *ptr2) return false;
	  }
	return true;
      }
      break;
    default:
      assert(false);
    }
  return true;
}

//
// fastEqual does a pointer comparison of two terms to see if they are equal.
//
truth3 Heap::fastEqual(PrologValue& t1, PrologValue& t2)
{
  //
  // Do a variable dereference on the term part. This is done as a quick
  // method before a "full" Dereference.
  //	
  t1.setTerm(t1.getTerm()->variableDereference());
  t2.setTerm(t2.getTerm()->variableDereference());
  
  //
  // Check the pointers.
  //
  if (t1.getSubstitutionBlockList() == t2.getSubstitutionBlockList() &&
      t1.getTerm() == t2.getTerm())
    {
      return true;
    }
      
  prologValueDereference(t1);
  prologValueDereference(t2);
  
  truth3 result = fastEqualTerm(t1.getTerm(), t2.getTerm());

  if (result != true)
    {
      return(result);
    }
  else if (fastEqualSubstitution(t1.getSubstitutionBlockList(), 
				  t2.getSubstitutionBlockList()))
    {
      return true;
    }
  else
    {
      return(truth3::UNSURE);
    }
}


Cons*
Heap::newCons(char* s)
{
  char* c = s;
  assert(*c != '\0');

  Cons* list = newCons();
  Cons* result = list;
  while (true)
    {
      list->setHead(newInteger((int)(*c)));
      c++;
      if (*c == '\0')
        {
          list->setTail(AtomTable::nil);
          break;
        }
      Cons* list_tmp = newCons();
      list->setTail(list_tmp);
      list = list_tmp;
    }
  return result;
}

Object*
Heap::stringToList(char* s)
{
  if (*s == '\0') return AtomTable::nil;
  else return newCons(s);
}

