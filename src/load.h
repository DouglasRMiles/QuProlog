// load.h - Load and link a .qo file.
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
// $Id: load.h,v 1.2 2002/06/30 05:29:58 qp Exp $

#ifndef	LOAD_H
#define	LOAD_H

//
// psi_load(filenama, querynamee)
// Load and link a .qo file.  If the operation is successful, 0 is returned in
// X1.
// mode(in, out)
//
ReturnValue psi_load(Object *& , Object *&);

#endif	// LOAD_H

