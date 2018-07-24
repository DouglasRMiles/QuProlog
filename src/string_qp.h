// string_qp.h -
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
// $Id: string_qp.h,v 1.3 2002/11/08 00:44:21 qp Exp $

#ifndef	STRING_QP_H
#define	STRING_QP_H

#include <string.h>

#include <iostream>

#include "defs.h"
#include "errors.h"

class String {
private:
  size_t length;
  char *string;

public:
  //
  // Copies the supplied string.
  //
  String(const char *str)
    : length(strlen(str)),
      string(new char[length + 1])
  {
    strcpy(string, str);
    string[length] = '\0';
  }

  String(const char *str,
	 const size_t len)
    : length(len),
      string(new char[length + 1])
  {
    strncpy(string, str, length);
    string[length] = '\0'; 
  }

  String(const String& str)
    : length(str.Length()),
      string(new char[length + 1])
  {
    strncpy(string, str.Str(), length);
    string[length] = '\0';
  }

//  String(std::istream& istrm);

  ~String(void)
  {
    delete [] string;
  }

  size_t Length(void) const { return length; }
  const char *Str(void) const { return string; }

  bool operator==(const String& s) const
  {
    return streq(Str(), s.Str());
  }

  bool operator!=(const String& s) const
  {
    return ! (*this == s);
  }

  bool operator==(const char *s) const
  {
    return streq(Str(), s);
  }

  bool operator!=(const char *s) const
  {
    return ! (*this == s);
  }

  // Write a string to the stream in a form that allows it to be read
  // back readily.
 // std::ostream& Save(std::ostream&) const;
};

// Print out a String in a form that can be read by a person.
extern std::ostream& operator<<(std::ostream&, const String&);

#endif	// STRING_QP_H

