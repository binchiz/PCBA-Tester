#pragma once
#include <Arduino.h>

enum Mode{
    serial,
    web
};

const int ledPin = 13;
const int ledTestPin = 12;
const int switch1 = 1;
const int powerControlPin = 2;
const int powerPolarity = LOW;
const int latchPin = 5;
const int clockPin = 4;
const int dataPin = 7;
const int enablePin = 6;
const int resetPin = 3;
const int andA = 8;
const int andB = 9;
const int orA = 10;
const int orB = 11;
const int andOut = A2;
const int orOut = A1;
const int wait = 250;
const int L33 = A3;
const int L34 = A4;
const int sipoOut = A5;
const int sipoNumBits = 8;
const int voltagePin = A0;
const float adcVoltageFactor = 5.0 / 1023.0;
const int buttonPin = 1;