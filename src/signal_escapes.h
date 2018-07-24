// signal_escapes.h - Support predicates for signal.
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
// $Id: signal_escapes.h,v 1.2 2001/06/17 21:54:48 qp Exp $

#ifndef	SIGNAL_ESCAPES_H
#define	SIGNAL_ESCAPES_H

public:
//
// psi_clear_signal(signal number)
// Remove any waiting signal for a given signal number.
// mode(in)
//
ReturnValue	psi_clear_signal(Object *& );

//
// psi_clear_all_signals
// Remove all waiting signals.
// mode()
//
ReturnValue	psi_clear_all_signals(void);

//
// psi_default_signal_handler(signal number)
// Call the default signal handler.
// mode(in)
//
ReturnValue	psi_default_signal_handler(Object *& );

#endif	// SIGNAL_ESCAPES_H
