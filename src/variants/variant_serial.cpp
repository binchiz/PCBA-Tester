#include "variant_serial.h"

void serial_setup() {
    Serial.println("PCBA Tester");
    Serial.println("Menu:");
    for (int i = 0; i < TEST_COUNT; i++) {
        Serial.print(i + 1);
        Serial.print(". ");
        Serial.println(TEST_REGISTRY[i].name);
    }
    Serial.println("Enter a number or \"all\" to run all tests:");
}

void serial_loop() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();
        String result = runTestByNumber(input);
        result.replace("\r\n", "\n");
        result.replace("\n", "\r\n");
        Serial.print(result);
    }
}
