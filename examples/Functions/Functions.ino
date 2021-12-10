// Functions example using Bugtton - button debounce library.
// Created by Sami Kaukasalo / sakabug, July 20, 2021.

#include <Bugtton.h>

// Button count and button pin array
// Default is Active-Low with pinMode INPUT_PULLUP
// Negative pin number is Active-High with pinMode INPUT
const uint8_t buttonCount = 6;
const uint8_t buttonPins[buttonCount] = {2,-3,4,5,6,7}; // pin 3 on pull down resistor
Bugtton buttons(buttonCount, buttonPins, 100);

void setup() {
    Serial.begin(57600);
    delay(500);
    buttons.debounceTime(25);   // Changing debounce time
    buttons.setMode(7, INPUT);  // Setting pinMode INPUT for pull down resistor
}

void loop() {
    buttons.update();
    // Print every fell/rose
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
    if (buttons.heldUntil(2,3000)) Serial.println("B1 held for 3s. Mode activated.");
    if (buttons.held(3) && buttons.duration(3) >= 2000) Serial.println("Push it, baby");
    if (buttons.intervalTick(4,1000)) {
        Serial.print("B4 held for ");
        Serial.print(buttons.duration(4)/1000);
        Serial.println("s");
    }
    if (buttons.upUntil(5, 5000)) Serial.println("B5 haven't been pressed in 5s");
}