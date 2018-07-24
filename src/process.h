// process.h - Pseudo-instructions for handling the process attributes associated
//		with a QuProlog invocation.
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
// $Id: process.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	PROCESS_H
#define	PROCESS_H

public:
// @doc
// @pred process_pid(ProcessID)
// @mode process_pid(-) is det
// @type process_pid(process_id)
// @description
// Return the process-id of the current process.
// @end pred
// @end doc
ReturnValue psi_process_pid(Object *&);

// @doc
// @pred process_symbol(Name)
// @mode process_symbol(-) is det
// @type process_symbol(atom)
// @description
// Return the symbolic name of this process.
// @end pred
// @end doc
ReturnValue psi_process_symbol(Object *&);

#endif
