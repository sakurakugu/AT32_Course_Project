/**
 * @brief WeatherService: 从网络获取天气并更新 LVGL 界面
 */

#pragma once

#include "lvgl.h"
#include "../../gui/generated/gui_guider.h"

class WeatherService {
public:
    static WeatherService &GetInstance() {
        static WeatherService instance;
        return instance;
    }

    WeatherService(const WeatherService &) = delete;
    WeatherService &operator=(const WeatherService &) = delete;

    // 更新当前天气与未来三天预报到指定 UI
    bool UpdateWeather(lv_ui *ui);

private:
    WeatherService() = default;

    bool http_get_seniverse(const char *path, char *resp_out, int resp_out_size);
    bool parse_and_apply_current(lv_ui *ui, const char *http_resp);
    bool parse_and_apply_daily(lv_ui *ui, const char *http_resp);
};