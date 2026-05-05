#pragma once
#include <Arduino.h>
#include "board_setup.h"
#include "test_result.h"

#include "../tests/test2portLogicAnalog.h"
#include "../tests/test2portLogicDigital.h"
#include "../tests/testCycleTimeAnalog.h"
#include "../tests/testCycleTimeDigital.h"
#include "../tests/testSIPO.h"
#include "../tests/testVoltage.h"
#include "../tests/testConnection.h"

// a structure to hold test name and function pointer for running the test
struct TestEntry {
    const char* name;
    TestResult (*run)();
};

extern const TestEntry TEST_REGISTRY[];
extern const int TEST_COUNT;

String runTestByNumber(String input);
