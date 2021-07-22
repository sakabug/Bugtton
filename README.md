# Bugtton
Fast button debounce library for ATmega328P, uses registers.

## Why another button library?
I've tried plenty of different button libraries with ATmega328P, but most of them lacked something, or were too bulky for my own use.
But first and foremost it was a practice to make my first public Arduino library.

## Fast
It uses registers, and it's fast. 1000 cycles with various button amounts gave following:
Unpressed buttons 0.003 ms per cycle regardless button count.
Pressed buttons 0.010 - 0.085 ms per cycle with 1-18 buttons.

Unpressed state is sleeking fast.

## Usage In nutshell
```
#include <Bugtton.h>

const uint8_t buttonCount = 5;
const uint8_t buttonPins[buttonCount] = {2,3,4,5,6};
Bugtton buttons(buttonCount, buttonPins, INPUT_PULLUP, 25);
-
void loop() {
  buttons.update();
  
  if (buttons.fell(0))            //B0 down and debounced
  if (buttons.heldUntil(1,3000))  //B1 has been pressed 3 seconds
  -
```

## Usable functions
```
Bugtton(const uint8_t buttonCount, const uint8_t *pinArray, uint8_t mode, uint8_t debounceTime)
void setMode(uint8_t i, uint8_t mode)
void debounceTime(uint16_t a);       
void update()
unsigned long duration(uint8_t)
bool fell(uint8_t i)
bool rose(uint8_t i)
bool up(uint8_t i)
bool held(uint8_t i)
bool heldUntil(uint8_t i, int t)
bool upUntil(uint8_t i, int t)
```

## Oneshot functions
heldUntil(0,1000) returns true ONCE when button 0 has been down 1 sec.
upUntil(1,10000) returns true ONCE when button 1 has been unpressed for 10 sec.