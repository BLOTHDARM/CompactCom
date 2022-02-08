#include <CompactCom.h>
#include <Arduino.h>
#include <SoftwareSerial.h>


SoftwareSerial mySerial(6, 7);
CompactCom nodeCom(&mySerial,'1');


void setLedStateRes(ReplyData data){
  Serial.println("Led set result: " + data.data);
}

void getLedStateRes(ReplyData data){
  Serial.println("Led get result: " + data.data);
}

void setup(){
  Serial.begin(9600);
  mySerial.begin(9600);
  nodeCom.bind(setLedStateRes,10);
  nodeCom.bind(getLedStateRes,11);
}

void loop(){
  nodeCom.loop();
  if(Serial.available()){
    String temp="";
    delay(10);
    while(Serial.available())
        temp+=(char)Serial.read();
    if(temp=="on\n"){
      Serial.println("start");
      nodeCom.send(10,'2',"HIGH");
      return;
    }
    if(temp=="off\n"){
      nodeCom.send(10,'2',"LOW");
      return;
    }
    if(temp=="state\n"){
      nodeCom.send(11,'2',"get");
      return;
    }
  }
}
