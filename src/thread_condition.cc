// thread_condition.cc -
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
// $Id: thread_condition.cc,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#include "thread_condition.h"

ostream&
operator<<(ostream& ostrm, const ThreadCondition& thread_condition)
{
  switch (thread_condition.Condition())
    {
    case ThreadCondition::NEW:
      ostrm << "NEW      ";
      break;
    case ThreadCondition::RUNNABLE:
	ostrm << "RUNNABLE ";
	break;
    case ThreadCondition::SUSPENDED:
      ostrm << "SUSPENDED";
      break;
    case ThreadCondition::EXITED:
      ostrm << "EXITED   ";
      break;
      }
  
  return ostrm;
}



