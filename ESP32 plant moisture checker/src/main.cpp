#include <Arduino.h>

extern "C" {
    #include "settings.h"
}

void setup() {
    if (!scan_for_sensors()) {
        pinMode(LED_BUILTIN, OUTPUT);
        bool toggle_led = false;

        while(true) {
            toggle_led = !toggle_led;
            digitalWrite(LED_BUILTIN, toggle_led ? HIGH : LOW);
            delay(500);
        }
    }
}

void loop() {
    static ulong_t last_timer = 0;

    if (millis() - last_timer > TIMEOUT_IN_MS) {            // each one elapsed second
        last_timer = millis();
        runtime_sequence();
    }
}