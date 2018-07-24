/***************************************************************************
                          xqp.h  -  Interface to QP
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

// $Id: xqp.h,v 1.2 2004/05/16 04:27:55 qp Exp $

#ifndef XQP_H
#define XQP_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <qapplication.h>
#include <qwidget.h>
#include <qmainwindow.h>
#include <sys/types.h>
#include <qstring.h>
//#include <qmultilineedit.h>
#include <qdialog.h>
#include <qmainwindow.h>
#include <qtextbrowser.h>
#include <qcolordialog.h>

#include "interact.h"
#include "qpconfig.h"
#include "qthelp.h"


// A dialog box for configuration
class ConfigDialog : public QDialog
{
  Q_OBJECT
public:
  ConfigDialog(Xqp *parent, QFont, QColor);
  public slots:
    void choose_font();
  void choose_colour();
  void accept();
 private:
  Xqp* p;
  QFont f;
  QColor c;
  QTextBrowser *browser;
};


/** Xqp is the base class of the project */
class Xqp : public QMainWindow
{
  Q_OBJECT 
    public:
  /** construtor */
  Xqp(int c_stdout, int c_stdin, pid_t c_pid);
  /** destructor */
  ~Xqp();
  public slots:
   void send_cmd_to_qp(QString cmd);
   void process_qp_cmd(QString cmd);
   void process_char(int fd);
   void process_CTRL_D();
   void process_CTRL_C();
   void configure_int();
   void showAbout();
   void showHelp();
 signals:
    void exit_signal();
    void eof_signal();

private:
  QPConfig* config;
  Interact* qpint;
  int qp_stdout;
  int qp_stdin;
  pid_t child_pid;
  QSocketNotifier* sn;
  QSocketNotifier* sn_err;

  QRegExp* prompt1;
  static const int buff_size = 10000;
  char* read_buff;

  QMenu* view_menu;
  QTHelp* qthelp;

public:
  void processChar(int s);
  void setConfigs(QFont, QColor);

protected:
  void closeEvent(QCloseEvent *e);


};

#endif
