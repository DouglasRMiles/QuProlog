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
// $Id: asm_objects.h,v 1.8 2005/03/08 00:34:59 qp Exp $

#ifndef	ASM_OBJECTS_H
#define	ASM_OBJECTS_H

#include <vector>
#ifdef WIN32
#include <list>
#endif


#include "asm_int.h"
#include "code.h"
#include "code_block.h"
#include "labels.h"
//#include "string_qp.h"

using namespace std;

class AtomArityLabel
{
private:
  ASMInt<Code::ConstantSizedType> *atom;
  ASMInt<Code::NumberSizedType> *arity;
  string *label;
public:
  AtomArityLabel(ASMInt<Code::ConstantSizedType> *at,
		 ASMInt<Code::NumberSizedType> *ar,
		 string *l) :
    atom(at), arity(ar), label(l) { }
  
  // For constructing ``default'' switch table entries.
  AtomArityLabel(string *l) : label(l)
    {
      atom = new ASMInt<Code::ConstantSizedType>(0);

      atom->Value(UnsignedMax(atom->Value()));
      
      arity = new ASMInt<Code::NumberSizedType>(0);
    }
  
  ~AtomArityLabel(void)	{ }
  
  bool operator==(const AtomArityLabel& aal) const
    {
      return *atom == *(aal.atom) &&
	*arity == *(aal.arity) &&
	*label == *(aal.label);
    }
  
  void Put(CodeBlock &code, LabelTable& labels,
	   const u_int jump_offset_base) const
    {
      atom->Put(code);
      arity->Put(code);
      labels.AddReference(*label, code, jump_offset_base);
    }
  
  u_int SizeOf(void) const
    {
      return static_cast<u_int>(atom->SizeOf() + arity->SizeOf() + Code::SIZE_OF_OFFSET);
    }

  void operator=(const AtomArityLabel& aal)
    {
      atom->Value(aal.atom->Value());
      arity->Value(aal.arity->Value());

      delete label;
      label = new string(*(aal.label));
    }
};

class ConstantLabel
{
private:
  ASMInt<Code::ConstantSizedType> *constant;
  string *label;
public:
  ConstantLabel(ASMInt<Code::ConstantSizedType> *c,
		string *l)
    : constant(c), label(l)
    { }
  
  // For constructing ``default'' switch table entries.
  ConstantLabel(string *l) : label(l)
    {
      constant = new ASMInt<Code::ConstantSizedType>(0);
      constant->Value(UnsignedMax(constant->Value()));
    }

  ~ConstantLabel(void)	{ }
  
  bool operator==(const ConstantLabel& cl) const
    {
      return *constant == *(cl.constant) &&
	*label == *(cl.label);
    }
  
  void Put(CodeBlock& code, LabelTable& labels,
	   const u_int jump_offset_base) const
    {
      ASMInt<Code::NumberSizedType> type(static_cast<Code::NumberSizedType>(constant->Type()));
      constant->Put(code);
      type.Put(code);
      labels.AddReference(*label, code, jump_offset_base);
    }
  
  u_int SizeOf(void) const
    {
      return static_cast<u_int>(constant->SizeOf() + Code::SIZE_OF_OFFSET);
    }

  void operator=(const ConstantLabel& c)
    {
      constant->Value(c.constant->Value());
      
      delete label;
      label = new string(*(c.label));
    }
};

#if 0
template <class Item>
class SwitchTable
{
private:
  u_int jump_offset_base;
  ASMInt<Code::TableSizeSizedType> *num_table_entries;
  string *default_label;
  vector<Item *> *ilist;
public:
  SwitchTable(const u_int job,
	      ASMInt<Code::TableSizeSizedType> *num,
	      string *dl, vector<Item *> *l)
    : jump_offset_base(job),
      num_table_entries(num),
      default_label(dl),
      ilist(l)
      { }
  
  ~SwitchTable(void) { }
  
  void Put(CodeBlock& code,
	   LabelTable& labels)
    {
      u_int count = 0;			// Count of entries output
      
      Item default_entry(default_label);
      
      default_entry.Put(code, labels, jump_offset_base);
      
      count++;					// ``One wonderful entry!!!''
      
      // Output all the list entries
      for (vector<Item *>::iterator iter = ilist->begin();
	   iter != ilist->end();
	   iter++)
	{
	  (*iter)->Put(code, labels, jump_offset_base);
	  count++;
	}
      
      // Fill up extra places with default entries
      
      for (;
	   count < num_table_entries->Value();
	   count++)
	{
	  default_entry.Put(code, labels, jump_offset_base);
	}
    }
};
#endif
class AtomSwitchTable
{
private:
  u_int jump_offset_base;
  ASMInt<Code::TableSizeSizedType> *num_table_entries;
  string *default_label;
  vector<AtomArityLabel *> *ilist;
public:
  AtomSwitchTable(const u_int job,
	      ASMInt<Code::TableSizeSizedType> *num,
	      string *dl, vector<AtomArityLabel *> *l)
    : jump_offset_base(job),
      num_table_entries(num),
      default_label(dl),
      ilist(l)
      { }
  
  ~AtomSwitchTable(void) { }
  
  void Put(CodeBlock& code,
	   LabelTable& labels)
    {
      u_int count = 0;			// Count of entries output
      
      AtomArityLabel default_entry(default_label);
      
      default_entry.Put(code, labels, jump_offset_base);
      
      count++;					// ``One wonderful entry!!!''
      
      // Output all the list entries
      for (vector<AtomArityLabel *>::iterator iter = ilist->begin();
	   iter != ilist->end();
	   iter++)
	{
	  (*iter)->Put(code, labels, jump_offset_base);
	  count++;
	}
      
      // Fill up extra places with default entries
      
      for (;
	   count < num_table_entries->Value();
	   count++)
	{
	  default_entry.Put(code, labels, jump_offset_base);
	}
    }
};

class ConstantSwitchTable
{
private:
  u_int jump_offset_base;
  ASMInt<Code::TableSizeSizedType> *num_table_entries;
  string *default_label;
  vector<ConstantLabel *> *ilist;
public:
  ConstantSwitchTable(const u_int job,
	      ASMInt<Code::TableSizeSizedType> *num,
	      string *dl, vector<ConstantLabel *> *l)
    : jump_offset_base(job),
      num_table_entries(num),
      default_label(dl),
      ilist(l)
      { }
  
  ~ConstantSwitchTable(void) { }
  
  void Put(CodeBlock& code,
	   LabelTable& labels)
    {
      u_int count = 0;			// Count of entries output
      
      ConstantLabel default_entry(default_label);
      
      default_entry.Put(code, labels, jump_offset_base);
      
      count++;					// ``One wonderful entry!!!''
      
      // Output all the list entries
      for (vector<ConstantLabel *>::iterator iter = ilist->begin();
	   iter != ilist->end();
	   iter++)
	{
	  (*iter)->Put(code, labels, jump_offset_base);
	  count++;
	}
      
      // Fill up extra places with default entries
      
      for (;
	   count < num_table_entries->Value();
	   count++)
	{
	  default_entry.Put(code, labels, jump_offset_base);
	}
    }
};

#endif	// ASM_OBJECTS_H
