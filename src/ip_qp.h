// ip_qp.h - Routines for manipulating implicit parameters, which must be an atom.
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
// $Id: ip_qp.h,v 1.2 2001/09/24 00:38:33 qp Exp $

#ifndef	IP_QP_H
#define	IP_QP_H

public:
//
// psi_ip_set(key, value)
// Assign a value for an implicit parameter.
// mode(in,in)
//
ReturnValue psi_ip_set(Object *& , Object *& );

// psi_ip_setA(key, hashVal, value)
// Assign a value for an array implicit parameter.
// mode(in,in,in)
//
ReturnValue psi_ip_setA(Object *& , Object *& , Object *& );

//
// psi_ip_lookup(key, value)
// Look up the value of an implicit parameter.
// mode(in,out)
//
ReturnValue	psi_ip_lookup(Object *& , Object *& );

// psi_ip_lookupA(key, hashVal, value)
// Lookup a value for an array implicit parameter.
// mode(in,in,out)
//
ReturnValue psi_ip_lookupA(Object *& , Object *& , Object *& );

// psi_ip_get_array_keys(name, values)
// return all the keys for the IP array name
// mode(in, out)
//
ReturnValue psi_ip_get_array_entries(Object *&, Object *&);

// psi_ip_array_clear(key)
// Clear (initilize) an IP array.
// mode(in)
//
ReturnValue psi_ip_array_clear(Object *& );

// psi_ip_array_init(key, size)
// Initilize an IP array to size.
// mode(in, in)
//
ReturnValue psi_ip_array_init(Object *& , Object *&);


//
// psi_ip_lookup_default(key, value,default)
// Look up the value of an implicit parameter.
// mode(in,out,in)
//
ReturnValue psi_ip_lookup_default(Object *&, Object *&, Object *&);

// psi_ip_lookupA_default(key, hash_val, value, default)
// Lookup a value for an array implicit parameter.
// mode(in,in,out, in)
//
ReturnValue psi_ip_lookupA_default(Object *&, Object *&,  Object *&, Object *&);
#endif	// IP_QP_H

