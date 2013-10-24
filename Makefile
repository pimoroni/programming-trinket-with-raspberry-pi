ARDUINO_DIR = /usr/share/arduino
ARDMK_PATH    = /usr/bin
AVR_TOOLS_DIR = /usr

# List of libs in your project

ARDUINO_LIBS =

# Adafruit Trinket
# Swap the board tag depending on your Trinket version
# To overclock a 3.3v Trinket to 5v, use trinket5
# 
# You must also include avr/power.h into your .ino/.pde file
# and set the clock_prescale in setup():
#
# #include <avr/power.h>
#
# void setup() {
#   if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
# }

ifndef BOARD_TAG
    BOARD_TAG = trinket3
    #BOARD_TAG = trinket5 # For 5v version
endif

# You probably wont need to change anything below

ALTERNATE_CORE = attiny

# For make ispload

ISP_PROG = gpio
ISP_PORT = /dev/ttyAMA0

# For make upload

MONITOR_PORT = /dev/ttyAMA0
AVRDUDE_OPTS = -e
AVRDUDE_ARD_PROGRAMMER = gpio # change to linuxspi if using https://github.com/kcuzner/avrdude
RESET_CMD = true # disable call to ard-reset-board
AVRDUDE_ARD_BAUDRATE = 57600

include ../../Arduino-Makefile/arduino-mk/Arduino.mk
