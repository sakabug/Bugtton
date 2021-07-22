
// Example for multiple buttons using Bugtton - button debounce library.
// Created by Sami Kaukasalo / sakabug, July 20, 2021.

#include <Bugtton.h>

const uint8_t buttonCount = 5;
const uint8_t buttonPins[buttonCount] = {2,3,4,5,6};
Bugtton buttons(buttonCount, buttonPins, INPUT_PULLUP, 25);

bool flipFlop = 0;
int8_t count1 = -1;

void setup() {
    Serial.begin(9600);
}

void loop() {
    
    // Update button states handler
    buttons.update();
    
    // Code for handling button actions
    if (buttons.fell(0)) Serial.println("B0 fell");
    
    if (buttons.rose(0)) Serial.println("B0 rose");
    
    if (buttons.held(0)) {
        int t1 = buttons.duration(0)/1000;
        if (count1 != t1){
            count1++;
            Serial.print("B0 held for ");
            Serial.print(count1);
            Serial.println(" s");
        }
    }

    // If button 2 held for 1 sec - oneshot
    if (buttons.heldUntil(1,1000)) {
        flipFlop = !flipFlop;
        if (flipFlop) Serial.println("ACTIVATED");
        else Serial.println("DEACTIVATED");
    }

    // If button 2 is left unpressed for 5 sec - it tells user to press it - oneshot
    if (buttons.upUntil(1,5000))
        Serial.println("Press B1 for 1 second");
   
}