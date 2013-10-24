#include <avr/eeprom.h>
#include "eeprom.h"

#define MY_PIN 1

struct settings_t
{
  int time_on;
  int time_off;
} settings;

void setup(){
  pinMode(MY_PIN,OUTPUT);

  // Read the settings from EEPROM
  eeprom_read_block((void*)&settings, (void*)0, sizeof(settings));

  // Increment, this happens on every reset
  settings.time_on += 50;
  settings.time_off += 100;

  // Loop back round if the values get large
  if ( settings.time_on > 1000 ) settings.time_on = 50;
  if ( settings.time_off > 2000 ) settings.time_off = 100;

  // Write the incremented settings back to EEPROM
  eeprom_write_block((const void*)&settings, (void*)0, sizeof(settings));
}

void loop(){
  digitalWrite(MY_PIN,HIGH);
  delay(settings.time_on);
  digitalWrite(MY_PIN,LOW);
  delay(settings.time_off);
}