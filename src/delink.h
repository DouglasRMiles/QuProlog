// delink.h - The code used by the deassembler and delinker
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
// $Id: delink.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef DELINK_H
#define DELINK_H

#include "atom_table.h"
#include "code.h"
#include "defs.h"
#include "obj_index.h"
#include "instructions.h"
#include "pred_table.h"
#include "string_map.h"
//
//
// Deassembler() is used for both delinking and deassembling code and queries
// obatined from the .qo and .qx files. The output is to the stdout using
// the cout command.
//
extern void deassembler(Code& code, AtomTable& atoms, PredTab& predicates,
            	CodeLoc start, CodeLoc finish, bool PrintAddr);
 
#endif  // DELINK_H





