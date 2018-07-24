// heap_buffer.h - Qu-Prolog buffer management.
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
// $Id: heap_buffer.h,v 1.5 2006/01/31 23:17:50 qp Exp $

#ifndef	HEAP_BUFFER_H
#define	HEAP_BUFFER_H

//
// Buffers are used in conjunction with the scratchpad for findall 
// and simplifying substitutions.
//

#include "defs.h"
#include "objects.h"

class HeapBuffer
{
private:
  u_int count;       // how many list elements are in the buffer
  heapobject* buffer_start;     // address of the start of the buffer
  Object** tail_address; // the address of the list tail for the next element
  heapobject* initial_heap_top; // the top of heap when buffer allocated

public:
  
  //
  // Access methods.
  //
  u_int 	 getCount(void)	      const { return(count); }
  heapobject*	 getStart(void )      const { return(buffer_start); }
  Object**       getTailAddress(void) const { return(tail_address); }
  heapobject*    getInitialTop(void)  const { return(initial_heap_top); }
  
  void incCount(void)                { count++; }
  void setTailAddress(Object** addr) { tail_address = addr; }

  void init(heapobject* heapTop, heapobject* scratchTop)
    {
      count = 0;
      buffer_start = scratchTop;
      tail_address = NULL;
      initial_heap_top = heapTop;
    }

  HeapBuffer(void)			       
    {
      count = 0;
      buffer_start = NULL;
      tail_address = NULL;
      initial_heap_top = NULL;
    }
      
};

class	HeapBufferManager
{
private:

  HeapBuffer		*buffers;
  word32		size;		// Size of buffers array.
  word32		top;		// Points to the next free entry.
  
public:
  //
  // Check if no buffers have been allocated.
  //
  bool isEmpty(void) { return (top == 0); }

  //
  // Allocate a buffer, return the buffer index.
  //
  word32 allocate(heapobject* heapTop, heapobject* scratchTop);
  
  //
  // Pop the buffer from the scratchpad and release the buffer object.
  //
  void deallocate(word32 bindex);

  //
  // Get the start address of the buffer
  //
  heapobject* getStart(word32 bindex)
    {
      assert(bindex == (top - 1));
      return(buffers[bindex].getStart());
    }

  //
  // Get the initial heap address stored in the buffer
  //
  heapobject* getInitialTop(word32 bindex)
    {
      assert(bindex == (top - 1));
      return(buffers[bindex].getInitialTop());
    }

  //
  // Get the count i.e. number of elements in list of the buffer.
  //
  u_int getCount(word32 bindex)
    {
      assert(bindex == (top - 1));
      return(buffers[bindex].getCount());
    }

  //
  // Increment the count in list of the buffer.
  //
  void incCount(word32 bindex)
    {
      assert(bindex == (top - 1));
      buffers[bindex].incCount();
    }
  
  //
  // Get the address of the list tail of the buffer.
  //
  Object** getTailAddress(word32 bindex)
    {
      assert(bindex == (top - 1));
      return(buffers[bindex].getTailAddress());
    }

  //
  // Set the address of the list tail of the buffer.
  //
  void setTailAddress(word32 bindex, Object** addr)
    {
      assert(bindex == (top - 1));
      buffers[bindex].setTailAddress(addr);
    }


  //
  // Get the list of the buffer.
  //
  Object* getTerm(word32 bindex)
    {
      assert(bindex == (top - 1));
      return(reinterpret_cast<Object*>(buffers[bindex].getStart()));
    }
    

  //
  // Allocate space and initialize.
  //
  explicit HeapBufferManager(word32 NumberOfBuffers)
    {
      buffers = new HeapBuffer [NumberOfBuffers];
      size = NumberOfBuffers; 
      top = 0;
    }
  ~HeapBufferManager(void)
    {
      if (buffers != NULL)
	{
	  delete [] buffers;
	}
      top = 0;
    }
};

#endif  // HEAP_BUFFER_H




