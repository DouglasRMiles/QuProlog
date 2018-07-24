// delay_escape.h - General delay mechanism.
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
// $Id: delay_escape.h,v 1.3 2001/09/20 03:22:05 qp Exp $

#ifndef	DELAY_ESCAPE_H
#define	DELAY_ESCAPE_H

public:
//
// psi_delay(variable, term)
// Delay the call to term and associate the problem with variable.
// mode(in,in)
//
ReturnValue	psi_delay(Object *& , Object *& );

//
// psi_delayed_problems_for_var(variable, term)
// Return the list of delayed problems associated with the given variable.
// mode(in,out)
//
ReturnValue	psi_delayed_problems_for_var(Object *& , Object *& );

//
// psi_get_bound_structure(variable, variable)
// Return the dereferenced variable as the argument of a "bound" structure.
// mode(in,out)
//
ReturnValue	psi_get_bound_structure(Object *& , Object *& );

//
// psi_psidelay_resume
// Restore the thread state after a retry delay from a pseudo instruction
// mode()
//
ReturnValue	 psi_psidelay_resume(void);

//
// psi_get_delays(delays,type,avoid)
// Return the list of delayed problems of given type
// type is 'all' or 'unify' other than those in avoid.
// mode(out,in,in)
// 

ReturnValue psi_get_delays(Object *&, Object*&, Object*&);

//
// psi_bound(term)
// test if term is bound to something
// mode(in)
//
ReturnValue psi_bound(Object *&);

//
// Remove any solved problems associated with any variables.
//
ReturnValue psi_compress_var_delays(void);


//
// Retry the delayed nfi problems.
//
ReturnValue psi_retry_ov_delays(void);

//
// Retry the delayed nfi and = problems.
//
ReturnValue psi_retry_ov_eq_delays(void);

#endif	// DELAY_ESCAPE_H
