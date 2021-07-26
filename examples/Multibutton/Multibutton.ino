
// Example for multiple buttons using Bugtton - button debounce library.
// Created by Sami Kaukasalo / sakabug, July 20, 2021.

#include <Bugtton.h>

const uint8_t buttonCount = 5;
const uint8_t buttonPins[buttonCount] = {2,3,4,5,6};
Bugtton buttons(buttonCount, buttonPins, INPUT_PULLUP, 25);

bool flipFlop = false;

void setup() {
    Serial.begin(57600);
}

void loop() {
    
    // Update button states handler
    buttons.update();
    
    // Testing buttons
    for (uint8_t i=0; i<buttonCount; i++){
        if (buttons.fell(i)) {
            Serial.print("B");
            Serial.print(i);
            Serial.println(" fell");
        }
        if (buttons.rose(i)){
            Serial.print("B");
            Serial.print(i);
            Serial.println(" rose");
        }
    }

    // Printing continuous held time
    if (buttons.held(0)) {
        Serial.print("B0 held for ");
        Serial.print(buttons.duration(0));
        Serial.println(" ms");
    }

    // If button 2 held for 1 sec, destroy something?
    if (buttons.heldUntil(1,1000)) {
        flipFlop = !flipFlop;
        if (flipFlop) Serial.println("SELF DESTRUCT ACTIVATED");
        else Serial.println("SELF DESTRUCT DEACTIVATED");
    }

    // If button 2 is left unpressed for 10 sec - it tells user to press it
    if (buttons.upUntil(2,10000)) {
        Serial.println("Try holding B2");
    }
    
    // Ticks once every 1000 ms
    if (buttons.intervalTick(2,1000)){
        Serial.print("B2 pressed for ");
        Serial.print(buttons.duration(2)/1000);
        Serial.println(" secs");
    }
   
}
