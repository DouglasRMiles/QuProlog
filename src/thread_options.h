// thread_options.h - Options for sizing of thread data
//		structures.
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
// $Id: thread_options.h,v 1.2 2001/11/21 00:21:18 qp Exp $

#ifndef THREAD_OPTIONS_H
#define THREAD_OPTIONS_H

#include "defs.h"
#include "option.h"
#include "qem_options.h"

class ThreadOptions
{
private:
  Option<word32> name_table_size;
  Option<word32> ip_table_size;
  Option<word32> heap_size;
  Option<word32> scratchpad_size;
  Option<word32> environment_stack_size;
  Option<word32> choice_stack_size;
  Option<word32> binding_trail_size;
  Option<word32> other_trail_size;
public:
  word32 NameTableSize(void) const { return name_table_size.Value(); }
  word32 IPTableSize(void) const { return ip_table_size.Value(); }
  word32 HeapSize(void) const { return heap_size.Value(); }
  word32 ScratchpadSize(void) const { return scratchpad_size.Value(); }
  word32 EnvironmentStackSize(void) const { return environment_stack_size.Value(); }
  word32 ChoiceStackSize(void) const { return choice_stack_size.Value(); }
  word32 BindingTrailSize(void) const { return binding_trail_size.Value(); }
  word32 OtherTrailSize(void) const { return other_trail_size.Value(); }

  void NameTableSize(const word32 nts) { name_table_size = nts; }
  void IPTableSize(const word32 its) { ip_table_size = its; }
  void HeapSize(const word32 hs) { heap_size = hs; }
  void ScratchpadSize(const word32 hs) { scratchpad_size = hs; }
  void EnvironmentStackSize(const word32 ess) { environment_stack_size = ess; }
  void ChoiceStackSize(const word32 css) { choice_stack_size = css; }
  void BindingTrailSize(const word32 ts) { binding_trail_size = ts; }
  void OtherTrailSize(const word32 ts) { other_trail_size = ts; }


  ThreadOptions(const word32 ntas,
		const word32 itas,
		const word32 hs,
		const word32 ss,
		const word32 ess,
		const word32 css,
		const word32 bts,
		const word32 ots)
    : name_table_size(ntas),
    ip_table_size(itas),
    heap_size(hs),
    scratchpad_size(ss),
    environment_stack_size(ess),
    choice_stack_size(css),
    binding_trail_size(bts),
    other_trail_size(ots) {}


  ThreadOptions(const QemOptions& qem_opts)
    : name_table_size(qem_opts.NameTableSize()),
      ip_table_size(qem_opts.IPTableSize()),
      heap_size(qem_opts.HeapSize()),
      scratchpad_size(qem_opts.ScratchpadSize()),
      environment_stack_size(qem_opts.EnvironmentStackSize()),
      choice_stack_size(qem_opts.ChoiceStackSize()),
      binding_trail_size(qem_opts.BindingTrailSize()),
      other_trail_size(qem_opts.OtherTrailSize())
      {}
};

#endif // THREAD_OPTIONS_H
