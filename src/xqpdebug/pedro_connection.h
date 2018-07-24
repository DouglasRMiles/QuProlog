
#ifndef	XPEDRO_ENV_H
#define	XPEDRO_ENV_H

#include <string>

using namespace std;

class PedroConnection
{
private:
  string my_address;
  string other_address;
  string host;
  int ack_fd;
  int data_fd;
  string in;

  int get_ack();

public:
  PedroConnection(string me, string other, int port, u_long ip);

  int getAckFD() { return ack_fd; }
  int getDataFD() { return data_fd; }

  bool send(string s);

  bool send_p2p(string s);

  bool msgAvail();

  bool getMsg(string& msg);

};

#endif

