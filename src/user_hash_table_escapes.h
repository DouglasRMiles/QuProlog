// user_hash_table_escapes.h - Interface to user hash table.
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
// $Id: user_hash_table_escapes.h,v 1.1 2006/01/31 23:19:10 qp Exp $

#ifndef USER_HT_ESCAPES_H
#define USER_HT_ESCAPES_H

public:

//
// psi_user_ht_insert(Fst, Snd, Data)
// Insert Data into the user hash table indexed by Fst and Snd
//
// mode(in,in,in)

ReturnValue psi_user_ht_insert(Object *&, Object *&, Object *&);


//
// psi_user_ht_lookup(Fst, Snd, Data)
// Lookup Data in the user hash table indexed by Fst and Snd
//
// mode(in,in,out)

ReturnValue psi_user_ht_lookup(Object *&, Object *&, Object *&);

//
// psi_user_ht_remove(Fst, Snd)
// Remove entry in the user hash table indexed by Fst and Snd
//
// mode(in,in)

ReturnValue psi_user_ht_remove(Object *&, Object *&);

//
// psi_user_ht_search(Fst, Snd, Data)
// Collect together all entries in the hash table that match
// Fst and Snd. Data is a list of elements of the form '$'(F,S,T)
//
// mode(in,in,out)

ReturnValue psi_user_ht_search(Object *&, Object *&, Object *&);


#endif  // USER_HT_ESCAPES_H
