// ipc_escapes.h - Interprocess communication.
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
// $Id: ipc_escapes.h,v 1.3 2003/10/05 04:50:46 qp Exp $

#ifndef	IPC_ESCAPES_H
#define	IPC_ESCAPES_H

public:


//
// ipc_make_iterator(reference_out)
//
// Create an iterator for use with ipc_first and ipc_next
//
// mode(out)
//
//
ReturnValue psi_make_iterator(Object *&);

// ipc_first(reference_in, timeout, reference_out)
//
// Get the reference to the first message on the thread's ipc queue.
//
// mode(in, in, out)
//
ReturnValue psi_ipc_first(Object *&, Object *&, Object *&);

//
// ipc_next(timeout, reference-in, reference-out)
//
// Get the reference to the next message off the thread's ipc queue.
//
// mode(in, in, out)
//
ReturnValue psi_ipc_next(Object *&, Object *&, Object *&);

//
// ipc_get_message(message, reference, from-address, remember-names)
//
// Lookup and decode the fields of a message given a reference.
//
// mode(out, in, out, in)
//
ReturnValue psi_ipc_get_message(Object *&, Object *&, Object *&, Object *&);

//
// ipc_commit(reference)
//
// Commit to receiving a message.
//
// mode(in)
//
ReturnValue psi_ipc_commit(Object *&);


//
// Broadcast message to all current local threads
// mode(in)
//
ReturnValue psi_broadcast(Object *&);

#endif	// IPC_ESCAPES_H





