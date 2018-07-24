// string_escapes.h - Get string from a string stream.
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
// $Id: string_escapes.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef STRING_ESCAPES_H
#define STRING_ESCAPES_H

public:
//
// psi_stream_to_chars(stream_index, variable)
// Get the list of characters from a string stream.
// mode(in,out)
//
ReturnValue psi_stream_to_chars(Object *& , Object *& );

//
// psi_stream_to_atom(stream_index, variable)
// Get an atom from a string stream.
// mode(in,out)
//
ReturnValue psi_stream_to_atom(Object *& , Object *& );

//
// psi_stream_to_string(stream_index, variable)
// Get a string from a string stream.
//
ReturnValue psi_stream_to_string(Object *& stream_arg, Object *& string_arg);

//
// psi_list_to_string(list, variable)
// Convert a list into a string
//
ReturnValue psi_list_to_string(Object *& list_arg, Object *& string_arg);

//
// psi_string_to_list(string, variable)
// Convert a string into a list
//
ReturnValue psi_string_to_list(Object *& string_arg, Object *& list_arg);

//
// psi_string_to_atom(string, variable)
// Convert a string into an atom
//
ReturnValue psi_string_to_atom(Object *& string_arg, Object *& atom_arg);

//
// psi_atom_to_string(atom, variable)
// Convert an atom into a string
//
ReturnValue psi_atom_to_string(Object *& atom_arg, Object *& string_arg);

//
// psi_string_length(string, variable)
// Get the length of a string
//
ReturnValue psi_string_length(Object *& string_arg, Object *& length_arg);

//
// psi_string_concat(string, string, variable)
// Concatentate 2 strings
//
ReturnValue psi_string_concat(Object *& string1_arg, Object *& string2_arg, 
			      Object *& concat_arg);

//
// psi_split_string(string, integer, variable, variable)
// Split a string at the given position
//
ReturnValue psi_split_string(Object *& string_arg, Object *& pos_arg, 
			     Object *& split1_arg, Object *& split2_arg);


//
// psi_hash_string(A,B)
// mode(in,out)
// 
//
ReturnValue psi_hash_string(Object *& object1, Object *& object2);


ReturnValue psi_re_free(Object *& object1);

ReturnValue psi_re_compile(Object *& object1, Object *& object2);

ReturnValue psi_re_match(Object *& object1, Object *& object2,
                         Object *& object3, Object *& object4,
                         Object *& object5);

#endif // STRING_ESCAPES_H
