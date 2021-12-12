## Bugtton
Fast button debounce library for ATmega328P. Uses registers instead of digitalRead.
Library tries to minimize any excess cycle time when buttons are unpressed.
Individual Active-Low and Active-High.

### Updates
v1.0.5 you can set individual pins active-low (positive number), or active-high (negative number).

If you have ideas, hit me message or make an issue.

### Usage In nutshell
```
#include <Bugtton.h>

const uint8_t buttonCount = 6;
const uint8_t buttonPins[buttonCount] = {2,3,4,-5,6,7}; // pin5 with pull down resistor
Bugtton buttons(buttonCount, buttonPins, 25);

void setup() {
    Serial.begin(57600);
    delay(500);
}

void loop() {
    buttons.update();
    
    // Testing buttons
    if (buttons.fell(0))              // Button0 pressed, execute once
    if (buttons.heldUntil(1,2000))    // Button1 down 2s, execute once
    if (buttons.intervalTick(2,1000)) // Button2 down, execute once every 1s
}
```

### Usable functions
Function|Notes
:--------|:--------
**`Bugtton(buttonCount, *pinArray, debounceTime)`**<br>|*Creates button handler*<br>
**`void setMode(pin, mode)`**<br>|*If you need to set individual pins as INPUT and INPUT_PULLUP*
**`void debounceTime(time)`**<br>|*If you need to test different debounce times*
**`void update()`**<br>|*One update to rule them all*
**`unsigned long duration(button_i)`**<br>|*Returns pressed OR unpressed duration of button_i*
**`bool fell(button_i)`**<br>|*Did button_i change state from unpressed to pressed?*
**`bool rose(button_i)`**<br>|*Did button_i change state from pressed to unpressed?*
**`bool up(button_i)`**<br>|*Is button_i unpressed?*
**`bool held(button_i)`**<br>|*Is button_i pressed?*
**`bool heldUntil(button_i, time)`**<br>|*Returns true ONCE when button_i have been pressed x time*
**`bool upUntil(button_i, time)`**<br>|*Returns true ONCE when button_i have been unpressed x time*
**`bool intervalTick(button_i, time)`**<br>|*Returns true ONCE every set interval while button_i pressed*

### Why another button library?
Idea was to make fast button library when nothing is pressed so it would affect to the cycle time as little as possible.

Doesn't matter if you have 1 or 18 buttons, update() takes between 3100-3250 microseconds per 1000 update on unpressed buttons -> 3us per loop

**Measuring time is useless in itself, because just storing micros into uint8_t/uint16_t/uint32_t will affect time differently, but for mere comparison versus other libraries I used:**
```
#include <Bugtton.h>

const uint8_t buttonCount = 5;
const uint8_t buttonPins[buttonCount] = {2,3,4,5,6};
Bugtton buttons(buttonCount, buttonPins, INPUT_PULLUP, 25);

uint32_t t1,t2;
uint16_t count1 = 0;
uint16_t amount = 1000;

void setup() {
    Serial.begin(57600);
    t1 = micros();
}

void loop() {
    buttons.update();
    count1++;
    if (count1 == amount){
        t2 = micros();
        Serial.println(t2-t1);
        for(;;);
    }  
}
```
