#ifndef ERROR_CODE_H
#define ERROR_CODE_H

/*
* Depending on which error may appear at any time a way to figure out what kind
* of error has been triggered is going to show. Since no Serial instance shall be
* used, the built in LED may be used instead.
*
* description:
*   S := short show up (for 50 ms)
*   L := long show up (for 250 ms)
*   a break between two or more codes is given with a delay of 25ms
*
*   |           event               |    code   |   spent time  |       source              |   is critical |
*   |-------------------------------|-----------|---------------|---------------------------|---------------|
*   | everything is fine            |   S       |   50 ms       |   main.cpp:24             |   no          |
*   | update time on init           |   SL      |   325 ms      |   rtc_settings.cpp:12     |   no          |
*   | initialized invalid date time |   SLS     |   400 ms      |   rtc_settings.cpp:21     |   no          |
*   | RTC write protected           |   SLLS    |   650 ms      |   rtc_settings.cpp:29     |   no          |
*   | RTC is not running            |   SLLLS   |   825 ms      |   rtc_settings.cpp:34     |   no          |
*   | invalid date time             |   SS      |   125 ms      |   rtc_settings.cpp:52     |   no          |
*   | MP3 module unable to begin    |   LSSS    |   475 ms      |   music_settings.cpp:14   |   yes         |
*/

enum class ErrorCodec {
    EVERYTHING_IS_FINE,                 //  S
    UPDATE_TIME_ON_INIT,                //  SL
    INVALID_DATE_TIME_ON_INIT,          //  SLS
    RTC_WRITE_PROTECTED,                //  SLLS
    RTC_IS_NOT_RUNNING,                 //  SLLLS
    INVALID_DATE_TIME_ON_RUNNING,       //  SS
    MP3_MODULE_INIT_ERROR               //  LSSS
};

/// @brief Depending on given error codec a certain sequence
///        for the built in LED is going to show.
/// @param ec the codec to use
void handle_error_codec(const ErrorCodec ec);

#endif