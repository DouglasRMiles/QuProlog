// occurs_check.h - 	Performing occurs check.
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
// $Id: occurs_check.h,v 1.2 2002/08/25 23:35:10 qp Exp $

#ifndef	OCCURS_CHECK_H
#define	OCCURS_CHECK_H

public:
enum CheckType {ALL_CHECK, DIRECT};

private:
truth3 occursCheckSubAndSimplify(const CheckType type,
				 Object *sub_block_list,
				 Object*& simp_list, Object* var);

bool simpleOccursCheckSub(Object* subblock, Object* var);

truth3 simpleOccursCheck(Object* term, Object* var);


public:

truth3 occursCheckAndSimplify(const CheckType type, 
			      PrologValue& term, Object*& simpterm, 
			      Object* var);

//
// Check occurrence of variable in term. 
//
inline truth3 occursCheck(const CheckType type,
			  Object* variable, Object* term, Object*& simpterm)
{
  assert(variable->isVariable());
  if (OBJECT_CAST(Variable*, variable)->isOccursChecked() &&
      status.testOccursCheck())
    {
      truth3 result = simpleOccursCheck(term, variable);
      if (result == false)
	{
	  simpterm = term;
	  return false;
	}
      else if (result == true)
	{
	  simpterm = term;
	  return true;
	}
      PrologValue pt(term);
      Object* var = variable->variableDereference();
      return(occursCheckAndSimplify(type, pt, simpterm, var));
    }
  else
    {
      //
      // Do not perform occurs check.
      //
      simpterm = term;
      return false;
    }
}

inline truth3 occursCheckPV(const CheckType type,
			    Object* variable, PrologValue& term, 
			    Object*& simpterm)
{
  Object* oterm =  heap.prologValueToObject(term);
  return occursCheck(type, variable, oterm, simpterm);
}

#endif	// OCCURS_CHECK_H


