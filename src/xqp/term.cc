/***************************************************************************
                          term.cc  -  testing for end of term
                             -------------------
    begin                : April 2004
    copyright            : (C) 2004 by Peter Robinson
    email                : pjr@itee.uq.edu.au
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

// $Id: term.cc,v 1.1 2004/05/09 23:51:10 qp Exp $

#include "term.h"

void skip_to_closing_quote(const QString pattern, 
			   QString& line, int& pos)
{
  if (line == QString::null) return;
  int n = line.indexOf(QRegExp(pattern), pos);
  if (n != -1)
    {
      pos = n+pattern.length();
    }
  else
    {
      pos = line.length();
    }
  return;
}


bool graphic_char(QChar c)
{
    switch (c.toAscii())
    {
       case '-':
       case '/':
       case '+':
       case '*':
       case '<':
       case '=':
       case '>':
       case '#':
       case '@':
       case '$':
       case '\\':
       case '^':
       case '&':
       case '~':
       case '`':
       case ':':
       case '.':
       case '?':
       case '|':
          return true;
          break;
       default:
          return false;
      }
}


bool end_of_term(QString& line, int pos)
{
   if (line == QString::null) return false;
   int n = line.indexOf(QRegExp("('|\x0022|/\\*|%|\\.\\s|\\.$)"), pos);
   if (n == -1)
     {
       return false;
     }
    if (n > pos && line.at(n) == '\'' && line.at(n-1) == '0')
     {
        pos = n + 2;
        return end_of_term(line, pos);
     }
    if (line.at(n) == '\'')
     {
        pos = n+1;
        skip_to_closing_quote("'", line, pos);
        return end_of_term(line, pos);
     }
    if (line.at(n) == '%')
     {
       skip_to_closing_quote("\n", line,pos);
       return end_of_term(line,pos);
     }
    if (line.at(n) == '"')
     {
        pos = n+1;
        skip_to_closing_quote("\x0022", line, pos);
        return end_of_term(line, pos);
     }
    if (line.at(n) == '/')
     {
        pos = n + 2;
        skip_to_closing_quote("\\*/", line,pos);
        return end_of_term(line, pos);
     }
    if (graphic_char(line.at(n-1)))
     {
        pos = n + 1;
        return end_of_term(line, pos);
     }
    return true;

}
