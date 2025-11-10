#include <stdint.h>

extern uint8_t music_arr[];  // 音乐数组（音调）
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

#ifdef __cplusplus
extern "C" {
#endif

extern void TaskMusic(void *pvParameters);

#ifdef __cplusplus
}
#endif