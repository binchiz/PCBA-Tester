#include "testConnection.h"

TestResult testConnection(int pin1, int pin2) {
    TestResult result;
    result.test_name = "Connection Test";
    result.passed = false;
    result.details = "";

    pinMode(pin1, OUTPUT);
    pinMode(pin2, INPUT);

    // Test LOW
    digitalWrite(pin1, LOW);
    delay(10);
    int readLow = digitalRead(pin2);

    // Test HIGH
    digitalWrite(pin1, HIGH);
    delay(10);
    int readHigh = digitalRead(pin2);

    result.details += "LOW read: " + String(readLow) + "\n";
    result.details += "HIGH read: " + String(readHigh) + "\n";

    result.passed = (readLow == LOW && readHigh == HIGH);

    return result;
}