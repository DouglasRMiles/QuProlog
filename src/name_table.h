// name_table.h - Definitions of the name table for storing variable names
// and the implicit parameter table for storing implicit parameters.
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
// $Id: name_table.h,v 1.6 2006/01/31 23:17:51 qp Exp $

#ifndef	NAME_TABLE_H
#define	NAME_TABLE_H

#include <iostream>

#include "atom_table.h"
#include "area_offsets.h"
#include "objects.h"
#include "defs.h"
#include "hash_table.h"
#include "magic.h"
//#include "thread.h"
//#include "trail.h"

class Thread;

//
// Information stored in the hash table for  variable names.
//
//
class	NameEntry
{

private:

  Atom* name;		// The atom representing the name of the variable.
  Object* value;       // The variable.

public:

  //
  // Assign the values to the entry.
  //
  void	assign(Atom* n, Object* v)
  {
    name = n;
    value = v;
  }

  //
  // Method to extract field.
  //
  Object*&	getValue(void) { return(value); }
  Atom*&       getName(void) { return(name); }
  heapobject*   getValueAddr(void) 
    { return(reinterpret_cast<heapobject*>(&value)); }
  heapobject*   getNameAddress(void) 
    { return(reinterpret_cast<heapobject*>(&name)); }
 
  //
  // Testing method.
  //
  bool	isEmpty(void)		const	{ return(value == NULL); }

  //
  // Using the string to hash into the name table.
  //
  word32 hashFn(void) const
  { return(static_cast<word32>(reinterpret_cast<wordptr>(name))); }
  
  //
  // The two entries are equal if their atom ptrs are the same.
  //
  bool	operator==(const NameEntry& e) const
  { return(name == e.name); }
  
  NameEntry(void)
  {
    name = NULL;
    value = NULL;
  }
};

class 	NameTable : public HashTable <NameEntry, NameEntry>
{
private:
  //
  // Calculate the hash value for a given entry.
  //
  word32 hashFunction(const NameEntry key) const
  { return(key.hashFn()); }
  
  //
  // Add a new entry or update an entry.
  //
  void set(NameEntry key, Thread& th);
  void setVariableName(Atom* index, Object* var, Thread& th)
  {
    NameEntry	entry;
    
    entry.assign(index, var);
    set(entry, th);
  }
  
  //
  // Return the name of the table.
  //
  virtual const char	*getAreaName(void) const
  { return("name table"); }
  
public:
  explicit NameTable(word32 TableSize)
    : HashTable <NameEntry, NameEntry> (TableSize)
    {}
  
  //
  // Retrieve the value field in an entry.
  //
  Object* value(const NameLoc index)
  {
    if (index == EMPTY_LOC)
      {
	return(NULL);
      }
    else
      {
	return getEntry(index).getValue();
      }
  }

  Object* getVariable(Atom* index)
  {
    NameEntry	entry;
    
    entry.assign(index, NULL);
    return(value(lookUpTable(entry)));
  }
  

  void setNameNewVar(Atom* index, Object* var, Thread& th);

  void setNameOldVar(Atom* index, Object* var, Thread& th);
  
#ifdef QP_DEBUG
  void printMe(AtomTable& atoms)
    {
      word32 i;
      
      for (i = 0; i < allocatedSize(); i++)
	{
	  if (! inspectEntry(i).isEmpty())
	    {
	      cerr << endl << i << ": Name" << endl;
	      getEntry(i).getName()->printMe_dispatch(atoms);
	      cerr << endl << "Value" << endl;
	      getEntry(i).getValue()->printMe_dispatch(atoms);
	    }
	}
    }
#endif // DEBUG
  //
  // Save the name table.
  //
  void   save(ostream& strm) const
  { saveTable(strm, NAME_TABLE_MAGIC_NUMBER); }
  
  //
  // Restore the name table.
  //
  void   load(istream& strm)
  { loadTable(strm); }
};


//
// Information stored in the hash table for implicit parameters (IP).
//
class IPEntry
{

private:

  Atom* name;	       // The atom representing the name of the IP.
  Object* value;       // The value of the IP.

  //
  // Assign the values to the entry.
  //
  void	assign(Atom* n, Object* v)
  {
    name = n;
    value = v;
  }

public:

  //
  // Method to extract field.
  //
  Object*&	getValue(void)			{ return(value); }
  heapobject*	getValueAddr(void) 
    { return(reinterpret_cast<heapobject*>(&value)); }
  Object*       getName(void) { return(name); }
  heapobject*   getNameAddress(void) 
    { return(reinterpret_cast<heapobject*>(&name)); }

  //
  // Assign the values to the entry.
  //
  void	implicitPara(Atom* n)
  {
    name = n;
  }
  void	implicitPara(Atom* n, Object* v)
  { assign(n, v); }
  
  //
  // Testing method.
  //
  bool	isEmpty(void)		const	{ return(name == NULL); }

  //
  // Using the string to hash into the name table.
  //
  word32 hashFn(void) const
  { return(static_cast<word32>(reinterpret_cast<wordptr>(name))); }
  
  //
  // The two entries are equal if their atom ptrs are the same.
  //
  bool	operator==(const IPEntry& e) const
  { return(name == e.name); }
  
  IPEntry(void)
  {
    name = NULL;
    value = NULL;
  }
};


class 	IPTable : public HashTable <IPEntry, IPEntry>
{
private:
  //
  // Calculate the hash value for a given entry.
  //
  word32 hashFunction(const IPEntry key) const
  { return(key.hashFn()); }
  
  //
  // Add a new entry or update an entry.
  //
  void set(IPEntry key, Thread& th);
  
  //
  // Return the name of the table.
  //
  virtual const char	*getAreaName(void) const
  { return("IP table"); }
  
public:
  explicit IPTable(word32 TableSize)
    : HashTable <IPEntry, IPEntry> (TableSize)
    {}
  
  
  //
  // Retrieve the value field in an entry.
  //
  Object* value(const IPLoc index)
  {
    if (index == EMPTY_LOC)
      {
	return(NULL);
      }
    else
      {
	return getEntry(index).getValue();
      }
  }

  inline  Object* getImplicitPara(Object* index)
  {
    assert(index->isAtom());
    IPEntry entry;
    
    entry.implicitPara(OBJECT_CAST(Atom*, index));
    return(value(lookUpTable(entry)));
  }

  //
  // Assign value for implicit parameter or variable.
  //
  inline  void setImplicitPara(Object* index, Object* ip, Thread& th)
  {
    assert(index->isAtom());
    IPEntry	entry;
    
    entry.implicitPara(OBJECT_CAST(Atom*, index), ip);
    set(entry, th);
  }

  void   save(ostream& strm) const
    { assert(false); }

  void   load(istream& strm)
    { assert(false); }

#ifdef QP_DEBUG
  void printMe(AtomTable& atoms)
    {
      word32 i;
      
      for (i = 0; i < allocatedSize(); i++)
	{
	  if (! inspectEntry(i).isEmpty())
	    {
	      cerr << endl << i << ": Name" << endl;
	      getEntry(i).getName()->printMe_dispatch(atoms);
	      cerr << endl << "Value" << endl;
	      getEntry(i).getValue()->printMe_dispatch(atoms);
	    }
	}
    }
#endif // DEBUG

};

#endif	// NAME_TABLE_H



