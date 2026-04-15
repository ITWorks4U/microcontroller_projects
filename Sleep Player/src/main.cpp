#include <Arduino.h>

#include "button_options.h"
#include "light_settings.h"
#include "music_settings.h"
#include "rtc_settings.h"
#include "error_code.h"

#define TIMEOUT_IN_MS       1000        //  1,000ms => 1s
#define TIMEOUT_FOR_ONE_DAY 8640000     //  8,640,000ms => 86,400s => 24h

#define TEST_MODE                       //  only for testing

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    init_ds1302_module();
    init_led_stripe();
    init_mp3_module();

    pinMode(PIN_ISR_BUTTON, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PIN_ISR_BUTTON), isr_stop_music, RISING);

    //  turn off the LED stripe
    toggle_led_stripe(ColorCode::TURN_OFF);
    handle_error_codec(ErrorCodec::EVERYTHING_IS_FINE);
}

void loop() {
    #ifdef TEST_MODE
    static const ulong timeout_in_ms = 10000;
    static ulong last_time = 0;
    static int ctr = 0;
    static int upper_boundary = 4;

    if (millis() - last_time > timeout_in_ms) {
        last_time = millis();

        switch(ctr) {
            case 0:
                toggle_led_stripe(ColorCode::MORNING, /*fade_in: */ true);
                play_music(3, 20);
                // handle_error_codec(ErrorCodec::EVERYTHING_IS_FINE);
                break;
            case 1:
                toggle_led_stripe(ColorCode::MORNING);
                stop_music();
                // handle_error_codec(ErrorCodec::INVALID_DATE_TIME_ON_INIT);
                break;
            case 2:
                toggle_led_stripe(ColorCode::EVENING, /*fade_in: */ true);
                play_music(4, 10);
                // handle_error_codec(ErrorCodec::INVALID_DATE_TIME_ON_RUNNING);
                break;
            case 3:
                toggle_led_stripe(ColorCode::EVENING);
                stop_music();
                // handle_error_codec(ErrorCodec::MP3_MODULE_INIT_ERROR);
                break;
            case 4:
                // handle_error_codec(ErrorCodec::RTC_IS_NOT_RUNNING);
                break;
            case 5:
                // handle_error_codec(ErrorCodec::RTC_WRITE_PROTECTED);
                break;
            case 6:
                // handle_error_codec(ErrorCodec::UPDATE_TIME_ON_INIT);
                break;
            case 7:
                // digitalWrite(LED_BUILTIN, HIGH);

                // while(true) {
                //     delay(1);
                // }
                break;
        }

        ctr = (ctr + 1) % upper_boundary;
    }

    #else
    RtcDateTime now = rtc.GetDateTime();

    #ifdef TIME_DISPLAY_AVAILABLE       //  see:    rtc_settings.h
    display_time(now);
    #endif

    bool on_start_morning = !on_still_playing && now.Hour() == 6 && now.Minute() == 0 && now.Second() == 0;       //  start in the morning
    bool on_end_morning =   on_still_playing && now.Hour() == 7 && now.Minute() == 0 && now.Second() == 0;        //  end in the morning
    bool on_start_evening = !on_still_playing && now.Hour() == 21 && now.Minute() == 0 && now.Second() == 0;      //  start in the evening
    bool on_end_evening =   on_still_playing && now.Hour() == 22 && now.Minute() == 0 && now.Second() == 0;       //  end in the evening

    if (on_start_morning) {
        toggle_led_stripe(ColorCode::MORNING, /*fade_in: */ true);
        play_music(/*music_number: */1, /*volume: */20);
    }

    if (on_end_morning) {
        toggle_led_stripe(ColorCode::MORNING);
        stop_music();
    }

    if (on_start_evening) {
        toggle_led_stripe(ColorCode::EVENING, /*fade_in: */true);
        play_music(/*music_number: */2, /*volume: */10);
    }

    if (on_end_evening) {
        toggle_led_stripe(ColorCode::EVENING);
        stop_music();
    }

    //  only, if the STOP_BUTTON has been pressed
    if (trigger_stop_music) {
        trigger_stop_music = false;
        toggle_led_stripe(ColorCode::TURN_OFF);
        stop_music();
    }

    //  wait one second
    delay(TIMEOUT_IN_MS);
    #endif
}