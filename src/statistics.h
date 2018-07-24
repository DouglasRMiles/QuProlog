// statistics.h - Return statistical information.
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
// $Id: statistics.h,v 1.2 2001/11/21 00:21:17 qp Exp $

#ifndef	STATISTICS_H
#define STATISTICS_H

private:

//
// Return the amount of space used and available in a stack.
//
ReturnValue return_stack_stat(const FixedSizeStack& stack, Object *& );

//
// Return the amount of space used and available in the binding trail.
//
ReturnValue return_stack_stat(const BindingTrail&, Object *& );

//
// Return the amount of space used and available in the other trail.
//
ReturnValue return_stack_stat(const OtherTrail&, Object *& );

//
// Return the amount of space used and available in a heap.
//
ReturnValue return_heap_stat(Heap& hp, Object *& );
//
// Return the amount of space used and available in the code area.
//
ReturnValue return_code_stat(Code& code, Object *& object1, 
			     Object *& object2, Object *& object3);
//
// Return the amount of space used and available in a hash table.
//
ReturnValue return_table_stat(FixedSizeHashTable& table, 
			      Object *& );

public:
//
// psi_cputime(var)
// Unifies  with the time in milliseconds since the system was
// started up.
//
ReturnValue psi_cputime(Object *& );

//
// psi_stat_choice(var, var, var)
// Return the amount of space used and available, and maximum usage
// in choice point stack.
//
ReturnValue psi_stat_choice(Object *& , Object *& , Object *& );

//
// psi_stat_global(var, var, var)
// Return the amount of space used and available, and maximum usage in heap.
//
ReturnValue psi_stat_global(Object *& , Object *& , Object *& );

//
// psi_stat_local(var, var, var)
// Return the amount of space used and available, and maximum usage
// in environment stack.
//
ReturnValue psi_stat_local(Object *& , Object *& , Object *& );
//
// psi_stat_binding_trail(var, var, var)
// Return the amount of space used and available, and maximum usage
// in the binding trail.
//
ReturnValue psi_stat_binding_trail(Object *& , Object *& , Object *& );
//
// psi_stat_other_trail(var, var, var)
// Return the amount of space used and available, and maximum usage
// in the other trail.
//
ReturnValue psi_stat_other_trail(Object *& , Object *& , Object *& );


//
// psi_stat_code(var, var, var)
// Return the amount of space used and available, and maximum usage
// in the code area.
//
ReturnValue psi_stat_code(Object *& , Object *& , Object *& );

//
// psi_stat_string(var, var, var)
// Return the amount of space used and available, and maximum usage
// in the string table.
//
ReturnValue psi_stat_string(Object *& , Object *& , Object *& );

//
// psi_stat_ip(var, var, var)
// Return the amount of space used and available in the IP table.
//
ReturnValue psi_stat_ip_table(Object *& , Object *& );

//
// psi_stat_name(var, var)
// Return the amount of space used and availabe in the name table.
//
ReturnValue psi_stat_name(Object *& , Object *& );

//
// psi_stat_atom(var, var)
// Return the amount of space used and availabe in the atom table.
//
ReturnValue psi_stat_atom(Object *& , Object *& );
//
// psi_stat_scratchpad(var, var)
// Return the space info for the scratchpad.
//
ReturnValue psi_stat_scratchpad(Object *&, Object *&,  Object *&);

//
// psi_stat_predicate(var, var)
// Return the amount of space used and availabe in the predicate table.
//
ReturnValue psi_stat_predicate(Object *& , Object *& );

//
// psi_stat_memory(var)
// Return the total amount of space allocated by the operating system.
//
ReturnValue psi_stat_memory(Object *& );

//
// psi_stat_program(var)
// Return the amount of space used by code area and various tables.
//
ReturnValue psi_stat_program(Object *& );

#endif // STATISTICS_H
