// asm_int.h - Integer storage for the assembler.
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
// $Id: asm_int.h,v 1.7 2005/08/31 03:20:19 qp Exp $

#ifndef	ASM_INT_H
#define	ASM_INT_H

#ifdef WIN32
#include <list>
#endif


#include "code_block.h"
#include "int.h"
#include "config.h"

template <class IntType>
class ASMInt: public Int<IntType>
{
public:
  ASMInt(const IntType v,
	 const int m = 0) : Int<IntType>(v, m) { }

  void Put(CodeBlock& code_block) const
  {
    const IntType v = this->value;
    switch (sizeof(IntType))
      {
      case 1:
	code_block.Put(static_cast<char>((word32)v & 0xff));
	break;
      case 2:
	{
	  code_block.Put(static_cast<char>(((word32)v >> 8) & 0xff));
	  code_block.Put(static_cast<char>((word32)v & 0xff));
	}
	break;
      case 4:
	{
	  code_block.Put(static_cast<char>(((word32)v >> 24) & 0xff));
	  code_block.Put(static_cast<char>(((word32)v >> 16) & 0xff));
	  code_block.Put(static_cast<char>(((word32)v >> 8) & 0xff));
	  code_block.Put(static_cast<char>((word32)v & 0xff));
	}
	break;
#if BITS_PER_WORD == 64
      case 8:
	{
	  code_block.Put(static_cast<char>(((wordptr)v >> 56) & 0xff));
	  code_block.Put(static_cast<char>(((wordptr)v >> 48) & 0xff));
	  code_block.Put(static_cast<char>(((wordptr)v >> 40) & 0xff));
	  code_block.Put(static_cast<char>(((wordptr)v >> 32) & 0xff));
	  code_block.Put(static_cast<char>(((wordptr)v >> 24) & 0xff));
	  code_block.Put(static_cast<char>(((wordptr)v >> 16) & 0xff));
	  code_block.Put(static_cast<char>(((wordptr)v >> 8) & 0xff));
	  code_block.Put(static_cast<char>((wordptr)v & 0xff));
	}
	break;
#endif
      }
  }
  
  void Put(CodeBlockLoc loc, CodeBlock& code_block) const
  {
    const IntType v = this->value;
    
    switch (sizeof(IntType))
      {
      case 1:
	code_block.Put(loc, v & 0xff);
	break;
      case 2:
	{
	  code_block.Put(loc++, (v >> 8) & 0xff);
	  code_block.Put(loc++, v & 0xff);
	}
	break;
      case 4:
	{
	  code_block.Put(loc++, (v >> 24) & 0xff);
	  code_block.Put(loc++, (v >> 16) & 0xff);
	  code_block.Put(loc++, (v >> 8) & 0xff);
	  code_block.Put(loc++, v & 0xff);
	}
	break;
#if BITS_PER_WORD == 64
      case 8:
	{
	  code_block.Put(loc++, (((wordptr)v) >> 56) & 0xff);
	  code_block.Put(loc++, (((wordptr)v) >> 48) & 0xff);
	  code_block.Put(loc++, (((wordptr)v) >> 40) & 0xff);
	  code_block.Put(loc++, (((wordptr)v) >> 32) & 0xff);
	  code_block.Put(loc++, (((wordptr)v) >> 24) & 0xff);
	  code_block.Put(loc++, (((wordptr)v) >> 16) & 0xff);
	  code_block.Put(loc++, (((wordptr)v) >> 8) & 0xff);
	  code_block.Put(loc++, ((wordptr)v) & 0xff);
	}
	break;
#endif
      }
  }
};

// Separate type because double is the same size as wordptr
// on 64-bit systems.
template <class IntType>
class ASMDouble: public Int<IntType>
{
public:
  ASMDouble(const IntType v,
	    const int m = 0) : Int<IntType>(v, m) { }

  void Put(CodeBlock& code_block) const
  {
    const IntType v = this->value;
    
    char w[sizeof(double)];
    memcpy(w, &v, sizeof(double));
    for (u_int i = 0; i < sizeof(double); i++)
      code_block.Put(w[i]);
  }
  
  void Put(CodeBlockLoc loc, CodeBlock& code_block) const
  {
    const IntType v = this->value;
    
    char w[sizeof(double)];
    memcpy(w, &v, sizeof(double));
    for (u_int i = 0; i < sizeof(double); i++)
    {
      code_block.Put(loc++, w[i]);
    }
  }
};

#endif	// ASM_INT_H






