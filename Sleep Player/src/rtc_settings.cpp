#include "rtc_settings.h"
#include "error_code.h"

static ThreeWire _tw(PIN_DAT, PIN_CLK, PIN_RST);
RtcDS1302<ThreeWire> rtc(_tw);

void init_ds1302_module() {
    rtc.Begin();
 
    //  NOTE: No need to set up the time over and over again on init.
    //        This macro is not defined by default. => see: rtc_settings.h
    #ifdef SETUP_TIMER_MODULE
    handle_error_codec(ErrorCodec::UPDATE_TIME_ON_INIT);

    //  NOTE: On compile time the detected time will be set here before this
    //        instance is going to call on init. Thus, this time lies
    //        some seconds behind the real time.
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    rtc.SetDateTime(compiled);

    if (!rtc.IsDateTimeValid()) {
        // Common Causes:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing
        handle_error_codec(ErrorCodec::INVALID_DATE_TIME_ON_INIT);
        rtc.SetDateTime(compiled);
    }

    if (rtc.GetIsWriteProtected()) {
        handle_error_codec(ErrorCodec::RTC_WRITE_PROTECTED);
        rtc.SetIsWriteProtected(false);
    }

    if (!rtc.GetIsRunning()) {
        handle_error_codec(ErrorCodec::RTC_IS_NOT_RUNNING);
        rtc.SetIsRunning(true);
    }

    RtcDateTime now = rtc.GetDateTime();
    if (now < compiled) {
        //  RTC is older than compile time. => RTC is going to update
        rtc.SetDateTime(compiled);
    }

    //  otherwise the RTC is newer that the compile time or this is equal
    //  => no need to do anything here
    #endif            // SETUP_TIMER_MODULE
}

#ifdef TIME_DISPLAY_AVAILABLE
void display_time(const RtcDateTime dt) {
    if (!dt.IsValid()) {
        handle_error_codec(ErrorCodec::INVALID_DATE_TIME_ON_RUNNING);

        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        return;
    }

    String s = String(dt.Hour()) + ":" + String(dt.Minute()) + ":" + String(dt.Second());
    Serial.println(s);
}
#endif

TimeSetup check_for_switch_time(void) {
    //TODO: needs to be updated
    //      whenever the last sunday on March has been detected: switch to summer time
    //      whenever the last sunday on October has been detected: switch to winter time
    //
    //      Since the calendary days are unequeal each year an unique way shall be used here.
    return TimeSetup::NO_SWITCH_REQUIRED;
}

void update_time(TimeSetup toggled_setup) {

}