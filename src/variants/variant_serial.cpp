#include "variant_serial.h"

void setMode(Mode mode);

void serial_setup() {
    Serial.begin(115200);
    while (!Serial);
    Serial.println("PCBA Tester in serial mode. Type \"web\" to switch to web mode.");
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

        if(input == "web"){
            Serial.println("Switching mode to web variant");
            setMode(web);
            return;
        }

        String result = runTestByNumber(input);
        Serial.println(result);
    }
}