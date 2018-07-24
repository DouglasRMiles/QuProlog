// pred_table.h - The predicate table is a hash table providing the link
//		  between the predicate name and its code.  Each entry is
//		  hashed on the predicate name and its arity.  Rather using
//		  the string of the predicate name, the atom is used.
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
// $Id: pred_table.h,v 1.7 2006/02/05 22:14:55 qp Exp $

#ifndef	PRED_TABLE_H
#define	PRED_TABLE_H

#include <iostream>

#include "config.h"

#include "area_offsets.h"
#include "code.h"
#include "dynamic_code.h"
#include "defs.h"
#include "hash_table.h"
#include "magic.h"
#include "foreign_interface.h"
//
// Forward declaration.
//
class	Thread;
class   DynamicPredicate;

//
// Prototyping an escape function.
//
typedef	bool (*EscFn)(ForeignInterface*);

//
// Hold the code address for the predicate or an escape function.
//
class	PredCode
{
 public:
  enum PredType { ESCAPE_PRED, STATIC_PRED, DYNAMIC_PRED };
  
private:

  PredType	predClass;
  union
  {
    CodeOffset	pred;	// Start of the predicate.
    EscFn	escape;	// An escape function.
    DynamicPredicate* dyn_pred;
  } address;

public:

  //
  // Initialisation functions.
  //
  void	makeEscape(const EscFn f)
  { predClass = ESCAPE_PRED; address.escape = f; }

  void  initPredicate(void)
    {
      predClass = STATIC_PRED;
      address.pred = EMPTY_LOC;
    }

  void	makePredicate(const PredType t, const CodeLoc addr, Code *code)
    { 
      assert(t == STATIC_PRED); 
      predClass = t; 
      if (addr == NULL)
	{
	  address.pred = EMPTY_LOC;
	}
      else
	{
	  address.pred = static_cast<CodeOffset>(addr - code->getBaseOfStack()); 
	}
    }

  void  makeDynamicPredicate(DynamicPredicate* addr)
  { predClass = DYNAMIC_PRED; address.dyn_pred = addr; }
  
  //
  // Retrieval functions.
  //
  EscFn	getEscape(void) const
  { assert(predClass == ESCAPE_PRED); return(address.escape); }

  CodeLoc	getPredicate(Code *code) const
    {  
      assert(predClass == STATIC_PRED);
      return(address.pred + Code::SIZE_OF_HEADER + code->getBaseOfStack()); 
    }

  DynamicPredicate* getDynamicPred(void) const
  { assert(predClass == DYNAMIC_PRED); return(address.dyn_pred); }

  PredType	type(void)	const		{ return(predClass); }
};

//
// Information needed for both hashing and storing.
//
class	PredEntry
{

private:

  AtomLoc predicateName;	// The atom representing the predicate name.
  word32 predicateArity;
  PredCode predicateCode;
  
public:
  
  //
  // Get the name of the predicate.
  //
  Atom*		getPredName(AtomTable *atoms) const	
    { return(predicateName + atoms->getAddress(0)); }
  
  //
  // Get the arity of the predicate.
  //
  word32		getArity(void) const	{ return(predicateArity); }
  
  //
  // Retrieve the code of the predicate.
  //
  PredCode&	getCode(void) 		{ return(predicateCode); }

  const PredCode& inspectCode(void) const { return predicateCode; }

  //
  // Initialize an entry.
  //
  void init(const PredCode code)
    {
      predicateName = EMPTY_LOC;
      predicateArity = 0;
      predicateCode = code;
    }

  //
  // Assign the values to the entry.
  //
  void	assign(Atom* PredName, const word32 arity,
	       const PredCode code, AtomTable* atoms)
  {
    if (PredName == NULL)
      {
	predicateName = EMPTY_LOC;
      }
    else
      {
	predicateName = static_cast<AtomLoc>(PredName - atoms->getAddress(0));
      }
    predicateArity = arity;
    predicateCode = code;
  }
  
  //
  // Check whether the entry is empty.
  //
  bool	isEmpty(void) const
  { return(predicateName == EMPTY_LOC); }
  
  //
  // The two entries are equal if their predicate names and arities
  // are equal.
  //
  bool	operator==(const PredEntry& e) const
  {
    return(predicateName == e.predicateName &&
	   predicateArity == e.predicateArity);
  }
  
  //
  // Using the atom table offset and arity to hash into the predicate
  // table.
  //
  PredLoc	hashFn(void) const
  { return(((word32)predicateName * 167) ^ predicateArity); }
  
  PredEntry(void)
  {
    PredCode	code;
    
    code.initPredicate();
    init(code);
  }
};

//
// Each entry is hashed on the pointer to the predicate name 
// and the predicate arity.
//
// If the predicate is a dynamic predicate (i.e. predClass == DYNAMIC_PRED)
// then the address is the address of a dynamic code object.
//
// If the predicate is a static predicate (i.e. predClass == STATIC_PRED)
// the address points to the code where the preamble starts.
//	Pred Table	Code
//	|	|    |		|
//	+-------+    +----------+
//	|	|--> | Preamble |
//	+-------+    +----------+
//	|	|    |   Byte   |
//		     |   Code   |
//		     +----------+
//		     |		|
//
// If the predicate is an escape function, including foreign functions (i.e.
// predClass == ESCAPE_PRED), the address points to the C++ function directly.
//	Pred Table
//	|	|
//	+-------+
//	|	|--> C++ function
//	+-------+
//	|	|
//
// Error messages that can be reported:
//	Warning.
//
class PredTab : public HashTable <PredEntry, PredEntry>
{

private:
  //
  // Calculate the hash value for a given entry.
  //
  PredLoc hashFunction(const PredEntry entry) const
  { return(entry.hashFn()); }
  
  //
  // Return the name of the table.
  //
  virtual const char *getAreaName(void) const { return("predicate table"); }

  //
  // Add a new entry (a predicate or an escape function) to the
  // predicate table.
  // Warning of redefinition of a predicate is reported if another
  // definition of the same predicate is added.
  //
  PredLoc add(AtomTable* atoms,
	      Atom* PredName, const word32 arity,
	      const PredCode code, Code* codePtr);
  
  //
  // Insert an escape function into the table.
  //
  void	insertEscape(AtomTable* atoms, const char *name, const word32 arity, 
		     Code* code)
  {
    PredCode        escape;
    
    escape.makeEscape(NULL);
    add(atoms, atoms->add(name), arity, escape, code);
  }
  
public:
  PredTab(AtomTable* atoms, word32 TableSize);
  
  //
  // Check whether the entry is empty or not.
  //
  bool	isEmpty(const PredLoc index) const
  { return(inspectEntry(index).isEmpty()); }
  
  //
  // Get the name of the predicate.
  //
  Atom* getPredName(const PredLoc index, AtomTable* atoms) const
  { return(inspectEntry(index).getPredName(atoms)); }
  
  //
  // Get the arity of the predicate.
  //
  word32 getArity(const PredLoc index) const
  { return(inspectEntry(index).getArity()); }
  
  //
  // Get the code component of the predicate.
  //
  PredCode& getCode(const PredLoc index)
    { return(getEntry(index).getCode()); }

  const PredCode& inspectCode(const PredLoc index) const
    { return inspectEntry(index).inspectCode(); }

  //
  // Look up an existing entry.  If it exists, return a pointer to the
  // entry.  Otherwise, it returns EMPTY_LOC.
  //
  PredLoc lookUp(Atom* PredName, const word32 arity, AtomTable* atoms, 
		 Code* code)
  {
    PredEntry entry;
    PredCode pred;
    
    pred.initPredicate();
    entry.assign(PredName, arity, pred, atoms);
    return(lookUpTable(entry));
  }
  
  //
  // Reset the code location (Entry point) to EMPTY_LOC.
  // This is used by the buffer code and is a spin-off from sbprolog.
  //
  void resetEp(Atom* PredName, const word32 arity, AtomTable* atoms, 
	       Code* code);
  
  //
  // Add a new entry to the predicate table.
  // Warning of redefinition of a predicate is reported if another
  // definition of the same predicate is added.
  //
  PredLoc addPredicate(AtomTable* atoms,
		       Atom* PredName, const word32 arity,
		       const PredCode::PredType type, const CodeLoc code,
		       Code* codePtr)
    {
      PredCode pred;
      
      pred.makePredicate(type, code, codePtr);
      return(add(atoms, PredName, arity, pred, codePtr));
    }
  
  PredLoc addDynamicPredicate(AtomTable* atoms, 
		              Atom* PredName, const word32 arity,
                              DynamicPredicate* addr, Code* code)
    {
      PredCode pred;
      pred.makeDynamicPredicate(addr);
      return(add(atoms, PredName, arity, pred, code));
    }
  
  //
  // Add a new escape function to the predicate table.
  // Warning of redefinition of a predicate is reported if another
  // definition of the same predicate is added.
  //
  PredLoc addEscape(AtomTable* atoms,
		    Atom* PredName,
		    const word32 arity,
		    const EscFn f, Code* code)
  {
    PredCode pred;
    
    pred.makeEscape(f);
    return(add(atoms, PredName, arity, pred, code));
  }
  
  //
  // Link an escape function with its name.
  //
  void	linkEscape(AtomTable* atoms,
		   const char *name, const word32 arity, const EscFn f);
  
  //
  // Return the size of the table.
  //
  word32 size(void) const { return(allocatedSize()); }
  
  //
  // Save the predicate table.
  //
  void save(ostream& ostrm) const { saveTable(ostrm, PRED_TABLE_MAGIC_NUMBER); }
  
  //
  // Restore the predicate table.
  //
  void	load(istream& istrm) { loadTable(istrm); }
};

#endif	// PRED_TABLE_H








