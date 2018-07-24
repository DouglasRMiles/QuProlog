/***************************************************************************
                          qthelp.h  -  XQP help widget
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

// $Id: qthelp.h,v 1.1 2004/05/09 23:51:09 qp Exp $

#ifndef QTHELP_H
#define QTHELP_H

#include <qwidget.h>
#include <qmainwindow.h>
#include <qtextedit.h>


class QTHelp : public QMainWindow
{
  Q_OBJECT
    public:
  QTHelp(QWidget *parent);
  ~QTHelp();
  
public slots:
  
 signals:

 private:
  QTextEdit* help;
  QWidget* parent;
  
 protected:

};

#endif // QT_HELP
