/*
* created:    September 11th, 2025
* updated:    May 14th, 2026
* author:     ITWorks4U
* version:    2.0.2
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
    static int reduced_additional_time = 0;                 // subtract up to additional 400 ms for the next clean 1 second

    if (wait_time_nbr_of_sensors > 0) {
        reduced_additional_time = wait_time_nbr_of_sensors;
        wait_time_nbr_of_sensors = 0;
    }

    if (millis() - last_timer > (TIMEOUT_IN_MS - reduced_additional_time)) {
        last_timer = millis();
        runtime_sequence();

        if (reduced_additional_time > 0) {
            reduced_additional_time = 0;
        }
    }
}