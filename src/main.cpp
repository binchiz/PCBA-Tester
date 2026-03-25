#include <Arduino.h>
#include "tests/testVoltage.h"

void setup() {
    Serial.begin(9600);
    
    TestResult r = testVoltage(-1, 0, A0, 4.5, 5.5);
    Serial.println(r.passed ? "Voltage: PASS" : "Voltage: FAIL");
    Serial.println(r.details);
}

void loop() {}