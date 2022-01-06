
#include "thread_qp.h"
#include "tcp_qp.h"

#include "pedro_env.h"
#include "write_support.h"

extern int pedro_port;
extern char* pedro_address;

extern ThreadTable *thread_table;

extern PedroMessageChannel* pedro_channel;

Thread::ReturnValue
Thread::psi_pedro_is_connected()
{
  if (pedro_channel->isConnected())
    return RV_SUCCESS;
  else
    return RV_FAIL;
}

Thread::ReturnValue
Thread::psi_pedro_connect(Object*& port_obj, Object*& addr_obj)
{
  if (pedro_channel->isConnected())
    {
      Warning(Program, "Already connected");
      return RV_FAIL;
    }


  pedro_port = port_obj->variableDereference()->getInteger();
  pedro_address = OBJECT_CAST(Atom*, addr_obj->variableDereference())->getName();
  wordlong ip_address; // = LookupMachineIPAddress(pedro_address);
  if (ip_to_ipnum(pedro_address, ip_address) == -1) {
    Fatal(__FUNCTION__, "host name error");
    return RV_FAIL;
  }
  if (pedro_channel->connect(pedro_port, ip_address))
    return RV_SUCCESS;
  else
    return RV_FAIL;
}

Thread::ReturnValue
Thread::psi_pedro_disconnect()
{
    if (!pedro_channel->isConnected())
    {
      Warning(Program, "Already disconnected");
      return RV_FAIL;
    }
    pedro_channel->disconnect();
    pedro_address = NULL;
    return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_pedro_subscribe(Object *& sub, Object *& id_obj)
{
    if (!pedro_channel->isConnected())
    {
      Warning(Program, "Not connected");
      return RV_FAIL;
    }
    int id = pedro_channel->subscribe(sub->variableDereference());
    if (id == 0) return RV_FAIL;
    id_obj = heap.newInteger(id);
    return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_pedro_unsubscribe(Object*& id_obj, Object *& unsub)
{
  if (!pedro_channel->isConnected())
    {
      Warning(Program, "Not connected");
      return RV_FAIL;
    }
  if (pedro_channel->unsubscribe(id_obj->variableDereference()->getInteger(),
				 unsub->variableDereference()))
    return RV_SUCCESS;
  else
    return RV_FAIL;
}

Thread::ReturnValue
Thread::psi_pedro_notify(Object *& n)
{
  if (!pedro_channel->isConnected())
    {
      Warning(Program, "Not connected");
      return RV_FAIL;
    }
  if (pedro_channel->notify(n->variableDereference()))
    return RV_SUCCESS;
  else
    return RV_FAIL;
}

Thread::ReturnValue
Thread::psi_pedro_register(Object *& reg)
{
  if (!pedro_channel->isConnected())
    {
      Warning(Program, "Not connected");
      return RV_FAIL;
    }
  if (pedro_channel->getName() != NULL)
    {
      Warning(Program, "Already registered");
      return RV_FAIL;
    }
  if (pedro_channel->pedro_register(reg->variableDereference()))
    return RV_SUCCESS;
  else
    return RV_FAIL;
}

Thread::ReturnValue
Thread::psi_pedro_deregister()
{
  if (!pedro_channel->isConnected())
    {
      Warning(Program, "Not connected");
      return RV_FAIL;
    }
  if (pedro_channel->getName() == NULL)
    {
      Warning(Program, "Not registered");
      return RV_FAIL;
    }
  if (pedro_channel->pedro_deregister(pedro_channel->getName()))
    return RV_SUCCESS;
  else
    return RV_FAIL;
}

Thread::ReturnValue
Thread::psi_pedro_is_registered()
{
  if (pedro_channel->getName() == NULL)
    return RV_FAIL;
  else
    return RV_SUCCESS;
}


Thread::ReturnValue
Thread::psi_thread_handle(Object*& handle_obj)
{
  if (!pedro_channel->isConnected())
    {
      Structure* cstr = heap.newStructure(2);
      cstr->setFunctor(AtomTable::colon);
      cstr->setArgument(1, atoms->add(TInfo().Symbol().c_str()));
      cstr->setArgument(2, atoms->add("UnnamedProcess"));
      
      Structure* atstr = heap.newStructure(2);
      atstr->setFunctor(AtomTable::at);
      atstr->setArgument(1, cstr);
      atstr->setArgument(2, atoms->add("localhost"));
      handle_obj = atstr;
      return RV_SUCCESS;
    }
  if (pedro_channel->getName() == NULL)
    {
      Warning(Program, "Not registered");
      return RV_FAIL;
    }
  Structure* cstr = heap.newStructure(2);
  cstr->setFunctor(AtomTable::colon);
  cstr->setArgument(1, atoms->add(TInfo().Symbol().c_str()));
  cstr->setArgument(2, pedro_channel->getName());

  Structure* atstr = heap.newStructure(2);
  atstr->setFunctor(AtomTable::at);
  atstr->setArgument(1, cstr);
  atstr->setArgument(2, pedro_channel->getHost());
  handle_obj = atstr;
  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_pedro_address(Object*& addr_obj)
{
  if (pedro_address == NULL)
    return RV_FAIL;

  addr_obj = atoms->add(pedro_address);
  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_pedro_port(Object*& port_obj)
{
  if (pedro_address == NULL)
    return RV_FAIL;

  port_obj = heap.newInteger(pedro_port);
  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_local_p2p(Object*& thread_obj, Object*& msg_obj)
{
  Object* threadname = thread_obj->variableDereference();
  ThreadTableLoc tid 
    = thread_table->LookupName(OBJECT_CAST(Atom*, threadname)->getName());

  if (tid != (ThreadTableLoc)-1) {
    string m = pedro_write(msg_obj);
    m.append("\n");
    Thread* thread = thread_table->LookupID(tid);
    assert(thread != NULL);
    thread->MessageQueue().push_back(new PedroMessage(m));
  }
  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_set_default_message_thread(Object*& thread_name)
{
  Object* threadname = thread_name->variableDereference();
  
  if (threadname->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }
  if (!threadname->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  thread_table->setDefaultThread(OBJECT_CAST(Atom*, threadname)->getName());
  return RV_SUCCESS;
}

Thread::ReturnValue
Thread::psi_default_message_thread(Object*& thread_name)
{
  thread_name = atoms->add(thread_table->getDefaultThread());
  return RV_SUCCESS;
}
  
