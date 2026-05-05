#include "test_run.h"


// only TestResult and TestEntry need to be modified to run different tests or add new ones. These will be used both for serial and web
static TestResult runOR()         { return test2portLogicAnalog(powerControlPin, powerPolarity, orA, orB, orOut, 3, 0.0, 1.4); }
static TestResult runAND()        { return test2portLogicAnalog(powerControlPin, powerPolarity, andA, andB, andOut, 1, 0.0, 1.4); }
static TestResult runCycleTime() {
    delay(5000); // extra stabilization on first call
    return testCycleTimeAnalog(powerControlPin, powerPolarity, L33, 300000, 500000);
}
static TestResult runSIPO()       { return testSIPO(dataPin, clockPin, latchPin, enablePin, resetPin, sipoOut, sipoNumBits); }
static TestResult runVoltage()    { return testVoltage(powerControlPin, 0, voltagePin, 2.2, 2.8); }
static TestResult runConnection() { return testConnection(ledPin, ledTestPin); }
static TestResult readButton()    { return readButton(buttonPin); }

// this is an array of Test entry structs that holds data of names that will be used for displaying in serial/creating buttons in web, and corresponding func
const TestEntry TEST_REGISTRY[] = {
    {"OR gate analog", runOR},
    {"AND gate analog", runAND},
    {"Cycle time analog", runCycleTime},
    {"SIPO test", runSIPO},
    {"Voltage test", runVoltage},
    {"Connection test", runConnection},
    {"Button test", readButton},
};
const int TEST_COUNT = sizeof(TEST_REGISTRY) / sizeof(TEST_REGISTRY[0]);

static String printResult(TestResult result) {
    String output = "";
    output += "================================\n";
    output += "Tests\n";
    output += "================================\n";
    output += String(result.test_name) + "     | " + (result.passed ? "PASSED" : "FAIL") + " |\n";
    output += "Details:\r\n" + result.details + "\n";
    output += "--------------------------------\n";
    return output;
}

String runTestByNumber(String input) {
    if (input.equalsIgnoreCase("all")) {
        String output = "";
        for (int i = 0; i < TEST_COUNT; i++){
            output += printResult(TEST_REGISTRY[i].run());
            //add a delay between tests
            delay(200);
            //reset the status
            digitalWrite(powerControlPin, !powerPolarity);
            delay(100);
        }
        return output;
    }
    int id = input.toInt() - 1;
    if (id >= 0 && id < TEST_COUNT)
        return printResult(TEST_REGISTRY[id].run());
    return "Invalid input";
}
