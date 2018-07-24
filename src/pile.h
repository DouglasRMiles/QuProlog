// pile.h - Definition of the pile (Qu-Prolog stack).
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
// $Id: pile.h,v 1.5 2006/01/31 23:17:51 qp Exp $

#ifndef	PILE_H
#define	PILE_H

#include "defs.h"
#include "prolog_value.h"
#include "stack_qp.h"

template <class StoredType>
class	Pile : public PrologStack <StoredType>
{

private:

	//
	// Return the name of the area.
	//
virtual	const char	*getAreaName(void)	const	{ return("pile"); }

public:

	//
	// Push a StoredType onto the pile.
	//
	void	push(const StoredType s){ this->pushElement(s); }

	//
	// Pop a StoredType off the pile.
	//
	StoredType	pop(void)	{ return(this->popElement()); }

	//
	// Pop n entries of StoredType off the pile.
	//
	void	popNEntries(word32 n)	{ this->setTopOfStack(this->getTopOfStack() - n); }

	//
	// Check whether the pile is empty or not.
	//
	bool	isEmpty(void)	const	{ return(this->getTopOfStack() == 0); }

	//
	// Return the size of the pile in use.
	//
	word32	size(void)	const	{ return(this->sizeOfStack()); }

	//
	// Empty the pile.
	//
	void	clear(void)		{ this->clearStack(); }

	explicit Pile(word32 size = PILE_SIZE) :
			PrologStack <StoredType> (size, PILE_SIZE / 10)
					{}
};

class	PushDownStack : public Pile <Object*>
{

public:

	explicit PushDownStack(word32 size = PILE_SIZE) : Pile <Object*> (size)
					{}
	~PushDownStack(void)		{}
};

#endif	// PILE_H
