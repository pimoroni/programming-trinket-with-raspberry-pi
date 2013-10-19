# Trinket Examples

## Blink

The canonical Arduino "hello world" example. By default this will blink the onboard RED LED on and then off every half a second.

To build and upload, simply:

    cd blink
    make upload

## Serial

An Arduino/Pi combo wouldn't be much use without some way of communicating between them.

The Serial example shows basic setup of the SoftwareSerial library on your Trinket, using pins 3 and 4 which would be normally used by USB.

    cd serial
    make upload
