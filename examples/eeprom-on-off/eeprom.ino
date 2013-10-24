#include <avr/eeprom.h>
#include "eeprom.h"

#define MY_PIN 1

struct settings_t
{
  boolean state;
} settings;

void setup(){
  pinMode(MY_PIN,OUTPUT);

  // Read the settings from EEPROM
  eeprom_read_block((void*)&settings, (void*)0, sizeof(settings));

  // Toggle, this happens on every reset
  settings.state = !settings.state;

  // Write the settings back to EEPROM
  eeprom_write_block((const void*)&settings, (void*)0, sizeof(settings));
}

void loop(){
  if( !settings.state ) return;
  digitalWrite(MY_PIN,HIGH);
  delay(1000);
  digitalWrite(MY_PIN,LOW);
  delay(1000);
}