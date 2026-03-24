#include "testCycleTimeAnalog.h"

TestResult testCycleTimeAnalog(int powerPin, int powerPolarity, int testPin, int targetMin, int targetMax) {
    
    TestResult result;
    result.test_name = "Cycle Time Analog";
    result.passed = false;
    result.details = "";

    if (powerPin !=- 1) {
        pinMode(powerPin, OUTPUT);
        digitalWrite(powerPin, powerPolarity);
    }

    pinMode(testPin, INPUT);
    
    const int threshold = 512; // midpoint of the 10-bit ADC range
    const unsigned long timeout = 500000UL; // 500 milliseconds in microseconds

    //wait for the signal to drop below the threshold
    unsigned long startTime = micros();
    while (analogRead(testPin) > threshold) {
        if (micros() - startTime > timeout) {
            result.details = "Timeout";
            result.passed = false;
            if (powerPin != -1) digitalWrite(powerPin, !powerPolarity);
            return result; // Timeout error
        }
    }

    //wait for the first rising edge
    startTime = micros();
    while (analogRead(testPin) <= threshold) {
        if (micros() - startTime > timeout) {
            result.details = "Timeout";
            result.passed = false;
            if (powerPin != -1) digitalWrite(powerPin, !powerPolarity);
            return result; // Timeout error
        }
    }
    unsigned long t1 = micros();

    //wait for signal to go low again
    startTime = micros();
    while (analogRead(testPin) > threshold) {
        if (micros() - startTime > timeout) {
            result.details = "Timeout";
            result.passed = false;
            if (powerPin != -1) digitalWrite(powerPin, !powerPolarity);
            return result; // Timeout error 
        }
    }

    //wait for the second rising edge
    startTime = micros();
    while (analogRead(testPin) <= threshold) {
        if (micros() - startTime > timeout) {
            result.details = "Timeout";
            result.passed = false;
            if (powerPin != -1) digitalWrite(powerPin, !powerPolarity);
            return result; // Timeout error
        }
    }
    unsigned long t2 = micros();

    if (powerPin != -1) digitalWrite(powerPin, !powerPolarity);

    //calculate cycle time and check if it's within the target range
    unsigned long cycleTime = t2 - t1;
    if (cycleTime < targetMin || cycleTime > targetMax) {
        result.details = "Cycle time out of range";
        result.passed = false;
        return result; // Cycle time out of range
    }
    result.details = String("Cycle time: ") + cycleTime + " microseconds";
    result.passed = true;
    return result; // Success
}