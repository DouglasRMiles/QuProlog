// foreign.h - Incremental loading of foreign language functions.
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
// $Id: foreign.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	FOREIGN_H
#define	FOREIGN_H

#include "pred_table.h"

private:
  
EscFn FnAddr(const char *fn) const;

bool LinkLoad(Object* objects, Object* libraries);

public:
//
// psi_load_foreign(object files, libraries, predicate list, function list)
// Link and load the object files.  Link the predicate and function together.
//
ReturnValue psi_load_foreign(Object *&, Object *&, Object *&, Object *&);

#endif	// FOREIGN_H






