

#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
extern uint8_t lm75_buf[2];
#ifdef __cplusplus
}
#endif

class LM75 {
  public:
    // 删除拷贝构造函数和赋值运算符
    LM75(const LM75 &) = delete;
    LM75 &operator=(const LM75 &) = delete;

    uint8_t Read();

  private:
    friend class Board;
    LM75() = default;
    ~LM75() = default;
};
