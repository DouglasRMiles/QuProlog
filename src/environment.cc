// environment.cc - Each environment records the state of computation within a
//		    clause.  It enables the computation to continue after the
//		    current subgoal has been solved.
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
// $Id: environment.cc,v 1.4 2005/03/08 00:35:04 qp Exp $

#include "area_offsets.h"
#include "objects.h"
#include "defs.h"
#include "environment.h"
#include "indent.h"

//
// Push a new environment onto the stack.
// If EnvLoc or StackLoc changes representation, then a bug may
// occur if this is not changed.
//
/*
EnvLoc
EnvironmentStack::push(const EnvLoc PrevEnv, const CodeLoc ContInst,
		       const word32 NumYs)
{
	EnvLoc	env;

	//
	// Allocate environment.
	//
	env = pushRecord(sizeof(Environment) + (NumYs - 1) * sizeof(Object*));
	//
	// Initialise fixed fields.
	//
	fetchEnv(env)->previousEnvironment = PrevEnv;
	fetchEnv(env)->continuationInstruction = ContInst;
	fetchEnv(env)->NumYRegs = NumYs;
	fetchEnv(env)->zeroYRegs();

	return(env);
}
*/

// Display the meaningful fields for debugging purposes.
ostream&
EnvironmentStack::Display(ostream& ostrm, const EnvLoc index, 
			  const size_t depth)
{
  Environment *e = fetchEnv(index);

  Indent(ostrm, depth);
  cerr << "previousEnvironment=" << hex <<  e->previousEnvironment << dec << endl;

  Indent(ostrm, depth);
  cerr << "continuationInstruction=" << hex << e->continuationInstruction << dec << endl;
  
  return ostrm;
}


#ifdef QP_DEBUG
void 
EnvironmentStack::printMe(AtomTable& atoms, EnvLoc env)
{  
  while (true)
    {
      cerr << "Environment [" << env << "] ";
      if (gc_isMarkedEnv(env))
	{
	  cerr << "gc_marked";
	}
      cerr << endl;
      for (int i = (getNumYRegs(env) & 0x7FFFFFFFUL)-1; i >= 0; i--)
	{
	  cerr << "Y[" << i << "] : " << hex << (wordptr)(yReg(env,i)) << dec << endl;
	}
            if (env == firstEnv())
	{
	  return;
	}
      env = getPreviousEnv(env);
    }
}
#endif //DEBUG














