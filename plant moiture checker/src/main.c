/*
* created:    September 11th, 2025
* updated:    April 16th, 2026
* author:     ITWorks4U
* version:    2.0.0
*/

#include <Arduino.h>
#include "general_settings.h"
#include "moiture_settings.h"            // only for external wait_time_nbr_of_sensors

void setup() {
    if (!init_devices()) { // on init no moiture sensor has been detected => no run sequence for loop
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
    // NOTE: Since an Arduino (Uno) can't handle a value, like 8,640,000 ms (one day),
    //       and the range of an integer is [-32,768..32,767] an another way is in use.

    static ulong_t last_timer = 0;
    static int reduced_additional_time = 0;              // subtract up to additional 400 ms for the next clean 1 second

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