#ifndef BUTTON_OPTIONS_H
#define BUTTON_OPTIONS_H

/////
/// constants
/////

#define PIN_ISR_BUTTON  12      //  pull-up button to stop the music, when playing

/////
/// external
/////

/// @brief internal flag whenever the music
///        shall be stopped; triggered by PIN_ISR_BUTTON
extern volatile bool trigger_stop_music;

/////
/// function prototype
/////

/// @brief ISR function when the PIN_ISR_BUTTON has been pressed.
void isr_stop_music(void);

#endif