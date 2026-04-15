#include "music_settings.h"
#include "error_code.h"

static DFRobotDFPlayerMini _mp_player;          //  MP3 module instance
bool on_still_playing = false;

void init_mp3_module(void) {
    //  https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299#

    //  initial setup for RX/TX for an ESP32 (DOITESP32 DEVKIT V1) only
    //  NOTE: RX and TX can be any pin number.
    FPSerial.begin(BAUD_MP3_PLAYER, SERIAL_8N1, /*rx =*/16, /*tx =*/17);

    if (!_mp_player.begin(FPSerial)) {
        handle_error_codec(ErrorCodec::MP3_MODULE_INIT_ERROR);

        //  possible reason: no micro SD has been plugged in
        while(true){
            delay(1);
        }
    }
}

void play_music(uint8_t music_number, uint8_t volume) {
    on_still_playing = true;
    _mp_player.volume(volume);
    _mp_player.play(music_number);
}

void stop_music(void) {
    on_still_playing = false;
    _mp_player.stop();
}