// env_var.h - Interface to environment variables. The name is env_var.h
// 		to avoid clashes with other environment files.
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
// $Id: env_var.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	ENV_VAR_H
#define	ENV_VAR_H

// @doc
// @pred env_getenv(Name, Value)
// @type env_getenv(string, string)
// @mode env_getenv(+, -) is semidet
//
// Looks up the Value associated with name, if any,
// in the process's environment. Succeeds if the name has
// a value in the environment, fails otherwise.
//
// @internaldoc
// Interfaces more or less directly with the getenv(3c) call.
// Implemented directly by pseudo-instruction.
// @end internaldoc
// @end doc
ReturnValue psi_env_getenv(Object *&, Object *&);

// @doc
// @pred env_putenv(Name, Value)
// @type env_putenv(string, string)
// @mode env_putenv(+, +) is det
//
// Sets the Value associated with Name in the process's environment.
// @internaldoc
// Interfaces more or less directly with the putenv(3c) call.
// Implemented directly by pseudo-instruction.
// @end internaldoc
// @end doc
ReturnValue psi_env_putenv(Object *&, Object *&);

#endif	// ENV_VAR_H
