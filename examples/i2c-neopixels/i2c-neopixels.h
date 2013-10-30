#define __AVR_ATtiny85_
#ifndef TWI_RX_BUFFER_SIZE
#define TWI_RX_BUFFER_SIZE ( 16 )
#endif

int32_t Wheel(byte WheelPos);
void requestEvent();
void receiveEvent(uint8_t howMany);
void setup();
void loop();
