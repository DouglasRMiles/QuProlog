// string_map.cc - Used for relocation of atoms and numbers during loading.
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
// $Id: string_map.cc,v 1.5 2005/03/08 00:35:15 qp Exp $

#include <iostream>
#include <string.h>
#include <stdio.h>

#include "atom_table.h"
#include "code.h"
#include "defs.h"
#include "int.h"
#include "string_map.h"

//
// Read in the strings.
// Return whether it is successful or not.
//
// The .qo file format is:
//	+-------+
//	| size	|	} SIZE_OF_ADDRESS
//	+-------+
//	|   s	|	}
//	|   t	|	}
//	|   r	|	} size bytes
//	|   i	|	}
//	|   n	|	}
//	|   g	|	}
//	|   s	|	}
//	+-------+
//
bool
StringMap::loadStrings(istream& istrm, const char *file, AtomTable& atoms)
{
  Code::AddressSizedType StringSize = 
    IntLoad<Code::AddressSizedType>(istrm);
  for (;
       StringSize > 0;
       )
    {
      char string[ATOM_LENGTH];
      //
      // Get string.
      //
      if (istrm.good() && istrm.getline(string, ATOM_LENGTH, '\0').fail())
	{
	  WrongFileFormat(__FUNCTION__, file);
	  return(false);
	}
      //
      // Add to atom table and string map.
      //
      pushElement(atoms.add(string));
      StringSize -= static_cast<Code::AddressSizedType>(strlen(string) + 1);
    }
  
  return(true);
}

bool
NumberMap::loadNumbers(istream& istrm, Heap& number_heap)
{
  for (Code::AddressSizedType size = 
	 IntLoad<Code::AddressSizedType>(istrm);
       size > 0; size--)
    {
      int32 i = IntLoad<Code::AddressSizedType>(istrm);
      pushElement(number_heap.newInteger(i));
      
    }
  return(true);
}









