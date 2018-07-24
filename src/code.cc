// code.cc - Storage for holding compiled programs and functions for the
//	     manipulation.
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
// $Id: code.cc,v 1.16 2006/01/31 23:17:49 qp Exp $

#include "config.h"
#include <iostream>
#ifdef GCC_VERSION_2
#include <streambuf.h>
#else
#include <streambuf>
#endif
#include <stdio.h>

#include "area_offsets.h"
#include "atom_table.h"
#include "objects.h"
#include "code.h"
#include "defs.h"
#include "indexing.h"
#include "instructions.h"
#include "int.h"
#include "pred_table.h"
#include "stack_qp.h"
#include "string_map.h"

//
// StaticCodeArea
//
StaticCodeArea::StaticCodeArea(word32 size)
{
  word32        FullSize;

  FullSize = size * K;
  base = new word8 [FullSize];
  top = base;
  last = base + FullSize;
  allocated_size = FullSize;
}

StaticCodeArea::~StaticCodeArea(void)
{
  if (base != NULL)
    {
      delete [] base;
    }
}       

//
// Loading and saving the code area assumes that CodeLoc is a word8 pointer.
//

void
StaticCodeArea::saveArea(ostream& ostrm, const u_long magic) const
{
  const size_t size = top - base;

  //
  // Write out the magic number.
  //
  IntSave<word32>(ostrm, magic);

  //
  // Write out the size.
  //
  IntSave<word32>(ostrm, static_cast<word32>(size));

  //
  // Write out the code.
  //
  ostrm.write((char*)base, static_cast<std::streamsize>(size));
  if (ostrm.fail())
    {
      SaveFailure(__FUNCTION__, "data segment", getAreaName());
    }
}


void 
StaticCodeArea::readData(istream& istrm, const word32 readSize)
{
  //
  // Read in a segment into the code area.
  //
  if (top + readSize >= last)
    {
      OutOfPage(__FUNCTION__, "code area", allocated_size / K);
    }
#if defined(MACOSX)
    istrm.read((char*)top, readSize);
#else
  if (istrm.good() &&
      istrm.read((char*)top, readSize).fail())
    {
      ReadFailure(__FUNCTION__, "data segment", "code area");
    }

#endif // defined(MACOSX)
  top += readSize;
}

void 
StaticCodeArea::loadArea(istream& istrm)
{
  const word32 readSize = IntLoad<word32>(istrm);
  if (readSize > allocated_size)
    {
      //
      // Wrong size.
      //
      FatalS(__FUNCTION__, "wrong size for", getAreaName());
    }

  readData(istrm, readSize);
}


// 
// Read the predicate together with its preamble and store them in the code
// area.
// Return whether it is successful or not.
//
// The .qo file format is:
//	+-------+
//	|string#|	} SIZE_OF_ADDRESS	}
//	+-------+				}
//	| arity	|	} SIZE_OF_NUMBER	}
//	+-------+				}
//	| size	|	} SIZE_OF_OFFSET	} repeat for each predicate
//	+-------+				}
//	|  c	|	}			}
//	|  o	|	} size bytes		}
//	|  d	|	}			}
//	|  e	|	}			}
//	+-------+
//
bool
Code::addPredicate(istream& istrm,
		   const char *file,
		   const StringMap& map,
		   const StringMapLoc base,
		   AtomTable* atoms,
		   PredTab& predicates,
		   Code* code)
{
  const AddressSizedType string = IntLoad<AddressSizedType>(istrm);
  const NumberSizedType arity = IntLoad<NumberSizedType>(istrm);
  const OffsetSizedType size = IntLoad<OffsetSizedType>(istrm);

  //
  // Update the predicate table and push the preamble into the code area.
  //

  Atom* pred = map.convert(base, string);
  
  predicates.addPredicate(atoms, pred, arity, PredCode::STATIC_PRED, getTop(),
			  code);
  pushPredAtom(pred);
  pushNumber((word8) arity);
  pushOffset((word16) size);

  //
  // Load the predicate
  //
  loadFileSegment(istrm, size);

  return(true);
}

//
// The following manipulation requires a bit of finesse.
// The CALL_ADDRESS and CALL_ESCAPE instructions are smaller than the 
// EXECUTE_PREDICATE instruction, so we have to move stuff around a bit.
// The EXECUTE_ADDRESS and EXECUTE_ESCAPE instructions are likewise smaller.
// 
void
Code::updateCallInstruction(const CodeLoc loc,
			    const word8 inst,
			    const CodeLoc addr)
{
  updateInstruction(loc, inst);
  updateCodeLoc(loc + SIZE_OF_INSTRUCTION, addr);
  switch (inst)
    {
    case CALL_ADDRESS:
    case CALL_ESCAPE:
      {
	CodeLoc numloc = loc +
	  SIZE_OF_INSTRUCTION + SIZE_OF_ADDRESS + SIZE_OF_NUMBER;
	const word32 number = getNumber(numloc);
	numloc = loc + SIZE_OF_INSTRUCTION + SIZE_OF_ADDRESS;
	updateNumber(numloc, (word8) number);
	const CodeLoc nooploc = loc +
	  SIZE_OF_INSTRUCTION + SIZE_OF_ADDRESS + SIZE_OF_NUMBER;
	updateInstruction(nooploc, NOOP);
      }
      break;
    case EXECUTE_ADDRESS:
    case EXECUTE_ESCAPE:
    case DB_EXECUTE_ADDRESS:
      {
	const CodeLoc nooploc = loc + SIZE_OF_INSTRUCTION + SIZE_OF_ADDRESS;
	updateInstruction(nooploc, NOOP);
      }
      break;
    default:
      assert(false);
      break;
    }
}

//
// Resolve the CALL_PREDICATE and EXECUTE_PREDICATE instructions.
//		Old					New
//	call_predicate pred, arity, n		call_address address, n
//	call_predicate pred, arity, n		call_escape pred_entry, n
//	execute_predicate pred, arity		execute_address address
//	execute_predicate pred, arity		execute_escape pred_entry
//
void
Code::resolveCallInstruction(const CodeLoc loc, const PredLoc pred, 
			     const word8 EscInst, const word8 AddrInst,
			     PredTab& predicates, Code* codePtr)
{
  PredCode	code = predicates.getCode(pred);

  if (code.type() == PredCode::ESCAPE_PRED)
    {
      //
      // Convert to escape call.
      //
      updateCallInstruction(loc - SIZE_OF_INSTRUCTION, EscInst, reinterpret_cast<CodeLoc>(pred));
    }
  else
    {
      //
      // Convert to address call.
      //
      assert(code.type() == PredCode::STATIC_PRED);
      updateCallInstruction(loc - SIZE_OF_INSTRUCTION, AddrInst,
			    code.getPredicate(codePtr));
    }
}

//
// Resolve all the references to constants, and create hash table for
// "switch" instructions.  For atom, offset to the string table in the .qo
// file is converted to atom pointers.  For numbers, offsets to 
// number table in the .qo file are converted to pointers to  number objects.
// For predicate, if the
// definition is known, convert from call_predicate (execute_predicate)
// instruction to call_address (execute_address) instruction.  If the
// definition is unknown, put a new offset in place of the old one.
//
// The following instructions will be resolved:
//		Old					New
//	put_constant old_atom_offset, i		put_constant new_atom_offset, i
//	get_constant old_atom_offset, i		get_constant new_atom_offset, i
//	unify_constant old_atom_offset		unify_constant new_atom_offset
//	set_constant old_atom_offset		set_constant new_atom_offset
//	call_predicate pred, arity, n		call_address address, n
//	call_predicate pred, arity, n		call_escape pred_entry, n
//	call_predicate old, arity, n		call_predicate new, arity, n
//	execute_predicate pred, arity		execute_address address
//	execute_predicate pred, arity		execute_escape pred_entry
//	execute_predicate old, arity		execute_predicate new, arity
//	switch_on_constant i, n, old		switch_on_constant i, n, new
//	switch_on_structure i, n, old		switch_on_structure i, n, new
//	switch_on_quantifier i, n, old		switch_on_quantifier i, n, new
//
void
Code::resolveCode(CodeLoc pc, const CodeLoc end, 
		  const StringMap& string_map, const StringMapLoc string_base,
		  PredTab& predicates, AtomTable* atoms, Code* code)
{
  CodeLoc		loc;
  word32		arity, size, i;
  PredLoc		pred;

  while (pc < end)
    {
      switch (getInstruction(pc))
	{
	  //
	  // The following instructions need resolving.
	  //
	case PUT_CONSTANT:		// put_constant c, i
	case GET_CONSTANT:		// get_constant c, i
	  {
	    loc = pc;
	    wordptr c = getAddress(pc);
	    updateConstant(loc, string_map.convert(string_base, c));
	    pc += SIZE_OF_REGISTER;
	    break;
	  }
	case GET_STRUCTURE:		// get_structure c, n, i
	  {
	    loc = pc;
	    wordptr c = getAddress(pc);
	    updateConstant(loc, string_map.convert(string_base, c));
	    pc += SIZE_OF_NUMBER + SIZE_OF_REGISTER;
	    break;
	  }
	case SET_CONSTANT:		// set_constant c
	case UNIFY_CONSTANT:		// unify_constant c
	  {
	    loc = pc;
            wordptr c = getAddress(pc);
            updateConstant(loc, string_map.convert(string_base, c));
	    break;
	  }
	case CALL_PREDICATE:	// call_predicate predicate, arity, n
	  {
	    loc = pc;
	    wordptr c = getAddress(pc);
	    Atom* pred_atom = string_map.convert(string_base, c);

	    arity = getNumber(pc);
	    pred = predicates.lookUp(pred_atom, arity, atoms, code);
	    if (pred == EMPTY_LOC || 
                predicates.getCode(pred).type() == PredCode::DYNAMIC_PRED)
	      {
		//
		// The predicate is either unknown or dynamic.
		// Update the constant.
		//
		updatePredAtom(loc, pred_atom);
	      }
	    else
	      {
		resolveCallInstruction(loc, pred,
				       CALL_ESCAPE,
				       CALL_ADDRESS,
				       predicates, code);
	      }
	    pc += SIZE_OF_NUMBER;
	    break;
	  }
	case EXECUTE_PREDICATE:	// execute_predicate predicate, arity 
	  {
	    loc = pc;
	    wordptr c = getAddress(pc);
	    Atom* pred_atom = string_map.convert(string_base, c);

	    arity = getNumber(pc);
	    pred = predicates.lookUp(pred_atom, arity, atoms, code);
	    if (pred == EMPTY_LOC || 
                predicates.getCode(pred).type() == PredCode::DYNAMIC_PRED)
	      {
		//
		// The predicate is either unknown or dynamic.
		// Update the constant.
		//
		updatePredAtom(loc, pred_atom);
	      }
	    else
	      {
		resolveCallInstruction(loc, pred,
				       EXECUTE_ESCAPE,
				       EXECUTE_ADDRESS,
				       predicates, code);
	      }
	    break;
	  }
	  break;
	case SWITCH_ON_CONSTANT:    	// switch_on_constant i, n
	  {
	    ConstEntry	*ConstTable;
	    
	    pc += SIZE_OF_REGISTER;
	    size = getTableSize(pc);
	    loc = pc;	// Mark the beginning of the hash table.
	    //
	    // Set data to manipulate the table in the code area.
	    //
	    ConstantTable	CodeConstTable(*this, loc, size);
	    //
	    // Allocate some space to create a temporary table.
	    //
	    ConstTable = new ConstEntry[CodeConstTable.size()];
	    //
	    // Get the default offset.
	    //
	    ConstTable[0].load(*this, pc);
	    //
	    // Transfer the entries of the table out for hashing.
	    // Clean the old table.
	    //
	    i = 1;
	    ConstTable[i].load(*this, pc);
	    while (! ConstTable[i].isEmpty() &&
		   i < CodeConstTable.size())
	      {
		ConstTable[i].relocate(string_map, string_base);
		ConstTable[0].store(*this, pc - ConstEntry::SIZE);
		i++;
		ConstTable[i].load(*this, pc);
	      }
	    //
	    // Hash into each entry into the table.
	    //
	    for (i--; i > 0; i--)
	      {
		CodeConstTable.add(ConstTable[i]);
	      }
	    //
	    // Clean up and advance to the next instruction.
	    //
	    delete [] ConstTable;
	    pc = loc + CodeConstTable.size() * ConstEntry::SIZE;
	  }
	break;
	case SWITCH_ON_STRUCTURE:   	// switch_on_structure i, n
	  {
	    StructEntry	*StructTable;
	    
	    pc += SIZE_OF_REGISTER;
	    size = getTableSize(pc);
	    loc = pc;	// Mark the beginning of the hash table.
	    //
	    // Set data to manipulate the table in the code area.
	    //
	    StructureTable	CodeStructTable(*this, loc, size);
	    //
	    // Allocate some space to create a temporary table.
	    //
	    StructTable = new StructEntry[CodeStructTable.size()];
	    //
	    // Get the default offset.
	    //
	    StructTable[0].load(*this, pc);
	    //
	    // Transfer the entries of the table out for hashing.
	    // Clean the old table.
	    //
	    i = 1;
	    StructTable[i].load(*this, pc);
	    while (! StructTable[i].isEmpty() &&
		   i < CodeStructTable.size())
	      {
		StructTable[i].relocate(string_map, string_base); 
		StructTable[0].store(*this,
				     pc - StructEntry::SIZE);
		i++;
		StructTable[i].load(*this, pc);
	      }
	    //
	    // Hash into each entry into the table.
	    //
	    for (i--; i > 0; i--)
	      {
		CodeStructTable.add(StructTable[i]);
	      }
	    //
	    // Clean up and advance to the next instruction.
	    //
	    delete [] StructTable;
	    pc = loc + CodeStructTable.size() * StructEntry::SIZE;
	  }
	break;
	case SWITCH_ON_QUANTIFIER:   	// switch_on_quantifier i, n
	  {
	    StructEntry	*QuantTable;
	    
	    pc += SIZE_OF_REGISTER;
	    size = getTableSize(pc);
	    loc = pc;	// Mark the beginning of the hash table.
	    //
	    // Set data to manipulate the table in the code area.
	    //
	    StructureTable	CodeQuantTable(*this, loc, size);
	    //
	    // Allocate some space to create a temporary table.
	    //
	    QuantTable = new StructEntry[CodeQuantTable.size()];
	    //
	    // Get the default offset.
	    //
	    QuantTable[0].load(*this, pc);
	    //
	    // Transfer the entries of the table out for hashing.
	    // Clean the old table.
	    //
	    i = 1;
	    QuantTable[i].load(*this, pc);
	    while (! QuantTable[i].isEmpty() &&
		   i < CodeQuantTable.size())
	      {
		QuantTable[i].relocate(string_map, string_base);
		QuantTable[0].store(*this,
				    pc - StructEntry::SIZE);
		i++;
		QuantTable[i].load(*this, pc);
	      }
	    //
	    // Hash into each entry into the table.
	    //
	    for (i--; i > 0; i--)
	      {
		CodeQuantTable.add(QuantTable[i]);
	      }
	    //
	    // Clean up and advance to the next instruction.
	    //
	    delete [] QuantTable;
	    pc = loc + CodeQuantTable.size() * StructEntry::SIZE;
	  }
	break;
	
	//
	// None of the following instructions needs resolving.
	//
	case PUT_INTEGER:
	case GET_INTEGER:
	  pc += SIZE_OF_REGISTER + SIZE_OF_INTEGER;
	  break;
	case PUT_DOUBLE:
	case GET_DOUBLE:
	  pc += SIZE_OF_REGISTER + SIZE_OF_DOUBLE;
	  break;
	case PUT_STRING:
	case GET_STRING:
	  {
	    pc += SIZE_OF_REGISTER;
	    char* c = (char*)pc;
	    int size = strlen(c);
	    pc += size+1;
	  }
	  break;
	case SET_INTEGER:
	case UNIFY_INTEGER:
	  pc += SIZE_OF_INTEGER;
	  break;
	case SET_DOUBLE:
	case UNIFY_DOUBLE:
	  pc += SIZE_OF_DOUBLE;
	  break;
	case SET_STRING:
	case UNIFY_STRING:
	  {
	    char* c = (char*)pc;
	    int size = strlen(c);
	    pc += size+1;
	  }
	  break;

	case PUT_X_VARIABLE:		// put_x_variable i, j
	case PUT_Y_VARIABLE:		// put_y_variable i, j
	case PUT_X_VALUE:		// put_x_value i, j
	case PUT_Y_VALUE:		// put_y_value i, j
	case PUT_X_OBJECT_VARIABLE:	// put_x_object_variable i, j
	case PUT_Y_OBJECT_VARIABLE:	// put_y_object_variable i, j
	case PUT_X_OBJECT_VALUE:	// put_x_object_value i, j
	case PUT_Y_OBJECT_VALUE:	// put_y_object_value i, j
	case PUT_X_TERM_SUBSTITUTION:	// put_x_term_substitution i j
	case PUT_Y_TERM_SUBSTITUTION:	// put_y_term_substitution i j
	case GET_X_VARIABLE:		// get_x_variable i, j
	case GET_Y_VARIABLE:		// get_y_variable i, j
	case GET_X_VALUE:		// get_x_value	i, j
	case GET_Y_VALUE:		// get_y_value i, j
	case GET_X_OBJECT_VARIABLE:	// get_x_object_variable i, j
	case GET_Y_OBJECT_VARIABLE:	// get_y_object_variable i, j
	case GET_X_OBJECT_VALUE:	// get_x_object_value i, j
	case GET_Y_OBJECT_VALUE:	// get_y_object_value i, j
	  pc += SIZE_OF_REGISTER + SIZE_OF_REGISTER;
	  break;
	case PUT_STRUCTURE:		// put_structure n, i
	case PUT_SUBSTITUTION:		// put_substitution n,i
	case GET_STRUCTURE_FRAME:	// get_structure_frame n, i
	  pc += SIZE_OF_NUMBER + SIZE_OF_REGISTER;
	  break;
	case PUT_LIST:			// put_list i
	case PUT_QUANTIFIER:		// put_quantifier i 
	case CHECK_BINDER:		// check_binder i 
	case PUT_INITIAL_EMPTY_SUBSTITUTION:
	  // put_initial_empty_substitution i
	case GET_LIST:			// get_list i
	case UNIFY_X_VARIABLE:		// unify_x_variable i
	case UNIFY_Y_VARIABLE:		// unify_y_variable i
	case UNIFY_X_REF:		// unify_x_ref i
	case UNIFY_Y_REF:		// unify_y_ref i
	case UNIFY_X_VALUE:		// unify_x_value i
	case UNIFY_Y_VALUE:		// unify_y_value i
	case SET_X_VARIABLE:		// set_x_variable i
	case SET_Y_VARIABLE:		// set_y_variable i
	case SET_X_VALUE:		// set_x_value i
	case SET_Y_VALUE:		// set_y_value i
	case SET_X_OBJECT_VARIABLE:	// set_x_object_variable i
	case SET_Y_OBJECT_VARIABLE:	// set_y_object_variable i
	case SET_X_OBJECT_VALUE:	// set_x_object_value i
	case SET_Y_OBJECT_VALUE:	// set_y_object_value i
	case GET_X_LEVEL:		// get_x_level i
	case GET_Y_LEVEL:		// get_y_level i
	case CUT:			// cut i
	  pc += SIZE_OF_REGISTER;
	  break;
	case UNIFY_VOID:		// unify_void n
	case SET_VOID:			// set_void n
	case SET_OBJECT_VOID:		// set_object_void n
	case ALLOCATE:			// allocate n
	case CALL_ESCAPE:		// call_escape n
	case EXECUTE_ESCAPE:		// execute_escape n
	  pc += SIZE_OF_NUMBER;
	  break;
	case DEALLOCATE:		// deallocate
	case NOOP:			// noop
	case PROCEED:			// proceed
	case ::FAIL:			// fail
	case HALT:			// halt
	case EXIT:			// exit
	case TRUST_ME_ELSE_FAIL:	// trust_me_else_fail
	case NECK_CUT:			// neck_cut
	  break;
	case JUMP:			// jump address
	  pc += SIZE_OF_ADDRESS;
	  break;
	case CALL_ADDRESS:		// call_address address, n
	  pc += SIZE_OF_ADDRESS + SIZE_OF_NUMBER;
	  break;
	case EXECUTE_ADDRESS:		// execute_address address, n
	  pc += SIZE_OF_ADDRESS;
	  break;
	case TRY_ME_ELSE:		// try_me_else n, label
	case TRY:			// try n, label
	  pc += SIZE_OF_NUMBER + SIZE_OF_OFFSET;
	  break;
	case RETRY_ME_ELSE:		// retry_me_else label
	case RETRY:			// retry label
	case TRUST:			// trust label
	  pc += SIZE_OF_OFFSET;
	  break;
	case SWITCH_ON_TERM:		// switch_on_term i, 6 * label
	  pc += SIZE_OF_REGISTER + 6 * SIZE_OF_OFFSET;
	  break;
	case PSEUDO_INSTR0:		// pseudo_instr0 i
	  pc += SIZE_OF_NUMBER; 
	  break;
	case PSEUDO_INSTR1:		// pseudo_instr1 i, i
	  pc += SIZE_OF_NUMBER + SIZE_OF_REGISTER; 
	  break;
	case PSEUDO_INSTR2:		// pseudo_instr2 i, i, j
	  pc += SIZE_OF_NUMBER + 2 * SIZE_OF_REGISTER;
	  break;
	case PSEUDO_INSTR3:		// pseudo_instr3 i, i, j, k
	  pc += SIZE_OF_NUMBER + 3 * SIZE_OF_REGISTER;
	  break;
	case PSEUDO_INSTR4:		// pseudo_instr4 i,j,k,m
	  pc += SIZE_OF_NUMBER + 4 * SIZE_OF_REGISTER;
	  break;
	case PSEUDO_INSTR5:		// pseudo_instr5 i,j,k,m,o
	  pc += SIZE_OF_NUMBER + 5 * SIZE_OF_REGISTER;
	  break;
	default:
	  loc = pc - SIZE_OF_INSTRUCTION;
	  cerr << "illegal opcode " <<  getInstruction(loc) << endl;
	  assert(false);
	  break;
	}
    }
}

void
Code::pointersToOffsets(CodeLoc pc, const CodeLoc end, AtomTable& atoms)
{
  CodeLoc		loc;
  word32		size, i;

  while (pc < end)
    {
      switch (getInstruction(pc))
	{
	  //
	  // The following instructions need translation.
	  //
	case PUT_CONSTANT:		// put_constant c, i
	case GET_CONSTANT:		// get_constant c, i
	  {
	    loc = pc;
	    Object* c = getConstant(pc);
	    assert(c->isAtom());
	    updateAddress(loc, atoms.getOffset(OBJECT_CAST(Atom*, c)));
	    pc += SIZE_OF_REGISTER;
	    break;
	  }
	case GET_STRUCTURE:		// get_structure c, n, i
	  {
	    loc = pc;
	    Object* c = getConstant(pc);
	    assert(c->isAtom());
	    updateAddress(loc, atoms.getOffset(OBJECT_CAST(Atom*, c)));
	    pc += SIZE_OF_NUMBER + SIZE_OF_REGISTER;
	    break;
	  }
	case SET_CONSTANT:		// set_constant c
	case UNIFY_CONSTANT:		// unify_constant c
	  {
	    loc = pc;
	    Object* c = getConstant(pc);
	    assert(c->isAtom());
		updateAddress(loc, atoms.getOffset(OBJECT_CAST(Atom*, c)));
	    break;
	  }
	case CALL_PREDICATE:	// call_predicate predicate, arity, n
	  {
	    loc = pc;
	    Object* c = getConstant(pc);
	    assert(c->isAtom());
	    updateAddress(loc, atoms.getOffset(OBJECT_CAST(Atom*, c)));
	    pc += 2*SIZE_OF_NUMBER;
	    break;
	  }
	case EXECUTE_PREDICATE:	// execute_predicate predicate, arity 
	  {
	    loc = pc;
	    Object* c = getConstant(pc);
	    assert(c->isAtom());
	    updateAddress(loc, atoms.getOffset(OBJECT_CAST(Atom*, c)));
	  }
	  pc += SIZE_OF_NUMBER;
	  break;
	case CALL_ADDRESS:		// call_address address, n
	  {
	    loc = pc;
	    CodeLoc cloc = getCodeLoc(pc);
	    updateAddress(loc, static_cast<word32>(cloc - getBaseOfStack()));
	  }
	  pc += SIZE_OF_NUMBER;
	  break;
	case EXECUTE_ADDRESS:		// execute_address address
	  {
	    loc = pc;
	    CodeLoc cloc = getCodeLoc(pc);
	    updateAddress(loc, static_cast<word32>(cloc - getBaseOfStack()));
	  }
	  break;

	  case SWITCH_ON_CONSTANT:    	// switch_on_constant i, n
	  {
	    pc += SIZE_OF_REGISTER;
	    size = getTableSize(pc);

	    // Translate table

	    for (i = 0 ; i < size; i++)
	      {
		ConstEntry entry;
		entry.load(*this, pc);
		if (entry.isAtom())
		  {
		    entry.pointerToOffset(atoms);
		    entry.store(*this, pc - ConstEntry::SIZE);
		  }
	      }
	  }
	break;
	case SWITCH_ON_STRUCTURE:   	// switch_on_structure i, n
	  {
	    pc += SIZE_OF_REGISTER;
	    size = getTableSize(pc);

	    // Translate table

	    for (i = 0 ; i < size; i++)
	      {
		StructEntry entry;
		entry.load(*this, pc);
                if (!entry.isEmpty())
                  {
		    entry.pointerToOffset(atoms);
		    entry.store(*this, pc - StructEntry::SIZE);
                  }
	      }
	  }
	break;
	case SWITCH_ON_QUANTIFIER:   	// switch_on_quantifier i, n
	  {
	    pc += SIZE_OF_REGISTER;
	    size = getTableSize(pc);

	    for (i = 0 ; i < size; i++)
	      {
		StructEntry entry;
		entry.load(*this, pc);
                if (!entry.isEmpty())
                  {
		    entry.pointerToOffset(atoms);
		    entry.store(*this, pc - StructEntry::SIZE);
                  }
	      }
	  }
	break;
	
	//
	// None of the following instructions needs translating.
	//
        case PUT_INTEGER:
        case GET_INTEGER:
	  pc += SIZE_OF_REGISTER + SIZE_OF_INTEGER;
	  break;
        case PUT_DOUBLE:
        case GET_DOUBLE:
	  pc += SIZE_OF_REGISTER + SIZE_OF_DOUBLE;
	  break;
	case PUT_STRING:
	case GET_STRING:
	  {
	    pc += SIZE_OF_REGISTER;
	    char* c = (char*)pc;
	    int size = strlen(c);
	    pc += size+1;
	  }
	  break;

	case UNIFY_INTEGER:
	case SET_INTEGER:
	  pc += SIZE_OF_INTEGER;
	  break;
	case UNIFY_STRING:
	case SET_STRING:
	  {
	    char* c = (char*)pc;
	    int size = strlen(c);
	    pc += size+1;
	  }
	  break;

	case UNIFY_DOUBLE:
	case SET_DOUBLE:
	  pc += SIZE_OF_DOUBLE;
	  break;
	case PUT_X_VARIABLE:		// put_x_variable i, j
	case PUT_Y_VARIABLE:		// put_y_variable i, j
	case PUT_X_VALUE:		// put_x_value i, j
	case PUT_Y_VALUE:		// put_y_value i, j
	case PUT_X_OBJECT_VARIABLE:	// put_x_object_variable i, j
	case PUT_Y_OBJECT_VARIABLE:	// put_y_object_variable i, j
	case PUT_X_OBJECT_VALUE:	// put_x_object_value i, j
	case PUT_Y_OBJECT_VALUE:	// put_y_object_value i, j
	case PUT_X_TERM_SUBSTITUTION:	// put_x_term_substitution i j
	case PUT_Y_TERM_SUBSTITUTION:	// put_y_term_substitution i j
	case GET_X_VARIABLE:		// get_x_variable i, j
	case GET_Y_VARIABLE:		// get_y_variable i, j
	case GET_X_VALUE:		// get_x_value	i, j
	case GET_Y_VALUE:		// get_y_value i, j
	case GET_X_OBJECT_VARIABLE:	// get_x_object_variable i, j
	case GET_Y_OBJECT_VARIABLE:	// get_y_object_variable i, j
	case GET_X_OBJECT_VALUE:	// get_x_object_value i, j
	case GET_Y_OBJECT_VALUE:	// get_y_object_value i, j
	  pc += SIZE_OF_REGISTER + SIZE_OF_REGISTER;
	  break;
	case PUT_STRUCTURE:		// put_structure n, i
	case PUT_SUBSTITUTION:		// put_substitution n,i
	case GET_STRUCTURE_FRAME:	// get_structure_frame n, i
	  pc += SIZE_OF_NUMBER + SIZE_OF_REGISTER;
	  break;
	case PUT_LIST:			// put_list i
	case PUT_QUANTIFIER:		// put_quantifier i 
	case CHECK_BINDER:		// check_binder i 
	case PUT_INITIAL_EMPTY_SUBSTITUTION:
	  // put_initial_empty_substitution i
	case GET_LIST:			// get_list i
	case UNIFY_X_VARIABLE:		// unify_x_variable i
	case UNIFY_Y_VARIABLE:		// unify_y_variable i
	case UNIFY_X_REF:		// unify_x_ref i
	case UNIFY_Y_REF:		// unify_y_ref i
	case UNIFY_X_VALUE:		// unify_x_value i
	case UNIFY_Y_VALUE:		// unify_y_value i
	case SET_X_VARIABLE:		// set_x_variable i
	case SET_Y_VARIABLE:		// set_y_variable i
	case SET_X_VALUE:		// set_x_value i
	case SET_Y_VALUE:		// set_y_value i
	case SET_X_OBJECT_VARIABLE:	// set_x_object_variable i
	case SET_Y_OBJECT_VARIABLE:	// set_y_object_variable i
	case SET_X_OBJECT_VALUE:	// set_x_object_value i
	case SET_Y_OBJECT_VALUE:	// set_y_object_value i
	case GET_X_LEVEL:		// get_x_level i
	case GET_Y_LEVEL:		// get_y_level i
	case CUT:			// cut i
	  pc += SIZE_OF_REGISTER;
	  break;
	case UNIFY_VOID:		// unify_void n
	case SET_VOID:			// set_void n
	case SET_OBJECT_VOID:		// set_object_void n
	case ALLOCATE:			// allocate n
	case CALL_ESCAPE:		// call_escape n
	case EXECUTE_ESCAPE:		// execute_escape n
	  pc += SIZE_OF_NUMBER;
	  break;
	case DEALLOCATE:		// deallocate
	case NOOP:			// noop
	case PROCEED:			// proceed
	case ::FAIL:			// fail
	case HALT:			// halt
	case EXIT:			// exit
	case TRUST_ME_ELSE_FAIL:	// trust_me_else_fail
	case NECK_CUT:			// neck_cut
	  break;
	case JUMP:			// jump address
	  pc += SIZE_OF_ADDRESS;
	  assert(false);
	  break;
	case TRY_ME_ELSE:		// try_me_else n, label
	case TRY:			// try n, label
	  pc += SIZE_OF_NUMBER + SIZE_OF_OFFSET;
	  break;
	case RETRY_ME_ELSE:		// retry_me_else label
	case RETRY:			// retry label
	case TRUST:			// trust label
	  pc += SIZE_OF_OFFSET;
	  break;
	case SWITCH_ON_TERM:		// switch_on_term i, 6 * label
	  pc += SIZE_OF_REGISTER + 6 * SIZE_OF_OFFSET;
	  break;
	case PSEUDO_INSTR0:		// pseudo_instr0 i
	  pc += SIZE_OF_NUMBER; 
	  break;
	case PSEUDO_INSTR1:		// pseudo_instr1 i, i
	  pc += SIZE_OF_NUMBER + SIZE_OF_REGISTER; 
	  break;
	case PSEUDO_INSTR2:		// pseudo_instr2 i, i, j
	  pc += SIZE_OF_NUMBER + 2 * SIZE_OF_REGISTER;
	  break;
	case PSEUDO_INSTR3:		// pseudo_instr3 i, i, j, k
	  pc += SIZE_OF_NUMBER + 3 * SIZE_OF_REGISTER;
	  break;
	case PSEUDO_INSTR4:		// pseudo_instr4 i,j,k,m
	  pc += SIZE_OF_NUMBER + 4 * SIZE_OF_REGISTER;
	  break;
	case PSEUDO_INSTR5:		// pseudo_instr5 i,j,k,m,o
	  pc += SIZE_OF_NUMBER + 5 * SIZE_OF_REGISTER;
	  break;
	default:
	  loc = pc - SIZE_OF_INSTRUCTION;
	  cerr << "illegal opcode " << getInstruction(loc) << endl;
	  assert(false);
	  break;
	}
    }
}


void
Code::offsetsToPointers(CodeLoc pc, const CodeLoc end, AtomTable& atoms)
{
  CodeLoc		loc;
  word32		size, i;

  while (pc < end)
    {
      switch (getInstruction(pc))
	{
	  //
	  // The following instructions need translation.
	  //
	case PUT_CONSTANT:		// put_constant c, i
	case GET_CONSTANT:		// get_constant c, i
	  {
	    loc = pc;
	    wordptr c = getAddress(pc);
	    updateConstant(loc, atoms.getAddress(c));
	    pc += SIZE_OF_REGISTER;
	    break;
	  }
	case GET_STRUCTURE:		// get_structure c, n, i
	  {
	    loc = pc;
	    wordptr c = getAddress(pc);
	    updateConstant(loc, atoms.getAddress(c));
	    pc += SIZE_OF_NUMBER + SIZE_OF_REGISTER;
	    break;
	  }
	case SET_CONSTANT:		// set_constant c
	case UNIFY_CONSTANT:		// unify_constant c
	  {
	    loc = pc;
	    wordptr c = getAddress(pc);
	    updateConstant(loc, atoms.getAddress(c));
	    break;
	  }
	case CALL_PREDICATE:	// call_predicate predicate, arity, n
	  {
	    loc = pc;
	    wordptr c = getAddress(pc);
	    updateConstant(loc, atoms.getAddress(c));
	    pc += 2*SIZE_OF_NUMBER;
	    break;
	  }
	case EXECUTE_PREDICATE:	// execute_predicate predicate, arity 
	  {
	    loc = pc;
	    wordptr c = getAddress(pc);
	    updateConstant(loc, atoms.getAddress(c));
	  }
	  pc += SIZE_OF_NUMBER;
	  break;
	case CALL_ADDRESS:		// call_address address, n
	  {
	    loc = pc;
	    wordptr cloc = getAddress(pc);
	    updateCodeLoc(loc, cloc + getBaseOfStack());
	  }
	  pc += SIZE_OF_NUMBER;
	  break;
	  
	case EXECUTE_ADDRESS:		// execute_address address
	  {	  
	    loc = pc;
	    wordptr cloc = getAddress(pc);
	    updateCodeLoc(loc, cloc + getBaseOfStack());
	  }
	  break;
	case SWITCH_ON_CONSTANT:    	// switch_on_constant i, n
	  {
            ConstEntry  *ConstTable;
 
            pc += SIZE_OF_REGISTER;
            size = getTableSize(pc);
            loc = pc;   // Mark the beginning of the hash table.
            //
            // Set data to manipulate the table in the code area.
            //
            ConstantTable       CodeConstTable(*this, loc, size);
            //
            // Allocate some space to create a temporary table.
            //
            ConstTable = new ConstEntry[size];
            ConstEntry empty(EMPTY_ENTRY, ConstEntry::EMPTY);
            //
            // Transfer the entries of the table out for hashing.
            // Clean the old table.
            //
            i = 0;
	    bool found = false;
            for (word32 count = 0; count < size; count++)
              {
                ConstTable[i].load(*this, pc);
                if (ConstTable[i].isEmpty())
                  {
		    if (!found)
		      {
			pc -= ConstEntry::SIZE;
			empty.load(*this, pc);
			found = true;
		      }
                    continue;
                  }
                if (ConstTable[i].isAtom())
                  {
                    ConstTable[i].offsetToPointer(atoms);
                  }
                i++;
              }
	    assert(found);
	    assert(empty.isEmpty());
	    // Clean out table
	    pc = loc;
            for (word32 count = 0; count < size; count++)
	      {
		empty.store(*this, pc);
                pc += ConstEntry::SIZE;
	      } 
	    //
            // Hash into each entry into the table.
            //
            while (i > 0)
              {
                i--;
                CodeConstTable.add(ConstTable[i]);
              }
            //
            // Clean up and advance to the next instruction.
            //
            delete [] ConstTable;
            pc = loc + size * ConstEntry::SIZE;
	  }
	  break;
	case SWITCH_ON_STRUCTURE:   	// switch_on_structure i, n
	  {
            StructEntry  *StructTable;
 
            pc += SIZE_OF_REGISTER;
            size = getTableSize(pc);
            loc = pc;   // Mark the beginning of the hash table.
            //
            // Set data to manipulate the table in the code area.
            //
            StructureTable       CodeStructTable(*this, loc, size);
            //
            // Allocate some space to create a temporary table.
            //
            StructTable = new StructEntry[size];
            StructEntry empty(EMPTY_ENTRY,0);
            //
            // Transfer the entries of the table out for hashing.
            // Clean the old table.
            //
            int i = 0;
	    bool found = false;
            for (word32 count = 0; count < size; count++)
              {
                StructTable[i].load(*this, pc);
                if (StructTable[i].isEmpty())
                  {
		    if (!found)
		      {
			pc -= StructEntry::SIZE;
			empty.load(*this, pc);
			found = true;
		      }
                    continue;
                  }
                StructTable[i].offsetToPointer(atoms);
		i++;
              }
	    assert(found);
	    assert(empty.isEmpty());
	    // Clean out table
	    pc = loc;
            for (word32 count = 0; count < size; count++)
	      {
		empty.store(*this, pc);
                pc += StructEntry::SIZE;
	      }
            //
            // Hash into each entry into the table.
            //                                     
	    while (i > 0)
              {
                i--;
		assert(!StructTable[i].isEmpty());
                CodeStructTable.add(StructTable[i]);
              }

            //
            // Clean up and advance to the next instruction.
            //
            delete [] StructTable;
            pc = loc + size * StructEntry::SIZE;   
	  }
	break;
	case SWITCH_ON_QUANTIFIER:   	// switch_on_quantifier i, n
	  {
            StructEntry  *StructTable;
 
            pc += SIZE_OF_REGISTER;
            size = getTableSize(pc);
            loc = pc;   // Mark the beginning of the hash table.
            //
            // Set data to manipulate the table in the code area.
            //
            StructureTable       CodeStructTable(*this, loc, size);
            //
            // Allocate some space to create a temporary table.
            //
            StructTable = new StructEntry[size];
            StructEntry empty(EMPTY_ENTRY,0);
            //
            // Transfer the entries of the table out for hashing.
            // Clean the old table.
            //
            i = 0;
	    bool found = false;
            for (word32 count = 0; count < size; count++)
              {
                StructTable[i].load(*this, pc);
                if (StructTable[i].isEmpty())
                  {
		    if (!found)
		      {
			pc -= StructEntry::SIZE;
			empty.load(*this, pc);
			found = true;
		      }
                    continue;
                  }
                StructTable[i].offsetToPointer(atoms);
                empty.store(*this, pc - StructEntry::SIZE);
                i++;
              }

 	    assert(found);
	    assert(empty.isEmpty());
	    // Clean out table
	    pc = loc;
            for (word32 count = 0; count < size; count++)
	      {
		empty.store(*this, pc);
                pc += StructEntry::SIZE;
	      }

            //
            // Hash into each entry into the table.
            //
            while (i > 0)
              {
                i--;
                CodeStructTable.add(StructTable[i]);
              }
            //
            // Clean up and advance to the next instruction.
            //
            delete [] StructTable;
            pc = loc + size * StructEntry::SIZE;     
	  }
	break;
	
	//
	// None of the following instructions needs translating.
	//
        case PUT_INTEGER:
        case GET_INTEGER:
	  pc += SIZE_OF_REGISTER + SIZE_OF_INTEGER;
	  break;
	case UNIFY_INTEGER:
	case SET_INTEGER:
	  pc += SIZE_OF_INTEGER;
	  break;
        case PUT_DOUBLE:
        case GET_DOUBLE:
	  pc += SIZE_OF_REGISTER + SIZE_OF_DOUBLE;
	  break;
	case UNIFY_DOUBLE:
	case SET_DOUBLE:
	  pc += SIZE_OF_DOUBLE;
	  break;
	case PUT_STRING:
	case GET_STRING:
	  {
	    pc += SIZE_OF_REGISTER;
	    char* c = (char*)pc;
	    int size = strlen(c);
	    pc += size+1;
	  }
	  break;

	case UNIFY_STRING:
	case SET_STRING:
	  {
	    char* c = (char*)pc;
	    int size = strlen(c);
	    pc += size+1;
	  }
	  break;

	case PUT_X_VARIABLE:		// put_x_variable i, j
	case PUT_Y_VARIABLE:		// put_y_variable i, j
	case PUT_X_VALUE:		// put_x_value i, j
	case PUT_Y_VALUE:		// put_y_value i, j
	case PUT_X_OBJECT_VARIABLE:	// put_x_object_variable i, j
	case PUT_Y_OBJECT_VARIABLE:	// put_y_object_variable i, j
	case PUT_X_OBJECT_VALUE:	// put_x_object_value i, j
	case PUT_Y_OBJECT_VALUE:	// put_y_object_value i, j
	case PUT_X_TERM_SUBSTITUTION:	// put_x_term_substitution i j
	case PUT_Y_TERM_SUBSTITUTION:	// put_y_term_substitution i j
	case GET_X_VARIABLE:		// get_x_variable i, j
	case GET_Y_VARIABLE:		// get_y_variable i, j
	case GET_X_VALUE:		// get_x_value	i, j
	case GET_Y_VALUE:		// get_y_value i, j
	case GET_X_OBJECT_VARIABLE:	// get_x_object_variable i, j
	case GET_Y_OBJECT_VARIABLE:	// get_y_object_variable i, j
	case GET_X_OBJECT_VALUE:	// get_x_object_value i, j
	case GET_Y_OBJECT_VALUE:	// get_y_object_value i, j
	  pc += SIZE_OF_REGISTER + SIZE_OF_REGISTER;
	  break;
	case PUT_STRUCTURE:		// put_structure n, i
	case PUT_SUBSTITUTION:		// put_substitution n,i
	case GET_STRUCTURE_FRAME:	// get_structure_frame n, i
	  pc += SIZE_OF_NUMBER + SIZE_OF_REGISTER;
	  break;
	case PUT_LIST:			// put_list i
	case PUT_QUANTIFIER:		// put_quantifier i 
	case CHECK_BINDER:		// check_binder i 
	case PUT_INITIAL_EMPTY_SUBSTITUTION:
	  // put_initial_empty_substitution i
	case GET_LIST:			// get_list i
	case UNIFY_X_VARIABLE:		// unify_x_variable i
	case UNIFY_Y_VARIABLE:		// unify_y_variable i
	case UNIFY_X_REF:		// unify_x_ref i
	case UNIFY_Y_REF:		// unify_y_ref i
	case UNIFY_X_VALUE:		// unify_x_value i
	case UNIFY_Y_VALUE:		// unify_y_value i
	case SET_X_VARIABLE:		// set_x_variable i
	case SET_Y_VARIABLE:		// set_y_variable i
	case SET_X_VALUE:		// set_x_value i
	case SET_Y_VALUE:		// set_y_value i
	case SET_X_OBJECT_VARIABLE:	// set_x_object_variable i
	case SET_Y_OBJECT_VARIABLE:	// set_y_object_variable i
	case SET_X_OBJECT_VALUE:	// set_x_object_value i
	case SET_Y_OBJECT_VALUE:	// set_y_object_value i
	case GET_X_LEVEL:		// get_x_level i
	case GET_Y_LEVEL:		// get_y_level i
	case CUT:			// cut i
	  pc += SIZE_OF_REGISTER;
	  break;
	case UNIFY_VOID:		// unify_void n
	case SET_VOID:			// set_void n
	case SET_OBJECT_VOID:		// set_object_void n
	case ALLOCATE:			// allocate n
	case CALL_ESCAPE:		// call_escape n
	case EXECUTE_ESCAPE:		// execute_escape n
	  pc += SIZE_OF_NUMBER;
	  break;
	case DEALLOCATE:		// deallocate
	case NOOP:			// noop
	case PROCEED:			// proceed
	case ::FAIL:			// fail
	case HALT:			// halt
	case EXIT:			// exit
	case TRUST_ME_ELSE_FAIL:	// trust_me_else_fail
	case NECK_CUT:			// neck_cut
	  break;
	case JUMP:			// jump address
	  pc += SIZE_OF_ADDRESS;
	  assert(false);
	  break;
	case TRY_ME_ELSE:		// try_me_else n, label
	case TRY:			// try n, label
	  pc += SIZE_OF_NUMBER + SIZE_OF_OFFSET;
	  break;
	case RETRY_ME_ELSE:		// retry_me_else label
	case RETRY:			// retry label
	case TRUST:			// trust label
	  pc += SIZE_OF_OFFSET;
	  break;
	case SWITCH_ON_TERM:		// switch_on_term i, 6 * label
	  pc += SIZE_OF_REGISTER + 6 * SIZE_OF_OFFSET;
	  break;
	case PSEUDO_INSTR0:		// pseudo_instr0 i
	  pc += SIZE_OF_NUMBER; 
	  break;
	case PSEUDO_INSTR1:		// pseudo_instr1 i, i
	  pc += SIZE_OF_NUMBER + SIZE_OF_REGISTER; 
	  break;
	case PSEUDO_INSTR2:		// pseudo_instr2 i, i, j
	  pc += SIZE_OF_NUMBER + 2 * SIZE_OF_REGISTER;
	  break;
	case PSEUDO_INSTR3:		// pseudo_instr3 i, i, j, k
	  pc += SIZE_OF_NUMBER + 3 * SIZE_OF_REGISTER;
	  break;
	case PSEUDO_INSTR4:		// pseudo_instr4 i,j,k,m
	  pc += SIZE_OF_NUMBER + 4 * SIZE_OF_REGISTER;
	  break;
	case PSEUDO_INSTR5:		// pseudo_instr5 i,j,k,m,o
	  pc += SIZE_OF_NUMBER + 5 * SIZE_OF_REGISTER;
	  break;
	default:
	  loc = pc - SIZE_OF_INSTRUCTION;
	  cerr << "illegal opcode " << getInstruction(loc) << endl;
	  assert(false);
	  break;
	}
    }
}



size_t
Code::argSize(const char c) const
{
  word32 arg_size = 0;

  switch (c)
    {
    case 'c':
      arg_size = SIZE_OF_CONSTANT;
      break;
    case 'i':
      arg_size = SIZE_OF_INTEGER;
      break;
    case 'd':
      arg_size = SIZE_OF_DOUBLE;
      break;
    case 'n':
      arg_size = SIZE_OF_NUMBER;
      break;
    case 'o':
      arg_size = SIZE_OF_OFFSET;
      break;
    case 'p':
      arg_size = SIZE_OF_PRED;
      break;
    case 'r':
      arg_size = SIZE_OF_REGISTER;
      break;
    case 't':
      arg_size = SIZE_OF_TABLE_SIZE;
      break;
    default:
      Fatal(__FUNCTION__, "Uncaught case");
      break;
    }

  return arg_size;
}

//
// Save the code area.
//
void	
Code::save(ostream& ostrm, AtomTable& atoms) 
{
  word32 size;
  CodeLoc start, sizeLoc;
  
  for (start = getBaseOfStack();
       start < getTopOfStack();
       start += Code::SIZE_OF_HEADER + size)
    {
      CodeLoc pc = start;
      Object* c = getConstant(pc);
      updateAddress(start, atoms.getOffset(OBJECT_CAST(Atom*, c)));
      sizeLoc = start + Code::SIZE_OF_ADDRESS + Code::SIZE_OF_NUMBER;
      size = getOffset(sizeLoc);
      pointersToOffsets(start + Code::SIZE_OF_HEADER, 
			start + Code::SIZE_OF_HEADER + size, atoms);
    }
  saveArea(ostrm, CODE_MAGIC_NUMBER);
}

//
// Restore the code area.
//
void Code::load(istream& istrm, AtomTable& atoms)
{
  loadArea(istrm);
  word32 size;
  CodeLoc start, sizeLoc;
  
  for (start = getBaseOfStack();
       start < getTopOfStack();
       start += Code::SIZE_OF_HEADER + size)
    {
      CodeLoc pc = start;
      wordptr c = getAddress(pc);
      updateConstant(start, atoms.getAddress(c));
      sizeLoc = start + Code::SIZE_OF_ADDRESS + Code::SIZE_OF_NUMBER;
      size = getOffset(sizeLoc);
      offsetsToPointers(start + Code::SIZE_OF_HEADER, 
			start + Code::SIZE_OF_HEADER + size, atoms);
    }
}










