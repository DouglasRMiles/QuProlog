// ql.cc - The main program for the Qu-Prolog linker.
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
// $Id: ql.cc,v 1.7 2004/12/23 22:40:36 qp Exp $

#include <stdlib.h>

#include "area_offsets.h"
#include "atom_table.h"
#include "code.h"
#include "defs.h"
#include "executable.h"
#include "instructions.h"
#include "obj_index.h"
#include "pred_table.h"
#include "ql.h"
#include "ql_options.h"
#include "string_map.h"

const char *Program = "ql";

//
// Handler for out of memory via new
//
//typedef void (*new_handler) ();
//new_handler set_new_handler(new_handler p) throw();

void noMoreMemory()
{
   cerr << "No more memory available for " << Program << endl;
   abort();
}

//
// A 3-steps Qu-Prolog linker:
//	1. Load the files.
//	2. Resolve the code and symbols.
//	3. Save the result.
//

AtomTable *atoms = NULL;
Code *code = NULL;

int
main(int32 argc, char** argv)
{
  // set the out-of-memory handler
  std::set_new_handler(noMoreMemory);

  QlOptions ql_options(argc, argv);

  if (! ql_options.Valid())
    {
      Usage(Program, ql_options.Usage());
    }

  //
  // Allocate areas in the Qu-Prolog Abstract Machine.
  //
  atoms =
    new AtomTable(ql_options.AtomTableSize(),
		ql_options.StringTableSize(), 0);

  PredTab predicates(atoms, ql_options.PredicateTableSize());
  
  code = new Code(ql_options.CodeSize());
  
  StringMap *string_map =
    new StringMap(ql_options.StringMapSize(), 0); 

  //
  // Step 1 - load all the files in.
  // 
  typedef ObjectIndex* ObjectIndexPtr;
  ObjectIndex **ObjectIndices =
    new ObjectIndexPtr[ql_options.NumObjectFiles()];

  word32 NumQuery = 0;
  for (int i = 0; i < ql_options.NumObjectFiles(); i++)
    {
      ObjectIndices[i] = 
	new ObjectIndex(*code, *atoms, predicates);
      ObjectIndices[i]->loadObjectFile(ql_options.ObjectArgv()[i],
				    NumQuery,
				    *string_map, predicates);
    }

  //
  // Step 2 - Resolve the code and query.
  //
  CodeLoc SizeLoc = (CodeLoc)EMPTY_LOC;
  if (NumQuery > 0)
    {
      //
      // Put in the header for the query.
      //
      Atom* query = atoms->add("$query");
      predicates.addPredicate(atoms, 
			      query,
			      0, PredCode::STATIC_PRED,
			      code->getTop(), code);
      code->pushConstant(query);
      code->pushNumber((word8) 0);
      SizeLoc = code->getTop();
      code->pushOffset((word16) 0);
      code->pushInstruction(ALLOCATE);
      code->pushNumber((word8) 0);
    }
  for (int32 i = 0; i < ql_options.NumObjectFiles(); i++)
    {
      Object* QName;
      ObjectIndices[i]->resolveObject(*string_map, predicates, true, QName);
    }
  if (NumQuery > 0)
    {
      //
      // Put in the trailer for the query.
      //
      code->pushInstruction(DEALLOCATE);
      code->pushInstruction(PROCEED);
      updateOffset(SizeLoc,
		   (word16) (code->getTop()-SizeLoc-Code::SIZE_OF_OFFSET));
    }

  //
  // Step 3 - Save the resolved code to a file.
  //
  SaveExecutable(ql_options.ExecutableFile(),
		 *code, *atoms, predicates);

  exit(EXIT_SUCCESS);
}







