#pragma once
#include <Arduino.h>
#include "test_result.h"

TestResult test2portLogicAnalog(int powerPin, int powerPolarity, int input1, int input2, int output, int numberofHigh,
                                float targetLow, float targetHigh);