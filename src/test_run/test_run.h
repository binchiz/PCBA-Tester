#pragma once
#include <Arduino.h>
#include "board_setup.h"
#include "test_result.h"

//available tests
#include "../tests/test2portLogicAnalog.h"
#include "../tests/test2portLogicDigital.h"
#include "../tests/testCycleTimeAnalog.h"
#include "../tests/testSIPO.h"
#include "../tests/testVoltage.h"
#include "../tests/testConnection.h"


String runTestByNumber(String input);