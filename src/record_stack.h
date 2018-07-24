// record_stack.h - Stack class deals with individual elements while
//		    RecordStack class handles variable size records.  Hence,
//		    RecordStack is derived from Stack.
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
// $Id: record_stack.h,v 1.3 2001/06/07 05:18:12 qp Exp $

#ifndef	RECORD_STACK_H
#define	RECORD_STACK_H

#include "area_offsets.h"
#include "defs.h"
#include "stack_qp.h"

//
// After a record is pushed onto the stack, the previous top of stack is
// pushed onto the stack.  So poping a record is a matter restoring the top of
// stack to previous value.  Hence, the size of the record is not required.
// This approach makes the stack management simplier in the multiple page
// model because no record is not allowed to break up and store in two pages,
// and no need to worry about the amount of unused space left on previous
// page.
//
class	RecordStack : public PrologStack <StackWord>
{

protected:

	//
	// Return the name of the table.
	//
virtual	const char	*getAreaName(void) const
			{ return("record stack"); }

	//
	// Push a record onto the stack.
	// The old top of stack is pushed after the allocation of the record.
	// This makes internal maintenance easier.
	//
	StackLoc	pushRecord(const word32 size)
          {
	    StackLoc	OldTop, record;

	    OldTop = getTopOfStack();
	    record = allocateBlock(size);		// Allocate record.
	    pushElement((StackWord)(OldTop));	// Push the old top of stack.
	    return(record);
          }
	
	//
	// Pop the topmost record off the stack.
	//
	void		popRecord(void)
			{
				setTopOfStack((StackLoc)(popElement()));
			}

	//
	// Reduce the size of the record on the top of the stack, pointed by
	// 'loc', to 'size'.  The size is defined in bytes.
	//
	void		trimRecord(const StackLoc loc, const word32 size)
          {
	    StackLoc	OldTop;

	    OldTop = (StackLoc)(popElement());
	    setTopOfStack(loc + roundBasicUnit(size, sizeof(StackWord)));
	    pushElement((StackWord)(OldTop));
          }

	//
	// Return the previous top of stack, which is stored at the location
	// beneath the start of the record.
	//
	StackLoc	previousTop(const StackLoc loc)	const
			{ return(*inspectAddr(loc - 1)); }

	//
	// Change the value for the previous top of stack.
	//
	void		changePreviousTop(const StackLoc loc,
					  const StackLoc NewValue)
			{ *fetchAddr(loc - 1) = NewValue; }

	//
	// Get the number of StackWords in a record of size bytes
	// including the internal maintenance data.
	//
	word32		numberOfStackWords(const word32 size) const
			{
				return(roundBasicUnit(size,sizeof(StackWord))
				       + 1);
			}

	//
	// Reset the top of stack to after the record pointed by 'loc',
	// including the internal maintenance data.  The size of the record is
	// defined by 'size' in bytes.
	//
	void		resetTopOfStack(const StackLoc loc, const word32 size)
			{
				setTopOfStack(loc +
					      roundBasicUnit(size, 
							sizeof(StackWord)) +
					      1);
			}

public:

	RecordStack(word32 size, word32 overflow) :
				PrologStack <StackWord> (size, overflow)
			{}

};

#endif	// RECORD_STACK_H
