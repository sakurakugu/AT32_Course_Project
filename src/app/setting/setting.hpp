#pragma once
#include "setting.h"

class Setting {
  public:
    static Setting &GetInstance() {
        static Setting instance;
        return instance;
    }
    // 删除拷贝构造函数和赋值运算符
    Setting(const Setting &) = delete;
    Setting &operator=(const Setting &) = delete;

    bool SyncNetworkTime(); // 同步网络时间
    bool ParseDatetimeISO8601(const char *json, int *year, int *month, int *day, int *hour, int *min, int *sec); // 解析 ISO 8601 格式的日期时间字符串
    void ApplyTimeToAll(int hour, int min, int sec); // 应用时间到所有界面
    void ApplyDateLabels(int year, int month, int day); // 应用日期到所有界面
    void BacklightSetPercent(uint8_t percent); // 设置背光亮度百分比

  private:
    Setting() = default;
    ~Setting() = default;
};