# Bugtton
Fast button debounce library for ATmega328P, uses registers.
Cycle speed 0.003ms unpressed, 0.010-0.085ms pressed (1-18 buttons).

## Why another button library?
I've tried plenty of different button libraries with ATmega328P, but most of them lacked something, or were too bulky for my own use.
But first and foremost it was a practice to make my first public Arduino library.

## Fast
It uses registers, and it's fast. 1000 cycles with various button amounts gave following:
Unpressed buttons 0.003 ms per cycle regardless button count.
Pressed buttons 0.010 - 0.085 ms per cycle with 1-18 buttons.

Unpressed state is sleeking fast.

## Usable functions
* Bugtton(const uint8_t a, const uint8_t *b, uint8_t mode, uint8_t dt)
Bugtton buttons(buttonCount, pinArray, INPUT_PULLUP, 20)*

* void setMode(uint8_t i, uint8_t mode)
* void debounceTime(uint16_t a);       
* void update()
* unsigned long duration(uint8_t)
* bool fell(uint8_t i)
* bool rose(uint8_t i)
* bool up(uint8_t i)
* bool held(uint8_t i)
* bool heldUntil(uint8_t i, int t)
* bool upUntil(uint8_t i, int t)    