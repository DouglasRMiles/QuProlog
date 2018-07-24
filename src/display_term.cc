// display_term.cc -
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
// $Id: display_term.cc,v 1.7 2005/03/08 00:35:02 qp Exp $

#include "config.h"
#ifdef GCC_VERSION_2
#include <ostream.h>
#else
#include <ostream>
#endif

//#include "atom_table.h"
#include "heap_qp.h"
#include "indent.h"

void
Heap::display_term(ostream& ostrm, AtomTable& atoms, Object* term,
		   const size_t depth)
{
  Indent(ostrm, depth);

  if (term->isVariable())
    {
      Object* ref = term;

      ostrm << "VARIABLE ";

      while (ref->isVariable() && 
	     ref != OBJECT_CAST(Reference*, ref)->getReference() &&
	     reinterpret_cast<heapobject*>(ref) < getTop())
	{
	  ostrm << hex << reinterpret_cast<wordptr>(ref) << "->" << dec;
	  ref = OBJECT_CAST(Reference*, ref)->getReference();
	}

      if (ref->isVariable() &&
	  reinterpret_cast<heapobject*>(ref) >= getTop())
	{
	  ostrm << "<< Invalid reference: " << hex << reinterpret_cast<wordptr>(ref) << dec << ">>" << endl;
	}
      else if (ref->isVariable() && 
	       ref == OBJECT_CAST(Reference*, ref)->getReference())
	{
	  if (!OBJECT_CAST(Reference*, ref)->hasExtraInfo())
	    {
	      ostrm << "<< No Extra Info >>";
	    }
	  else
	    {
	      Atom* name = OBJECT_CAST(Reference*, ref)->getName();
	      if (name == NULL)
		{
		  ostrm << ": << No Name >>";
		}
	      else
		{
		  ostrm << ":" << name->getName();
		}
	      // Print out any other information.
	      if (OBJECT_CAST(Variable*, ref)->isOccursChecked())
		{
		  ostrm << ":" << "occurs";
		}
	      if (OBJECT_CAST(Variable*,ref)->isThawed())
		{
		  ostrm << ":" << "thawed";
		}
	      if (OBJECT_CAST(Variable*,ref)->isFrozen())
		{
		  ostrm << ":" << "frozen";
		}
	    }
	}
      else
	{
	  ostrm << endl;
	  
	  display_term(ostrm, atoms, ref, depth);
	}
    }
  
  else if (term->isObjectVariable())
    {
      Object* ref = term;
      
      ostrm << "OBJECT_VARIABLE";

      ostrm << " ";

      while (ref->isObjectVariable() && 
	     ref != OBJECT_CAST(Reference*, ref)->getReference() &&
	     reinterpret_cast<heapobject*>(ref) < getTop())
	{
	  ostrm << hex << reinterpret_cast<wordptr>(ref) << "->" << dec;
	  ref = OBJECT_CAST(Reference*, ref)->getReference();
	}
      if (ref->isObjectVariable() &&
	  reinterpret_cast<heapobject*>(ref) >= getTop())
	{
	  ostrm << "<< Invalid reference: " << hex << reinterpret_cast<wordptr>(ref) << dec << ">>" << endl;
	}
      else if (ref->isObjectVariable() && 
	       ref == OBJECT_CAST(Reference*, ref)->getReference())
	{
	  if (!OBJECT_CAST(Reference*, ref)->hasExtraInfo())
	    {
	      ostrm << "<< No Extra Info >>";
	    }
	  else
	    {
	      Atom* name = OBJECT_CAST(Reference*, ref)->getName();
	      if (name == NULL)
		{
		  ostrm << ": << No Name >>";
		}
	      else
		{
		  ostrm << ":" << name->getName();
		}

	      if (ref->isThawedVariable())
		{
		  ostrm << ":" << "thawed";
		}
	      if (ref->isFrozenVariable())
		{
		  ostrm << ":" << "frozen";
		}
	    }
	}
      else
	{
	  ostrm << endl;
      
	  display_term(ostrm, atoms, ref, depth);
	}
    }
  else if (term->isCons())
    {
      ostrm << "LIST [" << hex << reinterpret_cast<wordptr>(term) << "]" << dec << endl;

      display_term(ostrm, atoms, OBJECT_CAST(Cons*, term)->getHead(), depth+1);
      display_term(ostrm, atoms, OBJECT_CAST(Cons*, term)->getTail(), depth+1);
    }
  else if (term->isStructure())
    {
      ostrm << "STRUCTURE [" << hex << reinterpret_cast<wordptr>(term) << "]" << dec << endl;

      ostrm << " " << static_cast<u_int>(OBJECT_CAST(Structure*, term)->getArity()) << endl;

      display_term(ostrm, atoms, 
		   OBJECT_CAST(Structure*, term)->getFunctor(), depth+1);

      for (u_long i = 1; i <= OBJECT_CAST(Structure*, term)->getArity(); i++)
	{
	  display_term(ostrm, atoms,
		       OBJECT_CAST(Structure*, term)->getArgument(i), depth+1);
	}
    }
  else if (term->isQuantifiedTerm())
    {
      ostrm << "QUANTIFIER [" << hex << reinterpret_cast<wordptr>(term) << "]" << dec << endl;

      display_term(ostrm, atoms, 
		   OBJECT_CAST(QuantifiedTerm*, term)->getQuantifier(), 
		   depth+1);
      display_term(ostrm, atoms, 
		   OBJECT_CAST(QuantifiedTerm*, term)->getBoundVars(), 
		   depth+1);
      display_term(ostrm, atoms, 
		   OBJECT_CAST(QuantifiedTerm*, term)->getBody(), depth+1);
    }
  else if (term->isAtom())
    {
      ostrm << "ATOM:" << hex << reinterpret_cast<wordptr>(term) << ":" << dec <<OBJECT_CAST(Atom*, term)->getName() <<  endl;
    }
  else if (term->isInteger())
    {
      ostrm << "INTEGER:" << hex << reinterpret_cast<wordptr>(term) << ":" << dec << term->getInteger() <<  endl;
    }
  else if (term->isSubstitution())
    {
      ostrm << "SUBSTITUTION" << endl;
    }
  else
    {
      ostrm << "*** Bad Value = " << hex << reinterpret_cast<wordptr>(term) << ":" << dec <<  endl;
    }
}      

void
Heap::displayTerm(ostream& ostrm, AtomTable& atoms,
		  Object* term, const size_t depth)
{
  display_term(ostrm, atoms, term, depth);
}

void
Heap::quick_display_term(ostream& ostrm, AtomTable& atoms, Object* term)
{
  term = term->variableDereference();
  
  if (term->isVariable())
    {
      cerr << "_V";
    }
  else if (term->isObjectVariable())
    {
      ostrm << "_OV";
    }
  else if (term->isCons())
    {
      ostrm << "[";

      quick_display_term(ostrm, atoms, OBJECT_CAST(Cons*, term)->getHead());
      
      ostrm << "|";
      
      quick_display_term(ostrm, atoms, OBJECT_CAST(Cons*, term)->getTail());
      
      ostrm << "]";
    }
  else if (term->isStructure())
    {
      quick_display_term(ostrm, atoms,
			 OBJECT_CAST(Structure*, term)->getFunctor() );
      
      if (OBJECT_CAST(Structure*, term)->getArity() > 0)
	{
	  ostrm << "(";
	  
	  for (u_long i = 1; i <= OBJECT_CAST(Structure*, term)->getArity(); i++)
	    {
	      quick_display_term(ostrm, atoms,
				 OBJECT_CAST(Structure*, term)->getArgument(i));
	      if (i < OBJECT_CAST(Structure*, term)->getArity())
		{
		  ostrm << ",";
		}
	    }
	  
	  ostrm << ")";
	}
    }
  else if (term->isQuantifiedTerm())
    {
      quick_display_term(ostrm, atoms,
			 OBJECT_CAST(QuantifiedTerm*, term)->getQuantifier());
      ostrm << " ";
      quick_display_term(ostrm, atoms, 
			 OBJECT_CAST(QuantifiedTerm*, term)->getBoundVars());
      ostrm << " ";
      quick_display_term(ostrm, atoms, 
			 OBJECT_CAST(QuantifiedTerm*, term)->getBody());
    }
  else if (term->isAtom())
    {
      ostrm << OBJECT_CAST(Atom*, term)->getName();
    }
  else if (term->isInteger())
    {
      ostrm << term->getInteger();
    }
  else if (term->isDouble())
    {
      ostrm << term->getDouble();
    }
  else if (term->isSubstitution())
    {
      ostrm << "SUBSTITUTION" << endl;
    }
  else
    {
      ostrm << "*** Bad Value = " << hex << reinterpret_cast<wordptr>(term) << dec << endl;
    }
}      

void
Heap::quickDisplayTerm(ostream& ostrm, AtomTable& atoms, Object* term)
{
  quick_display_term(ostrm, atoms, term);
  ostrm << '\0';
}




