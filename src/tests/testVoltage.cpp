#include "testVoltage.h"

TestResult testVoltage(int powerPin, int powerPolarity, int testPin, float targetMin, float targetMax) {
    TestResult result;
    result.test_name = "Voltage Test";
    result.passed = false;
    result.details = "";

    if (powerPin != -1) {
        pinMode(powerPin, OUTPUT);
        digitalWrite(powerPin, powerPolarity);
        delay(10);
    }

    float voltage = analogRead(testPin) * (5.0 / 1023.0);

    result.details += "Measured voltage: " + String(voltage) + "V\n";
    result.details += "Target range: " + String(targetMin) + "V - " + String(targetMax) + "V\n";

    result.passed = (voltage >= targetMin && voltage <= targetMax);

    if (powerPin != -1) {
        digitalWrite(powerPin, !powerPolarity);
    }

    return result;
}