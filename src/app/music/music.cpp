#include "music.hpp"
#include "FreeRTOS.h"
#include "task.h"
#include "beep.hpp"

/* 音高表：music_arrX 中的数值作为索引，映射到实际频率 */
static const uint16_t note_freqs[] = {
    TONE_REST,
    TONE_L1, TONE_L2, TONE_L3, TONE_L4, TONE_L5, TONE_L6, TONE_L7,
    TONE_M1, TONE_M2, TONE_M3, TONE_M4, TONE_M5, TONE_M6, TONE_M7,
    TONE_H1, TONE_H2, TONE_H3, TONE_H4, TONE_H5, TONE_H6, TONE_H7,
    // Tone::REST,
    // Tone::L1, Tone::L2, Tone::L3, Tone::L4, Tone::L5, Tone::L6, Tone::L7,
    // Tone::M1, Tone::M2, Tone::M3, Tone::M4, Tone::M5, Tone::M6, Tone::M7,
    // Tone::H1, Tone::H2, Tone::H3, Tone::H4, Tone::H5, Tone::H6, Tone::H7,
};

// 红尘情歌
uint8_t music_arr[] = { // 音调
    5, 5, 6, 8,  7,  6, 5, 6,  0, 0, 5, 5, 6, 8,  7, 6, 5, 3, 0, 0, 2, 2,
    3, 5, 3, 5,  6,  3, 2, 1,  6, 6, 5, 6, 5, 3,  6, 5, 0, 0,

    5, 5, 6, 8,  7,  6, 5, 6,  0, 0, 5, 5, 6, 8,  7, 6, 5, 3, 0, 0, 2, 2,
    3, 5, 3, 5,  6,  3, 2, 1,  6, 6, 5, 6, 5, 3,  6, 1,

    0, 8, 9, 10, 10, 9, 8, 10, 9, 8, 6, 0, 6, 8,  9, 9, 8, 6, 9, 8, 6, 5,
    0, 2, 3, 5,  5,  3, 5, 5,  6, 8, 7, 6, 6, 10, 9, 9, 8, 6, 5, 6, 8};
uint8_t time_arr[] = { // 时间
    2, 4, 2, 2, 2, 2, 2, 8, 4, 4, 2, 4, 2, 2, 2, 2, 2, 8, 4, 4, 2, 4, 2, 4, 2, 2, 4, 2, 2, 8, 2, 4, 2, 2, 2, 2, 2, 8,
    4, 4,

    2, 4, 2, 2, 2, 2, 2, 8, 4, 4, 2, 4, 2, 2, 2, 2, 2, 8, 4, 4, 2, 4, 2, 4, 2, 2, 4, 2, 2, 8, 2, 4, 2, 2, 2, 2, 2, 8,

    4, 2, 2, 2, 4, 2, 2, 2, 2, 2, 8, 4, 2, 2, 2, 4, 2, 2, 2, 2, 2, 8, 4, 2, 2, 2, 4, 2, 2, 5, 2, 6, 2, 4, 2, 2, 2, 4,
    2, 4, 2, 2, 12};

// 荷塘月色
uint8_t music_arr1[] = {8,  12, 6,  5,  6, 8,  8,  9,  10, 9,  9,  8,  9,  9,  12, 12, 10, 10, 9,  10, 8,  8,  6, 5, 12,
                        10, 9,  10, 9,  8, 9,  9,  8,  9,  9,  10, 9,  8,  6,  9,  8,  8,  8,  6,  5,  6,  8,  8, 9, 10,
                        9,  9,  8,  9,  9, 12, 12, 10, 10, 9,  10, 8,  8,  8,  6,  5,  12, 10, 9,  10, 9,  8,  9, 9, 8,
                        9,  9,  10, 9,  8, 6,  9,  8,  10, 12, 12, 12, 12, 13, 12, 10, 9,  8,  13, 15, 13, 10, 9, 8, 6,
                        9,  9,  10, 10, 9, 10, 12, 12, 12, 12, 13, 12, 10, 9,  8,  6,  8,  6,  5,  9,  10, 8,  0};

uint8_t time_arr1[] = {2, 4, 2, 4, 4, 4, 2, 2, 8, 2, 4, 2, 4, 2, 2, 2, 2, 2, 2, 8, 2, 4, 2, 4, 4, 2, 2, 2, 2, 8,  2,
                       4, 2, 2, 4, 2, 2, 2, 2, 2, 8, 2, 4, 2, 4, 4, 2, 4, 2, 8, 2, 4, 2, 4, 2, 2, 2, 2, 2, 2, 8,  2,
                       2, 2, 2, 4, 4, 2, 2, 2, 2, 8, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 8, 2, 4, 2, 4, 4, 2, 2, 2, 2,  8,
                       2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 6, 2, 4, 2, 4, 4, 2, 2, 2, 2, 8, 2, 2, 2, 2, 4, 4, 12, 4};

// 沉默是金
uint8_t music_arr2[] = {10, 12, 12, 13, 12, 12, 10, 9,  10, 10, 10, 9,  8,  8,  13, 15, 15, 16, 15, 15, 13,
                        12, 10, 12, 13, 15, 15, 16, 15, 15, 13, 12, 10, 12, 12, 12, 13, 10, 10, 12, 10,

                        9,  13, 12, 10, 9,  10, 12,

                        10, 12, 12, 13, 12, 12, 10, 9,  10, 10, 10, 9,  8,  8,  13, 15, 15, 16, 15, 15, 13,
                        12, 10, 12, 13, 15, 15, 16, 15, 15, 13, 12, 10, 12, 12, 12, 13, 10, 10, 12, 10,

                        9,  13, 12, 10, 9,  8,  15, 15, 16, 17, 17, 17, 16, 15, 13, 15, 15, 13, 12, 12, 13,
                        15, 15, 16, 15, 15, 13, 12, 10, 12, 13, 15, 15, 16, 15, 13, 12, 12, 13, 10, 10, 12,
                        10, 9,  10, 9,  9,  10, 11, 12, 10, 12, 12, 13, 12, 12, 10, 9,  10, 10, 10, 9,  8,
                        8,  13, 15, 15, 16, 15, 15, 13, 12, 10, 12, 13, 15, 15, 16, 15, 15, 13, 12, 10, 12,
                        12, 12, 13, 10, 10, 12, 10, 9,  9,  13, 12, 10, 9,  8};
uint8_t time_arr2[] = {2, 2, 2, 1, 1,  4,  1,  3, 2, 2, 2, 1, 1, 8, 2, 2, 2, 1, 1, 4, 2, 2, 2, 16, 2,
                       2, 2, 1, 1, 4,  2,  2,  2, 2, 2, 2, 1, 1, 4, 2, 2,

                       6, 2, 4, 2, 2,  2,  16,

                       2, 2, 2, 1, 1,  4,  1,  3, 2, 2, 2, 1, 1, 8, 2, 2, 2, 1, 1, 4, 2, 2, 2, 16, 2,
                       2, 2, 1, 1, 4,  2,  2,  2, 2, 2, 2, 1, 1, 4, 2, 2,

                       6, 2, 4, 2, 2,  16, 4,  2, 1, 1, 3, 1, 1, 3, 2, 2, 2, 1, 1, 8, 2, 2, 2, 1,  1,
                       4, 2, 2, 2, 16, 6,  2,  2, 2, 4, 2, 2, 2, 1, 1, 4, 2, 2, 6, 2, 4, 2, 2, 2,  16,
                       2, 2, 2, 1, 1,  4,  1,  3, 2, 2, 2, 1, 1, 8, 2, 2, 2, 1, 1, 4, 2, 2, 2, 16, 2,
                       2, 2, 1, 1, 4,  2,  2,  2, 2, 2, 2, 1, 1, 4, 2, 2, 2, 4, 2, 2, 4, 2, 16};

/* 播放控制标志的实际定义 */
volatile int music_start = 0;
volatile int music_index = 0;
volatile int music_timer = 0;
volatile int music_resume = 0;
volatile int music_playing = 0;
volatile int music_song_id = 0;

/* 播放一首歌：根据 music_song_id 选择曲目并播放 */
void Music::play_one_song() {
    const uint8_t *notes = nullptr;
    const uint8_t *times = nullptr;
    size_t total = 0;

    switch ((music_song_id % 3 + 3) % 3) { // 规范到 0..2
    case 0:
        notes = music_arr;
        times = time_arr;
        total = sizeof(time_arr) / sizeof(time_arr[0]);
        break;
    case 1:
        notes = music_arr1;
        times = time_arr1;
        total = sizeof(time_arr1) / sizeof(time_arr1[0]);
        break;
    case 2:
        notes = music_arr2;
        times = time_arr2;
        total = sizeof(time_arr2) / sizeof(time_arr2[0]);
        break;
    }

    /* 起始索引由全局 music_index 控制，可从头或从中间继续 */
    for (; music_index < (int)total; ++music_index) {
        if (!music_playing) {
            break; /* 被外部停止 */
        }

        /* 暂停：在暂停期间保持短延时轮询，并立即静音 */
        if (music_resume) {
            g_beep.disableOutput();
            vTaskDelay(pdMS_TO_TICKS(50));
            /* 重做当前音符，不前进索引 */
            --music_index; /* for 循环会 ++，抵消保持当前 */
            continue;
        }

        uint8_t note_id = notes[music_index];
        uint16_t freq = (note_id < (sizeof(note_freqs) / sizeof(note_freqs[0]))) ? note_freqs[note_id] : 0;

        if (freq == 0) {
            g_beep.disableOutput();
        } else {
            g_beep.setFreq(freq);
            g_beep.enableOutput();
        }

        int duration_units = times[music_index];
        if (duration_units <= 0) {
            duration_units = 1;
        }
        /* 单位为 100ms */
        vTaskDelay(pdMS_TO_TICKS(duration_units * 100));
    }

    /* 结束本曲播放 */
    g_beep.disableOutput();
    music_playing = 0;
    music_index = 0;
}

/* FreeRTOS 任务：根据控制标志开始/暂停播放 */
void TaskMusic([[maybe_unused]] void *pvParameters) {
    for (;;) {
        /* 外部请求开始播放 */
        if (music_start) {
            music_start = 0;   /* 消耗启动请求 */
            music_index = 0;   /* 从头开始 */
            music_resume = 0;  /* 取消暂停 */
            music_playing = 1; /* 标记正在播放 */
        }

        if (music_playing) {
            Music::GetInstance().play_one_song();
        } else {
            /* 空闲，降低占用 */
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }
}

