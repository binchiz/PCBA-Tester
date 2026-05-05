#include <Arduino.h>
#include "board_setup.h"
#include "variants/variant_serial.h"

#ifdef USE_WIFI
    #include "variants/variant_web.h"
#endif

void setup() {
    Serial.begin(115200);
    while (!Serial);
    serial_setup();
#ifdef USE_WIFI
    web_setup();
#endif
}

void loop() {
    serial_loop();
#ifdef USE_WIFI
    web_loop();
#endif
}