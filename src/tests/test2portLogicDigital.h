#pragma once
#include <Arduino.h>
#include "test_result.h"

TestResult test2portLogicDigital(int powerPin, int powerPolarity, int input1, int input2, int output, int numberofHigh);