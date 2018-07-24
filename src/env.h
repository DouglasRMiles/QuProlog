//
// env.h - Contains a set of functions which can be used for
// 	     assessing the overall tasks such as setting flags,
//           call another functions and print out the statistics.
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
// $Id: env.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $


#ifndef ENV_H
#define ENV_H

private:
ReturnValue call_predicate(int32 noargs, ...);

public:

//
// psi_uncurry(term1, term2).
// Flattens (uncurries) term1 to term2.
// mode(in,out)
//
ReturnValue psi_uncurry(Object *& , Object *& );

//
// psi_set_flag(integer, integer).
// Sets internal system flag.
// mode(in,in)
//
ReturnValue psi_set_flag(Object *& , Object *& );

//
// psi_get_flag(integer, variable).
// Gets internal system flag.
// mode(in,out)
//
ReturnValue psi_get_flag(Object *& , Object *& );

ReturnValue psi_make_cleanup_cp(Object *& );

//
// psi_call_predicate(structure,..args...)
// These functions execute the nonvariable term as the term
// itself in the program text with arguments ...args....
// mode(in)
// mode(in,in)
// mode(in,in,in)
// mode(in,in,in,in)
// 
ReturnValue psi_call_predicate0(Object *&);
ReturnValue psi_call_predicate1(Object *&, Object *&);
ReturnValue psi_call_predicate2(Object *&, Object *&, Object *&);
ReturnValue psi_call_predicate3(Object *&, Object *&, Object *&, Object *&);
ReturnValue psi_call_predicate4(Object *&, Object *&, Object *&, Object *&, Object *&);

#if 0
// 
// psi_call_clause(address, term)
// Execute a clause from address and use the term as query.  This is used for
// decompiling a dynamic clause.
// mode(in,in)
//
ReturnValue psi_call_clause(Object *& , Object *& );
#endif // 0

//
// psi_get_qplibpath(variable).
// This functionn returns the path for 
// files to the variable.
// mode(out)
//
ReturnValue psi_get_qplibpath(Object *& );

//
// Get hold of the value of the environment variable QPLIBPATH.
//
void	InitQPLibPath(void);

#endif	// ENV_H

