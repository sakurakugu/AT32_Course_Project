#include <stdint.h>

// 定义低音频率
#define L1 262
#define L2 294
#define L3 330
#define L4 349
#define L5 392
#define L6 440
#define L7 494
// 定义中音
#define M1 523
#define M2 587
#define M3 659
#define M4 698
#define M5 784
#define M6 880
#define M7 988
// 定义高音
#define H1 1047
#define H2 1175
#define H3 1319
#define H4 1397
#define H5 1568
#define H6 1760
#define H7 1976
// 定义不发音（避免与CMSIS位域N冲突）
#define REST 0

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

extern void music_process();
extern void TaskMusic(void *pvParameters);

#ifdef __cplusplus
}
#endif
