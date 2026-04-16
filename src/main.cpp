#include <Arduino.h>
#include "variants/variant_serial.h"
#include "variants/variant_web.h"
#include "board_setup.h"


void setup() {
    Serial.begin(115200);
    while (!Serial);
    serial_setup();
    web_setup();
}

void loop() {
    serial_loop();
    web_loop();
}
