#include <CompactCom.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

#define LED 13

bool led_state=true;

CompactCom nodeCom(&Serial,'2');

void setLedState(ReplyData data){
  String temp = data.data;
  led_state=(temp=="HIGH") ? 1: 0;
  digitalWrite(LED, led_state);
  nodeCom.send(10,data.from_addr,"OK");
}

void getLedState(ReplyData data){
  nodeCom.send(11,data.from_addr,String(led_state));
}

void setup(){
  pinMode(LED,OUTPUT);
  digitalWrite(LED,led_state);
  Serial.begin(9600);
  nodeCom.bind(setLedState,10);
  nodeCom.bind(getLedState,11);
}

void loop(){
  nodeCom.loop();
}
