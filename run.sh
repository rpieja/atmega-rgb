#!/bin/bash
avr-gcc -g -Os -mmcu=atmega8 -c src/main.c &&
avr-gcc -g -mmcu=atmega8 -o main.elf main.o &&
avr-objcopy -j .text -j .data -O ihex main.elf main.hex &&
avrdude -c usbasp -p atmega8 -v -U flash:w:main.hex
