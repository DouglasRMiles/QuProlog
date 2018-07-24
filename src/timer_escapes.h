// timer_escapes.h - Timer procedures
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

#ifndef	TIMER_ESCAPES_H
#define	TIMER_ESCAPES_H

public:
ReturnValue psi_create_timer(Object *&, Object *&, Object *&, Object *&);
ReturnValue psi_delete_timer(Object *&);
ReturnValue psi_timer_goals(Object *&);




#endif	// TIMER_ESCAPES_H
