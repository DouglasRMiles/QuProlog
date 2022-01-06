// token.h -     Qu-Prolog tokeniser
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
// $Id: token.h,v 1.4 2005/03/27 22:07:43 qp Exp $

#ifndef TOKEN_H
#define TOKEN_H

private:
//
// Look up the classification of a character.
//
inline int8 InType(const signed char c);

//
// Look up the digital value of a character.
//
inline int32 DigVal(const signed char c);

//
// true if it is a space.
// 
inline bool IsLayout(const signed char c);
 
// 
// Output messages for detected syntax errors. 
//
inline void SyntaxError(qint64& Integer, const int32 err);

//
// Peek ahead one character
//
inline int Peek(QPStream *InStrm, const word32);

//
// Echo a read prompt.
//
// Retained for historical reasons.
//
inline void ReadPrompt(const QPStream *, const signed char);

//
// Recover from a numeric error.
//
inline void RecoverNumber(QPStream *InStrm, const int32 base);

//
// Recover from a name that is too long.
//
inline void RecoverName(QPStream *InStrm);

//
// Recover from a quoted name.
//
inline void RecoverQuotedName(QPStream *InStrm, const bool put);

//
// Get a character.
//
inline int Get(QPStream *InStrm);

//
// Put back a character or clear EOF.
//
inline void Putback(QPStream *InStrm, const int c);

int32 base_num(QPStream *InStrm, qint64& Integer, int base);

int32 get_number_token(QPStream *InStrm, char c, qint64& Integer, double& Double);

//
// ReadCharacter(Stream *InStrm, int8 q)
// Reads one character from a quoted atom or list.
// Two adjacent quotes are read as a single character, otherwise a quote is
// returned as 0.  Error is returned as -1.  If the input syntax has character
// escapes, they are processed.
// \xhh sequences are two hexadecimal digits long.
// Note that the \c sequence allows continuation of strings.  For example:
//     "This is a string, which \c
//      has to be continued over \c
//      several lines.\n".
//
int32 ReadCharacter(QPStream *InStrm, const signed char q, qint64& Integer);

//
// GetToken() reads a single token from the input stream and returns the
// token type.  The value of the token is stored in one of the
// variables: Integer, Simple, String.
//
int32 GetToken(QPStream *InStrm, qint64& Integer, double& Double, char *Simple, Object*& String);

public:
//
// psi_read_next_token(stream, var, var)
//
// Read a token from the stream and return the token type and value.
// mode(in,out,out)
//
ReturnValue psi_read_next_token(Object *&, Object *&, Object *&);

#endif	// TOKEN_H
