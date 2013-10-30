#define __AVR_ATtiny85_

// These define the commands available when writing via i2c
#define CMD_SET_PIXEL_COLOR_RGB 0x01
// i2cset -y 1 0x04 0x01 0x00 0xFF 0xFF 0xFF 0xFF 0x00 0x00   - Set first pixel to white and second pixel to red
#define CMD_SET_PIXEL_COLOR_WHEEL 0x02

int32_t Wheel(byte WheelPos);
void requestEvent();
void receiveEvent(uint8_t NumBytes);
void setup();
void loop();
