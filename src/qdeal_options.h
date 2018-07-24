// qdeal_options.h - Options parsing for qem.
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
// $Id: qdeal_options.h,v 1.2 2001/11/21 00:21:16 qp Exp $

#ifndef QDEAL_OPTIONS_H
#define QDEAL_OPTIONS_H

#include "defs.h"
#include "option.h"
#include "options.h"

// #include "atom_table.h"

class QdealOptions : public Options
{
private:
  Option<word32> code_size;
  Option<word32> string_table_size;
  Option<word32> predicate_table_size;
  Option<word32> atom_table_size;
  Option<word32> string_map_size;

  Option<const char *> qx_file;

public:
  word32 CodeSize(void) const { return code_size.Value(); }
  word32 StringTableSize(void) const { return string_table_size.Value(); }
  word32 PredicateTableSize(void) const { return predicate_table_size.Value(); }
  word32 AtomTableSize(void) const { return atom_table_size.Value(); }
  word32 StringMapSize(void) const { return string_map_size.Value(); }
  const char *QxFile(void) const { return qx_file.Value(); }

  QdealOptions(int c,		// Incoming argc
	       char **v);	// Incoming argv
};

#endif // QDEAL_OPTIONS_H
