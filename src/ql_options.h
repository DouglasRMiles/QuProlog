// ql_options.h - Options parsing for ql.
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
// $Id: ql_options.h,v 1.2 2001/11/21 00:21:16 qp Exp $

#ifndef QL_OPTIONS_H
#define QL_OPTIONS_H

#include "defs.h"
#include "option.h"
#include "options.h"

#include "ql_options.h"

// #include "atom_table.h"

class QlOptions: public Options
{
private:
  Option<word32> code_size;
  Option<word32> string_table_size;
  Option<word32> atom_table_size;
  Option<word32> predicate_table_size;
  Option<word32> string_map_size;
  Option<char *> executable_file;

  int num_object_files;

  int object_argc;
  char **object_argv;

public:
  word32 CodeSize(void) const { return code_size.Value(); }
  word32 StringTableSize(void) const { return string_table_size.Value(); }
  word32 PredicateTableSize(void) const { return predicate_table_size.Value(); }
  word32 AtomTableSize(void) const { return atom_table_size.Value(); }
  word32 StringMapSize(void) const { return string_map_size.Value(); }

  const char *ExecutableFile(void) const { return executable_file.Value(); }

  int NumObjectFiles(void) const { return num_object_files; }
  int ObjectArgc(void) const { return object_argc; }
  char **ObjectArgv(void) { return object_argv; }

  QlOptions(int c,		// Incoming argc
	     char **v);		// Incoming argv
};

#endif // QL_OPTIONS_H
