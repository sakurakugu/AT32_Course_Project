#pragma once

#include "gui_guider.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern uint8_t music_arr[];  // 音乐数组（红尘情歌）（音调）
extern uint8_t time_arr[];   // 时间数组（持续时间）
extern uint8_t music_arr1[]; // 音乐数组（荷塘月色）
extern uint8_t time_arr1[];  // 时间数组（持续时间）
extern uint8_t music_arr2[]; // 音乐数组（沉默是金）
extern uint8_t time_arr2[];  // 时间数组（持续时间）

extern volatile int music_start;   // 音乐是否开始（置1后由任务消费并清零）
extern volatile int music_index;   // 当前播放的音符索引
extern volatile int music_timer;   // 当前音符的持续时间（保留未用）
extern volatile int music_resume;  // 音乐是否暂停（1=暂停，0=继续）
extern volatile int music_playing; // 当前是否处于播放状态
extern volatile int music_song_id; // 当前选中的歌曲索引（0=红尘情歌，1=荷塘月色，2=沉默是金）

typedef enum {
    // 低音
    TONE_L1 = 262,
    TONE_L2 = 294,
    TONE_L3 = 330,
    TONE_L4 = 349,
    TONE_L5 = 392,
    TONE_L6 = 440,
    TONE_L7 = 494,

    // 中音
    TONE_M1 = 523,
    TONE_M2 = 587,
    TONE_M3 = 659,
    TONE_M4 = 698,
    TONE_M5 = 784,
    TONE_M6 = 880,
    TONE_M7 = 988,

    // 高音
    TONE_H1 = 1047,
    TONE_H2 = 1175,
    TONE_H3 = 1319,
    TONE_H4 = 1397,
    TONE_H5 = 1568,
    TONE_H6 = 1760,
    TONE_H7 = 1976,

    // 不发音
    TONE_REST = 0,
} Tone;

// 音乐播放器事件
void music_list_item_event_handler(lv_event_t *e);      // 列表项点击播放对应歌曲
void music_prev_btn_event_handler(lv_event_t *e);       // 切换到上一首（循环）
void music_next_btn_event_handler(lv_event_t *e);       // 切换到下一首（循环）
void music_play_pause_btn_event_handler(lv_event_t *e); // 播放/暂停切换

#ifdef __cplusplus
}
#endif