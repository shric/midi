//
// Created by Chris Young on 22/4/20.
//
#include "imgui.h"

#include "Piano.h"

static bool has_black(int key) {
    return (!((key - 1) % 7 == 0 || (key - 1) % 7 == 3) && key != 51);
}

void Piano::up(int key) {
    key_states[key] = 0;
}

void Piano::down(int key, int velocity) {
    key_states[key] = velocity;

}

void Piano::draw(bool *show) {
    ImU32 Black = IM_COL32(0, 0, 0, 255);
    ImU32 White = IM_COL32(255, 255, 255, 255);
    ImU32 Red = IM_COL32(255,0,0,255);
    ImGui::Begin("Keyboard", show);
    ImDrawList *draw_list = ImGui::GetWindowDrawList();
    ImVec2 p = ImGui::GetCursorScreenPos();
    int width = 20;
    int cur_key = 21;
    for (int key = 0; key < 52; key++) {
        ImU32 col = White;
        if (key_states[cur_key]) {
            col = Red;
        }
        draw_list->AddRectFilled(
                ImVec2(p.x + key * width, p.y),
                ImVec2(p.x + key * width + width, p.y + 120),
                col, 0, ImDrawCornerFlags_All);
        draw_list->AddRect(
                ImVec2(p.x + key * width, p.y),
                ImVec2(p.x + key * width + width, p.y + 120),
                Black, 0, ImDrawCornerFlags_All);
        cur_key++;
        if (has_black(key)) {
            cur_key++;
        }
    }
    cur_key = 22;
    for (int key = 0; key < 52; key++) {
        if (has_black(key)) {
            ImU32 col = Black;
            if (key_states[cur_key]) {
                col = Red;
            }
            draw_list->AddRectFilled(
                    ImVec2(p.x + key * width + width * 3 / 4, p.y),
                    ImVec2(p.x + key * width + width * 5 / 4 + 1, p.y + 80),
                    col, 0, ImDrawCornerFlags_All);
            draw_list->AddRect(
                    ImVec2(p.x + key * width + width * 3 / 4, p.y),
                    ImVec2(p.x + key * width + width * 5 / 4 + 1, p.y + 80),
                    Black, 0, ImDrawCornerFlags_All);

            cur_key += 2;
        } else {
            cur_key++;
        }
    }
    ImGui::End();
}

std::vector<int> Piano::current_notes() {
    std::vector<int> result{};
    for (int i = 0; i < 256; i++) {
        if (key_states[i]) {
            result.push_back(i);
        }
    }
    return result;
}
