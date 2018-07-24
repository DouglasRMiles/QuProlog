// trail.h - The various trails used by QuProlog.
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
// $Id: trail.h,v 1.13 2006/01/31 23:17:52 qp Exp $

#ifndef	TRAIL_H
#define	TRAIL_H

#include <iostream>

#include "area_offsets.h"
#include "objects.h"
#include "defs.h"
#include "dynamic_code.h"

extern void gc_mark_pointer(Object*, Heap&, ObjectsStack&, GCBits&);

class CleanupEntry;
class UpdatableObjectEntry;
class UpdatableTagEntry;
class PredRefEntry;
//
// A generic trail entry class
//
class TrailEntry
{
 public:
  virtual const word32 size() const = 0;
  virtual void backtrack() = 0;
  virtual bool tidy(TrailLoc tloc,TrailLoc stop,  heapobject* savedH, 
		    Heap& heap) = 0;
  virtual bool operator==(const CleanupEntry& t) const {return false; }
  virtual bool operator==(const UpdatableObjectEntry& t) const {return false; }
  virtual bool operator==(const UpdatableTagEntry& t) const {return false; }
  virtual bool operator==(const PredRefEntry& t) const {return false; }

  virtual void gc_mark(Heap& heap, 
		       ObjectsStack& gcstack, GCBits& gcbits) = 0;
  virtual void gc_sweep(Heap& heap, GCBits& gcbits) = 0;

#ifdef QP_DEBUG
  virtual bool check(Heap& heap) const = 0;
#endif
  virtual ~TrailEntry() {}
};



//
// An updatable object entry
//
class UpdatableObjectEntry : public TrailEntry
{
 private:
  heapobject* addr;
  Object*     old_value;
  u_int       offset;
  
  
 public:
  UpdatableObjectEntry(heapobject* a, Object* o, u_int off) 
    :addr(a),old_value(o), offset(off) {}
    
    const word32 size() const 
    { return sizeof(UpdatableObjectEntry)/sizeof(u_int); }
    
    void backtrack()
    {
      if (addr != NULL)
	*(addr + offset) = reinterpret_cast<heapobject>(old_value);
    }
    
    bool tidy(TrailLoc tloc, TrailLoc stop, heapobject* savedHeapTop, 
	      Heap& heap)
    {
      if (addr == NULL)
	{
	  return true;
	}
      //if (addr >= heap.getSavedTop() && addr < heap.getTop())
      if (addr >= savedHeapTop && addr < heap.getTop())
	{
	  return true;
	}

      TrailLoc loc = tloc;
      while (loc < stop)
	{
	  TrailEntry* entry = (TrailEntry*)loc;
	  if (*entry == *this)
	    {
	      addr = NULL;
	      return true; // XXX break;
	    }
	  loc += entry->size();
	}
      return false;
    }
    
    
    virtual bool operator==(const UpdatableObjectEntry& t) const 
    {return ((addr == t.addr) && (offset == t.offset)); }
    
    void gc_mark(Heap& heap, ObjectsStack& gcstack,
		 GCBits& gcbits)
    {
      if (heap.isHeapPtr(addr) && !gcbits.isSet(addr  - heap.getBase())) 
	return;
      if( heap.isHeapPtr(reinterpret_cast<heapobject*>(old_value)) &&
	  !gcbits.isSet(reinterpret_cast<heapobject*>(old_value) - heap.getBase()))
	{
	  gc_mark_pointer(old_value, heap, gcstack, gcbits);
	}
      
    }
    
    void gc_sweep(Heap& heap, GCBits& gcbits)
    {
      if (heap.isHeapPtr(addr) && !gcbits.isSet(addr  - heap.getBase()))
	{ 
	  addr = NULL;
	  old_value = NULL;
	  return;
	}

      if (heap.isHeapPtr(addr) && gcbits.isSet(addr - heap.getBase()))
	{
	  threadGC(reinterpret_cast<heapobject*>(&addr));
	}
      if ((old_value != NULL) && 
	  heap.isHeapPtr(reinterpret_cast<heapobject*>(old_value)))
	{
	  threadGC(reinterpret_cast<heapobject*>(&old_value));
	}
    }


#ifdef QP_DEBUG
    bool check(Heap& heap) const
    {
      return ((old_value == NULL)
	      || (heap.isActive((heapobject*)old_value) &&
		  old_value->check_object()));
    }
#endif


};

//
// A tag entry
//
class UpdatableTagEntry : public TrailEntry
{
 private:
  heapobject* addr;
  heapobject     old_value;
 public:
  UpdatableTagEntry(heapobject* a, heapobject t):addr(a),old_value(t) {}

    const word32 size() const 
    { return sizeof(UpdatableTagEntry)/sizeof(u_int); }

    void backtrack()
    {
      if (addr != NULL)
	*addr = old_value;
    }

    bool tidy(TrailLoc tloc, TrailLoc stop, heapobject* savedHeapTop, 
	      Heap& heap)
    {
      //return (addr >= heap.getSavedTop() && addr < heap.getTop());
      if (addr == NULL)
	{
	  return true;
	}
      if (addr >= savedHeapTop && addr < heap.getTop())
	{
	  return true;
	}

      TrailLoc loc = tloc;
      while (loc < stop)
	{
	  TrailEntry* entry = (TrailEntry*)loc;
	  if (*entry == *this)
	    {
	      addr = NULL;
	      return true; // XXX break;
	    }
	  loc += entry->size();
	}
      return false;
    }

    void gc_mark(Heap& heap, ObjectsStack& gcstack,
		 GCBits& gcbits) {}

    void gc_sweep(Heap& heap, GCBits& gcbits)
    {
      int index = addr - heap.getBase();
      if ((addr != NULL) && (index >= 0) && (addr < heap.getTop()) && 
	  gcbits.isSet(index))
	{
	  threadGC(reinterpret_cast<heapobject*>(&addr));
	}
      else
	{
	  addr = NULL;
	}
    }

    virtual bool operator==(const UpdatableTagEntry& t) const 
    {return (addr == t.addr); }

#ifdef QP_DEBUG
    bool check(Heap& heap) const {return true;}
#endif
};

//
// An entry for predicate ref counts
//
class PredRefEntry : public TrailEntry
{
 private :
  DynamicPredicate* pred;
 public:
  PredRefEntry(DynamicPredicate* p) : pred(p) {}

    const word32 size() const 
    { return sizeof(PredRefEntry)/sizeof(u_int); }

    void backtrack()
    {
      pred->release();
    }

    bool tidy(TrailLoc tloc, TrailLoc stop, heapobject* savedHeapTop, 
	      Heap& heap)
    {
      pred->release();
      return true;
    }

    void gc_mark(Heap& heap, ObjectsStack& gcstack, 
		 GCBits& gcbits) {}
    void gc_sweep(Heap& heap, GCBits& gcbits){}

#ifdef QP_DEBUG
    bool check(Heap& heap) const {return true;}
#endif

};

class Thread;
//
// An entry for cleanup calls
//
class CleanupEntry : public TrailEntry
{
 private :
  word32 cloc;
  word32* cleanuploc;
 public:
  CleanupEntry(word32 c, word32* t) : cloc(c), cleanuploc(t)
  { }

    const word32 size() const 
    { return sizeof(CleanupEntry)/sizeof(u_int); }

    void backtrack()
    {
      if (cloc < *cleanuploc) *cleanuploc = cloc;
    }

    bool tidy(TrailLoc tloc, TrailLoc stop, heapobject* savedHeapTop, 
	      Heap& heap)
    {
      if (cloc < *cleanuploc) *cleanuploc = cloc;
      return true;
    }

    void gc_mark(Heap& heap, ObjectsStack& gcstack, 
		 GCBits& gcbits) {}
    void gc_sweep(Heap& heap, GCBits& gcbits){}

#ifdef QP_DEBUG
    bool check(Heap& heap) const {return true;}
#endif

};

//
// A trail for variable bindings.
//
class OtherTrail 
{

 private:
  static const size_t min_size = sizeof(PredRefEntry)/sizeof(u_int);
  TrailLoc stack;
  TrailLoc high;
  TrailLoc low;
  TrailLoc top;
  TrailLoc low_water;

 public:
  OtherTrail(word32 size)
    {
      word32 sizeK = size*K;
      stack = new wordptr[sizeK];
      low = stack;
      high = stack + sizeK;
      top = high;
      low_water = high;
    }
  ~OtherTrail() { delete [] stack; }
  
  //
  // Get the current trail top.
  //
  TrailLoc	getTop(void)	const	{ return(top); }

  //
  // Get the trail high.
  //
  TrailLoc	getHigh(void)	const	{ return(high); }

  int maxUsage() const { return high - low_water; }

  int usedTrail() const { return high - top; }

  int allocatedSize() const { return high - low; }

  
  //
  // Trail an updatable object.
  //
  void push(heapobject* a, Object* o, u_int off)
  {
    top -= sizeof(UpdatableObjectEntry)/sizeof(u_int);
    if (top <= low)
      Fatal(__FUNCTION__, "Overflow trail");
    new(top) UpdatableObjectEntry(a, o, off);
    if (top < low_water) low_water = top;
  }
  
  //
  // Trail an updatable tag.
  //
  void push(heapobject* a, heapobject t)
  {
    top -= sizeof(UpdatableTagEntry)/sizeof(u_int);
    if (top <= low)
      Fatal(__FUNCTION__, "Overflow trail");
    new(top) UpdatableTagEntry(a, t);
    if (top < low_water) low_water = top;
  }
  
  //
  // Trail a pred ref entry.
  //
  void push(DynamicPredicate* p)
  {
    top -= sizeof(PredRefEntry)/sizeof(u_int);
    if (top <= low)
      Fatal(__FUNCTION__, "Overflow trail");
    new(top) PredRefEntry(p);
    if (top < low_water) low_water = top;
  }
 
  //
  // Trail a cleanup entry.
  //
  void push(word32 c, word32* t)
  {
    top -= sizeof(CleanupEntry)/sizeof(u_int);
    if (top <= low)
      Fatal(__FUNCTION__, "Overflow trail");
    new(top) CleanupEntry(c, t);
    if (top < low_water) low_water = top;
  }
 
   
  //
  // Roll back the trail to a specified position.  
  //
  void backtrackTo(const TrailLoc loc)
  {
    assert(loc >= top);
    assert((loc - high)<= 0);
    TrailLoc	current;
    for (current = getTop(); current < loc;)
      {
	TrailEntry* entry = (TrailEntry*)current;
	entry->backtrack();
	current += entry->size();
      }
    top = loc;
  }
  
  //
  // Given a segment of trail between start and the top, re-determine
  // whether the entry is needed or not.
  //
  void tidyUpTrail(TrailLoc loc, heapobject* savedHeapTop, 
		   Heap& heap)
  {    assert(loc >= top);
    assert(loc <= high);
    u_int keepsize = 1 + (loc - top)/min_size;
    TrailLoc* keep = new TrailLoc[keepsize];
    
    u_int keepind = 0;
    
    TrailLoc current = top;
    TrailEntry* entry;
    while (current < loc)
      {
	entry = (TrailEntry*)current;
	if (!entry->tidy(current + entry->size(), loc, savedHeapTop, heap))
	  {
	    keep[keepind] = current;
            keepind++;
	  }
	current += entry->size();
      }
    // compress trail
    top = loc;
    for (int i = keepind; i > 0; i--)
      {
	TrailLoc ptr = keep[i-1];
	entry = (TrailEntry*)ptr;
	u_int es = entry->size();
	if (ptr != top - es)
	  {
	    memmove(top - es, ptr, es*sizeof(u_int));
	  }
	top -= es;
      }
    assert(top <= high);
    delete [] keep;
  }

  void gc_mark(Heap& heap, ObjectsStack& gcstack, 
	       GCBits& gcbits)
  {
    TrailLoc current = top;

    while (current < high)
      {
	TrailEntry *entry = (TrailEntry*)current;
	entry->gc_mark(heap, gcstack, gcbits);
	current += entry->size();
      }
  }

  void gc_sweep(Heap& heap, GCBits& gcbits)
  {
    TrailLoc current = top;

    while (current < high)
      {
	TrailEntry *entry = (TrailEntry*)current;
	entry->gc_sweep(heap, gcbits);
	current += entry->size();
      }
  }
#ifdef QP_DEBUG
  bool check(Heap& heap) const
  {
    TrailLoc current = top;

    while (current < high)
      {
	TrailEntry *entry = (TrailEntry*)current;
	if (!entry->check(heap)) return false;
	current += entry->size();
      }
    return true;
  }
#endif
};
  
class BindingTrail
{
 private:
  TrailLoc stack;
  TrailLoc high;
  TrailLoc low;
  TrailLoc top;
  TrailLoc low_water;

 public:
  BindingTrail(word32 size)
    {
      word32 sizeK = size*K;
      stack = new wordptr[sizeK];
      low = stack;
      high = stack + sizeK;
      top = high;
      low_water = high;
    }
  ~BindingTrail() { delete [] stack; }
  
  //
  // Get the current trail top.
  //
  TrailLoc	getTop(void)	const	{ return(top); }

  //
  // Get the trail high.
  //
  TrailLoc	getHigh(void)	const	{ return(high); }

  int maxUsage() const { return high - low_water; }

  int usedTrail() const { return high - top; }

  int allocatedSize() const { return high - low; }

  //
  // Trail a binding.
  //
  void push(heapobject* v)
  {
    top--;
    if (top <= low)
      Fatal(__FUNCTION__, "Overflow trail");
    *top = (wordptr)v;
    if (top < low_water) low_water = top;
  }
  
 //
  // Roll back the trail to a specified position.  
  //
  void backtrackTo(const TrailLoc loc)
  {
    assert(loc >= top);
    assert(loc <= high);
    TrailLoc	current;
    for (current = top; current < loc; current++)
      {
	heapobject* var = (heapobject*)(*current);
	assert(var != NULL);
	*(var+1) = reinterpret_cast<heapobject>(var);
      }
    top = loc;
  }

  void tidyUpTrail(TrailLoc loc, heapobject* savedHeapTop)
  {
    TrailLoc current = loc-1;
    TrailLoc follower = loc; 
    for ( ; current >= top; current--)
      {
	heapobject* var = (heapobject*)(*current);
	if (var < savedHeapTop)
	  {
	    follower--;
	    if (current < follower)
	      {
		*follower = *current;
	      }
	  }
      }
    top = follower;
  }
  
  void gc_sweep(Heap& heap, GCBits& gcbits)
  {	
    TrailLoc current = top;
    
    while (current < high)
      {
#ifdef QP_DEBUG
	heapobject* var = (heapobject*)(*current);
	if (!gcbits.isSet(var - heap.getBase()))
	  cerr << hex << "var = " << (wordptr)var <<
	    " var* = " << (wordptr)(*var) << 
	    " var+1* = " << (wordptr)(*(var+1)) <<
	    " var+1** = " << (wordptr)(*(heapobject*)(*(var+1))) << dec << endl;
	assert(gcbits.isSet(var - heap.getBase()));
#endif	
	threadGC(current);
	
	current++;
      }
  }

#ifdef QP_DEBUG
  bool check(Heap& heap) const
  {
    TrailLoc current = top;
    
    while (current < high)
      {
	heapobject* var = (heapobject*)(*current);
	if (!heap.isHeapPtr(var))
	  {
	    cerr << "check - not heap ptr" << endl;
	    return false;
	  } 
	if (!heap.isActive(var))
	  {
	    cerr << "check - not active heap ptr" << endl;
	    return false;
	  } 
	if (!((Object*)var)->isAnyVariable()) 
	  {
	    cerr << "check - not a variable" << endl;
	    return false;
	  }
	current++;
      }
    return true;
  }
#endif
};
  
#endif // TRAIL_H








