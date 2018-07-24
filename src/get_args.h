// get_args.h - Put the list of atoms onto the heap in WAM format.
//		 argv is the arrey of atoms on the mainline call.
//
// Also manages initial goal passed in with -g switch
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
// $Id: get_args.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	GET_ARGS_H
#define	GET_ARGS_H

public:
//
// Put the list of atoms onto the heap in WAM format. 
// argv is the arrey of atoms on the mainline call.
// mode(out)
//
ReturnValue psi_get_args(Object *& );


//
// Extract the initial goal as a string - fails if no initial goal
//
ReturnValue psi_initial_goal(Object *& );

#endif	// GET_ARGS_H
