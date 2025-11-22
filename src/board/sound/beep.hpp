#pragma once
#include "beep.h"

class Beep {
  public:
    void Init();
    void SetFreq(int freq);
    void Start(uint16_t beepTime, uint16_t stopTime, uint16_t cycle);
    void Stop();
    void KeyTone();
    void Process();
    void Pause();
    void Resume();
    void SetMute(bool mute);

    void EnableOutput();
    void DisableOutput();

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