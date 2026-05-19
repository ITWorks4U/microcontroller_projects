/*
* created:    September 11th, 2025
* updated:    May 18th, 2026
* author:     ITWorks4U
* version:    2.1.0
*/

#include <Arduino.h>
#include "general_settings.h"
#include "moisture_settings.h"                              // only for external wait_time_nbr_of_sensors

void setup() {
    if (!scan_for_sensors()) {                              // on init no moisture sensor has been detected => no run sequence for loop
        pinMode(LED_BUILTIN, OUTPUT);
        bool toggle_led = false;

        while(true) {
            toggle_led = !toggle_led;
            digitalWrite(LED_BUILTIN, toggle_led ? HIGH : LOW);
            delay(500);
        }
    }

    scan_for_potentiometer_existence();
}

void loop() {
    static ulong_t last_timer = 0;

    if (millis() - last_timer > TIMEOUT_IN_MS) {            // each one elapsed second
        last_timer = millis();
        runtime_sequence();
    }
}