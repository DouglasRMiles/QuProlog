// thread_status.h -
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
// $Id: thread_status.h,v 1.3 2002/03/08 00:29:34 qp Exp $

#ifndef	THREAD_STATUS_H
#define	THREAD_STATUS_H

#include "defs.h"
#include "status.h"

//
// Flags require restoring to old value on backtracking.
//
class	ThreadStatus : private Status <word8>
{
private:
  
  static const word8 FAST_RETRY		= 0x01;
  static const word8 OCCURS_CHECK	= 0x02;
  static const word8 HEAT_WAVE		= 0x04;
  static const word8 DOING_RETRY     	= 0x08;
  static const word8 DO_GC	     	= 0x10;
  static const word8 NECK_CUT_RETRY     = 0x20;
  static const word8 TIMESLICE          = 0x40;
  
public:
  
  //
  // Set the flags.
  //
  void	setFastRetry(void)		{ set(FAST_RETRY); }
  void	setOccursCheck(void)		{ set(OCCURS_CHECK); }
  void	setHeatWave(void)		{ set(HEAT_WAVE); }
  void  setDoingRetry(void)             { set(DOING_RETRY); }
  void  setDoGC(void) 		        { set(DO_GC); }
  void  setNeckCutRetry(void) 	        { set(NECK_CUT_RETRY); }
  void  setTimeslicing(void) 	        { set(TIMESLICE); }
  
  //
  // Reset the flags.
  //
  void	resetFastRetry(void)		{ reset(FAST_RETRY); }
  void	resetOccursCheck(void)		{ reset(OCCURS_CHECK); }
  void	resetHeatWave(void)		{ reset(HEAT_WAVE); }
  void  resetDoingRetry(void)           { reset(DOING_RETRY); }
  void  resetDoGC(void)           	{ reset(DO_GC); }
  void  resetNeckCutRetry(void)         { reset(NECK_CUT_RETRY); }
  void  resetTimeslicing(void)          { reset(TIMESLICE); }
  
  //
  // Test the flags.
  //
  bool	testFastRetry(void) const	{ return(test(FAST_RETRY)); }
  bool	testOccursCheck(void) const	{ return(test(OCCURS_CHECK)); }
  bool	testHeatWave(void) const	{ return(test(HEAT_WAVE)); }
  bool  testDoingRetry(void) const      { return(test(DOING_RETRY)); }
  bool  testDoGC(void) const      	{ return(test(DO_GC)); }
  bool  testNeckCutRetry(void) const    { return(test(NECK_CUT_RETRY)); }
  bool  testTimeslicing(void) const     { return(test(TIMESLICE)); }
  
  ThreadStatus(void)			
  { 
    setOccursCheck(); 
    setTimeslicing();
  }
};

#endif	// THREAD_STATUS_H
