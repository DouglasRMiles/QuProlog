// pipe.cc -
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
// $Id: pipe.cc,v 1.5 2005/03/08 00:35:11 qp Exp $

#include <errno.h>
#ifdef WIN32
#include <io.h>
#include <fcntl.h>
#endif

#include "thread_qp.h"

Thread::ReturnValue
Thread::psi_pipe(Object *& input_stream_arg,
		 Object *& output_stream_arg)
{
  int fdes[2];

#ifdef WIN32
  int res = _pipe(fdes, 256, _O_BINARY);
#else
  int res = pipe(fdes);
#endif
  if (res == -1)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, 0);
    }

  QPStream *instream = new QPifdstream(fdes[0]);

  QPStream *outstream = new QPofdstream(fdes[1]);


  input_stream_arg =  heap.newInteger(reinterpret_cast<wordptr>(instream));
  output_stream_arg = heap.newInteger(reinterpret_cast<wordptr>(outstream));

  return RV_SUCCESS;
}















