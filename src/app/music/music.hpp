#pragma once

#include "music.h"

#pragma once

// namespace Tone {
//     // 低音
//     constexpr uint16_t L1 = 262;
//     constexpr uint16_t L2 = 294;
//     constexpr uint16_t L3 = 330;
//     constexpr uint16_t L4 = 349;
//     constexpr uint16_t L5 = 392;
//     constexpr uint16_t L6 = 440;
//     constexpr uint16_t L7 = 494;

//     // 中音
//     constexpr uint16_t M1 = 523;
//     constexpr uint16_t M2 = 587;
//     constexpr uint16_t M3 = 659;
//     constexpr uint16_t M4 = 698;
//     constexpr uint16_t M5 = 784;
//     constexpr uint16_t M6 = 880;
//     constexpr uint16_t M7 = 988;

//     // 高音
//     constexpr uint16_t H1 = 1047;
//     constexpr uint16_t H2 = 1175;
//     constexpr uint16_t H3 = 1319;
//     constexpr uint16_t H4 = 1397;
//     constexpr uint16_t H5 = 1568;
//     constexpr uint16_t H6 = 1760;
//     constexpr uint16_t H7 = 1976;

//     // 不发音
//     constexpr uint16_t REST = 0;
// }



class Music {
  public:
    static Music &GetInstance() {
        static Music instance;
        return instance;
    }
    // 删除拷贝构造函数和赋值运算符
    Music(const Music &) = delete;
    Music &operator=(const Music &) = delete;

    void PlayOneSong();

  private:
    Music() = default;
    ~Music() = default;
};

extern void TaskMusic(void *pvParameters);