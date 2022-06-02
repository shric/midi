//
// Created by Chris Young on 22/4/20.
//

#ifndef MIDI_MIDI_H
#define MIDI_MIDI_H

#include <functional>

#include <portmidi.h>
#include <porttime.h>

class Midi {
    PmDeviceID deviceID;
    PortMidiStream *stream;
public:
    virtual ~Midi();

private:
    PmEvent buffer[1024];
public:
    void poll(std::function<void(PmTimestamp, uint8_t, PmMessage, PmMessage)> callback, bool debug = false);
    Midi();
};


#endif //MIDI_MIDI_H
