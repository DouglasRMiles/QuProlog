// copy_term.cc - Functions for copy terms from heap to heap.
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
// $Id: copy_term.cc,v 1.9 2006/01/31 23:17:49 qp Exp $

#include "heap_qp.h"

#include <list>

Object*
Heap::copy_var(Object* source_var,
	       Heap& target_heap, 
	       list<VarRec *>& var_rec_list)
{
  // Determine if we've seen this variable before.
  heapobject* target_loc = NULL;
  // Scan down the list of variable records.
  for (list<VarRec *>::iterator iter = var_rec_list.begin();
       iter != var_rec_list.end();
       iter++)
    {
      if ((*iter)->sourceLoc() == reinterpret_cast<heapobject*>(source_var))
	{
	  target_loc = (*iter)->targetLoc();
	  break;
	}
    }

  // If we haven't seen this variable before...
  if (target_loc == NULL)
    {
      // Record its location in the target heap.
      VarRec *var_rec = new VarRec(reinterpret_cast<heapobject*>(source_var),
				   target_heap.getTop());
      
      var_rec_list.push_back(var_rec);

      Variable* target_var = target_heap.newVariable();
      if (OBJECT_CAST(Variable*, source_var)->isOccursChecked())
	{
	  target_var->setOccursCheck();
	}
      return(target_var);
    }
  else
    {
      assert(reinterpret_cast<Object*>(target_loc)->isVariable());
      return(reinterpret_cast<Object*>(target_loc));
    }
}

Object*
Heap::copy_object_variable(Object* source_object_variable,
			   Heap& target_heap,
			   list<VarRec *>& object_variable_rec_list)
{
  // Determine if we've seen this variable before.
  heapobject* target_loc = NULL;

  // Scan down the list of variable records.
  for (list<VarRec *>::iterator iter = object_variable_rec_list.begin();
       iter != object_variable_rec_list.end();
       iter++)
    {
      if ((*iter)->sourceLoc() == reinterpret_cast<heapobject*>(source_object_variable))
	{
	  target_loc = (*iter)->targetLoc();
	  break;
	}
    }

  // If we haven't seen this variable before...
  if (target_loc == NULL)
    {
      // Record its location in the target heap.
      VarRec *object_variable_rec 
	= new VarRec(reinterpret_cast<heapobject*>(source_object_variable),
		     target_heap.getTop());
      
      object_variable_rec_list.push_back(object_variable_rec);

      return(target_heap.newObjectVariable());

    }
  else
    {
      assert(reinterpret_cast<Object*>(target_loc)->isObjectVariable());
      return(reinterpret_cast<Object*>(target_loc));
    }
}


Object*
Heap::copy_subblock(Object* source_term, Heap& target_heap,
		    list<VarRec *>& var_rec_list,
		    list<VarRec *>& object_variable_rec_list)
{
  assert(source_term->isSubstitutionBlock());
  
  SubstitutionBlock* source_block = OBJECT_CAST(SubstitutionBlock*,
						source_term);
  SubstitutionBlock* target_block
    = target_heap.newSubstitutionBlock(source_block->getSize());

  for (size_t i = 1; i <= source_block->getSize(); i++)
    {
      Object* domain = source_block->getDomain(i)->variableDereference();
      target_block->setDomain(i,
			      copy_object_variable(domain,
						   target_heap,
						   object_variable_rec_list));
      target_block->setRange(i, copy_term(source_block->getRange(i),
					  target_heap,
					  var_rec_list,
					  object_variable_rec_list));
    }
  return(target_block);
}


Object*
Heap::copy_term(Object* source_term, Heap& target_heap,
		list<VarRec *>& var_rec_list,
		list<VarRec *>& object_variable_rec_list)
{

  assert(source_term->variableDereference()->hasLegalSub());
  source_term = dereference(source_term);

  switch(source_term->tTag())
    {
    case Object::tVar:
      return(copy_var(source_term, target_heap, var_rec_list));
      break;

    case Object::tShort:
    case Object::tLong:
    case Object::tDouble:
    case Object::tString:
      {
	size_t size = source_term->size_dispatch();
	heapobject* hcopy = target_heap.allocateHeapSpace(size);
	heapobject* sterm = reinterpret_cast<heapobject*>(source_term);
	Object* res = reinterpret_cast<Object*>(hcopy);
	for (u_int i = 0; i < size; i++)
	  {
	    *hcopy = *sterm;
	    hcopy++;
	    sterm++;
	  }
	return res;
	break;
      }
    case Object::tAtom:
      { 
	return source_term;
	break;
      }

    case Object::tStruct:
      {
	Structure* source_struct = OBJECT_CAST(Structure*, source_term);
	assert(source_struct->getArity() <= MaxArity);
	Structure* target_term
	  = target_heap.newStructure(source_struct->getArity());
	
	heapobject* source_storage = source_term->storage();
	heapobject* target_storage = target_term->storage();

	for (size_t i = 0; i <= source_struct->getArity(); i++)
	  {
	    *target_storage =  reinterpret_cast<heapobject>
	      (copy_term(reinterpret_cast<Object*>(*source_storage),
			 target_heap, 
			 var_rec_list,
			 object_variable_rec_list));
	    target_storage++;
	    source_storage++;
	  }
	return(target_term);
	break;
      }

    case Object::tCons:
      {
	if (OBJECT_CAST(Cons*, source_term)->isSubstitutionBlockList())
	  {
	    //
	    // The list is a substitution block list so make a copy
	    //
	    Cons* target_term = target_heap.newCons();
	    Object** tail_ref = target_term->getTailAddress();
	    target_term->makeSubstitutionBlockList();
	    target_term->setHead(copy_subblock(OBJECT_CAST(Cons*,  source_term)->getHead(),
					       target_heap,
					       var_rec_list,
					       object_variable_rec_list));
	    for (source_term 
		   = dereference(OBJECT_CAST(Cons*, source_term)->getTail());
		 source_term->isCons();
		 source_term 
		   = dereference(OBJECT_CAST(Cons*, source_term)->getTail()))
	      {
		
		Cons* cons = target_heap.newCons();
		cons->makeSubstitutionBlockList();
		cons->setHead(copy_subblock(OBJECT_CAST(Cons*, source_term)->getHead(),
					target_heap,
					var_rec_list, 
					object_variable_rec_list));
		*tail_ref = cons;
		tail_ref = cons->getTailAddress();
	      }
	    assert(source_term == AtomTable::nil);
	    *tail_ref = AtomTable::nil;
	    return(target_term);
	  }
	//
	// A list that is not a substitution block list
	//
	Cons* target_term = target_heap.newCons();
	Object** tail_ref = target_term->getTailAddress();
	target_term->setHead(copy_term(OBJECT_CAST(Cons*, source_term)->getHead(), 
				       target_heap,
				       var_rec_list,
				       object_variable_rec_list));

	
	for (source_term 
	       = dereference(OBJECT_CAST(Cons*, source_term)->getTail());
	     source_term->isCons();
	     source_term 
	       = dereference(OBJECT_CAST(Cons*, source_term)->getTail()))
	  {

	    Cons* cons = target_heap.newCons();
	    cons->setHead(copy_term(OBJECT_CAST(Cons*, source_term)->getHead(),
				    target_heap,
				    var_rec_list, object_variable_rec_list));
	    *tail_ref = cons;
	    tail_ref = cons->getTailAddress();
	  }
	
	*tail_ref = copy_term(source_term,  target_heap,
			      var_rec_list, object_variable_rec_list);
	return(target_term);
	break;
      }

    case Object::tObjVar:
      return(copy_object_variable(source_term, target_heap,
				  object_variable_rec_list));
      break;

    case Object::tSubst:
      {
	Substitution* source_sub = OBJECT_CAST(Substitution*, source_term);
	
	Substitution* target_term = target_heap.newSubstitution();
	target_term->setTerm(copy_term(source_sub->getTerm(),
				       target_heap, var_rec_list,
				       object_variable_rec_list));
	Object* temp = copy_term(source_sub->getSubstitutionBlockList(), 
				 target_heap,
				 var_rec_list,
				 object_variable_rec_list);
        assert(temp->isCons());
	target_term->setSubstitutionBlockList(temp);

	return(target_term);
	break;
      }

    case Object::tQuant:
      {
	QuantifiedTerm* source_quant 
	  = OBJECT_CAST(QuantifiedTerm*, source_term);

	QuantifiedTerm* target_quant = target_heap.newQuantifiedTerm();

	target_quant->setQuantifier(copy_term(source_quant->getQuantifier(),
					      target_heap,
					      var_rec_list,
					      object_variable_rec_list));
	target_quant->setBoundVars(copy_term(source_quant->getBoundVars(),
					     target_heap,
					     var_rec_list,
					     object_variable_rec_list));
	target_quant->setBody(copy_term(source_quant->getBody(),
					target_heap,
					var_rec_list,
					object_variable_rec_list));
	return(target_quant);
	break;
      }


    default:
      assert(false);
      return source_term;
      break;
    }
}


Object*
Heap::copy_share_subblock(Object* source_term, Heap& target_heap,
		    const heapobject* low, const heapobject* high)
{
  assert(source_term->isSubstitutionBlock());
  
  SubstitutionBlock* source_block = OBJECT_CAST(SubstitutionBlock*,
						source_term);
  SubstitutionBlock* target_block
    = target_heap.newSubstitutionBlock(source_block->getSize());

  for (size_t i = 1; i <= source_block->getSize(); i++)
    {
      Object* domain = source_block->getDomain(i)->variableDereference();
      target_block->setDomain(i, domain);
      target_block->setRange(i, copy_share_term(source_block->getRange(i),
						target_heap,
						low, high));
    }
  return(target_block);
}

 
//
// Copy a term to a heap. This function is used by simplify_term to copy
// substitutions from one heap to another. Terms between low and high
// are shared. It is assumed that if a term is between low and high then 
// all its subterms that are either between low and high or do not point
// to any heap (e.g.atoms).
// Low will be set to the base of the heap in which simplification is being
// done. High is set to the top of the heap at the time when simplification
// is called.
//
Object*
Heap::copy_share_term(Object* source_term, Heap& target_heap,
		      const heapobject* low, const heapobject* high)
{

  assert(source_term->variableDereference()->hasLegalSub());
  source_term = dereference(source_term);

#ifndef DEBUG
  if (reinterpret_cast<heapobject*>(source_term) < high &&
      reinterpret_cast<heapobject*>(source_term) >= low)
    {
      return(source_term);
    }
#endif // DEBUG

  //
  // some copying required
  //
  switch(source_term->tTag())
    {
    case Object::tVar:
    case Object::tObjVar:
      assert(reinterpret_cast<heapobject*>(source_term) < high &&
                   reinterpret_cast<heapobject*>(source_term) >= low);
      return(source_term);
      break;
    case Object::tShort:
    case Object::tLong:
    case Object::tDouble:
    case Object::tAtom:
    case Object::tString:
      return(source_term);
      break;

    case Object::tStruct:
      {
	Structure* source_struct = OBJECT_CAST(Structure*, source_term);
	assert(source_struct->getArity() <= MaxArity);
	Structure* target_term
	  = target_heap.newStructure(source_struct->getArity());
	
	heapobject* source_storage = source_term->storage();
	heapobject* target_storage = target_term->storage();

	for (size_t i = 0; i <= source_struct->getArity(); i++)
	  {
	    *target_storage =  reinterpret_cast<heapobject>
	      (copy_share_term(reinterpret_cast<Object*>(*source_storage),
			       target_heap, low, high));

	    target_storage++;
	    source_storage++;
	  }
	return(target_term);
	break;
      }

    case Object::tCons:
      {
	
	if (OBJECT_CAST(Cons*, source_term)->isSubstitutionBlockList())
	  {
	    //
	    // The list is a substitution block list so make a copy
	    //
	    // There should only be one substitution.
	    //
	    Cons* target_term = target_heap.newCons();
	    target_term->makeSubstitutionBlockList();
	    target_term->setHead(copy_share_subblock(OBJECT_CAST(Cons*,  source_term)->getHead(),
					       target_heap,
					       low, high));
  assert(OBJECT_CAST(Cons*, source_term)->getTail()->variableDereference()->hasLegalSub());
	    source_term 
		   = dereference(OBJECT_CAST(Cons*, source_term)->getTail());
		
	    assert(source_term == AtomTable::nil);
	    target_term->setTail(AtomTable::nil);
	    return(target_term);
	  }
	//
	// A list that is not a substitution block list
	//
	Cons* target_term = target_heap.newCons();
	Object** tail_ref = target_term->getTailAddress();
	target_term->setHead(copy_share_term(OBJECT_CAST(Cons*, source_term)->getHead(), 
				       target_heap, low, high));
	
	for (source_term 
	       = dereference(OBJECT_CAST(Cons*, source_term)->getTail());
	     source_term->isCons();
	     source_term 
	       = dereference(OBJECT_CAST(Cons*, source_term)->getTail()))
	  {

	    Cons* cons = target_heap.newCons();
	    cons->setHead(copy_share_term(OBJECT_CAST(Cons*, source_term)->getHead(),
				    target_heap, low, high));
	    *tail_ref = cons;
	    tail_ref = cons->getTailAddress();
	  }
	
	*tail_ref = copy_share_term(source_term,  target_heap, low, high);
	return(target_term);
	break;
      }

    case Object::tSubst:
      {
	Substitution* source_sub = OBJECT_CAST(Substitution*, source_term);
	
	Substitution* target_term = target_heap.newSubstitution();
	target_term->setTerm(copy_share_term(source_sub->getTerm(),
					     target_heap, low, high));
	Object* temp = copy_share_term(source_sub->getSubstitutionBlockList(), 
				       target_heap, low, high);

        assert(temp->isCons());
	target_term->setSubstitutionBlockList(temp);

	return(target_term);
	break;
      }

    case Object::tQuant:
      {
	QuantifiedTerm* source_quant 
	  = OBJECT_CAST(QuantifiedTerm*, source_term);

	QuantifiedTerm* target_quant = target_heap.newQuantifiedTerm();

	target_quant->setQuantifier(copy_share_term(source_quant->getQuantifier(),
						    target_heap, low, high));

	target_quant->setBoundVars(copy_share_term(source_quant->getBoundVars(),
					     target_heap, low, high));

	target_quant->setBody(copy_share_term(source_quant->getBody(),
					target_heap, low, high));

	return(target_quant);
	break;
      }

    default:
      assert(false);
      return source_term;
      break;
    }
}

Object*
Heap::copyTerm(Object* source_term, Heap& target_heap)
{
  list<VarRec *> var_rec_list;
  list<VarRec *> object_variable_rec_list;

  Object* result =  
       copy_term(source_term, target_heap, 
		 var_rec_list, object_variable_rec_list);
  for (list<VarRec *>::iterator iter = var_rec_list.begin();
       iter != var_rec_list.end();
       iter++)
    {
      delete *iter;
    }
  for (list<VarRec *>::iterator iter = object_variable_rec_list.begin();
       iter != object_variable_rec_list.end();
       iter++)
    {
      delete *iter;
    }
  return result;
}

Object*
Heap::copyShareTerm(Object* source_term, Heap& target_heap,
		   const heapobject* low, const heapobject* high)
{
  return (copy_share_term(source_term, target_heap, low, high));
}








