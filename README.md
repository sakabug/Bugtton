## Bugtton
Fast button debounce library for ATmega328P. Uses registers instead of digitalRead.

### Usage In nutshell
Compact to use.
```
#include <Bugtton.h>
const uint8_t buttonCount = 5;
const uint8_t buttonPins[buttonCount] = {2,3,4,5,6};
Bugtton buttons(buttonCount, buttonPins, INPUT_PULLUP, 25);
--
void loop() {
  buttons.update();
  
  if (buttons.fell(0))            //B0 down and debounced
  if (buttons.heldUntil(1,3000))  //B1 has been pressed 3 seconds
  --
```

### Usable functions
Function|Notes
:--------|:--------
**`Bugtton(buttonCount, *pinArray, mode, debounceTime)`**|*Creates button handler*<br>
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
**`bool intervalTick(button_i, time)`**|*Returns true ONCE every set interval while button_i pressed*

I use long press functionality alot in my codes, so I wanted to add suitable functions for it. Feel free to suggest new ideas.

### Why this library was made
Idea was to make fast button library when nothing is pressed so it would affect to the cycle time as little as possible.
