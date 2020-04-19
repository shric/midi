//
// Created by Chris Young on 25/4/20.
//
#include <string>

#include <portmidi.h>

#ifndef MIDI_UTIL_H
#define MIDI_UTIL_H

std::string timestampString(PmTimestamp timestamp);
std::string midiNoteString(uint8_t note);
std::string midiChordString(std::vector<int> notes);

#endif //MIDI_UTIL_H
