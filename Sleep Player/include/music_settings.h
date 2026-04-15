#ifndef MUSIC_SETTINGS_H
#define MUSIC_SETTINGS_H

#include <DFRobotDFPlayerMini.h>    //  required library for MP3-TF-16P module (https://github.com/DFRobot/DFRobotDFPlayerMini)

/////
/// constants
/////

#define BAUD_MP3_PLAYER 9600        //  the MP3-TF-16P must use this BAUD rate

//  settings for MP3-TF-16P
//  NOTE: Since an ESP32 is in use, this hardware
//        serial driver is already known and don't
//        need any additional setup
#define FPSerial Serial1

/////
/// external
/////

extern bool on_still_playing;       //  check, if the media player is still playing

/////
/// prototypes
/////

/// @brief Initializing the MP3 module.
void init_mp3_module(void);

//  Print some information about MP3-TF-16P's action, like
//  an error message or a status of the current audio file
//  or else.

/// @brief Try to play the given music number and its volume level.
///        If the number was unable to find, no music is going to play.
///        The volume comes with a range between [0..30].
/// @param music_number the used number to play
/// @param volume the used volume
void play_music(uint8_t music_number, uint8_t volume);

/// @brief Stop playing the current music. This happens after the certain
///        elapsed time (1 hour) or if the ISR_BUTTON has been pressed.
void stop_music(void);

#endif