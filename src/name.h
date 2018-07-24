// name.h - Functions which build up a string which corresponds to a 
//          given list, or build up a list whose elements correspond 
//          to a given name.
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
// $Id: name.h,v 1.2 2006/02/01 04:26:02 qp Exp $

#ifndef	NAME_H
#define	NAME_H

public:

//void addEscapes(string& str, char quote);

//void removeEscapes(string& str, char quote);

//
// psi_atom_codes(atom, var)
// Convert an atom to a list of character codes.
// mode(in,out)
//
ReturnValue	psi_atom_codes(Object *& , Object *& );

//
// psi_codes_atom(list integer, var)
// Convert from a list of character codes to an atom.
// mode(in,out)
//
ReturnValue	psi_codes_atom(Object *& , Object *& );

//
// psi_char_code(char, var)
// Convert a character to its character code.
// mode(in,out)
//
ReturnValue	psi_char_code(Object *& , Object *& );
//
// psi_code_char(integer, var)
// Convert a character code to its character.
// mode(in,out)
//
ReturnValue	psi_code_char(Object *& , Object *& );

//
// psi_number_codes(number, list)
// Convert number to ASCII representation
// mode(in,out)
//
ReturnValue     psi_number_codes(Object *& , Object *& );

//
// psi_codes_number(number, list)
// Convert a list (an ASCII representation of a number) iinto that number
// mode(in,out)
//
ReturnValue     psi_codes_number(Object *& , Object *& );

#endif // NAME_H
