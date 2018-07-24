// freeness.h - has two components:
//               a.  freeness test returns no, unsure, yes.
//               b.  applies not_free_in constraints to terms.
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
// $Id: freeness.h,v 1.3 2002/03/13 01:38:25 qp Exp $

#ifndef	FREENESS_H
#define	FREENESS_H

private:

bool notFreeInStructure(ObjectVariable *, PrologValue&,
			bool gen_delays = true);

bool notFreeInList(ObjectVariable *, PrologValue&, bool gen_delays = true);

bool notFreeInQuantifier(ObjectVariable *, PrologValue&, 
			 bool gen_delays = true);


public:
//
// Check whether ObjectVariable is not free in the s*X.
// (X may be a variable or object variable)
//
bool notFreeInVar(ObjectVariable *, PrologValue&, bool gen_delays = true);

//
// Constrain object variable to be not free in the term.  Fails if free in.
// Succeeds if not free in.  Delays otherwise.
// Delayed not_free_in problems are generated where necessary.
//
bool notFreeIn(ObjectVariable *, PrologValue&, bool gen_delays = true);

//
// Not free in calls generated internally by the system can be of the form
// object_variable not_free_in term with object_variable of the form s*x and
// term having possible free locals.
//
bool internalNotFreeIn(PrologValue object_variable,
		       PrologValue term);

//
// Simplify the substitution associated with var and apply not free in.
//
bool notFreeInVarSimp(ObjectVariable *, PrologValue&);

//
// Add extra info to all variables appearing in the term.
// This is needed so that when simplifying terms new variables with extra
// info are not produced because, otherwise it will cause problems
// with term copying.
//
void addExtraInfoToVars(Object *term);

//
// Used in simplifying substitutions.
// Do trivial simplifications without resorting to simplify_term.
// "Complicated" constraints are ignored
//
bool notFreeInNFISimp(ObjectVariable*, PrologValue&);

//
// A C-level implementation of freeness_test.
// 
truth3 freeness_test(ObjectVariable*, PrologValue&);

//
// freeness_test_quant does the freeness test on a quantified term
//
truth3 freeness_test_quant(ObjectVariable*, PrologValue&);

//
// freeness_test_var does the freeness test on a var term
//
truth3 freeness_test_var(ObjectVariable*, PrologValue&);

//
// freeness_test_obvar does the freeness test on an obvar term
//
truth3 freeness_test_obvar(ObjectVariable*, PrologValue&);

//
// Carry out a quick test to see if an object var is NFI a term.
// USed by dropSub to remove subs where possible.
//

bool fastNFITerm(ObjectVariable*, Object*);

#endif	// FREENESS_H








