// dyn_code.h - Dynamic code area management.
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
// $Id: dyn_code.h,v 1.4 2005/11/06 22:59:16 qp Exp $

#ifndef	DYN_CODE_H
#define	DYN_CODE_H

//
// psi_code_top(variable)
// Return the top of the code area.
// mode(out)
//
ReturnValue psi_code_top(Object*& object1);

//
// psi_get_opcode(opcode, buffer, offset)
// Get an opcode from the code area at offset from buffer.
// mode(out,in,in)
//
ReturnValue psi_get_opcode(Object*& object1, Object*& object2, 
			   Object*& object3);

//
// psi_get_const(constant, buffer, offset)
// Get a constant from the code area at offset from buffer.
// mode(out,in,in)
//
ReturnValue psi_get_const(Object*& object1, Object*& object2, 
			  Object*& object3);

//
// psi_get_integer(constant, buffer, offset)
// Get an integer from the code area at offset from buffer.
// mode(out,in,in)
//
ReturnValue psi_get_integer(Object*& object1, Object*& object2, 
			    Object*& object3);

//
// psi_get_double(constant, buffer, offset)
// Get a double from the code area at offset from buffer.
// mode(out,in,in)
//
ReturnValue psi_get_double(Object*& object1, Object*& object2, 
                           Object*& object3);


//
// psi_get_number(number, buffer, offset)
// Get a number from the code area at offset from buffer.
// mode(out,in,in)
//
ReturnValue psi_get_number(Object*& object1, Object*& object2, 
			   Object*& object3);

//
// psi_get_address(address, buffer, offset)
// Get an address from the code area at offset from buffer.
// mode(out,in,in)
//
ReturnValue psi_get_address(Object*& object1, Object*& object2, 
			    Object*& object3);

//
// psi_get_offset(offset, buffer, offset)
// Get an offset from the code area at offset from buffer.
// mode(out,in,in)
//
ReturnValue psi_get_offset(Object*& object1, Object*& object2, 
			   Object*& object3);

//
// psi_get_pred(predicate atom, buffer, offset)
// Get a predicate atom from the code area at offset from buffer.
// mode(out,in,in)
//
ReturnValue psi_get_pred(Object*& object1, Object*& object2, Object*& object3);

//
// psi_get_entry(offset, predicate, predtype)
// Get the entry point to a predicate.
// mode(out,in, out)
//
ReturnValue psi_get_entry(Object*& object1, Object*& object2, 
			  Object*& object3);

//
// psi_reset_entry(predicate, arity)
// Abolish the predicate definition. 
// mode(in,in)
//
ReturnValue psi_reset_entry(Object*& object1, Object*& object2);

// psi_assert(Head, Assembled, FirstLast, Ref).
// mode(in,in,in,out).
//
ReturnValue psi_assert(Object*& object1, Object*& object2, 
		       Object*& object3, Object*& object4);

// psi_retract(Ref).
// retract clause with reference Ref.
// mode(in,in).
//
ReturnValue psi_retract(Object*& object1);

// Get the timestamp for a predicate
// mode psi_predicate_stamp(in,in,out)
//
ReturnValue psi_predicate_stamp(Object*& object1, Object*& object2,
                            Object*& object3);
// Get the P/N info if the timestamps have changed
// mode psi_predicate_stamp_change(in,in,out)
//
ReturnValue psi_predicate_stamp_change(Object*& object1, Object*& object2,
				       Object*& object3);
//
// psi_dynamic(pred, arity, indexArg, hashtablesize)
// Declare pred/arity as a dynamic predicate with indexArg (default = 1)
// and hashtablesize (default = 2)
// mode(in,in,in,in).
ReturnValue psi_dynamic(Object*& object1, Object*& object2, 
			Object*& object3, Object*& object4);

//
// psi_get_dynamic_chain(predicate, chain)
// Get the entry point to a predicate.
// mode(in, out)
//
ReturnValue psi_get_dynamic_chain(Object*& object1, Object*& object2);

//
// psi_get_first_clause(chain, time, ref, more)
// Get the first linkblock ptr for the chain
// more is true if there are subsequent clauses
//
ReturnValue psi_get_first_clause(Object*& object1, Object*& object2,
				 Object*& object3, Object*& object4);
//
// psi_get_next_clause(ptr, time, next, more)
// Get the next linkblock ptr for ptr.
// mode(in, out, out)
//
ReturnValue psi_get_next_clause(Object*& object1, Object*& object2,
				Object*& object3, Object*& object4);


//
// psi_get_next_clause(link, nextlink)
// get the next link in the clause linking chain
// mode(in,out)
//
//ReturnValue psi_get_next_clause(Object*& object1, Object*& object2);

#endif	// DYN_CODE_H



