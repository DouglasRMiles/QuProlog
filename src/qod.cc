// qod.cc -
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
// $Id: qod.cc,v 1.6 2005/03/08 00:35:13 qp Exp $

#include <iostream>
#include <stdio.h>
#include <fstream>

#include <string.h>

#include "code.h"
#include "defs.h"
#include "defaults.h"
#include "errors.h"
#include "instructions.h"
#include "int.h"

const char *Program = "qod";

//
// Handler for out of memory via new
//
typedef void (*new_handler) ();
new_handler set_new_handler(new_handler p) throw();

void noMoreMemory()
{
   cerr << "No more memory available for " << Program << endl;
   abort();
}

static void dump_instruction(istream&, u_long&, u_long&,
			     char *[], const size_t);
static void dump_predicate(istream&, u_long&,
			   char *[], const size_t);
static void advance(const u_long, u_long&, u_long&); 
static void dump_constant(const Code::ConstantSizedType,
			  char *[], const size_t);
static void dump_table_constant(const Code::ConstantSizedType,
				char *[], const size_t);
static void dump_table_atom_arity(const Code::ConstantSizedType,
				  const Code::NumberSizedType,
				  char *[], const size_t);
static void dump_table_label(const Code::OffsetSizedType, const u_long);

int
main(int argc, char **argv)
{
  // set the out-of-memory handler
#ifdef WIN32
  std::set_new_handler(noMoreMemory);
#else
  set_new_handler(noMoreMemory);
#endif

  if (argc != 2)
    {
      Usage("qod", "input-file");
    }

  ifstream ifstrm(argv[1]);
  if (ifstrm.bad())
    {
      FatalS(__FUNCTION__, "Couldn't open ", argv[1]);
    }

  // Initialise
  u_long byte_count = 0;

  // Read the string table
  char *strings[1024];
  u_long string_count = 0;

  printf("% 8lx: ", byte_count);

  Code::AddressSizedType string_table_size =
    IntLoad<Code::AddressSizedType>(ifstrm);
  byte_count += Code::SIZE_OF_ADDRESS;

  printf("String table size = %ld bytes\n", string_table_size);

  while (string_table_size > 0)
    {
      u_long len = 0;

      printf("% 8lx: ", byte_count);

      char *str = new char[ATOM_LENGTH];
      
      // Read a string
      char c;

      do {
	if (ifstrm.bad())
	  {
	    Fatal(__FUNCTION__, "Bad news from the input file");
	  }

	ifstrm.get(c);
	str[len] = c;
	len++;
	byte_count++;
      }	while (c != '\0');

      printf("% 4ld %s\n", string_count, str);
      strings[string_count] = str;
      string_count++;

      string_table_size -= len;
    }

  Code::OffsetSizedType query_block_size =
    IntLoad<Code::OffsetSizedType>(ifstrm);

  if (query_block_size > 0)
    {
      u_long size = query_block_size;

      cout << '' << endl;
      printf("% 8lx: ", byte_count);
      printf("Query block size = %ld bytes\n", query_block_size);

      while (size > 0)
	{
	  dump_instruction(ifstrm, byte_count, size, strings, string_count);
	}
    }
  else
    {
      cout << "--------------------------------------------------" << endl;
      printf("% 8lx: ", byte_count);
      printf("Query block size = %ld bytes\n", query_block_size);
    }

  byte_count += Code::SIZE_OF_OFFSET;

  while (ifstrm.peek() != EOF)
    {
      cout << '' << endl;
      dump_predicate(ifstrm, byte_count, strings, string_count);
    }

  ifstrm.close();

  exit(0);
}

void
advance(const u_long bytes,
	u_long& byte_count,
	u_long& size)
{
  byte_count += bytes;
  size -= bytes;
}

void
dump_table_constant(const Code::ConstantSizedType constant,
		    char *strings[], const size_t string_count)
{
  if (constant == (Code::ConstantSizedType) -1)
    {
      cout << "$default";
    }
  else
    {
      dump_constant(constant, strings, string_count);
    }
}

void
dump_table_label(const Code::OffsetSizedType label, const u_long end_addr)
{
  if (label == (Code::OffsetSizedType) -1)
    {
      cout << "$fail";
    }
  else
    {
      printf("%lx=%lx", label, label + end_addr);
    }
}

void
dump_table_atom_arity(const Code::ConstantSizedType atom,
		      const Code::NumberSizedType arity,
		      char *strings[], const size_t string_count)
{
  if (atom == (Code::ConstantSizedType) -1 && arity == 0)
    {
      cout << "$default";
    }
  else
    {
      Cell cell;

      cell.set(atom);

      if (cell.isAtom())
	{
	  const u_long atom_loc = cell.restOfAtomic();

	  printf("%ld=%s/%ld", atom_loc, strings[atom_loc], arity);
	}
      else
	{
	  printf("%lx=?atom?/%ld", atom, arity);
	}
    }
}

void
dump_constant(const Code::ConstantSizedType constant,
	      char *strings[],
	      const size_t string_count)
{
  printf("%lx=", constant);

  Cell cell;

  cell.set(constant);

  if (cell.isShort())
    {
      printf("%ld short", cell.shortOf());
    }
  else if (cell.isAtom())
    {
      const u_long atom_loc = cell.restOfAtomic();

      if (atom_loc < string_count)
	{
	  printf("%ld '%s'", atom_loc, strings[atom_loc]);
	}
      else
	{
	  printf("%lx ?atom?", atom_loc);
	}
    }
  else
    {
      printf("%lx ?constant?", constant);
    }
}

void
dump_instruction(istream& istrm,
		 u_long& byte_count,
		 u_long& size,
		 char *strings[],
		 const size_t string_count)
{
  const u_long instr_start = byte_count;

  printf("% 8lx: ", byte_count);

  const Code::InstructionSizedType instruction =
    IntLoad<Code::InstructionSizedType>(istrm);
  advance(Code::SIZE_OF_INSTRUCTION, byte_count, size);

  if (instruction == 0 ||
      instruction > UNIFY_Y_REF)
    {
      Fatal(__FUNCTION, "Bad instruction: ");
    }

  printf("%s[%s]", opnames[instruction], operands[instruction]);

  const char *args = operands[instruction];
  const size_t num_args = strlen(args);

  Code::TableSizeSizedType table_size = 0;

  if (num_args > 0)
    {
      cout << '(';
      for (size_t i = 0; i < num_args; i++)
	{
	  switch (args[i])
	    {
	    case 'c':
	      {
		const Code::ConstantSizedType constant =
		  IntLoad<Code::ConstantSizedType>(istrm);
		advance(Code::SIZE_OF_CONSTANT, byte_count, size);

		dump_constant(constant, strings, string_count);
	      }
	      break;
	    case 'n':
	      {
		const Code::NumberSizedType number =
		  IntLoad<Code::NumberSizedType>(istrm);
		advance(Code::SIZE_OF_NUMBER, byte_count, size);

		printf("%ld", number);
	      }
	      break;
	    case 'o':
	      {
		size_t offset_adjust = 0;
		
		switch  (instruction)
		  {
		  case TRY:
		  case TRY_ME_ELSE:
		    offset_adjust = Code::SIZE_OF_INSTRUCTION +
		      Code::SIZE_OF_NUMBER + Code::SIZE_OF_OFFSET;
		    break;
		  case RETRY:
		  case RETRY_ME_ELSE:
		    offset_adjust = Code::SIZE_OF_INSTRUCTION +
		      Code::SIZE_OF_OFFSET;
		    break;
		  case TRUST:
		    offset_adjust = Code::SIZE_OF_INSTRUCTION +
		      Code::SIZE_OF_OFFSET;
		    break;
		  }
	
		const Code::OffsetSizedType offset =
		  IntLoad<Code::OffsetSizedType>(istrm);
		advance(Code::SIZE_OF_OFFSET, byte_count, size);

		printf("%lx %lx", offset,
			  offset + instr_start + offset_adjust);
	      }
	      break;
	    case 'p':
	      {
		const Code::PredSizedType predicate =
		  IntLoad<Code::PredSizedType>(istrm);
		advance(Code::SIZE_OF_PRED, byte_count, size);

		printf("%ld=%s", predicate, strings[predicate]);
	      }
	      break;
	    case 'r':
	      {
		const Code::RegisterSizedType reg =
		  IntLoad<Code::RegisterSizedType>(istrm);
		advance(Code::SIZE_OF_REGISTER, byte_count, size);

		printf("%ld", reg);
	      }
	      break;
	    case 't':
	      {
		table_size = IntLoad<Code::TableSizeSizedType>(istrm);
		advance(Code::SIZE_OF_TABLE_SIZE, byte_count, size);

		printf("%ld", table_size);
	      }
	      break;
	    default:
	      Fatal(__FUNCTION__, "Uncaught operand case ");
	      break;
	    }

	  if (i < num_args - 1)
	    {
	      cout << ", ";
	    }
	}
      
      cout << ')';
    }
  
  const u_long instr_size = byte_count - instr_start;
  const u_long instr_end = byte_count;

  printf(" (%ld bytes)", instr_size);
  if (instr_size != opsizes[instruction])
    {
      Fatal(__FUNCTION__, "Wrong instruction size");
    }

  if (instruction == SWITCH_ON_TERM ||
      instruction == SWITCH_ON_CONSTANT ||
      instruction == SWITCH_ON_STRUCTURE ||
      instruction == SWITCH_ON_QUANTIFIER)
    {
      switch (instruction)
	{
	case SWITCH_ON_TERM:
	  {
	    const char *branch = "VOLSQC";

	    const u_long table_bytes = 6 * Code::SIZE_OF_OFFSET;
            const u_long table_end = instr_end + table_bytes;

	    cout << endl;
	    printf("% 8lx: ", byte_count);
	    for (u_long i = 0; i < 6; i++)
	      {
		const Code::OffsetSizedType label =
		  IntLoad<Code::OffsetSizedType>(istrm);
		advance(Code::SIZE_OF_OFFSET, byte_count, size);

		cout << branch[i] << " ";
		dump_table_label(label, table_end);

		if (i < 5)
		  {
		    cout << ", ";
		  }
	      }
	    
	    const u_long bytes = byte_count - instr_end;
	    printf(" (%ld bytes)", bytes);
	    if (bytes != table_bytes)
	      {
		Fatal(__FUNCTION__, "Table size: computed=%ld != actual=%ld",
		      table_bytes, bytes);
	      }
	  }
	  break;
	case SWITCH_ON_CONSTANT:
	  {
	    const u_long table_bytes = table_size * (Code::SIZE_OF_CONSTANT +
						     Code::SIZE_OF_OFFSET);

	    for (size_t entry = 0; entry < table_size; entry++)
	      {
		if (entry % 4 == 0)
		  {
		    cout << endl;
		    printf("% 8lx: % 4ld ", byte_count, entry);
		  }

		const Code::ConstantSizedType constant =
		  IntLoad<Code::ConstantSizedType>(istrm);
		advance(Code::SIZE_OF_CONSTANT, byte_count, size);
		
		const Code::OffsetSizedType label =
		  IntLoad<Code::OffsetSizedType>(istrm);
		advance(Code::SIZE_OF_OFFSET, byte_count, size);
		
		dump_table_constant(constant, strings, string_count);
		cout << ":";
		dump_table_label(label, instr_end);
		
		if (entry + 1 < table_size)
		  {
		    cout << ", ";
		  }
	      }

	    const u_long bytes = byte_count - instr_end;
	    printf(" (%ld bytes)", bytes);
	    if (bytes != table_bytes)
	      {
		Fatal(__FUNCTION__, "Table size: computed=%ld != actual=%ld",
		      table_bytes, bytes);
	      }
	  }
	  break;
	case SWITCH_ON_STRUCTURE:
	  {
	    const u_long table_bytes = table_size * (Code::SIZE_OF_CONSTANT +
						     Code::SIZE_OF_NUMBER +
						     Code::SIZE_OF_OFFSET);
	    
	    for (u_long entry = 0; entry < table_size; entry++)
	      {
		if (entry % 4 == 0)
		  {
		    cout << endl;
		    printf("% 8lx: % 4ld ", byte_count, entry);
		  }

		const Code::ConstantSizedType atom =
		  IntLoad<Code::ConstantSizedType>(istrm);
		advance(Code::SIZE_OF_CONSTANT, byte_count, size);
		
		const Code::NumberSizedType arity =
		  IntLoad<Code::NumberSizedType>(istrm);
		advance(Code::SIZE_OF_NUMBER, byte_count, size);
		
		const Code::OffsetSizedType label =
		  IntLoad<Code::OffsetSizedType>(istrm);
		advance(Code::SIZE_OF_OFFSET, byte_count, size);
		
		dump_table_atom_arity(atom, arity, strings, string_count);
		cout << ":";
		dump_table_label(label, instr_end);
		
		if (entry + 1 < table_size)
		  {
		    cout << ", ";
		  }
	      }

	    const u_long bytes = byte_count - instr_end;
	    printf(" (%ld bytes)", bytes);
	    if (bytes != table_bytes)
	      {
		Fatal(__FUNCTION__, "Table size: computed=%ld != actual=%ld",
		      table_bytes, bytes);
	      }
	  }
	  break;
	case SWITCH_ON_QUANTIFIER:
	  {
	    const u_long table_bytes = table_size * (Code::SIZE_OF_CONSTANT +
						     Code::SIZE_OF_OFFSET);

	    for (u_long entry = 0; entry < table_size; entry++)
	      {
		if (entry % 4 == 0)
		  {
		    cout << endl;
		    printf("% 8lx: % 4ld ", byte_count, entry);
		  }
		
		const Code::ConstantSizedType atom =
		  IntLoad<Code::ConstantSizedType>(istrm);
		advance(Code::SIZE_OF_CONSTANT, byte_count, size);
		
		const Code::OffsetSizedType label =
		  IntLoad<Code::OffsetSizedType>(istrm);
		advance(Code::SIZE_OF_OFFSET, byte_count, size);
		
		printf("%ld:", atom);
		dump_table_label(label, instr_end);

		if (entry + 1 < table_size)
		  {
		    cout << ", ";
		  }
	      }

	    const u_long bytes = byte_count - instr_end;
	    printf(" (%ld bytes)", bytes);
	    if (bytes != table_bytes)
	      {
		Fatal(__FUNCTION__, "Table size: computed=%ld != actual=%ld",
		      table_bytes, bytes);
	      }
	  }
	  break;
	}
    }

  cout << endl;
}

void
dump_predicate(istream& istrm,
	       u_long& byte_count,
	       char *strings[],
	       const size_t string_count)
{
  printf("% 8lx: ", byte_count);

  const Code::AddressSizedType string_num =
    IntLoad<Code::AddressSizedType>(istrm);
  byte_count += Code::SIZE_OF_ADDRESS;

  const Code::NumberSizedType arity =
    IntLoad<Code::NumberSizedType>(istrm);
  byte_count += Code::SIZE_OF_NUMBER;

  const Code::OffsetSizedType pred_size =
    IntLoad<Code::OffsetSizedType>(istrm);
  u_long bytes = pred_size;

  byte_count += Code::SIZE_OF_OFFSET;

  const u_long pred_start = byte_count;

  printf("%ld=%s/%ld (%ld bytes, next pred=%lx)\n",
	    string_num, strings[string_num],
	    arity, pred_size, pred_start + pred_size);

  while (bytes > 0)
    {
      dump_instruction(istrm, byte_count, bytes, strings, string_count);
    }

  const u_long size = byte_count - pred_start;
  if (pred_size != size)
    {
      Fatal(__FUNCTION__, "Predicate size: computed=%ld != actual=%ld",
	    pred_size, size);
    }
}
