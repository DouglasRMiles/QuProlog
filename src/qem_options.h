// qem_options.h - Options parsing for qem.
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
// $Id: qem_options.h,v 1.5 2006/04/04 01:56:36 qp Exp $

#ifndef QEM_OPTIONS_H
#define QEM_OPTIONS_H

#include <sys/types.h>

#include "defs.h"
#include "option.h"
#include "options.h"
//#include "string_qp.h"

// #include "atom_table.h"

class QemOptions: public Options
{
private:
  Option<word32> code_size;
  Option<word32> string_table_size;
  Option<word32> predicate_table_size;
  Option<word32> atom_table_size;
  Option<word32> name_table_size;
  Option<word32> heap_size;
  Option<word32> environment_stack_size;
  Option<word32> choice_stack_size;
  Option<word32> binding_trail_size;
  Option<word32> other_trail_size;
  Option<word32> string_map_size;
  Option<word32> ip_table_size;
  Option<word32> scratchpad_size;
  Option<word32> thread_table_size;
  Option<bool> stand_alone;
  Option<char *> qx_file;
  Option<char *> pedro_server;
  Option<u_short> pedro_port;	// Host byte order.
  Option<char *> process_symbol;
  Option<char *> initial_goal;
  Option<char *> initial_file;
  Option<bool> debugging;

  int prolog_argc;
  char **prolog_argv;

public:
  word32 CodeSize(void) const { return code_size.Value(); }
  word32 StringTableSize(void) const { return string_table_size.Value(); }
  word32 PredicateTableSize(void) const { return predicate_table_size.Value(); }
  word32 AtomTableSize(void) const { return atom_table_size.Value(); }
  word32 NameTableSize(void) const { return name_table_size.Value(); }
  word32 IPTableSize(void) const { return ip_table_size.Value(); }
  word32 HeapSize(void) const { return heap_size.Value(); }
  word32 ScratchpadSize(void) const { return scratchpad_size.Value(); }
  word32 EnvironmentStackSize(void) const { return environment_stack_size.Value(); }
  word32 ChoiceStackSize(void) const { return choice_stack_size.Value(); }
  word32 BindingTrailSize(void) const { return binding_trail_size.Value(); }
  word32 OtherTrailSize(void) const { return other_trail_size.Value(); }
  word32 StringMapSize(void) const { return string_map_size.Value(); }
  word32 ThreadTableSize(void) const { return thread_table_size.Value(); }

  char *QxFile(void) const { return qx_file.Value(); }

  bool StandAlone(void) const { return stand_alone.Value(); }

  char *PedroServer(void) const { return pedro_server.Value(); }

  // The result is in host byte order.
  u_short PedroPort(void) const { return pedro_port.Value(); }
  
  char *ProcessSymbol(void) const { return process_symbol.Value(); }

  char *InitialGoal(void) const { return initial_goal.Value(); }

  char *InitialFile(void) const { return initial_file.Value(); }

  bool Debugging(void) const { return debugging.Value(); }

  int PrologArgc(void) const { return prolog_argc; }
  char **PrologArgv(void) { return prolog_argv; }

  QemOptions(int c,		// Incoming argc
	     char **v);		// Incoming argv
};

#endif // QEM_OPTIONS_H
