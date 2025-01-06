#include <game_engine/util/audio.h>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

#include <stdio.h>

ma_engine engine;
ma_result result;

void GameEngine_AudioInit() {
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        exit(1);
    }
}

void GameEngine_AudioDestroy() {
    ma_engine_uninit(&engine);
}

void GameEngine_AudioPlaySound(const char *filepath) {
    ma_engine_play_sound(&engine, filepath, NULL);
}