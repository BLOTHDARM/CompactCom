#include "Arduino.h"
#include "CompactCom.h"

CompactCom::CompactCom(Stream* serial,int addr){
  this->_addr = addr;
  this->_serial = serial;
}

void CompactCom::loop()
{
  if(this->_serial->available()){
    ReplyData data;
    data = this->getData();
    if(data.cmd == 0)
      return;
    Node *tmp = _head;
    if(tmp->command == data.cmd)
    {
      tmp->fnc(data);
    }
    tmp = tmp->next;
    while(tmp!=_head){
      if(tmp->command == data.cmd)
      {
        tmp->fnc(data);
      }
      tmp = tmp->next;
    }
  }
}

void CompactCom::bind(void (*function)(ReplyData),int cmd)
{
  Node* n;
  if (!_head)
  {
    _head = new Node;
    _head->fnc = function;
    _head->command = cmd;
    _head->next = _head;
    _head->prev = _head;
    return;
  }
  else
  {
    n = _head;
    Node* newNode = new Node;
    newNode->fnc = function;
    newNode->command = cmd;
    newNode->next = _head;
    newNode->prev = _head->prev;
    _head->prev->next = newNode;
    _head->prev = newNode;
    _head = newNode;
    return;
  }
}

void CompactCom::send(int cmd, int addr,String data){
  this->_serial->write(addr);
  this->_serial->write(cmd);
  this->_serial->write(this->_addr);
  this->_serial->print(data);
}

ReplyData CompactCom::getData(){
  ReplyData data;
  if(this->_serial->available()){
    int addr = this->_serial->read();
    if(this->_addr == addr){
      delay(10);
      int cmd = this->_serial->read();
      int from_addr = this->_serial->read();
      data.cmd = cmd;
      data.from_addr = from_addr;
      while(this->_serial->available())
        data.data+=(char)this->_serial->read();
      return data;
    }
  }
  data.cmd=0;
  return data;
}
