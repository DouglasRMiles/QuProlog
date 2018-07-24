//   main.cc - The main program for the Qu-Prolog deassembler / delinker.
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
// $Id: qdeal.cc,v 1.9 2002/12/05 03:39:33 qp Exp $

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "atom_table.h"
#include "code.h"
#include "defs.h"
#include "pred_table.h"
#include "string_map.h"
#include "obj_index.h"
#include "executable.h"
#include "delink.h"
#include "qdeal.h"
#include "qdeal_options.h"

const char *Program = "qdeal";

//
// Handler for out of memory via new
//

//typedef void (*new_handler)();
//new_handler set_new_handler(new_handler) throw();

void noMoreMemory()
{
   cerr << "No more memory available for " << Program << endl;
   abort();
}


AtomTable *atoms = NULL;
Code *code = NULL;

// a 2-step Qu-Prolog De-linker:
//  	1. Load the .qo  or .qx file
//	2. deassemble and output this file.
//
int
main(int32 argc, char** argv)
{
  // set the out-of-memory handler
  std::set_new_handler(noMoreMemory);

  QdealOptions *qdeal_options = new QdealOptions(argc, argv);

  if (!qdeal_options->Valid())
    {
      Usage(Program, qdeal_options->Usage());
    }

  atoms =
    new AtomTable(qdeal_options->AtomTableSize(),
		qdeal_options->StringTableSize(), 0);
  PredTab *predicates =
    new PredTab(atoms, qdeal_options->PredicateTableSize());

  code = new Code(qdeal_options->CodeSize());

  StringMap *string_map =
    new StringMap(qdeal_options->StringMapSize(), 0); 

  //
  // Step one - Load in the file.
  //
  const CodeLoc codeAreaBase = code->getTop();

  //
  // Determine which type of file we are inputting, ie .qx or .qo, and
  // load that file using approriate load function.
  //
  bool PrintAddr = false;
  const char *qoorqs = strrchr(qdeal_options->QxFile(), '.');
  if (qoorqs != NULL)
    {
      if (streq(qoorqs, ".qx")) 
	{
	  LoadExecutable(qdeal_options->QxFile(),
			 *code, *atoms, *predicates); 
	  PrintAddr = true;
	}
      else if (streq(qoorqs,".qo")) 
	{
	  word32 NumQuery = 0;
	  ObjectIndex ObjIndex(*code, *atoms, *predicates);
	  ObjIndex.loadObjectFile(qdeal_options->QxFile(),
				  NumQuery, *string_map, *predicates);
	  Object* QName;
	  ObjIndex.resolveObject(*string_map, *predicates, false, QName);
	  PrintAddr = false;
	}
      else 
	{
	  FatalS(__FUNCTION__, qdeal_options->QxFile(), " not a .qo or .qx file");
	}
    }
  else 
    {
      FatalS(__FUNCTION__, qdeal_options->QxFile(), " not a .qo or .qx file");
    }

  //
  // Get size of code area.
  // 
  const CodeLoc codeAreaTop = code->getTop();

  //
  // Step Two - Delink the code and output to standard output.
  //
  deassembler(*code, *atoms, *predicates,
	      codeAreaBase, codeAreaTop,
	      PrintAddr);
}

