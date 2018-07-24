// messages.h - message processing.
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
// $Id: messages.h,v 1.8 2006/02/14 02:40:09 qp Exp $

#ifndef	MESSAGES_H
#define	MESSAGES_H

#include "thread_table.h"
#include "timeval.h"

#ifdef WIN32
#define _WINSOCKAPI_
#include <windows.h>
#include <winsock2.h>
#endif

class Thread;

//
// The base class for individual messages
//
class Message
{
private:
  int references;    // reference count for deleting messages
  bool committed;   // has message been consummed?

public:
  Message():references(0),committed(false) {}

  virtual ~Message() {}

  void IncReferences(void) { references++; }
  void DecReferences(void) { references--; }

  size_t References(void) const { return references; }

  void Commit(void) { committed = true; }
  bool Committed(void) const { return committed; }

  bool canDelete(void) const { return(committed && (references == 0)); }

  // virtual methods vor derived classes

  virtual void constructMessage(Object*& sender, Object*& msg,
				Thread&, AtomTable&,
				bool remember_names = false) = 0;
};

//
// The base class for message channels
//

class MessageChannel
{
private:
  ThreadTable& thread_table;
public:
  explicit MessageChannel(ThreadTable& t) : thread_table(t) {}

  virtual ~MessageChannel() {}

  ThreadTable& getThreadTable(void) { return thread_table; }

  // Put messages on appropriate threads' message buffer
  virtual bool ShuffleMessages(void) = 0;

  // Update FD_SET's for testing with select
  virtual void updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd) = 0;

  // Process timeouts related to message channel
  virtual void processTimeouts(Timeval& timeout) = 0;
};


#endif // MESSAGES_H
