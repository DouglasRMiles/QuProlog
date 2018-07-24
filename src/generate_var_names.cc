// generate_var_names.cc -
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
// $Id: generate_var_names.cc,v 1.6 2006/03/30 22:50:30 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;

//
// Generate a new name for variables.  Find one that is either not in use or
// generate a new variable name.
// The name sequence is:
//  A, .., Z, A1, .., Z1, A2, .., Z2, ...
//
Atom*
Thread::GenerateVarName(Thread* threadPtr, word32& counter)
{
  ostringstream strm;
  AtomLoc loc;
  string strm_string;
  
  do
    {
      strm.str("");
      //
      // Generate a new name and check whether it is used.
      //
      strm << (char)('A' + counter % 26);
      //
      // Add the digit suffix when the suffix is greater than 0.
      if (counter > 25)
        {
          strm << (counter / 26);
        }
      //strm << ends;
      counter++;
      strm_string = strm.str();
      loc = atoms->lookUp(strm_string.c_str());
    }
  while (loc != EMPTY_LOC && 
     threadPtr->names.getVariable(atoms->getAtom(loc)) != NULL);

  //
  // A name is found.
  //
  if (loc == EMPTY_LOC)
    {
      return(atoms->add(strm_string.c_str()));
    }
  else
    {
      return(atoms->getAtom(loc));
    }
}

//
// Generate a new name for object variables.  Find one that is either not in
// use or generate a new variable name.
//
// !!!!
// Note that another version of this function,
// GenerateRObjectVariableName(), is used for generating
// the names of object variables when
// psi_writeR_ObjectVariable is called.
// !!!!
//
Atom*
Thread::GenerateObjectVariableName(Thread* threadPtr, word32& counter)
{
  ostringstream strm;
  AtomLoc loc = EMPTY_LOC;
  string strm_string;

  do
    {
      strm.str("");
      //
      // Generate a new name and check whether it is used.
      //
      strm << "_x" << counter;
      counter++;
      strm_string = strm.str();
      loc = atoms->lookUp(strm_string.c_str());
    } while (loc != EMPTY_LOC && 
         threadPtr->names.getVariable(atoms->getAtom(loc)) != NULL);

  //
  // A name is found.
  //
  if (loc == EMPTY_LOC)
    {
      return(atoms->add(strm_string.c_str()));
    }
  else
    {
      return(atoms->getAtom(loc));
    }
}


//
// Generate a new name for object variables.  Find one that is either not in
// use or generate a new variable name.
//
// !!!!
// Note that another version of this function,
// GenerateObjectVariableName(), is used for generating
// the names of object variables when
// psi_write_ObjectVariable is called.
// !!!!
//
Atom*
Thread::GenerateRObjectVariableName(Thread* threadPtr, word32& counter)
{
  ostringstream strm;
  AtomLoc loc = EMPTY_LOC;
  string strm_string;

  do
    {
      strm.str("");
      //
      // Generate a new name and check whether it is used.
      //
      strm << "x" << counter;
      counter++;
      strm_string = strm.str();
      loc = atoms->lookUp(strm_string.c_str());
     } while (loc != EMPTY_LOC && 
          threadPtr->names.getVariable(atoms->getAtom(loc)) != NULL);

  //
  // A name is found.
  //
  if (loc == EMPTY_LOC)
    {
      return(atoms->add(strm_string.c_str()));
    }
  else
    {
      return(atoms->getAtom(loc));
    }
}





