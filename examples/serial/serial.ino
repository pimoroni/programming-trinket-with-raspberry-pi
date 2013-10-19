#include <SoftwareSerial.h>
#include "serial.h" // Our function prototypes

#define MY_PIN 1 // Built-in red LED

SoftwareSerial Serial(3,4);

void setup(){
  pinMode(MY_PIN,OUTPUT);
  Serial.begin(9600);
  Serial.println("Hello World");
}

void loop(){
  if(Serial.available())
  {
    int received = Serial.parseInt();
    Serial.println("Got Data!");
    blink(received);
  }
}

void blink(unsigned int delayms){
  digitalWrite(MY_PIN,HIGH);
  delay(delayms);
  digitalWrite(MY_PIN,LOW);
  delay(delayms);
}
