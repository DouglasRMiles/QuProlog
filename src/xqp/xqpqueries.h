/***************************************************************************
                          xqpqueries.h  -  QP queries widget
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

// $Id: xqpqueries.h,v 1.1 2004/05/09 23:51:11 qp Exp $

#ifndef XQPQUERIES_H
#define XQPQUERIES_H

#include <qwidget.h>
#include <qmainwindow.h>
#include <qtextedit.h>


class XQPQueries : public QMainWindow
{
  Q_OBJECT
    public:
  XQPQueries(QWidget *parent, QString& name, QString text);
  ~XQPQueries();
  
public slots:
  
 signals:
 void process_text(QString);
 void process_return();
 private:
  QTextEdit* queries;
  QWidget* parent;
  
 protected:
  void keyPressEvent(QKeyEvent *);

};

#endif // XQPQUERIES_H
