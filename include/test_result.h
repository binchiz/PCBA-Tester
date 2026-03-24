#pragma once
#include <Arduino.h>

struct TestResult {
    const char *test_name;
    bool passed;
    String details;
};