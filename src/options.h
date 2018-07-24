// options.h - For handling command line options.
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
// $Id: options.h,v 1.3 2006/01/31 23:17:51 qp Exp $

#ifndef	OPTIONS_H
#define	OPTIONS_H

class Options
{
protected:
  const char *usage;
  bool valid;

public:
  const char *Usage(void) const { return usage; }
  bool Valid(void) const { return valid; }

  explicit Options(const char *u) : usage(u), valid(false) {}
};

#endif	// OPTIONS_H
