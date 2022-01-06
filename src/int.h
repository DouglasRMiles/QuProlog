// int.h - Handling of integers to reduce the problems of moving QuProlog
//	objects between machines of different ``endian-ness''.
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
// $Id: int.h,v 1.12 2005/06/29 22:05:30 qp Exp $

#ifndef	INT_H
#define	INT_H

#include "int.h"
#ifdef GCC_VERSION_2
#include <istream.h>
#else
#include <istream>
#endif
#include <limits.h>
//#include <netinet/in.h>

#include "errors.h"
#ifdef WIN32
//#define __PRETTY_FUNCTION__ __FUNCDNAME__
#endif

using namespace std;

template <class IntType>
class Int
{
protected:
  IntType value;
  int type;

public:
  virtual size_t SizeOf(void) const { return sizeof(IntType); }

  // v is the value
  // type is an optional type used in the assembler to distinguish
  // between atom ptrs and integers.
  Int(const IntType v, const int m = 0) : value(v), type(m) { }
  
  // Note: If you're passing an istrstream as the istream argument,
  // make sure you've used the istrstream(const char *, int)
  // constructur, otherwise you'll probably get a premature end of stream!
  Int(istream& istrm, const int m = 0) : type(m)
  {
#if BITS_PER_WORD != 64
    if (sizeof(IntType) == sizeof(double))
      {
        u_char w[sizeof(double)];
        for (size_t i = 0; i < sizeof(IntType); i++)
          {
            if (istrm.good())
              {
                w[i] = (u_char)istrm.get();
              }
            else
              {
                ReadFailure("integer", "i/o error");
              }
           }
         memcpy(&value, w, sizeof(double));
       }
     else
#endif
       {
         IntType v = 0;
    
         for (size_t i = 0; i < sizeof(IntType); i++)
           {
	     u_char c;

	     if (istrm.good())
	       {
	         c = (u_char)istrm.get();
	       }
	     else
	       {
	         ReadFailure("integer", "i/o error");
	       }

	     v = (v << 8) | c;
           }
         value = v;
       }
  }
  
  virtual IntType Value(void) const { return value; }
  virtual void Value(const IntType v) { value = v; }

  virtual int Type(void) const { return type; }

  virtual bool operator==(const Int<IntType>& i) const
  {
    return ((Value() == i.Value()) && (Type() == i.Type()));
  }

  virtual ostream& Save(ostream& ostrm) const
    {
#if BITS_PER_WORD != 64
      if (sizeof(IntType) == sizeof(double))
          {
            u_char w[sizeof(double)];
            memcpy(w, &value, sizeof(double));
            for (size_t i = 0; i < sizeof(IntType); i++)
              {
                ostrm << w[i];
              }
              return ostrm;
           }
         else
#endif
           {
              IntType v = Value();
              for (size_t i = sizeof(IntType); i > 0; i--)
	        {
	          const u_char c = (u_char) ((wordptr)v >> (8 * (i - 1))) & 0xff;
	          ostrm << c;
	        }
      
              return ostrm;
            }
    }
  virtual ~Int() {}
};

// Print ot an Int in a form that can be read by a person.
template <class IntType>
ostream& 
operator<<(ostream& ostrm, const Int<IntType>& i)
{
  return ostrm << i.Value();
}

template <class IntType>
void
IntSave(ostream& ostrm, const IntType value)
{
  if (! ostrm.good())
    {
      SaveFailure(__PRETTY_FUNCTION__, "precondition");
    }

  Int<IntType> i(value);
  i.Save(ostrm);
      
  if (ostrm.fail())
    {
      SaveFailure(__PRETTY_FUNCTION__, "postcondition");
    }
}

template <class IntType>
IntType
IntLoad(istream& istrm)
{
  if (! istrm.good())
    {
      ReadFailure(__PRETTY_FUNCTION__, "precondition");
    }

  Int<IntType> i(istrm);

  if (istrm.fail())
    {
      ReadFailure(__PRETTY_FUNCTION__, "postcondition");
    }

  return i.Value();
}

template <class IntType>
IntType
UnsignedMax(const IntType)
{
  switch (sizeof(IntType))
    {
    case 1:
      return UCHAR_MAX;
      break;
    case 2:
      return USHRT_MAX;
      break;
    case 4:
      return (IntType)UINT_MAX;
      break;
#if BITS_PER_WORD == 64
    case 8:
      return (IntType)ULLONG_MAX;
      break;
#endif
    default:
      return 0;
      break;
    }
}

template <class IntType>
IntType
SignedMax(const IntType)
{
  switch (sizeof(IntType))
    {
    case 1:
      return CHAR_MAX;
      break;
    case 2:
      return SHRT_MAX;
      break;
    case 4:
      return INT_MAX;
      break;
#if BITS_PER_WORD == 64
    case 8:
      return (IntType)LLONG_MAX;
      break;
#endif
    }
}

template <class IntType>
IntType
SignedMin(const IntType)
{
  switch (sizeof(IntType))
    {
    case 1:
      return CHAR_MIN;
      break;
    case 2:
      return SHRT_MIN;
      break;
    case 4:
      return INT_MIN;
      break;
#if BITS_PER_WORD == 64
    case 8:
      return (IntType)LLONG_MIN;
      break;
#endif
    }
}


#endif	// INT_H








