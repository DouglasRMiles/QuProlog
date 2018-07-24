// block.h - Information carried by blocked threads.
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
// $Id: block.h,v 1.13 2006/02/14 02:40:09 qp Exp $

#ifndef	BLOCK_H
#define	BLOCK_H

#include "defs.h"
#include "timeval.h"
#include <list>
#include <sys/types.h>
#ifndef WIN32
        #include <sys/time.h>
#endif

#ifdef WIN32
        #define _WINSOCKAPI_
        #include <windows.h>
        #include <winsock2.h>
#endif

#include "objects.h"
#include "dynamic_code.h"

class Thread;
class Code;
class IOManager;
class Message;


class BlockStatus
{
 private:
  enum RunType {
    RUNNABLE,       
    RESTART_IO,
    RESTART_MSG,
    RESTART_TIME,
    RESTART_WAIT,
    BLOCKED
  };

  RunType status;
 public:
  BlockStatus() : status(RUNNABLE) {}

  ~BlockStatus() {}

  bool isBlocked(void) const { return status == BLOCKED; }
  bool isRunnable(void) const { return status == RUNNABLE; }
  bool isRestarted(void) const 
    { return (status != BLOCKED) && (status != RUNNABLE); }

  bool isRestartTime(void) const { return status == RESTART_TIME; }
  bool isRestartIO(void)   const { return status == RESTART_IO; }
  bool isRestartMsg(void)  const { return status == RESTART_MSG; }
  bool isRestartWait(void) const { return status == RESTART_WAIT; }

  void setBlocked(void)     { status = BLOCKED; }
  void setRunnable(void)    { status = RUNNABLE; }
  void setRestartIO(void)   { status = RESTART_IO; }
  void setRestartMsg(void)  { status = RESTART_MSG; }
  void setRestartTime(void) { status = RESTART_TIME; }
  void setRestartWait(void) { status = RESTART_WAIT; }

};


// The base class for blocking objects

class BlockingObject
{
private:
  Thread* thread;     // the blocked thread
  bool is_wait;
public:
  explicit BlockingObject(Thread* const t) : thread(t) { is_wait = false; }

  virtual ~BlockingObject() {}

  Thread* getThread(void) { return thread; }

  bool isWaitObject(void) { return is_wait; }

  void setIsWait(void) { is_wait = true; }

  virtual bool unblock(Timeval& tout) = 0;

  virtual bool hasFD(void) = 0;

#ifdef WIN32
  virtual int getFD(void) = 0;
#endif
  virtual void updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd) = 0;
};

class BlockingIOObject : public BlockingObject
{
 private:
  Timeval retry_time;            // Absolute time of retry
  int fd;                       // The fd to wait on
  IOType io_type;               // Type of io to be waited on
  IOManager* iomp;
 public:
  BlockingIOObject(Thread* const t, int f, IOType iot, IOManager* mp)
    : BlockingObject(t), retry_time(-1, 0), fd(f), io_type(iot), iomp(mp) {}

  bool unblock(Timeval& tout);

  bool hasFD(void) { return true; }

  int getFD(void) { return fd; }

  void updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd);
};

class BlockingTimeoutObject : public BlockingObject
{
 private:
  Timeval timeout;
 public:
  BlockingTimeoutObject(Thread* const t, double to) 
    : BlockingObject(t), timeout(to) {}

  bool unblock(Timeval& tout);

  bool hasFD(void) { return false; }

#ifdef WIN32
  int getFD(void) { return -1; }
#endif

  void updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd) {}

};

class BlockingMessageObject : public BlockingObject
{
 private:
  Timeval timeout;
  std::list<Message *>::iterator *iter;
  u_int size;
 public:
  BlockingMessageObject(Thread* const t, double to, 
			std::list<Message *>::iterator *i);

  bool unblock(Timeval& tout);

  bool hasFD(void) { return true; }

#ifdef WIN32
  int getFD(void) { return -1; }
#endif

  void updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd);

};

class WaitPred
{
 public:
  Object* predname;
  int arity;
  DynamicPredicate* predptr;
  u_int stamp;
  u_int assert_stamp;
  u_int retract_stamp;
  u_int saved_stamp;
  u_int saved_assert_stamp;
  u_int saved_retract_stamp;
  bool modified;
  bool check_assert;
  bool check_retract;

  WaitPred(Object* pn, int a, DynamicPredicate* pp, int s, int as, 
	   int rs, bool ca, bool cr); 

  void updateStamps(void);
};
      
class BlockingWaitObject : public BlockingObject
{
 private:
  Code* code; 
  Timeval timeout;
  u_int stamp;
  vector<WaitPred*> wait_preds;
  double retry_timeout;   // -1 if not retry
  bool wake_on_timeout;

 public:
  BlockingWaitObject(Thread* const t, Code* c, Object* preds, 
		     Object* until, Object* every, PredTab* predicates);

  ~BlockingWaitObject(void);

  bool unblock(Timeval& tout);

  bool hasFD(void) { return false; }
  
  void setWakeOnTimeout(bool v) { wake_on_timeout = v; }

  bool isWakeOnTimeout(void) { return wake_on_timeout; }

  void update(void);

  bool is_unblocked(void);

  Object* extract_changed_preds(void);

  void dump(void);


#ifdef WIN32
  int getFD(void) { return -1; }
#endif

  void updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd) {}

};



#endif	// BLOCK_H

