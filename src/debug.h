// debug.h - Low level debug facilities for Qu-Prolog emulator.
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
// $Id: debug.h,v 1.7 2006/03/30 22:50:30 qp Exp $

#ifndef DEBUG_H
#define DEBUG_H

#ifndef NDEBUG

#include <iostream>
//#include <pthread.h>
#include <stdlib.h>

#define QP_DEBUG

// Every program in the suite has to define its own name.
extern const char *Program;

#endif	// DEBUG
#include <assert.h>

#endif	// DEBUG_H


