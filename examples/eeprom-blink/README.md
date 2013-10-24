# EEPROM

This example shows basic use of the Trinket's limited amount 
of non-volatile memory.

The EEPROM lets you store customisable settings which are 
persisted even when you reset your Trinket.

## Using this example

This example increments the time that the built-in LED is turned 
on and off each time the Trinket is reset.

Every time you press the reset button, the onboard LED should blink 
slower until it loops back to blinking quickly again.

Without EEPROM the timings would not persist between resets!

Just:

  make upload

And hit the reset button a few times to test.