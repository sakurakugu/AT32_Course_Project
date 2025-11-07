/**
 * @brief 蜂鸣器类
 * 
 * 该类用于控制无源蜂鸣器的发声和停止。
 */

#pragma once
#include <stdint.h>

class Beep {
  public:
    void init();
    void setFreq(int freq);
    void start(uint16_t beepTime, uint16_t stopTime, uint16_t cycle);
    void stop();
    void keyTone();
    void process();
    void pause();
    void resume();

    void enableOutput();
    void disableOutput();

  private:
    // 状态参数
    uint8_t enableFlag = 0;
    uint8_t state = 0;
    uint16_t beepTime = 0;
    uint16_t stopTime = 0;
    uint16_t cycle = 0;
    uint16_t count = 0;
    uint16_t cycleCount = 0;
    uint8_t mute = 0; // 1表示静音

    // 时钟相关
    uint16_t prescalerValue = 0;
};

extern Beep g_beep;
