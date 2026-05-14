#ifndef MOISTURE_DATA_H
#define MOISTURE_DATA_H

#ifndef __cplusplus                      // not available for raw C code
#include <stdbool.h>
#endif

/////
/// constants
/////

#define THRESHOLD_MOITURE       2000     // the limitation, when the pump shall start
#define DURATION_SENSOR_IN_MS   100      // 100ms delay before reading the next data
#define MAX_NBR_OF_DEVICES      4        // up to 4 sensors and 4 pumps
#define MIN_RESP_SENSOR_VALUE   50       // minimal responding analog sensor value
#define TINY_DELAY_PWR_SENSOR   125      // 125ms for inital sequence

/////
/// structures
/////

/// @brief Container for moisture sensor.
///
///        A pump can only be triggered, if the coresponding
///        sensor is available.
typedef struct {
    bool exits;                          // true := available, false := unavailable
    int data;                            // in a range of [400..2,000]
} Device;

/////
/// function prototypes
/////

/// @brief Trigger the moisture sensor and receive
///        the current moisture data.
void trigger_moisture_sensor(void);

#endif