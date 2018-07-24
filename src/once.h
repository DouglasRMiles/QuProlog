// once.h - A class for single assignment things.
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
// $Id: once.h,v 1.3 2006/01/31 23:17:51 qp Exp $

#ifndef	ONCE_H
#define	ONCE_H

#include <stddef.h>

#include "errors.h"

template <class Type>
class Once
{
private:
  bool
  Type once;
public:
  Once(void) : once(NULL) { }

  bool IsSet(void) const { return once != NULL; }
  void Set(const Type& o)
  {
    assert(! once);
    once = o;
  }
  Type& Get(void)
  {
    assert(once);
    return once;
  }
};

#endif	// ONCE_H

