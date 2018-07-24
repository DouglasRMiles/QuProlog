// machine_status.h -
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
// $Id: machine_status.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	MACHINE_STATUS_H
#define	MACHINE_STATUS_H

#include "defs.h"
#include "status.h"

//
// Flags do not restore on backtracking.
//
class MachineStatus : public Status <word8>
{
private:
  static const word8 ENABLE_SIGNALS	= 0x01;
  static const word8 SIGNALS		= 0x02;
public:
  //
  // Set the flags.
  //
  void setEnableSignals(void)	{ set(ENABLE_SIGNALS); }
  void setSignals(void)		{ set(SIGNALS); }
  //
  // Reset the flags.
  //
  void resetEnableSignals(void)		{ reset(ENABLE_SIGNALS); }
  void resetSignals(void)		{ reset(SIGNALS); }
  //
  // Test the flags.
  //
  bool testEnableSignals(void) const	{ return test(ENABLE_SIGNALS);}
  bool testSignals(void) const		{ return test(SIGNALS); }

  MachineStatus(void)			{ }
};

#endif	// MACHINE_STATUS_H

