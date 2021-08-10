
// Bugtton - button debounce library for ATmega168/328P

// Fast button debounce library for ATmega328P. Uses registers instead of digitalRead.
// Cycle speed 0.003ms unpressed, 0.010-0.085ms pressed (1-18 buttons).

// Created by Sami Kaukasalo / sakabug, July 20, 2021.

// MIT License

// Copyright (c) 2021 Sami Kaukasalo / sakabug

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "Bugtton.h"

// Bugtton buttons(buttonCount, buttonPins(array), INPUT/INPUT_PULLUP, debounce time)
Bugtton::Bugtton(const uint8_t a, const uint8_t *b, uint8_t mode, uint8_t dt){
    // Init values
    _maskD = B00000000;
    _maskB = B00000000;
    _maskC = B00000000;
    _count = a;
    _debounceTime = dt;
    _allStable = false;
    _flag1 = false;
    
    // Create buttons (was first separate classes, but this is the way I went)
    _pins = new uint8_t[_count];
    _bits = new uint8_t[_count];
    _stateStarted = new uint32_t[_count];
    _ticksStarted = new uint32_t[_count];
    // Init button data
    for(uint8_t i=0; i<_count; i++){
        setMode(b[i], mode);
        _pins[i] = b[i];
        _bits[i] = B11100000;
        _stateStarted[i] = 0;
        _ticksStarted[i] = 0;
    }
    
    // Make bitmasks
    makeMasks();
}

// Bitmask for registers, formed from pin array
void Bugtton::makeMasks(){
    for (uint8_t i=0; i<_count; i++){
        if (_pins[i] < 8) bitWrite(_maskD, _pins[i], 1);
        else if (_pins[i] >= 8 && _pins[i] < 14) bitWrite(_maskB, (_pins[i]-8), 1);
        else if (_pins[i] >= 14 && _pins[i] < 20) bitWrite(_maskC, (_pins[i]-14), 1);
    }
}

// For debugging purposes
void Bugtton::printBIN(uint8_t b){
  for(int i = 7; i >= 0; i--)
    Serial.print(bitRead(b,i));
  Serial.println();  
}

// If you need set debounce time with code, THIS IS set at constructor
void Bugtton::debounceTime(uint16_t a){ _debounceTime = a; }

// Updates all buttons at once, needs to run only once in loop, this is what I wanted
void Bugtton::update(){
    _allUp = false;
    if (_allStable){
        if ((_maskD == (PIND&_maskD)) &&
            (_maskB == (PINB&_maskB)) &&
            (_maskC == (PINC&_maskC)) ){
            // if no buttons down, and buttons states are stable
            if (_flag1) {
                return;
            }
            _flag1 = true;
        }
    }
    //Update bits
    for (uint8_t i=0; i<_count; i++){
        
        // Reset changedBit
        changedBit(i, 0);
        
        // Update currentBit from registers
        if (_pins[i] < 8) currentBit(i, PIND&(1<<_pins[i]) );
        else if (_pins[i] < 14) currentBit(PINB&(1<<(_pins[i]-8) ));
        else if (_pins[i] < 20) currentBit(PINC&(1<<(_pins[i]-14) ));
        
        //No change in button state
        if ( currentBit(i) == oldBit(i)){
          stableBit(i, 1);
          _allStable = true;
        }
        
        //Change in button state
        else {
            _allStable = false;
            _flag1 = false;
            // Unstable, wait for debounce time
            if (stableBit(i)){
                stableBit(i, 0);
                stateStarted(i, millis());
            }
            // Stable, debounce finished, state will change
            else if (millis() - stateStarted(i) >= _debounceTime ){
                stableBit(i, 1);
                oldBit(i, currentBit(i));
                changedBit(i, 1);
                stateStarted(i, millis());
                _ticksStarted[i] = millis();
                heldUntilUsed(i,0);
            }
        }
    }
}

// Manipulating single button byte
void Bugtton::currentBit(uint8_t i, bool a) { bitWrite(_bits[i], 7, a); }
bool Bugtton::currentBit(uint8_t i)         { return bitRead(_bits[i], 7); }
void Bugtton::stableBit(uint8_t i, bool a)  { bitWrite(_bits[i], 6, a); }
bool Bugtton::stableBit(uint8_t i)          { return bitRead(_bits[i], 6); }      
void Bugtton::oldBit(uint8_t i, bool a)     { bitWrite(_bits[i], 5, a); }
bool Bugtton::oldBit(uint8_t i)             { return bitRead(_bits[i], 5); }
void Bugtton::changedBit(uint8_t i, bool a) { bitWrite(_bits[i], 4, a); }
bool Bugtton::changedBit(uint8_t i)         { return bitRead(_bits[i], 4); }
void Bugtton::heldUntilUsed(uint8_t i, bool a) { bitWrite(_bits[i], 3, a); }
bool Bugtton::heldUntilUsed(uint8_t i)      { return bitRead(_bits[i], 3); }
void Bugtton::tickBit(uint8_t i, bool a)    { bitWrite(_bits[i], 2, a); }
bool Bugtton::tickBit(uint8_t i)            { return bitRead(_bits[i], 2); }

// Timestamps for debounce, and duration function
void Bugtton::stateStarted(uint8_t i, uint32_t a){ _stateStarted[i] = a; }
uint32_t Bugtton::stateStarted(uint8_t i) { return _stateStarted[i]; }
uint32_t Bugtton::duration(uint8_t i) { return millis() - _stateStarted[i]; }

// Set pin mode here
void Bugtton::setMode(uint8_t i, uint8_t mode){
    if (mode == OUTPUT){
        // Set DDR bit -> OUTPUT
        if (i < 8) DDRD|=(1<<(i));
        else if (i < 14) DDRB|=(1<<(i-8));
        else if (i < 20) DDRC|=(1<<(i-14));
        // Defaults to LOW if coming from INPUT mode (HIGH if from INPUT_PULLUP)
    }
    else{
        // Clear DDR bit -> INPUT
        if (i < 8) DDRD&=~(1<<(i));
        else if (i < 14) DDRB&=~(1<<(i-8));
        else if (i < 20) DDRC&=~(1<<(i-14));
        
        if (mode == INPUT_PULLUP){
            // Set PORT bit
            if (i < 8) PORTD|=(1<<(i));
            else if (i < 14) PORTB|=(1<<(i-8));
            else if (i < 20) PORTC|=(1<<(i-14));
        }
        else{
            // Clear PORT bit
            if (i < 8) PORTD&=~(1<<(i));
            else if (i < 14) PORTB&=~(1<<(i-8));
            else if (i < 20) PORTC&=~(1<<(i-14));
        }
    }
}

// Button state has changed to unpressed to pressed
bool Bugtton::fell(uint8_t i){
	if ( (_bits[i]&B11110000) == B01010000 ) {
        return true;
    }
	return false;
}

// Button state has changed to pressed to unpressed
bool Bugtton::rose(uint8_t i){
	if ( (_bits[i]&B11110000) == B11110000 ) {
        return true;
    }
	return false;
}

// Button is unpressed
bool Bugtton::up(uint8_t i){
    if ( (_bits[i]&B11110000) == B11100000 ) {
        return true;
    }
    return false;
}

// Button is being held down (pressed)
bool Bugtton::held(uint8_t i){
	if ( (_bits[i]&B11110000) == B01000000 ) {
        return true;
    }
	return false;
}

// Returns true once when <time> ms reached while button pressed state
bool Bugtton::heldUntil(uint8_t i, uint16_t t){
    //printBIN(_bits[i]);
	if ( (_bits[i]&B11111000) == B01000000 && duration(i) >= t) {
        bitWrite(_bits[i], 3, 1);
        return true;
    }
	return false;
}

// Returns true once when <time> ms reached while button unpressed state
bool Bugtton::upUntil(uint8_t i, uint16_t t){
	if ( (_bits[i]&B11111000) == B11100000 && duration(i) >= t) {
        bitWrite(_bits[i], 3, 1);
        return true;
    }
	return false;
}

// Returns true once every <time> ms
bool Bugtton::intervalTick(uint8_t i, uint32_t t){
    if ( (_bits[i]&B11110000) == B01000000){
        if ( (millis() - _ticksStarted[i]) >= t && !tickBit(i) ){
            tickBit(i, 1);
            _ticksStarted[i] += t;
            return true;
        }
        else if ( (millis() - _ticksStarted[i]) < t && tickBit(i) ){
            tickBit(i, 0);
        }
    }
    return false;
}





