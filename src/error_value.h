// error_value.h -
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
// $Id: error_value.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	ERROR_VALUE_H
#define	ERROR_VALUE_H

// Ensure that this list stays up to date with respect to 
// library/psi_errors.ql.

enum ErrorValue {
  EV_NO_ERROR			= 0,	/* No error. */
  EV_INST			= 1,	/* Instantiation error. */
  EV_TYPE			= 2,	/* Type error. */
  EV_RANGE			= 3,	/* Out of range value. */
  EV_VALUE			= 4,	/* Bad value. */
  EV_ZERO_DIVIDE		= 5,	/* Division by zero. */
  EV_NOT_PERMITTED		= 6,	/* Not able to perform some operation. */
  EV_ALLOCATION_FAILURE		= 7,	/* Resource allocation failure. */
  EV_SYSTEM			= 8,	/* Operationg system call failure. */
  EV_UNIMPLEMENTED		= 9,	/* The operation requested isn't implemented yet. */
  EV_UNSUPPORTED		= 10	/* The operation requested is no longer supported */
};

#endif	// ERROR_VALUE_H

