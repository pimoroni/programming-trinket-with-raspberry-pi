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

## Usage

The I2C NeoPixel Driver uses the I2C protocol. You'll need a few things installed on your Raspberry Pi to make effective use of it.

First you should edit /etc/modprobe.d/raspi-blacklist.conf and comment out the i2c entry so that it looks like this:

    #blacklist i2c-bcm2708

You should also edit /etc/modules and add

    i2c-dev

Then you'll need i2c-tools which will give you the i2cdetect, i2cget and i2cset commands.

    sudo apt-get update
    sudo apt-get install i2c-tools

Give the Pi user access to i2c by adding it to the relevant group:

    sudo adduser pi i2c

Finally, test your NeoPixel driver by running:

    i2cdetect -y 1

If you see it's i2c address ( 04 by default ) in the resulting table, you're good to go.

Turn on all the LEDs by running:

    i2cset -y 1 0x04 0xff 0x01 10 10 10 i

I've deliverately put the i2c address, register address and command byte in hexadecimal and the R G and B values in decimal so you can see the difference. But hexidecimal and decimal are interchangable in i2cset, so use whatever you're comfortable with ( 0xff is 255, 0x01 is 1 etc )

Specifying 0xff immediately after the i2c address places the device in command mode, the structure of the commands are as follows:

### Set all LEDs to R G B
   
    i2cset -y 1 0x04 0xff 0x01 R G B i

### Set LED % N to R G B
Where the index of an LED % N = 0, that LED will be toggled
    
    i2cset -y 1 0x04 0xff 0x02 R G B N i

For example, this will set every 2nd LED to full Red
    
    i2cset -y 1 0x04 0xff 0x02 255 0 0 2 i

This command also supports an offset, so you could offset by 1 and change the other LEDs to Blue

    i2cset -y 1 0x04 0xff 0x02 0 0 255 2 1 i

Where the last digit is the offset.

### Turn all LEDs off

    i2cset -y 1 0x04 0xff 0x00 i
