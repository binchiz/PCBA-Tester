#include "readButton.h"

TestResult readButton(int buttonPin){

    TestResult result;
    result.test_name = "Read Button";
    result.passed = false;
    result.details = "";

    pinMode(buttonPin, INPUT_PULLUP);

    int initial = digitalRead(buttonPin);
    if (initial == LOW) {
        result.details = "Test failed. Wiring issue or button stuck low. \n";
        result.passed = false;
        return result;
    }

    //prompts for user
    result.details += "Press button within 5 seconds.\n";

    unsigned long start = millis();
    const unsigned long timeout = 5000; 

    while (digitalRead(buttonPin) == HIGH){
        if (millis() - start > timeout){
            result.details += "Button not pressed or test failed. \n";
            result.passed = false;
            return result;
        }
    }

    result.details += "Button pressed OK\n";
    result.passed = true;

    return result;
}