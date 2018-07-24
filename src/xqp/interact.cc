/***************************************************************************
                          interact.cc  -  QP interaction widget
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

// $Id: interact.cc,v 1.3 2004/05/25 04:31:33 qp Exp $

#include <signal.h>
#include <unistd.h>
#include <string>
#include <iostream>

#include "interact.h"
#include "term.h"
#include "xqpqueries.h"
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qfile.h>
#include <qtextstream.h>
#include <QKeyEvent>

using namespace std;

Interact::Interact( QWidget *box )
  : QTextEdit(box)
{
  parent = box;
  setFont( QFont( "Lucidatypewriter", 12, QFont::Normal ) );
  indent = 0;
  readonly = false;
  connect(this, SIGNAL(send_cmd(QString)), box, SLOT(send_cmd_to_qp(QString)));
  in_history = false;
  hist_pos = 0;
}

void Interact::insert_at_end(QString s)
{
  insertPlainText(s);
  QTextCursor cursor(textCursor());
  cursor.movePosition(QTextCursor::End);
  setTextCursor(cursor);
  setTextColor(Qt::blue);
  in_query = (s.contains(QRegExp("'| \\?- $")));
  //if (in_query) 
  indent = cursor.position();
}

void Interact::processF5(QString s)
{
  QTextCursor cursor(textCursor());
  cursor.movePosition(QTextCursor::End);
  cursor.insertText(s);
  setTextCursor(cursor);
}

void Interact::processReturn()
{
  QTextCursor cursor(textCursor());
  cursor.setPosition(indent);
  cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
  in_history = false;
  QString cmd = cursor.selectedText();
  cmd.replace(QChar::ParagraphSeparator, QString("\n"));
  if (!in_query || end_of_term(cmd, 0))
    {
      cmd.append("\n");
      send_cmd(cmd);
      cmd.truncate(cmd.length()-1);
      if (in_query)
        {
          addHistoryItem(new QString(cmd));
          hist_pos = 0;
        }
      in_query = false;
    }
}


Interact::~Interact()
{
}

void Interact::mouseReleaseEvent(QMouseEvent* e)
{
  QTextCursor cursor(textCursor());
  int p = cursor.position();
  if (p < indent)
    {
      if (e->button() != Qt::MidButton)
	QTextEdit::mouseReleaseEvent(e);
      cursor.movePosition(QTextCursor::End);
      setTextCursor(cursor);
      readonly = true;
    }
  else
    {
      QTextEdit::mouseReleaseEvent(e);
      readonly = false;
    }
}

void Interact::mousePressEvent(QMouseEvent* e)
{
  if (e->button() == Qt::MidButton)
    {
      QMouseEvent lbe(QEvent::MouseButtonPress, e->pos(), 
		      Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
      QTextEdit::mousePressEvent(&lbe);
      QTextEdit::mouseReleaseEvent(&lbe);
    }
  QTextEdit::mousePressEvent(e);
}

void Interact::cut()
{
  if (readonly) QTextEdit::copy();
  else QTextEdit::cut();
}

void Interact::paste()
{
  if (!readonly) QTextEdit::paste();
}

void Interact::keyPressEvent(QKeyEvent *k)
{
  int key_pressed = k->key();
  if (key_pressed == Qt::Key_Control)
    {
      QTextEdit::keyPressEvent(k);
      return;
    }
  if (k->modifiers() == Qt::ControlModifier)
    {
      in_history = false;
      if (key_pressed == 'D')
        {
          emit ctrl_D_sig();
          return;
        } 
      if (key_pressed == 'C')
	{
	  QTextEdit::keyPressEvent(k);
	  return;
	}
    }
  if (readonly)
    {
      in_history = false;
      QTextCursor cursor(textCursor());
      cursor.movePosition(QTextCursor::End);
      setTextCursor(cursor);
    }
  if (key_pressed == Qt::Key_Return)
    {
      processReturn();
    }
  if ((key_pressed == Qt::Key_Backspace)
      || (key_pressed == Qt::Key_Left))
    {
      int p;
      in_history = false;
      QTextCursor cursor(textCursor());
      p = cursor.position();
      if (p <= indent)
        {
          return;
        }
    }
  if (key_pressed == Qt::Key_Up)
    {
      QString* item;
      if (!in_history)
	{
	  item = firstHistoryItem();
	}
      else
	{
	  item = nextHistoryItem();
	}
      in_history = true;
      if (item != NULL)
	{
	  QTextCursor cursor(textCursor());
	  cursor.setPosition(indent);
	  cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
	  cursor.removeSelectedText();
          setTextColor(Qt::blue);
	  insertPlainText(*item);
	}
      return;
    }
  if (key_pressed == Qt::Key_Down)
    {
       QString* item = previousHistoryItem();
       QTextCursor cursor(textCursor());
       cursor.setPosition(indent);
       cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
       cursor.removeSelectedText();
       setTextColor(Qt::blue);
       if ( item != NULL)
         {
	   insertPlainText(*item);
          }
       else
	 {
           in_history = false;
	   insertPlainText("");
	 }
       return;
    }
  if (key_pressed == Qt::Key_Home)
    {
      in_history = false;
      if (k->modifiers() == Qt::ControlModifier)
	{
	  QTextCursor cursor(textCursor());
	  cursor.setPosition(indent);
	  setTextCursor(cursor);
	  return;
	}
      else
	{
	  int p;
	  QTextCursor cursor(textCursor());
	  cursor.movePosition(QTextCursor::StartOfBlock);
	  p = cursor.position();
	  if (p > indent)
	    {
	      setTextCursor(cursor);
	    }
	  return;
	}
    }
  if (key_pressed == Qt::Key_PageUp)
    {
      in_history = false;
      QTextCursor cursor(textCursor());
      cursor.setPosition(indent);
      setTextCursor(cursor);
      return;
    }

  in_history = false;
  QTextEdit::keyPressEvent(k);
}

void Interact::addHistoryItem(QString* s)
{
  history.prepend(s);
}

QString* Interact::firstHistoryItem(void)
{
    if (history.size() == 0) return NULL;
    return history.first();
}

QString* Interact::nextHistoryItem(void)
{
    if (history.size() <= hist_pos+1) return NULL;
    return history[++hist_pos];
}

QString* Interact::previousHistoryItem(void)
{
    if (hist_pos == 0) return NULL;
    return history[--hist_pos];
}

void Interact::openQueryFile()
{
  QString fileName = QFileDialog::getOpenFileName(this, QString::null, QString::null, "*");
  if (fileName != QString::null)
    {
      QFile f(fileName);
      if (f.open(QIODevice::ReadOnly))
	{
	  QTextStream t(&f);
	  XQPQueries* xqp_queries = new XQPQueries(parent, fileName, t.readAll());
	  xqp_queries->setFont(font());
	  connect(xqp_queries, SIGNAL(process_text(QString)), this, SLOT(processF5(QString)));
	  connect(xqp_queries, SIGNAL(process_return()), this, SLOT(processReturn()));
	  f.close();
	}
    }
}

void Interact::saveHistory()
{  
  QString fileName = QFileDialog::getSaveFileName(this, QString::null, QString::null, "*");
  if (fileName != QString::null)
    {
      QFile f(fileName);
      if (f.open(QIODevice::WriteOnly))
	{
	  QString* item = firstHistoryItem();
	  QTextStream out(&f);
	  while (item != NULL)
	    {
	      out << *item << "\n";
	      item = nextHistoryItem();
	    }
	  f.close();
	}
    }
}

void Interact::saveSession()
{
  QString fileName = QFileDialog::getSaveFileName(this, QString::null, QString::null, "*");
  if (fileName != QString::null)
    {
      QFile f(fileName);
      if (f.open(QIODevice::WriteOnly))
	{
	  QString s = toPlainText();
	  QTextStream out(&f);
	  out << s;
	  f.close();
	}
    }
}
