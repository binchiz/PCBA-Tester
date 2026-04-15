#include <Arduino.h>
#include "variants/variant_serial.h"
#include "variants/variant_web.h"
#include "board_setup.h"


void serial_setup();
void serial_loop();
void web_setup();
void web_loop();

Mode currentMode = serial;

void setMode(Mode mode) {
    currentMode = mode;
    if (mode == web) {
        web_setup();
    } else {
        serial_setup();
    }
}

void setup() {
    serial_setup();
}

void loop() {
    if (currentMode == serial) {
        serial_loop();
    } else {
        web_loop();
    }
}
