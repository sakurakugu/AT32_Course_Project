/*
*
*	模块名称 : 按键驱动模块
*	文件名称 : bsp_key.h
*
*/

#pragma once
#include <stdint.h>

/* 按键ID, 主要用于bsp_KeyState()函数的入口参数 */
typedef enum {
    KID_K1 = 0,
    KID_K2,
    KID_K3,
    KID_K4,
    KID_K5,
    KID_K6,
    KID_K7,
    KID_K8
} KEY_ID_E;

/*
    按键滤波时间50ms, 单位10ms。
    只有连续检测到50ms状态不变才认为有效，包括弹起和按下两种事件
    即使按键电路不做硬件滤波，该滤波机制也可以保证可靠地检测到按键事件
*/
#define KEY_FILTER_TIME 5
#define KEY_LONG_TIME 100 /* 单位10ms， 持续1秒，认为长按事件 */

/*
    每个按键对应1个全局的结构体变量。
*/
typedef struct {
    /* 下面是一个函数指针，指向判断按键手否按下的函数 */
    uint8_t (*IsKeyDownFunc)(void); /* 按键按下的判断函数,1表示按下 */

    uint8_t Count;       /* 滤波器计数器 */
    uint16_t LongCount;  /* 长按计数器 */
    uint16_t LongTime;   /* 按键按下持续时间, 0表示不检测长按 */
    uint8_t State;       /* 按键当前状态（按下还是弹起） */
    uint8_t RepeatSpeed; /* 连续按键周期 */
    uint8_t RepeatCount; /* 连续按键计数器 */
} KEY_T;

/*
    定义键值代码, 必须按如下次序定时每个键的按下、弹起和长按事件

    推荐使用enum, 不用#define，原因：
    (1) 便于新增键值,方便调整顺序，使代码看起来舒服点
    (2) 编译器可帮我们避免键值重复。
*/
typedef enum {
    KEY_NONE = 0, /* 0 表示按键事件 */

    KEY_1_DOWN, /* 1键按下 */
    KEY_1_UP,   /* 1键弹起 */
    KEY_1_LONG, /* 1键长按 */

    KEY_2_DOWN, /* 2键按下 */
    KEY_2_UP,   /* 2键弹起 */
    KEY_2_LONG, /* 2键长按 */

    KEY_3_DOWN, /* 3键按下 */
    KEY_3_UP,   /* 3键弹起 */
    KEY_3_LONG, /* 3键长按 */

    KEY_4_DOWN, /* 4键按下 */
    KEY_4_UP,   /* 4键弹起 */
    KEY_4_LONG, /* 4键长按 */

    KEY_5_DOWN, /* 5键按下 */
    KEY_5_UP,   /* 5键弹起 */
    KEY_5_LONG, /* 5键长按 */

    KEY_6_DOWN, /* 6键按下 */
    KEY_6_UP,   /* 6键弹起 */
    KEY_6_LONG, /* 6键长按 */

    KEY_7_DOWN, /* 7键按下 */
    KEY_7_UP,   /* 7键弹起 */
    KEY_7_LONG, /* 7键长按 */

    KEY_8_DOWN, /* 8键按下 */
    KEY_8_UP,   /* 8键弹起 */
    KEY_8_LONG, /* 8键长按 */
} KEY_ENUM;

/* 按键FIFO用到变量 */
#define KEY_FIFO_SIZE 10
typedef struct {
    uint8_t Buf[KEY_FIFO_SIZE]; /* 键值缓冲区 */
    uint8_t Read;               /* 缓冲区读指针1 */
    uint8_t Write;              /* 缓冲区写指针 */
    uint8_t Read2;              /* 缓冲区读指针2 */
} KEY_FIFO_T;

#define HARD_KEY_NUM 8 /* 实体按键个数 */
#define KEY_COUNT 8    /* 8个独立键 */

class Key {
  public:
    static Key &GetInstance() {
        static Key instance;
        return instance;
    }
    // 删除拷贝构造函数和赋值运算符
    Key(const Key &) = delete;
    Key &operator=(const Key &) = delete;

    void Init();
    void Scan10ms();
    void Scan1ms();
    void Put(uint8_t code);
    uint8_t Get();
    uint8_t Get2();
    uint8_t State(KEY_ID_E id) const;
    void SetParam(uint8_t id, uint16_t long_time, uint8_t repeat_speed);
    void Clear();

  private:
    Key();
    KEY_T btn[KEY_COUNT] = {0};
    KEY_FIFO_T fifo{};

    void InitVars();
    void InitHardware();
    uint8_t PinActive(uint8_t id) const;
    uint8_t IsDown(uint8_t id) const;
    void DetectKey(uint8_t i);
    void DetectFast(uint8_t i);
};
