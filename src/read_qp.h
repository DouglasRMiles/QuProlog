// read_qp.h - Different specialised version of read for variables.
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
// $Id: read_qp.h,v 1.1 2000/12/13 23:10:02 qp Exp $

#ifndef	READ_QP_H
#define	READ_QP_H

public:
//
// psi_readR_var(variable, name)
// Return the variable associated with the name.  Otherwise, associate the
// given variable with the name.  No association is made for any name starting
// with '_'.
// mode(out,in)
//
ReturnValue	psi_readR_var(Object *& , Object *& );

//
// psi_readR_object_variable(variable, name)
// Return the object variable associated with the name.  If none exists,
// create a new object variable and establish the association before returning
// the object variable.  No association is made for any name starting with
// '_'.
// mode(out,in)
//
ReturnValue	psi_readR_object_variable(Object *& , Object *& );

#endif	// READ_QP_H
