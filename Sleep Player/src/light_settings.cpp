#include "light_settings.h"

static CRGB _led_stripe[NUMBER_LEDS];

void init_led_stripe(void) {
    FastLED.addLeds<WS2812B, PIN_LED_STRIPE, GRB>(_led_stripe, NUMBER_LEDS);
    FastLED.setBrightness(50);
}

void toggle_led_stripe(const ColorCode cc, bool fade_in) {
    const int steps = 25;
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;

    switch(cc) {
        case ColorCode::MORNING:
            red = 63;
            green = 60;
            blue = 0;
            break;
        case ColorCode::EVENING:
            red = 7;
            green = 0;
            blue = 63;
            break;
        case ColorCode::TURN_OFF:
            red = 0;
            green = 0;
            blue = 0;

            // turn all LEDs off immediately
            fill_solid(_led_stripe, NUMBER_LEDS, CRGB(red, green, blue));
            FastLED.show();
            return;
    }

    for (int s = 0; s <= steps; s++) {
        int i = fade_in ? s : (steps - s);

        uint8_t r = (red   * i) / steps;
        uint8_t g = (green * i) / steps;
        uint8_t b = (blue  * i) / steps;

        fill_solid(_led_stripe, NUMBER_LEDS, CRGB(r, g, b));
        FastLED.show();
        delay(15);
    }
}