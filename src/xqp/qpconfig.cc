/***************************************************************************
                          qpconfig.cc  -  configuration
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

// $Id: qpconfig.cc,v 1.1 2004/05/09 23:51:08 qp Exp $

#include "qpconfig.h"
#include <iostream>
#include "xqp.h"

using namespace std;

QPConfig::QPConfig(Xqp* xe) 
  : QSettings(),
    parent(xe),
    default_font("Lucidatypewriter", 12, QFont::Normal),
    default_color(QColor("white"))
{

   QString sf =  default_font.toString();
   QString fontstring = value("/Xqp/font", sf).toString();
   font.fromString(fontstring);
   QString def_cname = default_color.name();
   QString cname = value("/Xqp/color", def_cname).toString();
   color = QColor(cname);
   x = value("/Xqp/x", 0).toInt();
   y = value("/Xqp/y", 0).toInt();
   width = value("/Xqp/width", 800).toInt();
   height = value("/Xqp/height", 800).toInt();
}

QPConfig::~QPConfig()
{
   setValue("/Xqp/font", font.toString());
   setValue("/Xqp/color", color.name());
   setValue("/Xqp/x",parent-> x());
   setValue("/Xqp/y", parent->y());
   setValue("/Xqp/width", parent->width());
   setValue("/Xqp/height", parent->height());
}

void QPConfig::setQPFont(const QFont& f)
{
      font = f;
}

void QPConfig::setQPColor(const QColor& c)
{
      color = c;
}
