// system_support.cc 
//
// Functions for general system support

//
// ##Copyright##
// 
// Copyright 2000-2016 Peter Robinson  (pjr@itee.uq.edu.au)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.00 
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// ##Copyright##
//
// $Id: system_support.cc,v 1.3 2006/03/30 22:50:31 qp Exp $

// PORT
#include "system_support.h"
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#ifdef WIN32
#include <direct.h>
#endif //WIN32

using namespace std;

void wordexp(string& str)
{
  

#ifdef WIN32
  // expand environment variables
  size_t pos;
  pos = str.find("%");
  while (pos != string::npos)
    {
      size_t end = str.find("%", pos+1);
      if (end != string::npos)
        {
          string env = string(str, pos+1, end-pos-1);
          char* expenv = getenv(env.c_str());
          if (expenv == NULL)
            {
              str.replace(pos, end-pos+1, "");
            }
          else
            {
              str.replace(pos, end-pos+1, expenv);
            }
          pos = end;
        }
      pos = str.find("%", pos+1);
    }
  pos = str.find("/");
  if (pos == 0)
    {
      str.replace(0, 1, "c:\\");
    }
  // replace /   
  pos = str.find("/");
  while (pos != string::npos)
    {
      str.replace(pos, 1, "\\");
      pos = str.find("/");
    }

  if (str == ".")
    {
      char path[256];
      if (_getcwd(path, 255) != NULL)
        str.replace(0,1,path);
    }
    // add full path if path doesn't start with C:\\ or c:\\
  pos = str.find("C:\\");
  if (pos != 0)
    {
      // doesn't start with C:
      pos = str.find("c:\\");
      if (pos != 0)
        {
          //doesn't start with c:
          char path[256];
          if (_getcwd(path, 255) != NULL)
            {
              str.insert(0, "\\");
              str.insert(0, path);
            }
        }
    }
  // process ".."
  pos = str.find("..");
  while (pos != string::npos)
    {
      if (str[pos-1] != '\\')
        break;
      size_t slashpos = str.rfind("\\", pos-2);
      if (slashpos == string::npos)
        break;
      str.replace(slashpos, pos+2-slashpos, "");
      pos = str.find("..");
    }

  pos = str.find("\\.\\");
  while (pos != string::npos)
    {
      str.replace(pos, 2, "");
      pos = str.find("\\.\\");
    }

#else //UNIX STUFF HERE
  
  // expand environment variables
  size_t pos;
  pos = str.find("$");
  while (pos != string::npos)
    {
      size_t end = str.find("/", pos);
      if (end == string::npos)
        {
          end = str.size();
        }
      string env = string(str, pos+1, end-pos-1);
      char* expenv = getenv(env.c_str());
      if (expenv == NULL)
        {
	  str.replace(pos, end-pos, "");
        }
      else
        {
	  str.replace(pos, end-pos, expenv);
        }
      pos = str.find("$");
    }
  // expand leading ~ to home dir
  pos = str.find("~/");
  if (pos == 0)
    {
      str.replace(0,1, getenv("HOME"));
    }
  // expand "~"
  if (str == "~")
    {
      str.replace(0,1,getenv("HOME"));
    }
  // replace "." by current dir
  if (str == ".")
    {
      char path[256];
      if (getcwd(path, 255) != NULL)
        str.replace(0,1,path);
    }
  // add full path if path doesn't start with /
  pos = str.find("/");
  if (pos != 0)
    {
      char path[256];
      if (getcwd(path, 255) != NULL)
        {
          str.insert(0, "/");
          str.insert(0, path);
        }
    }
  // remove //
  pos = str.find("//");
  while (pos != string::npos)
    {
      str.replace(pos, pos+1, "/");
      pos = str.find("//");
    }
  // process ".."
  pos = str.find("..");
  while (pos != string::npos)
    {
      if (str[pos-1] != '/')
        break;
      size_t slashpos = str.rfind("/", pos-2);
      if (slashpos == string::npos)
        break;
      str.replace(slashpos, pos+2-slashpos, "");
      pos = str.find("..");
    }
  // replace "/./" with "/"
  pos = str.find("/./");
  while (pos != string::npos)
    {
      str.replace(pos, 2, "");
      pos = str.find("/./");
    }

#endif
}
