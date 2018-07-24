// write.h - Different specialised versions of write for atoms, integers, and
//	     variables.
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
// $Id: write.h,v 1.5 2005/03/27 22:07:43 qp Exp $

#ifndef WRITE_H
#define WRITE_H

private:
void writeVarName(Object* ref, NameGen,
		  word32& counter, QPStream *stream);

public:
//
// Different specialised versions of write for atoms.
//

//
// psi_write_atom(stream_index, atom)
// Default method for writing atoms.  The string is written without any
// processing.
// mode(in,in)
// 
ReturnValue psi_write_atom(Object *& , Object *& );

//
// psi_writeq_atom(stream_index, atom)
// The string is written with quotes whenever it is needed.
// mode(in,in)
// 
ReturnValue psi_writeq_atom(Object *& , Object *& );

//
// psi_write_integer(stream_index, integer)
// Write for integers.
// mode(in,in)
//
ReturnValue psi_write_integer(Object *& , Object *& );

//
// psi_write_float(stream_index, float)
// Write for floats.
// mode(in,in)
//
ReturnValue psi_write_float(Object *& , Object *& );

//
// psi_write_string(stream_index, string)
// Write for strings.
// mode(in,in)
//
ReturnValue psi_write_string(Object *& object1, Object *& object2);

//
// psi_writeq_string(stream_index, string)
// Write for strings - quotes added.
// mode(in,in)
//
ReturnValue psi_writeq_string(Object *& object1, Object *& object2);

//
// Different specialised versions of write for variables.
//

//
// psi_write_var(stream_index, variable)
// Default method for writing variables.  If the variable has a name, use the
// name.  Otherwise, the location of the variable is written as a base 16 
// number with '_' preceding it.
// mode(in,in)
//
ReturnValue psi_write_var(Object *& , Object *& );

//
// psi_writeR_var(stream_index, variable)
// Write the assigned name for the variable.
// mode(in,in)
//
ReturnValue psi_writeR_var(Object *& , Object *& );

//
// Different specialised versions of write for object variables.
//

//
// psi_write_object_variable(stream_index, object_variable)
// Default method for writing object variables.  If the variable has a name,
// use the name.  Otherwise, the location of the variable is written as a base
// 16 number with '_x' preceding it.
// mode(in,in)
//
ReturnValue psi_write_object_variable(Object *& , Object *& );

//
// psi_writeR_object_variable(stream_index, object_variable)
// Write the assigned name for the object variable.
// mode(in,in)
//
ReturnValue psi_writeR_object_variable(Object *& , Object *& );

//
// psi_writeq_object_variable(stream_index, object_variable)
// Write the assigned name for the object variable.
// Quote it if there's anything nasty inside.
//
ReturnValue psi_writeq_object_variable(Object *& , Object *& );

//
// A low-level dump of the term
//
ReturnValue psi_debug_write(Object *& );

#endif // WRITE_H
