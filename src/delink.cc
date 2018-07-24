//  delink.cc - De-assemble binary files.
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
// $Id: delink.cc,v 1.7 2005/03/27 22:07:38 qp Exp $

#include "atom_table.h"
#include "code.h"
#include "delink.h"
#include "indexing.h"
#include "instructions.h"

extern AtomTable *atoms;

const int NUM_OF_OFFSETS = 500;

//
//  Constants is used exclusively by deassembler() and simply prints out the
// string, integer or short of a given object.
//
//
static void
constants(Object* cell, AtomTable& atoms)
{
  if (cell->isAtom())
    {
      cout << "\'" << OBJECT_CAST(Atom*, cell)->getName() << "\'";
    }
  if (cell->isInteger())
    {
      cout << cell->getInteger();
    }
  if (cell->isDouble())
    {
      cout << cell->getDouble();
    }
}
//
// This procedure is used for instructions that have a hash table.
//
static void
hashInstruct(CodeLoc & pc, word32 instruct,long array[],
	     int & arr_index,AtomTable& atoms,Code& code)
  
{
  cout << "(";
  const word32 r = getRegister(pc);
  cout << r << ", ";
  const word32 n = getTableSize(pc); // Size of hash = n.
  const CodeLoc startofhash = pc;

  cout  << n << ", [";
  for (word32 j = 1; j <= n ;j++)
    {
      word32 val_arity = 0;
      Object* val_const;

      if (startofhash != pc) cout << ", ";
      wordptr val_addr = getAddress(pc);
      val_arity = getNumber(pc);
      const word32 offset = getOffset(pc);

      if (val_addr == EMPTY_ENTRY)
	{
	  cout << "'default'";
	}
      else
	{
          if ((instruct == SWITCH_ON_CONSTANT) && 
              (val_arity == ConstEntry::INTEGER_TYPE))
            {
              cout << (long)val_addr;
            }
          else
            {
	      val_const = reinterpret_cast<Object*>(val_addr);
	      constants(val_const,atoms);
            }
	  if (instruct != SWITCH_ON_CONSTANT) 
	    {
	      cout << "/" << val_arity;
	    }
	}
      if ((offset == Code::FAIL) || (offset == 0)) 
	{
	  cout << ":'fail'"; 
	}
      else
	{
	  //
	  // Do offset flaging.	
	  //
	  const CodeLoc address = offset + startofhash;
	  int i;
	  for (i = 0;
	       (signed long) address != array[i] && i <= arr_index;
	       i++)
	    ;

	  if (i > arr_index) 
	    {
	      arr_index++;
	      if (arr_index > NUM_OF_OFFSETS)
		{
		  Fatal(__FUNCTION__, "too many labels");
		}
	      array[arr_index] = (signed long) address;
	    }
	  cout << ":$" << i;
	}
    }
  cout  << "]) ";
}
//
// This is procedure that outputs the parameters of each instruction
//
static void
outputParams(int length, int commaflag, char coded_array[],
	     CodeLoc & pc,
	     AtomTable& atoms,long array[],int & arr_index,
	     CodeLoc end_of_inst, Code& code)	
{
  int 	i;
  Atom* predicate;
  Object* 	cell;
  CodeLoc	address;
  
  
  for (int counter = 0; counter < length; counter++) 
    {
      if (commaflag == 0)
	{
	  cout << ", ";
	}
      commaflag = 0;
      char param = coded_array[counter];
      switch(param)
	{
	  
	case 'p':		 // predatom parameters
	  {
	    predicate = getPredAtom(pc);
	    
	    const char *pred_string = OBJECT_CAST(Atom*, predicate)->getName();
	    cout << "\'" << pred_string << "\'" ;
	  }
	  break;
	  
	case 'a':      		 // address parameters
	  cout << getAddress(pc);
	  break;

	case 'n':        // number parameters   
	  cout << (word32)getNumber(pc);
	  break;
	  
	case 'd':        // double parameters   
	  cout << getDouble(pc);
	  break;
	  
	case 'c':      	// constant parameters
	  cell = getConstant(pc);
	  constants(cell,atoms);
	  break;
   
        case 'i':            // integer
          cout << getInteger(pc);
          break;
	  
	case 'r':         // register parameters
	  cout << (word32)getRegister(pc);
	  break;
	  
	case 'o':          // offset parameters
          word32 offset = getOffset(pc);
	  if (offset == Code::FAIL) 
	    {
	      cout << "'fail'"; 
	    }
	  else
	    {	
	      i=0;
	      address = end_of_inst + offset;
	      while( ((signed long) address != array[i]) && 
		     (i <= arr_index)) i++;
	      if (i >  arr_index) 
		{
		  arr_index++;
		  array[arr_index] = (signed long) address;
		}
	      cout << "$" << i;
	    }
	}
    }
};

//   
// Deassembler() is used for both delinking and deassembling code and queries
// obatined from the .qo and .qx files. The output is to the stdout using 
// the cout command.
// The parameters used are the areas involved ie code, PredTable, AtomTable,
// StringMap, and also the start and finish address of the code to 
// be deassembled.
// The main loop is executed for each predicate in the area being deassembled.
// Until the finish is encounted. (variable pc is used as a program counter.)
// Inside this loop, the pre-amble is read.
// For the Code area, the Predicate offset is check in the Predicate table to
// ensure that the Predicate Table back-references correctly. 
// Once the preamble is read, a inner loop executes for each instruction. There
// are three (3) special types of instruction that require extra handling 
// beacause they insert hash tables into the code area.
// If it is not one of these instructions then, the parameters are outputed
// using the information obtained from the array operands which
// is obtained using the Makefile MKparamInst. The coding is explained below.
// This array tells the program how many and what type of operands to expect
// with each instruction.
//
void deassembler(Code& code, AtomTable& atoms, PredTab& predicates,
		 CodeLoc start, CodeLoc finish, 
		 bool PrintAddr)
{
	Atom*   predicate;
	word32 	arity,
		instruct,
		size;
	long 	array[NUM_OF_OFFSETS];
	int 	arr_index,
		i,
		paramflag,
		commaflag,
		length;
	char 	coded_array[10];
	CodeLoc index, 
		start_of_predicate,
		start_of_pred,
		start_of_inst,
		end_of_inst,
		pc;
  

	pc = start;		// set counter to start.

	while (pc < finish)	// Main Loop, repeat until finished       
	{
		start_of_predicate = pc;
		predicate = reinterpret_cast<Atom*>(getAddress(pc));  
		arity =  getNumber(pc);
		size = getOffset(pc);
		//
		// look up predicate table 
		//
		const char *name_string = OBJECT_CAST(Atom*, predicate)->getName();
		cout << "\'" << name_string << "\'/" << arity << ':';
		cout <<	"  (" << (wordptr)pc << ")";

                if (predicates.getCode(predicates.lookUp(predicate,arity, &atoms, &code)).type() == PredCode::STATIC_PRED)
                  {
		    index = predicates.getCode(predicates.lookUp(predicate,arity, &atoms, &code)).getPredicate(&code);
		    if (index != pc) // Is back-referencing correct?
		    { 
			cout << "**** WARNING: Not accessable.**";
		    }
                  }
		cout << "\n\n";
		//
		// The number of parameters and their order of each 
		// instruction is stored in
		// operands which is created using a makefile.
		// Coded the following way:
		//
		// number	'n'
		// offset	'o'
		// constant     'c'
		// integer      'i'
		// double       'd'
		// register	'r'
		// address	'a'
		// predatom	'p'
		//
		// So if an instruction may have one predatom and two address
		// parameters,
		// then it's operands[instruction number] = "paa".
		//
		// Initialize offset array.
		//
		for (i=0; i< NUM_OF_OFFSETS; i++) array[i] = -1L; 
		arr_index = 0;
		start_of_pred = pc;
		while ( pc < (start_of_pred+size) ) // for each instruction do:
 		{	
			paramflag = 0;
			i = 0;
			//
			//	Check for any labels to be printed.
			//
			while (((signed long) pc != array[i]) &&
			       (i <= arr_index)) i++;
			if (i <= arr_index)
			{
				cout << "\n$" << i << ":\n"; 
			}		
			//
			//	Print out instruction.
			//
			start_of_inst = pc;	
  			instruct = getInstruction(pc);
			end_of_inst = start_of_inst + opsizes[instruct];
			if (PrintAddr)
			{
				cout << (wordptr)(pc - 1) << "\t";
			}
			cout <<  "\t" << opnames[instruct];
			const char *coded_inst = operands[instruct];
			//
			// decode instruction parameters
			//
			switch(instruct)
			  {		
			    //
			    //		Does instruct have a hash table:
			    //
			  case  SWITCH_ON_CONSTANT:
			  case  SWITCH_ON_STRUCTURE:
			  case  SWITCH_ON_QUANTIFIER:
			    hashInstruct(pc,instruct,array,arr_index,
					 atoms,code);
			    break;
			  case PUT_STRING:
			  case GET_STRING:
			    {
			      word32 i = (word32)getRegister(pc);
			      cout << "(\"";
			      cout << (char*)pc;
			      cout << "\", " << i << ")";
			      char* c = (char*)pc;
			      int size = strlen(c);
			      pc += size+1;
			      break;
			    }
			  case SET_STRING:
			  case UNIFY_STRING:
			    {
			      cout << "(\"";
			      cout << (char*)pc;
			      cout << "\")";
			      char* c = (char*)pc;
			      int size = strlen(c);
			      pc += size+1;
			      break;
			    }

			  case SWITCH_ON_TERM: // not picked up by Mk...
			    coded_inst = "roooooo";
			    end_of_inst = start_of_inst + 14;
			    
			  default:   // The other instructions.
			    commaflag = 0;	
			    length = static_cast<int>(strlen(coded_inst));
			    if (length != 0 ) 
				{
				  //
				  // There are parameters!
				  //
				  paramflag = 1;
				  commaflag = 1;
				  cout << "(";
				}
				strcpy(coded_array,coded_inst);
 				outputParams(length,commaflag,coded_array,
					     pc,atoms, array,
					     arr_index,end_of_inst,code);
			  }
			if (paramflag) cout  << ")"; 
			cout << "\n";
		}
		cout << "end(\'" << name_string << "\'/" << arity << "):\n\n\n\n";
	}
}















