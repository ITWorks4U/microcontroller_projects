#include "Arduino.h"

extern "C" {
    #include "settings.h"
}

static MoistureSensorDevice devices[MAX_NBR_OF_DEVICES];    // moisture sensor(s)
static int addr_sensor_in[] = {32, 33, 34, 35};             // ADC ports
static int addr_gates[] = {16, 17, 4, 5};                   // digital ports (MOSFET gates)
static int device_id = 0;                                   // pointer for moisture sensor, as well as, MOSFETs

bool scan_for_sensors(void) {
    int nbr_of_devices = 0;

    for(int i = 0; i < MAX_NBR_OF_DEVICES; i++) {
        pinMode(addr_sensor_in[i], INPUT);

        // Check, if a sensor on the certain ADC pin is connected. To realize this, a 10 kΩ
        // resistor for each analog pin and GND is given to prevent a random floating value
        // from the certain pin. Since a sensor has been plugged in, a value of at least
        // 81 can be read, otherwise no sensor is truly connected to that pin.
        if (analogRead(addr_sensor_in[i]) > MIN_RESP_SENSOR_DATA) {
            devices[i].exits = true;                        // this sensor is truly available
            nbr_of_devices++;
        } else {
            devices[i].exits = false;                       // no sensor detected
        }
    }

    return nbr_of_devices > 0;
}

void runtime_sequence(void) {
    static int counter_seconds = 0;
    static int counter_hours = 0;
    counter_seconds = (counter_seconds + 1) % HOUR_IN_SECONDS;

    if (counter_seconds == 0) {                             // one hour elapsed
        counter_hours = (counter_hours + 1) % ELAPSED_HOURS;
    }

    if (counter_hours % ELAPSED_HOURS == 0) {               // 24 hours elapsed
        trigger_moisture_sensor();
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