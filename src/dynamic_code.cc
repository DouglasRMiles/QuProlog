// dynamic_code.cc - Storage for dynamic code.
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
// $Id: dynamic_code.cc,v 1.14 2006/01/31 23:17:50 qp Exp $  

#include "objects.h"
#include "thread_qp.h"
#include "dynamic_code.h"
//#include "dynamic_hash_table.cc"

extern AtomTable* atoms;
//
// Construct a hash entry for indexing into dynamic code area.
// "Variables" have tag set to 0 - they may match any term. 
// The tag is set to 0 if:
// 1. The term is a variable
// 2. The term is an obvar with a substitution.
// 3. The term is a structure with a non-atom functor.
// 4. The term is a quantifier with a non-atom quant.
//
// Otherwise tag is the cell tag of the term.
// The value part in non-zero if it contains some useful discrimination.
//

//
// Garbage collect the link blocks in the chain whose clause block
// has been retracted.
//
void ChainEnds::gcChain(word32 time, bool deleteBlock)
{
  if (firstPtr == NULL)
    {
      return;
    }

  // The start of the chain
  LinkedClause* start = firstPtr;
  while (start != NULL && start->toDelete(time))
    {
      if (deleteBlock)
	{
	  CodeBlock* blockPtr = start->getCodeBlock();
	  delete blockPtr;
	}
      LinkedClause* tmp = start->getNext();
      delete start;
      start = tmp;
    }

  if (start == NULL)
    {
      firstPtr = NULL;
      lastPtr = NULL;
      return;
    }

  firstPtr = start;

  LinkedClause* step = start;
  LinkedClause* follower = start;

  while (step != NULL)
    {
      follower = step;
      step = step->getNext();
      while (step != NULL && step->toDelete(time))
	{
	  if (deleteBlock)
	    {	  
	      CodeBlock* blockPtr = step->getCodeBlock();
	      delete blockPtr;
	    }
	  LinkedClause* tmp = step->getNext();
	  delete step;
	  step = tmp;
	}
      follower->setNext(step);
    }
  lastPtr = follower;
}


DynamicClauseHashEntry*  
DynamicPredicate::makeEntry(Thread &th, Object* term)
{
  wordptr t, v;
  if (term == NULL) {
    t = 0; v = 0;
    DynamicClauseHashEntry *entry = new DynamicClauseHashEntry(t, v); 
    return entry;
  }
  Object* pterm = term->variableDereference();
  const u_int argTag = pterm->tTag();
  
  switch (argTag)
    {
    case Object::tVar:
      {
        t = 0; v = 0;
      }
      break;
      
    case Object::tObjVar:
      {
	// cannot discriminate between obvars
	t = static_cast<wordptr>(argTag); 
	v = 0;  
      }
      break;
      
    case Object::tCons:
      {
        t = argTag; v = 0;  // no useful info to put in v
      }
      break;
      
    case Object::tStruct:
      {
	Structure* str = OBJECT_CAST(Structure*, pterm);
	
	if (str->getFunctor()->isAtom())
          {
            t = argTag;
 	    v = reinterpret_cast<wordptr>(str->getFunctor());
          }
        else
          {
            t = 0; v = 0;
          }
      }
      break;
      
    case Object::tQuant:
      {
	QuantifiedTerm* quant = OBJECT_CAST(QuantifiedTerm*, pterm);
	
	if (quant->getQuantifier()->isAtom())
          {
            t = argTag;
 	    v = reinterpret_cast<wordptr>(quant->getQuantifier());
          }
        else
          {
            t = 0; v = 0;
          }
      }
      break;
      
    case Object::tShort:
    case Object::tLong:
      {
	t = argTag;
	v = pterm->getInteger();
	break;
      }
    case Object::tDouble:
      {
	t = argTag;
	assert(pterm->isDouble());
	double d = pterm->getDouble();
	u_int x[sizeof(double)];
	*((double*)x) = d;
	v = (x[0] | x[1]) & ~(x[0] & x[1]);
	break;
      }
    case Object::tAtom:
      {
        t = argTag;
	v = reinterpret_cast<wordptr>(pterm);
      }
      break;
    case Object::tString:
      t = Object::tCons; v = 0;
      break;      
    case Object::tSubst:
      {
        PrologValue spterm(pterm);
        th.TheHeap().prologValueDereference(spterm);
        const u_int sargTag = spterm.getTerm()->tTag();
	
	switch (sargTag)
	  {
	  case Object::tCons:
	    {
	      t = sargTag; v = 0;  // no useful info to put in v
	    }
	    break;
	    
	  case Object::tStruct:
	    {
	      Structure* str = OBJECT_CAST(Structure*, spterm.getTerm());
	      
	      if (str->getFunctor()->isAtom())
		{
		  t = sargTag;
		  v = reinterpret_cast<wordptr>(str->getFunctor());
		}
	      else
		{
		  t = 0; v = 0;
		}
	    }
	    break;
	    
	  case Object::tQuant:
	    {
	      QuantifiedTerm* quant = OBJECT_CAST(QuantifiedTerm*, 
						  spterm.getTerm());
	      
	      if (quant->getQuantifier()->isAtom())
		{
		  t = sargTag;
		  v = reinterpret_cast<wordptr>(quant->getQuantifier());
		}
	      else
		{
		  t = 0; v = 0;
		}
	    }
	    break;
	  case Object::tShort:
	  case Object::tLong:
	    {
	      t = argTag;
	      v = pterm->getInteger();
	    }
	  case Object::tDouble:
	    {
	      t = argTag;
	      double d = pterm->getDouble();
	      u_int x[sizeof(double)];
	      *((double*)x) = d;
	      v = (x[0] | x[1]) & ~(x[0] & x[1]);
	    }
	  case Object::tAtom:
	    {
	      t = argTag;
	      v = reinterpret_cast<wordptr>(pterm);
	    }
	    break;
	  case Object::tString:
	    t = Object::tCons; v = 0;
	    break;         
	  default:
	    t = 0;v=0;
	  }
      }
      break;
      
    default:
      t = 0;v=0;
      assert(false);
    }
  DynamicClauseHashEntry *entry = new DynamicClauseHashEntry(t, v); 
  return entry;
}


//
// Add clause to each hash entry - used to add clause with var in indexed arg.
// 
void
DynamicPredicate::addToHashedChains(const bool asserta, CodeBlock* codeBlock)
{
  //
  // Set up hash table iterator
  //
  indexedClauses.iter_reset();
  int index = indexedClauses.iter_next();
  while(index != -1)
    {
      if (asserta)
	{
	  indexedClauses.getEntry(index).addToChainStart(codeBlock);
	}
      else
	{
	  indexedClauses.getEntry(index).addToChainEnd(codeBlock);
	}
      index = indexedClauses.iter_next();
    } 
}

//
// Copy the var clause chain to hash entry.
// Used to copy the var clauses when adding the first clause with
// a given hash value.
//
void
DynamicPredicate::copyVarClauses(ChainEnds& chain)
{
  LinkedClause* iter = varChain.first();
  for (; iter != NULL; iter = iter->getNext())
    {
      chain.addToChainEnd(iter->getCodeBlock());
    }
}

//
// Garbage collect the predicate
//
void DynamicPredicate::gcPredicate(word32 time)
{
#ifdef QP_DEBUG_ASSERT
  cerr << "======== gcPredicate ===========" << endl;
  display();
#endif
  // First go through the hash table without deleting the code blocks
  indexedClauses.iter_reset();
  int index = indexedClauses.iter_next();
  while(index != -1)
    {
      indexedClauses.getEntry(index).getChainEnds()->gcChain(time, false);
      index = indexedClauses.iter_next();
    }
  // Now go through all vars chain without deleting code blocks
  varChain.gcChain(time, false);
  // Finally go through the all chain and delete code blocks
  allChain.gcChain(time, true);
  dirty = false;
#ifdef QP_DEBUG_ASSERT
  display();
#endif
}

// 
// Asserting a new clause.
// indexarg - the term in the index position.
// instrs - a Prolog list representing the instructions for the clause.
// blockPtr - the location of the new clause.
// asserta - front or back?
//
void  
DynamicPredicate::assertClause(Thread &th, Object* indexarg, 
			       Object* instrs,  
			       const bool asserta)
{
  word32 newtime = stamp.GetStamp() + 1;
  instrs = instrs->variableDereference();
  
  CodeLoc code = reinterpret_cast<CodeLoc>(instrs->getInteger());
  CodeBlock* newblock = new CodeBlock(newtime, code, this);

  if (clauseArity == 0)
    {
      //
      // No args to index on so use the all clause chain.
      //
      if (asserta)
	{
	  allChain.addToChainStart(newblock);
	}
      else
	{
	  allChain.addToChainEnd(newblock);
	}
      return;
    }
  //
  // clauseArity > 0
  //
  
  DynamicClauseHashEntry* entry = makeEntry(th, indexarg); 
  
  //
  // add to all clause chain.
  //
  if (asserta)
    {
      allChain.addToChainStart(newblock);
    }
  else
    {
      allChain.addToChainEnd(newblock);
    }
  if (entry->isEmpty())
    {
      //
      // index arg is var so add to var chain.
      //
      if (asserta)
	{
	  varChain.addToChainStart(newblock);
	}
      else
	{
	  varChain.addToChainEnd(newblock);
	}
      //
      // Update existing hash entries.
      //
      addToHashedChains(asserta, newblock);
      delete entry;
    }
  else 
    {
      //
      // Something to add to hash table
      //
      int index = indexedClauses.search(*entry);
      if (index == -1)
	{
	  // Not found - then add
	  indexedClauses.insert(*entry, index);
	}
      delete entry;
      ChainEnds* chainPtr = indexedClauses.getEntry(index).getChainEnds();
      assert(chainPtr != NULL);
      if (chainPtr->first() == NULL)
	{
	  assert(chainPtr->last() == NULL);
	  //
	  // New entry so copy var clauses into this chain.
	  //
	  copyVarClauses(*chainPtr);
	}
      if (asserta)
	{
	  chainPtr->addToChainStart(newblock);
	}
      else
	{
	  chainPtr->addToChainEnd(newblock);
	}
    }
}


#ifdef QP_DEBUG_ASSERT
void 
DynamicPredicate::display()
{

  cerr << "clauseArity = " << (word32)clauseArity << " index arg = " << (word32)indexedArg << endl;
  if (dirty) cerr << "Dirty" << endl;

  cerr << "refcount = " << refcount << " stamp = " << GetStamp() << endl;

  cerr << "------------ allChain -----------------" << endl;

  LinkedClause* iter = allChain.first();
  while (iter != NULL)
    {
      CodeBlock* cb = iter->getCodeBlock();
      assert(this == cb->getThisPred());
      cerr << hex << (word32)cb << dec;
      cerr << ":  createTS = " << cb->getCTS() << " deleteTS = " << cb->getDTS() << " PC = " << (word32)(cb->getCode()) << endl;
      iter= iter->getNext();
    }
   cerr << "------------ varChain -----------------" << endl;

  iter = varChain.first();
  while (iter != NULL)
    {
      CodeBlock* cb = iter->getCodeBlock();
      cerr << hex << (word32)cb << dec;
      iter= iter->getNext();
    }

    cerr << "------------ HashedChains -----------------" << endl;


  indexedClauses.iter_reset();
  int index = indexedClauses.iter_next();
  while(index != -1)
    {
      cerr << "++++ " << index << " ++++" << endl;
      iter = indexedClauses.getEntry(index).getChainEnds()->first();
      while (iter != NULL)
	{
	  CodeBlock* cb = iter->getCodeBlock();
	  cerr << hex << (word32)cb << dec <<endl;
	  iter= iter->getNext();
	}

      index = indexedClauses.iter_next();
    }

}
#endif
