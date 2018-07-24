// signals.h -
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
// $Id: signals.h,v 1.4 2006/01/31 23:17:51 qp Exp $

#ifndef	SIGNALS_H
#define	SIGNALS_H


#include <signal.h>
#include <string.h>

#include "debug.h"
#include "defs.h"
#include "status.h"

class SignalStatus : public Status <word8>
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
  
  SignalStatus(void)			{ }
};

class Signals
{
private:
  class Signal
  {
  private:
    int signal;
    char *name;
  public:
    //
    // Set and clear the signal.
    //
    void Increment(void) { signal++; }
    void Decrement(void) { signal--; }
    
    void Clear(void) { signal = 0; }

    bool IsSet(void)
      {
	bool is_set;
	is_set = signal != 0;
	return is_set;
      }
    
    //
    // Get the cell representation of the signal.
    //
    const char *Name(void) const { return name; }
    
    //
    // Initialise the entry.
    //
    void init(const char *n) {
      int len = strlen(n);
      name = new char[len+1];
      strcpy(name, n);
    }

  public:    
    Signal(void) : signal(0), name(NULL) { }
    ~Signal(void) { }
  };

  Signal signals[NSIG + 1];

  SignalStatus signal_status;

public:
  void Increment(const int sig)
    {
      assert(0 < sig && sig <= NSIG);
      signals[sig].Increment();
    }
  void Decrement(const int sig)
    {
      assert(0 < sig && sig <= NSIG);
      signals[sig].Decrement();
    }
  bool IsSet(const int sig)
    {
      assert(0 < sig && sig <= NSIG);
      return signals[sig].IsSet();
    }
  void Clear(const int sig)
    {
      assert(0 < sig && sig <= NSIG);
      signals[sig].Clear();
    }
  const char *Name(const int sig)
    {
      assert(0 < sig && sig <= NSIG);
      return signals[sig].Name();
    }

  SignalStatus& Status(void) { return signal_status; }

  Signals(void);
};

#endif	// SIGNALS_H
