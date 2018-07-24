// obj_index.cc - Object for handling a .qo file during linking.
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
// $Id: obj_index.cc,v 1.9 2005/03/08 00:35:10 qp Exp $

//
// Format of a .qo file
// --------------------
//
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
//	| size	|	} SIZE_OF_ADDRESS
//	+-------+
//	|   n	|	} ignore 1st byte ???????
//	|   u	|	}
//	|   m	|	} size bytes
//	|   b	|	}
//	|   e	|	}
//	|   r	|	}
//	|   s	|	}
//	+-------+
//	| size	|	} SIZE_OF_OFFSET
//	+-------+
//	| q  c	|	}
//	| u  o	|	}
//	| e  d	|	} size bytes
//	| r  e	|	}
//	| y	|	}
//	+-------+
//	|string#|	} SIZE_OF_ADDRESS	}
//	+-------+				}
//	| arity	|	} SIZE_OF_NUMBER	}
//	+-------+				}
//	| size	|	} SIZE_OF_OFFSET	} repeat for each predicate
//	+-------+				}
//	|  c	|	}			}
//	|  o	|	} size bytes		}
//	|  d	|	}			}
//	|  e	|	}			}
//	+-------+
//

#include <iostream>
#include <fstream>

#include "config.h"

#include "area_offsets.h"
#include "atom_table.h"
#include "objects.h"
#include "defs.h"
#include "global.h"
#include "obj_index.h"
#include "instructions.h"
#include "int.h"
#include "pred_table.h"
#include "string_map.h"

//
// Load a .qo file into the memory and record the boundaries of string map,
// and code areas.
// Return whether it is successful or not.
//
bool
ObjectIndex::loadObjectFile(const char *file, word32& NumQuery, 
			    StringMap& string_map,
			    PredTab& predicates)
{
  bool status = true;

  //
  // Record the details before reading.
  //
  name = file;
  stringMap = string_map.getTop();

  codeAreaBase = code.getTop();

  //
  // Open the file for reading.
  //
  ifstream istrm(file, ios::binary);
  if (istrm.fail())
    {
      //
      // Fail to open the file.
      //
      name = NULL;
      WarningS(__FUNCTION__, "cannot open the file ", file);
      istrm.close();
      return(false);
    }
  
  //
  // Read in the strings.
  //
  status &= string_map.loadStrings(istrm, file, atoms);
  
  //
  // Read in the queries.
  //
  const Code::OffsetSizedType QuerySize =
    IntLoad<Code::OffsetSizedType>(istrm);
  
  //
  // Perform loading process only if there is something to load.
  //
  if (QuerySize <= 1)
    {
      if (istrm.good() &&
	  istrm.seekg(QuerySize, ios::cur).fail())
	{
	  ReadFailure(__FUNCTION__, "query", file);
	}
    }
  else
    {
      NumQuery++;
      
      if (istrm.good() &&
	  istrm.seekg(Code::SIZE_OF_INSTRUCTION, ios::cur).fail())
	{
	  ReadFailure(__FUNCTION__, "query", file);
	}

      queryName = IntLoad<Code::PredSizedType>(istrm);
      
      query = true;
      
      if (istrm.good() &&
	  istrm.seekg(Code::SIZE_OF_NUMBER, ios::cur).fail())
	{
	  ReadFailure(__FUNCTION__, "query", file);
	}
    }
  
  //
  // Read in predicates.
  //
  while (istrm.peek() != EOF)
    {
      status &= code.addPredicate(istrm, file, string_map, stringMap,
				  &atoms, predicates, &code);
    }
  codeAreaTop = code.getTop();

  //
  // Close the file.
  //
  istrm.close();
  
  return(status);
}

//
// Resolve the references to atoms and predicates in each object file.
//
void
ObjectIndex::resolveObject(const StringMap& string_map, 
			   PredTab& predicates, bool dump_query_calls,
			   Object*& query_name)
{
  word32	size;
  CodeLoc	start, SizeLoc;

  //
  // Resolve the query by adding a call to the queries in a file.
  //
  query_name = AtomTable::failure;
  if (query)
    {
      // Return the query name
      query_name = string_map.convert(stringMap, queryName);
      // Add calls to code area - for linked files
      if (dump_query_calls)
	{
	  code.pushInstruction(CALL_ADDRESS);
	  code.pushCodeLoc(predicates.getCode(
	    predicates.lookUp(string_map.convert(stringMap, queryName),
			      0, &atoms, &code)).getPredicate(&code));
	  code.pushNumber((word8) 0);
	}
    }
  
  for (start = codeAreaBase;
       start < codeAreaTop;
       start += Code::SIZE_OF_HEADER + size)
    {
      SizeLoc = start + Code::SIZE_OF_ADDRESS + Code::SIZE_OF_NUMBER;
      size = getOffset(SizeLoc);
      //
      // Resolve a predicate.
      //
      code.resolveCode(start + Code::SIZE_OF_HEADER,
		       start + Code::SIZE_OF_HEADER + size,
		       string_map, stringMap, 
		       predicates, &atoms, &code);
    }
}


