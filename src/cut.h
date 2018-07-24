// cut.h - Cut support routines for interpreter.
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
// $Id: cut.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	CUT_H
#define	CUT_H

public:
//
// psi_get_level(variable)
// Return the current choice point as an integer.
// mode(out)
//
ReturnValue	psi_get_level(Object *& );

//
// psi_delayneckcut(choicepoint)
// Cut the choice back to the specified position.
// Restore X registers - needed to recover from delay handling at neck
// cut.
// mode(in)
//
ReturnValue	psi_delayneckcut(Object *& );

//
// psi_cut(choicepoint)
// Cut the choice back to the specified position.
// mode(in)
//
ReturnValue	psi_cut(Object *& );

#endif	// CUT_H


