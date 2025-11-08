/**
 * @file custom.c
 * @brief 自定义函数实现文件
 * @details 包含自定义函数的实现，如更新音量图标等（该文件不会被覆盖）
 */

#include "custom.h"
#include "lvgl.h"
#include <stdio.h>

#include "../../src/app/calculator/calculator.h"

volatile uint8_t wifi_reconnect_requested;

void custom_init(lv_ui *ui) {
    /* Add your codes here */
}

/**
 * @brief 更新音量图标
 * @param ui 指向lv_ui结构体的指针，用于访问GUI元素
 * @param volume 音量值，0表示静音，1-100表示不同音量等级
 */
void update_volume_icon(lv_ui *ui, uint8_t volume) {
    if (volume > 0) {
        // 显示“有音量”
        // lv_obj_clear_flag(ui->screen_voice_on, LV_OBJ_FLAG_HIDDEN);
        // lv_obj_add_flag(ui->screen_voice_off, LV_OBJ_FLAG_HIDDEN);
    } else {
        // 显示“静音”
        // lv_obj_add_flag(ui->screen_voice_on, LV_OBJ_FLAG_HIDDEN);
        // lv_obj_clear_flag(ui->screen_voice_off, LV_OBJ_FLAG_HIDDEN);
    }
}

// 统一的按键事件处理器：从 user_data 读取按键字符串并转交给计算器
void calc_key_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        const char *key = (const char *)lv_event_get_user_data(e);
        calculator_input_key(key);
    }
}

// 点击“连接”按钮事件：读取输入->触发异步连接->成功后写EEPROM
void wifi_link_btn_event_handler(lv_event_t *e) {
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui) return;

    const char *ssid_text = lv_textarea_get_text(ui->setting_app_wifi_name_input);
    const char *pwd_text = lv_textarea_get_text(ui->setting_app_wifi_password_input);

    if (!ssid_text || !pwd_text) return;

    // 复制到运行时缓冲，并更新全局凭据指针
    strncpy(wifi_ssid, ssid_text, sizeof(wifi_ssid) - 1);
    strncpy(wifi_password, pwd_text, sizeof(wifi_password) - 1);
    wifi_ssid[sizeof(wifi_ssid) - 1] = '\0';
    wifi_password[sizeof(wifi_password) - 1] = '\0';

    // 由后台任务异步完成连接，避免阻塞UI
    wifi_reconnect_requested = 1;
}

