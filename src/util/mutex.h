#pragma once

#include "FreeRTOS.h"
#include "semphr.h"

class mutex {
  public:
    mutex() { handle_ = xSemaphoreCreateMutex(); }
    ~mutex() {
        if (handle_)
            vSemaphoreDelete(handle_);
    }

    void lock() { xSemaphoreTake(handle_, portMAX_DELAY); } // 阻塞等待直到获取互斥锁
    void unlock() { xSemaphoreGive(handle_); }

    // 禁止拷贝（互斥锁不可复制）
    mutex(const mutex &) = delete;
    mutex &operator=(const mutex &) = delete;

  private:
    SemaphoreHandle_t handle_;
};