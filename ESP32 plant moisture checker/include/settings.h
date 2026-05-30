#ifndef SETTINGS_H
#define SETTINGS_H

/////
/// definitions
/////

#define ELAPSED_HOURS        24        // 24 hours

#define TIMEOUT_IN_MS        1000      // 1,000 ms for the next runtime sequence
#define HOUR_IN_SECONDS      3600      // 3,600s => 1h

#define THRESHOLD_MOITURE    2000      // the limitation, when the pump shall start
#define MAX_NBR_OF_DEVICES   4         // up to 4 sensors and 4 pumps
#define MIN_RESP_SENSOR_DATA 80        // minimal responding analog sensor data

typedef unsigned long ulong_t;

/////
/// structures
/////

/// @brief Container for moisture sensor.
///
///        A pump can only be triggered, if the coresponding
///        sensor is available.
typedef struct {
    bool exits;                         // true := available, false := unavailable
}MoistureSensorDevice;

/////
/// function prototypes
/////

/// @brief On first runtime check which device is available.
///
///        If no moisture sensor was able to found, then the internal LED
///        blinks each 500ms forever.
/// @return true, if the initialization was successful, otherwise false
bool scan_for_sensors(void);

/// @brief Run over and over again.
void runtime_sequence(void);

/// @brief Trigger the moisture sensor and receive
///        the current moisture data.
void trigger_moisture_sensor(void);

#endif