// manager.h - For managing finite collections of things.
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
// $Id: manager.h,v 1.5 2006/01/31 23:17:51 qp Exp $

#ifndef	MANAGER_H
#define	MANAGER_H

#include <stdlib.h>
#include "defs.h"
#include "errors.h"

template <class Type>
class Manager
{
protected:
  word32 MAX;
  Type **elems;

public:
  explicit Manager(const word32 size)
    {
      assert(size > 0);

      MAX = size;

      typedef Type *TypePtr;	// For the benefit of ANSI C++
      elems = new TypePtr[MAX];
     
      assert(elems != NULL);

      for (word32 index = 0; index < MAX; index++)
	{
	  elems[index] = NULL;
	}
    }

  ~Manager(void)
    {
      delete [] elems;
    }

  bool isLegalIndex(const word32 index) const	
    { return index < MAX; }

  bool isElem(const word32 index) const
    { return isLegalIndex(index) && elems[index] != NULL; }
  
  Type &operator[](const word32 index) const
    {
      if (isElem(index))
	{
	  return *elems[index];
	}
      else
	{
	  Fatal(__FUNCTION__, "Bad index argument");
	}
    }

  int nextFree(const word32 start) const
    {
      word32 index;

      for (index = start; index < MAX && elems[index] != NULL; index++)
	;
      
      return (index == MAX) ? -1 : (int) index;
    }

  int nextFree(void) const { return nextFree(0); }
  
  //
  // Grab any slot.
  //
  int grab(Type *e)
    {
      int i = nextFree(0);
      
      if (isLegalIndex(i))
	{
	  elems[i] = e;
	}
      
      return i;
    }

  //
  // Grab a particular slot.
  //
  int grab(const word32 index, Type *e)
    {
      if (isLegalIndex(index))
	{
	  if (isElem(index))
	    {
	      Fatal(__FUNCTION__, "Attempt to overwrite item");
	    }
	  else
	    {
	      elems[index] = e;

	      return index;
	    }
	}
      else
	{
	  Fatal(__FUNCTION__, "Bad index argument ");
	}
    }

  //
  // Grab any slot after the one specified.
  //
  int grabAfter(const word32 start, Type *e)
    {
      int i = nextFree(start);
      
      if (isLegalIndex(i))
	{
	  elems[i] = e;
	}

      return i;
    }

  void release(const word32 index)
    {
      if (isLegalIndex(index))
	{
	  elems[index] = NULL;
	}
    }
};

#endif	// MANAGER_H
