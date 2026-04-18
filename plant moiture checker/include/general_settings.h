#ifndef GENERAL_SETTINGS_H
#define GENERAL_SETTINGS_H

#ifndef __cplusplus
#include <stdbool.h>
#endif

/////
/// definitions
/////

#define PIN_POT_TIME_SPAN    A0        // 10 kOhm potentiometer for time span [3..24] h
#define SHORTEST_TIME_HOURS  3         // minimum: 3 hours
#define LONGEST_TIME_HOURS   24        // maximum: 24 hours

#define TIMEOUT_IN_MS        1000      // 1,000 ms for the next runtime sequence
#define HOUR_IN_SECONDS      3600      // 3,600s => 1h

typedef unsigned long ulong_t;

/////
/// external
/////

/// @brief Depending on how many moiture sensors are truly plugged in,
///        each sensor comes with a delay of 100ms to prepare sensor data.
///
///        Since a delay() function is in use (runtime.c:71), the delayed time
///        needs to be subtracted in loop() function for the next elapsed second
///        to prevent a continiously delay after many hours or days.
extern unsigned int wait_time_nbr_of_sensors;

/////
/// function prototypes
/////

/// @brief On first runtime check which device is available.
///
///        The minimal time consumes 500ms and can be
///        extended up to 1.5 seconds.
/// @return true, if the initialization was successful, otherwise false
bool scan_for_sensors(void);

/// @brief Scan, if a potentiometer on address A0 has been plugged in.
///
///        If true, then the timespan can be switched between 3 and 24 hours,
///        otherwise a fixed timespan of 24 hours is set.
/// @param  
void scan_for_potentiometer_existence(void);

/// @brief Run over and over again.
void runtime_sequence(void);

// NOTE: Since this project comes with raw C code, the map() function
//       is unknown. This is going to define here.
#ifndef __cplusplus

/// @brief Do a mapping. This function is identical to the commonly known map function,
///
///        however, in C this function does not exist.
/// @param x input value
/// @param in_min minimal incoming value
/// @param in_max maximal incoming value
/// @param out_min minimal outgoing value
/// @param out_max maximal outgoing value
/// @return the mapped value depending on given arguments
long map(long x, long in_min, long in_max, long out_min, long out_max);
#endif

#endif