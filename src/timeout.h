// timeout.h - Defines the timeouts used by some blocking operations.
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
// $Id: timeout.h,v 1.2 2006/02/14 02:40:09 qp Exp $

#ifndef	TIMEOUT_H
#define	TIMEOUT_H

#define DECODE_TIMEOUT_ARG(heap, cell, arg_num, timeout)	\
  do {								\
    if (cell->isVariable())					\
      {								\
	PSI_ERROR_RETURN(EV_INST, arg_num);			\
      }								\
    else if (! (heap).IsTimeout(cell))				\
      {								\
	PSI_ERROR_RETURN(EV_TYPE, arg_num);			\
      }								\
    timeout = (heap).DecodeTimeout(cell);			\
  } while (0)

public:
//
// Return true if the cell contains a valid timeout.
//
bool IsTimeout(Object*);

//
// The timeout is passed in via the cell. The output is determined thus:
//
// Input		Output
// -----		------
// atom:"poll"		0
// integer:n		n
// atom::"block"	-1
// 
double DecodeTimeout(Object*);

#endif	// TIMEOUT_H





