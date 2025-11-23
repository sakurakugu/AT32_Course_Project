#include "electronic_organ.h"
#include "board.h"
#include "music.hpp"

// 电子琴：按钮矩阵点击发声
void electronic_organ_btnm_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_VALUE_CHANGED) return;

    lv_obj_t *btnm = lv_event_get_target(e);
    uint16_t id = lv_btnmatrix_get_selected_btn(btnm);
    const char *txt = lv_btnmatrix_get_btn_text(btnm, id);
    if (!txt || !txt[0]) return;

    uint16_t freq = 0;
    int n = (txt[1] >= '0' && txt[1] <= '7') ? (txt[1] - '0') : 0;
    if (n < 1 || n > 7) return;

    switch (txt[0]) {
    case 'L':
        switch (n) {
        case 1: freq = Tone::L1; break;
        case 2: freq = Tone::L2; break;
        case 3: freq = Tone::L3; break;
        case 4: freq = Tone::L4; break;
        case 5: freq = Tone::L5; break;
        case 6: freq = Tone::L6; break;
        case 7: freq = Tone::L7; break;
        }
        break;
    case 'M':
        switch (n) {
        case 1: freq = Tone::M1; break;
        case 2: freq = Tone::M2; break;
        case 3: freq = Tone::M3; break;
        case 4: freq = Tone::M4; break;
        case 5: freq = Tone::M5; break;
        case 6: freq = Tone::M6; break;
        case 7: freq = Tone::M7; break;
        }
        break;
    case 'H':
        switch (n) {
        case 1: freq = Tone::H1; break;
        case 2: freq = Tone::H2; break;
        case 3: freq = Tone::H3; break;
        case 4: freq = Tone::H4; break;
        case 5: freq = Tone::H5; break;
        case 6: freq = Tone::H6; break;
        case 7: freq = Tone::H7; break;
        }
        break;
    default: break;
    }

    if (freq > 0) {
        Board::GetInstance().GetBeep().SetFreq(freq);
        // 点击发音：短促按键音（50ms）
        Board::GetInstance().GetBeep().Start(5, 1, 1);
    }
}