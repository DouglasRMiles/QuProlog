// token.cc - Tokenizer.  It assumes that EOF is -1.
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
// $Id: token.cc,v 1.15 2006/03/30 22:50:31 qp Exp $

#include <iostream>
#include <sstream>
#include <errno.h>

#include "config.h"

#include "atom_table.h"
#include "io_qp.h"
#include "is_ready.h"
#include "thread_qp.h" 
#include "scheduler.h"
#ifdef WIN32
#include <conio.h>
#include "qem.h"
#endif

extern AtomTable *atoms;
extern IOManager *iom;
extern Scheduler *scheduler;

//
// Maximum sizes:
//
static const	word32	ASCII_SIZE 	= 256;
static const	wordlong	MAX_LONG 	= (1ULL << (BITS_PER_WORD-1)) - 1;	// max long
static const	wordlong	MAX_LONG_LIMIT	= MAX_LONG / 10;
static const	word32	MAX_DIGIT_LIMIT	= MAX_LONG % 10;

//
// Special characters:
//
static const	signed char	EOLCOM		= '%';	// end-of-line comment
static const	signed char	BEGCOM		= '/';	// comment start
static const	signed char	ASTCOM		= '*';	// comment
static const	signed char	ENDCOM		= BEGCOM;// comment end
static const	signed char	QUOTE		= '\'';	// quote
static const	signed char	DOUBLE_QUOTE	= '"';	// double quote
static const	signed char	ESCAPE		= '\\';	// string escape character
static const	signed char	TERMIN		= '.';	// clause terminator
static const	signed char	U_SCORE		= '_';	// underscore
static const	signed char	BANG		= '!';	// quotes object_variables and quants

//
// Token types:
//
static const	int32	ERROR_TOKEN	= 0;	// error
static const	int32	SPECIAL_TOKEN	= 1;	// puncuation
static const	int32	VAR_TOKEN	= 2;	// variable 
static const	int32	NUMBER_TOKEN	= 3;	// number 
static const	int32	ATOM_TOKEN	= 4;	// atom or object variable
static const	int32	ENDCL_TOKEN	= 5;	// end of clause
static const	int32	USCORE_TOKEN	= 6;	// '_' 
static const	int32	ATOM_ONLY_TOKEN	= 7;	// ; ! quoted atom 
static const	int32	EOF_TOKEN	= 8;	// end of file
static const	int32	STRING_TOKEN	= 9;	// string 
static const	int32	OBJECT_VARIABLE_TOKEN	=10;	// LOWER8 implicit object_variable
static const	int32	OBJECT_VARIABLE_ESC_TOKEN	=11;	// !
static const	int32	QUANT_ESC_TOKEN	=12;	// !!
static const	int32	NEWLINE_TOKEN	=13;	// newlines
static const	int32	DOUBLE_TOKEN	=14;	// double 

//
// Error code:
//
static const	int32	RECEIVE_SIGNAL	= 0;	// Receive a signal
static const	int32	EOF_IN_QUOTE	= 1;	// EOF appears in quoted term
static const	int32	BAD_CHAR_CODE	= 2;	// unexpected character
static const	int32	INT_OVERFLOW	= 3;	// integer overflow
static const	int32	BAD_RADIX	= 4;	// radix is bigger than 36
static const	int32	TOO_LONG	= 5;	// token too long
static const	int32	EOF_IN_COMMENT	= 6;	// EOF appears in comment

//
// Character classifications:
//
static const	int8	DIGIT		= 1;	// 0 .. 9 
static const	int8	UPPER		= 2;	// A .. Z _
static const	int8	LOWER8		= 3;	// 8 bit a .. z
static const	int8	LOWER		= 4;	// a .. z 
static const	int8	SIGN		= 5;	// -/+*<=>#@$\^&~`:.? 
static const	int8	NOBLE		= 6;	// ;
static const	int8	PUNCT		= 7;	// (),[]|{}%
static const	int8	ATMQT		= 8;	// '
static const	int8	LISQT		= 9;	// "
static const	int8	SPACE		= 10;	// spaces
static const	int8	EOFCH		= 11;	// end of file 
static const	int8	BANGS		= 12;	// extra quote characters

//
// Classify each character.
//
const	int8	ChType[ASCII_SIZE + 1] =
  {
    EOFCH,                  // really the -1th element of the table: 
    //  ^@      ^A      ^B      ^C      ^D      ^E      ^F      ^G      
    SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,
    //  ^H      ^I      ^J      ^K      ^L      ^M      ^N      ^O      
    SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,
    //  ^P      ^Q      ^R      ^S      ^T      ^U      ^V      ^W      
    SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,
    //  ^X      ^Y      ^Z      ^[      ^\      ^]      ^^      ^_      
    SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE, 
    //  sp      !       "       #       $       %       &       '       
    SPACE,  BANGS,  LISQT,  SIGN,   SIGN,   PUNCT,  SIGN,   ATMQT,
    //  (       )       *       +       ,       -       .       /       
    PUNCT,  PUNCT,  SIGN,   SIGN,   PUNCT,  SIGN,   SIGN,   SIGN,
    //  0       1       2       3       4       5       6       7       
    DIGIT,  DIGIT,  DIGIT,  DIGIT,  DIGIT,  DIGIT,  DIGIT,  DIGIT,
    //  8       9       :       ;       <       =       >       ?       
    DIGIT,  DIGIT,  SIGN,   NOBLE,  SIGN,   SIGN,   SIGN,   SIGN,
    //  @       A       B       C       D       E       F       G       
    SIGN,   UPPER,  UPPER,  UPPER,  UPPER,  UPPER,  UPPER,  UPPER,
    //  H       I       J       K       L       M       N       O       
    UPPER,  UPPER,  UPPER,  UPPER,  UPPER,  UPPER,  UPPER,  UPPER,
    //  P       Q       R       S       T       U       V       W       
    UPPER,  UPPER,  UPPER,  UPPER,  UPPER,  UPPER,  UPPER,  UPPER,
    //  X       Y       Z       [       \       ]       ^       _       
    UPPER,  UPPER,  UPPER,  PUNCT,  SIGN,   PUNCT,  SIGN,   UPPER,
    //  `       a       b       c       d       e       f       g       
    SIGN,   LOWER,  LOWER,  LOWER,  LOWER,  LOWER,  LOWER,  LOWER,
    //  h       i       j       k       l       m       n       o       
    LOWER,  LOWER,  LOWER,  LOWER,  LOWER,  LOWER,  LOWER,  LOWER,
    //  p       q       r       s       t       u       v       w       
    LOWER,  LOWER,  LOWER,  LOWER,  LOWER,  LOWER,  LOWER,  LOWER,
    //  x       y       z       {       |       }       ~       ^?      
    LOWER,  LOWER,  LOWER,  PUNCT,  SIGN,  PUNCT,  SIGN,   SPACE,
    //  128     129     130     131     132     133     134     135     
    SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,
    //   136     137     138     139     140     141     142     143     
    SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,
    //   144     145     146     147     148     149     150     151     
    SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,
    //   152     153     154     155     156     157     158     159     
    SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,  SPACE,
    //   NBSP    !-inv   cents   pounds  ching   yen     brobar  section 
    SPACE,  SIGN,   SIGN,   SIGN,   SIGN,   SIGN,   SIGN,   SIGN,
    //   "accent copyr   -a ord  <<      nothook SHY     (reg)   ovbar   
    SIGN,   SIGN,   LOWER,  SIGN,   SIGN,   SIGN,   SIGN,   SIGN,
    //   degrees +/-     super 2 super 3 -       micron  pilcrow -       
    SIGN,   SIGN,   LOWER,  LOWER,  SIGN,   SIGN,   SIGN,   SIGN,
    //   ,       super 1 -o ord  >>      1/4     1/2     3/4     ?-inv   
    SIGN,   LOWER,  LOWER,  SIGN,   SIGN,   SIGN,   SIGN,   SIGN,
    //   `A      'A      ^A      ~A      "A      oA      AE      ,C      
    UPPER,  UPPER,  UPPER,  UPPER,  UPPER,  UPPER,  UPPER,  UPPER, 
    //   `E      'E      ^E      "E      `I      'I      ^I      "I      
    UPPER,  UPPER,  UPPER,  UPPER,  UPPER,  UPPER,  UPPER,  UPPER, 
    //   ETH     ~N      `O      'O      ^O      ~O      "O      x times 
    UPPER,  UPPER,  UPPER,  UPPER,  UPPER,  UPPER,  UPPER,  UPPER, 
    //   /O      `U      'U      ^U      "U      'Y      THORN   ,B      
    UPPER,  UPPER,  UPPER,  UPPER,  UPPER,  UPPER,  UPPER,  LOWER,
    //   `a      'a      ^a      ~a      "a      oa      ae      ,c      
    LOWER,  LOWER8, LOWER8, LOWER8, LOWER8,  LOWER8, LOWER8, LOWER8,
    //   `e      'e      ^e      "e      `i      'i      ^i      "i      
    LOWER8, LOWER8, LOWER8, LOWER8, LOWER8, LOWER8, LOWER8, LOWER8,
    //   eth     ~n      `o      'o      ^o      ~o      "o      -:-     
    LOWER8, LOWER8, LOWER8, LOWER8, LOWER8, LOWER8, LOWER8, LOWER8,
    //   /o      `u      'u      ^u      "u      'y      thorn  "y       
    LOWER8, LOWER8, LOWER8, LOWER,  LOWER,  LOWER,  LOWER,  LOWER
  };


//
// Convert a character to a digital value.
//
static const int32 DigitVal[ASCII_SIZE + 1] =
  {
    //
    // This table helps to recognise digit numbers (including 
    // hexadecimal digits). That is Each symbol, other than '0'..'9'and 
    // 'A' .. 'E' and 'a'..'e', is associated with the number 99. 
    //
    99,                     // really the -1th element of the table 
    //  ^@      ^A      ^B      ^C      ^D      ^E      ^F      ^G      
    99,     99,     99,     99,     99,     99,     99,     99,
    //  ^H      ^I      ^J      ^K      ^L      ^M      ^N      ^O      
    99,     99,     99,     99,     99,     99,     99,     99,
    //  ^P      ^Q      ^R      ^S      ^T      ^U      ^V      ^W      
    99,     99,     99,     99,     99,     99,     99,     99,
    //  ^X      ^Y      ^Z      ^[      ^\      ^]      ^^      ^_      
    99,     99,     99,     99,     99,     99,     99,     99,
    //  sp      !       "       #       $       %       &       '       
    99,     99,     99,     99,     99,     99,     99,     99,
    //  (       )       *       +       ,       -       .       /       
    99,     99,     99,     99,     99,     99,     99,     99,
    //  0       1       2       3       4       5       6       7       
    0,      1,      2,      3,      4,      5,      6,      7,
    //  8       9       :       ;       <       =       >       ?       
    8,      9,      99,     99,     99,     99,     99,     99,
    //  @       A       B       C       D       E       F       G       
    99,     10,     11,     12,     13,     14,     15,     16,
    //  H       I       J       K       L       M       N       O       
    17,     18,     19,     20,     21,     22,     23,     24,
    //  P       Q       R       S       T       U       V       W       
    25,     26,     27,     28,     29,     30,     31,     32,
    //  X       Y       Z       [       \       ]       ^       _       
    33,     34,     35,     99,     99,     99,     99,     99,
    //  `       a       b       c       d       e       f       g       
    99,     10,     11,     12,     13,     14,     15,     16,
    //  h       i       j       k       l       m       n       o       
    17,     18,     19,     20,     21,     22,     23,     24,
    //  p       q       r       s       t       u       v       w       
    25,     26,     27,     28,     29,     30,     31,     32,
    //  x       y       z       {       |       }       ~       ^?      
    33,     34,     35,     99,     99,     99,     99,     99,
    //  128     129     130     131     132     133     134     135     
    99,     99,     99,     99,     99,     99,     99,     99,
    //  136     137     138     139     140     141     142     143     
    99,     99,     99,     99,     99,     99,     99,     99,
    //  144     145     146     147     148     149     150     151     
    99,     99,     99,     99,     99,     99,     99,     99,
    //  152     153     154     155     156     157     158     159     
    99,     99,     99,     99,     99,     99,     99,     99,
    //  160     161     162     163     164     165     166     167     
    99,     99,     99,     99,     99,     99,     99,     99,
    //  168     169     170(-a) 171     172     173     174     175     
    99,     99,     99,     99,     99,     99,     99,     99,
    //  176     177     178(2)  179(3)  180     181     182     183     
    99,     99,     2,      3,      99,     99,     99,     99,
    //  184     185(1)  186(-o) 187     188     189     190     191     
    99,     1,      99,     99,     99,     99,     99,     99,
    //  192     193     194     195     196     197     198     199     
    99,     99,     99,     99,     99,     99,     99,     99,
    //  200     201     202     203     204     205     206     207     
    99,     99,     99,     99,     99,     99,     99,     99,
    //  208     209     210     211     212     213     214     215     
    99,     99,     99,     99,     99,     99,     99,     99,
    //  216     217     218     219     220     221     222     223     
    99,     99,     99,     99,     99,     99,     99,     99,
    //  224     225     226     227     228     229     230     231     
    99,     99,     99,     99,     99,     99,     99,     99,
    //  232     233     234     235     236     237     238     239     
    99,     99,     99,     99,     99,     99,     99,     99,
    //  240     241     242     243     244     245     246     247     
    99,     99,     99,     99,     99,     99,     99,     99,
    //  248     249     250     251     252     253     254     255     
    99,     99,     99,     99,     99,     99,     99,     99
  };

//
// Look up the classification of a character.
//
inline int8
Thread::InType(const signed char c)
{
  if (c+1 < 0)
    return((ChType + 257)[c]);
  else
    return((ChType + 1)[c]);
}

//
// Look up the digital value of a character.
//
inline int32 
Thread::DigVal(const signed char c)  
{
  if (c+1 < 0)
    return((DigitVal + 257)[c]);
  else
    return((DigitVal + 1)[c]);
}

//
// true if it is a space.
// 
inline bool
Thread::IsLayout(const signed char c)
{
  return(InType(c) == SPACE);
}
 
// 
// Output messages for detected syntax errors. 
//
inline void 
Thread::SyntaxError(qint64& Integer, const int32 err)
{
  Integer = err;
}

//
// Get a character.
//
inline int
Thread::Get(QPStream *InStrm)
{
  int c;
  c = InStrm->get();
  
  if (c == '\n')
    {
      InStrm->newline();
    }

  return(c);
}

//
// Put back a character or clear EOF.
//
inline void
Thread::Putback(QPStream *InStrm, const int c)
{
  if (c == EOF)
    {
      InStrm->clear();
    }
  else
    {
      if (c == '\n')
	{
	  InStrm->unline();
	}
      InStrm->unget();
    }
}

//
// Recover from a numeric error.
//
inline void
Thread::RecoverNumber(QPStream *InStrm, const int32 base)
{
  int c = Get(InStrm);

  while (DigVal(c) < base)
    {
      c = Get(InStrm);
    }
  Putback(InStrm, c);
}

//
// Recover from a name that is too long.
//
inline void
Thread::RecoverName(QPStream *InStrm)
{
  int c = Get(InStrm);

  while (InType(c) <= LOWER)
    {
      c = Get(InStrm);
    }
  Putback(InStrm, c);
}

//
// Recover from a quoted name.
//
inline void
Thread::RecoverQuotedName(QPStream *InStrm, const bool put)
{
  int c = Get(InStrm);

  while (c != QUOTE)
    {
      c = Get(InStrm);
    }
  if (put)
    {
      Putback(InStrm, c);
    }
  else if (c == EOF)
    {
      InStrm->clear();
    }
}

//
// ReadCharacter(Stream *InStrm, int8 q)
// Reads one character from a quoted atom or list.
// Two adjacent quotes are read as a single character, otherwise a quote is
// returned as 0.  Error is returned as -1.  If the input syntax has character
// escapes, they are processed.
// \xhh sequences are two hexadecimal digits long.
// Note that the \c sequence allows continuation of strings.  For example:
//     "This is a string, which \c
//      has to be continued over \c
//      several lines.\n".
//
int32
Thread::ReadCharacter(QPStream *InStrm, const signed char q, qint64& Integer)
{
  int c = Get(InStrm);

 BACK:
  if (c == EOF) 
    {
    DOERR:
      assert(q == QUOTE || q == DOUBLE_QUOTE);
      
      InStrm->clear();
      SyntaxError(Integer, EOF_IN_QUOTE);
      return(-1);
    }
  if (c == q) 
    {	
      //
      // Two adjacent quotes are read as a single character,
      // otherwise a quote is returned as 0.
      //
      c = Get(InStrm);

      if (c == q)
	{
	  return(c);
	}
      else
	{
	  Putback(InStrm, c);
	  return(0);
	}
    } 
  if (c != ESCAPE)
    {
      return(c);
    }
  // 
  // If we get here, we have read the "\" of an escape sequence.  
  //
  c = Get(InStrm);

  switch (c) 
    {
    case EOF:
      InStrm->clear();
      goto DOERR; 	     // Syntax error	
      break;
      
    case 'a':  
    case 'A':	// alarm 
      return('\a');
      break;
      
    case 'b':  
    case 'B':	// backspace 
      return('\b');
      break;
      
    case 'f':  
    case 'F':	// formfeed 
      return('\f');
      break;
      
    case 'n': 
    case 'N':	// newline 
      return('\n');
      break;
      
    case 'r':  
    case 'R':	// return 
      return('\r');
      break;
      
    case 's':  
    case 'S':	// space 
      return(' ');
      break;

    case 't':  
    case 'T':	// tab 
      return('\t');
      break;
      
    case 'v':  
    case 'V':	// vertical tab 
      return('\v');
      break;
      
    case '^':	// control 
      c = Get(InStrm);

      if (c == EOF)
	{
	  goto DOERR;  // Syntax error
	}
      return(((c == '?') ? (127) : (c & 31)));
      break;

    case 'c':  
    case 'C':	// continuation 
      c = Get(InStrm);

      while (IsLayout(c)) 
	{
	  c = Get(InStrm);
	}
      goto BACK;    	     // read the rest of a string
      break;
      
    case 'x':  
    case 'X':	// hexadecimal \xhh 
      {  	
	int32	n = 0, i = 2, digit;
	
	do
	  {
	    c = Get(InStrm);

	    digit = DigVal(c);
	    if (digit < 16)
	      {
		n = 16 * n + digit;
	      }
	    else
	      {
		if (c == EOF)
		  {
		    goto DOERR;
		  }
		RecoverQuotedName(InStrm, false);
		SyntaxError(Integer, BAD_CHAR_CODE); 
		return(-1);
	      }
	  } while (--i > 0);
	return (n);
      }
      break;
      
    case 'o':  
    case 'O':	// octal \odd or \Odd. here d is a digit < 8
      c = Get(InStrm);
      //
      // Drop through to the following case for parsing.
      //
    case '0':  
    case '1':  
    case '2':  
    case '3':
    case '4':  
    case '5':  
    case '6':  
    case '7':	// octal \dd or a format of the above. 
      {  	
	int32	n = 0, i = 2, digit;
	
	while (true)
	  {
	    digit = DigVal(c);
	    if (digit < 8)
	      {
		n = 8 * n + digit;
	      }
	    else
	      {
		if (c == EOF)
		  {
		    goto DOERR;
		  }
		RecoverQuotedName(InStrm, false);
		SyntaxError(Integer, BAD_CHAR_CODE); 
		return(-1);
	      }
	    
	    if (--i == 0)
	      {
		return(n);
	      }
	    else
	      {
		c = Get(InStrm);
	      }
	  }
      }
      break;
      
    default:
      if (! IsLayout(c)) 
	{
	  return(c);
	}
      else
	{
	  c = Get(InStrm);

	  goto BACK;
	}
    }
} 

int32 Thread::base_num(QPStream *InStrm, qint64& Integer, int base)
{
  Integer = 0;
  qint64 BaseMax = MAX_LONG / base;
  qint64 BaseDigit = MAX_LONG % base;
  int c = Get(InStrm);
  int digit = DigVal(c);
  while (digit < base)
    {
      if ((Integer > BaseMax) || 
          ((Integer == BaseMax) &&
           digit > BaseDigit))
        {
          RecoverNumber(InStrm, base);
          SyntaxError(Integer, INT_OVERFLOW);
          return(ERROR_TOKEN);
        }
      Integer = base * Integer + digit;
      c = Get(InStrm);
      digit = DigVal(c);
    }
  if (digit != 99) 
    {
      RecoverNumber(InStrm, base);
      SyntaxError(Integer, INT_OVERFLOW);
      return(ERROR_TOKEN);
    }
  Putback(InStrm, c);
  return(NUMBER_TOKEN); 

}

int32 Thread::get_number_token(QPStream *InStrm, char c, qint64& Integer, double& Double)
{
  int32		digit, base; 
  qint64 BaseMax, BaseDigit;
  char          number[128];
  char*          numptr;

      Integer = 0;
      while (InType(c) == DIGIT)
	{
	  digit = DigVal(c);
	  if ((Integer > (qint64) MAX_LONG_LIMIT) ||
	      (Integer == (qint64) MAX_LONG_LIMIT && digit > (qint64) MAX_DIGIT_LIMIT))
	    {
	      RecoverNumber(InStrm, 10);

	      if ((c = Get(InStrm)) != QUOTE)
		{
		  Putback(InStrm, c);
		}
	      else if ((c = Get(InStrm)) != QUOTE)
		{
		  Putback(InStrm, c);
		}
	      SyntaxError(Integer, INT_OVERFLOW);
	      return(ERROR_TOKEN);
	    }
	  Integer = 10 * Integer + digit;
	  c = Get(InStrm);
	}
      
      if (c == TERMIN)
        {
          stringstream out;
          out << Integer;
          strcpy(number, out.str().c_str()); 
	  //sprintf(number, "%lld", Integer);
	  size_t len = strlen(number);
	  numptr = number + len;
	  *numptr++ = c;
	  c = Get(InStrm);
	  if (InType(c) != DIGIT)
	    {
	      Putback(InStrm, c);
	      Putback(InStrm, TERMIN);
	      return(NUMBER_TOKEN); 
	    }
	  while (InType(c) == DIGIT)
	    {
	      *numptr++ = c;
	      c = Get(InStrm);
	    }
	  if (c == 'e')
	    {
	      *numptr++ = c;
	      c = Get(InStrm);
	      if ((c == '-') || (c == '+'))
		{
		  *numptr++ = c;
		  c = Get(InStrm);
		}
              while (InType(c) == DIGIT)
		{
		  *numptr++ = c;
		  c = Get(InStrm);
		}
	    }
	  *numptr = '\0';
	  Putback(InStrm, c);
	  sscanf(number, "%lf" , &Double);
	  return(DOUBLE_TOKEN);
        }
      if (c == 'e')
        {
          stringstream out;
          out << Integer;
          strcpy(number, out.str().c_str()); 
	  //sprintf(number, "%lld", Integer);
	  size_t len = strlen(number);
	  numptr = number + len;
	  *numptr++ = c;
	  c = Get(InStrm);
	  if ((c == '-') || (c == '+'))
	    {
	      *numptr++ = c;
	      c = Get(InStrm);
	    }
	  while (InType(c) == DIGIT)
	    {
	      *numptr++ = c;
	      c = Get(InStrm);
	    }
	  *numptr = '\0';
	  Putback(InStrm, c);
	  sscanf(number, "%lf" , &Double);
	  return(DOUBLE_TOKEN);
        }
      if (c == QUOTE)  
	{
	  //
	  // Calculate integer with explicit base.
	  //
	  base = Integer;
	  
          if (base > 36)
	    {
	      SyntaxError(Integer, BAD_RADIX);
	      return(ERROR_TOKEN);
	    }
	  else
	    {
	      Integer = 0;
	      BaseMax = MAX_LONG / base;
	      BaseDigit = MAX_LONG % base;
	      c = Get(InStrm);
	      digit = DigVal(c);
	      while (digit < base)
		{
		  if ((Integer > BaseMax) || 
		      ((Integer == BaseMax) &&
		       digit > BaseDigit))
		    {
		      RecoverNumber(InStrm, base);
		      SyntaxError(Integer, INT_OVERFLOW);
		      return(ERROR_TOKEN);
		    }
		  Integer = base * Integer + digit;
		  c = Get(InStrm);
		  digit = DigVal(c);
		}
	      if (digit != 99) 
		{
		  RecoverNumber(InStrm, base);
		  SyntaxError(Integer, INT_OVERFLOW);
		  return(ERROR_TOKEN);
		}
 
	    }
	}
      Putback(InStrm, c);
      return(NUMBER_TOKEN); 
}

//
// GetToken() reads a single token from the input stream and returns the
// token type.  The value of the token is stored in one of the
// variables: Integer, Simple, String.
//
int32
Thread::GetToken(QPStream *InStrm, qint64& Integer, double& Double, char *Simple, Object*& String)
{
  int32		digit, base, n, i;
  qint64 BaseMax, BaseDigit;
  int d, e;
  char		*s = Simple;
  char          number[128];
  char*          numptr;
  bool		flag; 
  
  int c = Get(InStrm);

 START:
  switch (InType(c)) 
    {
    case DIGIT: 
      //
      // The only cases considered are listed as follows.
      // 1. positive decimal integers: a string of decimal digits. 
      // 2. positive based integers: base'number.
      //
      if (DigVal(c) == 0)
        {
          c  = Get(InStrm);
          if (c == 'b')
            {
              return base_num(InStrm, Integer, 2);
            }
          else if (c == 'o')
            {
              return base_num(InStrm, Integer, 8);
            }
          else if (c == 'x')
            {
              return base_num(InStrm, Integer, 16);
            }
          else if (c =='\'')
	    {
	      //
	      // 0'c is a charater code.
	      //
	      n = ReadCharacter(InStrm, QUOTE, Integer);
	      
	      if (n == -1)
		{
		  return(ERROR_TOKEN);
		}
	      else
		{
		  Integer = ((n == 0) ? QUOTE : (n));
		  return(NUMBER_TOKEN);
		}
	    }
        } 
      return get_number_token(InStrm, c, Integer, Double); 
      break;
      
    case UPPER:
      n = ATOM_LENGTH - 1;
      do 
	{
	  //
	  // The maximum length for a variable name is ATOM_LENGTH.
	  //
	  if (n-- == 0)  
	    { 
	      RecoverName(InStrm);
	      SyntaxError(Integer, TOO_LONG);
	      return(ERROR_TOKEN);
	    }
	  *s++ = c;
	  c = Get(InStrm);
	} while (InType(c) <= LOWER);
      *s = '\0';
      Putback(InStrm, c);
      
      if (Simple[0] == U_SCORE && Simple[1] == '\0')
	{
	  return(USCORE_TOKEN);
	}
      else
	{
	  return(VAR_TOKEN);
	}
      break;
      
    case LOWER8:
      n = ATOM_LENGTH - 1;
      do 
	{
	  //
	  // The maximum length for an atom is ATOM_LENGTH.
	  //
	  if (n-- == 0)  
	    { 
	      RecoverName(InStrm);
	      SyntaxError(Integer, TOO_LONG);
	      return(ERROR_TOKEN);
	    }
	  *s++ = c;
	  c = Get(InStrm);
	} while (InType(c) <= LOWER);
      *s = '\0';
      Putback(InStrm, c);
      return(OBJECT_VARIABLE_TOKEN);
      break;
      
    case LOWER:
      n = ATOM_LENGTH - 1;
      do 
	{
	  //
	  // The maximum length for an atom is ATOM_LENGTH.
	  //
	  if (n-- == 0)  
	    { 
	      RecoverName(InStrm);
	      SyntaxError(Integer, TOO_LONG);
	      return(ERROR_TOKEN);
	    }
	  *s++ = c;
	  c = Get(InStrm);
	} while (InType(c) <= LOWER);
      *s = '\0';
      Putback(InStrm, c);
      return(ATOM_TOKEN);
      break;
      
    case SIGN:
      *s = c;
      n = ATOM_LENGTH - 2;
      d = Get(InStrm);
      // if ((c == '-') && (InType(d) == DIGIT))
      //   {
      //     int32 retval = get_number_token(InStrm, d, Integer, Double);
      //     if (retval == NUMBER_TOKEN)
      //       { 
      //         Integer = -Integer;
      //       }
      //     else if (retval == DOUBLE_TOKEN)
      //       {
      //         Double = -Double;
      //       }
      //     return retval;
      //   }
      // if ((c == '+') && (InType(d) == DIGIT))
      //   {
      //     return get_number_token(InStrm, d, Integer, Double);
      //   }

      if (c == BEGCOM && d == ASTCOM) 
	{
	  //
	  // Consume /* */ comments.
	  //
	  flag = false;
	  //do
          while (d >= 0)
	    {
	      d = Get(InStrm);
	      if (flag && d == ENDCOM)
		{
		  break;
		}
	      flag = (d == ASTCOM);
	    } // while (d >= 0);
	  if (d == EOF)
	    {
	      InStrm->clear();
	      SyntaxError(Integer, EOF_IN_COMMENT);
	      return(ERROR_TOKEN);
	    }
	  
	  c = Get(InStrm);
	  goto START;
	} 
      
      //
      // a token could be a string of signs and may also include '|'.
      //
      while ((InType(d) == SIGN) || (d == '|')) 
	{
	  if (n-- == 0)
	    {
	      d = Get(InStrm);
	      while ((InType(d) == SIGN) || (d == '|'))
		{
		  d = Get(InStrm);
		}
	      Putback(InStrm, d);
	      SyntaxError(Integer, TOO_LONG);
	      return(ERROR_TOKEN);
	    }
	  *++s = d;
	  d = Get(InStrm);
	}
      *++s = '\0';
      if (InType(d) >= SPACE &&
	  Simple[0] == TERMIN && Simple[1] == '\0') 
	{
	  return(ENDCL_TOKEN);
	}
      Putback(InStrm, d);
      return(ATOM_TOKEN);
      break;
      
    case NOBLE:
      Simple[0] = c;
      Simple[1] = '\0';
      return(ATOM_ONLY_TOKEN);
      break;
      
    case PUNCT:
      if (c == EOLCOM)
	{
	  do
	    {
	      c = Get(InStrm);
	    } while(c != EOF && c != '\n');
	  
	  if (c != EOF)
	    {
	      c = Get(InStrm);
	    }
	  goto START;
	}
      *s++ = c;
      d = Get(InStrm);
      if ((c == '|') && ((InType(d) == SIGN) || (d == '|')))
	{
	  n = ATOM_LENGTH - 2;
	  //
	  // a token could be a '|' followed by a string of signs 
          // and may also include '|'.
	  //
	  while ((InType(d) == SIGN) || (d == '|')) 
	    {
	      if (n-- == 0)
		{
		  d = Get(InStrm);
		  while ((InType(d) == SIGN) || (d == '|'))
		    {
		      d = Get(InStrm);
		    }
		  Putback(InStrm, d);
		  SyntaxError(Integer, TOO_LONG);
		  return(ERROR_TOKEN);
		}
	      *s++ = d;
	      d = Get(InStrm);
	    }
	  *s = '\0';
	  if (InType(d) >= SPACE &&
	      Simple[0] == TERMIN && Simple[1] == '\0') 
	    {
	      return(ENDCL_TOKEN);
	    }
	  Putback(InStrm, d);
	  return(ATOM_TOKEN);
	}
      Putback(InStrm, d);
      *s = '\0';
      return(SPECIAL_TOKEN);
      break;
      
    case ATMQT:	// quoted atom, 'atom'
      n = ATOM_LENGTH - 1;
      i = ReadCharacter(InStrm, QUOTE, Integer);
      while (i > 0) 
	{
	  if (n-- == 0) 
	    {
	      *s = '\0';
	      RecoverQuotedName(InStrm, false);
	      SyntaxError(Integer, TOO_LONG);
	      return(ERROR_TOKEN);
	    }
	  else
	    {
	      *s++ = static_cast<char>(i);
	    }
	  i = ReadCharacter(InStrm, QUOTE, Integer);
	}
      if (i == -1)
	{
	  return(ERROR_TOKEN);
	}
      else
	{
	  *s = '\0';
	  return(ATOM_ONLY_TOKEN);
	}
      break;
      
    case LISQT:	// quoted list
      {
	string str;
	i = ReadCharacter(InStrm, DOUBLE_QUOTE, Integer);
	while (i > 0)
	  {
	    str.push_back((char)i);
	    i = ReadCharacter(InStrm, DOUBLE_QUOTE, Integer);
	  }
	if (i == -1)
	  {
	    return(ERROR_TOKEN);
	  }
	else
	  {
	    //if (*(str.c_str()) == '\0')
            //   String = AtomTable::nil;
            // else
	      String = heap.newStringObject(str.c_str());
	    return(STRING_TOKEN);
	  }
      break;
      }
      
    case SPACE:
      while ((InType(c) == SPACE) && (c != '\n'))
	{
	  c = Get(InStrm);
	} 
      
      if (c == '(')
	{
	  Simple[0] = ' ';
	  Simple[1] = '(';
	  Simple[2] = '\0';
	  return(SPECIAL_TOKEN);
	}
      else if (c == '\n')
	{
	  return(NEWLINE_TOKEN);
	}
      else
	{
	  goto START;	// start a new token
	}
      break;
      
    case BANGS:	// !: Could be a quoted quantifier, a quoted object_variable
      //    or just a `cut'
      d = Get(InStrm);
      
      if (d == BANG) {		// !!q
	e = Get(InStrm);
	Putback(InStrm, e);
	
	if (IsLayout(e) ||
	    (SIGN <= InType(d) && InType(d) <= PUNCT)) {
	  Simple[0] = c;
	  Simple[1] = d;
	  Simple[2] = '\0';
	  return(ATOM_ONLY_TOKEN);
	} else {
	  return(QUANT_ESC_TOKEN);
	}
      } else if (IsLayout(d) ||
		 (SIGN <= InType(d) && InType(d) <= PUNCT)) {
	Putback(InStrm, d);
	Simple[0] = c;
	Simple[1] = '\0';
	return(ATOM_ONLY_TOKEN);
      } else {
	Putback(InStrm, d);
	return(OBJECT_VARIABLE_ESC_TOKEN);
      }
      break;
      
    case EOFCH:
      InStrm->clear();
      return(EOF_TOKEN);
      break;
      
    default:
      assert(false);
      break;
    }
  return(EOF_TOKEN);
}

//
// psi_read_next_token(stream, var, var)
//
// Read a token from the stream and return the token type and value.
//
Thread::ReturnValue
Thread::psi_read_next_token(Object *& stream_arg, Object *& type_arg, Object *& value_arg)
{
  Object* argS = heap.dereference(stream_arg);

  QPStream *stream;
  DECODE_STREAM_INPUT_ARG(heap, *iom, argS, 1, stream);

  IS_READY_STREAM(stream);

  errno = 0;

  qint64	Integer;
  Object* String;
  double Double;
	
  int32 i = GetToken(stream, Integer, Double, atom_buf1, String);

  if (errno == EINTR)
    {
      SyntaxError(Integer, RECEIVE_SIGNAL);
      i = ERROR_TOKEN;
    }

  switch (i) 
    {
    case ERROR_TOKEN:
    case NUMBER_TOKEN:
      value_arg = heap.newInteger(Integer);
      break;
    case DOUBLE_TOKEN:
      value_arg = heap.newDouble(Double);
      break;
      
    case USCORE_TOKEN:
    case VAR_TOKEN:
    case ATOM_TOKEN:
    case ENDCL_TOKEN:
    case ATOM_ONLY_TOKEN:
    case SPECIAL_TOKEN:
    case OBJECT_VARIABLE_TOKEN:
      value_arg = atoms->add(atom_buf1);
      break;
      
    case OBJECT_VARIABLE_ESC_TOKEN:
    case QUANT_ESC_TOKEN:
    case NEWLINE_TOKEN:
      value_arg = heap.newInteger(0);
      break;
      
    case STRING_TOKEN:
      value_arg = String;
      break;
      
    case EOF_TOKEN:
      value_arg = heap.newInteger(0);
      break;
      
    default:
      assert(false); 
    }
  
  type_arg = heap.newInteger(i); 

  return RV_SUCCESS;
}











