#include "write_support.h"
#include "defs.h"
#include "atom_table.h"

extern AtomTable* atoms;

/*
  The string is safe if the string is one of the followings:
  1.  []
  2.  {}
  3.  ;
  4.  !
  5.  abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789 .
  6.  #$&*+-./:<=>?@^~\
*/
bool
SafeAtom(const char *s, bool vbar)
{
  if (*s == '\0' ||
      streq(s, "."))
    {
      //
      // Null atom ('') or a single full stop ('.').
      //
      return(false);
    }
  else if (streq(s, "[]") ||
	   streq(s, "{}") ||
	   streq(s, ";") ||
	   streq(s, "!"))
    {
      return(true);
    }
  else if (strchr("abcdefghijklmnopqrstuvwxyz", *s) != NULL)
    {
      s++;
      while(*s != '\0')
	{
	  if (strchr("abcdefghijklmnopqrstuvwxyz"
		     "ABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789",
		     *s) !=
	      NULL)
	    {
	      //
	      // index finds the given character in the 'safe'
	      // range.  So check the next character.
	      // 
	      s++;
	    }
	  else
	    {
	      //
	      // index cannot find the character in the 'safe'
	      // range.  So it is unsafe.
	      //
	      return(false);
	    }
	}
      return(true);
    }
  else
    {
      while(*s != '\0')
	{
	  if (strchr("#$&*+-./:<=>?@^~\\|", *s) != NULL)
	    {
              // if vbar is false then a '|' is considered unsafe
              if (!vbar && (*s == '|')) {
                  return false;
                }
	      //
	      // index finds the given character in the 'safe'
	      // range.  So check the next character.
	      // 
	      s++;
	    }
	  else
	    {
	      //
	      // index cannot find the character in the 'safe'
	      // range.  So it is unsafe.
	      //
	      return(false);
	    }
	}
      return(true);
    }
}

void addEscapes(string& str, char quote)
{
  string tmp;
  for (string::iterator iter = str.begin(); iter != str.end(); iter++)
    {
      char c = *iter;
      switch ((int)c)
	{
	case 7:  // \a
	  tmp.push_back('\\');
	  tmp.push_back('a');
	  break;
	case 8:  // \b
	  tmp.push_back('\\');
	  tmp.push_back('b');
	  break;
	case 9:  // \t
	  tmp.push_back('\\');
	  tmp.push_back('t');
	  break;
	case 10:  // \n
	  tmp.push_back('\\');
	  tmp.push_back('n');
	  break;
	case 11:  // \v
	  tmp.push_back('\\');
	  tmp.push_back('v');
	  break;
	case 12:  // \f
	  tmp.push_back('\\');
	  tmp.push_back('f');
	  break;
	case 13:  // \r
	  tmp.push_back('\\');
	  tmp.push_back('r');
	  break;
        case 92:  
	  tmp.push_back('\\');
	  tmp.push_back('\\');
	  break;
	default:
          if (c == quote)
	    {
	      tmp.push_back('\\');
	      tmp.push_back(c);
	    }
	  else
            tmp.push_back(c);
	  break;
	}
    }
  str = tmp;
}

void removeEscapes(string& str, char quote)
{
  string tmp;
  for (string::iterator iter = str.begin(); iter != str.end(); iter++)
    {
      char c = *iter;
      if (c == '\\') {
	iter++;
	assert(iter != str.end());
	c = *iter;
	switch ((int)c)
	  {
	  case 'a': 
	    tmp.push_back('\a');
	    break;
	  case 'b':  
	    tmp.push_back('\b');
	    break;
	  case 't':  
	    tmp.push_back('\t');
	    break;
	  case 'n':  
	    tmp.push_back('\n');
	    break;
	  case 'v': 
	    tmp.push_back('\v');
	    break;
	  case 'f':  
	    tmp.push_back('\f');
	    tmp.push_back('f');
	    break;
	  case 'r': 
	    tmp.push_back('\r');
	    break;
	  case '\\':  
	    tmp.push_back('\\');
	    break;
	  default:
            if (c == quote)
	      {
		tmp.push_back(c);
	      }
	    else
	      {
		assert(false);
	      }
	    break;
	  }
      }
      else {
	tmp.push_back(c);
      }
    }
  str = tmp;
}

void writeAtom(ostream& strm, Object* a)
{
  assert(a->isAtom());
  string name(OBJECT_CAST(Atom*, a)->getName());
  addEscapes(name, '\'');
  if (SafeAtom(name.c_str(), true))
    {
      strm << name;
    }
  else
    {
      strm << '\'';
      strm << name;
      strm << '\'';
    }
}

void writePedroAtom(ostream& strm, Object* a)
{
  assert(a->isAtom());
  string name(OBJECT_CAST(Atom*, a)->getName());
  if (SafeAtom(name.c_str(), false))
    {
      strm << name;
    }
  else
    {
      addEscapes(name, '\'');
      strm << '\'';
      strm << name;
      strm << '\'';
    }
}
