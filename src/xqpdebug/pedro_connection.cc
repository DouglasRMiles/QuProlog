
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/utsname.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include "pedro_connection.h"
#include <string.h>

#include "../tcp_qp.h"

const char *Program = "xqpdebug";

int read_from_socket(int fd, char* buff)
{  
  int size;
  int offset = 0;
  while (1) {
    size = recv(fd, buff + offset, 30 - offset, 0);
    offset += size;
    if (offset > 25) {
      return 1;
    }
    if (buff[offset-1] == '\n') {
      buff[offset] = '\0';
      break;
    }
  }
  return 0;
}




bool needsQuotes(string& str)
{
  if (str == "") return true;
  if ((str == "[]") || (str == ";")) return false;

  string::size_type pos = str.find_first_of("abcdefghijklmnopqrstuvwxyz");

  if (pos == 0) {
    pos = str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789");
    return (pos != string::npos);
  }
  return (str.find_first_not_of("#$&*+-./:<=>?@^~\\") != string::npos);
}

void addQuotes(string& str)
{
  if (needsQuotes(str)) {
    str.append("'");
    str.insert(0, "'");
  }
}

PedroConnection::PedroConnection(string me, string other, 
				 int port, u_long ip) :
  my_address(me), other_address(other)
{
  addQuotes(my_address);
  addQuotes(other_address);


  // Create a socket to get info
  int info_fd = ::socket(AF_INET, SOCK_STREAM, 0); 
  u_short p_port = ntohs(port);
  if (!do_connection(info_fd, p_port, ip)) {
    close(info_fd);
    return;
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
  unsigned long ipaddr = inet_addr(ipstr);

  // Create a socket connection for ack
  ack_fd = ::socket(AF_INET, SOCK_STREAM, 0); 
  if (!do_connection(ack_fd, ack_port, ipaddr)) {
    close(ack_fd);
    exit(1);
  }

  // get the client ID
  u_int id = (u_int)get_ack();


  // create data socket
  data_fd = ::socket(AF_INET, SOCK_STREAM, 0);
  if (!do_connection(data_fd, data_port, ipaddr)) {
    close(ack_fd);
    close(data_fd);
    exit(1);
  }

  // send the client ID on data socket
  ostringstream strm;
  strm << id << "\n";
  string st = strm.str();
  int len = st.length();
  // WIN CHANGE int num_written = write(fd, st.c_str(), len);
  int num_written = ::send(data_fd, st.c_str(), len, 0);
  if (num_written != len) {
    fprintf(stderr, "Pedro Connect: Can't send ID\n");
    exit(1);
  }
  // read flag on data socket
  char buff[32];
  int size;
  int offset = 0;
  while (1) {
    size = recv(data_fd, buff + offset, 30 - offset, 0);
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
  // buff now contains flag - test if "ok\n"
  if (strcmp(buff, "ok\n") != 0){
    cerr << "Can't complete connection" << endl;
    close(ack_fd);
    close(data_fd);
    exit(1);
  }

  // figure out my IP address
  struct sockaddr_in add;
  memset(&add, 0, sizeof(add));
  socklen_t addr_len = sizeof(add);
  
  getsockname(ack_fd, (struct sockaddr *)&add, &addr_len);
  strcpy(ipstr, inet_ntoa(add.sin_addr));
  struct in_addr in = add.sin_addr;
  hostent *hp = gethostbyaddr((char *) &in, sizeof(in), AF_INET);
  if (hp == NULL) 
    {
      // we can't look up name given address so just use dotted IP
      host = ipstr;
    } 
  else 
    {
      // check if we can look up the same IP from hostname 
      hostent *hp2 = gethostbyname(hp->h_name);
      if ((hp2 == NULL) || (strcmp(hp->h_name, hp2->h_name) != 0))
        {
          // no - so use IP address
          host = ipstr;
        }
      else
        {
          host = hp->h_name;
        }
    }

  ostringstream s1;
  s1.str("");
  s1 << "register(" << my_address << ")\n";
  if (!send(s1.str())) {
    cerr << "Can't register" << endl;
    exit(1);
  }

  addQuotes(host);

}

bool 
PedroConnection::send(string s)
{
  size_t len = s.length();
  
  size_t num_written = write(data_fd, s.c_str(), len);
  
  while (num_written != len)
    {
      s.erase(0, num_written);
      fd_set fds;
      FD_ZERO(&fds);
      FD_SET(data_fd, &fds);
      select(data_fd + 1, (fd_set *) NULL, &fds, (fd_set *) NULL, NULL);
      assert(s.length() == (len - num_written));
      len = s.length();
      num_written = write(data_fd, s.c_str(), len);
    }
  return (get_ack() != 0);
}

int 
PedroConnection::get_ack()
{
  char buff[32];
  int size;
  int offset = 0;
  while (1) {
    size = recv(ack_fd, buff + offset, 30 - offset, 0);
    offset += size;
    if (offset > 25) {
      cerr << "Can't get ack" << endl;
      exit(1);
    }
    if (buff[offset-1] == '\n') {
      buff[offset] = '\0';
      break;
    }
  }
  return atoi(buff);
}

void addEscapes(string& str)
{
  string tmp;
  for (string::iterator iter = str.begin(); iter != str.end(); iter++)
    {
      char c = *iter;
      switch ((int)c)
	{
	case 7:  // \a
	  tmp.push_back('\\');
	  tmp.push_back('a');
	  break;
	case 8:  // \b
	  tmp.push_back('\\');
	  tmp.push_back('b');
	  break;
	case 9:  // \t
	  tmp.push_back('\\');
	  tmp.push_back('t');
	  break;
	case 10:  // \n
	  tmp.push_back('\\');
	  tmp.push_back('n');
	  break;
	case 11:  // \v
	  tmp.push_back('\\');
	  tmp.push_back('v');
	  break;
	case 12:  // \f
	  tmp.push_back('\\');
	  tmp.push_back('f');
	  break;
	case 13:  // \r
	  tmp.push_back('\\');
	  tmp.push_back('r');
	  break;
	case 92:  
	  tmp.push_back('\\');
	  tmp.push_back('\\');
	  break;
	default:
	  if (c == '"')
	    {
	      tmp.push_back('\\');
	      tmp.push_back(c);
	    }
	  else
	      tmp.push_back(c);
	  break;
	}
    }
  str = tmp;
}

bool 
PedroConnection::send_p2p(string s)
{
  addEscapes(s);
  ostringstream strm;
  strm << "p2pmsg('':"
       << other_address
       << "@"
       << host
       << ", "
       << "'':"
       << my_address
       << "@"
       << host
       << ", \""
       << s
       << "\")\n";
  return send(strm.str());
}

bool 
PedroConnection::msgAvail()
{
      fd_set fds;
      timeval tv = { 0, 0 };
      FD_ZERO(&fds);
      FD_SET(data_fd, &fds);
      int ret = select(data_fd + 1, &fds, (fd_set *) NULL,  
			(fd_set *) NULL, &tv);
      if (ret == 1) {
	char buff[1101];
	ssize_t size = read(data_fd, buff, 1100);
	buff[size] = '\0';
	in.append(buff);
	return true;
      }
      return false;
}


void removeEscapes(string& str)
{
  string tmp;
  for (string::iterator iter = str.begin(); iter != str.end(); iter++)
    {
      char c = *iter;
      if (c == '\\') {
	iter++;
	assert(iter != str.end());
	c = *iter;
	switch ((int)c)
	  {
	  case 'a': 
	    tmp.push_back('\a');
	    break;
	  case 'b':  
	    tmp.push_back('\b');
	    break;
	  case 't':  
	    tmp.push_back('\t');
	    break;
	  case 'n':  
	    tmp.push_back('\n');
	    break;
	  case 'v': 
	    tmp.push_back('\v');
	    break;
	  case 'f':  
	    tmp.push_back('\f');
	    tmp.push_back('f');
	    break;
	  case 'r': 
	    tmp.push_back('\r');
	    break;
	  case '\\':  
	    tmp.push_back('\\');
	    break;
	  default:
	    if (c == '"')
	      {
		tmp.push_back(c);
	      }
	    else
	      {
		assert(false);
	      }
	    break;
	  }
      }
      else {
	tmp.push_back(c);
      }
    }
  str = tmp;
}

bool
PedroConnection::getMsg(string& msg)
{
  size_t pos = in.find('\n');
  if (pos != string::npos)
    {
      string m = in.substr(0, pos + 1);
      in.erase(0, pos+1);
      size_t loc_quote1 = m.find('"');
      size_t loc_quote2 = m.find_last_of('"');
      msg =  m.substr(loc_quote1+1, loc_quote2 - loc_quote1 - 1);
      removeEscapes(msg);
      return true;
    }
  return false;
}
