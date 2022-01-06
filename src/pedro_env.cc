#ifdef WIN32
        #include <winsock2.h>
#define _WIN32_WINNT 0x501
        #include <ws2tcpip.h>
        #define _WINSOCKAPI_
        #include <windows.h>
        typedef int socklen_t;

        //We also need to initialise the winsock tcp crud
        WSADATA wsaData;
        WORD wVersionRequested = MAKEWORD( 2, 2 );
        int err = WSAStartup( wVersionRequested, &wsaData );

        #define MSG_DONTWAIT 0
        #include <stdio.h>
        const char* inet_ntop(int af, const void* src, char* dst, int cnt){
 
            struct sockaddr_in srcaddr;
 
            memset(&srcaddr, 0, sizeof(struct sockaddr_in));
            memcpy(&(srcaddr.sin_addr), src, sizeof(srcaddr.sin_addr));
 
            srcaddr.sin_family = af;
            if (WSAAddressToString((struct sockaddr*) &srcaddr, sizeof(struct sockaddr_in), 0, dst, (LPDWORD) &cnt) != 0) {
            DWORD rv = WSAGetLastError();
            printf("WSAAddressToString() : %ld\n",rv);
            return NULL;
         }
        return dst;
      }
#else
        #include <sys/types.h>
        #include <netdb.h>
        #include <sys/socket.h>
        #include <sys/file.h>
        #include <sys/ioctl.h>
        #include <sys/un.h>
        #include <net/if.h>
        #include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif


#include <algorithm>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#include "QuProlog.h"
#include "thread_table.h"
#include "scheduler.h"
#include "io_qp.h"
#include "thread_qp.h"

#include "pedro_env.h"
#include "pedro_token.h"
#include "write_support.h"
#include "objects.h"
#include "tcp_qp.h"

// Required global variables from QP
extern AtomTable* atoms;
extern ThreadTable *thread_table;
extern Scheduler *scheduler;

static const char* p2pmsg_string = "p2pmsg(";
static const char* stream_string = "''";

static const int p2pmsg_string_len = strlen(p2pmsg_string);

// Global variables for Pedro interface.
// static PedroMessageChannel* pedro_channel_ptr = NULL;


void getIPfromaddinfo(char* ip, char* dotted_ip)
{
  struct addrinfo *ailist;
  struct addrinfo hint;
  struct sockaddr_in *sinp;
  const char *addr;
  char abuf[INET_ADDRSTRLEN];

  hint.ai_flags = 0; 
  hint.ai_family = 0;
  hint.ai_socktype = 0;
  hint.ai_protocol = 0;
  hint.ai_addrlen = 0;
  hint.ai_canonname = NULL;
  hint.ai_addr = NULL;
  hint.ai_next = NULL;
  if (getaddrinfo(ip, 0, &hint, &ailist) != 0)
    return;
  if (ailist->ai_family == AF_INET) {
    sinp = (struct sockaddr_in *)ailist->ai_addr;
    addr = inet_ntop(AF_INET, &sinp->sin_addr, abuf, INET_ADDRSTRLEN);
    strcpy(dotted_ip, (char*)addr);
  }
}

Object* parse_basic(Thread* th, AtomTable& atoms, VarMap& vmap, 
		    ObjectsStack& stk, bool remember);
Object* parse_prec50(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember);
Object* parse_prec100(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember);
Object* parse_prec200(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember);
Object* parse_prec400(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember);
Object* parse_prec500(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember);
Object* parse_prec700(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember);
Object* parse_prec1000(Thread* th, AtomTable& atoms, VarMap& vmap, 
		       ObjectsStack& stk, bool remember);
Object* parse_prec1050(Thread* th, AtomTable& atoms, VarMap& vmap, 
		       ObjectsStack& stk, bool remember);
Object* parse_prec1100(Thread* th, AtomTable& atoms, VarMap& vmap, 
		       ObjectsStack& stk, bool remember);

extern int pedro_port;
extern char* pedro_address;

static int curr_token_type = ERROR_TOKEN;
static Object* curr_token = NULL;

void next_token(Thread* th, AtomTable& atoms, VarMap& vmap, bool remember)
{
  curr_token_type = scanner(th, &atoms, &vmap, &curr_token, remember);
}



int parseargs(Thread* th, AtomTable& atoms, VarMap& vmap, 
	      ObjectsStack& stk, bool remember)
{
  if (curr_token_type == CBRA_TOKEN) {
    return 0;
  }
  int num = 0;
  Object* t = parse_prec700(th, atoms, vmap, stk, remember);
  assert(t != NULL);
  stk.push(t);
  num++;
  while (curr_token_type == COMMA_TOKEN) {
    next_token(th, atoms, vmap, remember);
    t = parse_prec700(th, atoms, vmap, stk, remember);
    assert(t != NULL);
    stk.push(t);
    num++;
  }
  return num;
}

Object* parse_basic(Thread* th, AtomTable& atoms, VarMap& vmap, 
		    ObjectsStack& stk, bool remember)
{
  switch (curr_token_type) {
  case ERROR_TOKEN:
  case NEWLINE_TOKEN:
  case CBRA_TOKEN:
  case CSBRA_TOKEN:
  case COMMA_TOKEN:
    assert(false);
    return NULL;
    break;
  case OBRA_TOKEN:
    {
      next_token(th, atoms, vmap, remember);
      Object* t = parse_prec1100(th, atoms, vmap, stk, remember);
      assert(curr_token_type == CBRA_TOKEN);
      next_token(th, atoms, vmap, remember);
      return t;
      break;
    }
  case OSBRA_TOKEN:
    {
      next_token(th, atoms, vmap, remember);
      if (curr_token_type == CSBRA_TOKEN)
	{
	  next_token(th, atoms, vmap, remember);
	  return AtomTable::nil;
	}
      Object* t = parse_prec700(th, atoms, vmap, stk, remember);
      assert(t != NULL);
      Cons* lst = th->TheHeap().newCons();
      lst->setHead(t);
      Cons* lst_tmp = lst;
      while (curr_token_type == COMMA_TOKEN) 
	{
	  next_token(th, atoms, vmap, remember);
	  t = parse_prec700(th, atoms, vmap, stk, remember);
	  assert(t != NULL);
	  Cons* tmp = th->TheHeap().newCons();
	  tmp->setHead(t);
	  lst_tmp->setTail(tmp);
	  lst_tmp = tmp;
	}
      if (curr_token_type == VBAR_TOKEN) {
        next_token(th, atoms, vmap, remember);
        t = parse_prec700(th, atoms, vmap, stk, remember);
        assert(t != NULL);
        lst_tmp->setTail(t);
      }
      else {
        lst_tmp->setTail(AtomTable::nil);
      }
      assert(curr_token_type == CSBRA_TOKEN); 
      next_token(th, atoms, vmap, remember);
      return lst;
    }
    break;
  case TERM_TOKEN:
    {
      Object* t = curr_token;
      next_token(th, atoms, vmap, remember);
      if (t->isAtom() && (curr_token_type == OBRA_TOKEN))
	{
	  next_token(th, atoms, vmap, remember);
	  int arity = parseargs(th, atoms, vmap, stk, remember);
          if (arity == 0) {
            next_token(th, atoms, vmap, remember);
            Structure* compound = th->TheHeap().newStructure(1);
            compound->setFunctor(t);
            compound->setArgument(1, AtomTable::a_d_none_);
            return compound;
          }
	  assert((arity != 0) && (curr_token_type == CBRA_TOKEN));
	  next_token(th, atoms, vmap, remember);
	  Structure* compound = th->TheHeap().newStructure(arity);
	  compound->setFunctor(t);
	  for (int i = arity; i > 0; i--)
	    {
	      compound->setArgument(i, stk.pop());
	    }
	  return compound;
	}
      else
	{
	  return t;
	}
      break;
    }
  default:
    assert(false);
    return curr_token;
    break;
  }
}

Object* parse_prec50(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember)
{
  Object* t1 = parse_basic(th, atoms, vmap, stk, remember);
  if (t1 == NULL) return NULL;
  if (curr_token == AtomTable::colon) {
    next_token(th, atoms, vmap, remember);
    Object* t2 = parse_basic(th, atoms, vmap, stk, remember);
    if (t2 == NULL) return NULL;
    Structure* sterm = th->TheHeap().newStructure(2);
    sterm->setFunctor(AtomTable::colon);
    sterm->setArgument(1, t1);
    sterm->setArgument(2, t2);
    return sterm;
  }
  return t1;
}

Object* parse_prec100(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember)
{
  Object* t1 = parse_prec50(th, atoms, vmap, stk, remember);
  if (t1 == NULL) return NULL;
  if (curr_token == AtomTable::at) {
    next_token(th, atoms, vmap, remember);
    Object* t2 = parse_prec50(th, atoms, vmap, stk, remember);
    if (t2 == NULL) return NULL;
    Structure* sterm = th->TheHeap().newStructure(2);
    sterm->setFunctor(AtomTable::at);
    sterm->setArgument(1, t1);
    sterm->setArgument(2, t2);
    return sterm;
  }
  return t1;
}

Object* parse_prec200(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember)
{
  assert((curr_token_type != ERROR_TOKEN) 
	 && (curr_token_type != NEWLINE_TOKEN));

  if (curr_token == AtomTable::minus) {
    next_token(th, atoms, vmap, remember);
    Object* arg = parse_prec100(th, atoms, vmap, stk, remember);
    if (arg == NULL) return NULL;
    Structure* sterm = th->TheHeap().newStructure(1);
    sterm->setFunctor(AtomTable::minus);
    sterm->setArgument(1, arg);
    return sterm;
  }
  Object* t1 = parse_prec100(th, atoms, vmap, stk, remember);
  if (t1 == NULL) return NULL;
  if (curr_token == AtomTable::power) {
    next_token(th, atoms, vmap, remember);
    Object* t2 = parse_prec100(th, atoms, vmap, stk, remember);
    if (t2 == NULL) return NULL;
    Structure* sterm = th->TheHeap().newStructure(2);
    sterm->setFunctor(AtomTable::power);
    sterm->setArgument(1, t1);
    sterm->setArgument(2, t2);
    return sterm;
  }
  return t1;
}

Object* parse_prec400(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember)
{
  Object* t1 = parse_prec200(th, atoms, vmap, stk, remember);
  if (t1 == NULL) return NULL;
  while ((curr_token == AtomTable::multiply) ||
         (curr_token == AtomTable::divide) ||
         (curr_token == AtomTable::intdivide) ||
         (curr_token == AtomTable::mod) ||
         (curr_token == AtomTable::shiftl) ||
         (curr_token == AtomTable::shiftr)) {
    Object* op = curr_token;
    next_token(th, atoms, vmap, remember);
    Object* t2 = parse_prec200(th, atoms, vmap, stk, remember);
    if (t2 == NULL) return NULL;
    Structure* sterm = th->TheHeap().newStructure(2);
    sterm->setFunctor(op);
    sterm->setArgument(1, t1);
    sterm->setArgument(2, t2);
    t1 = sterm;
  }
  return t1;
}

Object* parse_prec500(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember)
{
  Object* t1 = parse_prec400(th, atoms, vmap, stk, remember);
  if (t1 == NULL) return NULL;
  while ((curr_token == AtomTable::plus) ||
         (curr_token == AtomTable::minus) ||
         (curr_token == AtomTable::bitwiseand) ||
         (curr_token == AtomTable::bitwiseor)) {
    Object* op = curr_token;
    next_token(th, atoms, vmap, remember);
    Object* t2 = parse_prec400(th, atoms, vmap, stk, remember);
    if (t2 == NULL) return NULL;
    Structure* sterm = th->TheHeap().newStructure(2);
    sterm->setFunctor(op);
    sterm->setArgument(1, t1);
    sterm->setArgument(2, t2);
    t1 = sterm;
  }
  return t1;
}

Object* parse_prec700(Thread* th, AtomTable& atoms, VarMap& vmap, 
		      ObjectsStack& stk, bool remember)
{
  Object* t1 = parse_prec500(th, atoms, vmap, stk, remember);
  if (t1 == NULL) return NULL;
  if ((curr_token == AtomTable::equal) || (curr_token == AtomTable::is) ||
      (curr_token == AtomTable::lt) || (curr_token == AtomTable::gt) ||
      (curr_token == AtomTable::le) || (curr_token == AtomTable::ge)) {
    Object* op = curr_token;
    next_token(th, atoms, vmap, remember);
    Object* t2 = parse_prec500(th, atoms, vmap, stk, remember);
    if (t2 == NULL) return NULL;
    Structure* sterm = th->TheHeap().newStructure(2);
    sterm->setFunctor(op);
    sterm->setArgument(1, t1);
    sterm->setArgument(2, t2);
    return sterm;
  }
  return t1;
}

Object* parse_prec1000(Thread* th, AtomTable& atoms, VarMap& vmap, 
		       ObjectsStack& stk, bool remember)
{  
  Object* t1 = parse_prec700(th, atoms, vmap, stk, remember);
  if (t1 == NULL) return NULL;
  if (curr_token_type == COMMA_TOKEN) {
    Object* op = AtomTable::comma;
    next_token(th, atoms, vmap, remember);
    Object* t2 = parse_prec1000(th, atoms, vmap, stk, remember);
    if (t2 == NULL) return NULL;
    Structure* sterm = th->TheHeap().newStructure(2);
    sterm->setFunctor(op);
    sterm->setArgument(1, t1);
    sterm->setArgument(2, t2);
    return sterm;
  }
  return t1;
}

Object* parse_prec1050(Thread* th, AtomTable& atoms, VarMap& vmap, 
		       ObjectsStack& stk, bool remember)
{
  Object* t1 = parse_prec1000(th, atoms, vmap, stk, remember);
  if (t1 == NULL) return NULL;
  if (curr_token == AtomTable::arrow) {
    Object* op = curr_token;
    next_token(th, atoms, vmap, remember);
    Object* t2 = parse_prec1050(th, atoms, vmap, stk, remember);
    if (t2 == NULL) return NULL;
    Structure* sterm = th->TheHeap().newStructure(2);
    sterm->setFunctor(op);
    sterm->setArgument(1, t1);
    sterm->setArgument(2, t2);
    return sterm;
  }
  return t1;
}

Object* parse_prec1100(Thread* th, AtomTable& atoms, VarMap& vmap, 
		       ObjectsStack& stk, bool remember)
{
  Object* t1 = parse_prec1050(th, atoms, vmap, stk, remember);
  if (t1 == NULL) return NULL;
  if (curr_token == AtomTable::semi) {
    Object* op = curr_token;
    next_token(th, atoms, vmap, remember);
    Object* t2 = parse_prec1100(th, atoms, vmap, stk, remember);
    if (t2 == NULL) return NULL;
    Structure* sterm = th->TheHeap().newStructure(2);
    sterm->setFunctor(op);
    sterm->setArgument(1, t1);
    sterm->setArgument(2, t2);
    return sterm;
  }
  return t1;

}

Object* parsePedroTerm(Thread* th, AtomTable& atoms,
		       VarMap& vmap, ObjectsStack& stk, bool remember)
{
  next_token(th, atoms, vmap, remember);
  Object* t = parse_prec1100(th, atoms, vmap, stk, remember);
  if (t == NULL) return NULL;
  assert(curr_token_type == NEWLINE_TOKEN);
  return t;
}

void write_term(Object* term, int prec, ostringstream& strm);

void write_list_tail(Object* tail, ostringstream& strm)
{
  if (tail->isCons())
    {
      strm << ", ";
      Cons* lst = OBJECT_CAST(Cons*, tail);
      write_term(lst->getHead(), 999, strm);
      write_list_tail(lst->getTail()->variableDereference(), strm);
    }
  else if (tail == AtomTable::nil)
    {
      strm << ']';
    }
  else
    {
      strm << '|';
      write_term(tail, 999, strm);
      strm << ']';
    }
}

void get_pre_prec(Object* functor, int& argprec)
{
  if (functor == AtomTable::minus)
    {
      argprec = 200;
    }
}

void write_prefix(Object* functor, Object* arg, int prec, 
		  int argprec, ostringstream& strm)
{
  if (argprec < prec)
    {
      write_term(functor, 999, strm);
      strm << ' ';
      write_term(arg, argprec, strm);
    }
  else
    {
      strm << '(';
      write_term(functor, 999, strm);
      strm << ' ';
      write_term(arg, argprec, strm);
      strm << ')';
    }
}

void get_infix_prec(Object* functor, int& funprec, int& lprec, int & rprec)
{
  if (functor == AtomTable::power)
    {
      funprec = 200;
      lprec = 199;
      rprec = 199;
    }
  else if ((functor == AtomTable::multiply) ||
	   (functor == AtomTable::divide) || 
	   (functor == AtomTable::intdivide) || 
	   (functor == AtomTable::mod) || 
	   (functor == AtomTable::shiftl) || 
	   (functor == AtomTable::shiftr))
    {
      funprec = 400;
      lprec = 400;
      rprec = 399;
    }
  else if ((functor == AtomTable::plus) ||
	   (functor == AtomTable::minus) || 
	   (functor == AtomTable::bitwiseand) || 
	   (functor == AtomTable::bitwiseor))
    {
      funprec = 500;
      lprec = 500;
      rprec = 499;
    }
  else if ((functor == AtomTable::equal) ||
	   (functor == AtomTable::is) || 
	   (functor == AtomTable::lt) || 
	   (functor == AtomTable::gt) || 
	   (functor == AtomTable::le) || 
	   (functor == AtomTable::ge))
    {
      funprec = 700;
      lprec = 699;
      rprec = 699;
    }
  else if (functor == AtomTable::comma)
    {
      funprec = 1000;
      lprec = 999;
      rprec = 1000;
    }
  else if (functor == AtomTable::arrow)
    {
      funprec = 1050;
      lprec = 1049;
      rprec = 1050;
    }
  else if (functor == AtomTable::semi)
    {
      funprec = 1100;
      lprec = 1099;
      rprec = 1100;
    }
  else if (functor == AtomTable::colon)
    {
      funprec = 50;
      lprec = 49;
      rprec = 49;
    }
  else if (functor == AtomTable::at)
    {
      funprec = 200;
      lprec = 199;
      rprec = 199;
    }
}

void write_infix(Object* functor, Object* larg, Object* rarg, int prec, 
		 int funprec, int leftprec, int rightprec, ostringstream& strm)
{
  if (funprec <= prec)
    {
      write_term(larg, leftprec, strm);
      strm << ' ';
      write_term(functor, 999, strm);
      strm << ' ';
      write_term(rarg, rightprec, strm);
    }
  else
    {
      strm << '(';
      write_term(larg, leftprec, strm);
      strm << ' ';
      write_term(functor, 999, strm);
      strm << ' ';
      write_term(rarg, rightprec, strm);
      strm << ')';
    }
}

void write_infix_comma(Object* larg, Object* rarg, int prec, 
		       ostringstream& strm)
{
  if (1000 <= prec)
    {
      write_term(larg, 999, strm);
      strm << " , ";
      write_term(rarg, 1000, strm);
    }
  else
    {
      strm << '(';
      write_term(larg, 999, strm);
      strm << " , ";
      write_term(rarg, 1000, strm);
      strm << ')';
    }
}

void write_structure(Structure* str, int arity, ostringstream& strm)
{
  write_term(str->getFunctor(), 999, strm);
  Object* arg = str->getArgument(1)->variableDereference();
  if (arg == AtomTable::a_d_none_) {
    strm << "()";
  } else {
    strm << '(';
    for (int i = 1; i <arity; i++)
      {
        write_term(str->getArgument(i), 999, strm);
        strm << ", ";
      }
    write_term(str->getArgument(arity), 999, strm);
    strm << ')';
  }
}

void write_term(Object* term, int prec, ostringstream& strm)
{
  term = term->variableDereference();
  
  switch (term->tTag())
    {
    case Object::tShort:
    case Object::tLong:
      strm << term->getInteger();
      break;
    case Object::tDouble:
      {
	double d = term->getDouble();
	char buff[20];
	sprintf(buff, "%g", d);
	if (strpbrk(buff, ".e") == NULL) {
	  strcat(buff, ".0");
	}
	strm << buff; 
	break;
      }
    case Object::tAtom:
      {
	writePedroAtom(strm, term);
	break;
      }
    case Object::tString:
      {
	const char *s = OBJECT_CAST(StringObject*, term)->getChars();
	string thechars(s);
	addEscapes(thechars, '"');
	strm << '"';
	strm << thechars;
	strm << '"';
	break;
      }
    case Object::tVar:
      {
	Variable* var = OBJECT_CAST(Variable*, term);

	if (var->hasExtraInfo() && var->getName() != NULL) {
	  strm << var->getName()->getName();
	}
	else {
	  strm << '_' << (wordptr)var;
	}
	break;
      }
    case Object::tCons:
      {
	strm << '[';
	Cons* lst = OBJECT_CAST(Cons*, term);
	write_term(lst->getHead(), 999, strm);
	write_list_tail(lst->getTail()->variableDereference(), strm);
	break;
      }
    case Object::tStruct:
      {
	Structure* str = OBJECT_CAST(Structure*, term);
	int arity = str->getArity();
	if (arity > 2)
	  {
	    write_structure(str, arity, strm);
	  } 
	else if (arity == 1)
	  {
	    int argprec = -1;
	    Object* functor = str->getFunctor()->variableDereference();
	    get_pre_prec(functor, argprec);
	    if (argprec < 0)
	      {
		write_structure(str, 1, strm);
	      }
	    else
	      {
		Object* arg = str->getArgument(1)->variableDereference();
		write_prefix(functor, arg, prec, argprec, strm);
	      }
	  }
	else
 	  {
	    Object* functor = str->getFunctor()->variableDereference();
	    if (functor == AtomTable::comma)
	      {
		Object* larg = str->getArgument(1)->variableDereference();
		Object* rarg = str->getArgument(2)->variableDereference();
		write_infix_comma(larg, rarg, prec, strm);
	      }
	    else
	      {
		int funprec = -1;
		int leftprec = -1;
		int rightprec = -1;
		get_infix_prec(functor, funprec, leftprec, rightprec);
		if (funprec < 0)
		  {
		    write_structure(str, 2, strm);
		  }
		else
		  {
		    Object* larg = str->getArgument(1)->variableDereference();
		    Object* rarg = str->getArgument(2)->variableDereference();
		    write_infix(functor, larg, rarg, prec, funprec, leftprec, rightprec, strm);
		  }
	      }
	  }
	break;
      }
    default:
      assert(false);
    }

}

void 
PedroMessage::constructMessage(Object*& sender, Object*& msgterm,
			       Thread& thread, AtomTable& atoms,
			       bool rn)
{
  char buff[1026];
  strcpy(buff, msg.c_str());
  int size = msg.length();
  buff[size+1] = '\0';
  ObjectsStack stk(1024);
  VarMap varMap;


  set_buffstate(buff, size+2);
  Object* term = parsePedroTerm(&thread, atoms, varMap, stk, rn); 
  delete_buffstate();



  if (term == NULL) {
    sender = AtomTable::semi;
    msgterm = AtomTable::semi;
    return;
  }
  if (!term->isStructure()) {
    sender = atoms.add("pedro");
    msgterm = term;
    return;
  }
  Structure* sterm = OBJECT_CAST(Structure*, term);
  if (sterm->getFunctor() == atoms.add("p2pmsg")) {
    assert(sterm->getArity() == 2);
    sender = sterm->getArgument(1);
    msgterm = sterm->getArgument(2);
  }
  else {
    sender = atoms.add("pedro");
    msgterm = term;
  }
}

void
PedroMessageChannel::updateFDSETS(fd_set* rfds, fd_set* wfds, int& max_fd)
{
  if (fd == -1) return;

  if (fd > max_fd) max_fd = fd;
  FD_SET(fd, rfds);
}

void
PedroMessageChannel::readMessages()
{
  size_t pos = in.find('\n');
  while (pos != string::npos)
    {
      string m = in.substr(0, pos + 1);
      in.erase(0, pos+1);
      size_t sppos = m.find(' ');
      assert(sppos != string::npos);
      int id = atoi(m.c_str());
      m.erase(0, sppos+1);
      pushMessage(id, m);
      pos = in.find('\n');
    }
}

bool 
PedroMessageChannel::ShuffleMessages(void)
{
  if (fd == -1) return false;

  bool new_msg = false;
  timeval tv = { 0, 0 };
  fd_set fds;

  while (true)
    {
      FD_ZERO(&fds);
      FD_SET(fd, &fds);
      int result = select(fd + 1, &fds, (fd_set *) NULL, (fd_set *) NULL, &tv);
      if (!result || !FD_ISSET(fd, &fds)) return new_msg;
      char buff[1101];
      // WIN CHANGE ssize_t size = read(fd, buff, 1100);
      ssize_t size = recv(fd, buff, 1100, 0);
      if (size == 0) {
        Warning(Program, "Pedro Server Closed Connection");
        disconnect();
        break;
      }
      buff[size] = '\0';
      in.append(buff);
      new_msg = true;
      readMessages();
    }
  return new_msg;
}

void
PedroMessageChannel::clear_ack()
{
  struct timeval timeout = { 0, 0};
  fd_set rfds;
  char buff[32];
  while (1) {
    FD_ZERO(&rfds);
    FD_SET(ack_fd, &rfds);
    int result = select(ack_fd+1, &rfds, NULL, NULL, &timeout);
    if (result > 0) {
      //cerr << "removing acks" << endl;
      recv(ack_fd, buff, 30, 0);
    } else {
      break;
    }
  }
}
int
PedroMessageChannel::get_ack()
{
  char buff[32];
  int size;
  int offset = 0;
  while (1) {
    size = recv(ack_fd, buff + offset, 30 - offset, 0);
    offset += size;
    if (offset > 25) {
      fprintf(stderr, "Can't get ack\n");
      exit(1);
    }
    if (buff[offset-1] == '\n') {
      buff[offset] = '\0';
      break;
    }
  }
  return atoi(buff);
}

int
PedroMessageChannel::subscribe(Object* t)
{
  clear_ack();
  send(t);
  int id = get_ack();
  if (id != 0) attach_subscription(id, t);
  return id;
}

void
PedroMessageChannel::attach_subscription(int id, Object* t)
{
  t = t->variableDereference();
  assert(t->isStructure());
  Structure* st = OBJECT_CAST(Structure*, t);
  int tid = st->getArgument(3)->variableDereference()->getInteger();
  list<int>& tid_list = thread_subs[tid];
  tid_list.push_back(id);
}


void
PedroMessageChannel::pushMessage(int id, string m)
{
  ThreadTable& thread_table = getThreadTable();
  ThreadTableLoc tid = id;
  string thread_name;
  string::size_type loc = m.find(p2pmsg_string, 0);
  if (loc == 0) {
    // p2p msg found - get the thread name
    string::size_type loc_comma1 =  m.find(',', loc);
    assert(loc_comma1 != string::npos);
    loc =  m.find('@', p2pmsg_string_len);
    string::size_type loc_colon =  m.find(':', p2pmsg_string_len);
    if ((loc < loc_comma1) && (loc_colon < loc)) {
      // has thread name
      // so strip off trailing spaces
      int i = loc_colon-1;
      while (m.at(i) == ' ') i--;
      // and leading spaces
      int j = p2pmsg_string_len;
      while (m.at(j) == ' ') j++;
      thread_name = m.substr(j, i-j+1);
      // if the thread name is '' then this is message stream
      // message
      if (thread_name == stream_string) {
	string::size_type loc_comma2 =  m.find(',', loc_comma1 + 1);
	assert(loc_comma2 != string::npos);
	string from_addr;
	// copy the address part removing spaces
	for (string::size_type i = loc_comma1+1; i < loc_comma2; i++) {
	  if (m.at(i) != ' ') from_addr.push_back(m.at(i));
	}
	// Now get the string part - the message argument should be a string
	// starting and ending with "
	string::size_type loc_quote1 =  m.find('"', loc_comma2);
	if (loc_quote1 == string::npos) return;
	string::size_type loc_quote2 =  m.find_last_of('"');
	if (loc_quote2 == string::npos) return;
	if (loc_quote1 >= loc_quote2) return;
	string message =  m.substr(loc_quote1+1, loc_quote2 - loc_quote1 - 1);
	removeEscapes(message, '"');
	iom.updateStreamMessages(from_addr, message);
	return;
      }
    } else {
      thread_name = thread_table.getDefaultThread();
    }
    // So this is a p2p message that is not being used as a message stream
    // erase the to address for this string because the recipient knows
    // who they are
    string::size_type loc_comma =  m.find(',', p2pmsg_string_len);
    assert(loc_comma != string::npos);
    m.erase(p2pmsg_string_len, loc_comma - p2pmsg_string_len + 1);

    // is the thread name a quoted atom?
    char first_char = thread_name[0];
    if (first_char == '\'') {
      thread_name.erase(0,1);
      thread_name.erase(thread_name.length()-1);
    }

    if (isupper(first_char) || first_char == '_') {
      for (word32 i = 0; i < thread_table.Size(); i++) {
        Thread* thread = thread_table.LookupID(i);
        if (thread != NULL) {
          thread->MessageQueue().push_back(new PedroMessage(m));
        }
      }
      return;
    }
    tid = thread_table.LookupName(thread_name.c_str());
    if (tid == (ThreadTableLoc) -1)
      return;

  }
  if (!thread_table.IsValid(tid)) return;

  Thread* thread = thread_table.LookupID(tid);
  if (thread != NULL) {
    thread->MessageQueue().push_back(new PedroMessage(m));
  }
}

bool
PedroMessageChannel::unsubscribe(int tid, Object* t)
{
  t = t->variableDereference();
  assert(t->isStructure());
  Structure* st = OBJECT_CAST(Structure*, t);
  int id = st->getArgument(1)->variableDereference()->getInteger();

  list<int>::iterator iter;
  list<int>& entry = thread_subs[tid];
  iter = find(entry.begin(), entry.end(), id);
  if (iter == entry.end()) return false;
  clear_ack();
  send(t);
  int ack = get_ack();
  if (ack == id) {
    entry.erase(iter);
    return true;
  }
  return false;
}

bool
PedroMessageChannel::notify(Object* t)
{
  #ifdef WIN32
  clear_ack();
  #else
  char buff[32];
  recv(ack_fd, buff, 30, MSG_DONTWAIT);
  #endif
  //clear_ack();
  send(t);
  return true;
}

void
PedroMessageChannel::send(Object* t)
{
  ostringstream strm;
  write_term(t, 1200, strm);
  strm << '\n';
  send(strm.str());
}

string pedro_write(Object* t)
{
  ostringstream strm;
  write_term(t, 1200, strm);
  return strm.str();
}

void
PedroMessageChannel::send(string s)
{
  size_t len = s.length();
  
  // WIN CHANGE size_t num_written = write(fd, s.c_str(), len);
  size_t num_written = ::send(fd, s.c_str(), len, 0);
  while (num_written != len)
    {
      #ifdef WIN32
      if ((int)num_written == SOCKET_ERROR) {
        cerr << "Socket Error in pedro send" << endl;
        return;
      }
      #endif
      s.erase(0, num_written);
      fd_set fds;
      FD_ZERO(&fds);
      FD_SET(fd, &fds);
      select(fd + 1, (fd_set *) NULL, &fds, (fd_set *) NULL, NULL);
      assert(s.length() == (len - num_written));
      len = s.length();
      num_written = write(fd, s.c_str(), len);
    }
      
}

void 
PedroMessageChannel::delete_subscriptions(int tid)
{
  list<int>::iterator iter;
  list<int>& entry = thread_subs[tid];
  while (entry.size() > 0)
  {
    int id = entry.front();
    ostringstream strm;
    strm << "unsubscribe(" << id << ")\n";
    string s = strm.str();
  clear_ack();
    send(s); 
    get_ack();
    entry.pop_front();
  } 
}


bool 
PedroMessageChannel::connect(int pedro_port, wordlong ip_address)
{
 
  // Create a socket to get info
  int info_fd = ::socket(AF_INET, SOCK_STREAM, 0); 
  u_short port = ntohs(pedro_port);
  if (!do_connection(info_fd, port, ip_address)) {
    close(info_fd);
    return false;
  }
  // read info
  char infobuff[1024];
  int isize;
  int ioffset = 0;
  while (1) {
    isize = recv(info_fd, infobuff + ioffset, 1000 - ioffset, 0);
    ioffset += isize;
    if (ioffset > 1000) {
      fprintf(stderr, "Can't get info\n");
      close(info_fd);
      exit(1);
    }
    if (infobuff[ioffset-1] == '\n') {
      infobuff[ioffset] = '\0';
      break;
    }
  }
  close(info_fd);
  int ack_port, data_port;
  char ipstr[20];
  if (sscanf(infobuff, "%s %d %d", ipstr, &ack_port, &data_port) != 3) {
    fprintf(stderr, "Can't read ip and ports\n");
    exit(1);
  }
  ack_port = htons((unsigned short)ack_port);
  data_port = htons((unsigned short)data_port);
  wordptr ipaddr = inet_addr(ipstr);
  //inet_aton(ipstr, &ipaddr);

  // Create a socket connection for ack
  ack_fd = ::socket(AF_INET, SOCK_STREAM, 0); 
  if (!do_connection(ack_fd, ack_port, ipaddr)) {
    close(ack_fd);
    return false;
  }


  // get the client ID
  u_int id = (u_int)get_ack();

  // create data socket
  fd = ::socket(AF_INET, SOCK_STREAM, 0);
  if (!do_connection(fd, data_port, ipaddr)) {
    close(ack_fd);
    close(fd);
    return false;
  }


  // send the client ID on data socket
  ostringstream strm;
  strm << id << "\n";
  string st = strm.str();
  int len = st.length();
  // WIN CHANGE int num_written = write(fd, st.c_str(), len);
  int num_written = ::send(fd, st.c_str(), len, 0);
  if (num_written != len) {
    fprintf(stderr, "Pedro Connect: Can't send ID\n");
    exit(1);
  }
  // read flag on data socket
  char buff[32];
  int size;
  int offset = 0;
  while (1) {
    size = recv(fd, buff + offset, 30 - offset, 0);
    offset += size;
    if (offset > 25) {
      fprintf(stderr, "Can't get flag\n");
      exit(1);
    }
    if (buff[offset-1] == '\n') {
      buff[offset] = '\0';
      break;
    }
  }

    // figure out my IP address
  //wordlong ip_num;
  //char ip_name[100];
  struct sockaddr_in add;
  memset(&add, 0, sizeof(add));
  socklen_t addr_len = sizeof(add);
  getsockname(ack_fd, (struct sockaddr *)&add, &addr_len);
  strcpy(ipstr, inet_ntoa(add.sin_addr));
  host = atoms->add(ipstr);
  // if (ip_to_ipnum(ipstr, ip_num) == -1 ||
  //     ipnum_to_ip(ip_num, ip_name) == -1)  
  //   {
  //     // we can't look up name given address so just use dotted IP
  //     host = atoms->add(ipstr);
  //   } 
  // else 
  //   {
  //     host = atoms->add(ip_name);
  //     /*
  //       // check if we can look up the same IP from hostname 
  //       //hostent *hp2 = gethostbyname(hp->h_name);
  //       //cerr << hp->h_name << " " << hp2->h_name << endl;
  //       //if ((hp2 == NULL) or !streq(hp->h_name, hp2->h_name))
  //       char *str, *token, *saveptr, *lasttoken;
  //       int num;
  //       // If hp->h_name does not really do a DNS lookup but
  //       // succeeds then it must be the hostname which is 
  //       // either hostname or hostname.local
  //       char hname[100];
  //       gethostname(hname, 100);
  //       char hname_local[100];
  //       strcpy(hname_local, hname);
  //       strcat(hname_local, ".local");
  //       if (streq(hp->h_name, hname) || streq(hp->h_name,hname_local))
  //         {
  //           // no - so use IP address
  //           host = atoms->add(ipstr);
  //         }
  //       else
  //         {
  //           host = atoms->add(hp->h_name);
  //         }

  //     */
  //     }

  // buff now contains flag - test if "ok\n"
  return (strcmp(buff, "ok\n") == 0);
}

/* disconnect */
void 
PedroMessageChannel::disconnect()
{
  close(ack_fd);
  close(fd);
  fd = -1; 
  ack_fd = -1;
}


bool
PedroMessageChannel::pedro_register(Object* regname)
{
  ostringstream strm;
  strm << "register(" << OBJECT_CAST(Atom*, regname)->getName() << ")\n";
  string s = strm.str();
  clear_ack();
  send(s);

  if (get_ack() == 0) return false;
  name = regname;
  return true;
}

bool
PedroMessageChannel::pedro_deregister(Object* regname)
{
  ostringstream strm;
  strm << "deregister(" << OBJECT_CAST(Atom*, regname)->getName() << ")\n";
  string s = strm.str();
  clear_ack();
  send(s);

  if (get_ack() == 0) return false;
  name = NULL;
  return true;
}
