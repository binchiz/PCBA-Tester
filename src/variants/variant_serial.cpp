#include "variant_serial.h"
#include "tests/testVoltage.h"
#include "tests/testConnection.h"

void printResult(TestResult result) {
    Serial.println("================================");
    Serial.println("Tests");
    Serial.println("================================");
    
    Serial.println(String(result.test_name) + "     | " + (result.passed ? "PASSED" : "FAIL") + " |");
    Serial.println("Details:\r\n" + result.details);
    Serial.println("--------------------------------");
}

void setup() {
    Serial.begin(115200);
    while (!Serial);
    Serial.println("PCBA Tester");
    Serial.println("Menu:");
    Serial.println("1. OR gate analog test");
    Serial.println("2. AND gate analog test");
    Serial.println("3. Cycle time analog test");
    Serial.println("4. SIPO test");
    Serial.println("5. Voltage test");
    Serial.println("6. Connection test");
    Serial.println("Enter the number of the test to run or \"all\" to run all tests:");
}

void loop() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();

        if (input == "1") {
            TestResult result = test2portLogicAnalog(powerControlPin, LOW, orA, orB, orOut, 3, 0.0, 1.4);
            printResult(result);
        } else if (input == "2") {
            TestResult result = test2portLogicAnalog(powerControlPin, LOW, andA, andB, andOut, 1, 0.0, 1.4);
            printResult(result);
        } else if (input == "3") {
            TestResult result1 = testCycleTimeAnalog(powerControlPin, LOW, L33, 300000, 500000);
            printResult(result1);
        } else if (input == "4") {
            TestResult result = testSIPO(dataPin, clockPin, latchPin, enablePin, resetPin, sipoOut, sipoNumBits);
            printResult(result);
        } else if (input == "5") {
            TestResult result = testVoltage(powerControlPin, 0, voltagePin, 2.2, 2.8);
            printResult(result);
        } else if (input == "6") {
            TestResult result = testConnection(ledPin, ledTestPin);
            printResult(result);
        } else if (input.equalsIgnoreCase("all")) {
            TestResult result1 = test2portLogicAnalog(powerControlPin, LOW, orA, orB, orOut, 3, 0.0, 1.4);
            printResult(result1);
            TestResult result2 = test2portLogicAnalog(powerControlPin, LOW, andA, andB, andOut, 1, 0.0, 1.4);
            printResult(result2);
            TestResult result3 = testCycleTimeAnalog(powerControlPin, LOW, L33, 300000, 500000);
            printResult(result3);
            TestResult result4 = testSIPO(dataPin, clockPin, latchPin, enablePin, resetPin, sipoOut, sipoNumBits);
            printResult(result4);
            TestResult result5 = testVoltage(powerControlPin, 0, voltagePin, 2.2, 2.8);
            printResult(result5);
            TestResult result6 = testConnection(ledPin, ledTestPin);
            printResult(result6);
        } else {
            Serial.println("Invalid input. Please enter a valid input.");
        }
        Serial.println("\nEnter test number or \"all\":");
    }
}