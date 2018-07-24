// code_block.cc -
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
// $Id: code_block.cc,v 1.2 2005/03/08 00:35:01 qp Exp $

#include "code.h"
#include "code_block.h"

ostream&
CodeBlock::Save(ostream& ostrm) const
{
  switch (Type())
    {
    case QUERY_BLOCK:
      break;
    case PREDICATE_BLOCK:
      {
	IntSave<Code::AddressSizedType>(ostrm, Atom());
	IntSave<Code::NumberSizedType>(ostrm, static_cast<Code::NumberSizedType>(Arity()));
      }
    break;
    }
  
  IntSave<Code::OffsetSizedType>(ostrm, static_cast<const Code::OffsetSizedType>(Current()));
  
  for (CodeBlockLoc loc = 0; loc < Current(); loc++)
    {
      ostrm << code[loc];
    }

  return ostrm;
}
