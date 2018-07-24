// qa_options.h - Options parsing for qa.
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
// $Id: qa_options.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef QA_OPTIONS_H
#define QA_OPTIONS_H

#include "defs.h"
#include "option.h"
#include "options.h"

class QaOptions: public Options
{
private:
  Option<const char *> input_file;
  Option<const char *> output_file;

public:
  const char *InputFile(void) const { return input_file.Value(); }
  const char *OutputFile(void) const { return output_file.Value(); }

  QaOptions(int,		// Incoming argc
	    char **);		// Incoming argv
};

#endif // QA_OPTIONS_H
