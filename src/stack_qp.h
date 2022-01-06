// stack_qp.h - Fundamental stack arrangement.
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
// $Id: stack_qp.h,v 1.13 2006/01/31 23:17:51 qp Exp $

#ifndef	STACK_QP_H
#define	STACK_QP_H

#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#ifndef WIN32
        #include <unistd.h>
#endif
#include <signal.h>

#include "area_offsets.h"
#include "defs.h"
#include "errors.h"
#include "page_table.h"
#include "timestamp.h"

#include "int.h"

typedef	word32	StackWord;

extern const char *Program;

using namespace std;

//
// This is primary used for stack inspection by statistics.
//
class	FixedSizeStack
{
public:

	//
	// Return the size of the stack in use.  The size is defined as the
	// number of StoredType in the stack.
	//
virtual	word32		sizeOfStack(void) const		{ return(0); }

	//
	// Return the size allocated to the stack.  The size is defined as the
	// number of StoredType in the stack.
	//
virtual	word32		allocatedSize(void) const	{ return(0); }

	//
	// Return the maximum usage for this session.
	//
virtual	word32		maxUsage(void) const		{ return(0); }

 virtual ~FixedSizeStack() {}
};

//
// StoredType is the data type stored in the stack.
// Error messages that can be reported:
//	OutOfPage, BadReset, BadReference, EmptyStack.
//

template <class StoredType>
class	PrologStack : private PageTable <StoredType>,
		      public FixedSizeStack
{

private:

  StackLoc	top;			// Top of stack.
  StackLoc	overflow;		// Overflow boundary.
  StackLoc	highWaterMark;		// Maximum usage for a session.
  
  //
  // Return the name of the table.
  //
  virtual	const char	*getAreaName(void) const
    { return("prolog stack"); }
  
  //
  // Indicate the stack will overflow.
  //
  void		stackWillOverflow(void) const
    {
      ErrArea = getAreaName();
      FatalS(__FUNCTION__, "stack overflow ", ErrArea);
    }
  
  //
  // Raise an exception if the allocation crosses over the overflow
  // boundary.
  //
  void		overflowCheck(const StackLoc OldTop,
			      const StackLoc NewTop)
    {
      if (highWaterMark < NewTop)
	{
	  if (NewTop <= overflow)
	    {
	      highWaterMark = NewTop;
	    }
	  else if (OldTop <= overflow)
	    {
	      stackWillOverflow();
	    }
	}
    }
  
protected:
  
  const StoredType& inspectEntry(const StackLoc s) const
    {
#ifndef NDEBUG
    if (s >= top)
    {
      BadReference(__FUNCTION__, getAreaName(), s);
    }
#endif
      
      return(this->getItem(s));
    }

  //
  // Get the current top of stack location.
  //
  StackLoc	getTopOfStack(void) const	{ return(top); }
  
  //
  // Set the top of the stack.
  // BadReset is reported if the top of stack is reset to anywhere
  // above the current top of stack.
  //
  void		setTopOfStack(const StackLoc NewTop)
    {
/*
      DEBUG_CODE(if (NewTop > top)
		    {
		      BadReset(__FUNCTION__,
			       getAreaName(),
			       NewTop);
		    }
		    );
*/
      top = NewTop;
    }
  
  //
  // Reset the top of the stack to the beginning of the stack.
  //
  void		clearStack(void)		{ setTopOfStack(0); }
  
  const StoredType *inspectAddr(const StackLoc loc) const
    {
#ifndef NDEBUG
      if (loc >= top)
        {
          BadReference(__FUNCTION__,
	    	       getAreaName(),
	    	       loc);
        }
#endif
      return(this->offsetToAddress(loc));
    }
  
  //
  // Push an element onto the stack.
  // OutOfPage is reported if the index table is run out; or
  //
  void	pushElement(const StoredType word)
    {
	this->allocateItems(top, 1);
	this->getItem(top) = word;
	top++;
	overflowCheck(top - 1, top);
    }
  
  //
  // Pop an element off the stack.
  // EmptyStack is reported if it tries to pop beyond the bottom of the
  // stack.
  //
  StoredType	popElement(void)
    {
#ifndef NDEBUG
      if (top == 0)
        {
          EmptyStack(__FUNCTION__,
  		     getAreaName());
        }
#endif
      //
      // Because the top points to next free entry, so
      // decrement the pointer and return the popped
      // value.
      //
      return(this->getItem(--top));
    }
  
  //
  // Allocate 'n' elements of StoredType in the stack.
  // OutOfPage is reported if the index table is run out; or
  //
  StackLoc allocateElements(const word32 n)
    {
	StackLoc	block = top;

	this->allocateItems(top, n);
	top += n;
	overflowCheck(block, top);
	return(block);
    }
  
  //
  // Round 'size' to the next multiple of 'basic' unit.
  //
  word32 roundBasicUnit(const word32 size, const word32 basic) const
    { return((size + basic - 1) / basic); }
  
  //
  // Push a record onto the stack and return a pointer to it.
  // 'size' is given in bytes.
  // OutOfPage is reported if the index table is run out; or
  //
  StackLoc	allocateBlock(const word32 size)
    {
        word32   	elements;
	StackLoc	block, OldTop = top;

	//
	// Round up to the nearest whole StoredType.
	//
        elements = roundBasicUnit(size, sizeof(StoredType));
	block = this->allocateSegment(top, elements);
	top = block + elements;
	overflowCheck(OldTop, top);
	return(block);
    }
  
  //
  // Return the size of the stack in use.  The size is defined as the
  // number of StoredType in the stack.
  //
  virtual word32 sizeOfStack(void) const	{ return(getTopOfStack()); }
  
  //
  // Return the maximum usage for this session.
  //
  virtual word32 maxUsage(void) const		{return(highWaterMark);}
  
  //
  // Write the stack to a stream.
  //
  void		saveStack(std::ostream& ostrm, const wordlong magic) const;
  
  //
  // Load a file segment into the stack.
  //
  void		loadFileSegment(std::istream& istrm, const char *file,
				const word32 size)
    { readData(istrm, file, size, allocateElements(size)); }
  
  //
  // Load the stack from a stream.
  //
  void		loadStack(std::istream& istrm);
  
public:

  //
  // Given an index of a word in the stack, fetch the address.
  // BadReference is reported if reference is made above the current
  // top of stack.
  //
  StoredType *fetchAddr(const StackLoc loc)
    {
#ifndef NDEBUG
      if ((top > 0) && (loc >= top))
      {
	cerr << __FUNCTION__ << " " << loc << " " << top << endl;
	
	BadReference(__FUNCTION__, getAreaName(), loc);
      }
#endif
      return(this->offsetToAddress(loc));
    }

  //
  // Return the size allocated to the stack.  The size is defined as the
  // number of StoredType in the stack.
  //
  virtual word32 allocatedSize(void) const	{ return(this->areaSize()); }

  //
  // Get an element.
  //
  StoredType&	getEntry(const StackLoc s)
    {
#ifndef NDEBUG
      if (s >= top)
      {
        BadReference(__FUNCTION__, getAreaName(), s);
      }
#endif
      
      return(this->getItem(s));
    }

  PrologStack(word32 size, word32 boundary = 0) :
  PageTable <StoredType> (size)
    {
      top = 0;
      highWaterMark = 0;
      overflow =this-> areaSize() - boundary * K;
    }
  virtual	~PrologStack(void);
};



template <class StoredType>
PrologStack<StoredType>::~PrologStack(void)
{
        top = 0;
}

//
// Write the stack to a stream.
//
template <class StoredType>
void
PrologStack<StoredType>::saveStack(ostream& ostrm, const wordlong magic) const
{
  this->saveArea(ostrm, magic, 0, top);
  //
  // Write the top of stack.
  //
  IntSave<StackLoc>(ostrm, top);
}

//
// Load the stack from a stream.
//
template <class StoredType>
void
PrologStack<StoredType>::loadStack(istream& istrm)
{
  this->loadArea(istrm, 0);
  //
  // Read the top of stack.
  //
  top = IntLoad<StackLoc>(istrm);
}

#endif	// STACK_QP_H
