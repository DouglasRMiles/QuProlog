// executable.h - Saving and loading a .qx file.
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
// $Id: executable.h,v 1.2 2001/11/21 00:21:13 qp Exp $

//
// Format of a .qx file:
//
//	+-----------------------+
//	| code area's magic	| Size of word32.
//	+-----------------------+
//	| code area size	| Size of word32.
//	+-----------------------+
//	| string#		| } SIZE_OF_ADDRESS	}
//	+-----------------------+			}
//	| arity			| } SIZE_OF_NUMBER	}
//	+-----------------------+			} Repeat
//	| size			| } SIZE_OF_OFFSET	} for
//	+-----------------------+			} each
//	|  c			| }			} predicate.
//	|  o			| } size bytes		}
//	|  d			| }			}
//	|  e			| }			}
//	+-----------------------+
//	| code area's top	| Size of word32.
//	+-----------------------+
//	| string table's magic	| Size of word32.
//	+-----------------------+
//	| string table size	| Size of word32.
//	+-----------------------+
//	| String Table		|
//	|	List		|
//	|	of		|
//	|	'\0'		|
//	|	terminated	|
//	|	strings.	|
//	+-----------------------+
//	| string table's top	| Size of word32.
//	+-----------------------+
//	| atom table's magic	| Size of word32.
//	+-----------------------+
//	| atom table size	| Size of word32.
//	+-----------------------+
//	| Atom Table		|
//	|	Offsets		|
//	|	to		|
//	|	the		|
//	|	string		|
//	|	table.		|
//	+-----------------------+
//      | number table magic    |
//      +-----------------------+
//      | number table size     |
//      +-----------------------+
//      | heap of number objects|
//      +-----------------------+
//	| predicate's magic	| Size of word32.
//	+-----------------------+
//	| predicate table size	| Size of word32.
//	+-----------------------+
//	| Predicate Table	|
//	|	Offsets		|
//	|	to		|
//	|	the		|
//	|	code		|
//	|	area.		|
//	+-----------------------+
//

#ifndef	EXECUTABLE_H
#define	EXECUTABLE_H

#include "atom_table.h"
#include "code.h"
#include "pred_table.h"

//
// Save the areas to a .qx file.
//
extern void SaveExecutable(const char *file, Code& code,
			   AtomTable& atoms,
			   PredTab& predicates);

//
// Load the areas from a .qx file.
//
extern void LoadExecutable(const char *file, Code& code, AtomTable& atoms,
			   PredTab& predicates);

#endif	// EXECUTABLE_H

