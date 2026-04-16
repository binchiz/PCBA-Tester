#include "variant_serial.h"

void serial_setup() {
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

void serial_loop() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();
        String result = runTestByNumber(input);
        Serial.println(result);
    }
}