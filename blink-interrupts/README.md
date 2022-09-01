# Blink and interrupts

An interrupt version of Blink program. The program does not delay the
execution, i.e. it does not use `delay()` in Arduino).

## What the program does

The program blinks an LED connected to `PB0` at 1Hz (on for 500ms and off for
500ms).

## Requirements

* An ATTiny85
* An LED
* A 1K resistor

## Schematic

![Schematic](kicad/blink-interrupts.svg)

## Homework:

* Change the frequency to 2Hz.
