#include <Arduino.h>
#include <vector>
#include "error_code.h"

/////
/// internal definitions
/////
static const int pause_time_ms = 25;
static const int short_time_ms = 50;
static const int long_time_ms = 250;

void handle_error_codec(const ErrorCodec ec) {
    std::vector<int> v;

    switch(ec) {
        case ErrorCodec::UPDATE_TIME_ON_INIT:
            v.push_back(short_time_ms);
            v.push_back(pause_time_ms);
            v.push_back(long_time_ms);
            break;
        case ErrorCodec::INVALID_DATE_TIME_ON_INIT:
            v.push_back(short_time_ms);
            v.push_back(pause_time_ms);
            v.push_back(long_time_ms);
            v.push_back(pause_time_ms);
            v.push_back(short_time_ms);
            break;
        case ErrorCodec::RTC_WRITE_PROTECTED:
            v.push_back(short_time_ms);
            v.push_back(pause_time_ms);
            v.push_back(long_time_ms);
            v.push_back(pause_time_ms);
            v.push_back(long_time_ms);
            v.push_back(pause_time_ms);
            v.push_back(short_time_ms);
            break;
        case ErrorCodec::RTC_IS_NOT_RUNNING:
            v.push_back(short_time_ms);
            v.push_back(pause_time_ms);
            v.push_back(long_time_ms);
            v.push_back(pause_time_ms);
            v.push_back(long_time_ms);
            v.push_back(pause_time_ms);
            v.push_back(long_time_ms);
            v.push_back(pause_time_ms);
            v.push_back(short_time_ms);
            break;
        case ErrorCodec::INVALID_DATE_TIME_ON_RUNNING:
            v.push_back(short_time_ms);
            v.push_back(pause_time_ms);
            v.push_back(short_time_ms);
            break;
        case ErrorCodec::MP3_MODULE_INIT_ERROR:
            v.push_back(long_time_ms);
            v.push_back(pause_time_ms);
            v.push_back(short_time_ms);
            v.push_back(pause_time_ms);
            v.push_back(short_time_ms);
            v.push_back(pause_time_ms);
            v.push_back(short_time_ms);
            break;
        case ErrorCodec::EVERYTHING_IS_FINE:
            v.push_back(short_time_ms);
            break;
        default:
            //  for any case(s) in the future
            return;
    }

    for(int element : v) {
        switch(element) {
            case pause_time_ms:
                digitalWrite(LED_BUILTIN, LOW);
                delay(pause_time_ms);
                break;
            case short_time_ms:
                digitalWrite(LED_BUILTIN, HIGH);
                delay(short_time_ms);
                break;
            case long_time_ms:
                digitalWrite(LED_BUILTIN, HIGH);
                delay(long_time_ms);
                break;
        }
    }

    //  turn off the built in LED, if not already done yet
    digitalWrite(LED_BUILTIN, LOW);
}