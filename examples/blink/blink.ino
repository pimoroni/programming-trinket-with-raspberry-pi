#include "blink.h" // Our function prototypes

#define MY_PIN 1 // Built-in red LED

void setup(){
  pinMode(MY_PIN,OUTPUT);
}

void loop(){
  blink(250);
}

void blink(unsigned int delayms){
  digitalWrite(MY_PIN,HIGH);
  delay(delayms);
  digitalWrite(MY_PIN,LOW);
  delay(delayms);
}
