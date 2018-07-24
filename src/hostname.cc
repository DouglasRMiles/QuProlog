// hostname.cc -
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
// $Id: hostname.cc,v 1.4 2005/03/08 00:35:07 qp Exp $

#include "config.h"

#include <stdlib.h>

#include <sys/types.h>

#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

#ifdef GCC_VERSION_2
#include <iostream.h>
#else
#include <iostream>
#endif

#include "errors.h"
#include "hostname.h"

extern const char *Program;

void
hostname(char *name, const size_t len)
{
#ifndef WIN32
  SYSTEM_CALL_LESS_ZERO(gethostname(name, len));
#endif
}


