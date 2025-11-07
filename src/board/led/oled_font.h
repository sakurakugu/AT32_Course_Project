#pragma once

#include <stdint.h>

typedef struct {
    uint8_t value[4]; // GBK编码用2字节，UTF-8编码用4字节
    uint8_t data[24]; // 12x12 点阵
} 汉字转码_12;

extern const uint8_t chinese_12_len;
extern uint8_t Hzk[][32];
extern const uint8_t F6x8[][6];
extern const uint8_t F8X16[];
extern const 汉字转码_12 chinese_12[5];
