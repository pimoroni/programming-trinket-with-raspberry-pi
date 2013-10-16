# Programming Adafruit's Trinket (3v3) directly from a Raspberry Pi

This GitHub Repo accompanies our guide to programming your 3v3 Adafruit Trinket directly from the GPIO header on your Raspberry Pi.

Included are examples of Trinket-ready code.


## A note on NeoPixels

By default, Adafruit disable v1 NeoPixels on an 8Mhz Trinket. You can re-enable them as follows:

    #define __AVR_ATtiny85_
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_OF_PIXELS, YOUR_PIN, NEO_RGB + NEO_KHZ400);

Note the use of NEO_KHZ400. You can remove the #define and use NEO_KHZ800 if you run your Trinket at 16Mhz.
