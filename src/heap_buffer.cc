// heap_buffer.cc - Contains buffer management code.
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
// $Id: heap_buffer.cc,v 1.5 2006/01/31 23:17:50 qp Exp $

#include	<stdio.h>
#include	<string.h>

#include "heap_buffer.h"

extern const char *Program;

word32
HeapBufferManager::allocate(heapobject* heapTop, heapobject* scratchTop)
{
  word32 index = top++;	// index to new buffer.

  if (index >= size)
    {
      Fatal(__FUNCTION__, "Out of heap buffers");
    }
  else
    {
      buffers[index].init(heapTop, scratchTop);
    }
  return(index);
}

void 
HeapBufferManager::deallocate(word32 bindex)
{
  assert(bindex == (top - 1));
  buffers[bindex].init(NULL, NULL);
  top--;
}





