// executable.cc - Saving and loading a .qx file.
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
// $Id: executable.cc,v 1.7 2005/03/08 00:35:05 qp Exp $

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

#include <iostream>
#include <fstream>

#include "config.h"

#include "atom_table.h"
#include "code.h"
#include "defs.h"
#include "executable.h"
#include "int.h"
#include "magic.h"
#include "pred_table.h"

//
// Save the areas to a .qx file.
//
void
SaveExecutable(const char *file, Code& code, AtomTable& atoms,
	       PredTab& predicates)
{
  //
  // Open a file for writing.
  //
  ofstream ostrm(file, ios::out|ios::trunc|ios::binary);
  if (ostrm.fail())
    {
      //
      // Fail to open the file.
      //
      FatalS(__FUNCTION__, "cannot open ", file);
    }
  else
    {
      //
      // Write the version identification.
      //
      IntSave<word32>(ostrm, QU_PROLOG_VERSION);
      
      //
      // Save the areas.
      //
      atoms.saveStringTable(ostrm);
      //save the pointer to the beginning of the sring table
      IntSave<wordptr>(ostrm, (wordptr)(atoms.getStringTableBase()));
      atoms.save(ostrm);
      code.save(ostrm, atoms);
      predicates.save(ostrm);

      //
      // Close the file.
      //
      ostrm.close();
    }
}

//
// Load the areas from a .qx file.
//
void
LoadExecutable(const char *file, Code& code, AtomTable& atoms,
	       PredTab& predicates)
{
  char* old_atom_string_base = NULL;
  //
  // Open a file for reading.
  //
  ifstream istrm(file, ifstream::binary);
  if (istrm.fail())
    {
      FatalS(__FUNCTION__, "cannot open ", file);
    }
  else
    {
      word32 magic = 0;
  
      //
      // Read the version identification.
      //
      if (istrm.good())
	{
	  magic = IntLoad<word32>(istrm);
	}

      if (magic != QU_PROLOG_VERSION)
	{
	  Warning(__FUNCTION__, "incompatible version");
	  return;
	}
      
      //
      // Restore the areas.
      //
      while (istrm.peek() != EOF)
	{
	  magic = IntLoad<word32>(istrm);
	  if (magic == CODE_MAGIC_NUMBER)
            {
              code.load(istrm, atoms);
            }
          else if (magic == PRED_TABLE_MAGIC_NUMBER)
	    {
	      predicates.load(istrm);
	    }
	  else if (magic ==  STRING_TABLE_MAGIC_NUMBER)
	    {
	      atoms.loadStringTable(istrm);
	      old_atom_string_base = (char*)(IntLoad<wordptr>(istrm));
	    }
	  else if (magic ==  ATOM_TABLE_MAGIC_NUMBER)
	    {
	      atoms.load(istrm);
	    }
	  else
	    {
	      ReadFailure(__FUNCTION__,
			  "illegal magic number",
			  file);
	    }
	} 
      //
      // Close the file.
      //
      istrm.close();
      assert(old_atom_string_base != NULL);
      atoms.shiftStringPtrs(old_atom_string_base);
    }
}












