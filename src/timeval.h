// timeval.h - Routines for handling time. Covers only the timeval structure.
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
// $Id: timeval.h,v 1.7 2006/03/30 22:50:31 qp Exp $

#ifndef	TIMEVAL_H
#define	TIMEVAL_H

#include <math.h>

#ifdef WIN32
#include <time.h>
#include <winsock2.h>
#include <io.h>
#include <windows.h>	
extern int gettimeofday(struct timeval* tp, void* tzp);
typedef u_int suseconds_t;
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#include <iostream>
using namespace std;

#include "errors.h"

class Timeval
{
private:
  timeval tv;

public:
  Timeval(const time_t sec, const suseconds_t usec = 0)
    {
      assert(sec != (time_t) -1 || usec == 0);// sec == -1 -> usec == 0
      assert(usec < 1000000);		// 1 million

      tv.tv_sec = sec; 
      tv.tv_usec = usec;
    }
  Timeval(void)
    {
      SYSTEM_CALL_LESS_ZERO(gettimeofday(&tv, NULL));
    }

  // t1 - t2
  Timeval(const Timeval& t1, const Timeval& t2)
    {
      if (t1.isForever())
        {
          tv.tv_sec = (time_t) -1;
          tv.tv_usec = 0;
        }
      else if (t1.MicroSec() < t2.MicroSec())
        {
          tv.tv_usec = 1000000 + t1.MicroSec() - t2.MicroSec();
          tv.tv_sec = t1.Sec() - t2.Sec() - 1;
        }
      else
        {
          tv.tv_usec = t1.MicroSec() - t2.MicroSec();
          tv.tv_sec = t1.Sec() - t2.Sec();
        }
    }
      
  Timeval(const double d)
    {
      if (d < 0) 
        { 
           tv.tv_sec = (time_t) -1;  
           tv.tv_usec = 0; 
        } 
      else
        {
          gettimeofday(&tv, NULL);
          qint64 s = (qint64)floor(d);
          qint64 m = (qint64)floor((d-s)*1000000);
          qint64 ms = tv.tv_usec + m;
          qint64 secs = tv.tv_sec + s + ms / 1000000;
          qint64 usecs = ms % 1000000;
          tv.tv_sec = (time_t)secs;
          tv.tv_usec = (suseconds_t)usecs;
        }
    }

  time_t Sec(void) const { return tv.tv_sec; }
  suseconds_t MicroSec(void) const { return tv.tv_usec; }

  bool isForever(void) const { return Sec() == (time_t) -1; }

  void setTime(time_t s, suseconds_t ms)
  {
    tv.tv_sec = s;
    tv.tv_usec = ms;
  }

  void operator=(const Timeval& t)
    {
      tv.tv_sec = t.tv.tv_sec;
      tv.tv_usec = t.tv.tv_usec;
    }
  bool operator==(const Timeval& t) const
    {
      if (tv.tv_sec < t.tv.tv_sec) return false;
      if (tv.tv_sec > t.tv.tv_sec) return false;
      // tv.tv_sec == t.tv.tv_sec
      return tv.tv_usec == t.tv.tv_usec;
    }
  bool operator!=(const Timeval& t) const
    {
      if (tv.tv_sec < t.tv.tv_sec) return true;
      if (tv.tv_sec > t.tv.tv_sec) return true;
      // tv.tv_sec == t.tv.tv_sec
      return tv.tv_usec != t.tv.tv_usec;
    }
  bool operator<(const Timeval& t) const
    {
      if (Sec() == (time_t) -1)
	{
	  return false;
	}
      else if (t.Sec() == (time_t) -1)
	{
	  return true;
	}
      else
	{
          if (tv.tv_sec < t.tv.tv_sec) return true;
          if (tv.tv_sec > t.tv.tv_sec) return false;
          // tv.tv_sec == t.tv.tv_sec
          return tv.tv_usec < t.tv.tv_usec;
	}
    }
  bool operator<=(const Timeval& t) const
    {
      if (Sec() == (time_t) -1)
	{
	  return t.Sec() == (time_t) -1;
	}
      else if (t.Sec() == (time_t) -1)
	{
	  return true;
	}
      else
	{
          if (tv.tv_sec < t.tv.tv_sec) return true;
          if (tv.tv_sec > t.tv.tv_sec) return false;
          // tv.tv_sec == t.tv.tv_sec
          return tv.tv_usec <= t.tv.tv_usec;
	}
    }
/*
  bool operator>(const Timeval& t) const
    {
      if (Sec() == (time_t) -1)
	{
	  return t.Sec() != (time_t) -1;
	}
      else if (t.Sec() == (time_t) -1)
	{
	  return false;
	}
      else
	{
	  return timercmp(&tv, &t.tv, >);
	}
    }
  bool operator>=(const Timeval& t) const
    {
      if (Sec() == (time_t) -1)
	{
	  return t.Sec() == (time_t) -1;
	}
      else if (t.Sec() == (time_t) -1)
	{
	  return false;
	}
      else
	{
	  return timercmp(&tv, &t.tv, >=);
	}
    }
*/
};

inline std::ostream& operator<<(std::ostream& ostrm, const Timeval& t)
{
  ostrm << "sec = " << t.Sec() << " usec = " 
        << t.MicroSec();

  return ostrm;
}

#endif	// TIMEVAL_H
