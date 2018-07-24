// return.h - Management of returns from pseudo-instructions.
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
// $Id: return.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef RETURN_H
#define RETURN_H

#include "config.h"

#define PSI_ERROR_RETURN(value, arg)		\
  do {						\
    error_value = value;			\
    error_arg = arg;				\
    return RV_ERROR;				\
  } while(0)

public:
enum ReturnValue {
  RV_SUCCESS,	// Thread succeeded
  RV_FAIL,	// Thread failed

  RV_TIMESLICE,	// Thread exhausted its scheduler quantum
  RV_SIGNAL,	// Thread received a signal
  RV_BLOCK,	// Thread would have blocked
  RV_YIELD,	// Thread is voluntarily yielding the processor

  RV_EXIT,	// Thread exited through an exit call
  RV_HALT,	// Thread executed HALT instruction.
  RV_ERROR	// Error in execution of pseudo-instruction
};

ReturnValue BOOL_TO_RV(const bool b) const
{
  return b == true ? RV_SUCCESS : RV_FAIL;
}

#endif  // RETURN_H


