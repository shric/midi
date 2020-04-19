//
// Created by Chris Young on 25/4/20.
//
#include <SDL.h>

#include "Audio.h"

Audio::Audio() {
    SDL_AudioSpec want, have;
    SDL_memset(&want, 0, sizeof want);
    want.freq = 44100;
    want.format = AUDIO_S16;
    want.channels = 2;
    want.samples = 4096;
    audio = SDL_OpenAudioDevice(nullptr, false, &want, &have, 0);
}
