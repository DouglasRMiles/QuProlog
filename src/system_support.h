// system_support.h 
//
// Functions for general system support

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
// $Id: system_support.h,v 1.2 2005/03/08 00:35:16 qp Exp $

#ifndef SYSTEM_SUPPORT_H
#define SYSTEM_SUPPORT_H

#include <string>

using namespace std;

//
// wordexp(string) - a simplified wordexp(3) that expands ~ and environment
// variables

void wordexp(string&);

#endif // SYSTEM_SUPPORT_H
