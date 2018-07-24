// labels.h -
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
// $Id: labels.h,v 1.7 2006/01/31 23:17:51 qp Exp $

#ifndef	LABELS_H
#define	LABELS_H

#include <vector>

#include "asm_int.h"
#include "asm_string_table.h"
#include "code.h"
#include "code_block.h"
//#include "string_qp.h"

class Label
{
private:
  class Reference
    {
    private:
      u_int reference;			// Actual loc of reference
      u_int jump_offset_base;
    public:
      Reference(const u_int r, const u_int job)
	: reference(r), jump_offset_base(job) {	}
      ~Reference(void) { }
      
      u_int Ref(void) const { return reference; }
      u_int JumpOffsetBase(void) const { return jump_offset_base; }

      void operator=(const Reference& r)
	{
	  reference = r.reference;
	  jump_offset_base = r.jump_offset_base;
	}
    };

  string *name;

  bool resolved;
  
  vector<Reference *> *references;
public:
  explicit Label(const string& s) 
    : name(new string(s)),
    resolved(false),
    references(new vector<Reference *>)
    {
    }
  ~Label(void)
  {
    delete name;
    assert(resolved);
    delete references;
  }
  
  const string& Name(void) const { return *name; }

  bool operator==(const Label& l) const
  {
    return Name() == l.Name();
  }

  void AddReference(CodeBlock& code, const u_int jump_offset_base)
  {
    Reference *ref = new Reference(code.Current(), jump_offset_base);

    references->push_back(ref);
    code.Advance(Code::SIZE_OF_OFFSET);
  }

  void Resolve(CodeBlock& code)
  {
    assert(!resolved);
    
    resolved = true;
    
    for (vector<Reference *>::iterator iter = references->begin();
	 iter != references->end();
	 iter++)
      {
	const ASMInt<Code::OffsetSizedType> ref(static_cast<const Code::OffsetSizedType>(code.Current() - (*iter)->JumpOffsetBase()));
	ref.Put((*iter)->Ref(), code);
      }
  }

  // Specialised version of Resolve() for resovling failure labels, who always
  // turn into an offset of -1.
  void ResolveFail(CodeBlock& code)
  {
    resolved = true;
    
    for (vector<Reference *>::iterator iter = references->begin();
	 iter != references->end();
	 iter++)
      {
	ASMInt<Code::OffsetSizedType> ref(0);
	ref.Value(UnsignedMax(ref.Value()));
	
	ref.Put((*iter)->Ref(), code);
      }
  }

  void operator=(const Label& l)
    {
      delete name;
      name = new string(*(l.name));
      resolved = l.resolved;

      delete references;
      references = new vector<Reference *>(*(l.references));
    }
};

inline ostream& operator<<(ostream& ostrm, const Label& label)
{
  return ostrm << label.Name();
}


class LabelTable
{
private:
  vector<Label *> labels;
public:
  // s is the name of the label
  // code is the code block where it references
  // job is the jump offset base
  void AddReference(const string& s, CodeBlock& code, const u_int job)
  {
    Label *found = NULL;
    
    for (vector<Label *>::iterator iter = labels.begin();
	 iter != labels.end();
	 iter++)
      {
	if (s == (*iter)->Name())
	  {
	    found = *iter;
	    break;
	  }
      }
    
    if (found)
      {
	found->AddReference(code, job);
      }
    else
      {
	// Not found, so add it
	Label *label = new Label(s);
	label->AddReference(code, job);
	
	labels.push_back(label);
      }
  }
  
  void Resolve(const string& s, CodeBlock &code)
  {
    Label *found = NULL;
    
    for (vector<Label *>::iterator iter = labels.begin();
	 iter != labels.end();
	 iter++)
      {
	if (s == (*iter)->Name())
	  {
	    found = *iter;
	    break;
	  }
      }

    if (found)
      {
	found->Resolve(code);
      }
  }

  void ResolveFail(CodeBlock& code)
  {
    Label *found = NULL;

    for (vector<Label *>::iterator iter = labels.begin();
	 iter != labels.end();
	 iter++)
      {
	if ((*iter)->Name() == "fail")
	  {
	    found = *iter;
	    break;
	  }
      }
    
    if (found)
      {
	found->ResolveFail(code);
      }
  }
};

#endif	// LABELS_H
