// TRACE_ESCAPES.h -
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
// $Id: trace_escapes.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	TRACE_ESCAPES_H
#define	TRACE_ESCAPES_H

public:
//
// psi_set_trace_level(number)
//
ReturnValue psi_set_trace_level(Object *&);

ReturnValue psi_set_trace_flag(Object *&);
ReturnValue psi_clear_trace_flag(Object *&);
ReturnValue psi_test_trace_flag(Object *&);

#endif	// TRACE_ESCAPES_H

