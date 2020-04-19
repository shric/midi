//
// Created by Chris Young on 22/4/20.

#include <iostream>
#include <cstdlib>

#include "Midi.h"


template<typename T>
void must(T err) {
    if (err != 0) {
        std::cout << "Error: " << Pm_GetErrorText(static_cast<PmError>(err));
        std::exit(1);
    }
}

PmDeviceID init() {
    must(Pm_Initialize());
    Pt_Start(1, nullptr, nullptr);
    auto did = Pm_GetDefaultInputDeviceID();
    if (did < 0) {
        std::cout << "Couldn't find any MIDI devices for input."
                  << std::endl;
        return did;
    }
    int count = Pm_CountDevices();
    for (int id = 0; id < count; id++) {
        auto di = Pm_GetDeviceInfo(id);
        std::cout << di->interf << "/" << di->name
                  << ", input: " << di->input
                  << ", output: " << di->output
                  << ", opened: " << di->opened;
        if (id == did) {
            std::cout << " (DEFAULT)";
        }
        std::cout << std::endl;
    }
    return did;
}

void shutdown(PortMidiStream *stream) {
    must(Pm_Close(stream));
    must(Pt_Stop());
}


Midi::Midi() {
    deviceID = init();
    stream = nullptr;
    if (deviceID >= 0) {
        must(Pm_OpenInput(&stream, deviceID, nullptr, 1024, nullptr, nullptr));
    }

}

void Midi::poll(std::function<void(PmTimestamp, uint8_t, PmMessage, PmMessage)> callback, bool debug) {
    PmError err = Pm_Poll(stream);
    if (err > 0) {
        int count = Pm_Read(stream, buffer, 1024);
        if (count > 0) {
            for (int ev = 0; ev < count; ev++) {
                PmTimestamp timestamp = buffer[ev].timestamp;
                PmMessage message = buffer[ev].message;
                uint8_t Status = ((uint32_t) message & 0xFFu);
                PmMessage Data1 = (((uint32_t) message >> 8) & 0xFFu);
                PmMessage Data2 = ((uint32_t) message >> 16 & 0xFFu);
                if (Data1 || Data2) {
                    callback(timestamp, Status, Data1, Data2);
                }
            }
        }
    }
}

Midi::~Midi() {
    shutdown(stream);
}
