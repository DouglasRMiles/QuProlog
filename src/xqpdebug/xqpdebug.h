/***************************************************************************
                          xqpdebug.h  -  Interface to QP debugger
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

// $Id: xqpdebug.h,v 1.1 2004/05/11 03:24:03 qp Exp $

#ifndef XQPDEBUG_H
#define XQPDEBUG_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <qapplication.h>
#include <qwidget.h>
#include <qmainwindow.h>
//Added by qt3to4:
#include <QCloseEvent>
#include <sys/types.h>
#include <qstring.h>
//#include <q3multilineedit.h>
#include <qdialog.h>
#include <qmainwindow.h>
#include <qtextbrowser.h>
#include <qcolordialog.h>
#include <string>
#include "interact.h"
#include "qpconfig.h"


using namespace std;

class PedroConnection;

/** Xqpdebug is the base class of the project */
class Xqpdebug : public QWidget
{
  Q_OBJECT 
    public:
  /** construtor */
  Xqpdebug(char* threadname, char* processname, 
	   char* machineid, char* portstr);
  /** destructor */
  ~Xqpdebug();
  public slots:
    void process_msg(int fd);
  void send_cmd_to_qp(QString cmd);
  void process_qp_cmd(QString cmd);
  void process_CTRL_D();
  void configure_int();
  void process_creap();
  void process_skip();
  void process_leap();
  void process_exitd();
  void process_about();

 signals:
    void exit_signal();
    void eof_signal();

private:
  QPConfig* config;
  Interact* qpint;

  QSocketNotifier* sn;
  PedroConnection* pedro_conn;
  string to_addr;
  string handle;
public:
  void processChar(int s);
  void setConfigs(QFont, QColor);

protected:
  void closeEvent(QCloseEvent *e);


};

// A dialog box for configuration
class ConfigDialog : public QDialog
{
  Q_OBJECT
public:
  ConfigDialog(Xqpdebug *parent, QFont, QColor);
  public slots:
    void choose_font();
  void choose_colour();
  void accept();
 private:
  Xqpdebug* p;
  QFont f;
  QColor c;
  QTextBrowser *browser;
};

#endif
