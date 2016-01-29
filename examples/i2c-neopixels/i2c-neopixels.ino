#include <TinyWireS.h>
#include <Adafruit_NeoPixel.h>

// Open this header file to configure the NeoPixel i2c driver
#include "i2c-neopixels.h"

// Neo KHZ400 is necessary on the 8Mhz Trinket
// Note: NEO_KHZ400 has been made optional in recent versions of the NeoPixel library
// please open up Adafruit_NeoPixel.h and follow the instructions inside.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, PIN, PIXEL_COLOR_MODE + NEO_KHZ400);

// Tracks the current register pointer position and current pixel
// There are 3x as many "registers" as pixels, RGB*PIXELS
volatile uint8_t current_register = 0;
volatile uint8_t current_command = 0;
volatile uint8_t current_pixel = 0;

uint8_t r, g, b, x, n, o;

// Updates an individual color component according to the register position
void updatePixelColor(uint8_t value)
{
	current_pixel = (uint8_t)floor(current_register / 3) % (PIXELS*3);

	r = strip.getPixelColor( current_pixel ) >> 16;
	g = strip.getPixelColor( current_pixel ) >> 8;
	b = strip.getPixelColor( current_pixel );

	switch(current_register % 3){
		case 0: // red
			strip.setPixelColor( current_pixel, value, g, b );
			break;
		case 1: // blue
			strip.setPixelColor( current_pixel, r, value, b );
			break;
		case 2: // green
			strip.setPixelColor( current_pixel, r, g, value );
			break;
	}
}

// Handles each Read request
void handleRead()
{  
	// Each pixel has 3 components, R, G and B, to get the pixel index divide by 3
	current_pixel = floor(current_register / 3);

	uint8_t component_color = (uint8_t)( strip.getPixelColor( current_pixel ) >> (16 - ((current_register % 3)*8)) );

	TinyWireS.send(component_color);

	current_register = (current_register+1) % (PIXELS*3);
}

// Handles each Write request
void handleWrite(uint8_t NumBytes)
{
	// Exit if there is no data or more data than the buffer should ever allow
    if (NumBytes < 1 || NumBytes > TWI_RX_BUFFER_SIZE) return;

	// Always treat the first byte as the address
    current_register = TinyWireS.receive();
    NumBytes--;

	if( current_register == 255 && NumBytes )
	{
		handleCommand(NumBytes);
	}
	else
	{
		// If one byte, then addr set for next read
		if (!NumBytes) return;

		// Loop through the remaining bytes and update the pixel components sequentially
		while (NumBytes--)
		{
			updatePixelColor(TinyWireS.receive());
			current_register++;
		}
	}
	
	// Update the strip
    strip.show();
}

void handleCommand(uint8_t NumBytes)
{
	current_command = TinyWireS.receive();
	NumBytes--;
	switch(current_command){
		case CMD_ALL_OFF:
			for(x=0;x<PIXELS;x++){
				strip.setPixelColor(x,0,0,0);
			}
			break;
		case CMD_ALL_RGB:
			if (NumBytes < 3) return; // Not got R G and B components
			r = TinyWireS.receive();
			g = TinyWireS.receive();
			b = TinyWireS.receive();
    			NumBytes-=3;

			for(x=0;x<PIXELS;x++){
				strip.setPixelColor(x,r,g,b);
			}
			break;
		case CMD_SOME_RGB:
			if (NumBytes < 4) return; // Not got R G and B components
			r = TinyWireS.receive();
			g = TinyWireS.receive();
			b = TinyWireS.receive();
			n = TinyWireS.receive();
    			NumBytes-=4;
	
			o = 0; // Starting pixel

			if(NumBytes)
			{
				o = TinyWireS.receive();
				NumBytes--;
			}

			for(x=0;x<PIXELS-o;x++){
				if(x%n == 0){
					strip.setPixelColor(x+o,r,g,b);
				}
			}
			break;
	}
	// Consume any leftover bytes
	while (NumBytes--)
	{
		TinyWireS.receive();
	}
}

void setup()
{
    TinyWireS.begin(I2C_SLAVE_ADDRESS);
    TinyWireS.onReceive(handleWrite);
    TinyWireS.onRequest(handleRead);

    strip.begin();
    strip.show();
}

void loop()
{
    // Avoid putting anything in this loop, and *DO NOT* use delay() anywhere
    TinyWireS_stop_check();
}
