#pragma once
#include <Arduino.h>
#include "test_result.h"

TestResult testSIPO(int dataPin, int clockPin, int latchPin, int output, int numBits);