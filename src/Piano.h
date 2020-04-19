//
// Created by Chris Young on 22/4/20.
//

#ifndef MIDI_PIANO_H
#define MIDI_PIANO_H


#include <vector>

class Piano {
    int key_states[256] = {0};
public:
    void up(int key);
    void draw(bool *show);
    void down(int key, int velocity);
    std::vector<int> current_notes();
};


#endif //MIDI_PIANO_H
