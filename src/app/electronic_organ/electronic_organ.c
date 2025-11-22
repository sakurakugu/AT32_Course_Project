#include "electronic_organ.h"
#include "music.h"
#include "beep.h"

// 电子琴：按钮矩阵点击发声
void electronic_organ_btnm_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_VALUE_CHANGED)
        return;

    lv_obj_t *btnm = lv_event_get_target(e);
    uint16_t id = lv_btnmatrix_get_selected_btn(btnm);
    const char *txt = lv_btnmatrix_get_btn_text(btnm, id);
    if (!txt || !txt[0])
        return;

    uint16_t freq = 0;
    int n = (txt[1] >= '0' && txt[1] <= '7') ? (txt[1] - '0') : 0;
    if (n < 1 || n > 7)
        return;

    switch (txt[0]) {
    case 'L':
        switch (n) {
        case 1:
            freq = TONE_L1;
            break;
        case 2:
            freq = TONE_L2;
            break;
        case 3:
            freq = TONE_L3;
            break;
        case 4:
            freq = TONE_L4;
            break;
        case 5:
            freq = TONE_L5;
            break;
        case 6:
            freq = TONE_L6;
            break;
        case 7:
            freq = TONE_L7;
            break;
        }
        break;
    case 'M':
        switch (n) {
        case 1:
            freq = TONE_M1;
            break;
        case 2:
            freq = TONE_M2;
            break;
        case 3:
            freq = TONE_M3;
            break;
        case 4:
            freq = TONE_M4;
            break;
        case 5:
            freq = TONE_M5;
            break;
        case 6:
            freq = TONE_M6;
            break;
        case 7:
            freq = TONE_M7;
            break;
        }
        break;
    case 'H':
        switch (n) {
        case 1:
            freq = TONE_H1;
            break;
        case 2:
            freq = TONE_H2;
            break;
        case 3:
            freq = TONE_H3;
            break;
        case 4:
            freq = TONE_H4;
            break;
        case 5:
            freq = TONE_H5;
            break;
        case 6:
            freq = TONE_H6;
            break;
        case 7:
            freq = TONE_H7;
            break;
        }
        break;
    default:
        break;
    }

    if (freq > 0) {
        Beep_SetFreq(freq);
        // 点击发音：短促按键音（50ms）
        Beep_Start(5, 1, 1);
    }
}