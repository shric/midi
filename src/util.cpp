//
// Created by Chris Young on 25/4/20.
//

#include <vector>
#include <iostream>
#include "util.h"

std::string midiNoteString(uint8_t note) {
    static const char *base[] = {
            "C", "C#",
            "D", "D#",
            "E",
            "F", "F#",
            "G", "G#",
            "A", "A#",
            "B"
    };
    int octave = note / 12 - 1;
    note %= 12;
    char buf[50];
    snprintf(buf, sizeof buf, "%s%d", base[note], octave);
    return std::string(buf);
}

std::string midiChordString(std::vector<int> notes) {
    char buf[50];
    if (notes.size() == 3) {
        if (notes[2]-notes[1] == 3 && notes[1]-notes[0] == 4) {
            snprintf(buf, sizeof buf, "%s major", midiNoteString(notes[0]).c_str());
            return std::string(buf);
        } else if (notes[2]-notes[1] == 4 && notes[1]-notes[0] == 3) {
            snprintf(buf, sizeof buf, "%s minor", midiNoteString(notes[0]).c_str());
            return std::string(buf);
        }
    }
    return std::string("");
}

std::string timestampString(PmTimestamp timestamp) {
    char buf[100] = {0};

    unsigned int millis = timestamp % 1000;
    timestamp /= 1000;

    unsigned int seconds = timestamp % 60;
    timestamp /= 60;

    unsigned int minutes = timestamp % 60;
    timestamp /= 60;

    unsigned int hours = timestamp % 24;
    timestamp /= 24;

    snprintf(buf, sizeof buf, "%02d:%02d:%02d.%03d", hours, minutes, seconds, millis);
    return std::string(buf);
}
