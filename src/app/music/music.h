#pragma once

#include "gui_guider.h"

#ifdef __cplusplus
extern "C" {
#endif

// 音乐播放器事件
void music_list_item_event_handler(lv_event_t *e);      // 列表项点击播放对应歌曲
void music_prev_btn_event_handler(lv_event_t *e);       // 切换到上一首（循环）
void music_next_btn_event_handler(lv_event_t *e);       // 切换到下一首（循环）
void music_play_pause_btn_event_handler(lv_event_t *e); // 播放/暂停切换

#ifdef __cplusplus
}
#endif