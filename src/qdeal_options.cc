// qdeal_options.cc - Options for qdeal.
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
// $Id: qdeal_options.cc,v 1.3 2005/03/08 00:35:12 qp Exp $

#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

#include <stdlib.h>
#ifdef WIN32
#include "WinXGetopt.h" //#include "../win32/src/XGetopt.h"
#endif

#include "qdeal_options.h"

#include "defaults.h"

QdealOptions::QdealOptions(int argc, char **argv)
  : Options("[-a atom-table-size]\n"
	    "\t[-d code-size]\n"
	    "\t[-p predicate-table-size]\n"
	    "\t[-s string-table-size]\n"
	    "\t[-S string-map-size]\n"
	    "\t-Q object-file\n"),
    code_size(CODE_SIZE),
    string_table_size(STRING_TABLE_SIZE),
    predicate_table_size(PREDICATE_TABLE_SIZE),
    atom_table_size(ATOM_TABLE_SIZE),
    string_map_size(STRING_MAP_SIZE),
    qx_file(QX_FILE)
{
  int32 c;

  static const char *opts =  "d:p:s:S:u:M:a:Q:";

  //
  // Parse command line options.
  //
#ifdef LINUX
  while ((c = getopt(argc, argv, opts)),
	 (c != -1 && c != '?'))
#else	// LINUX
#ifdef WIN32
  while ((c = getopt(argc, argv, const_cast<TCHAR*>(opts))) != -1)
#else
  while ((c = getopt(argc, argv, opts)) != -1)
#endif	// LINUX
#endif
    {
      switch ((char) c)
	{
	case 'd':
	  code_size.Value(atoi(optarg));
	  break;
	case 'p':
	  predicate_table_size.Value(atoi(optarg));
	  break;
	case 's':
	  string_table_size.Value(atoi(optarg));
	  break;
	case 'a':
	  atom_table_size.Value(atoi(optarg));
	  break;
	case 'S':
	  string_map_size.Value(atoi(optarg));
	  break;
	case 'Q':
	  qx_file.Value(optarg);
	  break;
	}
    }
  
  argc -= optind;
  
  valid = qx_file.Value() != NULL;
}


