/*
  CompactCom - Library to easy comunicate with other boards.
  Created by Roman Balyk, February 8, 2022.
*/

#include "Arduino.h"

class ReplyData
{
  public:
    String data="";
    int cmd;
    int from_addr;
};

typedef void (*GeneralFunction) (ReplyData data);

struct Node
{
	GeneralFunction fnc;
  int command;
	Node* next;
	Node* prev;
};

class CompactCom
{
  private:
    int _addr=0;
    Stream *_serial;
    Node* _head = NULL;
  public:
    CompactCom(Stream* serial, int addr);
    void loop();
    ReplyData getData();
    void bind(void (*function)(ReplyData),int cmd);
    void send(int cmd, int addr,String data);
};
