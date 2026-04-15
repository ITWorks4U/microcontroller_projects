#include "button_options.h"

volatile bool trigger_stop_music = false;

void isr_stop_music(void) {
    // no need to use a button debounce algorithm,
    // because this event is going to trigger once
    trigger_stop_music = true;
}