#include "music.hpp"
#include "FreeRTOS.h"
#include "board.h"
#include "delay.h"
#include "task.h"

/* 音高表：music_arrX 中的数值作为索引，映射到实际频率 */
static const uint16_t note_freqs[] = {
    TONE_REST, TONE_L1, TONE_L2, TONE_L3, TONE_L4, TONE_L5, TONE_L6, TONE_L7, TONE_M1, TONE_M2, TONE_M3,
    TONE_M4,   TONE_M5, TONE_M6, TONE_M7, TONE_H1, TONE_H2, TONE_H3, TONE_H4, TONE_H5, TONE_H6, TONE_H7,
    // Tone::REST,
    // Tone::L1, Tone::L2, Tone::L3, Tone::L4, Tone::L5, Tone::L6, Tone::L7,
    // Tone::M1, Tone::M2, Tone::M3, Tone::M4, Tone::M5, Tone::M6, Tone::M7,
    // Tone::H1, Tone::H2, Tone::H3, Tone::H4, Tone::H5, Tone::H6, Tone::H7,
};

// 红尘情歌
uint8_t music_arr[] = { // 音调
    5, 5, 6, 8, 7, 6, 5, 6, 0, 0, 5, 5, 6, 8, 7, 6, 5, 3, 0, 0,  2,  2, 3, 5,  3, 5, 6, 3, 2, 1, 6,
    6, 5, 6, 5, 3, 6, 5, 0, 0, 5, 5, 6, 8, 7, 6, 5, 6, 0, 0, 5,  5,  6, 8, 7,  6, 5, 3, 0, 0, 2, 2,
    3, 5, 3, 5, 6, 3, 2, 1, 6, 6, 5, 6, 5, 3, 6, 1, 0, 8, 9, 10, 10, 9, 8, 10, 9, 8, 6, 0, 6, 8, 9,
    9, 8, 6, 9, 8, 6, 5, 0, 2, 3, 5, 5, 3, 5, 5, 6, 8, 7, 6, 6,  10, 9, 9, 8,  6, 5, 6, 8};

// 荷塘月色
uint8_t music_arr1[] = { // 音调
    8,  12, 6,  5,  6, 8,  8,  9,  10, 9,  9,  8,  9,  9,  12, 12, 10, 10, 9,  10, 8,  8,  6, 5, 12,
    10, 9,  10, 9,  8, 9,  9,  8,  9,  9,  10, 9,  8,  6,  9,  8,  8,  8,  6,  5,  6,  8,  8, 9, 10,
    9,  9,  8,  9,  9, 12, 12, 10, 10, 9,  10, 8,  8,  8,  6,  5,  12, 10, 9,  10, 9,  8,  9, 9, 8,
    9,  9,  10, 9,  8, 6,  9,  8,  10, 12, 12, 12, 12, 13, 12, 10, 9,  8,  13, 15, 13, 10, 9, 8, 6,
    9,  9,  10, 10, 9, 10, 12, 12, 12, 12, 13, 12, 10, 9,  8,  6,  8,  6,  5,  9,  10, 8,  0};

// 沉默是金
uint8_t music_arr2[] = { // 音调
    10, 12, 12, 13, 12, 12, 10, 9,  10, 10, 10, 9,  8,  8,  13, 15, 15, 16, 15, 15, 13, 12, 10, 12, 13, 15, 15,
    16, 15, 15, 13, 12, 10, 12, 12, 12, 13, 10, 10, 12, 10, 9,  13, 12, 10, 9,  10, 12, 10, 12, 12, 13, 12, 12,
    10, 9,  10, 10, 10, 9,  8,  8,  13, 15, 15, 16, 15, 15, 13, 12, 10, 12, 13, 15, 15, 16, 15, 15, 13, 12, 10,
    12, 12, 12, 13, 10, 10, 12, 10, 9,  13, 12, 10, 9,  8,  15, 15, 16, 17, 17, 17, 16, 15, 13, 15, 15, 13, 12,
    12, 13, 15, 15, 16, 15, 15, 13, 12, 10, 12, 13, 15, 15, 16, 15, 13, 12, 12, 13, 10, 10, 12, 10, 9,  10, 9,
    9,  10, 11, 12, 10, 12, 12, 13, 12, 12, 10, 9,  10, 10, 10, 9,  8,  8,  13, 15, 15, 16, 15, 15, 13, 12, 10,
    12, 13, 15, 15, 16, 15, 15, 13, 12, 10, 12, 12, 12, 13, 10, 10, 12, 10, 9,  9,  13, 12, 10, 9,  8};

// 红尘情歌
uint8_t time_arr[] = { // 时间
    2, 4, 2, 2, 2, 2, 2, 8, 4, 4, 2, 4, 2, 2, 2, 2, 2, 8, 4, 4, 2, 4, 2, 4, 2, 2, 4, 2, 2, 8, 2,
    4, 2, 2, 2, 2, 2, 8, 4, 4, 2, 4, 2, 2, 2, 2, 2, 8, 4, 4, 2, 4, 2, 2, 2, 2, 2, 8, 4, 4, 2, 4,
    2, 4, 2, 2, 4, 2, 2, 8, 2, 4, 2, 2, 2, 2, 2, 8, 4, 2, 2, 2, 4, 2, 2, 2, 2, 2, 8, 4, 2, 2, 2,
    4, 2, 2, 2, 2, 2, 8, 4, 2, 2, 2, 4, 2, 2, 5, 2, 6, 2, 4, 2, 2, 2, 4, 2, 4, 2, 2, 12};

// 荷塘月色
uint8_t time_arr1[] = { // 时间
    2, 4, 2, 4, 4, 4, 2, 2, 8, 2, 4, 2, 4, 2, 2, 2, 2, 2, 2, 8, 2, 4, 2, 4, 4, 2, 2, 2, 2, 8,  2,
    4, 2, 2, 4, 2, 2, 2, 2, 2, 8, 2, 4, 2, 4, 4, 2, 4, 2, 8, 2, 4, 2, 4, 2, 2, 2, 2, 2, 2, 8,  2,
    2, 2, 2, 4, 4, 2, 2, 2, 2, 8, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 8, 2, 4, 2, 4, 4, 2, 2, 2, 2,  8,
    2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 6, 2, 4, 2, 4, 4, 2, 2, 2, 2, 8, 2, 2, 2, 2, 4, 4, 12, 4};

// 沉默是金
uint8_t time_arr2[] = { // 时间
    2, 2, 2,  1, 1, 4, 1, 3,  2, 2, 2,  1, 1, 8, 2, 2,  2, 1, 1, 4, 2, 2, 2,  16, 2, 2, 2, 1, 1, 4, 2,  2,
    2, 2, 2,  2, 1, 1, 4, 2,  2, 6, 2,  4, 2, 2, 2, 16, 2, 2, 2, 1, 1, 4, 1,  3,  2, 2, 2, 1, 1, 8, 2,  2,
    2, 1, 1,  4, 2, 2, 2, 16, 2, 2, 2,  1, 1, 4, 2, 2,  2, 2, 2, 2, 1, 1, 4,  2,  2, 6, 2, 4, 2, 2, 16, 4,
    2, 1, 1,  3, 1, 1, 3, 2,  2, 2, 1,  1, 8, 2, 2, 2,  1, 1, 4, 2, 2, 2, 16, 6,  2, 2, 2, 4, 2, 2, 2,  1,
    1, 4, 2,  2, 6, 2, 4, 2,  2, 2, 16, 2, 2, 2, 1, 1,  4, 1, 3, 2, 2, 2, 1,  1,  8, 2, 2, 2, 1, 1, 4,  2,
    2, 2, 16, 2, 2, 2, 1, 1,  4, 2, 2,  2, 2, 2, 2, 1,  1, 4, 2, 2, 2, 4, 2,  2,  4, 2, 16};

extern "C" {
const uint8_t *music_arr_all[3] = {music_arr, music_arr1, music_arr2};
const uint8_t *time_arr_all[3] = {time_arr, time_arr1, time_arr2};
const uint16_t time_len_all[3] = {
    (uint16_t)(sizeof(time_arr) / sizeof(time_arr[0])),
    (uint16_t)(sizeof(time_arr1) / sizeof(time_arr1[0])),
    (uint16_t)(sizeof(time_arr2) / sizeof(time_arr2[0])),
};
}

/* 播放控制标志的实际定义 */
volatile int music_start = 0;
volatile int music_index = 0;
volatile int music_timer = 0;
volatile int music_resume = 0;
volatile int music_playing = 0;
volatile int music_song_id = 0;
volatile int music_switch_delay_ms = 0;

/* 播放一首歌：根据 music_song_id 选择曲目并播放 */
void Music::PlayOneSong() {
    const uint8_t *notes = nullptr;
    const uint8_t *times = nullptr;
    size_t total = 0;

    int sel = (music_song_id % 3 + 3) % 3;
    notes = music_arr_all[sel];
    times = time_arr_all[sel];
    total = time_len_all[sel];

    /* 起始索引由全局 music_index 控制，可从头或从中间继续 */
    for (; music_index < (int)total; ++music_index) {
        if (!music_playing) {
            break; /* 被外部停止 */
        }

        /* 暂停：在暂停期间保持短延时轮询，并立即静音 */
        if (music_resume) {
            Board::GetInstance().GetBeep().DisableOutput();
            delay_ms(50);
            /* 重做当前音符，不前进索引 */
            --music_index; /* for 循环会 ++，抵消保持当前 */
            continue;
        }

        uint8_t note_id = notes[music_index];
        uint16_t freq = (note_id < (sizeof(note_freqs) / sizeof(note_freqs[0]))) ? note_freqs[note_id] : 0;

        if (freq == 0) {
            Board::GetInstance().GetBeep().DisableOutput();
        } else {
            Board::GetInstance().GetBeep().SetFreq(freq);
            Board::GetInstance().GetBeep().EnableOutput();
        }

        int duration_units = times[music_index];
        if (duration_units <= 0) {
            duration_units = 1;
        }
        /* 单位为 100ms */
        delay_ms(duration_units * 100);
    }

    /* 结束本曲播放 */
    Board::GetInstance().GetBeep().DisableOutput();
    music_playing = 0;
    music_index = 0;
}

/* FreeRTOS 任务：根据控制标志开始/暂停播放 */
void TaskMusic([[maybe_unused]] void *pvParameters) {
    for (;;) {
        /* 外部请求开始播放 */
        if (music_start) {
            music_start = 0; /* 消耗启动请求 */
            int delay_ms_ = music_switch_delay_ms;
            music_switch_delay_ms = 0;
            if (delay_ms_ > 0) {
                Board::GetInstance().GetBeep().DisableOutput();
                delay_ms(delay_ms_);
            }
            music_index = 0;   /* 从头开始 */
            music_resume = 0;  /* 取消暂停 */
            music_playing = 1; /* 标记正在播放 */
        }

        if (music_playing) {
            Music::GetInstance().PlayOneSong();
        } else {
            /* 空闲，降低占用 */
            delay_ms(50);
        }
    }
}

#include "music.h"

// ===============================
// 音乐播放器事件实现
// ===============================

#ifdef KEIL_COMPILE

static void anim_img_angle_exec(void *var, int32_t v) {
    lv_img_set_angle((lv_obj_t *)var, v);
}

static void stylus_to_play_ready_cb(lv_anim_t *a) {
    (void)a;
    if (!lv_obj_is_valid(guider_ui.music_app_music_recode))
        return;
    lv_anim_del(guider_ui.music_app_music_recode, anim_img_angle_exec);
    ui_animation(guider_ui.music_app_music_recode, 2000, 0, 0, 3600, lv_anim_path_linear, LV_ANIM_REPEAT_INFINITE, 0, 0,
                 0, anim_img_angle_exec, NULL, NULL, NULL);
}

// 列表项点击：根据点击项设置曲目并开始播放
void music_list_item_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
        return;
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;
    lv_obj_t *target = lv_event_get_target(e);

    int sel = 0;
    if (target == ui->music_app_music_list_item0) {
        sel = 0;
    } else if (target == ui->music_app_music_list_item1) {
        sel = 1;
    } else if (target == ui->music_app_music_list_item2) {
        sel = 2;
    } else {
        return; // 未识别的项
    }

    music_song_id = sel;
    music_resume = 0;
    music_playing = 0;
    music_switch_delay_ms = 500;
    music_start = 1;

    // 播放按钮状态更新为“播放中”（显示暂停图标）
    if (lv_obj_is_valid(ui->music_app_music_player_or_pause_btn)) {
        lv_obj_clear_state(ui->music_app_music_player_or_pause_btn, LV_STATE_CHECKED);
    }

    if (lv_obj_is_valid(ui->music_app_music_stylus)) {
        lv_anim_del(ui->music_app_music_stylus, anim_img_angle_exec);
        ui_animation(ui->music_app_music_stylus, 400, 0, -240, 0, lv_anim_path_ease_in_out, 0, 0, 0, 0,
                     anim_img_angle_exec, NULL, stylus_to_play_ready_cb, NULL);
    } else if (lv_obj_is_valid(ui->music_app_music_recode)) {
        lv_anim_del(ui->music_app_music_recode, anim_img_angle_exec);
        ui_animation(ui->music_app_music_recode, 2000, 0, 0, 3600, lv_anim_path_linear, LV_ANIM_REPEAT_INFINITE, 0, 0,
                     0, anim_img_angle_exec, NULL, NULL, NULL);
    }
}

// 上一首：索引减一并循环，然后重启播放
void music_prev_btn_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
        return;
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;

    music_song_id = (music_song_id + 3 - 1) % 3;
    music_resume = 0;
    music_playing = 0;
    music_switch_delay_ms = 500;
    music_start = 1;

    if (lv_obj_is_valid(ui->music_app_music_player_or_pause_btn)) {
        lv_obj_clear_state(ui->music_app_music_player_or_pause_btn, LV_STATE_CHECKED);
    }

    if (lv_obj_is_valid(ui->music_app_music_stylus)) {
        lv_anim_del(ui->music_app_music_stylus, anim_img_angle_exec);
        ui_animation(ui->music_app_music_stylus, 400, 0, -240, 0, lv_anim_path_ease_in_out, 0, 0, 0, 0,
                     anim_img_angle_exec, NULL, stylus_to_play_ready_cb, NULL);
    } else if (lv_obj_is_valid(ui->music_app_music_recode)) {
        lv_anim_del(ui->music_app_music_recode, anim_img_angle_exec);
        ui_animation(ui->music_app_music_recode, 2000, 0, 0, 3600, lv_anim_path_linear, LV_ANIM_REPEAT_INFINITE, 0, 0,
                     0, anim_img_angle_exec, NULL, NULL, NULL);
    }
}

// 下一首：索引加一并循环，然后重启播放
void music_next_btn_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
        return;
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;

    music_song_id = (music_song_id + 1) % 3;
    music_resume = 0;
    music_playing = 0;
    music_switch_delay_ms = 500;
    music_start = 1;

    if (lv_obj_is_valid(ui->music_app_music_player_or_pause_btn)) {
        lv_obj_clear_state(ui->music_app_music_player_or_pause_btn, LV_STATE_CHECKED);
    }

    if (lv_obj_is_valid(ui->music_app_music_stylus)) {
        lv_anim_del(ui->music_app_music_stylus, anim_img_angle_exec);
        ui_animation(ui->music_app_music_stylus, 400, 0, -240, 0, lv_anim_path_ease_in_out, 0, 0, 0, 0,
                     anim_img_angle_exec, NULL, stylus_to_play_ready_cb, NULL);
    } else if (lv_obj_is_valid(ui->music_app_music_recode)) {
        lv_anim_del(ui->music_app_music_recode, anim_img_angle_exec);
        ui_animation(ui->music_app_music_recode, 2000, 0, 0, 3600, lv_anim_path_linear, LV_ANIM_REPEAT_INFINITE, 0, 0,
                     0, anim_img_angle_exec, NULL, NULL, NULL);
    }
}

void music_play_pause_btn_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (!(code == LV_EVENT_VALUE_CHANGED || code == LV_EVENT_CLICKED))
        return;
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;
    lv_obj_t *btn = lv_event_get_target(e);
    bool checked = lv_obj_has_state(btn, LV_STATE_CHECKED);

    if (checked) {
        if (music_playing) {
            music_resume = 1;
        }
        if (lv_obj_is_valid(ui->music_app_music_recode)) {
            lv_anim_del(ui->music_app_music_recode, anim_img_angle_exec);
        }
        if (lv_obj_is_valid(ui->music_app_music_stylus)) {
            lv_anim_del(ui->music_app_music_stylus, anim_img_angle_exec);
            int32_t cur = lv_img_get_angle(ui->music_app_music_stylus);
            ui_animation(ui->music_app_music_stylus, 400, 0, cur, -240, lv_anim_path_ease_in_out, 0, 0, 0, 0,
                         anim_img_angle_exec, NULL, NULL, NULL);
        }
    } else {
        music_resume = 0;
        if (!music_playing) {
            music_start = 1;
        }
        if (lv_obj_is_valid(ui->music_app_music_stylus)) {
            lv_anim_del(ui->music_app_music_stylus, anim_img_angle_exec);
            ui_animation(ui->music_app_music_stylus, 400, 0, -240, 0, lv_anim_path_ease_in_out, 0, 0, 0, 0,
                         anim_img_angle_exec, NULL, stylus_to_play_ready_cb, NULL);
        } else if (lv_obj_is_valid(ui->music_app_music_recode)) {
            lv_anim_del(ui->music_app_music_recode, anim_img_angle_exec);
            ui_animation(ui->music_app_music_recode, 2000, 0, 0, 3600, lv_anim_path_linear, LV_ANIM_REPEAT_INFINITE, 0,
                         0, 0, anim_img_angle_exec, NULL, NULL, NULL);
        }
    }
}

#endif
