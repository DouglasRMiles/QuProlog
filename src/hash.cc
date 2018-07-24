// hash.cc -
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
// $Id: hash.cc,v 1.5 2006/02/01 04:26:02 qp Exp $

#include <sys/types.h>

#include <sstream>

#include "defs.h"
#include "hash_qp.h"


using namespace std;

word32
Hash(const char *s)
{
  word32 value = 5381;
  int c;
  while ((c = *s++))
    {
      value = ((value << 5) + value) + c; /* hash * 33 + c */
    }
  return value;
}

word32
Hash(const char *s, const size_t len)
{
  word32 value = 5381;
  for (size_t i = 0; i < len; i++)
    {
      value = ((value << 5) + value) + *s++; /* hash * 33 + c */
    }

  return value;
}

word32
Hash(const word32 i)
{
  ostringstream ostrm;

  ostrm << i << ends;

  const word32 hash = Hash(ostrm.str().data());

  return hash;
}


