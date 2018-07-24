// encode_stream.h - Term encoding and decoding.
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
// $Id: encode_stream.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	ENCODE_STREAM_H
#define	ENCODE_STREAM_H

//
// psi_encoded_write(stream, term)
// Encode the term and write the result to the stream.
// mode(in,in,in)
//
ReturnValue psi_encoded_write(Object *&, Object *&, Object *&);

//
// psi_encoded_read(stream, variable)
// Read an encoded term from the stream.
// mode(in,out,out,in)
//
ReturnValue psi_encoded_read(Object *&, Object *&, Object *&, Object *&);
#endif	// ENCODE_STREAM_H
