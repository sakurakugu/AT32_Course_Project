/*
*********************************************************************************************************
*
*    模块名称 : 独立按键驱动模块 (外部输入IO) — C++ 封装
*    文件名称 : bsp_key.cpp
*
*********************************************************************************************************
*/

#include "key.h"
#include "at32f435_437_gpio.h"

/* 依次定义GPIO */
struct X_GPIO_T {
    gpio_type *gpio;
    uint16_t pin;
    uint8_t ActiveLevel; /* 激活电平 */
};

/* GPIO和PIN定义 */
static const X_GPIO_T s_gpio_list[HARD_KEY_NUM] = {
    {GPIOB, GPIO_PINS_13, 0}, /* K1 */
    {GPIOB, GPIO_PINS_14, 0}, /* K2 */
    {GPIOB, GPIO_PINS_15, 0}, /* K3 */
    {GPIOE, GPIO_PINS_1, 0},  /* K4 */
    {GPIOD, GPIO_PINS_2, 0},  /* K5 */
    {GPIOD, GPIO_PINS_12, 0}, /* K6 */
    {GPIOB, GPIO_PINS_2, 0},  /* K7 */
    {GPIOE, GPIO_PINS_4, 0},  /* K8 */
};

Key::Key() {
    init_vars();
}

void Key::init() {
    init_vars();
    init_hw();
}

/**
 * @brief 扫描10ms按键状态
 * @note  按键状态机，检测按键是否按下、弹起、长按
 */
void Key::scan10ms() {
    for (uint8_t i = 0; i < KEY_COUNT; i++) {
        detect_key(i);
    }
}

/**
 * @brief 扫描1ms按键状态
 * @note  按键状态机，检测按键是否按下、弹起、长按
 */
void Key::scan1ms() {
    for (uint8_t i = 0; i < KEY_COUNT; i++) {
        detect_fast(i);
    }
}

/**
 * @brief 按键FIFO写入
 * @param code 按键代码
 */
void Key::put(uint8_t code) {
    fifo.Buf[fifo.Write] = code;
    if (++fifo.Write >= KEY_FIFO_SIZE) {
        fifo.Write = 0;
    }
}

/**
 * @brief 按键FIFO读取
 * @return uint8_t 按键代码
 */
uint8_t Key::get() {
    uint8_t ret;
    if (fifo.Read == fifo.Write) {
        return KEY_NONE;
    }
    ret = fifo.Buf[fifo.Read];
    if (++fifo.Read >= KEY_FIFO_SIZE) {
        fifo.Read = 0;
    }
    return ret;
}

/**
 * @brief 按键FIFO读取2
 * @return uint8_t 按键代码
 */
uint8_t Key::get2() {
    uint8_t ret;
    if (fifo.Read2 == fifo.Write) {
        return KEY_NONE;
    }
    ret = fifo.Buf[fifo.Read2];
    if (++fifo.Read2 >= KEY_FIFO_SIZE) {
        fifo.Read2 = 0;
    }
    return ret;
}

/**
 * @brief 获取按键状态
 * @param id 按键ID
 * @return uint8_t 按键状态
 */
uint8_t Key::state(KEY_ID_E id) const {
    return btn[id].State;
}

/**
 * @brief 设置按键长按时间和连发速度
 * @param id 按键ID
 * @param long_time 长按时间
 * @param repeat_speed 连发速度
 */
void Key::set_param(uint8_t id, uint16_t long_time, uint8_t repeat_speed) {
    btn[id].LongTime = long_time;
    btn[id].RepeatSpeed = repeat_speed;
    btn[id].RepeatCount = 0;
}

/**
 * @brief 清空按键FIFO
 *
 */
void Key::clear() {
    fifo.Read = fifo.Write;
}

/**
 * @brief 初始化按键变量
 */
void Key::init_vars() {
    fifo.Read = 0;
    fifo.Write = 0;
    fifo.Read2 = 0;

    for (uint8_t i = 0; i < KEY_COUNT; i++) {
        btn[i].LongTime = KEY_LONG_TIME;
        btn[i].Count = KEY_FILTER_TIME / 2;
        btn[i].State = 0;
        btn[i].RepeatSpeed = 0;
        btn[i].RepeatCount = 0;
    }

    /* 摇杆上下左右，支持长按1秒后，自动连发 */
    set_param(KID_K1, 100, 6);
    set_param(KID_K2, 100, 6);
    set_param(KID_K3, 100, 6);
    set_param(KID_K4, 100, 6);
}

/**
 * @brief 初始化按键硬件
 */
void Key::init_hw() {
    gpio_init_type gpio_init_struct;
    gpio_default_para_init(&gpio_init_struct);

    crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE);

    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
    gpio_init_struct.gpio_pull = GPIO_PULL_DOWN;
    for (uint8_t i = 0; i < HARD_KEY_NUM; i++) {
        gpio_init_struct.gpio_pins = s_gpio_list[i].pin;
        gpio_init(s_gpio_list[i].gpio, &gpio_init_struct);
    }
}

/**
 * @brief 获取按键引脚激活电平
 * @param id 按键ID
 * @return uint8_t 激活电平
 */
uint8_t Key::pin_active(uint8_t id) const {
    uint8_t level = ((s_gpio_list[id].gpio->idt & s_gpio_list[id].pin) == 0) ? 0 : 1;
    return (level == s_gpio_list[id].ActiveLevel) ? 1 : 0;
}

/**
 * @brief 判断按键是否按下
 * @param id 按键ID
 * @return uint8_t 是否按下
 */
uint8_t Key::is_down(uint8_t id) const {
    if (id < HARD_KEY_NUM) {
        uint8_t count = 0, save = 255;
        for (uint8_t i = 0; i < HARD_KEY_NUM; i++) {
            if (pin_active(i)) {
                count++;
                save = i;
            }
        }
        if (count == 1 && save == id) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief 检测按键状态
 * @param i 按键ID
 */
void Key::detect_key(uint8_t i) {
    KEY_T *pBtn = &btn[i];
    if (is_down(i)) {
        if (pBtn->Count < KEY_FILTER_TIME) {
            pBtn->Count = KEY_FILTER_TIME;
        } else if (pBtn->Count < 2 * KEY_FILTER_TIME) {
            pBtn->Count++;
        } else {
            if (pBtn->State == 0) {
                pBtn->State = 1;
                put((uint8_t)(3 * i + 1));
            }

            if (pBtn->LongTime > 0) {
                if (pBtn->LongCount < pBtn->LongTime) {
                    if (++pBtn->LongCount == pBtn->LongTime) {
                        put((uint8_t)(3 * i + 3));
                    }
                } else {
                    if (pBtn->RepeatSpeed > 0) {
                        if (++pBtn->RepeatCount >= pBtn->RepeatSpeed) {
                            pBtn->RepeatCount = 0;
                            put((uint8_t)(3 * i + 1));
                        }
                    }
                }
            }
        }
    } else {
        if (pBtn->Count > KEY_FILTER_TIME) {
            pBtn->Count = KEY_FILTER_TIME;
        } else if (pBtn->Count != 0) {
            pBtn->Count--;
        } else {
            if (pBtn->State == 1) {
                pBtn->State = 0;
                put((uint8_t)(3 * i + 2));
            }
        }
        pBtn->LongCount = 0;
        pBtn->RepeatCount = 0;
    }
}

/**
 * @brief 快速检测按键状态
 * @param i 按键ID
 */
void Key::detect_fast(uint8_t i) {
    KEY_T *pBtn = &btn[i];
    if (is_down(i)) {
        if (pBtn->State == 0) {
            pBtn->State = 1;
            put((uint8_t)(3 * i + 1));
        }
        if (pBtn->LongTime > 0) {
            if (pBtn->LongCount < pBtn->LongTime) {
                if (++pBtn->LongCount == pBtn->LongTime) {
                    put((uint8_t)(3 * i + 3));
                }
            } else {
                if (pBtn->RepeatSpeed > 0) {
                    if (++pBtn->RepeatCount >= pBtn->RepeatSpeed) {
                        pBtn->RepeatCount = 0;
                        put((uint8_t)(3 * i + 1));
                    }
                }
            }
        }
    } else {
        if (pBtn->State == 1) {
            pBtn->State = 0;
            put((uint8_t)(3 * i + 2));
        }
        pBtn->LongCount = 0;
        pBtn->RepeatCount = 0;
    }
}
