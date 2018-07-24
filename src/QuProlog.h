// QuProlog.h - reduces number of #include required for foreign function
//              interface modules.
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
// $Id: QuProlog.h,v 1.4 2006/02/05 22:14:54 qp Exp $


#ifndef QU_PROLOG_H
#define QU_PROLOG_H

#include "thread_qp.h"


#ifdef WIN32
       #define QPVISIBLE _declspec(dllexport)
#else
       #define QPVISIBLE
#endif


#endif  // QU_PROLOG_H
