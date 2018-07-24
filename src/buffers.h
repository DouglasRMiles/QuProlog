// buffers.h - Qu-Prolog buffer management.
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
// $Id: buffers.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	BUFFERS_H
#define	BUFFERS_H

public:	
//
// psi_alloc_buffer(buffer)
// Return the allocated buffer.
// mode(out)
//
ReturnValue psi_alloc_buffer(Object *&);


//
// psi_dealloc_buffer(buffer)
// Trim scratchpad and deallocate the buffer.
// mode(in,in)
//
ReturnValue psi_dealloc_buffer(Object *&);

//
// psi_copy_term_from_buffer(buffer, term)
// Copy the term from the start of the buffer to the heap and return
// the copied term.
// mode(in, out)
//
ReturnValue 
psi_copy_term_from_buffer(Object *&, Object *&);

//
// psi_copy_to_buffer_tail(buffer, term, share)
// Copy the term to the buffer and add to the end of the buffer list.
// The term will be shared if share is true.
// mode(in, in, in)
//
ReturnValue
psi_copy_to_buffer_tail(Object *&, Object *&, Object *&);

//
// psi_copy_obvar_to_buffer_tail(buffer, obvar)
// Copy the obvar to the buffer and add to the end of the buffer list.
// The obvar is not dereferenced.
// mode(in, in)
//
ReturnValue
psi_copy_obvar_to_buffer_tail(Object *& , Object *&);

//
// psi_make_sub_from_buffer(buffer, term, substitution)
// The buffer contains a list representing a substitution block.
// A substitution block is built on the heap from shared copies of the domain
// and range elements in the buffer. The substitution block is turned into
// a substitution block list and applied to term to produce substitution.
//
// mode(in, in, out)
//
ReturnValue
psi_make_sub_from_buffer(Object *&, Object *&, Object *&);

//
// psi_buffer_set_domains_apart(buffer, obvar)
// Make all the domain elements in the sub in the buffer different from obvar.
//
// mode(in, in)
//
ReturnValue
psi_buffer_set_domains_apart(Object *& object1, Object *& object2);

//
// Copy a term directly in the heap.
//
// mode(in, out)
//
ReturnValue
psi_copy_term(Object *&, Object *&);

#endif  // BUFFERS_H









