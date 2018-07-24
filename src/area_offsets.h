// area_offsets.h - Contains all the 'typedef' for offset into different data
//		    areas.  If any of the area is changed, the following
//		    'typedef' may change.
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
// $Id: area_offsets.h,v 1.2 2000/12/13 23:10:00 qp Exp $

#ifndef	AREA_OFFSETS_H
#define	AREA_OFFSETS_H

#include "defs.h"

//
// Offsets for generic data areas.
//
typedef word32		PageLoc;	// See page.h
typedef PageLoc		StackLoc;	// See stack_qp.h
typedef word32	HashLoc;	// See hash_table.h

//
// Offsets for global data areas.
//
typedef StackLoc	StringLoc;	// See string_table.h
typedef HashLoc		AtomLoc;	// See atom_table.h
typedef HashLoc		PredLoc;	// See pred_table.h

//
// Offsets for data areas local to each thread.
//
typedef HashLoc		NameLoc;	// See name_table.h
typedef HashLoc         IPLoc;        // See name_table.h 
// typede	HeapLoc;	// See heap.h
typedef StackLoc	EnvLoc;		// See environment.h
typedef StackLoc	ChoiceLoc;	// See choice.h
typedef wordptr*	TrailLoc;	// See trail.h

//
// Offsets for data area for linking.
//
typedef	StackLoc	StringMapLoc;	// See string_map.h
typedef	StackLoc	NumberMapLoc;	// See string_map.h

#endif	// AREA_OFFSETS_H
