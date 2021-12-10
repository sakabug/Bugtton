// Simple example using Bugtton - button debounce library.
// Created by Sami Kaukasalo / sakabug, July 20, 2021.

#include <Bugtton.h>

// Button count and button pin array
// Default is Active-Low with pinMode INPUT_PULLUP
// Negative pin number is Active-High with pinMode INPUT
const uint8_t buttonCount = 18;
const uint8_t buttonPins[buttonCount] = {2,3,4,-5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
Bugtton buttons(buttonCount, buttonPins, 25);

void setup() {
    Serial.begin(57600);
    delay(500);
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
}
