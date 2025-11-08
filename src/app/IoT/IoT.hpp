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
    void Process_Received_Data(); // 处理接收数据
    void Check_Heartbeat(); // 检查心跳包
    void Send_Heartbeat(); // 发送心跳包
    void Send_Status_Report(); // 发送状态上报

    void Control_Lighting(uint8_t status); // 控制照明

  private:
    IoT() = default;
    ~IoT() = default;
};