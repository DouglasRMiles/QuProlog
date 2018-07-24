/***************************************************************************
                          interact.h  -  QP interaction widget
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

// $Id: interact.h,v 1.2 2004/05/16 04:27:54 qp Exp $

#ifndef INTERACT_H
#define INTERACT_H

#include <qwidget.h>
#include <qtextedit.h>
#include <qstring.h>
#include <fstream>
#include <qregexp.h>
#include <qsocketnotifier.h>
#include <qstringlist.h>



class Interact : public QTextEdit  {
  Q_OBJECT
    public: 
  Interact(QWidget *box);
  ~Interact();
  void insert_at_end(QString s); 
  
  public slots:
    void processReturn();
  void openQueryFile();
  void saveHistory();
  void saveSession();
  void processF5(QString s);
  
 signals:
  void send_cmd(QString s);
  void ctrl_D_sig();
  
 private:
  QWidget* parent;
  int indent;
  bool readonly;
  bool in_query;
  bool in_history;
  QList<QString*> history;
  int hist_pos;
  QString* firstHistoryItem(void);
  QString* nextHistoryItem(void);
  QString* previousHistoryItem(void);
  void addHistoryItem(QString* s);

 protected:
  void mouseReleaseEvent(QMouseEvent*);
  void mousePressEvent(QMouseEvent*);
  void cut();
  void keyPressEvent(QKeyEvent *);
  void clear() {}
  void paste();
 public:
 
  

};

#endif
