// load.cc - Load and link a .qo file.
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
// $Id: load.cc,v 1.9 2006/01/31 23:17:51 qp Exp $

#ifdef WIN32
        #include <io.h>
#else
        #include <unistd.h>
#endif

#include "atom_table.h"
#include "system_support.h"
#include "thread_qp.h"

#ifndef F_OK
#    define F_OK 00
#endif

extern AtomTable *atoms;
extern Code *code;
extern PredTab *predicates;
extern QemOptions *qem_options;

// psi_load(filename, queryname)
// Load and link a .qo file.  If the operation is successful, 0 is returned in
// X1.
// mode(in, out)
//
Thread::ReturnValue
Thread::psi_load(Object *& object1, Object*& object2)
{
  Object* val1 = heap.dereference(object1);

  assert(val1->isAtom());

  string filename = OBJECT_CAST(Atom*, val1)->getName();
  wordexp(filename);
  char file[1024];
  strcpy(file, filename.c_str());


#ifdef WIN32
  if (_access(file, F_OK) != -1)
#else
  if (access(file, F_OK) == 0)
#endif
    {
      ObjectIndex index(*code, *atoms, *predicates);
      StringMap string_map(qem_options->StringMapSize(), 0);
      word32 NumQuery = 0;

      //
      // Read the file.
      //
      if (index.loadObjectFile(file, NumQuery, string_map, *predicates))
	{
	  //
	  // Link the program.
	  //
	  index.resolveObject(string_map, *predicates, false, object2);
	  
	  return(RV_SUCCESS);
	}
    }

  return(RV_FAIL);
}





