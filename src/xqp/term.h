/***************************************************************************
                          term.h  -  testing for end of term
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

// $Id: term.h,v 1.1 2004/05/09 23:51:10 qp Exp $

#include <qstring.h>
#include <qregexp.h>
void skip_to_closing_quote(const QString, QString&, int&);
bool graphic_char(QChar);
bool end_of_term(QString&, int);
