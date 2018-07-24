/***************************************************************************
                          main.cc  -  QT interface to qp
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

// $Id: main.cc,v 1.2 2004/05/25 02:14:30 qp Exp $

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <errno.h>
#ifdef WIN32
//#define _WINSOCKAPI_
//#include <windows.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//# include <io.h>
//typedef int socklen_t;
#else

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#endif
#include "xqp.h"

using namespace std;

#ifdef WIN32
#include <windows.h>


   #pragma comment(lib, "User32.lib")
   void DisplayError(char *pszAPI);
   void ReadAndHandleOutput(HANDLE hPipeRead);
   void PrepAndLaunchRedirectedChild(HANDLE hChildStdOut,
                                     HANDLE hChildStdIn,
                                     HANDLE hChildStdErr);
   DWORD WINAPI GetAndSendInputThread(LPVOID lpvThreadParam);

   HANDLE hChildProcess = NULL;
   HANDLE hStdIn = NULL; // Handle to parents std input.
   BOOL bRunThread = TRUE;


   int main (int argc, char* argv[])
   {
      HANDLE hOutputReadTmp,hOutputRead,hOutputWrite;
      HANDLE hInputWriteTmp,hInputRead,hInputWrite;
      HANDLE hErrorWrite;
      HANDLE hThread;
      DWORD ThreadId;
      SECURITY_ATTRIBUTES sa;


      // Set up the security attributes struct.
      sa.nLength= sizeof(SECURITY_ATTRIBUTES);
      sa.lpSecurityDescriptor = NULL;
      sa.bInheritHandle = TRUE;


      // Create the child output pipe.
      if (!CreatePipe(&hOutputReadTmp,&hOutputWrite,&sa,0))
         DisplayError("CreatePipe");


      // Create a duplicate of the output write handle for the std error
      // write handle. This is necessary in case the child application
      // closes one of its std output handles.
      if (!DuplicateHandle(GetCurrentProcess(),hOutputWrite,
                           GetCurrentProcess(),&hErrorWrite,0,
                           TRUE,DUPLICATE_SAME_ACCESS))
         DisplayError("DuplicateHandle");


      // Create the child input pipe.
      if (!CreatePipe(&hInputRead,&hInputWriteTmp,&sa,0))
         DisplayError("CreatePipe");


      // Create new output read handle and the input write handles. Set
      // the Properties to FALSE. Otherwise, the child inherits the
      // properties and, as a result, non-closeable handles to the pipes
      // are created.
      if (!DuplicateHandle(GetCurrentProcess(),hOutputReadTmp,
                           GetCurrentProcess(),
                           &hOutputRead, // Address of new handle.
                           0,FALSE, // Make it uninheritable.
                           DUPLICATE_SAME_ACCESS))
         DisplayError("DupliateHandle");

      if (!DuplicateHandle(GetCurrentProcess(),hInputWriteTmp,
                           GetCurrentProcess(),
                           &hInputWrite, // Address of new handle.
                           0,FALSE, // Make it uninheritable.
                           DUPLICATE_SAME_ACCESS))
      DisplayError("DupliateHandle");


      // Close inheritable copies of the handles you do not want to be
      // inherited.
      if (!CloseHandle(hOutputReadTmp)) DisplayError("CloseHandle");
      if (!CloseHandle(hInputWriteTmp)) DisplayError("CloseHandle");


      // Get std input handle so you can close it and force the ReadFile to
      // fail when you want the input thread to exit.
      if ( (hStdIn = GetStdHandle(STD_INPUT_HANDLE)) ==
                                                INVALID_HANDLE_VALUE )
         DisplayError("GetStdHandle");

      PrepAndLaunchRedirectedChild(hOutputWrite,hInputRead,hErrorWrite);


      // Close pipe handles (do not continue to modify the parent).
      // You need to make sure that no handles to the write end of the
      // output pipe are maintained in this process or else the pipe will
      // not close when the child process exits and the ReadFile will hang.
      if (!CloseHandle(hOutputWrite)) DisplayError("CloseHandle");
      if (!CloseHandle(hInputRead )) DisplayError("CloseHandle");
      if (!CloseHandle(hErrorWrite)) DisplayError("CloseHandle");


      QApplication a(argc, argv);
      Xqp *xqp = new Xqp((int)hInputWrite,
                         (int)hOutputRead, 0);
      xqp->show();  

      int exitval =  a.exec();
      delete xqp;
      return exitval;

      // Launch the thread that gets the input and sends it to the child.
      hThread = CreateThread(NULL,0,GetAndSendInputThread,
                              (LPVOID)hInputWrite,0,&ThreadId);
      if (hThread == NULL) DisplayError("CreateThread");


      // Read the child's output.
      ReadAndHandleOutput(hOutputRead);
      // Redirection is complete


      // Force the read on the input to return by closing the stdin handle.
      if (!CloseHandle(hStdIn)) DisplayError("CloseHandle");


      // Tell the thread to exit and wait for thread to die.
      bRunThread = FALSE;

      if (WaitForSingleObject(hThread,INFINITE) == WAIT_FAILED)
         DisplayError("WaitForSingleObject");

      if (!CloseHandle(hOutputRead)) DisplayError("CloseHandle");
      if (!CloseHandle(hInputWrite)) DisplayError("CloseHandle");
   }


   /////////////////////////////////////////////////////////////////////// 
   // PrepAndLaunchRedirectedChild
   // Sets up STARTUPINFO structure, and launches redirected child.
   /////////////////////////////////////////////////////////////////////// 
   void PrepAndLaunchRedirectedChild(HANDLE hChildStdOut,
                                     HANDLE hChildStdIn,
                                     HANDLE hChildStdErr)
   {
      PROCESS_INFORMATION pi;
      STARTUPINFO si;

      // Set up the start up info struct.
      ZeroMemory(&si,sizeof(STARTUPINFO));
      si.cb = sizeof(STARTUPINFO);
      si.dwFlags = STARTF_USESTDHANDLES;
      si.hStdOutput = hChildStdOut;
      si.hStdInput  = hChildStdIn;
      si.hStdError  = hChildStdErr;
      // Use this if you want to hide the child:
      //     si.wShowWindow = SW_HIDE;
      // Note that dwFlags must include STARTF_USESHOWWINDOW if you want to
      // use the wShowWindow flags.


      // Launch the process that you want to redirect (in this case,
      // Child.exe). Make sure Child.exe is in the same directory as
      // redirect.c launch redirect from a command line to prevent location
      // confusion.
      //char buff[20];
      //strcpy(buff, "qp.bat");
      //LPTSTR qp_exec = buff;
char buff[150] = "qp.bat";
TCHAR qp_exec[150];

MultiByteToWideChar(CP_ACP, 0, buff, -1,  qp_exec, 150);

      if (!CreateProcess(NULL,qp_exec,NULL,NULL,TRUE,
                         CREATE_NO_WINDOW,NULL,NULL,&si,&pi))
         DisplayError("CreateProcess");


      // Set global child process handle to cause threads to exit.
      hChildProcess = pi.hProcess;


      // Close any unnecessary handles.
      if (!CloseHandle(pi.hThread)) DisplayError("CloseHandle");
   }


   /////////////////////////////////////////////////////////////////////// 
   // ReadAndHandleOutput
   // Monitors handle for input. Exits when child exits or pipe breaks.
   /////////////////////////////////////////////////////////////////////// 
   void ReadAndHandleOutput(HANDLE hPipeRead)
   {
      CHAR lpBuffer[256];
      DWORD nBytesRead;
      DWORD nCharsWritten;

      while(TRUE)
      {
         if (!ReadFile(hPipeRead,lpBuffer,sizeof(lpBuffer),
                                          &nBytesRead,NULL) || !nBytesRead)
         {
            if (GetLastError() == ERROR_BROKEN_PIPE)
               break; // pipe done - normal exit path.
            else
               DisplayError("ReadFile"); // Something bad happened.
         }

         // Display the character read on the screen.
         if (!WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE),lpBuffer,
                           nBytesRead,&nCharsWritten,NULL))
            DisplayError("WriteConsole");
      }
   }


   /////////////////////////////////////////////////////////////////////// 
   // GetAndSendInputThread
   // Thread procedure that monitors the console for input and sends input
   // to the child process through the input pipe.
   // This thread ends when the child application exits.
   /////////////////////////////////////////////////////////////////////// 
   DWORD WINAPI GetAndSendInputThread(LPVOID lpvThreadParam)
   {
      CHAR read_buff[256];
      DWORD nBytesRead,nBytesWrote;
      HANDLE hPipeWrite = (HANDLE)lpvThreadParam;

      // Get input from our console and send it to child through the pipe.
      while (bRunThread)
      {
         if(!ReadConsole(hStdIn,read_buff,1,&nBytesRead,NULL))
            DisplayError("ReadConsole");

         read_buff[nBytesRead] = '\0'; // Follow input with a NULL.

         if (!WriteFile(hPipeWrite,read_buff,nBytesRead,&nBytesWrote,NULL))
         {
            if (GetLastError() == ERROR_NO_DATA)
               break; // Pipe was closed (normal exit path).
            else
            DisplayError("WriteFile");
         }
      }

      return 1;
   }


   /////////////////////////////////////////////////////////////////////// 
   // DisplayError
   // Displays the error number and corresponding message.
   /////////////////////////////////////////////////////////////////////// 
   void DisplayError(char *pszAPI)
   {
       LPVOID lpvMessageBuffer;
       CHAR szPrintBuffer[512];
       DWORD nCharsWritten;

       FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
                NULL, GetLastError(),
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR)&lpvMessageBuffer, 0, NULL);

       //       wsprintf(szPrintBuffer,
       //   "ERROR: API    = %s.\n   error code = %d.\n   message    = %s.\n",
       //          pszAPI, GetLastError(), (char *)lpvMessageBuffer);

       cerr << "error " << szPrintBuffer << endl;
       //WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE),szPrintBuffer,
       //              lstrlen(szPrintBuffer),&nCharsWritten,NULL);

       LocalFree(lpvMessageBuffer);
       ExitProcess(GetLastError());
   }

#else


// Create 2 sockets for unidirectional communication to and from qp
int socket_main_to_qp[2], socket_qp_to_main[2];


int main(int argc, char *argv[])
{

  if (socketpair(AF_LOCAL, SOCK_STREAM, 0, socket_main_to_qp))
    {
      cerr << "Fail to open socket" << endl;
      exit(1);
    }
  if (socketpair(AF_LOCAL, SOCK_STREAM, 0, socket_qp_to_main))
    {
      cerr << "Fail to open socket" << endl;
      exit(1);
    }

  // fork child process that will exec qp
  pid_t PID = fork();
  
  if (PID == 0)
    {
      // In child -
      // close write end of socket_main_to_qp
      close(socket_main_to_qp[1]);
      // close read end of socket_qp_to_main
      close(socket_qp_to_main[0]);
      
      if (dup2(socket_qp_to_main[1], STDOUT_FILENO) == -1)
	{
          cerr << "Fail to dup socket_qp_to_main" << endl;
          exit(1);  
	}
      if (dup2(socket_qp_to_main[1], STDERR_FILENO) == -1)
	{
          cerr << "Fail to dup socket_qp_to_main" << endl;
          exit(1);  
	}
      if (dup2(socket_main_to_qp[0], STDIN_FILENO) == -1)
	{
          cerr << "Fail to dup socket_main_to_qp" << endl;
          exit(1);  
	}

      // exec qp
      char* qp_args[argc+1];
      char* qpstr = new char[strlen("qp")+1];
      strcpy(qpstr, "qp");
      qp_args[0] = qpstr;
      for (int i = 1; i < argc; i++) 
	{
	  qp_args[i] = argv[i];
	}
      qp_args[argc] = NULL;
      execvp("qp", qp_args);
    }
  else
    {
      // In parent - 
      // close read end of socket_main_to_qp
      close(socket_main_to_qp[0]);
      // close write end of socket_qp_to_main
      close(socket_qp_to_main[1]);

      // Set up the GUI

      QApplication a(argc, argv);
      Xqp *xqp = new Xqp(socket_qp_to_main[0],
			 socket_main_to_qp[1], PID);
      xqp->show();  

      int exitval =  a.exec();
      delete xqp;
      return exitval;
    }
}

#endif
