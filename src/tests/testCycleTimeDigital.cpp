#include "testCycleTimeDigital.h"

TestResult testCycleTimeDigital(int powerPin, int powerPolarity, int testPin, int targetMin, int targetMax) {
    
    TestResult result;
    result.test_name = "Cycle Time Digital";
    result.passed = false;
    result.details = "";

    if (powerPin !=- 1) {
        pinMode(powerPin, OUTPUT);
        digitalWrite(powerPin, powerPolarity);
    }

    pinMode(testPin, INPUT);

    const unsigned long timeout = 500000UL; // 500 milliseconds in microseconds

    //wait for the signal to go LOW
    unsigned long startTime = micros();
    while (digitalRead(testPin) == HIGH) {
        if (micros() - startTime > timeout) {
            result.details = "Timeout";
            result.passed = false;
            if (powerPin != -1) digitalWrite(powerPin, !powerPolarity);
            return result; // Timeout error
        }
    }

    //wait for the first HIGH
    startTime = micros();
    while (digitalRead(testPin) == LOW) {
        if (micros() - startTime > timeout) {
            result.details = "Timeout";
            result.passed = false;
            if (powerPin != -1) digitalWrite(powerPin, !powerPolarity);
            return result; // Timeout error
        }
    }
    unsigned long t1 = micros();

    //wait for signal to go LOW again
    startTime = micros();
    while (digitalRead(testPin) == HIGH) {
        if (micros() - startTime > timeout) {
            result.details = "Timeout";
            result.passed = false;
            if (powerPin != -1) digitalWrite(powerPin, !powerPolarity);
            return result; // Timeout error
        }
    }

    //wait for the second HIGH
    startTime = micros();
    while (digitalRead(testPin) == LOW) {
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
    }

    result.details = String("Cycle time: ") + cycleTime + " microseconds";
    result.passed = true;

    return result; 
}