// distinction.h - Contains a set of functions for dealing with distinctness 
//		   information associated with object variables.
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
// $Id: distinction.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef DISTINCTION_H
#define DISTINCTION_H


private:
void setDistinctObjectVariable(ObjectVariable *, ObjectVariable *);

bool distinctBoundList(ObjectVariable *, Object *bound_list);

public:
//
// Set two object variables to be distinct from each other.
//
void setDistinct(ObjectVariable *, ObjectVariable *);

//
// Check whether two object variables are distinct.
//
bool distinctFrom(Object *) const;

//
// Set all the range elements to be mutually disjoint from each other.
// Assume the ranges are newly created object variables.
//
void setMutualDistinctRanges(SubstitutionBlock *);

//
// If there is no distinctness information between the object variable
// and a domain, set the object variable to be distinct from the domain.
// Fail, if the object variable is equal to any domain.
// NOTE:
//      ObjectVariable should be dereferenced before this function is called.
//
bool generateDistinction(ObjectVariable *, Object *);

//
// The function returns true if the ObjectVariable is distinct from all domains
// in the i-th to SubSize-th entry of the substitution.
// 
bool distinctFromDomains(SubstitutionBlock *, size_t i);

//
// Ensure the object variables in the bound variable list are mutually 
// distinct.
//
bool checkBinder(Object *list, Object*);

//
// Return the length of the bound variables list.
//
size_t boundListLength(void);



#endif	// DISTINCTION_H









