#ifndef RTC_SETTINGS_H
#define RTC_SETTINGS_H

#include <RtcDS1302.h>              //  required library for DS1302 RTC module (https://github.com/Makuna/Rtc?tab=LGPL-3.0-1-ov-file)
#include <ThreeWire.h>

/////
/// constants
/////

#define PIN_RST 5                   //  RST
#define PIN_CLK 18                  //  CLK
#define PIN_DAT 23                  //  DAT

// #define SETUP_TIMER_MODULE       //  only in use, if the time needs to be updated
                                    //  NOTE:   a delay of estimated 10 +/- 5 seconds may appear,
                                    //          because the build time consumes a bit of time

#define TIME_DISPLAY_AVAILABLE   //  only if a LCD has been plugged in

/////
/// structures
/////

enum class TimeSetup {
    NO_SWITCH_REQUIRED,
    SWITCH_TO_SUMMER_TIME,          //  last sunday of March
    SWITCH_TO_WINTER_TIME           //  last sunday of October
};

/////
/// external
/////

extern RtcDS1302<ThreeWire> rtc;    //  DS1302 RTC module
extern bool on_winter_time_switch;  //  flag to switch to winter time, if required

/////
/// prototypes
/////

/// @brief Initializing the DS1302 RTC module.
void init_ds1302_module(void);

#ifdef TIME_DISPLAY_AVAILABLE
/// @brief Display the current time on a LCD.
/// @param dt the lived received timestamp
void display_time(const RtcDateTime dt);
#endif

/// @brief Check, if the time needs to be updated. Only for summer and winter time event.
/// @return if NO_SWITCH_REQUIRED returns, then update_time is going to use here
TimeSetup check_for_switch_time(void);

/// @brief Update the time on detected time setup. Doesn't work for "NO_SWITCH_REQUIRED".
/// @param toggled_setup a flag to update the current time
void update_time(TimeSetup toggled_setup);

#endif