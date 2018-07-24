// substitution.h - Contains a set of functions for dealing
//		    with Qu-Prolog substitution. 
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
// $Id: substitution.h,v 1.5 2006/01/31 23:17:51 qp Exp $

#ifndef	SUBSTITUTION_H
#define	SUBSTITUTION_H

//
// Throughout the comments relating to substitutions - substituted terms
// are represented as s1 * s2 * s3 ... * sn * t where si are substitution
// blocks. When the substitutions are collected together (as after dereference)
// then they are represented as a list. Because the right most sub block 
// applies to the term first then the list of substitution blocks has the
// the rightmost sub at the head and the left most at the tail.
// Also substitution blocks are represented as [tn/xn, ..., t1/x1]
// in comments and the t1/x1 applies first and so in the datastructure
// representing blocks t1, x1 is the first range, domain pair.
//

public:
//
// Copy the first n substitutions
//
Object* copySubSpineN(Object *input_list, int n);

//
// Copy the spine of a sequence of substitutions up to the stop point.
// tail specifies the new tail of copied version.
//
Object *copySubSpine(Object *sub_block_list1,
		     Object *sub_block_list2,
		     Object *sub_block_list3);

// 
// Split a sequence of substitutions at a specified point and return the
// right part.
// For example:
//	sub			= s1 * ... * si * sj * sk * ... * sn 
//	SplitPoint		= sj 
//	SplitSubstitution	= sk * ... * sn 
// 
inline Object *splitSubstitution(Object *sub_list, Object *split_point)
{
  assert(sub_list->isList() && split_point->isList());
  assert(sub_list->isNil() || OBJECT_CAST(Cons*, sub_list)->isSubstitutionBlockList());
  assert(split_point->isNil() || OBJECT_CAST(Cons*, split_point)->isSubstitutionBlockList());

  return copySubSpine(sub_list, split_point, AtomTable::nil);
}

// 
// Remove a specified substitution from a sequence of substitutions.
// For example:
//	sub			= s1 * ... * si * sj * sk * ... * sn 
//	unwanted		= sj 
//	RemoveSubstitution	= s1 * ... * si * sk * ... * sn 
// 
inline Object* removeSubstitution(Object *sub_list, Object *unwanted)
{
  assert(sub_list->isList() && unwanted->isCons());
  assert(sub_list->isNil() || OBJECT_CAST(Cons*, sub_list)->isSubstitutionBlockList());
  assert(OBJECT_CAST(Cons*, unwanted)->isSubstitutionBlockList());

  return copySubSpine(sub_list, unwanted, OBJECT_CAST(Cons*,unwanted)->getTail());
}

//
// Invert substitution.
//
bool invert(Thread&, Object *sub_block_list, PrologValue& term);

//
// Used to invert sub to transform sub * x not_free_in term into
// x not_free_in sub-1 * term .
//
// NOTE: no extra not_free_in conditions are added.
//
void invertWithoutNFI(Object *sub_block_list, PrologValue&);

//
// If a term has a non-empty substitution, create a new SUBSTITUTION_OPERATOR
// and assign substitution and term. If term has an empty substitution then
// just return the term part.
//
Object *prologValueToObject(PrologValue&);

//
// Check whether the object variable occurs as the most right range
// in any substitution from the composition of substitutions.
//
bool isLocalInRange(Object *, Object *sub_block_list);

//
// Copy the rightmost substitution table before any destructive processing is
// performed.  The range elements are replaced by $'s.
//
Object *copySubstitutionBlockWithDollars(Object *sub_block_list, size_t);

bool canRemove(Thread&, Object*, int, 
	       SubstitutionBlock**, Object*);
//
// Remove useless entry from a substitution wherever it is possible.
// Assumed to be (Prolog) dereferenced.
//
void dropSubFromTerm(Thread&, PrologValue&);

#endif	// SUBSTITUTION_H

