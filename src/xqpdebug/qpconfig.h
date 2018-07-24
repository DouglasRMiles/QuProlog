/***************************************************************************
                          qpconfig.h  -  Configuration
                             -------------------
    begin                : April 2004
    copyright            : (C) 2oo4 by Peter Robinson
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

// $Id: qpconfig.h,v 1.1 2004/05/11 03:24:02 qp Exp $

#ifndef QPCONFIG_H
#define QPCONFIG_H


#include <qsettings.h>
#include <qfont.h>
#include <qcolor.h>

class Xqpdebug;

class QPConfig : public QSettings 
{
 public: 
  QPConfig(Xqpdebug* xe);
  ~QPConfig();

  QFont qpFont() const { return font; }
  void setQPFont(const QFont& f);
  QColor qpColor() const { return color; }
  void setQPColor(const QColor& c);
  int getX() const { return x; }
  int getY() const { return y; }
  int getWidth() const { return width; }
  int getHeight() const { return height; }

private:
   Xqpdebug* parent;
   QFont default_font;
   QFont font;
   QColor default_color;
   QColor color;
   int x;
   int y;
   int width;
   int height;
};

#endif
