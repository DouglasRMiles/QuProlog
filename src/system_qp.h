// system_qp.h - Functions which use system to call CShell commands and
//           syscall to call system commands.
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
// $Id: system_qp.h,v 1.4 2004/11/24 00:12:35 qp Exp $

#ifndef SYSTEM_QP_H
#define SYSTEM_QP_H

public:
//
// psi_system(constant, var)
// X0 is a string for CShell commands. X1 is unified with the return
// value from the call to the function system.
// mode(in,out)
//
ReturnValue	psi_system(Object *& , Object *& );

//
// psi_access(atom, integer, var)
// Check the file in X0 whether has the mode in X1.  Return the result in X2.
// mode(in,in,out)
//
ReturnValue	psi_access(Object *& , Object *& , Object *& );

//
// psi_absolute_path(atom, atom)
// Get the full path name
// mode(in, out)
//
ReturnValue	psi_absolute_path(Object *& , Object *&);

//
// psi_chdir(atom)
// Change directory to dir given by the argument
// mode(in)
//
ReturnValue	psi_chdir(Object *&);

//
// psi_getcwd(atom)
// Get the current working directory
// mode(out)
//
ReturnValue	psi_getcwd(Object *&);

//
// psi_mktemp(atom, var)
// Return a temporary file name.
// mode(in,out)
//
ReturnValue	psi_mktemp(Object *& , Object *& );

//
// psi_realtime(-Integer)
//
// Returns system time.
//
ReturnValue psi_realtime(Object *&);

//
// psi_gmtime(?Integer, ?timestruct)
//
// psi_gmtime(Time, TimeStruct) succeeds if
// Time is the Unix Epoch time corresponding to the time given in
// TimeStruct which is of the form gmt_time(Year, Mth, Day, Hours, Mins, Secs)
ReturnValue psi_gmtime(Object *& , Object *& );

//
// psi_localtime(?Integer, ?timestruct)
//
// psi_localtime(Time, TimeStruct) succeeds if
// Time is the Unix Epoch time corresponding to the time given in
// TimeStruct which is of the form 
// local_time(Year, Mth, Day, Hours, Mins, Secs)
ReturnValue psi_localtime(Object *& , Object *& );

// @user
// @pred signal_to_atom(SignalNumber, SignalAtom)
// @type signal_to_atom(integer, atom)
// @mode signal_to_atom(+, -) is det
// @description
// Takes a signal number and maps it to the appropriate signal string.
// @end pred
// @end user
ReturnValue psi_signal_to_atom(Object *&, Object *&);

// @doc
// @pred nsig(NSIG)
// @type nsig(integer)
// @mode nsig(-) is det
// @description
// Returns the number of signals on this machine.
// @end pred
// @end user
ReturnValue psi_nsig(Object *&);

// @user
// @pred strerror(Errno, String)
// @type strerror(integer, atom)
// @mode strerror(in, out) is det
// @description
// An interface to the strerror(3C) call.
// @end pred
// @end doc
ReturnValue psi_strerror(Object *&, Object *&);



ReturnValue psi_stat(Object *&, Object *&);

#endif // SYSTEM_QP_H

