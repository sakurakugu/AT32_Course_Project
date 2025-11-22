#include "smart_home.h"
#include "led.h"
#include "color_led.h"

// ===============================
// 智能家居事件实现
// ===============================

// —— 通用滑动动画辅助 ——
static void smart_home_anim_hide_ready_cb(lv_anim_t *a) {
    lv_obj_t *obj = (lv_obj_t *)a->var;
    if (lv_obj_is_valid(obj)) {
        lv_obj_t *parent = lv_obj_get_parent(obj);
        lv_coord_t w = lv_obj_get_width(obj);
        lv_coord_t parent_w = lv_obj_is_valid(parent) ? lv_obj_get_width(parent) : lv_obj_get_x(obj);
        lv_obj_set_x(obj, parent_w - w);
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }
}

static void smart_home_slide_in(lv_obj_t *page) {
    if (!lv_obj_is_valid(page))
        return;
    lv_coord_t end_x = lv_obj_get_x(page);
    lv_coord_t y = lv_obj_get_y(page);
    lv_coord_t w = lv_obj_get_width(page);

    // 从右侧外部开始，清除隐藏
    lv_obj_clear_flag(page, LV_OBJ_FLAG_HIDDEN); // 清除隐藏标志位，确保页面可见
    lv_obj_set_pos(page, end_x + w, y);          // 设置初始位置为右侧外部，准备滑动进入

    lv_anim_t a;
    lv_anim_init(&a);                                          // 从右侧外部开始，滑动到目标位置
    lv_anim_set_var(&a, page);                                 // 目标对象：要滑动的页面
    lv_anim_set_values(&a, end_x + w, end_x);                  // 从右侧外部开始，滑动到目标位置
    lv_anim_set_time(&a, 250);                                 // 动画时间：250ms
    lv_anim_set_path_cb(&a, lv_anim_path_ease_out);            // 动画路径：缓出
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x); // 动画执行回调：设置对象的 x 坐标
    lv_anim_start(&a);                                         // 启动动画
}

static void smart_home_slide_out_and_hide(lv_obj_t *page) {
    if (!lv_obj_is_valid(page))
        return; // 无效页面，直接返回
    if (lv_obj_has_flag(page, LV_OBJ_FLAG_HIDDEN))
        return;                                 // 已隐藏，无需操作
    lv_coord_t start_x = lv_obj_get_x(page);    // 获取当前页面的 x 坐标
    lv_obj_t *parent = lv_obj_get_parent(page); // 获取父容器（假设为屏幕）
    lv_coord_t parent_w = lv_obj_is_valid(parent)
                              ? lv_obj_get_width(parent)
                              : (start_x + lv_obj_get_width(page)); // 父容器宽度（如果无效，默认使用当前页面宽度）

    lv_anim_t a;
    lv_anim_init(&a);                                          // 初始化动画
    lv_anim_set_var(&a, page);                                 // 目标对象：要滑动的页面
    lv_anim_set_values(&a, start_x, parent_w);                 // 从当前位置滑动到父容器宽度（右侧外部）
    lv_anim_set_time(&a, 200);                                 // 动画时间：200ms
    lv_anim_set_path_cb(&a, lv_anim_path_ease_in);             // 动画路径：缓入
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x); // 动画执行回调：设置对象的 x 坐标
    lv_anim_set_ready_cb(&a, smart_home_anim_hide_ready_cb);   // 动画完成回调：隐藏对象
    lv_anim_start(&a);                                         // 启动动画
}

void smart_home_close_all_pages_with_slide(lv_ui *ui) {
    if (!ui)
        return;
    smart_home_slide_out_and_hide(ui->smart_home_app_color_led_page);
    smart_home_slide_out_and_hide(ui->smart_home_app_led_green_page);
    smart_home_slide_out_and_hide(ui->smart_home_app_lm75_page);
    smart_home_slide_out_and_hide(ui->smart_home_app_ADC_page);
    smart_home_slide_out_and_hide(ui->smart_home_app_MPU6050_page);
    smart_home_slide_out_and_hide(ui->smart_home_app_key_page);
}

void smart_home_open_page_with_slide(lv_ui *ui, lv_obj_t *page) {
    if (!ui || !lv_obj_is_valid(page))
        return;
    // 先关闭其他已打开页面
    if (page != ui->smart_home_app_color_led_page)
        smart_home_slide_out_and_hide(ui->smart_home_app_color_led_page);
    if (page != ui->smart_home_app_led_green_page)
        smart_home_slide_out_and_hide(ui->smart_home_app_led_green_page);
    if (page != ui->smart_home_app_lm75_page)
        smart_home_slide_out_and_hide(ui->smart_home_app_lm75_page);
    if (page != ui->smart_home_app_ADC_page)
        smart_home_slide_out_and_hide(ui->smart_home_app_ADC_page);
    if (page != ui->smart_home_app_MPU6050_page)
        smart_home_slide_out_and_hide(ui->smart_home_app_MPU6050_page);
    if (page != ui->smart_home_app_key_page)
        smart_home_slide_out_and_hide(ui->smart_home_app_key_page);

    // 打开目标页面（右->左滑入）
    smart_home_slide_in(page);
}
// IoT页面 - 彩灯图标点击事件
void smart_home_iot_color_led_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_CLICKED)
        return;

    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;
    smart_home_open_page_with_slide(ui, ui->smart_home_app_color_led_page);
}

// IoT页面 - 绿灯图标点击事件
void smart_home_iot_led_green_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_CLICKED)
        return;

    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;
    smart_home_open_page_with_slide(ui, ui->smart_home_app_led_green_page);
}

// IoT页面 - ADC图标点击事件
void smart_home_iot_adc_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
        return;
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;
    smart_home_open_page_with_slide(ui, ui->smart_home_app_ADC_page);
}

// IoT页面 - MPU6050图标点击事件
void smart_home_iot_mpu6050_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
        return;
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;
    smart_home_open_page_with_slide(ui, ui->smart_home_app_MPU6050_page);
}

// IoT页面 - LM75图标点击事件
void smart_home_iot_lm75_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
        return;
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;
    smart_home_open_page_with_slide(ui, ui->smart_home_app_lm75_page);
}

// IoT页面 - 8Key图标点击事件
void smart_home_iot_8key_event_handler(lv_event_t *e) {
    if (lv_event_get_code(e) != LV_EVENT_CLICKED)
        return;
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;
    smart_home_open_page_with_slide(ui, ui->smart_home_app_key_page);
}

// IoT页面点击返回按键：关闭所有子页面（统一滑出）
void smart_home_iot_return_event_handler(lv_event_t *e) {
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;
    smart_home_close_all_pages_with_slide(ui);
}

#ifdef KEIL_COMPILE
// 彩灯开关事件：点击切换彩灯状态
void smart_home_color_led_sw_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_VALUE_CHANGED)
        return;

    lv_obj_t *sw = lv_event_get_target(e);
    bool checked = lv_obj_has_state(sw, LV_STATE_CHECKED);

    if (checked) {
        // 打开彩灯
        ColorLed_TurnOn();
    } else {
        // 关闭彩灯
        ColorLed_TurnOff();
    }
}

// 彩灯颜色选择事件：点击选择颜色
void smart_home_color_led_cpicker_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_VALUE_CHANGED)
        return;

    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;

    if (!lv_obj_has_state(ui->smart_home_app_color_led_sw, LV_STATE_CHECKED))
        return;

    lv_obj_t *cpicker = lv_event_get_target(e);
    lv_color_t color = lv_colorwheel_get_rgb(cpicker);
    uint32_t raw = lv_color_to32(color);
    lv_color32_t c32;
    c32.full = raw;
    uint8_t r = c32.ch.red;
    uint8_t g = c32.ch.green;
    uint8_t b = c32.ch.blue;

    // 获取当前亮度
    int32_t brightness = 100;
    if (lv_obj_is_valid(ui->smart_home_app_color_led_light_div_slider)) {
        brightness = lv_slider_get_value(ui->smart_home_app_color_led_light_div_slider);
    }

    // 应用亮度调整
    r = (uint8_t)((r * brightness) / 100);
    g = (uint8_t)((g * brightness) / 100);
    b = (uint8_t)((b * brightness) / 100);

    // 设置颜色
    ColorLed_SetColor(r, g, b);
}

// 彩灯亮度滑块事件：滑动调整亮度
void smart_home_color_led_light_slider_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_VALUE_CHANGED)
        return;

    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    if (!ui)
        return;

    if (!lv_obj_has_state(ui->smart_home_app_color_led_sw, LV_STATE_CHECKED))
        return;

    lv_obj_t *slider = lv_event_get_target(e);
    int32_t brightness = lv_slider_get_value(slider); // 0-100

    // 获取当前颜色
    lv_color_t color = lv_colorwheel_get_rgb(ui->smart_home_app_color_led_cpicker);
    uint32_t raw = lv_color_to32(color);
    lv_color32_t c32;
    c32.full = raw;
    uint8_t r = c32.ch.red;
    uint8_t g = c32.ch.green;
    uint8_t b = c32.ch.blue;

    // 应用亮度调整
    r = (uint8_t)((r * brightness) / 100);
    g = (uint8_t)((g * brightness) / 100);
    b = (uint8_t)((b * brightness) / 100);

    // 设置颜色
    ColorLed_SetColor(r, g, b);
}

// 绿灯开关事件
void smart_home_led_green_sw_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_VALUE_CHANGED)
        return;

    lv_obj_t *sw = lv_event_get_target(e);
    bool checked = lv_obj_has_state(sw, LV_STATE_CHECKED);

    if (checked) {
        // 打开绿灯
        LED_TurnOn(LED_Green);
    } else {
        // 关闭绿灯
        LED_TurnOff(LED_Green);
    }
}
#endif

