#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include <functional>
#include "mutex.h"


class Application {
  public:
    static Application &GetInstance() {
        static Application instance;
        return instance;
    }
    // 删除拷贝构造函数和赋值运算符
    Application(const Application &) = delete;
    Application &operator=(const Application &) = delete;

    void Start();
    void Reboot(); // 重启设备
    void OnClockTimer(); // 统一定时任务入口（由10ms节拍回调）
    
    Application();
    ~Application();
  private:

    // mutex mutex_; // 互斥锁

    // void Schedule(std::function<void()> callback); // 添加异步任务到主循环
    // void MainEventLoop();                          // 主事件循环
};

