// handler.h -
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
// $Id: handler.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	HANDLER_H
#define	HANDLER_H

public:
//
// handler_menu(int)
//
// Interact with the user, and return a value indicating any actions
// that need to be taken.
//
ReturnValue psi_handler_menu(Thread&, Object *&);

#endif	// HANDLER_H
