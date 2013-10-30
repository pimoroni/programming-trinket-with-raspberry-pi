# Make your Trinket into an I2C NeoPixel Driver

The Raspberry Pi can't handle the precise timing required to drive NeoPixels, 
but the Trinket can

This example demonstrates the use of TinyWireS ( the S stands for Slave ) 
and the NeoPixel library to turn the Trinket into an I2C Driver for NeoPixels.

To get started, you should make sure you have TinyWireS in your ~/sketchbook/library folder.

    cd /tmp
    git clone https://github.com/rambo/TinyWire
    cd TinyWire
    cp -r TinyWireS ~/sketchbox/libraries/
