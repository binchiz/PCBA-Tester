#pragma once
#include <Arduino.h>
#include "test_result.h"
#include "board_setup.h"

TestResult testVoltage(int powerPin, int powerPolarity, int testPin, float targetMin, float targetMax);