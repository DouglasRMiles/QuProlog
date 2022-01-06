// unify.h - The Qu-Prolog unify. 
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
// $Id: unify.h,v 1.3 2006/03/30 22:50:31 qp Exp $

#ifndef UNIFY_H
#define UNIFY_H

private:
//
// Extend open bound variable list. Extend shorter to match longer one.
// 
BoundVarState extendBoundVarListLoop(Object* varSub, Object* variable,
				     Object* listSub, Object* list,
				     Object*& delayedVar,
				     const bool swap, bool in_quant);

//
// Pair up bound variable lists.
// quantifier1 = s1 q1 BoundVarList1 term1
// quantifier2 = s2 q2 BoundVarList2 term2
//
BoundVarState pairUpBoundVarList(PrologValue& quantifier1,
				 PrologValue& quantifier2,
				 Object*& delayedVar, bool in_quant);

//
// Create two parallel substitutions where all ranges are new local
// object variables, and domains are bound object variables from the  
// push down stack. Bound object variables have been stored 
// in the push down stack before, from the bound variable lists of quantified 
// terms. Add the corresponding parallel substitution to the right 
// of term (quantifier) substitution.  
//
void makeQuantSubs(Object*& sub1, Object*& sub2, 
		   Object* qsub1, Object* qsub2, int old_size);

//
// Bind variable to a skeletal structure
//
void bindToSkelStruct(Object* variable, Object* structure);

//
// Bind variable to a skeletal list
//
void bindToSkelList(Object* variable);

//
// Bind variable to a skeletal quantified term
//
void bindToSkelQuant(Object* variable);

//
// Unify two quantified terms.
//
bool unifyQuantifiers(PrologValue& , PrologValue& , bool in_quant);

//
// Unify two frozen object variables.
//
bool unifyFrozenFrozenObjectVariables(PrologValue&, PrologValue&);


//
// Unify object variable and non-object variable term.
//
bool unifyObjectVariableTerm(PrologValue& objectVariable, 
			     PrologValue& term);


//
// Unify object variable with another object variable.
// 'ObjectVariable1' has no substitution.
//
bool unifyObjectVariableObjectVariable(Object* objectVariable1, 
				       PrologValue& objectVariable2);


//
// Unify variables.               
// 
// NOTE: variable1.term must contain the younger variable.
//	 variable1 and variable2 are different.
//
bool unifyVariableVariable1(PrologValue& variable1, 
			    PrologValue& variable2, bool in_quant);


//
// Unify frozen variable with a variable.               
// Frozen variable behaves like a constant.
// 
bool unifyFrozenVariable(PrologValue& frozenVariable, 
			 PrologValue& variable, bool in_quant);

//
// Unify two thawed variables.               
// 
bool unifyVariableVariable(PrologValue& variable1, 
			   PrologValue& variable2, bool in_quant);


//
// Unify variable and non-variable term.
//
bool unifyVariableTerm(PrologValue& variable, PrologValue& term, 
		       bool in_quant);

//
// Unify two variables.
//
bool unifyVarVar(PrologValue& variable1, PrologValue& variable2,
		 bool in_quant);

public:

//
// Unification of two Prolog Values.
// Assumes PrologValue dereference has been done to both terms.
//
bool unifyPrologValues(PrologValue& term1, PrologValue& term2, 
		       bool in_quant = false);

inline bool unifyAsPrologValues(Object* term1, Object* term2, bool in_quant);

bool unifyOtherConst(Object* term1, Object* term2, bool in_quant);

bool unifyOtherTerm(Object* term1, Object* term2, bool in_quant);

inline bool unifyVarOCTerm(Object* term1, Object* term2, bool in_quant);

inline bool unifyOtherVarTerm(Object* term1, Object* term2, bool in_quant);
//
// Unify algorithm.
//
bool unify(Object* term1, Object* term2, bool in_quant = false);

//
// Unify object variables.
//
bool unifyObjectVariables(PrologValue& objectVariable1,
				  PrologValue& objectVariable2);

//
// Structural unify. This unifies two terms as "structures" - i.e.
// Quantified terms and terms with substitutions are considered
// as ordinary structures. 
//
bool structuralUnify(PrologValue&, PrologValue&);

bool structuralUnifySubs(Object*, Object*);

bool structuralUnifyVarVar(PrologValue& term1, PrologValue& term2);

bool structuralUnifyVarQuantifier(PrologValue& term1, PrologValue& term2);

bool structuralUnifyVarStruct(PrologValue& term1, PrologValue& term2);

bool structuralUnifyVarCons(PrologValue& term1, PrologValue& term2);

bool structuralUnifyVarObjVar(PrologValue& term1, PrologValue& term2);

inline bool structuralUnifyVarConst(PrologValue& term1, PrologValue& term2);
inline bool structuralUnifyObjVarObjVar(PrologValue& term1, PrologValue& term2);
inline ReturnValue structuralUnifyTerm(Object*& term1, Object*& term2)
{
  PrologValue pval1(term1);
  PrologValue pval2(term2);
  return (structuralUnify(pval1, pval2) ? RV_SUCCESS : RV_FAIL);
}


#endif  // UNIFY_H







