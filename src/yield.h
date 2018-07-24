// yield.h - The Qu-Prolog yield procedures. 
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
// $Id: yield.h,v 1.3 2005/06/29 22:05:35 qp Exp $

#ifndef	YIELD_H
#define	YIELD_H

private:
typedef bool (*YieldCond)(Heap*, PrologValue&, Object *);

//
// Check whether the substitution list yields the term.
//
bool yield(Object *term, Object *sub_block_list,
	   YieldCond, ThreadStatus&);

//
// Extra condition for yield constant.
//
static bool yieldConstantCond(Heap* heapPtr, PrologValue& range, 
                              Object *constant)
{
  return (range.getTerm()->isConstant() &&
	  constant->equalConstants(range.getTerm()));
}

//
// Extra condition for yield variable.
//
static bool yieldVarCond(Heap* heapPtr, PrologValue& range, Object *variable)
{
  return (variable == range.getTerm());
}      

//
// Extra condition for yield structure.
//
static bool yieldStructureCond(Heap*, PrologValue&, Object *);

//
// Extra condition for yield list.
//
static bool yieldListCond(Heap* heapPtr, PrologValue& range, Object*)
{
  return range.getTerm()->isCons();
}

//
// Extra condition for yield quantifier.
//
static bool yieldQuantifierCond(Heap*, PrologValue&, Object *);

public:
//
// Check whether the substitution yields the constant.
//
bool yieldConstant(Object *constant,
		   Object *sub_block_list, 
		   ThreadStatus& status)
{
  return yield(constant, sub_block_list, &yieldConstantCond, status); 
}

//
// Check whether the substitution yields the variable.
//
bool yieldVariable(Object *variable,
		   Object *sub_block_list, 
		   ThreadStatus& status)
{
  return yield(variable, sub_block_list, &yieldVarCond, status); 
}

//
// Check whether the substitution yields the structure.
// 
bool yieldStructure(Object *structure,
		    Object *sub_block_list,
		    ThreadStatus& status)
{
  return yield(structure, sub_block_list, &yieldStructureCond, status); 
}

//
// Check whether the substitution yields the list.
// 
bool yieldList(Object *list,
	       Object *sub_block_list, 
	       ThreadStatus& status)
{
  return yield(list, sub_block_list, &yieldListCond, status); 
}

//
// Check whether the substitution yields the quantifier.
// 
bool yieldQuantifier(Object *quantified_term,
		     Object *sub_block_list,
		     ThreadStatus& status)
{
  return yield(quantified_term, sub_block_list, &yieldQuantifierCond, status); 
}

//
// Check whether the substitution yields the object variable.
//
bool yieldObjectVariable(Object *ObjectVariable,
			 Object *sub_block_list,
			 ThreadStatus& status);

#endif	// YIELD_H

