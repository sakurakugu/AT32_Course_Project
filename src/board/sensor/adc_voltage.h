#pragma once
#include <stdint.h>

class ADCVoltage {
  public:
    void Init();
    uint16_t Read();

    ADCVoltage(const ADCVoltage &) = delete;            // 禁用拷贝构造函数
    ADCVoltage &operator=(const ADCVoltage &) = delete; // 禁用赋值操作

  private:
    friend class Board; // 允许 Board 类访问私有成员
    ADCVoltage() = default;
    ~ADCVoltage() = default;

    void ConfigGPIO();
    void ConfigADC();
};

