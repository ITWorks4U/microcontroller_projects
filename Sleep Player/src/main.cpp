#include <Arduino.h>

#include "button_options.h"
#include "light_settings.h"
#include "music_settings.h"
#include "rtc_settings.h"
#include "error_code.h"

#define TIMEOUT_IN_MS       1000        //  1,000ms => 1s

void setup() {
    Serial.begin(9600);

    pinMode(LED_BUILTIN, OUTPUT);

    init_ds1302_module();
    init_led_stripe();
    init_mp3_module();

    pinMode(PIN_ISR_BUTTON, INPUT);
    attachInterrupt(digitalPinToInterrupt(PIN_ISR_BUTTON), isr_stop_music, RISING);

    //  turn off the LED stripe
    toggle_led_stripe(ColorCode::TURN_OFF);
    handle_error_codec(ErrorCodec::EVERYTHING_IS_FINE);
}

void loop() {
    static ulong time_ctr = 0;

    if (millis() - time_ctr >= TIMEOUT_IN_MS) {     //  each one elapsed second
        time_ctr = millis();

        RtcDateTime now = rtc.GetDateTime();

        #ifdef TIME_DISPLAY_AVAILABLE               //  see:    rtc_settings.h
        display_time(now);
        #endif

        bool on_start_morning = !on_still_playing && now.Hour() == 6 && now.Minute() == 0 && now.Second() == 0;       //  start in the morning
        bool on_end_morning =   on_still_playing && now.Hour() == 7 && now.Minute() == 0 && now.Second() == 0;        //  end in the morning
        bool on_start_evening = !on_still_playing && now.Hour() == 19 && now.Minute() == 0 && now.Second() == 0;      //  start in the evening
        bool on_end_evening =   on_still_playing && now.Hour() == 20 && now.Minute() == 0 && now.Second() == 0;       //  end in the evening

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
            play_music(/*music_number: */4, /*volume: */12);
        }

        if (on_end_evening) {
            toggle_led_stripe(ColorCode::EVENING);
            stop_music();
        }
    }

    //  stop playing music, if the music is currently playing
    if (trigger_stop_music) {
        trigger_stop_music = false;

        if (on_still_playing) {
            toggle_led_stripe(ColorCode::TURN_OFF);
            stop_music();
        }
    }
}