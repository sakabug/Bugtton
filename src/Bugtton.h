
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

#ifndef Bugtton_h
#define Bugtton_h

#include "Arduino.h"

// Read .cpp for comments
class Bugtton {
  
    private:

        byte _maskD;
        byte _maskB;
        byte _maskC;
        uint8_t _count;
        uint8_t *_debounceTime;
        bool _allStable;
        bool _flag1;
        bool _allUp;
        bool _allUpUsed;
        
        uint8_t *_pins;
        byte *_bits;
        unsigned long *_stateStarted;
        unsigned long *_ticksStarted;
        unsigned long _allUpStarted;
        
        void Bugtton::makeMasks();
        void Bugtton::printBIN(byte b);
        
        void Bugtton::currentBit(uint8_t i, bool a);
        bool Bugtton::currentBit(uint8_t i);
        void Bugtton::stableBit(uint8_t i, bool a);
        bool Bugtton::stableBit(uint8_t i);
        void Bugtton::oldBit(uint8_t i, bool a);
        bool Bugtton::oldBit(uint8_t i);
        void Bugtton::changedBit(uint8_t i, bool a);
        bool Bugtton::changedBit(uint8_t i);
        void Bugtton::heldUntilUsed(uint8_t i, bool a);
        bool Bugtton::heldUntilUsed(uint8_t i);
        void Bugtton::stateStarted(uint8_t i, unsigned long a);
        unsigned long Bugtton::stateStarted(uint8_t i);
        void Bugtton::tickBit(uint8_t i, bool a);
        bool Bugtton::tickBit(uint8_t i);

    public:

        Bugtton::Bugtton(const uint8_t a, const uint8_t *b, uint8_t mode, uint8_t dt);
        void Bugtton::debounceTime(uint16_t a);        
        void Bugtton::update();
        
        void Bugtton::setMode(uint8_t i, uint8_t mode);
        unsigned long Bugtton::duration(uint8_t);
        bool Bugtton::fell(uint8_t i);
		bool Bugtton::rose(uint8_t i);
		bool Bugtton::up(uint8_t i);
        bool Bugtton::held(uint8_t i);
        bool Bugtton::heldUntil(uint8_t i, int t);
        bool Bugtton::upUntil(uint8_t i, int t);
        bool Bugtton::intervalTick(uint8_t i, unsigned long t);
        
};


#endif


