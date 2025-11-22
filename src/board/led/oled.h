#pragma once

#include <stdint.h>

#define OLED_CMD 0
#define OLED_DATA 1
#define OLED_MODE 0

// OLED模式设置
// 0:4线串行模式
// 1:并行8080模式

#define SIZE 16
#define XLevelL 0x02
#define XLevelH 0x10
#define Max_Column 128
#define Max_Row 64
#define Brightness 0xFF
#define X_WIDTH 128
#define Y_WIDTH 64

class OLED {
  public:
    static OLED &GetInstance() {
        static OLED instance;
        return instance;
    }
    // 删除拷贝构造函数和赋值运算符
    OLED(const OLED &) = delete;
    OLED &operator=(const OLED &) = delete;

    void Init();
    void DisplayOn();
    void DisplayOff();
    void Clear();
    void SetPos(uint8_t x, uint8_t y);
    void ShowChar(uint8_t x, uint8_t y, uint8_t chr);
    void ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size2);
    void ShowString(uint8_t x, uint8_t y, uint8_t *p);
    void ShowChinese(uint8_t x, uint8_t y, uint8_t no);
    void DrawBMP(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, unsigned char BMP[]);
    void ShowCHStr(uint8_t X, uint8_t Y, uint8_t *pstr);
    void WriteByte(uint8_t dat, uint8_t cmd);

  private:
    OLED() = default;
    ~OLED() = default;
    
    static uint32_t PowUint32_t(uint8_t m, uint8_t n);
    void DCSet();
    void DCClr();
    void CSSet();
    void CSClr();
    void RSTSet();
    void RSTClr();
    void SPITransferByte(uint8_t data);
    void SPIConfig();
    void GPIOConfig();
};
