# CompactCom
 Library for easy command based communication


CompactCom provide tools which will help you set up command based communication

* Support any **Stream** based comunication classes.
* Up to 255 devices
* Up to 254 commands (command #0 reserved)


## How It Works

1. One board send packet wich contains address, command,sender address and packet
2. Another board parce it and run binded function


## Usage
You can use any **Stream** based classes for comunication (f.e. Serial or SoftwareSerial) 

### Configuring

Constructor need 2 arguments: Stream memory address and device address.

<details><summary><b>Show example</b></summary>

```diff
CompactCom nodeCom(&Serial,'1');
```
</details>

### Command binds
Use method ```bind()``` if you want to bind your function with some command
```bind()``` takes two arguments: function name and command


<details><summary><b>Show example</b></summary>

```diff
void getLedStateRes(ReplyData data){
  Serial.println("Led get result: " + data.data);
}

void setLedStateRes(ReplyData data){
  Serial.println("Led set result: " + data.data);
}

void setup(){
  mySerial.begin(9600);
  Serial.begin(9600);
  nodeCom.bind(setLedStateRes,10);
  nodeCom.bind(getLedStateRes,11);
}
```
</details>

Your will be started only from ```loop()``` method. So place it in each loop


<details><summary><b>Show example</b></summary>

```diff
void loop(){
  nodeCom.loop();
}
```
</details>
