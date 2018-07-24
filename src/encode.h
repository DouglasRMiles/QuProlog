// encode.h - Term encoding and decoding.
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
// $Id: encode.h,v 1.11 2005/03/27 22:07:39 qp Exp $

#ifndef ENCODE_H
#define ENCODE_H

#include "atom_table.h"
#include "objects.h"
#include "defs.h"
// #include "io_qp.h"
#include <vector>

class Heap;
class NameTable;
class Thread;

//
// Map the (meta and object) variables and atoms into unique entries.
//
class	EncodeMap
{
private:
  //
  // The array index cannot be larger than 1 byte because the encoder
  // sends 1 byte.
  // Therefore we consider a vector of tables with the max length of the
  // vector being 256.

  static const int TABLE_MAX	= 256;
  
#ifdef WIN32
  vector<Object**, allocator<Object**> >        vector_of_tables;
#else
  vector<Object**>      vector_of_tables;
#endif
  int top_table_entry;
  int top_vector_entry;
  
public:
  
  static const int32 NOT_FOUND	=             -1;
  static const word8 ENCODE_REFERENCE =        0;
  static const word8 ENCODE_VARIABLE =         1; 
  static const word8 ENCODE_OB_REFERENCE =     2;
  static const word8 ENCODE_OB_VARIABLE =      3;
  static const word8 ENCODE_LIST =             4;
  static const word8 ENCODE_STRUCTURE =        5; 
  static const word8 ENCODE_QUANTIFIER =       6;
  static const word8 ENCODE_ATOM_REF =         7;
  static const word8 ENCODE_ATOM =             8;
  static const word8 ENCODE_INTEGER =          9;
  static const word8 ENCODE_SUBSTITUTION =     10;
  static const word8 ENCODE_SUBSTITUTION_END = 11;
  static const word8 ENCODE_NAME =             12;
  static const word8 ENCODE_REF_OFFSET =       13;
  static const word8 ENCODE_DOUBLE =          14;
  static const word8 ENCODE_STRING =          15;

  //
  // Add.
  //
  void add(Object* c)
  {
    if (top_table_entry < TABLE_MAX)
      {
        vector_of_tables[top_vector_entry-1][top_table_entry++] = c;
      }
    else
      {
	if (top_vector_entry == TABLE_MAX)
	  {
	    cerr << "Not enough space to encode term" << endl;
            exit(1);
          }
	vector_of_tables.push_back(new Object* [TABLE_MAX]);
        top_table_entry = 0;
	vector_of_tables[top_vector_entry++][top_table_entry++] = c;
      }
  }
  
  //
  // Look-up.
  //
  Object* lookUp(word8 i, word8 j) { return(vector_of_tables[i][j]); }

  int32	lookUp(Object* c)
  {
    int i;
    int j;
    
    for (i = 0; i < top_table_entry; i++)
      {
	if (vector_of_tables[top_vector_entry-1][i] == c)
	  {
	    return(TABLE_MAX*(top_vector_entry-1) + i);
	  }
      }
    for (j = 0; j < top_vector_entry-1; j++)
      {
	for (i = 0; i < TABLE_MAX; i++)
	  {
	    if (vector_of_tables[j][i] == c)
	      {
		return(TABLE_MAX*j + i);
	      }
	  }
      }
    return(NOT_FOUND);
  }
  
  Object* getObjectVariableNames(Heap&);
  
  EncodeMap(void)
    {
#ifdef WIN32
      //Or windows will die
          vector_of_tables.reserve(1);
#endif
      vector_of_tables.push_back(new Object*[TABLE_MAX]);
      top_table_entry = 0;
      top_vector_entry = 1;
    }
  ~EncodeMap(void)
    {
      for (int i = 0; i < top_vector_entry; i++)
	{
	  delete [] vector_of_tables[i];
	}
      top_table_entry = 0;
    }
};

//
// Auxiliary class bundles up some useful things.
//
class EncodeBase
{
protected:
  bool success;
  EncodeMap *map;

public:
  EncodeBase(void)
    : map(new EncodeMap())
    {
    }
  ~EncodeBase(void)
    {
      delete map;
    }
  bool Success(void) const { return success; }
};

class EncodeWrite : public EncodeBase {
private:
  //
  // Write a character.
  //
  bool	writeEncodeChar(QPStream&, const word8);
  
  //
  // Encode write a number
  //
  bool writeEncodeNumber(QPStream&, const long);
  //
  // Encode write a double
  //
  bool writeEncodeDouble(QPStream&, const double);
    
  //
  // Encode the atom and write the result to the stream.
  //
  bool	encodeWriteAtom(QPStream&, Atom*, AtomTable& atoms);

  //
  // Encode the string and write the result to the stream.
  //

  bool	encodeWriteString(QPStream&, char*);

  //
  // Encode the variable name and sent it over.
  //
  bool	encodeWriteVarName(Heap&, QPStream&, Object*, AtomTable&);
  
  //
  // Encode the substitution and write the result to the stream.
  //
  bool encodeWriteSub(Thread&, Heap&, QPStream&, Object*, 
		      AtomTable&, const bool, NameTable&);

  bool encodeWriteTerm(Thread&, Heap&, QPStream&, Object*,
		       AtomTable&, const bool, NameTable&);
public:
  EncodeWrite(Thread& th, Heap& heap, QPStream& stream, Object* term,
	      AtomTable& atoms, const bool remember, NameTable& names)
    {
      success = encodeWriteTerm(th, heap, stream, term,
				atoms, remember, names);
    }

};

class EncodeRead : public EncodeBase {
private:
  char *stringbuff;

  //
  // Read a character.
  //
  bool encodeReadChar(QPStream&, word8&);
  
  //
  // Read from a stream and decode back to a string.
  //
  bool encodeReadString(QPStream&, Object*&, Heap&);

  //
  // Read from a stream and decode back to an atom.
  //
  bool encodeReadAtom(QPStream&, Atom*&, AtomTable&);

  //
  // Read a number.
  //
  bool encodeReadNumber(QPStream&, long&);
  //
  // Read a double.
  //
  bool encodeReadDouble(QPStream&, double&);

  //
  // Read from a stream and decode back to the substitution.
  //
  bool encodeReadSub(Thread&, Heap&, QPStream&, Object*&,
		     AtomTable&, const bool, NameTable&);

  bool encodeReadTerm(Thread&, Heap&, QPStream&, Object*&,
		      AtomTable&, const bool, NameTable&);
    
public:
  //
  // Read from a stream and decode back to the term.
  //
  EncodeRead(Thread& th,
	     Heap& heap, QPStream& stream,
	     Object*& term,
	     AtomTable& atoms,
	     const bool remember,
	     NameTable& names,
	     Object*& name_list)
    : stringbuff(new char[ATOM_LENGTH])
  {
    success = encodeReadTerm(th, heap, stream, term, atoms, remember, names);

    if (success)
      {
	name_list = map->getObjectVariableNames(heap);
      }
  }


  ~EncodeRead(void)
    {
      delete [] stringbuff;
    }

 
};

#endif	// ENCODE_H
