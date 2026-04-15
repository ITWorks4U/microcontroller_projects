#ifndef LIGHT_SETTINGS_H
#define LIGHT_SETTINGS_H

#include <FastLED.h>            //  required library for WS2812 LED strip (https://github.com/FastLED/FastLED)

/////
/// constants
/////
#define NUMBER_LEDS      144    //  1m, 144 LEDs
#define PIN_LED_STRIPE   13     //  pin number for LED control

/////
/// structures
/////

enum class ColorCode {
    MORNING,                    //  RGB: 255,120,0 (orange)
    EVENING,                    //  RGB: 15,0,127  (blue / violet)
    TURN_OFF                    //  RGB: 0,0,0     (black)
};

/////
/// prototypes
/////

/// @brief Initializing the LED stripe.
void init_led_stripe(void);

/// @brief Toggle the LED stripe to turn this on or off depending on the second
///        argument. If fade_in is true, then the the LED stripe fades in.
///        The certain color code determines which light is going to show on all 144 LEDs.
/// @param cc color code to use
/// @param fade_in trigger, if the light shall be fade in or out; defaults to false
void toggle_led_stripe(const ColorCode cc, bool fade_in = false);

#endif