#ifndef	PEDRO_ENV_H
#define	PEDRO_ENV_H

#include <string>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include "heap_qp.h"
#include "messages.h"

string pedro_write(Object* t);

class IOManager;

class PedroMessage : public Message
{
 private:
  string msg;

 public:
  PedroMessage(string m) : Message(), msg(m) {}

  ~PedroMessage() {}

  void constructMessage(Object*& sender, Object*& msgterm,
				Thread&, AtomTable&,
				bool remember_names = false);
};

class VarMap
{
 private:
  Object** pairs;
  int top;
  
 public:
  VarMap() { pairs = new Object*[2048]; top = 0; }
  ~VarMap() { delete pairs; }
  
  Object* getVar(Heap* heap, Object* name)
    {
      for (int i = 0; i < top; i += 2)
	{
	  if (pairs[i] == name) return pairs[i+1];
	}
      Object* var = heap->newVariable();
      pairs[top] = name;
      pairs[top+1] = var;
      top += 2;
      return var;
    }
};


class PedroMessageChannel : public MessageChannel
{
 private:
  int fd;
  IOManager& iom;
  int ack_fd;
  string in;
  list<int>* thread_subs;
  Object* name;
  Object* host;
  Heap* pedroHeap;

 public:
  bool ShuffleMessages(void);
  void updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd);
  void processTimeouts(Timeval& timeout) {};

  explicit PedroMessageChannel(ThreadTable& t, IOManager& i)
    : MessageChannel(t), fd(-1), iom(i) 
    { 
      thread_subs = new list<int>[t.Size()]; 
      name = NULL;
      host = NULL;
      pedroHeap = new Heap("Pedro Heap", 1024);
    }
  
  ~PedroMessageChannel() { delete [] thread_subs; }

  bool connect(int port, wordlong ip);
  void disconnect();

  int subscribe(Object* t);
  bool unsubscribe(int tid, Object* t);
  void delete_subscriptions(int tid);
  void attach_subscription(int id, Object* t);
  bool notify(Object* t);
  bool isConnected() { return fd != -1; }
  bool pedro_register(Object* regname);
  bool pedro_deregister(Object* regname);
  Object* getName() { return name; }
  Object* getHost() { return host; }
  void send(Object* t);
  void send(string s);
  int get_ack();
  void clear_ack();

 private:
  void pushMessage(int id, string m);
  void readMessages();
};



#endif
