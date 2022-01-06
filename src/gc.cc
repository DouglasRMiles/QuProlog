// gc.cc - Garbage collector.
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
// $Id: gc.cc,v 1.15 2006/01/31 23:17:50 qp Exp $

#include "global.h"
#include "gc.h"
#include "heap_qp.h"
#include "objects.h"


//
// The following garbage collector is an implementation
// of Jonker's algorithm
// 
// -------------------------
//
// Marking phase.
//
// -------------------------

#ifdef QP_DEBUG

//
// Code for checking the heap during and after GC
//

bool check_term(Object* term)
{

  if (term == NULL) return false;

    switch (term->tTag())
    {
    case Object::tVar:
      {
      Object* n  = OBJECT_CAST(Reference*, term)->getReference();
      if (n == term) return true;
      return (check_term(n));
      }
      break;
    case Object::tObjVar:
      {
	Object* n = OBJECT_CAST(Reference*, term)->getReference();
      if (n == term) return true;
      return (check_term(n));
      }
      break;
    case Object::tStruct:
      {
	Structure* s = OBJECT_CAST(Structure *, term);
      for (u_int i = 0; i <= s->getArity(); i++)
	{
	  if (!check_term(s->getArgument(i)))return false;
	}
      return true;
      }
      break;
    case Object::tCons:
      {
	Cons* l = OBJECT_CAST(Cons *, term);
      return (check_term(l->getHead()) && check_term(l->getTail()));
      }
      break;
    case Object::tQuant:
      {
	QuantifiedTerm* q = OBJECT_CAST(QuantifiedTerm *, term);
      return (check_term(q->getQuantifier()) && 
	      check_term(q->getBoundVars()) && check_term(q->getBody()));
      }
      break;
    case Object::tShort:
    case Object::tLong:
    case Object::tDouble:
    case Object::tAtom:
    case Object::tString:
      return true;
      break;
    case Object::tSubst:
      {
	Substitution* s = OBJECT_CAST(Substitution *, term);
      return(check_term(s->getTerm()) && check_term(s->getSubstitutionBlockList()));
      }
      break;
    case Object::tSubBlock:
      {
	SubstitutionBlock * s = OBJECT_CAST(SubstitutionBlock *, term);
      for (u_int i = 1; i <= s->getSize(); i++)
	{
	  if (!check_term(s->getDomain(i)) || !check_term(s->getRange(i)) )return false;
	}
      return true;
      }
      break;
    default:
      return false;
    }
}

bool checkVarExtendedSize(Object* term, int size)
{
  if (size != 5)
    {
      cerr << size << endl;
      heapobject* ptr = reinterpret_cast<heapobject*>(term);
      cerr << hex << (wordlong)(ptr) << " : " << *ptr << " " << *(ptr+1) << dec << endl;
      return false;
    }
  return true;
}
#endif // QP_DEBUG

#define NEXT do {				 \
    if (gcstack.getTop() == savedTop)		 \
      return;					 \
    term = gcstack.pop();			 \
    goto start;					 \
  } while (0)

void gc_mark_pointer(Object* t, Heap& heap, 
		     ObjectsStack& gcstack, GCBits& gcbits)
{
  assert(!t->isSubstitutionBlock());
  Object** savedTop = gcstack.getTop();
  Object* term = t;
  int index;  // offset of term in heap (and gcbits)
  // for a term to be marked it must have an index >= 0 and < last
  int last =  heap.getTop() - heap.getBase(); 

 start:

  index = reinterpret_cast<heapobject*>(term) - heap.getBase();

  // If not a heap pointer or already marked then ignore
  if ((term == NULL) || (index < 0) || (index >= last) || gcbits.isSet(index))
    NEXT;
  
  gcbits.set(index);
  if (term->isNumber() || term->isString())
    NEXT;


  heapobject* startOfStorage = term->storage();
  for (heapobject* next = term->last(); next - startOfStorage > 0; next--)
    {
      gcstack.push((Object*)(*next));
    }
  term = (Object*)(*startOfStorage);
  goto start;

}
	      
// -------------------------
//
// Compaction phase.
//
// -------------------------

// test for GC
bool isPointerGC(heapobject o) { return ((o & GC_B) == 0); }

void updateGC(heapobject* p, heapobject* dest)
{
  heapobject t = *p;
  while (isPointerGC(t))
    {
      heapobject tmp = *((heapobject*)t);
      *((heapobject*)t) = (heapobject)dest;
      t = tmp;
    }
  *p = t;
}

void update_forward_pointers(Heap& heap, GCBits& gcbits)
{
  heapobject* next_free = heap.getBase();
  // find the index of the next word of the bit array past the end
  // assumes that there is at least one word in the heap
  assert((heap.getTop() - heap.getBase()) > 0);
  int max_word_index = 
    1 + (heap.getTop() - heap.getBase())/bitsPerWord;
  int top = max_word_index * bitsPerWord;
  // set up a sentinal word
  gcbits.setWord(max_word_index, 1);
  assert(heap.getTop() - heap.getBase() < top);
  u_int* bitsptr = gcbits.getBitsPtr();
  int offset = 0;

  while (offset < top)
    {
      u_int x = *bitsptr;
      int bitoffset = offset;
      while (x != 0)
	{
	  if ((x & 1) == 1)
	    {
              heapobject* ptr = heap.getBase() + bitoffset;
	      Object* term = reinterpret_cast<Object*>(ptr);
	      assert(gcbits.isSet(bitoffset));
	      
	      updateGC(ptr, next_free);
	      int size = term->size_dispatch();
              if (term->isVariableExtended()) 
                {
                  assert(checkVarExtendedSize(term, size));
                  heapobject* last = term->last();
                  for (heapobject* next = term->storage(); 
                       next < last; next++)
                    {
                      if (heap.isHeapPtr(reinterpret_cast<heapobject*>(*next)))
                        threadGC(next);
                    }
                }
	      else if (!(term->isNumber() || term->isString()))
		{
		  heapobject* last = term->last();
		  for (heapobject* next = term->storage(); 
		       next <= last; next++)
		    {
		      if (heap.isHeapPtr(reinterpret_cast<heapobject*>(*next)))
			threadGC(next);
		    }
		}
	      next_free += size;


	    }
	  x >>= 1;
	  bitoffset++;
	}
      do { bitsptr++; offset += bitsPerWord; } while (*bitsptr == 0);
    }
}

void update_backward_pointers(Heap& heap, GCBits& gcbits)
{
  heapobject* next_free = heap.getBase();
  // find the index of the next word of the bit array past the end
  // assumes that there is at least one word in the heap
  assert((heap.getTop() - heap.getBase()) > 0);
  int max_word_index = 
    1 + (heap.getTop() - heap.getBase())/bitsPerWord;
  int top = max_word_index * bitsPerWord;
  // set up a sentinal word
  gcbits.setWord(max_word_index, 1);

  u_int* bitsptr = gcbits.getBitsPtr();
  int offset = 0;

  while (offset < top)
    {
      u_int x = *bitsptr;
      int bitoffset = offset;
      while (x != 0)
	{
	  if ((x & 1) == 1)
	    {


	      heapobject* ptr = heap.getBase() + bitoffset;
	      Object* term = reinterpret_cast<Object*>(ptr);
	      assert(gcbits.isSet(bitoffset));
	      updateGC(ptr, next_free);
	      int size = term->size_dispatch();
	      memcpy(next_free, ptr, size*sizeof(heapobject));
	      next_free += size;


	    }
	  x >>= 1;
	  bitoffset++;
	}
      *bitsptr = 0;   // zero off bits ready for next GC
      do { bitsptr++; offset += bitsPerWord; } while (*bitsptr == 0);
    }
  *bitsptr = 0;
  heap.setTop(next_free - 1);
}

