// block.cc -
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
// $Id: block.cc,v 1.15 2006/02/14 02:40:08 qp Exp $

#include "config.h"

#ifdef WIN32
        #define _WINSOCKAPI_
        #include <windows.h>
        #include <io.h>
#else
        #include <unistd.h>
#endif

//#include "block.h"
#include "io_qp.h"
#include "thread_qp.h"


bool 
BlockingIOObject::unblock(Timeval& tout)
{
  if (io_type == IMSTREAM)
    {
      if ((iomp->GetStream(fd) == NULL) ||
	  (iomp->GetStream(fd)->msgReady()))
	{
	  getThread()->getBlockStatus().setRestartIO();
	  return true;
	}
      else
	{
	  return false;
	}
    }
  else
    {
      if (is_ready(fd, io_type))
	{
	  getThread()->getBlockStatus().setRestartIO();
	  return true;
	}
      else
	{
	  return false;
	}
    }
}

void
BlockingIOObject::updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd)
{
  if (io_type != IMSTREAM)
    {
      if (fd > max_fd) max_fd = fd;
      FD_SET(fd, rfds);
    }
}

bool 
BlockingTimeoutObject::unblock(Timeval& tout)
{
  Timeval now;
  if (timeout.isForever())
    {
      return false;
    }
  else if (timeout <= now)
    {
      getThread()->getBlockStatus().setRestartTime();
      return true;
    }
  else
    { 
      Timeval delta(timeout, now);
      if (delta < tout) tout = delta;
      return false;
    }
}

BlockingMessageObject::BlockingMessageObject(Thread* const t, double to, 
					     list<Message *>::iterator *i)
  : BlockingObject(t), timeout(to), iter(i)
{
  size = static_cast<u_int>(t->MessageQueue().size());
}

void
BlockingMessageObject::updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd)
{
}

bool 
BlockingMessageObject::unblock(Timeval& tout)
{
  Timeval now;

  if (size != getThread()->MessageQueue().size())
    {
       *iter = getThread()->MessageQueue().begin();
      for (u_int i = 1; i < size; i++)
	{
	  (*iter)++;
	}
      getThread()->getBlockStatus().setRestartMsg();
      return true;
    }
  else if (timeout.isForever())
    {
      return false; 
    }
  else if (timeout <= now)
    {
      getThread()->getBlockStatus().setRestartTime();
      return true;
    }
  else
    { 	 
      Timeval delta(timeout, now);
      if (delta < tout) tout = delta;
      return false;
    }
}

WaitPred:: WaitPred(Object* pn, int a, DynamicPredicate* pp, int s,
		    int as, int rs, bool ca, bool cr) : 
  predname(pn), arity(a), predptr(pp)
{
  stamp = s;
  assert_stamp = as;
  retract_stamp = rs;
  saved_stamp = s;
  saved_assert_stamp = as;
  saved_retract_stamp = rs;
  check_assert = ca;
  check_retract = cr;
  modified = false;
}

void WaitPred::updateStamps(void)
{
  u_int newstamp = predptr->GetStamp();
  u_int newassertstamp = predptr->GetAssertStamp();
  u_int newretractstamp = predptr->GetRetractStamp();
  if (newstamp != stamp) {
    stamp = newstamp;
    modified = true;
    assert_stamp = saved_assert_stamp;
    retract_stamp = saved_retract_stamp;
    saved_assert_stamp = newassertstamp;
    saved_retract_stamp = newretractstamp;    
  } else if (assert_stamp != newassertstamp) {
    modified = true;
    assert_stamp = saved_assert_stamp;
    saved_assert_stamp = newassertstamp;
  } else if (retract_stamp != newretractstamp) {
    modified = true;
    retract_stamp = saved_retract_stamp;
    saved_retract_stamp = newretractstamp;    
  }
}

BlockingWaitObject::BlockingWaitObject(Thread* const t, Code* c, Object* preds,
				       Object* until, Object* every, 
				       PredTab* predicates) 
  :  BlockingObject(t), code(c)
{
  setIsWait();
  setWakeOnTimeout(false);
  stamp = c->GetStamp();
  for (Object* predlist = preds; predlist->isCons(); 
       predlist = OBJECT_CAST(Cons *, predlist)->getTail()->variableDereference())
    {
      Object* pred = OBJECT_CAST(Cons *, predlist)->getHead()->variableDereference();
      assert(pred->isStructure());
      Structure* predstr = OBJECT_CAST(Structure*, pred);
      int s = -1; 
      int as = -1; 
      int rs = -1; 
      bool has_stamp = false;
      int tmp_stamp = 0;
      if (predstr->getFunctor()->variableDereference() == AtomTable::multiply) {
        pred = predstr->getArgument(1)->variableDereference();
        tmp_stamp = predstr->getArgument(2)->variableDereference()->getInteger();
        has_stamp = true;
        predstr = OBJECT_CAST(Structure*, pred);
      }
      Object* arityobj = predstr->getArgument(2)->variableDereference();
      int arity =  arityobj->getInteger();
      Object* predname = predstr->getArgument(1)->variableDereference();
      bool ca = false;
      bool cr = false;
      Object* realpredname;
      if (predname->isStructure()) {
	Structure* realpredstr = OBJECT_CAST(Structure*, predname);
	Object* functor = realpredstr->getFunctor()->variableDereference();
	realpredname = realpredstr->getArgument(1)->variableDereference();
	if (functor == AtomTable::minus) {
	  cr = true;
          if (has_stamp) rs = tmp_stamp;
	} else {
	  ca = true;
          if (has_stamp) as = tmp_stamp;
	}
      } else {
	realpredname = predname;
        if (has_stamp) s = tmp_stamp;
      }
      PredLoc loc = predicates->lookUp(OBJECT_CAST(Atom*, realpredname), arity,
				       atoms, code);
      DynamicPredicate* predptr = predicates->getCode(loc).getDynamicPred();
      if (s == -1) s = predptr->GetStamp();
      if (as == -1) as = predptr->GetAssertStamp();
      if (rs == -1) rs = predptr->GetRetractStamp();
      WaitPred* wp = new WaitPred(realpredname, arity, predptr, 
				  s, as, rs, ca, cr);
      wait_preds.push_back(wp);  
    }
  double until_time;
  if (until->isInteger()) 
    {
      until_time = until->getInteger();
      timeout = Timeval(until_time);
    }
  else
    {
      assert(until->isDouble());
      until_time = until->getDouble();
      timeout = Timeval(until_time);
    }
  if (every->isInteger()) 
    {
      retry_timeout = every->getInteger();
      if (retry_timeout != -1)
	timeout = Timeval(retry_timeout);
    }
  else
    {
      assert(every->isDouble());
      retry_timeout = every->getDouble();
    }
}

BlockingWaitObject::~BlockingWaitObject(void)
{
  for (vector<WaitPred*>::iterator iter = wait_preds.begin();
       iter != wait_preds.end();
       iter++)
    {
      delete *iter;
    }
}

void
BlockingWaitObject::update(void)
{
  stamp = code->GetStamp();
  for (vector<WaitPred*>::iterator iter = wait_preds.begin();
       iter != wait_preds.end();
       iter++)
    {
      WaitPred* wp = *iter;
      wp->updateStamps();
    }
}


Object*
BlockingWaitObject::extract_changed_preds(void)
{
  Object* result = AtomTable::nil;
  for (int i = wait_preds.size()-1; i >= 0; i--)
    {
      WaitPred* wp = wait_preds[i];
      Object* annotatedpredobj;
      bool ca = wp->assert_stamp < wp->predptr->GetAssertStamp();
      bool cr = wp->retract_stamp < wp->predptr->GetRetractStamp();
      bool neither = !(wp->check_assert || wp->check_retract);
      if (wp->modified)
	{
	  if ((wp->check_assert) && ca) { 
	    Structure* annotatedpred = getThread()->TheHeap().newStructure(1);
	    annotatedpred->setFunctor(AtomTable::plus);
	    annotatedpred->setArgument(1, wp->predname);
	    annotatedpredobj = annotatedpred;
	  } else  if ((wp->check_retract) && cr) { 
	    Structure*annotatedpred = getThread()->TheHeap().newStructure(1);
	    annotatedpred->setFunctor(AtomTable::minus);
	    annotatedpred->setArgument(1, wp->predname);
	    annotatedpredobj = annotatedpred;
	  } else {
	    annotatedpredobj = wp->predname;
	  }
	  Structure* predstruct = getThread()->TheHeap().newStructure(2);
	  predstruct->setFunctor(AtomTable::divide);
	  predstruct->setArgument(1, annotatedpredobj);
	  predstruct->setArgument(2, getThread()->TheHeap().newInteger(wp->arity));
	  result = getThread()->TheHeap().newCons(predstruct, result);
	  wp->modified = false; // XXXX
	}
    }
  return result;
}

bool BlockingWaitObject::is_unblocked(void)
{
  if (wait_preds.begin() == wait_preds.end())
    return stamp < code->GetStamp();

  for (vector<WaitPred*>::iterator iter = wait_preds.begin();
       iter != wait_preds.end();
       iter++)
    {
      WaitPred* wp = *iter;
      if (wp->check_assert) {
	if (wp->saved_assert_stamp < wp->predptr->GetAssertStamp()) {
	  return true;
	}
      }	else if (wp->check_retract) {
	if (wp->saved_retract_stamp < wp->predptr->GetRetractStamp()) {
	  return true;
	}
      }	else {
	if (wp->stamp < wp->predptr->GetStamp()) {
	  return true;
	}
      }
    }
  return false;
}

void BlockingWaitObject::dump(void)
{
  for (vector<WaitPred*>::iterator iter = wait_preds.begin();
       iter != wait_preds.end();
       iter++)
    {
      WaitPred* wp = *iter;
      cerr << OBJECT_CAST(Atom*, wp->predname)->getName() 
	   << "/" << wp->arity << " " << wp->stamp  << "  " << 
	    wp->assert_stamp  << "  " <<  wp->retract_stamp << endl;
    }
}

bool 
BlockingWaitObject::unblock(Timeval& tout)
{
  Timeval now;

  if (is_unblocked())
    {
      getThread()->getBlockStatus().setRestartWait();
      if (retry_timeout != -1) 
	timeout = Timeval(retry_timeout);

      return true;
    }
  else if (timeout.isForever())
    {
      return false;
    }
  else if (timeout <= now)
    {
      if (retry_timeout != -1) 
	timeout = Timeval(retry_timeout);
      setWakeOnTimeout(retry_timeout == -1);
      getThread()->getBlockStatus().setRestartTime();
      return true;
    }
  else
    { 	 
      Timeval delta(timeout, now);
      if (delta < tout) tout = delta;
      return false;
    }
}
