// obj_index.h - Object for handling a .qo file during linking.
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
// $Id: obj_index.h,v 1.3 2002/06/30 05:30:00 qp Exp $

//
// Format of a .qo file
// --------------------
//
//	+-------+
//	| size	|	} SIZE_OF_ADDRESS
//	+-------+
//	|   s	|	} ignore 1st byte
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

#ifndef	OBJ_INDEX_H
#define	OBJ_INDEX_H

#include "atom_table.h"
#include "objects.h"
#include "pred_table.h"
#include "string_map.h"

class	ObjectIndex
{

private:

  Code& code;
  AtomTable& atoms;
  PredTab& predicates;

  const char *name;		// file name
  StringMapLoc stringMap;	// string map location before reading

  bool query;			// True if object file had query code
  AtomLoc queryName;		// Name of the query code

  CodeLoc codeAreaBase;	// code location before reading
  CodeLoc codeAreaTop;	// code location after reading

public:

  ObjectIndex(Code& c, AtomTable& a, PredTab& p) 
    : code(c), atoms(a), predicates(p), query(false) { }

  //
  // Load a .qo file into the memory and record the boundaries of
  // string map, number map, query, and code areas.
  // Return whether it is successful or not.
  //
  bool	loadObjectFile(const char *file, word32& NumQuery,
		       StringMap& string_map,
		       PredTab& predicates);

  //
  // Resolve the references to atoms and predicates in each object file.
  //
  void	resolveObject(const StringMap& string_map, 
		      PredTab& predicates, bool dump_query_calls,
		      Object*& query_name);
};

#endif	// OBJ_INDEX_H
