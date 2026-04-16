#include <Arduino.h>
#include "general_settings.h"
#include "moiture_settings.h"
#include "pump_settings.h"

static Device devices[MAX_NBR_OF_DEVICES];                     // moiture sensor(s)
static Pump pumps[MAX_NBR_OF_DEVICES];                         // pump(s)
unsigned int wait_time_nbr_of_sensors = 0;                     // initial setting (more in use in loop() function)

static int addr_sensor_out[] = {8, 9, 10, 11};                 // digital output 8..11 (sensor power)
static int addr_sensor_in[] = {15, 16, 17, 18};                // analog input A1..A5
static int addr_gates[] = {2, 3, 4, 5};                        // digital output 2..5 (MOSFET gate)

bool init_devices(void) {
    int nbr_of_devices = 0;

    for(int i = 0; i < MAX_NBR_OF_DEVICES; i++) {
        // preset for each pump (no matter, if this pump truly exists)
        pumps[i].is_running = false;
        pumps[i].runtime_counter = 0;

        // setting for each sensor
        pinMode(addr_sensor_out[i], OUTPUT);
        pinMode(addr_sensor_in[i], INPUT);

        digitalWrite(addr_sensor_out[i], HIGH);                // turn on the outgoing sensor for a short time
        delay(TINY_DELAY_PWR_SENSOR);                          // wait 125 ms

        // Check, if the sensor on pin A1..A5 is connected. To realize this, a 10 kOhm
        // resistor for each analog pin A1..A5 and GND is given to prevent a random floating value
        // from the certain pin. Since a sensor has been plugged in, a value of at least
        // 51 can be read, otherwise no sensor is truly connected to that pin.
        if (analogRead(addr_sensor_in[i]) > MIN_RESP_SENSOR_VALUE) {
            devices[i].exits = true;                           // this sensor is truly available
            nbr_of_devices++;
        } else {
            devices[i].exits = false;                          // no sensor detected
        }

        digitalWrite(addr_sensor_out[i], LOW);                 // turn the sensor output pin off

        if (devices[i].exits)  {                               // turn on the pump for 250ms and then turn this off
            pinMode(addr_gates[i], OUTPUT);
            digitalWrite(addr_gates[i], HIGH);
            delay(DURATION_INIT_PUMP_IN_MS);                   // run the pump for 250ms
            digitalWrite(addr_gates[i], LOW);
        }
    }

    return nbr_of_devices > 0;
}

void runtime_sequence() {
    static int elapsed_seconds = 0;
    static int counter_hours = 0;
    elapsed_seconds = (elapsed_seconds + 1) % HOUR_IN_SECONDS;

    if (elapsed_seconds == 0) {                                // one hour elapsed
        counter_hours = (counter_hours + 1) % LONGEST_TIME_HOURS;
    }

    int hour_time = map(analogRead(PIN_POT_TIME_SPAN), 0, 1023, SHORTEST_TIME_HOURS, LONGEST_TIME_HOURS);

    if (counter_hours % hour_time == 0) {                      // the time span has been reached
        trigger_moiture_sensor();                              // scan the plant earth for a too dry level
    }
}

void trigger_moiture_sensor(void) {
    for(int i = 0; i < MAX_NBR_OF_DEVICES; i++) {
        if (devices[i].exits) {

            // turn on the certain sensor
            digitalWrite(addr_sensor_out[i], HIGH);
            wait_time_nbr_of_sensors += 100;                   // subtracted in loop() function
            delay(DURATION_SENSOR_IN_MS);                      // hold this for 100ms (this is intented)
            devices[i].data = analogRead(addr_sensor_in[i]);
            digitalWrite(addr_sensor_out[i], LOW);

            if (devices[i].data > THRESHOLD_MOITURE) {         // dry value in range
                if (!pumps[i].is_running) {                    // the pump is not running yet
                    digitalWrite(addr_gates[i], HIGH);         // power the gate for certain pump
                    pumps[i].is_running = true;
                }

                pumps[i].runtime_counter++;                    // runtime [1..5]
                if (pumps[i].runtime_counter == MAX_ELAPSED_TIME_CTR_IN_SEC) {
                    pumps[i].runtime_counter = 0;              // reset counter
                    digitalWrite(addr_gates[i], LOW);          // turn off gate
                    pumps[i].is_running = false;               // set flag to false
                }
            }

            // turn off the pump (earlier), if the measured
            // value is already satisfied
            if (devices[i].data < THRESHOLD_MOITURE && pumps[i].is_running) {
                digitalWrite(addr_gates[i], LOW);
                pumps[i].is_running = false;
            }
        }
    }
}

#ifndef __cplusplus                                            // only for C
long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
#endif