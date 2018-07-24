// decompile.h -  A decompiler
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
// $Id: decompile.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $


#ifndef DECOMPILE_H
#define DECOMPILE_H

private:
ReturnValue decompile(CodeLoc programCounter, Object* head, 
		      Object*& instrlist);
ReturnValue next_instr(CodeLoc programCounter, Object* head, 
		       Object*& first, Object*& next);

public:
//
// psi_decompile(codeptr, headterm, bodylist)
// Returns the list of body "calls" for the body of the clause that starts at 
// codeptr and whose head matches headterm.
// mode(in,in,out)
//
ReturnValue psi_decompile(Object*& o1, Object*& o2, Object*& o3);

//
// psi_next_instr(codeptr, headterm, codeptr, codeptr)
// return the loc of current instr and next instr (or fail if no 
// next instr.
// mode(in,in,out,out)
//
ReturnValue psi_next_instr(Object*& o1, Object*& o2, Object*& o3, Object*& o4);

#endif // DECOMPILE_H
