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

// $Id: interact.cc,v 1.2 2004/05/16 04:27:55 qp Exp $

#include <signal.h>
#include <unistd.h>
#include <string>
#include <iostream>

#include "interact.h"
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qfile.h>
//Added by qt3to4:
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>

using namespace std;

Interact::Interact( QWidget *box )
  : QTextEdit(box)
{
  parent = box;
  //setTextFormat(Qt::PlainText);
  setFont( QFont( "Lucidatypewriter", 12, QFont::Normal ) );
  para = 0;
  indent = 0;
  //connect(this, SIGNAL(returnPressed()), this, SLOT(processReturn()));
  connect(this, SIGNAL(send_cmd(QString)), box, SLOT(send_cmd_to_qp(QString)));
}

void Interact::insert_at_end(QString s)
{
  insertPlainText(s);
  QTextCursor cursor(textCursor());
  cursor.movePosition(QTextCursor::End);
  setTextCursor(cursor);
  setTextColor(Qt::blue);
  indent = cursor.position();
}

void Interact::processReturn()
{ 
  QTextCursor cursor(textCursor());
  cursor.setPosition(indent);
  cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
  QString cmd = cursor.selectedText();
  send_cmd(cmd);
  cmd.truncate(cmd.length()-1);
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
      QTextCursor cursor(textCursor());
      cursor.movePosition(QTextCursor::End);
      setTextCursor(cursor);
    }
  if ((key_pressed == Qt::Key_Backspace)
      || (key_pressed == Qt::Key_Left))
    {
      int p;
      QTextCursor cursor(textCursor());
      p = cursor.position();
      if (p <= indent)
        {
          return;
        }
    }
  if (key_pressed == Qt::Key_Up)
    {
      int p;
      QTextCursor cursor(textCursor());
      p = cursor.position();
      if (p <= indent)
        {
          return;
        }
    }
  if (key_pressed == Qt::Key_Home)
    {
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
      QTextCursor cursor(textCursor());
      cursor.setPosition(indent);
      setTextCursor(cursor);
      return;
    }

  QTextEdit::keyPressEvent(k);
}

