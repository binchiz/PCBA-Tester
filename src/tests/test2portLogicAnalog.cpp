#include "test2portLogicAnalog.h"

TestResult test2portLogicAnalog(int powerPin, int powerPolarity, int input1, int input2, int output, int numberofHigh,
                                float targetLow, float targetHigh) {
    TestResult result;
    result.test_name = "2 Port Logic Analog";
    result.passed = false; 
    result.details = "";

    if (powerPin != -1) {
        pinMode(powerPin, OUTPUT);
        digitalWrite(powerPin, powerPolarity);
        delay(10);
    }

    //from arduino perspective, logig gate input pins set as output, logic gate output set as 
    // input for reading the val
    pinMode(input1, OUTPUT);
    pinMode(input2, OUTPUT);
    pinMode(output, INPUT);

    int highCount = 0;
    for (int i = 0; i < 4; ++i) {
        int inp1 = (i >> 1) & 1; //bit for input1
        int inp2 = i & 1; //bit for input2

        digitalWrite(input1, inp1);
        digitalWrite(input2, inp2);
        delay(10);

        // reading here needs to be from analog and converted to voltage
        int rawValue = analogRead(output);
        float voltage = (rawValue / 1023.0) * 3.3;
        if (voltage >= targetHigh) {
            ++highCount;
            result.details += "Inp1: " + String(inp1) + ", Inp2: " + String(inp2) + ", Out: " + String(voltage, 2) + "V " + "HIGH";
        } else if (voltage <= targetLow) {
            result.details += "Inp1: " + String(inp1) + ", Inp2: " + String(inp2) + ", Out: " + String(voltage, 2) + "V " + "LOW";
        } else {
            result.details += "Inp1: " + String(inp1) + ", Inp2: " + String(inp2) + ", Out: " + String(voltage, 2) + "V Undefined";
        }

        if (i < 3) result.details += "\n";
    }

    result.passed = (highCount == numberofHigh);

    if (powerPin != -1) {
        digitalWrite(powerPin, !powerPolarity);
    }

    return result;
}