// compiler_support.h -
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
// $Id: compiler_support.h,v 1.10 2006/01/31 23:17:49 qp Exp $

#ifndef	COMPILER_SUPPORT_H
#define	COMPILER_SUPPORT_H

#include "defs.h"
#include "errors.h"
// #include "io_qp.h"

#define WARRAYSIZE 16000
#define REGISTERSIZE 1600

extern const char *Program;

class QPStream;

//
// This class is used for storing the results of phases of the compiler.
// The entries are pointers to heap objects representing "instructions".
//
class WordArray
{
private:
  wordptr   *base;
  int       size;
  int       last;

public:
  explicit WordArray(int s)
    { 
      base = new wordptr[s];
      size = s; 
      last = 0;
    }

  virtual ~WordArray(void)
    { 
      if (base != NULL)
	{
	  delete [] base;
	}
    }

  inline void addEntry(wordptr entry)
    {
      if (last + 1 >= size)
	{
	  Fatal(__FUNCTION__, "Out of compiler array memory");
	}
      base[last++] = entry;
    }

  inline wordptr *Entries(void) { return base; }

  inline int lastEntry(void) { return last; }

  inline void resetLast(int l)
    {
      assert(l >= 0);
      assert(l < size);
      last = l;
    }

};

//
// This class is used to keep track of the lifetimes of X registers.
//
class xreglife
{
private:
  class llist
  {
  private:
    int start;
    int end;
    llist* next;

  public:
    llist(void) { start = 0; end = 0; next = NULL; }
    ~llist(void) {}

    int& getStart(void) { return start; }
    int& getEnd(void) { return end; }
    llist*& getNext(void) { return next; }
  };

  llist** reginfo;
  int size;

public:
  typedef llist* llistptr;
  explicit xreglife(int s) 
    {      
      reginfo = new llistptr[s];

      for (int i = 0; i < s; i++)
	{
	  reginfo[i] = NULL;
	}
      size = s; 
    }
  ~xreglife(void)
    {
      for (int i = 0; i < size; i++)
	{
	  llist* list = reginfo[i];
	  while (list != NULL)
	    {
	      llist* next = list->getNext();
	      delete list;
	      list = next;
	    }
	}
      delete [] reginfo;
    }

void add(int i, int s)
    {
      if (i > size)
	{
	  Fatal(__FUNCTION__, "Out of bounds in xreglife");
	}
      if (reginfo[i] == NULL)
	{
	  reginfo[i] = new llist;
	  reginfo[i]->getStart() = s;
	}
      else
	{
	  llist* next = reginfo[i];
	  while (next->getEnd() != 0 && next->getNext() != NULL)
	    {
	      next = next->getNext();
	    }
	  if (next->getEnd() == 0)
	    {
	      next->getEnd() = s;
	    }
	  else
	    {
	      llist* n = new llist;
	      n->getStart() = s;
	      next->getNext() = n;
	    }
	}
    }


  bool addRange(int i, int s, int e);
    
#if 0
  void display(void)
    {
      for (int i = 0; i < size; i++)
	{
	  if (reginfo[i] != NULL)
	    {
	      cerr << "xreg[" << i << "]: ";

	      for (llist* next = reginfo[i]; 
		   next != NULL; next = next->getNext())
		{
		  cerr << " [" << next->getStart() << ", " << next->getEnd()
		       << "]";
		}
	      cerr << endl;
	    }
	}
    }
#endif // 0
};

#if 0
class range
{
private:
  int start;
  int end;
public:
  range(int s, int e) { start = s; end = e; }
  ~range(void) { }
public:
  int& getStart(void) { return start; }
  int& getEnd(void) { return end; }
};
#endif // 0

void build_lifetime(WordArray&, xreglife&, WordArray&); 

void updateLife(WordArray&, Object*);

bool is_xreg(Object*, long&);

bool is_yreg(Object*);

long yreg_num(Object*);

bool equal_regs(Object*, Object*);

void prefer_registers_aux(WordArray&, xreglife&, WordArray&, int, int, int);

void prefer_registers(WordArray&, xreglife&, WordArray&, int);

void init_live(Object**);
void make_live(Object*, Object*, Object**);
void make_dead(Object*, Object**);
void reverse_make_dead(Object*, Object**);
void make_pseudo_dead(Object*, Object**);
bool is_live(Object*, Object*, Object**);

bool any_assoc_putset(Object*, int, WordArray&);

bool alloc_needed(Object*);

long psi_reg(Object*);

void writeCAtom(char*, QPStream*);

void writeInstructions(WordArray&, QPStream*);

word8* dumpInstructions(WordArray&);



#endif	// COMPILER_SUPPORT_H








