// user_hash_table.h - support for Prolog-level hash table.
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
// $Id: user_hash_table.h,v 1.2 2006/03/30 22:50:31 qp Exp $

#include "heap_qp.h"
#include "dynamic_hash_table.h"


//
// Entries in user-level hash table
// Two-level indexing using fst_entry and snd_entry
//
class UserHashEntry
{
private:
    Object* fst_entry;
    Object* snd_entry;
    int size;
    Object* value;
    heapobject* ptr;
    bool removed;
public:
    void clearEntry(void) { fst_entry = 0; }
    bool isEmpty(void) const {  return (fst_entry == 0); }
    bool isRemoved(void) { return removed; }
    void makeRemoved(void) { removed = true; }
    int hashFn(void) const 
    {
      wordlong fst_hash;
      switch (fst_entry->tTag())
        {
        case Object::tShort:
          fst_hash = (wordlong)(OBJECT_CAST(Short *, fst_entry)->getValue());
          break;
        case Object::tLong:
          fst_hash = (wordlong)(OBJECT_CAST(Long *, fst_entry)->getValue());
          break;
        case Object::tAtom:
          fst_hash = (wordlong)(OBJECT_CAST(Long *, fst_entry)->getValue());
          break;
        case Object::tDouble:
          fst_hash = (wordlong)(OBJECT_CAST(Double *, fst_entry)->hashFn());
          break;
        case Object::tString:
          fst_hash = (wordlong)(OBJECT_CAST(StringObject *, fst_entry)->hashFn());
          break;
        default:
          // Not all Tags considered!
          std::cerr << "Bogus type" << std::endl;
          std::cerr << (wordptr)(this) << " -> " << *((heapobject*)(this)) << std::endl;
          assert(false);
        }
      wordlong snd_hash;
      switch (snd_entry->tTag())
        {
        case Object::tShort:
          snd_hash = (wordlong)(OBJECT_CAST(Short *, snd_entry)->getValue());
          break;
        case Object::tLong:
          snd_hash = (wordlong)(OBJECT_CAST(Long *, snd_entry)->getValue());
          break;
        case Object::tAtom:
          snd_hash = (wordlong)(OBJECT_CAST(Long *, snd_entry)->getValue());
          break;
        case Object::tDouble:
          snd_hash = (wordlong)(OBJECT_CAST(Double *, snd_entry)->hashFn());
          break;
        case Object::tString:
          snd_hash = (wordlong)(OBJECT_CAST(StringObject *, snd_entry)->hashFn());
          break;
        default:
          // Not all Tags considered!
          std::cerr << "Bogus type" << std::endl;
          std::cerr << (wordptr)(this) << " -> " << *((heapobject*)(this)) << std::endl;
          assert(false);
        }
      return (int)(fst_hash ^ snd_hash);
    }

    bool operator==(const UserHashEntry entry) const
      { return ((fst_entry == entry.fst_entry) &&
                (snd_entry == entry.snd_entry) ); }
    void operator=(const UserHashEntry entry)
      { fst_entry = entry.fst_entry; snd_entry = entry.snd_entry;
        value = entry.value;
        ptr = entry.ptr; size = entry.size; removed = entry.removed; }

    void setSize(int s) { size = s; }
    int getSize(void) {return size; }

    void setPtr(heapobject* o) { ptr = o; }
    heapobject*  getPtr() { return ptr; }

    void setValue(Object* o) { value = o; }
    Object* getValue(void) {return value; }

    Object* getFstEntry(void) {return fst_entry; }
    Object* getSndEntry(void) {return snd_entry; }

    UserHashEntry(Object* t = AtomTable::dollar, Object* s = AtomTable::dollar)
    : fst_entry(t), snd_entry(s), size(0),
      value(NULL),  ptr(NULL), removed(false)
  {};

};

//
// Instantiation of DynamicHashTable for user hash table
//
class UserHashTable : public DynamicHashTable<UserHashEntry>
{
public:
  UserHashTable(const int size);

  ~UserHashTable(void);

   int   hashFunction(const UserHashEntry entry) const
      { return (entry.hashFn()); }

};

//
// Hash Table including heap for storing data
//
class UserHashState
{
private:
   UserHashTable hash_table;
   Heap* userhashheap;
   int total_garbage, heap_size, heap_sizeK;


public:

  void addEntry(Object* h1, Object* h2, Object* term, Heap& heap);
  bool lookupEntry(Object* h1, Object* h2, Object*& ret, Heap& heap);
  bool removeEntry(Object* h1, Object* h2);
  void hashIterReset(void);
  bool hashIterNext(Object*& a, Object*& b, Object*& c, Heap& heap);
  void garbageCollect(void);

  UserHashState(int hts, int hs)
    : hash_table(hts)
  {
    userhashheap = new Heap("User Hash Table Heap", hs * K, true);
    total_garbage = 0;
    heap_size = hs * K / sizeof (heapobject);
    heap_sizeK = hs;
  }


};
