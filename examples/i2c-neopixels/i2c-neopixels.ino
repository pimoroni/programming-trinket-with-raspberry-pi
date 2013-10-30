#include <TinyWireS.h>
#include <Adafruit_NeoPixel.h>
#include "i2c-neopixels.h"

// The I2C address that your Trinket will use
#define I2C_SLAVE_ADDRESS 0x4

// NeoPixel PIN, pixel count and brightness
#define PIN 1
#define PIXELS 7 // My NeoPixel stick is broken!
#define BRIGHTNESS 200

// You might want to change this to NEO_RGB if you're using anything but real NeoPixels
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, PIN, NEO_GRB + NEO_KHZ400);

// Registers to store the colours of each pixel
// volatile uint8_t i2c_regs[PIXELS];

// Tracks the current register pointer position
volatile byte reg_position;
volatile uint16_t current_pixel;

// Function to convert int to rgb colour, from AdaFruit example
int32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

/**
 * This is called for each read request we receive, never put more than one byte of data (with TinyWireS.send) to the 
 * send-buffer when using this callback
 */
void requestEvent()
{  
    // Implements i2cget, we'll implement this later
    // TinyWireS.send(i2c_regs[reg_position]);
    // Increment the reg position on each read, and loop back to zero
    //reg_position = (reg_position+1) % sizeof(i2c_regs);
}

/**
 * The I2C data received -handler
 *
 * This needs to complete before the next incoming transaction (start, data, restart/stop) on the bus does
 * so be quick, set flags for long running tasks to be called from the mainloop instead of running them directly,
 */
void receiveEvent(uint8_t NumBytes)
{
    if (NumBytes < 1)
    {
        // No data
        return;
    }

    if (NumBytes > TWI_RX_BUFFER_SIZE)
    {
        // Also insane number
        return;
    }

    uint8_t command = TinyWireS.receive();
    NumBytes--;

    switch(command){
      case CMD_SET_PIXEL_COLOR_RGB:
           
        current_pixel = TinyWireS.receive();

        NumBytes--;

        if (!NumBytes || NumBytes%3)
        {
          // Either no bytes, or not a valid multiple of 3 ( RGB RGB RGB etc )
          return;
        }      

        while(NumBytes>0)
        {
          // Receive R, G and B values
          strip.setPixelColor(current_pixel,TinyWireS.receive(),TinyWireS.receive(),TinyWireS.receive());
          current_pixel++; // De-increment by 3 ( RGB )
          NumBytes-=3;
        }

        strip.show();

      break;
      case CMD_SET_PIXEL_COLOR_WHEEL:
        
        current_pixel = TinyWireS.receive();

        NumBytes--; // Start pixel has been read

        if (!NumBytes)
        {
          // No bytes for pixel colours
          return;
        }
        while(NumBytes--)
        {
            // Update NeoPixels
            uint8_t col = TinyWireS.receive();

            if( col > 0 ){
              strip.setPixelColor(current_pixel%PIXELS, Wheel(col));
            }
            else
            {
              strip.setPixelColor(current_pixel%PIXELS, 0, 0, 0); // Set pixel off
            }

            // Increment register position
            current_pixel++;
        }
        strip.show();
        break;
      }
}

void setup()
{
    TinyWireS.begin(I2C_SLAVE_ADDRESS);
    TinyWireS.onReceive(receiveEvent);
    TinyWireS.onRequest(requestEvent);

    strip.begin();
    strip.show();
    strip.setBrightness(BRIGHTNESS);
}

void loop()
{
    /**
     * This is the only way we can detect stop condition (http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&p=984716&sid=82e9dc7299a8243b86cf7969dd41b5b5#984716)
     * it needs to be called in a very tight loop in order not to miss any (REMINDER: Do *not* use delay() anywhere, use tws_delay() instead).
     * It will call the function registered via TinyWireS.onReceive(); if there is data in the buffer on stop.
     */
    TinyWireS_stop_check();
}
