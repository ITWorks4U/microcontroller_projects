#include <Arduino.h>
#include "general_settings.h"
#include "moisture_settings.h"

static MoistureSensorDevice devices[MAX_NBR_OF_DEVICES];    // moisture sensor(s)
static int addr_sensor_in[] = {15, 16, 17, 18};             // analog input A1..A5
static int addr_gates[] = {2, 3, 4, 5};                     // digital output 2..5 (MOSFET gate)
static bool on_potentiometer_existing = false;              // checks, if a potentiometer on address A0 has been detected

static int device_id = 0;                                   // pointer for moisture sensor, as well as, MOSFETs

bool scan_for_sensors(void) {
    int nbr_of_devices = 0;

    for(int i = 0; i < MAX_NBR_OF_DEVICES; i++) {
        pinMode(addr_sensor_in[i], INPUT);

        // Check, if the sensor on pin A1..A5 is connected. To realize this, a 10 kΩ
        // resistor for each analog pin A1..A5 and GND is given to prevent a random floating value
        // from the certain pin. Since a sensor has been plugged in, a value of at least
        // 51 can be read, otherwise no sensor is truly connected to that pin.
        if (analogRead(addr_sensor_in[i]) > MIN_RESP_SENSOR_DATA) {
            devices[i].exits = true;                        // this sensor is truly available
            nbr_of_devices++;
        } else {
            devices[i].exits = false;                       // no sensor detected
        }
    }

    return nbr_of_devices > 0;
}

void scan_for_potentiometer_existence(void) {
    pinMode(PIN_POT_TIME_SPAN, INPUT);

    if (analogRead(PIN_POT_TIME_SPAN) > MIN_RESP_SENSOR_DATA) {
        // if a potentiometer was found, then this can be used,
        // otherwise a fixed time span of 24 hours will be used
        // instead
        on_potentiometer_existing = true;
    }
}

void runtime_sequence(void) {
    static int elapsed_seconds = 0;
    static int counter_hours = 0;
    elapsed_seconds = (elapsed_seconds + 1) % HOUR_IN_SECONDS;

    if (elapsed_seconds == 0) {                             // one hour elapsed
        counter_hours = (counter_hours + 1) % LONGEST_TIME_HOURS;
    }

    if (on_potentiometer_existing) {
        int hour_time = map(analogRead(PIN_POT_TIME_SPAN), 0, 1023, SHORTEST_TIME_HOURS, LONGEST_TIME_HOURS);

        if (counter_hours % hour_time == 0) {               // the time span has been reached
            trigger_moisture_sensor();                      // scan the plant earth for a too dry level
        }
    } else {
        if (counter_hours % LONGEST_TIME_HOURS == 0) {
            trigger_moisture_sensor();
        }
    }
}

void trigger_moisture_sensor(void) {
    bool switch_to_next = false;

    if (devices[device_id].exits) {
        // read the sensor value of the current device_id
        // and check, if this sensor reports too dry earth
        if (analogRead(addr_sensor_in[device_id]) >= THRESHOLD_MOITURE) {
            digitalWrite(addr_gates[device_id], HIGH);      // set high to the specific MOSFET
        } else {
            digitalWrite(addr_gates[device_id], LOW);       // set low to the specific MOSFET and switch to the next device
            switch_to_next = true;
        }
    } else {
        switch_to_next = true;
    }

    if (switch_to_next) {
        device_id = (device_id + 1) % MAX_NBR_OF_DEVICES;
    }
}

#ifndef __cplusplus                                         // only for C
long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
#endif