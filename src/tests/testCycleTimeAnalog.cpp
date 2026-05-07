#include "testCycleTimeAnalog.h"

TestResult testCycleTimeAnalog(int powerPin, int powerPolarity, int testPin, int targetMin, int targetMax) {
    
    TestResult result;
    result.test_name = "Cycle Time Analog";
    result.passed = false;
    result.details = "";

    if (powerPin !=- 1) {
        pinMode(powerPin, OUTPUT);
        digitalWrite(powerPin, powerPolarity);
        delay(1000); // wait for the signal to stabilize
    }

    pinMode(testPin, INPUT);
    
    // sample signal to find dynamic threshold
    int sigMin = 1023;
    int sigMax = 0;
    unsigned long sampleStart = millis();
    while (millis() - sampleStart < 100) {
        int val = analogRead(testPin);
        if (val < sigMin) sigMin = val;
        if (val > sigMax) sigMax = val;
    }
    int threshold = (sigMin + sigMax) / 2;
    const unsigned long timeout = 2000000UL; // 2s in microseconds

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
        result.details = String("Cycle time out of range: ") + cycleTime + " us";
        result.passed = false;
        return result; // Cycle time out of range
    }
    result.details = String("Cycle time: ") + cycleTime + " us";
    result.passed = true;
    return result; // Success
}