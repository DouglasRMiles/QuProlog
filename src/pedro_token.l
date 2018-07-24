%{
#include <math.h>
#include "objects.h"
#include "heap_qp.h"
#include "name_table.h"
#include "atom_table.h"
#include "pedro_env.h"
#include "pedro_token.h"

YY_BUFFER_STATE buffstate;

void copyWithoutEscapes(char* in, char* out, int len, char quote)
{
  int pos = 0;
  int i = 0;
  while (i < len) {
      char c = in[i];
      if (c == '\\') {
	i++;
	c = in[i];
	switch ((int)c)
	  {
	  case 'a': 
	    out[pos] = '\a';
	    break;
	  case 'b':
  	    out[pos] = '\b';
	    break;
	  case 't': 
 	    out[pos] = '\t';
	    break;
	  case 'n':
  	    out[pos] = '\n';
	    break;
	  case 'v':
 	    out[pos] = '\v';
	    break;
	  case 'f':
  	    out[pos] = '\f';
            pos++;
            out[pos] = 'f';
	    break;
	  case 'r':
 	    out[pos] = '\r';
	    break;
	  case '\\': 
 	    out[pos] = '\\';
	    break;
	  default:
            if (c == quote)
	      {
	        out[pos] = c;
	      }
	    else
	      {
		assert(false);
	      }
	    break;
	  }
      }
      else {
	out[pos] = c;
      }
      i++;
      pos++;
    }
  out[pos] = '\0';
}

#define YY_DECL int scanner(Thread* th, AtomTable* atoms, VarMap* vmap, Object** val, bool remember)
%}

%option noyywrap

DIGIT [0-9]
LOWER [a-z]
UPPER [A-Z]

%%
[0-9]+"."[0-9]+("e"|"e+"|"e-")[0-9]+  { *val = th->TheHeap().newDouble(atof(yytext)); return TERM_TOKEN; }
[0-9]+"."[0-9]+("E"|"E+"|"E-")[0-9]+  { *val = th->TheHeap().newDouble(atof(yytext)); return TERM_TOKEN; }
[0-9]+("e"|"e+"|"e-")[0-9]+  { *val = th->TheHeap().newDouble(atof(yytext)); return TERM_TOKEN; }
[0-9]+("E"|"E+"|"E-")[0-9]+  { *val = th->TheHeap().newDouble(atof(yytext)); return TERM_TOKEN; }
[0-9]+"."[0-9]+  { *val = th->TheHeap().newDouble(atof(yytext)); return TERM_TOKEN; }

"-"[0-9]+"."[0-9]+("e"|"e+"|"e-")[0-9]+  {*val = th->TheHeap().newDouble(atof(yytext)); return TERM_TOKEN; }
"-"[0-9]+"."[0-9]+("E"|"E+"|"E-")[0-9]+  {*val = th->TheHeap().newDouble(atof(yytext)); return TERM_TOKEN; }
"-"[0-9]+("e"|"e+"|"e-")[0-9]+  { *val = th->TheHeap().newDouble(atof(yytext)); return TERM_TOKEN; }
"-"[0-9]+("E"|"E+"|"E-")[0-9]+  { *val = th->TheHeap().newDouble(atof(yytext)); return TERM_TOKEN; }
"-"[0-9]+"."[0-9]+  { *val = th->TheHeap().newDouble(atof(yytext)); return TERM_TOKEN; }

[0-9]+    { *val = th->TheHeap().newInteger(atoi(yytext)); return TERM_TOKEN; }
"-"[0-9]+ { *val = th->TheHeap().newInteger(atoi(yytext)); return TERM_TOKEN; }




"("        { *val = 0; return OBRA_TOKEN; }
")"        { *val = 0; return CBRA_TOKEN; }
","        { *val = 0; return COMMA_TOKEN; }
"["        { *val = 0; return OSBRA_TOKEN; }
"]"        { *val = 0; return CSBRA_TOKEN; }
"|"        { *val = 0; return VBAR_TOKEN; }


[_A-Z][A-Za-z0-9_]*  {
                      if (yytext[0] == '_') {
                        if (yytext[1] == '\0') *val = th->TheHeap().newVariable();
                        else *val = vmap->getVar(&(th->TheHeap()), atoms->add(yytext));
                      }
                      else if (remember) {
                        Atom* a = atoms->add(yytext);
                        *val = th->getNames().getVariable(a);
                        if (*val == NULL) {
                          *val = th->TheHeap().newVariable(true);
                          th->getNames().setNameNewVar(a, *val, *th);
                        }
                      }
                      else *val = vmap->getVar(&(th->TheHeap()), atoms->add(yytext));
                      return TERM_TOKEN; }

[a-z][A-Za-z0-9_]*  { *val = atoms->add(yytext); return TERM_TOKEN; }

"'"[^'\\]*("\\".[^'\\]*)*"'"  { 
                          int size = strlen(yytext);
                          char* copy = new char[size];
                          copyWithoutEscapes(yytext+1, copy, size-2, '\'');
                          *val = atoms->add(copy); 
                          delete [] copy;
                          return TERM_TOKEN; 
                         }

"\""[^\"\\]*("\\".[^\"\\]*)*"\""  { 
                          int size = strlen(yytext);
                          char* copy = new char[size];
                          copyWithoutEscapes(yytext+1, copy, size-2, '"'); /* " */
                          *val = th->TheHeap().newStringObject(copy); 
                          delete [] copy;
                          return TERM_TOKEN; }

[-/+*<=>#@$\\^&~`:.?!;]+  { *val = atoms->add(yytext); return TERM_TOKEN; }

"{}"  { *val = atoms->add(yytext); return TERM_TOKEN; }

"\n" { return NEWLINE_TOKEN; }
[ \t]+

. { return ERROR_TOKEN; } 

%%

void set_buffstate(char* buff, int size)
{
    buffstate = yy_scan_buffer(buff, size);
}

void delete_buffstate()
{
    yy_delete_buffer(buffstate);
}

/*
int
atomNeedsQuotes(const char *s)
{
  s++;
  if (strcmp(s, "'") == 0)
    {
      return(1);
    }
  else if ((strcmp(s, "[]'") == 0) ||
           (strcmp(s, ";'") == 0))
    {
      return(0);
    }
  else if (strchr("abcdefghijklmnopqrstuvwxyz", *s) != NULL)
    {
      s++;
      while(*s != '\0')
        {
          if (strchr("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789", *s) !=
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
              return (strcmp(s, "'") != 0);
            }
        }
      return(0);
    }
  else
    {
      while(*s != '\0')
        {
          if (strchr("#$&*+-./:<=>?@^~\\", *s) != NULL)
            {
              //
              // index finds the given character in the 'safe'
              // range.  So check the next character.
              // 
              s++;
            }
          else
            {
              return (strcmp(s, "'") != 0);
            }
        }
      return(0);
    }
}
*/
