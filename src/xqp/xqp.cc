/***************************************************************************
                          xqp.cpp  -  Interface to QP
                             -------------------
    begin                : April 2004
    copyright            : (C) 2002 by Peter Robinson
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

// $Id: xqp.cc,v 1.2 2004/05/16 04:27:55 qp Exp $

#include <signal.h>
#include <unistd.h>
#include <string>
#include <iostream>

#include <qdialog.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qapplication.h>
#include <qmenu.h>
#include <qmainwindow.h>
#include <qmenubar.h>
#include <qmessagebox.h>
#include <qinputdialog.h>

#include "xqp.h"
#include "interact.h"
#include <qcolor.h>
#include <qfontdialog.h>


using namespace std;

// Dialog box for configuration
ConfigDialog::ConfigDialog(Xqp *parent, QFont xqpf, QColor xqpc)
  : QDialog(parent)
{
     QPushButton *ok, *cancel, *font, *colour;
     ok = new QPushButton("OK", this);
     cancel = new QPushButton("Cancel", this);
     font = new QPushButton("Choose Font", this);
     colour = new QPushButton("Choose Colour", this);
     f = xqpf;
     c = xqpc;
     p = parent;

     QLabel *label = new QLabel(this);
     label->setText("Sample");
     label->setGeometry(10,50,60,30);

     ok->setGeometry(20,200,120,40);
     cancel->setGeometry(190,200,120,40);
     font->setGeometry(10,10,150,40);
     colour->setGeometry(170,10,150,40);
     browser = new QTextBrowser(this);
     browser->setGeometry(10,80,310,100);
     browser->setText("AaBb :- \n| ?-");
     browser->setFont(f);

     QPalette p=browser->palette();
     p.setColor(QPalette::Base, c); 
     browser->setPalette(p);

     connect(ok, SIGNAL(clicked()), SLOT(accept()));
     connect(cancel, SIGNAL(clicked()), SLOT(reject()));
     connect(font, SIGNAL(clicked()), SLOT(choose_font()));
     connect(colour, SIGNAL(clicked()), SLOT(choose_colour()));
}

void ConfigDialog::choose_font()
{
   bool ok;
    QFont pick =  QFontDialog::getFont(&ok, f,this);
   if (ok)
     {
       browser->setFont(pick);
       f = pick;
     }

}

void ConfigDialog::choose_colour()
{
  QColor pick = QColorDialog::getColor(c, this);
  if (pick.isValid())
    {
      QPalette p=browser->palette();
      p.setColor(QPalette::Base, pick); 
      browser->setPalette(p);
      c = pick;
    }
}

void ConfigDialog::accept()
{
  p->setConfigs(f, c);
  QDialog::accept();
}


Xqp::Xqp(int e_stdout, int e_stdin, pid_t c_pid)
  : QMainWindow()
{
  config = new QPConfig(this);
  qp_stdin = e_stdin;
  qp_stdout = e_stdout;
  child_pid = c_pid;

  setWindowTitle("XQP");
  move(config->getX(), config->getY());
  resize(config->getWidth(), config->getHeight());
  read_buff = new char[buff_size+2];
  qpint = new Interact(this);
  qpint->setFont(config->qpFont());
  QPalette p=qpint->palette();
  p.setColor(QPalette::Base, config->qpColor()); 
  qpint->setPalette(p);
  setCentralWidget(qpint);
  qpint->setFocus();
  qpint->setReadOnly(false);  
  // Set up menu items
  // File menu
  QMenu* file = menuBar()->addMenu("File");
  file->addAction("Open Query File", qpint, SLOT(openQueryFile()), 0);
  file->addAction("Save History", qpint, SLOT(saveHistory()), 0);
  file->addAction("Save Session", qpint, SLOT(saveSession()), 0);
  file->addAction("Configure", this, SLOT(configure_int()), 0);
  
  QMenu* sigs = menuBar()->addMenu("Signals");
  sigs->addAction("SIGINT", this, SLOT(process_CTRL_C()), 0);
  
  
  // Help menu
  QMenu* help = menuBar()->addMenu("Help");
  help->addAction("Help", this, SLOT(showHelp()), 0);
  help->addAction("About", this, SLOT(showAbout()), 0);

  //connect(this, SIGNAL(exit_signal()), a, SLOT(quit()) );

  sn = new QSocketNotifier(qp_stdout, QSocketNotifier::Read, this);
  connect(sn, SIGNAL(activated(int)), this, SLOT(process_char(int)));
  connect(qpint, SIGNAL(ctrl_D_sig()), this, SLOT(process_CTRL_D()));

  show();

  qpint->setFocus();
}


void Xqp::process_qp_cmd(QString cmd)
{
   qpint->setTextColor(Qt::blue);
   qpint->insert_at_end(cmd);
   //qpint->setTextColor(Qt::black);
   send_cmd_to_qp(cmd);
   // qpint->setTextColor(Qt::blue);
}

void Xqp::send_cmd_to_qp(QString cmd)
{
   write(qp_stdin, cmd.toAscii(), cmd.length());
}

  
void Xqp::closeEvent(QCloseEvent *e)
{
  QMainWindow::closeEvent(e);
}


void Xqp::process_char(int s)
{
  int no;
  no = read(s, read_buff, buff_size);
  if (no == 0)
    {
      close();
      return;
    }
  read_buff[no] = '\0';
  QString inq = QString(read_buff);
  qpint->setTextColor(Qt::black);
  qpint->insert_at_end(inq);
  qpint->setTextColor(Qt::blue);
}


void Xqp::process_CTRL_D()
{
     write(qp_stdin, "", 1);
     //close();
}

void Xqp::process_CTRL_C()
{
#ifndef WIN32
  kill(child_pid, SIGINT);
#endif
}

void Xqp::setConfigs(QFont f, QColor c)
{
  config->setQPFont(f);
  qpint->setFont(config->qpFont());
  config->setQPColor(c);
  QPalette p=qpint->palette();
  p.setColor(QPalette::Base, config->qpColor()); 
  qpint->setPalette(p);
}
void Xqp::configure_int()
{
  ConfigDialog* cd;
  QColor cc = config->qpColor();
  cd = new ConfigDialog(this, config->qpFont(), cc);
  if (cd->exec())
    {   
      
    }
  delete cd;

  //   bool ok;
  // QFont pick =  QFontDialog::getFont(&ok, config->qpFont(),this);
  //if (ok)
  //  {
  //    config->setQPFont(pick);
  //    qpint->setFont(config->qpFont());
  //
  //  }
}


void Xqp::showAbout()
{
  QMessageBox::about(this, "xqp",
             "A QT interface to QP.\n\nPeter Robinson pjr@itee.uq.edu.au");
}

void Xqp::showHelp()
{
  qthelp = new QTHelp(this);
}

Xqp::~Xqp()
{
  delete qpint;
  delete config;
}


