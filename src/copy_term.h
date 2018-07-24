// copy_term.h - Copy a term from one heap to another.
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
// $Id: copy_term.h,v 1.3 2002/11/13 04:04:14 qp Exp $

#ifndef	COPY_TERM_H
#define	COPY_TERM_H


private:
class VarRec
{
private:
  heapobject* source_loc;
  heapobject* target_loc;
public:
  VarRec(heapobject* sl, heapobject* tl) : source_loc(sl), target_loc(tl)
    { }

  heapobject* sourceLoc(void) const { return source_loc; }
  heapobject* targetLoc(void) const { return target_loc; }

  bool operator==(const VarRec& v) const
  {
    return sourceLoc() == v.sourceLoc();
  }

  void operator=(const VarRec& v)
    {
      source_loc = v.sourceLoc();
      target_loc = v.targetLoc();
    }
};


Object* copy_var(Object*, Heap&, list<VarRec *>&);

Object* copy_object_variable(Object* source_object_variable, 
			     Heap& target_heap,
			     list<VarRec *>& object_variable_rec_list);


Object* copy_subblock(Object* source_substitution,
		      Heap& target_heap,
		      list<VarRec *>& var_rec_list,
		      list<VarRec *>& object_variable_rec_list);

Object* copy_share_subblock(Object* source_substitution,
			    Heap& target_heap,
			    const heapobject* low, const heapobject* high);

Object* copy_term(Object* source_term, Heap& target_heap,
		  list<VarRec *>& var_rec_list,
		  list<VarRec *>& object_variable_rec_list);

Object* copy_share_term(Object* source_term, Heap& target_heap,
			const heapobject* low, const heapobject* high);

public:
Object* copyTerm(Object* source_term, Heap& target_heap);

Object* copyShareTerm(Object* source_term, Heap& target_heap, 
		      const heapobject* low, const heapobject* high);

#endif	// COPY_TERM_H











