// code_block.h -
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
// $Id: code_block.h,v 1.5 2006/01/31 23:17:49 qp Exp $

#ifndef	CODE_BLOCK_H
#define	CODE_BLOCK_H

//#include <stream>

#include "int.h"
#include "code.h"

typedef u_long CodeBlockLoc;

const u_long INIT_CODE_SIZE = 1000;

enum CodeBlockType { QUERY_BLOCK, PREDICATE_BLOCK };

class CodeBlock
{
private:
  CodeBlockType type;		// Type of code block

  u_long atom;		// Name and arity of code block (predicates only)
  u_long arity;

  char *code;		// Code area, dynamically expanded

  u_long size;		// Current storage allocated for code area
  u_long current;	// Current fullness of code area

  void Expand(void)
    {
      u_long new_size = size * 2;
      char *tmp = new char[new_size];
      
      memcpy(tmp, code, size);
      
      delete [] code;
      
      code = tmp;
      size = new_size;
    }

public:
  CodeBlock(const CodeBlockType t,
	    const u_long at,
	    const u_long ar)
    : type(t),
      atom(at),
      arity(ar),
      code(new char[INIT_CODE_SIZE]),
      size(INIT_CODE_SIZE),
      current(0)
  {

  }

  ~CodeBlock(void)
    {
      delete [] code;
    }

  char operator[](const CodeBlockLoc loc) const
  {
    assert(loc <= current);
    return code[loc];
  }

  CodeBlockType Type(void) const { return type; }
  u_long Atom(void) const { return atom; }
  u_long Arity(void) const { return arity; }

  u_long Current(void) const { return current; }
  u_long Size(void) const { return size; }

  void Advance(u_long n)
    {
      while (current + n > size)
	{
	  Expand();
	}

      current += n;
    }

  // Version of put that sticks chars on the end, expanding the code
  // block when needed.
  // This will be the normal case.
  void Put(char c)
    {
      if (current == size)
	{
	  Expand();
	}

      code[current] = c;
      current++;
    }

  // Version of Put that explicitly supplies a position.
  // This is the case when we are patching the jumps to a label that
  // we've just encountered.
  // Since this use only makes sense when the p <= current,
  // we abort if p > current.
  void Put(u_long p, char c)
    {
      assert(p <= current);

      code[p] = c;
    }

  bool operator==(const CodeBlock& cb) const
  {
    return this == &cb;
  }

  ostream& Save(ostream& ostrm) const;
};

inline ostream& operator<<(ostream& ostrm, const CodeBlock&)
{
  return ostrm << "Code Block";
}


#endif	// CODE_BLOCK_H
