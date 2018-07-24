// symbol_info.h -
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
// $Id: symbol_info.h,v 1.4 2002/11/10 07:54:54 qp Exp $

#ifndef	SYMBOL_INFO_H
#define	SYMBOL_INFO_H

#include "defs.h"
//#include "string_qp.h"

class SymbolInfo
{
private:
  string symbol;
public:
  SymbolInfo(void) : symbol(NULL) { }
  ~SymbolInfo(void) { delete symbol; }

  bool SymbolSet(void) const { return symbol != NULL; }
  const string& Symbol(void) const
  {
    return symbol;
  }

  void SetSymbol(const string& s)
  {
    symbol = s;
  }
};

#endif	// SYMBOL_INFO_H
