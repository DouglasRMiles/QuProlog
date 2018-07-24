// truth3.h - 3 valued truth manipulation.
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
// $Id: truth3.h,v 1.2 2005/06/29 22:05:34 qp Exp $

#ifndef	TRUTH3_H
#define	TRUTH3_H

class truth3
{
public:
  //
  // These are not for general direct use.
  //
  enum	truth3type	{ UNSURE = -1, NO, YES }	value;

  truth3(void) { value = NO; }
  truth3(const truth3type val) { value = val; }
  truth3(const bool b) { value = b ? YES : NO; }
  
  //
  // Overload logical operators.
  //
  truth3 operator&&(const truth3& other) const
  {
    if (value == NO || other.value == NO)
      {
	return(NO);
      }
    else if (value == YES && other.value == YES)
      {
	return(YES);
      }
    else
      {
	return(UNSURE);
      }
    return(NO);
  }
  truth3 operator||(const truth3& other) const
  {
    if (value == NO && other.value == NO)
      {
	return(NO);
      }
    else if (value == YES || other.value == YES)
      {
	return(YES);
      }
    else
      {
	return(UNSURE);
      }
    return(NO);
  }
  truth3 operator!(void) const
  {
    truth3 result = UNSURE;
    
    switch (value)
      {
      case UNSURE:
	result = UNSURE;
	break;
      case NO:
	result = YES;
	break;
      case YES:
	result = NO;
	break;
      }
    
    return result;
  }
  bool operator==(const truth3& other) const
  { return(value == other.value); }
  bool operator!=(const truth3& other) const
  { return(! (*this == other)); }
};


#endif	// TRUTH3_H
