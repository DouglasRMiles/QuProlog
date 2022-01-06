// magic.h - Magic numbers for files.
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
// $Id: magic.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	MAGIC_H
#define	MAGIC_H

#include "defs.h"

//
// Size of a magic number.
//
const	word32	MAGIC_SIZE			= sizeof(word32);

//
// Convert an ASCII string of length 4 to a magic number.
//
//
#define Magic(s) ((wordlong)((s[0]<<24)|(s[1]<<16)|(s[2]<<8)|(s[3])))

//
// Magic strings for different areas.
//
#define  QU_PROLOG_VERSION		Magic("Q402")
#define  CODE_MAGIC_NUMBER		Magic("QCA0")
#define  PRED_TABLE_MAGIC_NUMBER	Magic("QPT0")
#define  STRING_TABLE_MAGIC_NUMBER	Magic("QST0")
#define  ATOM_TABLE_MAGIC_NUMBER	Magic("QAT0")
#define  NAME_TRAIL_MAGIC_NUMBER	Magic("QNT0")
#define  NAME_TABLE_MAGIC_NUMBER	Magic("QNA0")
#define  CHOICE_MAGIC_NUMBER		Magic("QCS0")
#define  ENVIRONMENT_MAGIC_NUMBER	Magic("QES0")
#define  HEAP_TRAIL_MAGIC_NUMBER	Magic("QHT0")
#define  HEAP_MAGIC_NUMBER		Magic("QHP0")
#define  RECORD_TABLE_MAGIC_NUMBER	Magic("QRT0")

#endif	// MAGIC_H
