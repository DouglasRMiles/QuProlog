// qa_options.cc - Options for qa.
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
// $Id: qa_options.cc,v 1.2 2005/03/08 00:35:12 qp Exp $

#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

#include <stdlib.h>

#ifdef WIN32
#include "WinXGetopt.h"  // #include "../win32/src/XGetopt.h"
#endif
#include "qa_options.h"

#include "defaults.h"

static const char *INPUT_FILE = NULL;
static const char *OUTPUT_FILE = NULL;

QaOptions::QaOptions(int argc, char **argv)
  : Options("-i input-file\n"
	    "\t-o output-file\n"),
    input_file(INPUT_FILE),
    output_file(OUTPUT_FILE)
{
  int32 c;

  static const char *opts =  "i:o:";

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
#endif
#endif // LINUX
    {
      switch ((char) c)
	{
	case 'i':
	  input_file.Value(optarg);
	  break;
	case 'o':
	  output_file.Value(optarg);
	  break;
	}
    }

  valid = input_file.Value() != NULL &&
    output_file.Value() != NULL;
}
