// dyn_code_block.h - Storage for dynamic code.
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
// $Id: dyn_code_block.h,v 1.6 2006/01/31 23:17:50 qp Exp $  

#ifndef DYN_CODE_BLOCK_H
#define DYN_CODE_BLOCK_H

#include <list>
//#include "atom_table.h"
//#include "code.h"
#include "dynamic_code.h"
#include "instructions.h"

// Forward declarations
class CodeLinkingBlock;

class DynCodeBlock
{
private:
  int refcount;
  list<CodeLinkingBlock*> codeblocks;
  CodeLoc code;
public:
  // When a new code block is created (by assert) refcount is set to 1
  // because asserting produces a reference.
  explicit DynCodeBlock(CodeLoc c):refcount(1)
  {
    code = c;
  }

  // Called when something references the clause.
  void aquire(void)
  {
    refcount++;
  }

  // Called when something is finished with the clause.
  // If the reference count becomes zero this object is deleted.
  void release(void)
  {
    refcount--;
    if (refcount == 0)
      {
	delete this;
      }
  }

  int getRefcount(void) { return refcount; }

  // Update the list of linking blocks.
  void addLinkBlock(CodeLinkingBlock* b)
  {
    codeblocks.push_back(b);
  }

  // When the clause is retracted the first instruction in the block
  // is set to fail and the jump address in the linking blocks are set to 0
  //
  void setFail(void)
  {
    updateInstruction(code, FAIL);
    for (list<CodeLinkingBlock*>::iterator iter = codeblocks.begin();
	 iter != codeblocks.end();
	 iter++)
      {
	(*iter)->setJumpAddr(0);
      }
  }
  
  ~DynCodeBlock(void) 
  {
    // delete the linking blocks
    for (list<CodeLinkingBlock*>::iterator iter = codeblocks.begin();
	 iter != codeblocks.end();
	 iter++)
      {
	(*iter)->release();
      }
    // delete the list
    codeblocks.clear();
    // delete the code
    delete [] code;
  }

  CodeLoc getStartOfCode(void)
  {
    return code;
  }

#ifdef QP_DEBUG
  void printMe(void)
  {
    cerr << "----DynCodeBlock-----" << endl;
    cerr << "refc = " << refcount << endl;
    cerr << "Code = " << (word32)code << endl;
  }

  bool list_member(CodeLinkingBlock* link)
  {
    for (list<CodeLinkingBlock*>::iterator iter = codeblocks.begin();
	 iter != codeblocks.end();
	 iter++)
      {
	if (*iter == link)
	  {
	    return true;
	  }
      }
    return false;
  }
#endif // DEBUG
	
};


#endif  // DYN_CODE_BLOCK_H










