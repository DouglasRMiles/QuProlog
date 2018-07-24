/***************************************************************************
                          qthelp.cc  -  XQP help widget
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


// $Id: qthelp.cc,v 1.2 2004/05/25 04:31:33 qp Exp $

#include "qthelp.h"

const char* text = 
"<H2>Using the Qu-Prolog interpreter GUI</H2>\n\
The GUI behaves much like the dumb terminal interface to qp. \
Output (stdout and stderr) appears in the GUI text window and \
input added to the text window is taken as input to qp. \
In addition Control-D has the same behaviour in the GUI as\
 in the dumb terminal interface. Because Control-C is used for editing in the \
text widget, SIGINT is sent to the Qu-Prolog interpreter using the \
Signals menu.\
The GUI also includes features not found in the dumb terminal interface\
 and these are listed below.\n\n\
<p>\
<H3>1. Query Editing</H3>\
Because the GUI uses a text window for interaction the usual \
text window editing can be used to edit input. \
When editing is complete a RETURN will send the entire input to qp.\
<H3>2. Query History</H3>\
Each query given to qp is added to the query history list. \
The up and down arrow keys can be used to move through \
the history list.\
<H3>3. Saving the History</H3>\
The entire contents of the text window can also be saved using the File menu. \
<H3>4. Saving the Session</H3>\
The entire contents of the text window can also be saved using the File menu. \
<H3>5. Opening a Query File</H3> \
The File menu also contains an option for opening a file. \
Typically this file contains a collection of queries - \
possibly produced by saving the history of another session. \
When this file is opened the contents of the file appear in a \
separate edit window. \
Within this window the following keys can be used to send strings \
to the interpreter window.\
<p>\
<b>F5</b> - If qp is waiting for a query then the current query \
(including the newline) is sent to the interpreter \
window and the cursor is advanced to the beginning of the next line. \
If qp is waiting for other input then the F5 key has the effect of \
sending the current line to qp.\
<p>\
<b>F6</b> - Send a newline to the interpreter window. \
This,and the next two keys, are typically used when qp is expecting a user \
response to the answer of the previous query.\
<p>\
<b>F7</b> - Send a semi-colon to the interpreter window.\
<p>\
<b>F8</b> - Send a comma to the interpreter window.\
<p>\
<b>F9</b> - Similar to F5 except that the newline is not sent - \
this can be used when the query needs to be edited.\
<p><p>";


QTHelp::QTHelp(QWidget *p)
  : QMainWindow(p)
{
  help = new QTextEdit(this);
  setCentralWidget(help);
  parent = p;
  resize(600,400);
  help->setHtml(text);
  help->setReadOnly(true);
  setWindowTitle("XQP Help");
  show();
}

QTHelp::~QTHelp() {}
  
