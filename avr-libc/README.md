# AVR libc lesson

AVR libc is a standard C library for AVR MCUs. The libc provides various
functions and macros. To use functions and macro definitions in the libc,
header files must be included at the top of files.

## What the program does

The program blinks an LED connected to `PB0`.

## Requirements

* An ATTiny85
* An LED
* A 1K resistor
* A push button, normally open.

## Schematic

![Schematic](kicad/avr-libc.svg)

## Homework:

* Change the input pin to `PB2`.
