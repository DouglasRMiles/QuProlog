// bios.h - Basic I/O.
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
// $Id: bios.h,v 1.2 2002/06/04 04:08:14 qp Exp $

#ifndef BIOS_H
#define BIOS_H

public:
//
// psi_get_char(stream_index, variable)
// Get the next character from the input stream.
// mode(in,out)
//
ReturnValue psi_get_char(Object *&, Object *&);
//
// psi_peek(stream_index, variable)
// Peek at the next character from the input stream.
// mode(in,out)
//
ReturnValue psi_peek(Object *&, Object *&);

//
// psi_put_char(stream_index, character)
// Put the character into the output stream.
// mode(in,in)
//
ReturnValue psi_put_char(Object *&, Object *&);

//
// psi_get_code(stream_index, variable)
// Get the next character from the input stream.
// mode(in,out)
//
ReturnValue psi_get_code(Object *&, Object *&);

//
// psi_put_code(stream_index, byte)
// Put the byte into the output stream.
// mode(in,in)
//
ReturnValue psi_put_code(Object *&, Object *&);

//
// psi_get_line(stream_index, variable)
// Get the next line from the input stream.
// The newline character is consumed but not added to the return
// value.
// mode(in,out)
//

ReturnValue psi_get_line(Object *& stream_arg, Object *& code_list);  

//
// psi_put_line(stream_index, list)
// Put the ASCII list to the stream - add a newline character.
//
// mode(in, in)

ReturnValue psi_put_line(Object *& stream_arg, Object *& code_list);

#endif // BIOS_H























