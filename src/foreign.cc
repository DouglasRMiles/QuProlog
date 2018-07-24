// foreign.cc - Incremental loading of foreign language functions.
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
// $Id: foreign.cc,v 1.20 2006/02/02 02:20:12 qp Exp $

#include "global.h"
#include "thread_qp.h"

#include "atom_table.h"
#include "pred_table.h"

extern AtomTable *atoms;
extern PredTab *predicates;

#if defined(SOLARIS) || defined(LINUX) || defined(FREEBSD) || defined(MACOSX) || defined(WIN32)


#include <sstream>
#include <stdlib.h>
#ifdef WIN32
#include <io.h>
#include <windows.h>
#else
#include <dlfcn.h>
#include <unistd.h>
#endif

#ifndef WIN32
#if (defined(FREEBSD) || defined(MACOSX))
#include        <pthread.h>
#include        <signal.h>
#include <sys/wait.h>
#endif //defined(FREEBSD) || defined(MACOSX)
#endif

#ifndef WIN32
extern	"C"	int mkstemp(char *);
#if (defined(FREEBSD) || defined(MACOSX))
extern char **environ;
int local_bsd_system (char *command) {
  int pid, status;
  
  if (command == 0)
    return 1;
  pid = fork();
  if (pid == -1)
    return -1;
  if (pid == 0) {
    signal(SIGVTALRM, SIG_IGN);
    char *argv[4];
    argv[0] = "sh";
    argv[1] = "-c";
    argv[2] = command;
    argv[3] = 0;
    execve("/bin/sh", argv, environ);
    exit(127);
  }
  do {
    if (waitpid(pid, &status, 0) == -1) {
      if (errno != EINTR)
	return -1;
    } else
      return status;
  } while(1);
}

#endif //defined(FREEBSD) || defined(MACOSX)
#endif

//
// Link and load the object files and libraries.
//
bool
Thread::LinkLoad(Object* objects, Object* libraries)
{
  ostringstream strm;
  char output[64];
  Object* file;
  void *handle;
  
  //
  // Generate the linking command.
  //
#ifdef WIN32
  // Since the dll can't be deleted use the first names object file as the 
  // name for the dll
  objects = objects->variableDereference();
  file =  OBJECT_CAST(Cons*,objects)->getHead()->variableDereference();
  strcpy(output, OBJECT_CAST(Atom*, file)->getName());
  output[strlen(output) - 2] = '\0';
#else
  strcpy(output, "symXXXXXX");
  int ret = mkstemp(output);
  if (ret == -1) return(false);
#endif

#ifdef WIN32
  char dll_file[64];
  char lib_file[64];
  strcpy(dll_file, output);
  strcpy(lib_file, "lib");
  strcat(dll_file, ".dll");
  strcat(lib_file, output);
  strcat(lib_file, ".a");
  strm << "g++ -shared -o " << dll_file << " "; 
#else
#ifdef SOLARIS
  strm << "ld -G ";
#else
#ifdef MACOSX
  strm << "g++ -flat_namespace -undefined suppress -bundle ";
#else
  strm << "g++ -shared -Wl,-soname," << output << " ";
#endif // MACOSX
#endif // SOLARIS
#endif // WIN32
  for (objects = objects->variableDereference();
       objects->isCons();
       objects = OBJECT_CAST(Cons*, objects)->getTail()->variableDereference())
    {
      file =  OBJECT_CAST(Cons*,objects)->getHead()->variableDereference();
      assert(file->isAtom());
      
      strm << OBJECT_CAST(Atom*, file)->getName() << " ";
    }
  assert(objects->isNil());
  
  for (libraries = libraries->variableDereference();
       libraries->isCons();
       libraries = 
	 OBJECT_CAST(Cons*, libraries)->getTail()->variableDereference())
    {
      file =  OBJECT_CAST(Cons*, libraries)->getHead()->variableDereference();
      
      assert(file->isAtom());
      
      strm << OBJECT_CAST(Atom*, file)->getName() << " ";
    }
  
  assert(libraries->isNil());
  
#ifdef WIN32
  strm << " -W1," << lib_file;
#else
#ifdef SOLARIS
  strm << "-lc -o " << output << ends;
#else // !SOLARIS
  strm << " -lc -o " << output << ends;
#endif // SOLARIS
#endif // WIN32 
  
  
  //
  // Link the object files and the libraries.
  //
  char *cmd = new char[strm.str().size() + 1];
  memcpy(cmd, strm.str().data(), strm.str().size());
  cmd[strm.str().size()] = '\0';
  
  
#if (!defined(WIN32) && (defined(FREEBSD) || defined(MACOSX)))
  if (local_bsd_system(cmd))
#else
    
  const char *command = cmd;
  if (system(command))
#endif
    
      {
#ifdef SOLARIS
	Warning(__FUNCTION__, "cannot ld -G");
#else // !SOLARIS
	Warning(__FUNCTION__, "Can't create shared object");
#endif // SOLARIS
	unlink(output);
	delete cmd;
	return(false);
      }
  
  
  delete cmd;

  
#ifdef WIN32
  //Load the library here
  if ((handle = reinterpret_cast<void*>(LoadLibrary(dll_file))) == NULL)
    {
      Warning(__FUNCTION__, "Error loading DLL. Check that it exists.");
      return(false);
    }
#else
  if ((handle = dlopen(output, RTLD_LAZY)) == NULL)
    {
      Warning(__FUNCTION__, dlerror());
      unlink(output);
      return(false);
    }
#endif 
  ForeignFile = new Handle(handle, ForeignFile);
  unlink(output);
  
  return(true);
}

//
// Look up a symbol.
//
EscFn
Thread::FnAddr(const char *fn) const
{
  void	*loc;
  
#ifdef WIN32
  if ((loc = (void *)GetProcAddress((HMODULE)ForeignFile->file(), fn)) == NULL)
    {
      Warning(__FUNCTION__, "Error loading function");
      return((EscFn)(EMPTY_LOC));
    }
#else
  if ((loc = dlsym(ForeignFile->file(), fn)) == NULL)
    {
      Warning(__FUNCTION__, dlerror());
      return((EscFn)(EMPTY_LOC));
    }
#endif
  return((EscFn)(loc));
}
#else	// SOLARIS
bool
Thread::LinkLoad(Object*, Object*)
{
  // Nothing!
  return true;
}

EscFn
Thread::FnAddr(const char *) const
{
  // Nothing, again!
  return (EscFn) NULL;
}

#endif	// SOLARIS

//
// psi_load_foreign(object files, libraries, predicate list, function list)
// Link and load the object files.  Link the predicate and function together.
//
Thread::ReturnValue
Thread::psi_load_foreign(Object *& object_file_arg,
			 Object *& libraries_arg,
			 Object *& predicate_list_arg,
			 Object *& function_list_arg)
{
  Object* argOF = heap.dereference(object_file_arg);
  Object* argL = heap.dereference(libraries_arg);
  Object* argPL = heap.dereference(predicate_list_arg);
  Object* argFL = heap.dereference(function_list_arg);
  
  
  if (argOF->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  
  if (argL->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }
  
  //
  // Link and load the object files and libraries with the emulator.
  //
  if (! LinkLoad(argOF, argL))
    {
      return RV_FAIL;
    }
  
  Object* predList = argPL->variableDereference();
  Object* funcList = argFL->variableDereference();
  
  //
  // Install the predicate with the function as the definition.
  //
  for (;
       predList->isCons() && funcList->isCons();
       predList = OBJECT_CAST(Cons*, predList)->getTail()->variableDereference(),
	 funcList = OBJECT_CAST(Cons*, funcList)->getTail()->variableDereference())
    {
      Object* head = 
	OBJECT_CAST(Cons*, predList)->getHead()->variableDereference();
      if (!head->isStructure() ||
	  OBJECT_CAST(Structure*, head)->getArity() != 2)
	{
	  PSI_ERROR_RETURN(EV_TYPE, 3);
	}
      
      Object* pred = OBJECT_CAST(Structure*, head)->getArgument(1)->variableDereference();
      Object* arity = OBJECT_CAST(Structure*, head)->getArgument(2)->variableDereference();
      Object* fn = OBJECT_CAST(Cons*, funcList)->getHead()->variableDereference();
      
      if (!pred->isAtom() ||
	  !arity->isShort() ||
	  !(0 <= arity->getInteger() && 
	    arity->getInteger() <= (signed) ARITY_MAX) ||
	  !fn->isAtom())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 4);
	}
      
      predicates->addEscape(atoms, OBJECT_CAST(Atom*, pred), 
			    arity->getInteger(),
			    FnAddr(OBJECT_CAST(Atom*, fn)->getName()), code);
    }
  
  if (!predList->isNil())
    {
      PSI_ERROR_RETURN(EV_RANGE, 3);
    }
  if (!funcList->isNil())
    {
      PSI_ERROR_RETURN(EV_RANGE, 4);
    }
  
  return RV_SUCCESS;
}







