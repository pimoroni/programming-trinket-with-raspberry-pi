# Programming Adafruit's Trinket (3v3) directly from a Raspberry Pi

This GitHub Repo accompanies our guide to programming your 3v3 Adafruit Trinket directly from the GPIO header on your Raspberry Pi.

Included are examples of Trinket-ready code.

## Requirements

You will need the Arduino IDE and avrdude installed:

    sudo apt-get install arduino

You will then need Gordon Henderson's modified avrdude, which lets you program using the GPIO header on your Pi.

On Raspbian you can do:

    cd avrdude
    sudo dpkg -i avrdude_5.10-4_armhf.deb
    sudo chmod 4755 /usr/bin/avrdude

For all other distributions you should find the appropriate package here, or compile from source:

    http://project-downloads.drogon.net/gertboard/

Finally, you will need to install the hardware files for the Trinket into your Arduino library folder.

You should be able to run trinket/install in this repository.

    cd trinket
    sudo ./install

This will copy the files to:

    /usr/share/arduino/hardware

Once you're set up, and have your Trinket connected properly, you can test everything by installing the Blink example:

    cd examples/blink
    make upload

## A note on NeoPixels

The Trinket is a great little compact NeoPixel driver, but it's a little short on memory.

By default, Adafruit disable v1 NeoPixels on an 8Mhz Trinket. You can re-enable them as follows:

    #define __AVR_ATtiny85_
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_OF_PIXELS, YOUR_PIN, NEO_RGB + NEO_KHZ400);

Note the use of NEO_KHZ400. You can remove the #define and use NEO_KHZ800 if you run your Trinket at 16Mhz.
