// 这是后端
#pragma once

#include "IoT.h"



class IoT {
  public:
    static IoT &GetInstance() {
        static IoT instance;
        return instance;
    }
    // 删除拷贝构造函数和赋值运算符
    IoT(const IoT &) = delete;
    IoT &operator=(const IoT &) = delete;

    void ParseJson(char *cmd);
    void ProcessReceivedData(); // 处理接收数据
    void CheckHeartbeat(); // 检查心跳包
    void SendHeartbeat(); // 发送心跳包
    void SendStatusReport(); // 发送状态上报

    void ControlLighting(uint8_t status); // 控制照明

  private:
    IoT() = default;
    ~IoT() = default;
};