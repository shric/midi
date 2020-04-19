//
// Created by Chris Young on 25/4/20.
//

#ifndef MIDI_LOG_H
#define MIDI_LOG_H

#include "imgui.h"

class Log {
private:
    ImGuiTextBuffer     Buf;
    ImGuiTextFilter     Filter;
    ImVector<int>       LineOffsets;        // Index to lines offset. We maintain this with AddLog() calls, allowing us to have a random access on lines
    bool                AutoScroll;     // Keep scrolling if already at the bottom
    void Clear();
public:
    void    AddLog(const char* fmt, ...) IM_FMTARGS(2);
    void Draw(const char *title, bool *p_open = nullptr);
    Log();
};


#endif //MIDI_LOG_H
