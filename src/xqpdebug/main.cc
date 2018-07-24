/***************************************************************************
                          main.cc  -  QT interface to qp debugger
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

// $Id: main.cc,v 1.1 2004/05/11 03:24:01 qp Exp $

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <fstream>

#include "xqpdebug.h"



int main(int argc, char *argv[])
{

  QApplication a(argc, argv);

  // Set up the GUI
  
  Xqpdebug *xqpdebug = new Xqpdebug(argv[1], argv[2], argv[3], argv[4]);
  //a.setMainWidget(xqpdebug);
  xqpdebug->show();  
  
  int exitval =  a.exec();
  delete xqpdebug;
  return exitval;
}
