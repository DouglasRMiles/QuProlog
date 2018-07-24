// generate_var_names.h -
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
// $Id: generate_var_names.h,v 1.4 2006/03/30 22:50:30 qp Exp $

#ifndef GENERATE_VAR_NAMES_H
#define GENERATE_VAR_NAMES_H

public:
typedef Atom* (*NameGen)(Thread*, word32&);

//
// Generate a new name for variables.  Find one that is either not in use or
// generate a new variable name.
// The name sequence is:
// A, .., Z, A1, .., Z1, A2, .., Z2, ...
//
static Atom* GenerateVarName(Thread* threadPtr, word32& counter);

//
// Generate a new name for object variables.  Find one that is either not in
// use or generate a new variable name.
//
static Atom* GenerateObjectVariableName(Thread* threadPtr, word32& counter);

//
// Generate a new remembered name for object variables.  
// Find one that is either not in
// use or generate a new variable name.
//
static Atom* GenerateRObjectVariableName(Thread* threadPtr, word32& counter);

#endif // GENERATE_VAR_NAMES_H






