#include "test_run.h"

//print detailed test results
String printResult(TestResult result) {
    String output = "";
    output += "================================\n";
    output += "Tests\n";
    output += "================================\n";
    
    output += String(result.test_name) + "     | " + (result.passed ? "PASSED" : "FAIL") + " |\n";
    output += "Details:\r\n" + result.details + "\n";
    output += "--------------------------------\n";
    return output;
}

//test options
String runTestByNumber(String input){
    if (input == "1") {
        return printResult(test2portLogicAnalog(powerControlPin, LOW, orA, orB, orOut, 3, 0.0, 1.4));
    } else if (input == "2") {
        return printResult(test2portLogicAnalog(powerControlPin, LOW, andA, andB, andOut, 1, 0.0, 1.4));
    } else if (input == "3") {
        return printResult(testCycleTimeAnalog(powerControlPin, LOW, L33, 300000, 500000));
    } else if (input == "4") {
        return printResult(testSIPO(dataPin, clockPin, latchPin, enablePin, resetPin, sipoOut, sipoNumBits));
    } else if (input == "5") {
        return printResult(testVoltage(powerControlPin, 0, voltagePin, 2.2, 2.8));
    } else if (input == "6") {
        return printResult(testConnection(ledPin, ledTestPin));
    } else if (input.equalsIgnoreCase("all")) {
        String output = "";
        output += printResult(test2portLogicAnalog(powerControlPin, LOW, orA, orB, orOut, 3, 0.0, 1.4));
        output += printResult(test2portLogicAnalog(powerControlPin, LOW, andA, andB, andOut, 1, 0.0, 1.4));
        output += printResult(testCycleTimeAnalog(powerControlPin, LOW, L33, 300000, 500000));
        output += printResult(testSIPO(dataPin, clockPin, latchPin, enablePin, resetPin, sipoOut, sipoNumBits));
        output += printResult(testVoltage(powerControlPin, 0, voltagePin, 2.2, 2.8));
        output += printResult(testConnection(ledPin, ledTestPin));

        return output;
    } else {
        return "Invalid input";
    }

}