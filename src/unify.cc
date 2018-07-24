// unify.cc - The Qu-Prolog  unify instructions.
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
// $Id: unify.cc,v 1.17 2006/02/06 00:51:38 qp Exp $

// #include "atom_table.h"
#include "global.h"
#include "thread_qp.h"

//
// The following define is used to constract a big switch statement
// in unify for the possible types of the terms being unified.
// !!!WARNING!!! This idea requires that 8 > Object::UOther 
// (the highest tag)
//
#define CrossTag(t1, t2)	(t1 << 3) | (t2 >> 1)

//
// Extend open bound variable list. Extend shorter to match longer one.
// 
BoundVarState
Thread::extendBoundVarListLoop(Object* varSub, Object* variable,
			     Object* listSub, Object* list,
			     Object*& delayedVar,
			     const bool swap, bool in_quant)
{
  assert(variable->isVariable());
  
  list = list->variableDereference();
  if (list->isNil())
    {
      if (unify(variable, list, in_quant))
	{
	  return(MATCH);
	}
      else
	{
	  return(MISMATCH);
	}
    }
  else if (list->isVariable())
    {
      delayedVar = list;
      return(DELAY);
    }
  else
    {
      assert(list->isCons());

      Variable* newTail = heap.newVariable();
      newTail->setOccursCheck();
      BoundVarState state =
	extendBoundVarListLoop(varSub, newTail, listSub,
			       OBJECT_CAST(Cons*, list)->getTail(),
			       delayedVar, swap, in_quant);
      
      Cons* newList = heap.newCons();
      newList->setTail(newTail);

      Object* head = 
	OBJECT_CAST(Cons*, list)->getHead()->variableDereference();
      if (head->isObjectVariable())
	{
	  // 
	  // The corresponding element in the list is an object
	  // variable. Create new list - [ObjectVariable | var1].
	  //
	  ObjectVariable* objectVariable = heap.newObjectVariable();
	  newList->setHead(objectVariable);
	  
	  if (!unify(variable, newList, in_quant))
	    {
	      return (MISMATCH);
	    }

	  if (swap)
	    {
	      pushDownStack.push(head);
	      pushDownStack.push(objectVariable);
	    }
	  else
	    {
	      pushDownStack.push(objectVariable);
	      pushDownStack.push(head);
	    }
	}
      else 
	{
	  assert(head->isStructure());
	  Structure* str = OBJECT_CAST(Structure*, head);
	  assert(str->getArity() == 2 && 
		       str->getFunctor() == AtomTable::colon);
	  
	  //
	  // The corresponding element in the list is a
	  // structure of the form: x : t.  Create structure -
	  // ObjectVariable : var1.
	  //
	  ObjectVariable* objectVariable = heap.newObjectVariable();
	  Variable* type = heap.newVariable();
	  type->setOccursCheck();
	  
	  Structure* term = heap.newStructure(2);
	  term->setFunctor(AtomTable::colon); 
	  term->setArgument(1, objectVariable);
	  term->setArgument(2, type); 
	  newList->setHead(term);
	  //
	  // Get object variables from head.
	  //
	  Object* headObjectVariable 
	    = str->getArgument(1)->variableDereference();
	  assert(headObjectVariable->isObjectVariable());
	  Object* headType = str->getArgument(2);
	  
	  //
	  // Unify term parts
	  // 
          assert(varSub->isLegalSub());
          assert(listSub->isLegalSub());
	  PrologValue t1(varSub, type);
	  PrologValue t2(listSub, headType);
	  heap.prologValueDereference(t1);
	  heap.prologValueDereference(t2);
	  
	  if (!unifyPrologValues(t1, t2, in_quant))
	    {
	      return(MISMATCH);
	    }
	
	  if (!unify(variable, newList, in_quant))
	    {
	      return (MISMATCH);
	    }
	  
	  if (swap)
	    {
	      pushDownStack.push(headObjectVariable);
	      pushDownStack.push(objectVariable);
	    }
	  else
	    {
	      pushDownStack.push(objectVariable);
	      pushDownStack.push(headObjectVariable);
	    }
      	}
      return(state);
    }
}

//
// Pair up bound variable lists.
// quantifier1 = s1 q1 BoundVarList1 term1
// quantifier2 = s2 q2 BoundVarList2 term2
//
BoundVarState
Thread::pairUpBoundVarList(PrologValue& quantifier1, PrologValue& quantifier2,
			 Object*& delayedVar, bool in_quant)
{
  assert(quantifier1.getTerm()->isQuantifiedTerm());
  assert(quantifier1.getTerm()->isQuantifiedTerm());

  Object* boundvars1
    = OBJECT_CAST(QuantifiedTerm*, quantifier1.getTerm())->getBoundVars();
  Object* boundvars2
    = OBJECT_CAST(QuantifiedTerm*, quantifier2.getTerm())->getBoundVars();
  
  for (boundvars1 = boundvars1->variableDereference(),
	 boundvars2 = boundvars2->variableDereference();
       boundvars1->isCons() && boundvars2->isCons() ;
       boundvars1 
	 = OBJECT_CAST(Cons*, boundvars1)->getTail()->variableDereference(),
       boundvars2 
	 = OBJECT_CAST(Cons*, boundvars2)->getTail()->variableDereference())
    {
      Object* head1 
	= OBJECT_CAST(Cons*, boundvars1)->getHead()->variableDereference();
      Object* head2 
	= OBJECT_CAST(Cons*, boundvars2)->getHead()->variableDereference();

      if (head1->isObjectVariable() && head2->isObjectVariable())
	{
	  //
	  // Both, head1 and head2 are object variables.
	  //
	  pushDownStack.push(head1);
	  pushDownStack.push(head2);
	}
      else if (head1->isStructure() && head2->isStructure())
	{
	  assert(OBJECT_CAST(Structure*, head1)->getFunctor()
		       == AtomTable::colon);
	  assert(OBJECT_CAST(Structure*, head1)->getArity() == 2);
	  assert(OBJECT_CAST(Structure*, head2)->getFunctor()
		       == AtomTable::colon);
	  assert(OBJECT_CAST(Structure*, head1)->getArity() == 2);
	  //
	  // head1 is  x : t1,  head2 is  y : t2
	  //
	  
	  //
	  // Push object variables x and y 
	  //
	  pushDownStack.push(OBJECT_CAST(Structure*, head1)->getArgument(1)->variableDereference());
	  pushDownStack.push(OBJECT_CAST(Structure*, head2)->getArgument(1)->variableDereference());
	  
	  //
	  // Unify term parts
	  //
          assert(quantifier1.getSubstitutionBlockList()->isLegalSub());
          assert(quantifier2.getSubstitutionBlockList()->isLegalSub());
	  PrologValue q1(quantifier1.getSubstitutionBlockList(),
			 OBJECT_CAST(Structure*, head1)->getArgument(2));
	  PrologValue q2(quantifier2.getSubstitutionBlockList(),
			 OBJECT_CAST(Structure*, head2)->getArgument(2));
	  heap.prologValueDereference(q1);
	  heap.prologValueDereference(q2);
	  if (!unifyPrologValues(q1, q2, in_quant))
	    {
	      return(MISMATCH);
	    }
	}
      else
	{
	  return(MISMATCH);
	}
    }
  if (boundvars1->isNil() && boundvars2->isNil())
    {
      return(MATCH);
    }
  else if (boundvars1->isVariable() && boundvars2->isVariable())
    {
      delayedVar = boundvars1;
      return(DELAY);
    }
  else if (boundvars1->isVariable())
    {
      //
      // If one bound variable list -  'boundVars1' is open, 
      // in the other words, it is ended with a variable, and 
      // the another - 'boundVars2' is not at the same point,
      // then the open one should be extended.
      //
      return(extendBoundVarListLoop(quantifier1.getSubstitutionBlockList(), 
				    boundvars1, 
				    quantifier2.getSubstitutionBlockList(), 
				    boundvars2,
				    delayedVar, false, in_quant));
    }
  else if (boundvars2->isVariable())
    {
      //
      // Similar to the case before. Because the order of
      // pushing object variables onto the object variable 
      // pair stack is important, and the same function  
      // 'extendBoundVarListLoop' is called the boolean 
      // argument 'swap' is set to true.
      // 
      return(extendBoundVarListLoop(quantifier2.getSubstitutionBlockList(), 
				    boundvars2, 
				    quantifier1.getSubstitutionBlockList(), 
				    boundvars1,
				    delayedVar, true, in_quant));
    }
  else
    {
      return(MISMATCH);
    }
}

//
// Create two parallel substitutions where all ranges are new local
// object variables, and domains are bound object variables from the  
// push down stack. Bound object variables have been stored 
// in the push down stack before, from the bound variable lists of quantified 
// terms. Add the corresponding parallel substitution to the right 
// of term (quantifier) substitution.  
//
void
Thread::makeQuantSubs(Object*& sub1, Object*& sub2, 
		      Object* qsub1, Object* qsub2, int old_size) 
{
  assert(qsub1->isNil() || (qsub1->isCons() &&
	       OBJECT_CAST(Cons*, qsub1)->isSubstitutionBlockList()));
  assert(qsub2->isNil() || (qsub2->isCons() &&
	       OBJECT_CAST(Cons*, qsub2)->isSubstitutionBlockList()));

  bool both_empty = (qsub1->isNil() && qsub2->isNil());
  // 
  // The size of a substitution is the size of 'ob_var_stack'
  // stack divided by 2, because this stack contains object
  // variables for both substitutions.
  // 

  size_t n;

  if (both_empty)
    {
      // Find the length of the sub not counting matching vars
      n = 0;
      for (size_t i = old_size; i < pushDownStack.size(); i += 2)
	{
	  if (pushDownStack.getEntry(static_cast<const StackLoc>(i))->variableDereference() !=
	      pushDownStack.getEntry(static_cast<const StackLoc>(i+1))->variableDereference())
	    {
	      n++;
	    }
	}
      if (n == 0)
	{
          pushDownStack.popNEntries(pushDownStack.size() - old_size);
	  sub1 = qsub1;
	  sub2 = qsub2;
	  return;
	}
    }
  else
    {
      n = (pushDownStack.size() - old_size)/ 2;
    }

  SubstitutionBlock* block1 = heap.newSubstitutionBlock(n);
  SubstitutionBlock* block2 = heap.newSubstitutionBlock(n);

  block1->makeInvertible();
  block2->makeInvertible();
  //
  // Fill domains and ranges.
  //
  for (size_t i = 1; i <= n; )
    {
      Object* o1 = pushDownStack.pop()->variableDereference();
      Object* o2 = pushDownStack.pop()->variableDereference();
      if (both_empty && (o1 == o2))
	{
	  continue;
	}
      ObjectVariable* local = heap.newObjectVariable(); 
      local->makeLocalObjectVariable();
      block2->setDomain(i, OBJECT_CAST(ObjectVariable*, o1));
      block1->setDomain(i, OBJECT_CAST(ObjectVariable*, o2));
      block1->setRange(i, local);
      block2->setRange(i, local);
      i++;
    }
  sub1 = heap.newSubstitutionBlockList(block1, qsub1); 
  sub2 = heap.newSubstitutionBlockList(block2, qsub2);
  assert(sub1->isLegalSub());
  assert(sub2->isLegalSub());
}

//
// Bind variable to a skeletal structure
//
void
Thread::bindToSkelStruct(Object* variable, Object* structure)
{
  assert(variable->isVariable());
  assert(structure->isStructure());

  u_int arity = static_cast<u_int>(OBJECT_CAST(Structure*, structure)->getArity());

  assert(arity <= MaxArity);
  Structure* newStruct = heap.newStructure(arity);

  Variable* funct = heap.newVariable();
  funct->setOccursCheck();

  newStruct->setFunctor(funct);

  for (u_int i = 1; i <= arity; i++)
    {
      //
      // Assign the i-th argument of 
      // the new created structure to 
      // a new variable.
      //
      Variable* arg = heap.newVariable();
      if (OBJECT_CAST(Variable*, variable)->isOccursChecked())
        {
          arg->setOccursCheck();
        }
      newStruct->setArgument(i, arg);
    }
  bind(OBJECT_CAST(Variable*, variable), newStruct);
}

//
// Bind variable to a skeletal list
//
void
Thread::bindToSkelList(Object* variable)
{
  assert(variable->isVariable());
  Variable* head = heap.newVariable();
  Variable* tail = heap.newVariable();
  head->setOccursCheck();
  tail->setOccursCheck();
  Cons* newList = heap.newCons(head, tail);

  //
  // Bind variable to the created list.
  //
  bind(OBJECT_CAST(Variable*, variable), newList);
}

//
// Bind variable to a skeletal quantified term
//
void
Thread::bindToSkelQuant(Object* variable)
{
  assert(variable->isVariable());

  //
  // Create a new quantified term and 
  // assign its quantifier, bound 
  // variable and bound term to new  
  // variables.
  //
  QuantifiedTerm* newQuant = heap.newQuantifiedTerm();
  Variable* q = heap.newVariable();
  Variable* bv = heap.newVariable();
  Variable* b = heap.newVariable();
  q->setOccursCheck();
  bv->setOccursCheck();
  b->setOccursCheck();
  newQuant->setQuantifier(q);
  newQuant->setBoundVars(bv);
  newQuant->setBody(b);

  bind(OBJECT_CAST(Variable*, variable), newQuant);

  //
  // Impose the constraint for bound variables.
  //
  Structure* problem = heap.newStructure(1);
  problem->setFunctor(AtomTable::checkBinder);
  problem->setArgument(1,bv);

  delayProblem(problem, bv);
}

//
// Unify two quantified terms.
//
bool
Thread::unifyQuantifiers(PrologValue& quant1, PrologValue& quant2, 
			 bool in_quant)
{
  assert(quant1.getTerm()->isQuantifiedTerm());
  assert(quant2.getTerm()->isQuantifiedTerm()); 

  Object*	delayedVar;

  //
  // Initialise push down stack.
  //
  // pushDownStack.clear();
  int old_size = pushDownStack.size();
  
  //
  // Both, term and quantifier, are quantified terms.
  // term       = s1 * q1 BoundVarList1 body1
  // quantifier = s2 * q2 BoundVarList2 body2
  //
  
  //
  // Pair up bound variable lists.
  //
  switch (pairUpBoundVarList(quant1, quant2, delayedVar, in_quant))
    {
    case MISMATCH:
      pushDownStack.popNEntries(pushDownStack.size() - old_size);
      return(false);
      break;
      
    case DELAY:
      pushDownStack.popNEntries(pushDownStack.size() - old_size);
      if (!in_quant || balanceLocals(quant1, quant2))
	{
	  //
	  // Unify quantifiers
	  //
	  PrologValue q1(quant1.getSubstitutionBlockList(),
			 OBJECT_CAST(QuantifiedTerm*,quant1.getTerm())->getQuantifier());
	  PrologValue q2(quant2.getSubstitutionBlockList(),
			 OBJECT_CAST(QuantifiedTerm*,quant2.getTerm())->getQuantifier());
	  heap.prologValueDereference(q1);
	  heap.prologValueDereference(q2);

	  if (!unifyPrologValues(q1, q2, in_quant))
	    {
	      return(false);
	    }
	  
	  delayUnify(quant1, quant2, delayedVar);
	}
      else
	{
	  return(false);
	}
      break;
      
    case MATCH:
      //
      // Unify quantifiers
      //
      PrologValue q1(quant1.getSubstitutionBlockList(),
		     OBJECT_CAST(QuantifiedTerm*,quant1.getTerm())->getQuantifier());
      PrologValue q2(quant2.getSubstitutionBlockList(),
		     OBJECT_CAST(QuantifiedTerm*,quant2.getTerm())->getQuantifier());
      heap.prologValueDereference(q1);
      heap.prologValueDereference(q2);

      if (!unifyPrologValues(q1, q2, in_quant))
	{
          pushDownStack.popNEntries(pushDownStack.size() - old_size);
	  return(false);
	}
      //
      // Create substitutions: 
      //	sub1 = s1 * [v1/x1, ..., vn/xn] 
      //	sub2 = s2 * [v1/y1, ..., vn/yn]. 
      // where:
      //	v1, ..., vn are 
      //	new local object variables,
      //	x1, ..., xn are object variables 
      //	from the list BoundVarList1
      //	y1, ..., yn are object variables 
      //	from the list BoundVarList2
      //
      Object *s1, *s2;
      makeQuantSubs(s1, s2, quant1.getSubstitutionBlockList(), 
		    quant2.getSubstitutionBlockList(), old_size);

      //
      // Unify bodies
      // 
      PrologValue b1(s1, OBJECT_CAST(QuantifiedTerm*,quant1.getTerm())->getBody());
      PrologValue b2(s2, OBJECT_CAST(QuantifiedTerm*,quant2.getTerm())->getBody());
      heap.prologValueDereference(b1);
      heap.prologValueDereference(b2);
      if (!unifyPrologValues(b1, b2, true))
	{
	  return(false);
	}
    }
  return(true);
}	


//
// Unify two frozen object variables.
//
bool
Thread::unifyFrozenFrozenObjectVariables(PrologValue& frozenObjectVariable1, 
				      PrologValue& frozenObjectVariable2)
{
  if (frozenObjectVariable1.getSubstitutionBlockList()->isNil() &&
      frozenObjectVariable2.getSubstitutionBlockList()->isNil())
    {
      return(false);
    }
  else
    {
      if (balanceLocals(frozenObjectVariable1, frozenObjectVariable2))
	{
	  delayUnify(frozenObjectVariable1, frozenObjectVariable2,
		     frozenObjectVariable1.getTerm());
	}
      else
	{
	  return(false);
	}
    }
return(true);
}

//
// Unify object variable and non-object variable term.
//
bool
Thread::unifyObjectVariableTerm(PrologValue& objectVariable, PrologValue& term)
{
  if (objectVariable.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, objectVariable);
    }
  switch(term.getTerm()->tTag())
    {
    case Object::tCons:	 
      if (heap.yieldList(term.getTerm(), 
		    objectVariable.getSubstitutionBlockList(), status))
	{
	  if (balanceLocals(objectVariable, term))
	    {
	      delayUnify(objectVariable, term, 
			 objectVariable.getTerm());
	    }
	  else
	    {
	      return(false);
	    }
	}
      else
	{
	  return(false);
	}
      break;
      
    case Object::tStruct:	 
      if (heap.yieldStructure(term.getTerm(), 
			 objectVariable.getSubstitutionBlockList(), 
			 status))
	{
	  if (balanceLocals(objectVariable, term))
	    {
	      delayUnify(objectVariable, term, 
			 objectVariable.getTerm());
	    }
	  else
	    {
	      return(false);
	    }
	}
      else
	{
	  return(false);
	}
      break;
      
    case Object::tShort:	 
    case Object::tLong:	 
    case Object::tDouble:	 
    case Object::tAtom:	 
    case Object::tString:	 
      if (heap.yieldConstant(term.getTerm(), 
			objectVariable.getSubstitutionBlockList(), 
			status))
	{
	  if (balanceLocals(objectVariable, term))
	    {
	      delayUnify(objectVariable, term, 
			 objectVariable.getTerm());
	    }
	  else
	    {
	      return(false);
	    }
	}
      else
	{
	  return(false);
	}
      break;
      
    case Object::tObjVar:
      return  unifyObjectVariables(objectVariable, term);
      break;
    case Object::tQuant:	 
      if (heap.yieldQuantifier(term.getTerm(), 
			  objectVariable.getSubstitutionBlockList(), 
			  status))
	{
	  if (balanceLocals(objectVariable, term))
	    {
	      delayUnify(objectVariable, term, 
			 objectVariable.getTerm());
	    }
	  else
	    {
	      return(false);
	    }
	}
      else
	{
	  return(false);
	}
      break;

    default:
      assert(false);
    }
  return(true); 
}

//
// Unify object variable with another object variable.
// 'ObjectVariable1' has no substitution.
//
bool
Thread::unifyObjectVariableObjectVariable(Object* objectVariable1, 
					  PrologValue& objectVariable2)
{
  assert(objectVariable1->isObjectVariable());
  assert(objectVariable1 == objectVariable1->variableDereference());
  assert(objectVariable2.getTerm()->isObjectVariable());
  assert(objectVariable2.getTerm() == objectVariable2.getTerm()->variableDereference());

  if (heap.yieldObjectVariable(OBJECT_CAST(ObjectVariable*, objectVariable1), 
			  objectVariable2.getSubstitutionBlockList(), 
			  status))
    {	
      PrologValue objectVariable(objectVariable1);
      if (balanceLocals(objectVariable, objectVariable2))
	{
	  delayUnify(objectVariable, objectVariable2, 
		     objectVariable2.getTerm());
	}
      else
	{
	  return(false);
	}
    }
  else if (objectVariable1->distinctFrom(objectVariable2.getTerm()))
    {
      return(false);
    }
  else
    {
      bindObjectVariables(OBJECT_CAST(ObjectVariable*, objectVariable1), 
			  OBJECT_CAST(ObjectVariable*, 
				      objectVariable2.getTerm()));
      objectVariable1 = objectVariable1->variableDereference();
      return(generateDistinction(OBJECT_CAST(ObjectVariable*, objectVariable1),
				 objectVariable2.getSubstitutionBlockList()));
    }
  return(true);
}

//
// Unify two object variables.
//
bool
Thread::unifyObjectVariables(PrologValue& objectVariable1, 
			     PrologValue& objectVariable2)
{
  assert(objectVariable1.getTerm()->isObjectVariable());
  assert(objectVariable2.getTerm()->isObjectVariable());

  if (objectVariable1.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, objectVariable1);
    }
  if (objectVariable2.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, objectVariable2);
    }
  assert(objectVariable2.getTerm()->isObjectVariable());
  if (objectVariable1.getTerm() == objectVariable2.getTerm())
    {
      if(objectVariable1.getSubstitutionBlockList() == 
         objectVariable2.getSubstitutionBlockList())
        {
          return true;
        }

      if (objectVariable1.getSubstitutionBlockList()->isNil() &&
	  ! heap.yieldObjectVariable(objectVariable1.getTerm(),
				objectVariable2.getSubstitutionBlockList(),
				status))
	{
	  return(generateDistinction(OBJECT_CAST(ObjectVariable*, objectVariable1.getTerm()),  objectVariable2.getSubstitutionBlockList()));
	}
      else if (objectVariable2.getSubstitutionBlockList()->isNil() &&
	       !heap.yieldObjectVariable(objectVariable2.getTerm(),
				    objectVariable1.getSubstitutionBlockList(),
				    status))
	{
	  return(generateDistinction(OBJECT_CAST(ObjectVariable*,objectVariable2.getTerm()), objectVariable1.getSubstitutionBlockList()));
	}
      else if (! balanceLocals(objectVariable1, objectVariable2))
	{
	  return(false);
	}
      else if (heap.fastEqual(objectVariable1, objectVariable2) != true)
	{
	  delayUnify(objectVariable1, objectVariable2,
		     objectVariable1.getTerm());
	}
    }
  else if (!status.testHeatWave() && 
	   OBJECT_CAST(ObjectVariable*, objectVariable1.getTerm())->isFrozen() && 
	   OBJECT_CAST(ObjectVariable*, objectVariable2.getTerm())->isFrozen())
    {
      return(unifyFrozenFrozenObjectVariables(objectVariable1,
					      objectVariable2));
    }
  else if (objectVariable1.getSubstitutionBlockList()->isNil() &&
	   objectVariable2.getSubstitutionBlockList()->isNil())
    {
      if (objectVariable1.getTerm()->distinctFrom(objectVariable2.getTerm()))
	{
	  return(false);
	}
      else
	{
	  bindObjectVariables(OBJECT_CAST(ObjectVariable*, objectVariable1.getTerm()), OBJECT_CAST(ObjectVariable*, objectVariable2.getTerm()));
	}
    } 
  else if (objectVariable1.getTerm()->isLocalObjectVariable())
    {
      Object *domElem, *newEnd;
      assert(objectVariable1.getSubstitutionBlockList()->isNil());
      if (! objectVariable1.getTerm()->containLocalObjectVariable(objectVariable2.getSubstitutionBlockList(), domElem, newEnd))
	{
	  return(false);
	}
      else
	{
	  //
	  // Because the last occurrence of the local object 
	  // variable ObjectVariable1.term in the substitution 
	  // ObjectVariable2.sub is as a range element, 
	  // ObjectVariable1.term is replaced with the corresponding 
	  // domain and the ObjectVariable2.sub with the new 
	  // substitution copied from the right up to the one 
	  // where the local object variable is found. 
	  //
	  // ObjectVariable1.term = vk
	  // ObjectVariable2.sub  = s1 * ... * 
	  //	[v1/x1, ... , vk/xk, ... vm/xm] * sj * ... * sn
	  // is transformed to:
	  // ObjectVariable1.term = xk
	  // ObjectVariable2.sub  = sj * ... * sn
	  //
	  objectVariable1.setTerm(domElem);
	  objectVariable2.setSubstitutionBlockList(heap.splitSubstitution(objectVariable2.getSubstitutionBlockList(), newEnd));
	  heap.prologValueDereference(objectVariable1);
	  return(unifyObjectVariables(objectVariable1, objectVariable2));
	}
    }
  else if (objectVariable2.getTerm()->isLocalObjectVariable())
    {
      Object *domElem, *newEnd;
      assert(objectVariable2.getSubstitutionBlockList()->isNil());
      if (! objectVariable2.getTerm()->containLocalObjectVariable(objectVariable1.getSubstitutionBlockList(), domElem, newEnd))
	{
	  return(false);
	}
      else
	{
	  //
	  // Because the last occurrence of the local object 
	  // variable ObjectVariable2.term in the substitution 
	  // ObjectVariable1.sub is as a range element, 
	  // ObjectVariable2.term is replaced with the corresponding 
	  // domain and the ObjectVariable1.sub with the new 
	  // substitution copied from the right up to the one 
	  // where the local object variable is found. 
	  //
	  // ObjectVariable2.term = vk
	  // ObjectVariable1.sub  = s1 * ... * 
	  //	[v1/x1, ... , vk/xk, ... vm/xm] * sj * ... * sn
	  // is transformed to:
	  // ObjectVariable2.term = xk
	  // ObjectVariable1.sub  = sj * ... * sn
	  //
	  objectVariable2.setTerm(domElem);
	  objectVariable1.setSubstitutionBlockList(heap.splitSubstitution(objectVariable1.getSubstitutionBlockList(), newEnd));
	  heap.prologValueDereference(objectVariable2);
	  return(unifyObjectVariables(objectVariable2, objectVariable1));
	}
    }
  else if (objectVariable1.getSubstitutionBlockList()->isNil())
    {
      return(unifyObjectVariableObjectVariable(objectVariable1.getTerm(), 
					       objectVariable2));
    }
  else if (objectVariable2.getSubstitutionBlockList()->isNil())
    {
      return(unifyObjectVariableObjectVariable(objectVariable2.getTerm(), 
					       objectVariable1));
    }
  else if (objectVariable1.getSubstitutionBlockList()->isNil() ||
	   OBJECT_CAST(Cons*, objectVariable1.getSubstitutionBlockList())->isInvertible())
    {
      if (heap.invert(*this, objectVariable1.getSubstitutionBlockList(),
		      objectVariable2))
	{
	  heap.prologValueDereference(objectVariable2);
	  return(unifyObjectVariableObjectVariable(objectVariable1.getTerm(), 
						   objectVariable2));
	}
      else
	{
	  return(false);
	}
    }
  else if (objectVariable2.getSubstitutionBlockList()->isNil() || OBJECT_CAST(Cons*, objectVariable2.getSubstitutionBlockList())->isInvertible())
    {
      if (heap.invert(*this, objectVariable2.getSubstitutionBlockList(), 
		 objectVariable1))
	{
	  heap.prologValueDereference(objectVariable1);
	  return(unifyObjectVariableObjectVariable(objectVariable2.getTerm(), 
						   objectVariable1));
	}
      else
	{
	  return(false);
	}
    }
  else if (balanceLocals(objectVariable1, objectVariable2))
    {
      delayUnify(objectVariable1, objectVariable2, 
		 objectVariable1.getTerm());
    }
  else
    {
      return(false);
    }
  return(true);
}

//
// Unify variables.               
// 
// NOTE: variable1.term must contain the younger variable.
//	 variable1 and variable2 are different.
//
bool
Thread::unifyVariableVariable1(PrologValue& variable1, PrologValue& variable2,
			       bool in_quant)
{
  assert(variable1.getTerm()->isVariable());
  assert(variable2.getTerm()->isVariable());
  assert(variable1.getTerm() != variable2.getTerm());
  assert(reinterpret_cast<void*>(variable1.getTerm()) 
	       >
	       reinterpret_cast<void*>(variable2.getTerm()));
  if (variable1.getSubstitutionBlockList()->isNil() ||
      OBJECT_CAST(Cons*, variable1.getSubstitutionBlockList())->isInvertible())
    {
      if (!heap.invert(*this, variable1.getSubstitutionBlockList(), variable2))
	{
	  return false;
	}
      variable1.setSubstitutionBlockList(AtomTable::nil);
      if (in_quant && !balanceLocals(variable1, variable2))
	{
	  return false;
	}

      Object* simpterm;
      Object* var = variable1.getTerm()->variableDereference();
      if (occursCheckPV(ALL_CHECK, var, variable2, simpterm) == false)
	{
	  if (OBJECT_CAST(Variable*, var)->isOccursChecked())
	    {
	      OBJECT_CAST(Variable*, variable2.getTerm())->setOccursCheck();
	    }
	  bind(OBJECT_CAST(Variable*, var), simpterm);
	  return true;
	}
      else
	{
	  delayUnify(variable1, variable2, var);
	  return true;
	}
    }
  else if (variable2.getSubstitutionBlockList()->isNil() ||
      OBJECT_CAST(Cons*, variable2.getSubstitutionBlockList())->isInvertible())
    {
      if (!heap.invert(*this, variable2.getSubstitutionBlockList(), variable1))
	{
	  return false;
	}
      variable2.setSubstitutionBlockList(AtomTable::nil);
      if (in_quant && !balanceLocals(variable2, variable1))
	{
	  return false;
	}

      Object* simpterm;
      Object* var = variable2.getTerm()->variableDereference();
      if (occursCheckPV(ALL_CHECK, var, variable1, simpterm) == false)
	{
	  if (OBJECT_CAST(Variable*, var)->isOccursChecked())
	    {
	      OBJECT_CAST(Variable*, variable1.getTerm())->setOccursCheck();
	    }
	  bind(OBJECT_CAST(Variable*, var), simpterm);
	  return true;
	}
      else
	{
	  delayUnify(variable2, variable1, var);
	  return true;
	}
    }
  else if (!in_quant || balanceLocals(variable1, variable2))
    {
      delayUnify(variable1, variable2, 
		 variable1.getTerm());
      return true;
    }
  else
    {
      return(false);
    }
  assert(false);
  return true;
}

//
// Unify frozen variable with a variable.               
// Frozen variable behaves like a constant.
// 
bool
Thread::unifyFrozenVariable(PrologValue& frozenVariable, PrologValue& variable,
			    bool in_quant)
{
  assert(frozenVariable.getTerm()->isFrozenVariable());

  if (variable.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, variable);
    }
  if (frozenVariable.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, frozenVariable);
    }

  if (!status.testHeatWave() && variable.getTerm()->isFrozenVariable())
    {
      if (frozenVariable.getTerm() != variable.getTerm())
	{
	  return(false);
	}
      else
	{
	  if (in_quant && ! balanceLocals(frozenVariable, variable))
	    {
	      return(false);
	    }
	  stripUnmatchedSubs(frozenVariable, variable);
	  if (heap.fastEqual(frozenVariable, variable) != true)
	    {
	      delayUnify(frozenVariable, variable, 
			 frozenVariable.getTerm());
	    }
	  return(true);
	}
    }
  else if (frozenVariable.getSubstitutionBlockList()->isNil() &&
	   variable.getSubstitutionBlockList()->isNil())
    {
      bindVariables(OBJECT_CAST(Variable*, frozenVariable.getTerm()), 
		    OBJECT_CAST(Variable*, variable.getTerm()));
      return true;
    }
  else if (variable.getSubstitutionBlockList()->isNil() ||
	   OBJECT_CAST(Cons*, variable.getSubstitutionBlockList())->isInvertible())
    {
      if (!heap.invert(*this, variable.getSubstitutionBlockList(), 
		      frozenVariable))
	{
	  return false;
	}
      variable.setSubstitutionBlockList(AtomTable::nil);
      if (in_quant && !balanceLocals(variable, frozenVariable))
	{
	  return false;
	}

      Object* simpterm;
      if (occursCheckPV(ALL_CHECK, variable.getTerm(), 
			frozenVariable, simpterm) == false)
	{
	  if (OBJECT_CAST(Variable*, variable.getTerm())->isOccursChecked())
	    {
	      OBJECT_CAST(Variable*, frozenVariable.getTerm())->setOccursCheck();
	    }
	  bind(OBJECT_CAST(Variable*, variable.getTerm()->variableDereference()), simpterm);
	  return true;
	}
    }
  if (!in_quant || balanceLocals(variable, frozenVariable))
    {
      delayUnify(variable, frozenVariable, 
		 variable.getTerm());
      return true;
    }
  else
    {
      return(false);
    }
}

//
// Unify two thawed variables.               
// 
bool
Thread::unifyVariableVariable(PrologValue& variable1, PrologValue& variable2,
			      bool in_quant)
{
  if (variable1.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, variable1);
    }
  if (variable2.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, variable2);
    }
  if (variable1.getTerm() == variable2.getTerm()) 
    {
      if (in_quant && ! balanceLocals(variable1, variable2))
	{
	  return(false);
	}
      stripUnmatchedSubs(variable1, variable2);
      if (heap.fastEqual(variable1, variable2) != true)
	{
	  delayUnify(variable1, variable2, variable1.getTerm());
	}
    }
  else if (variable1.getSubstitutionBlockList()->isNil() &&
	   variable2.getSubstitutionBlockList()->isNil())
    {
      bindVariables(OBJECT_CAST(Variable*, variable1.getTerm()), 
		    OBJECT_CAST(Variable*, variable2.getTerm()));
    }
  else if (reinterpret_cast<void*>(variable1.getTerm())
	   < 
	   reinterpret_cast<void*>(variable2.getTerm()))
    {
      return(unifyVariableVariable1(variable2, variable1, in_quant));
    }
  else
    {
      return(unifyVariableVariable1(variable1, variable2, in_quant));
    }
  
  return(true);
}

//
// Unify variable and non-variable term.
//
bool
Thread::unifyVariableTerm(PrologValue& variable, PrologValue& term,
			  bool in_quant)
{
  truth3		flag;
  
  if (!status.testHeatWave() && 
      OBJECT_CAST(Variable*, variable.getTerm())->isFrozen())
    {
      if (term.getTerm()->isObjectVariable())
        {
	  if (term.getSubstitutionBlockList()->isCons())
	    {
	      heap.dropSubFromTerm(*this, term);
	    }
          assert(term.getTerm()->isObjectVariable());
          if (heap.yieldVariable(variable.getTerm(), 
				 term.getSubstitutionBlockList(),
				 status))
	    {
	      if (!in_quant || balanceLocals(variable, term))
	        {
		  delayUnify(variable, term, variable.getTerm());
                  return(true);
	        }
	      else
	        {
	          return(false);
	        }
            }
          else
            {
              return (false);
            }
        }
      else
        {
          return(false);
        }
    }
  //
  // If we are inside a quant unify and the term is a local object variable
  // then the only possible solution is for the variable to be an object 
  // variable and so we bind the variable to a new object variable and
  // attempt the unification again.
  //
  if (in_quant && term.getTerm()->isLocalObjectVariable())
    {
      Object* newobj = heap.newObjectVariable();
      bind(OBJECT_CAST(Variable*, variable.getTerm()->variableDereference()), newobj);
      heap.prologValueDereference(variable);
      return unifyPrologValues(variable, term, in_quant);
    }

  if (variable.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, variable);
    }
  if (variable.getSubstitutionBlockList()->isNil() ||
      OBJECT_CAST(Cons*, variable.getSubstitutionBlockList())->isInvertible())
    {
      if (!heap.invert(*this, variable.getSubstitutionBlockList(), term))
	{ 
	  return false;
	}
      heap.prologValueDereference(term);
      variable.setSubstitutionBlockList(AtomTable::nil);

      Object* simpterm;
      flag = occursCheckPV(ALL_CHECK, variable.getTerm(), term, simpterm);
      if (flag == true)
	{
	  return(false);
	}
      else if (flag == truth3::UNSURE)
	{
	  if (!in_quant || balanceLocals(variable, term))
	    {
	      delayUnify(variable, term, 
			 variable.getTerm());
	      return(true);
	    }
	  else
	    {
	      return false;
	    }
	}
      else
	{
	  if (in_quant && !balanceLocals(variable, term))
	    {
	      return false;
	    }
	  bind(OBJECT_CAST(Variable*, variable.getTerm()->variableDereference()), simpterm);
	  return(true);
	}
    }
  else
    {
      Object* dummy;
      switch(term.getTerm()->tTag())
	{
	case Object::tCons:	 
	  if (heap.yieldList(term.getTerm(), 
			     variable.getSubstitutionBlockList(),
			     status))
	    {
	      if (!in_quant || balanceLocals(variable, term))
		{
		  delayUnify(variable, term, variable.getTerm());
		}
	      else
		{
		  return(false);
		}
	    }
	  else if (occursCheckPV(DIRECT, variable.getTerm(), term, dummy) 
		   == true)
	    {
	      return(false);
	    }
	  else
	    {
	      bindToSkelList(variable.getTerm());
	      heap.prologValueDereference(variable);
	      return(unifyPrologValues(variable, term, in_quant));
	    }
	  break;
	  
	case Object::tStruct:	 
	  if (heap.yieldStructure(term.getTerm(), 
				  variable.getSubstitutionBlockList(),
				  status))
	    {
	      if (!in_quant || balanceLocals(variable, term))
		{
		  delayUnify(variable, term, variable.getTerm());
		}
	      else
		{
		  return(false);
		}
	    }
	  else if (occursCheckPV(DIRECT, variable.getTerm(), term, dummy) 
		   == true)
	    {
	      return(false);
	    }
	  else
	    {
	      bindToSkelStruct(variable.getTerm(), term.getTerm());
	      heap.prologValueDereference(variable);
	      return(unifyPrologValues(variable, term, in_quant));
	    }
	  break;
	  
	case Object::tShort:	 
	case Object::tLong:	 
	case Object::tDouble:	 
	case Object::tAtom:	 
	case Object::tString:	 
	  if (heap.yieldConstant(term.getTerm(), 
				 variable.getSubstitutionBlockList(),
				 status))
	    {
	      if (!in_quant || balanceLocals(variable, term))
		{
		  delayUnify(variable, term, variable.getTerm());
		}
	      else
		{
		  return(false);
		}
	    }
	  else
	    {
	      bind(OBJECT_CAST(Variable*, variable.getTerm()->variableDereference()), 
		   term.getTerm());
	    }
	  break;
	  
	case Object::tObjVar:	 
	  if (term.getTerm()->isLocalObjectVariable())
	    {
	      Object *domElem, *newEnd;
	      if (! term.getTerm()->containLocalObjectVariable(variable.getSubstitutionBlockList(), domElem, newEnd)) 
		{
		  return(false);
		}
	      else
		{
		  //
		  // Because the last occurrence of the 
		  // local object variable term.term
		  // in the substitution variable.sub
		  // is as a range element, term.term
		  // is replaced with the corresponding 
		  // domain and the variable.sub with the 
		  // new substitution copied from the 
		  // right up to the one where the local 
		  // object variable is found. 
		  //
		  // term.term = vk
		  // variable.sub  = s1 * ... * 
		  //	[v1/x1, ... , vk/xk, ... vm/xm]
		  //		* sj * ... * sn
		  // is transformed to:
		  // term.term = xk
		  // variable.sub  = sj * ... * sn
		  //
		  term.setTerm(domElem);
		  variable.setSubstitutionBlockList(
                   heap.splitSubstitution(variable.getSubstitutionBlockList(),
					 newEnd));
		  heap.prologValueDereference(term);
		  heap.prologValueDereference(variable);
		  return(unifyPrologValues(variable, term, in_quant));
		}
	    }
	  else if (term.getSubstitutionBlockList()->isNil())
	    {
	      assert(variable.getTerm() == variable.getTerm()->variableDereference());
	      bind(OBJECT_CAST(Variable*, variable.getTerm()),
		   heap.newObjectVariable());
	      heap.prologValueDereference(variable);
	      return(unifyObjectVariableObjectVariable(term.getTerm(), 
						       variable));
	    }
	  else if (!in_quant || balanceLocals(variable, term))
	    {
	      delayUnify(variable, term, variable.getTerm());
	    }
	  else
	    {
	      return(false);
	    }
	  break;
	  
	case Object::tQuant:	 
	  if (heap.yieldQuantifier(term.getTerm(), 
				   variable.getSubstitutionBlockList(),
				   status))
	    {
	      if (!in_quant || balanceLocals(variable, term))
		{
		  delayUnify(variable, term, variable.getTerm());
		}
	      else
		{
		  return(false);
		}
	    }
	  else if (occursCheckPV(DIRECT, variable.getTerm(), term, dummy) 
		   == true)
	    {
	      return(false);
	    }
	  else
	    {
	      bindToSkelQuant(variable.getTerm());
	      heap.prologValueDereference(variable);
	      return(unifyQuantifiers(variable, term, in_quant));
	    }
	  break;
	  
	default:
	  assert(false);
	}
    }
  
  return(true); 
}

//
// Unify two variables.
//
bool
Thread::unifyVarVar(PrologValue& variable1, PrologValue& variable2, 
		    bool in_quant)
{
  assert(variable1.getTerm()->isVariable());
  assert(variable2.getTerm()->isVariable());

  if (!status.testHeatWave() && 
      OBJECT_CAST(Variable*, variable1.getTerm())->isFrozen())
    {
      return(unifyFrozenVariable(variable1, variable2, in_quant));
    }
  else if (!status.testHeatWave() && 
      OBJECT_CAST(Variable*, variable2.getTerm())->isFrozen())
    {
      return(unifyFrozenVariable(variable2, variable1, in_quant));
    }
  else
    {
      return(unifyVariableVariable(variable1, variable2, in_quant));
    }
}

//
// Unification of two Prolog Values.
// Assumes PrologValue dereference has been done to both terms.
//
bool
Thread::unifyPrologValues(PrologValue& term1, PrologValue& term2, 
			  bool in_quant)
{
  assert(term1.getSubstitutionBlockList()->isLegalSub());
  assert(term2.getSubstitutionBlockList()->isLegalSub());
  if (term1.getTerm() == term2.getTerm() &&
      term1.getSubstitutionBlockList() == term2.getSubstitutionBlockList())
    {
      return(true);
    }

  u_int ut1 = term1.getTerm()->getTag() & Object::UnifyMask;
  u_int ut2 = term2.getTerm()->getTag() & Object::UnifyMask;

  assert((ut1>>1) < 8);
  assert((ut2>>1) < 8);
  switch (CrossTag(ut1, ut2))
    {
      //
      // term1 is a variable
      //
    case CrossTag(Object::UVar, Object::UVar):
    case CrossTag(Object::UVar, Object::UVarOC):
      return(unifyVariableVariable(term1, term2, in_quant));
      break;
    case CrossTag(Object::UVar, Object::UNumber):
    case CrossTag(Object::UVar, Object::UAtom):
    case CrossTag(Object::UVar, Object::UString):
    case CrossTag(Object::UVar, Object::UStruct):
    case CrossTag(Object::UVar, Object::UCons):
    case CrossTag(Object::UVar, Object::UOther):
      if (term2.getTerm()->isVariable())
	return(unifyVarVar(term1, term2, in_quant));
      else
	return(unifyVariableTerm(term1, term2, in_quant));
      break;
      
    case CrossTag(Object::UVarOC, Object::UVar):
    case CrossTag(Object::UVarOC, Object::UVarOC):
      return(unifyVariableVariable(term1, term2, in_quant));
      break;
    case CrossTag(Object::UVarOC, Object::UNumber):
    case CrossTag(Object::UVarOC, Object::UAtom):
    case CrossTag(Object::UVarOC, Object::UString):
    case CrossTag(Object::UVarOC, Object::UStruct):
    case CrossTag(Object::UVarOC, Object::UCons):
    case CrossTag(Object::UVarOC, Object::UOther):
      if (term2.getTerm()->isVariable())
	return(unifyVarVar(term1, term2, in_quant));
      else
	return(unifyVariableTerm(term1, term2, in_quant));
      break;
      
      //
      // term1 is a number
      //
    case CrossTag(Object::UNumber, Object::UVar):
    case CrossTag(Object::UNumber, Object::UVarOC):
      return(unifyVariableTerm(term2, term1, in_quant));
      break;
    case CrossTag(Object::UNumber, Object::UNumber):
      return (term1.getTerm()->equalUninterp(term2.getTerm()));
      break;
    case CrossTag(Object::UNumber, Object::UAtom):
    case CrossTag(Object::UNumber, Object::UString):
    case CrossTag(Object::UNumber, Object::UStruct):
    case CrossTag(Object::UNumber, Object::UCons):
      return false;
      break;
    case CrossTag(Object::UNumber, Object::UOther):
      if (term2.getTerm()->isVariable())
	return(unifyVariableTerm(term2, term1, in_quant));
      if (term2.getTerm()->isObjectVariable())
	return(unifyObjectVariableTerm(term2, term1));
      return false;
      break;
      
      //
      // term1 is an atom
      //
    case CrossTag(Object::UAtom, Object::UVar):
    case CrossTag(Object::UAtom, Object::UVarOC):
      return(unifyVariableTerm(term2, term1, in_quant));
      break;
    case CrossTag(Object::UAtom, Object::UString):
    case CrossTag(Object::UAtom, Object::UNumber):
    case CrossTag(Object::UAtom, Object::UStruct):
    case CrossTag(Object::UAtom, Object::UCons):
      return false;
      break;
    case CrossTag(Object::UAtom, Object::UAtom):
      return false;
      break;
    case CrossTag(Object::UAtom, Object::UOther):
      if (term2.getTerm()->isVariable())
	return(unifyVariableTerm(term2, term1, in_quant));
      if (term2.getTerm()->isObjectVariable())
	return(unifyObjectVariableTerm(term2, term1));
      return false;
      break;

      //
      // term1 is an string
      //
    case CrossTag(Object::UString, Object::UVar):
    case CrossTag(Object::UString, Object::UVarOC):
      return(unifyVariableTerm(term2, term1, in_quant));
      break;
    case CrossTag(Object::UString, Object::UAtom):
    case CrossTag(Object::UString, Object::UNumber):
    case CrossTag(Object::UString, Object::UStruct):
    case CrossTag(Object::UString, Object::UCons):
      return false;
      break;
    case CrossTag(Object::UString, Object::UString):
      return (term1.getTerm()->equalUninterp(term2.getTerm()));
      break;
    case CrossTag(Object::UString, Object::UOther):
      if (term2.getTerm()->isVariable())
	return(unifyVariableTerm(term2, term1, in_quant));
      if (term2.getTerm()->isObjectVariable())
	return(unifyObjectVariableTerm(term2, term1));
      return false;
      break;

      //
      // term1 is a structure
      //
    case CrossTag(Object::UStruct, Object::UVar):
    case CrossTag(Object::UStruct, Object::UVarOC):
      return(unifyVariableTerm(term2, term1, in_quant));
      break;
    case CrossTag(Object::UStruct, Object::UNumber):
    case CrossTag(Object::UStruct, Object::UAtom):
    case CrossTag(Object::UStruct, Object::UString):
    case CrossTag(Object::UStruct, Object::UCons):
      return false;
      break;
    case CrossTag(Object::UStruct, Object::UStruct):
      {
	Structure* struct1 = OBJECT_CAST(Structure*, term1.getTerm());
	Structure* struct2 = OBJECT_CAST(Structure*, term2.getTerm());
	u_int arity = static_cast<int>(struct1->getArity());
	if (arity != struct2->getArity())
	  {
	    return(false);
	  }
	PrologValue funct1(term1.getSubstitutionBlockList(), 
			   struct1->getFunctor());
	PrologValue funct2(term2.getSubstitutionBlockList(), 
			   struct2->getFunctor());
	heap.prologValueDereference(funct1);
	heap.prologValueDereference(funct2);
	if (!unifyPrologValues(funct1, funct2, in_quant))
	  {
	    return(false);
	  }
      
	for (u_int i = 1; i <= arity; i++)
	  {
	    PrologValue arg1(term1.getSubstitutionBlockList(), 
			     struct1->getArgument(i));
	    PrologValue arg2(term2.getSubstitutionBlockList(), 
			     struct2->getArgument(i));

	    heap.prologValueDereference(arg1);
	    heap.prologValueDereference(arg2);
	    if (!unifyPrologValues(arg1, arg2, in_quant))
	      {
		return(false);
	      }
	  }
	break;
      }
    case CrossTag(Object::UStruct, Object::UOther):
      if (term2.getTerm()->isVariable())
	return(unifyVariableTerm(term2, term1, in_quant));
      if (term2.getTerm()->isObjectVariable())
	return(unifyObjectVariableTerm(term2, term1));
      return false;
      break;


      //
      // term1 is a cons
      //
    case CrossTag(Object::UCons, Object::UVar):
    case CrossTag(Object::UCons, Object::UVarOC):
      return(unifyVariableTerm(term2, term1, in_quant));
      break;
    case CrossTag(Object::UCons, Object::UNumber):
    case CrossTag(Object::UCons, Object::UAtom):
    case CrossTag(Object::UCons, Object::UStruct):
    case CrossTag(Object::UCons, Object::UString):
      return false;
      break;

    case CrossTag(Object::UCons, Object::UCons):
       {
	Cons* list1 = OBJECT_CAST(Cons*, term1.getTerm());
	Cons* list2 = OBJECT_CAST(Cons*, term2.getTerm());
	PrologValue head1(term1.getSubstitutionBlockList(), list1->getHead());
	PrologValue head2(term2.getSubstitutionBlockList(), list2->getHead());
	heap.prologValueDereference(head1);
	heap.prologValueDereference(head2);
	if (!unifyPrologValues(head1, head2, in_quant))
	  {
	    return(false);
	  }
	PrologValue tail1(term1.getSubstitutionBlockList(), list1->getTail());
	PrologValue tail2(term2.getSubstitutionBlockList(), list2->getTail());
	heap.prologValueDereference(tail1);
	heap.prologValueDereference(tail2);
	return (unifyPrologValues(tail1, tail2, in_quant));
	break;
      }

    case CrossTag(Object::UCons, Object::UOther):
      if (term2.getTerm()->isVariable())
	return(unifyVariableTerm(term2, term1, in_quant));
      if (term2.getTerm()->isObjectVariable())
	return(unifyObjectVariableTerm(term2, term1));
      return false;
      break;


      //
      // term1 is an other type {obvar quant var}
      //
    case CrossTag(Object::UOther, Object::UVar):
    case CrossTag(Object::UOther, Object::UVarOC):
      if (term1.getTerm()->isVariable())
	return(unifyVarVar(term1, term2, in_quant));
      else
	return(unifyVariableTerm(term2, term1, in_quant));
      break;
    case CrossTag(Object::UOther, Object::UNumber):
    case CrossTag(Object::UOther, Object::UAtom):
    case CrossTag(Object::UOther, Object::UString):
    case CrossTag(Object::UOther, Object::UStruct):
    case CrossTag(Object::UOther, Object::UCons):
      if (term1.getTerm()->isVariable())
	return(unifyVariableTerm(term1, term2, in_quant));
      if (term1.getTerm()->isObjectVariable())
	return(unifyObjectVariableTerm(term1, term2));
      return false;
      break;
    case CrossTag(Object::UOther, Object::UOther):
      if (term1.getTerm()->isVariable()) {
	if (term2.getTerm()->isVariable())
	  return unifyVarVar(term1, term2, in_quant);
	else
	  return(unifyVariableTerm(term1, term2, in_quant));
      }
      if (term2.getTerm()->isVariable())
	return(unifyVariableTerm(term2, term1, in_quant));
      if (term1.getTerm()->isObjectVariable()) {
	if (term2.getTerm()->isObjectVariable())
	  return unifyObjectVariables(term1, term2);
	else
	  return(unifyObjectVariableTerm(term1, term2));
      }
      if (term2.getTerm()->isObjectVariable())
	return(unifyObjectVariableTerm(term2, term1));
      assert(term1.getTerm()->isQuantifiedTerm());
      assert(term2.getTerm()->isQuantifiedTerm());
      return(unifyQuantifiers(term1, term2, in_quant));
      break;

    default:
      assert(false);
      return(false);
    }
  return(true);
}

inline bool
Thread::unifyAsPrologValues(Object* term1, Object* term2, bool in_quant)
{
  PrologValue pterm1(term1);
  PrologValue pterm2(term2);
  heap.prologValueDereference(pterm1);
  heap.prologValueDereference(pterm2);
  return(unifyPrologValues(pterm1, pterm2, in_quant));
}

bool
Thread::unifyOtherConst(Object* term1, Object* term2, bool in_quant)
{
  if (term1->isVariable())
    {
      Variable* var1 = OBJECT_CAST(Variable*, term1);

      if (var1->isThawed() || status.testHeatWave())
	{
	  Variable* var1 = OBJECT_CAST(Variable*, term1);
	  bind(var1, term2);
	  return true;
	}
      else
	{
	  return false;
	}
    }
  if (term1->isSubstitution())
    {
      return unifyAsPrologValues(term1, term2, in_quant);
    }
  return false;
}

bool
Thread::unifyOtherTerm(Object* term1, Object* term2, bool in_quant)
{
  if (term1->isVariable())
    {
      Variable* var1 = OBJECT_CAST(Variable*, term1);

      if (var1->isThawed() || status.testHeatWave())
	{
	  return unifyOtherVarTerm(term1, term2, in_quant);
	}
      else
	{
	  return false;
	}
    }
  if (term1->isSubstitution())
    {
      return unifyAsPrologValues(term1, term2, in_quant);
    }
  return false;
}

inline bool 
Thread::unifyVarOCTerm(Object* term1, Object* term2, bool in_quant)
{
  assert(term1->isVariable());
  Variable* var1 = OBJECT_CAST(Variable*, term1);
  Object* simpterm;
  truth3 flag = occursCheck(ALL_CHECK, var1, term2, simpterm);
  if (flag == false)
    {
      if (simpterm->isVariable())
	{
	  Variable* simpvar = OBJECT_CAST(Variable*, simpterm);
	  bindVariables(var1, simpvar);
	}
      else
	{
	  assert(!OBJECT_CAST(Reference*, var1)->hasExtraInfo());
	  bindAndTrail(var1, simpterm);
	}
    }
  else if (flag == true)
    {
      return(false);
    } 
  else
    {
      return unifyAsPrologValues(term1, term2, in_quant);
    }
  return(true);
}

inline bool 
Thread::unifyOtherVarTerm(Object* term1, Object* term2, bool in_quant)
{
  assert(term1->isVariable());
  Variable* var1 = OBJECT_CAST(Variable*, term1);
  Object* simpterm;
  truth3 flag = occursCheck(ALL_CHECK, var1, term2, simpterm);
  if (flag == false)
    {
      if (simpterm->isVariable())
	{
	  Variable* simpvar = OBJECT_CAST(Variable*, simpterm);
	  bindVariables(var1, simpvar);
	}
      else
	{
	  bind(var1, simpterm);
	}
    }
  else if (flag == true)
    {
      return(false);
    } 
  else
    {
      return unifyAsPrologValues(term1, term2, in_quant);
    }
  return(true);
}



//
// General unify algorithm. 
//
bool
Thread::unify(Object* term1, Object* term2, bool in_quant) 

#ifdef OBJECT_OVERRIDES
{

  bool* result = new bool();
  if(term1->Unify(term2, in_quant, *result)) {
    return *result;
  }
  if(term2->Unify(term1, in_quant, *result)) {
    return *result;
  }
  return unify_Original(term1, term2, in_quant);
}

bool
Object::OverridesUnify(Object* o2, bool in_quant, bool &result) 
{
  result = false;
  return false;
}

bool
Thread::unify_Original(Object* term1, Object* term2, bool in_quant) 
#endif 

{
  
  //
  // Do the full dereference.
  //
  assert(term1->variableDereference()->hasLegalSub());
  assert(term2->variableDereference()->hasLegalSub());
  term1 = heap.dereference(term1);
  term2 = heap.dereference(term2);
  if (term1 == term2)
    {
      return(true);
    }
  //
  // At this point the terms are different.
  //
  u_int ut1 = term1->getTag() & Object::UnifyMask;
  u_int ut2 = term2->getTag() & Object::UnifyMask;

  assert((ut1>>1) < 8);
  assert((ut2>>1) < 8);
  switch (CrossTag(ut1, ut2))
    {
      //
      // term1 is a variable
      //
    case CrossTag(Object::UVar, Object::UVar):
      assert(!OBJECT_CAST(Reference*, term2)->hasExtraInfo());
      bindVarVar(term1, term2);
      return(true);
      break;
    case CrossTag(Object::UVar, Object::UVarOC):
      bindAndTrail(term1, term2);
      return(true);
      break;
    case CrossTag(Object::UVar, Object::UNumber):
    case CrossTag(Object::UVar, Object::UAtom):
    case CrossTag(Object::UVar, Object::UString):
    case CrossTag(Object::UVar, Object::UStruct):
    case CrossTag(Object::UVar, Object::UCons):
    case CrossTag(Object::UVar, Object::UOther):
      assert(!OBJECT_CAST(Reference*, term1)->hasExtraInfo());
      bindAndTrail(term1, term2);
      return(true);
      break;

      //
      // term1 is a variable with OC set
      //
    case CrossTag(Object::UVarOC, Object::UVar):
      bindAndTrail(term2, term1);
      return(true);
      break;
    case CrossTag(Object::UVarOC, Object::UVarOC):
      assert(!OBJECT_CAST(Reference*, term2)->hasExtraInfo());
      bindVarVar(term1, term2);
      return(true);
      break;
    case CrossTag(Object::UVarOC, Object::UNumber):
    case CrossTag(Object::UVarOC, Object::UAtom):
    case CrossTag(Object::UVarOC, Object::UString):
      bindAndTrail(term1, term2);
      return(true);
      break;
    case CrossTag(Object::UVarOC, Object::UStruct):
    case CrossTag(Object::UVarOC, Object::UCons):
    case CrossTag(Object::UVarOC, Object::UOther):
      return unifyVarOCTerm(term1, term2, in_quant);
      break;

      //
      // term1 is a number
      //
    case CrossTag(Object::UNumber, Object::UVar):
    case CrossTag(Object::UNumber, Object::UVarOC):
      bindAndTrail(term2, term1);
      return(true);
      break;
    case CrossTag(Object::UNumber, Object::UNumber):
      return term1->equalUninterp(term2);
      break;
    case CrossTag(Object::UNumber, Object::UAtom):
    case CrossTag(Object::UNumber, Object::UString):
    case CrossTag(Object::UNumber, Object::UStruct):
    case CrossTag(Object::UNumber, Object::UCons):
      return(false);
      break;
    case CrossTag(Object::UNumber, Object::UOther):
      return unifyOtherConst(term2, term1, in_quant);
      break;
      //
      // term1 is an atom
      //
    case CrossTag(Object::UAtom, Object::UVar):
    case CrossTag(Object::UAtom, Object::UVarOC):
      bindAndTrail(term2, term1);
      return(true);
      break;
    case CrossTag(Object::UAtom, Object::UString):
    case CrossTag(Object::UAtom, Object::UNumber):
    case CrossTag(Object::UAtom, Object::UAtom):
    case CrossTag(Object::UAtom, Object::UStruct):
    case CrossTag(Object::UAtom, Object::UCons):
      return(false);
      break;
    case CrossTag(Object::UAtom, Object::UOther):
      return unifyOtherConst(term2, term1, in_quant);
      break;

      //
      // term1 is an string
      //
    case CrossTag(Object::UString, Object::UVar):
    case CrossTag(Object::UString, Object::UVarOC):
      bindAndTrail(term2, term1);
      return(true);
      break;
    case CrossTag(Object::UString, Object::UAtom):
    case CrossTag(Object::UString, Object::UNumber):
    case CrossTag(Object::UString, Object::UStruct):
    case CrossTag(Object::UString, Object::UCons):
      return(false);
      break;
    case CrossTag(Object::UString, Object::UString):
      return (term1->equalUninterp(term2));
      break;
    case CrossTag(Object::UString, Object::UOther):
      return unifyOtherTerm(term2, term1, in_quant);
      break;

      //
      // term1 is a structure
      //
    case CrossTag(Object::UStruct, Object::UVar):
      assert(!OBJECT_CAST(Reference*, term2)->hasExtraInfo());
      bindAndTrail(term2, term1);
      return(true);
      break;
    case CrossTag(Object::UStruct, Object::UVarOC):
      return unifyVarOCTerm(term2, term1, in_quant);
      break;
    case CrossTag(Object::UStruct, Object::UNumber):
    case CrossTag(Object::UStruct, Object::UAtom):
    case CrossTag(Object::UStruct, Object::UString):
    case CrossTag(Object::UStruct, Object::UCons):
      return(false);
      break;
    case CrossTag(Object::UStruct, Object::UStruct):
      {
	Structure* struct1 = OBJECT_CAST(Structure*, term1);
	Structure* struct2 = OBJECT_CAST(Structure*, term2);
	
	u_int arity = static_cast<int>(struct1->getArity());
	if (arity != struct2->getArity())
	  {
	    return(false);
	  }
	Object* funct1 = struct1->getFunctor();
	Object* funct2 = struct2->getFunctor();
	if ((funct1 != funct2) && !unify(funct1, funct2, in_quant))
	  {
	    return(false);
	  }
	for (u_int i = 1; i <= arity; i++)
	  {
	    if (!unify(struct1->getArgument(i), 
		       struct2->getArgument(i), in_quant))
	      {
		return(false);
	      }
	  }
	return(true);
	break;
      }

    case CrossTag(Object::UStruct, Object::UOther):
      return unifyOtherTerm(term2, term1, in_quant);
      break;

      //
      // term1 is a cons
      //
    case CrossTag(Object::UCons, Object::UVar):
      bindAndTrail(term2, term1);
      return(true);
      break;
     case CrossTag(Object::UCons, Object::UVarOC):
      return unifyVarOCTerm(term2, term1, in_quant);
      break;
    case CrossTag(Object::UCons, Object::UNumber):
    case CrossTag(Object::UCons, Object::UAtom):
    case CrossTag(Object::UCons, Object::UStruct):
    case CrossTag(Object::UCons, Object::UString):
      return(false);
      break;
    case CrossTag(Object::UCons, Object::UCons):
      {
	Cons* list1 = OBJECT_CAST(Cons*, term1);
	Cons* list2 = OBJECT_CAST(Cons*, term2);
	return (unify(list1->getHead(), list2->getHead(), in_quant) &&
		unify(list1->getTail(), list2->getTail(), in_quant));
	break;
      }
    case CrossTag(Object::UCons, Object::UOther):
      return unifyOtherTerm(term2, term1, in_quant);
      break;

      //
      // term1 is other {sub, obvar, quant, other_var}
      //
    case CrossTag(Object::UOther, Object::UVar):
      bindAndTrail(term2, term1);
      return(true);
      break;
    case CrossTag(Object::UOther, Object::UVarOC):
      return unifyVarOCTerm(term2, term1, in_quant);
      break;
    case CrossTag(Object::UOther, Object::UNumber):
    case CrossTag(Object::UOther, Object::UAtom):
      return unifyOtherConst(term1, term2, in_quant);
      break;
    case CrossTag(Object::UOther, Object::UString):
    case CrossTag(Object::UOther, Object::UStruct):
    case CrossTag(Object::UOther, Object::UCons):
      return unifyOtherTerm(term1, term2, in_quant);
      break;
    case CrossTag(Object::UOther, Object::UOther):
      {
	return unifyAsPrologValues(term1, term2, in_quant);
	break;
      }

    default:
#ifndef NDEBUG
      cerr << "Unmatched case in unify" << endl;
      term1->printMe_dispatch(*atoms);
      term2->printMe_dispatch(*atoms);
#endif
      assert(false);
      return(false);
    }
  assert(false);
  return(false);
}

bool
Thread::structuralUnifySubs(Object* sub1, Object* sub2)
{
  for ( ;
	sub1->isCons() && sub2->isCons();
	sub1 = OBJECT_CAST(Cons *, sub1)->getTail(),
	  sub2 = OBJECT_CAST(Cons *, sub2)->getTail())
    {
      assert(OBJECT_CAST(Cons *, sub1)->getHead()->isSubstitutionBlock());
      assert(OBJECT_CAST(Cons *, sub2)->getHead()->isSubstitutionBlock());
      SubstitutionBlock* b1 = 
	OBJECT_CAST(SubstitutionBlock*,
		    OBJECT_CAST(Cons *, sub1)->getHead());
      SubstitutionBlock* b2 = 
	OBJECT_CAST(SubstitutionBlock*,
		    OBJECT_CAST(Cons *, sub2)->getHead());
      if (b1->getSize() != b2->getSize())
	{
	  return false;
	}
      for (size_t i = 1; i <= b1->getSize(); i++)
	{
	  PrologValue dom1(b1->getDomain(i));
	  PrologValue dom2(b2->getDomain(i));
	  PrologValue ran1(b1->getRange(i));
	  PrologValue ran2(b2->getRange(i));
	  if (!structuralUnify(dom1,dom2)
	      || !structuralUnify(ran1,ran2))
	    {
	      return false;
	    }
	}
    }
  return (sub1->isNil() && sub2->isNil());
}

bool
Thread::structuralUnifyVarVar(PrologValue& term1, PrologValue& term2)
{
  assert(term1.getTerm()->isVariable());
  assert(term2.getTerm()->isVariable());

  if (term1.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, term1);
    }
  if (term2.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, term2);
    }
  
  Object* sub1 = term1.getSubstitutionBlockList();
  Object* sub2 = term2.getSubstitutionBlockList();
  Object* t1 = term1.getTerm();
  Object* t2 = term2.getTerm();
  
  Variable* var1 = OBJECT_CAST(Variable*, t1);
  Variable* var2 = OBJECT_CAST(Variable*, t2);
  
  // Walk through the subs
  int size1 = 0;
  for ( ;
	sub1->isCons();
	sub1 = OBJECT_CAST(Cons *, sub1)->getTail() ) size1++;

  int size2 = 0;
  for ( ;
	sub2->isCons();
	sub2 = OBJECT_CAST(Cons *, sub2)->getTail() ) size2++;


  // sub2 is longer than sub1
  if (size2 > size1)
    {
      if (var1->isFrozen() && !status.testHeatWave())
	{
	  return(false);
	}
      Object* newsub = 
	heap.copySubSpineN(term2.getSubstitutionBlockList(), size2 - size1);

      assert(newsub->isCons());
      Object* newterm = heap.newSubstitution(newsub,t2);
      
      Object* simpterm;
      truth3 flag = occursCheck(ALL_CHECK, var1, newterm, simpterm);
      if (flag == false)
	{
	  bind(var1, simpterm);
	}
      else
	{
	  return(false);
	}
      heap.prologValueDereference(term1);
    }
  // sub1 is longer than sub2
  else if (size1 > size2)
    {
      if (var2->isFrozen() && !status.testHeatWave())
	{
	  return(false);
	}
      Object* newsub =
	heap.copySubSpineN(term1.getSubstitutionBlockList(), size1 - size2);

      assert(newsub->isCons());
      Object* newterm = heap.newSubstitution(newsub,t1);
      
      Object* simpterm;
      truth3 flag = occursCheck(ALL_CHECK, var2, newterm, simpterm);
      if (flag == false)
	{
	  bind(var2, simpterm);
	}
      else
	{
	  return(false);
	}
      heap.prologValueDereference(term2);
    }
  else
    {
      assert(size1 == size2);
      if (term1.getTerm() != term2.getTerm())
	{
	  if (var1->isFrozen() && var2->isFrozen() && !status.testHeatWave())
	    {
	      return(false);
	    }
	  bindVariables(var1, var2);
	  heap.prologValueDereference(term1);
	  heap.prologValueDereference(term2);
	}
    }
  
  assert(term1.getTerm() == term2.getTerm());
  sub1 = term1.getSubstitutionBlockList();
  sub2 = term2.getSubstitutionBlockList();
  return structuralUnifySubs(sub1, sub2);
}

bool
Thread::structuralUnifyVarQuantifier(PrologValue& term1, PrologValue& term2)
{
  assert(term1.getTerm()->isVariable());
  assert(term2.getTerm()->isQuantifiedTerm());

  Object* t1 = term1.getTerm();
  Variable* var1 = OBJECT_CAST(Variable*, t1);
  if (var1->isFrozen() && !status.testHeatWave())
    {
      return(false);
    }

  if (term1.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, term1);
    }
  if (term2.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, term2);
    }
  
  Object* sub1 = term1.getSubstitutionBlockList();
  Object* sub2 = term2.getSubstitutionBlockList();
  Object* t2 = term2.getTerm();
  
  
  // Walk through the subs
  int size1 = 0;
  for ( ;
	sub1->isCons();
	sub1 = OBJECT_CAST(Cons *, sub1)->getTail() ) size1++;

  int size2 = 0;
  for ( ;
	sub2->isCons();
	sub2 = OBJECT_CAST(Cons *, sub2)->getTail() ) size2++;


  // sub2 is longer than sub1
  if (size2 > size1)
    {


      Object* newsub = 
	heap.copySubSpineN(term2.getSubstitutionBlockList(), size2 - size1);

      assert(newsub->isCons());
      Object* newterm = heap.newSubstitution(newsub,t2);
      
      Object* simpterm;
      truth3 flag = occursCheck(ALL_CHECK, var1, newterm, simpterm);
      if (flag == false)
	{
	  QuantifiedTerm* newQuant = heap.newQuantifiedTerm();
	  Variable* q = heap.newVariable();
	  Variable* bv = heap.newVariable();
	  Variable* b = heap.newVariable();
	  q->setOccursCheck();
	  bv->setOccursCheck();
	  b->setOccursCheck();
	  newQuant->setQuantifier(q);
	  newQuant->setBoundVars(bv);
	  newQuant->setBody(b);
	  Object* skelterm = heap.newSubstitution(newsub,newQuant);

	  bind(var1, skelterm);
	  return structuralUnify(term1, term2);
	}
      else
	{
	  return(false);
	}
    }
  // sub1 is longer than sub2
  else if (size1 > size2)
    {
      return false;
     }
  else
    {
      assert(size1 == size2);
      bindToSkelQuant(var1);
      return structuralUnify(term1, term2);
    }
}


bool
Thread::structuralUnifyVarStruct(PrologValue& term1, PrologValue& term2)
{
  assert(term1.getTerm()->isVariable());
  assert(term2.getTerm()->isStructure());

  Object* t1 = term1.getTerm();
  Variable* var1 = OBJECT_CAST(Variable*, t1);
  if (var1->isFrozen() && !status.testHeatWave())
    {
      return(false);
    }
  if (term1.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, term1);
    }
  Object* simpterm;
  truth3 flag = occursCheck(ALL_CHECK, var1,
			    heap.prologValueToObject(term2), simpterm);
  if (flag == false)
    {
      if (term1.getSubstitutionBlockList()->isCons())
	{
	  bindToSkelStruct(var1, term2.getTerm());
	  return structuralUnify(term1, term2);
	}
      else
	{
	  bind(var1, simpterm);
	  return(true);
	}
    }
  else
    {
      return(false);
    }
}

bool
Thread::structuralUnifyVarCons(PrologValue& term1, PrologValue& term2)
{
  assert(term1.getTerm()->isVariable());
  assert(term2.getTerm()->isCons());

  Object* t1 = term1.getTerm();
  Variable* var1 = OBJECT_CAST(Variable*, t1);
  if (var1->isFrozen() && !status.testHeatWave())
    {
      return(false);
    }
  if (term1.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, term1);
    }
  Object* simpterm;
  truth3 flag = occursCheck(ALL_CHECK, var1,
			    heap.prologValueToObject(term2), simpterm);
  if (flag == false)
    {
      if (term1.getSubstitutionBlockList()->isCons())
	{
	  bindToSkelList(var1);
	  return structuralUnify(term1, term2);
	}
      else
	{
	  bind(var1, simpterm);
	  return(true);
	}
    }
  else
    {
      return(false);
    }
}

inline bool
Thread::structuralUnifyVarConst(PrologValue& term1, PrologValue& term2)
{
  assert(term1.getTerm()->isVariable());
  Variable* var1 = OBJECT_CAST(Variable*, term1.getTerm());
  if (var1->isFrozen() && !status.testHeatWave())
    {
      return(false);
    }
  bind(var1, term2.getTerm());
  return(true);
}

inline bool
Thread::structuralUnifyObjVarObjVar(PrologValue& term1, PrologValue& term2)
{
  assert(term1.getTerm()->isObjectVariable());
  assert(term2.getTerm()->isObjectVariable());
  if (!structuralUnifySubs(term1.getSubstitutionBlockList(), 
			   term2.getSubstitutionBlockList()))
    return false;

  ObjectVariable* obvar1 = OBJECT_CAST(ObjectVariable*, term1.getTerm());
  ObjectVariable* obvar2 = OBJECT_CAST(ObjectVariable*, term2.getTerm());
  if ((obvar1->isFrozen() && obvar2->isFrozen() && !status.testHeatWave())
      || obvar1->distinctFrom(obvar2))
    {
      return(false);
    }
  bindObjectVariables(obvar1,obvar2);
  return(true);
}

bool
Thread::structuralUnifyVarObjVar(PrologValue& term1, PrologValue& term2)
{
  assert(term1.getTerm()->isVariable());
  assert(term2.getTerm()->isObjectVariable());

   Object* t1 = term1.getTerm();
  Variable* var1 = OBJECT_CAST(Variable*, t1);
  if (var1->isFrozen() && !status.testHeatWave())
    {
      return(false);
    }

  if (term1.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, term1);
    }
  if (term2.getSubstitutionBlockList()->isCons())
    {
      heap.dropSubFromTerm(*this, term2);
    }
  
  Object* sub1 = term1.getSubstitutionBlockList();
  Object* sub2 = term2.getSubstitutionBlockList();
  Object* t2 = term2.getTerm();
  
  
  // Walk through the subs
  int size1 = 0;
  for ( ;
	sub1->isCons();
	sub1 = OBJECT_CAST(Cons *, sub1)->getTail() ) size1++;

  int size2 = 0;
  for ( ;
	sub2->isCons();
	sub2 = OBJECT_CAST(Cons *, sub2)->getTail() ) size2++;


  // sub2 is longer than sub1
  if (size2 > size1)
    {


      Object* newsub = 
	heap.copySubSpineN(term2.getSubstitutionBlockList(), size2 - size1);

      assert(newsub->isCons());
      Object* newterm = heap.newSubstitution(newsub,t2);
      
      Object* simpterm;
      truth3 flag = occursCheck(ALL_CHECK, var1, newterm, simpterm);
      if (flag == false)
	{
	  bind(var1, simpterm);
	}
      else
	{
	  return(false);
	}
    }
  // sub1 is longer than sub2
  else if (size1 > size2)
    {
      return false;
     }
  else
    {
      assert(size1 == size2);
      bind(var1, t2);
    }
  heap.prologValueDereference(term1);
  assert(term1.getTerm() == term2.getTerm());
  sub1 = term1.getSubstitutionBlockList();
  sub2 = term2.getSubstitutionBlockList();
  
  return structuralUnifySubs(sub1, sub2);

}

//
// Structural unify. This unifies two terms as "structures" - i.e.
// Quantified terms and terms with substitutions are considered
// as ordinary structures. 
//
bool
Thread::structuralUnify(PrologValue& term1, PrologValue& term2)
{
  //
  // Do the full dereference.
  //
  heap.prologValueDereference(term1);
  heap.prologValueDereference(term2);
  if ((term1.getTerm() == term2.getTerm()) &&
      (term1.getSubstitutionBlockList() == term2.getSubstitutionBlockList()))
    {
      return(true);
    }
  //
  // At this point the terms are different.
  //

  u_int ut1 = term1.getTerm()->getTag() & Object::UnifyMask;
  u_int ut2 = term2.getTerm()->getTag() & Object::UnifyMask;

  assert((ut1>>1) < 8);
  assert((ut2>>1) < 8);
  switch (CrossTag(ut1, ut2))
    {
      //
      // term1 is a variable
      //
    case CrossTag(Object::UVar, Object::UVar):
    case CrossTag(Object::UVar, Object::UVarOC):
    case CrossTag(Object::UVarOC, Object::UVar):
    case CrossTag(Object::UVarOC, Object::UVarOC):
      return structuralUnifyVarVar(term1, term2);
      break;
      
    case CrossTag(Object::UVar, Object::UOther):
    case CrossTag(Object::UVarOC, Object::UOther):
      if (term2.getTerm()->isVariable())
	return structuralUnifyVarVar(term1, term2);
      else if (term2.getTerm()->isObjectVariable())
	return structuralUnifyVarObjVar(term1, term2);
      else
	return structuralUnifyVarQuantifier(term1, term2);
      break;
      
    case CrossTag(Object::UVar, Object::UStruct):
    case CrossTag(Object::UVarOC, Object::UStruct):
      return structuralUnifyVarStruct(term1, term2);
      break;
    case CrossTag(Object::UVar, Object::UCons):
    case CrossTag(Object::UVarOC, Object::UCons):
      return structuralUnifyVarCons(term1, term2);
      break;
    case CrossTag(Object::UVar, Object::UNumber):
    case CrossTag(Object::UVar, Object::UAtom):
    case CrossTag(Object::UVar, Object::UString):
    case CrossTag(Object::UVarOC, Object::UNumber):
    case CrossTag(Object::UVarOC, Object::UAtom):
    case CrossTag(Object::UVarOC, Object::UString):
      return structuralUnifyVarConst(term1, term2);
      break;

      //
      // term1 is a number
      //
    case CrossTag(Object::UNumber, Object::UVar):
    case CrossTag(Object::UNumber, Object::UVarOC):
      return structuralUnifyVarConst(term2, term1);
      break;
    case CrossTag(Object::UNumber, Object::UNumber):
      return term1.getTerm()->equalUninterp(term2.getTerm());
      break;
    case CrossTag(Object::UNumber, Object::UAtom):
    case CrossTag(Object::UNumber, Object::UString):
    case CrossTag(Object::UNumber, Object::UStruct):
    case CrossTag(Object::UNumber, Object::UCons):
      return false;
      break;
    case CrossTag(Object::UNumber, Object::UOther):
      return (term2.getTerm()->isVariable() &&
	      structuralUnifyVarConst(term2, term1));
      break;

      //
      // term1 is an atom
      //
    case CrossTag(Object::UAtom, Object::UVar):
    case CrossTag(Object::UAtom, Object::UVarOC):
      return structuralUnifyVarConst(term2, term1);
      break;
    case CrossTag(Object::UAtom, Object::UString):
    case CrossTag(Object::UAtom, Object::UAtom):
    case CrossTag(Object::UAtom, Object::UStruct):
    case CrossTag(Object::UAtom, Object::UCons):
      return false;
      break;
    case CrossTag(Object::UAtom, Object::UOther):
      return (term2.getTerm()->isVariable() &&
	      structuralUnifyVarConst(term2, term1));
      break;
      //
      // term1 is a string
      //
    case CrossTag(Object::UString, Object::UVar):
    case CrossTag(Object::UString, Object::UVarOC):
      return structuralUnifyVarConst(term2, term1);
      break;
    case CrossTag(Object::UString, Object::UString):
      return term1.getTerm()->equalUninterp(term2.getTerm());
      break;
    case CrossTag(Object::UString, Object::UAtom):
    case CrossTag(Object::UString, Object::UStruct):
    case CrossTag(Object::UString, Object::UCons):
      return false;
      break;
    case CrossTag(Object::UString, Object::UOther):
      return (term2.getTerm()->isVariable() &&
	      structuralUnifyVarConst(term2, term1));
      break;

      //
      // term1 is a structure
      //
    case CrossTag(Object::UStruct, Object::UVar):
    case CrossTag(Object::UStruct, Object::UVarOC):
      return structuralUnifyVarStruct(term2, term1);
      break;
    case CrossTag(Object::UStruct, Object::UNumber):
    case CrossTag(Object::UStruct, Object::UAtom):
    case CrossTag(Object::UStruct, Object::UString):
      return false;
      break;
    case CrossTag(Object::UStruct, Object::UStruct):
      {
	Structure* struct1 = OBJECT_CAST(Structure*, term1.getTerm());
	Structure* struct2 = OBJECT_CAST(Structure*, term2.getTerm());
	
	u_int arity = static_cast<int>(struct1->getArity());
	if (arity != struct2->getArity())
	  {
	    return(false);
	  }

	for (u_int i = 0; i <= arity; i++)
	  {
	    PrologValue arg1(term1.getSubstitutionBlockList(), 
			     struct1->getArgument(i));
	    PrologValue arg2(term2.getSubstitutionBlockList(), 
			     struct2->getArgument(i));

	    if (!structuralUnify(arg1, arg2))
	      {
		return(false);
	      }
	  }
	return(true);
	break;
      }
    case CrossTag(Object::UStruct, Object::UCons):
      return false;
      break;
    case CrossTag(Object::UStruct, Object::UOther):
      return (term2.getTerm()->isVariable() &&
	      structuralUnifyVarStruct(term2, term1));
      break;

      //
      // term1 is a cons
      //
    case CrossTag(Object::UCons, Object::UVar):
    case CrossTag(Object::UCons, Object::UVarOC):
      return structuralUnifyVarCons(term2, term1);
      break;
    case CrossTag(Object::UCons, Object::UNumber):
    case CrossTag(Object::UCons, Object::UAtom):
    case CrossTag(Object::UCons, Object::UStruct):
    case CrossTag(Object::UCons, Object::UString):
      return false;
      break;
    case CrossTag(Object::UCons, Object::UCons):
      {
	Cons* list1 = OBJECT_CAST(Cons*, term1.getTerm());
	Cons* list2 = OBJECT_CAST(Cons*, term2.getTerm());
	PrologValue head1(term1.getSubstitutionBlockList(), list1->getHead());
	PrologValue head2(term2.getSubstitutionBlockList(), list2->getHead());
	PrologValue tail1(term1.getSubstitutionBlockList(),list1->getTail() );
	PrologValue tail2(term2.getSubstitutionBlockList(), list2->getTail());
	
	return (structuralUnify(head1, head2) &&
		structuralUnify(tail1, tail2));
	break;
      }
    case CrossTag(Object::UCons, Object::UOther):
      return (term2.getTerm()->isVariable() &&
	      structuralUnifyVarCons(term2, term1));
      break;
      //
      // term1 is a var, object variable or quant
      //      
    case CrossTag(Object::UOther, Object::UVar):
    case CrossTag(Object::UOther, Object::UVarOC):
      if (term1.getTerm()->isVariable())
	return structuralUnifyVarVar(term2, term1);
      else if (term1.getTerm()->isObjectVariable())
	return structuralUnifyVarObjVar(term2, term1);
      else
	return structuralUnifyVarQuantifier(term2, term1);
      break;

    case CrossTag(Object::UOther, Object::UNumber):
    case CrossTag(Object::UOther, Object::UAtom):
    case CrossTag(Object::UOther, Object::UString):
      return (term1.getTerm()->isVariable() &&
	      structuralUnifyVarConst(term1, term2));
      break;
    case CrossTag(Object::UOther, Object::UStruct):
      return (term1.getTerm()->isVariable() &&
	      structuralUnifyVarStruct(term1, term2));
      break;
    case CrossTag(Object::UOther, Object::UCons):
      return (term1.getTerm()->isVariable() &&
	      structuralUnifyVarCons(term1, term2));
      break;
    case CrossTag(Object::UOther, Object::UOther):
      {
	if (term1.getTerm()->isVariable()) {
	  if (term2.getTerm()->isVariable())
	    return structuralUnifyVarVar(term1, term2);
	  else if (term2.getTerm()->isObjectVariable())
	    return structuralUnifyVarObjVar(term1, term2);
	  else
	    return structuralUnifyVarQuantifier(term1, term2);
        }
	if (term2.getTerm()->isVariable()) {
	  if (term1.getTerm()->isObjectVariable())
	    return structuralUnifyVarObjVar(term2, term1);
	  else
	    return structuralUnifyVarQuantifier(term2, term1);
        }
	if (term1.getTerm()->isObjectVariable())
	  return (term2.getTerm()->isObjectVariable() &&
		  structuralUnifyObjVarObjVar(term1, term2));

	assert(term1.getTerm()->isQuantifiedTerm());
	assert(term2.getTerm()->isQuantifiedTerm());
	QuantifiedTerm* q1 = OBJECT_CAST(QuantifiedTerm*, term1.getTerm());
	QuantifiedTerm* q2 = OBJECT_CAST(QuantifiedTerm*, term2.getTerm());
	PrologValue qu1(q1->getQuantifier());
	PrologValue qu2(q2->getQuantifier());
	PrologValue bv1(q1->getBoundVars());
	PrologValue bv2(q2->getBoundVars());
	PrologValue body1(q1->getBody());
	PrologValue body2(q2->getBody());
	return (structuralUnifySubs(term1.getSubstitutionBlockList(), 
				    term2.getSubstitutionBlockList())
		&& structuralUnify(qu1, qu2)
		&& structuralUnify(bv1, bv2)
		&& structuralUnify(body1, body2));


	break;
      }
    }

  assert(false);
  return(false);
}











