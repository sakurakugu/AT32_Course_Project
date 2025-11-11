#include "IoT.hpp"

#include "uart.h"
#include "board.h"
#include "bsp_eep_lm75.h"
#include "timer.h"
#include "board/led/led.h"
#include <cJSON.h>
#include <stdint.h>
#include "logger.h"
#include <string.h>

// 来自应用的串口接收保护标志
extern volatile uint8_t g_com3_guard;

// 心跳包相关变量
uint32_t heartbeat_timer = 0;
bool connection_status = 0; // 0: 未连接, 1: 已连接
uint32_t last_heartbeat_response_time = 0;
uint8_t heartbeat_sent = 0;                 // 标记是否已发送心跳包等待响应
uint32_t connection_lost_time = 0;          // 连接丢失时间
uint8_t consecutive_heartbeat_failures = 0; // 连续心跳失败次数
// 命令解析缓冲区
char command_buffer[256];
uint8_t command_index = 0;
uint8_t command_ready = 0;
// 发送状态上报
char TlinkCommandStr[20];
// 状态上报定时器
uint32_t send_timer = 0;
// 添加设备状态变量
uint8_t lm75_temp = 0;       // lm75温度值
uint16_t adc_value = 0;      // adc值
uint8_t lighting_status = 0; // 照明状态 (LED_YELLOW)


void IoT::ParseJson(char *cmd) {
    LOGI("\r\n收到命令: %s\r\n", cmd);

    cJSON *root = cJSON_Parse(cmd);
    if (root == NULL) {
        LOGI("JSON解析失败！\n");
        return;
    }

    // 判断是否是数组
    if (!cJSON_IsArray(root)) {
        LOGI("JSON格式错误，应为数组！\n");
        cJSON_Delete(root);
        return;
    }

    // 遍历数组中的每个对象
    int array_size = cJSON_GetArraySize(root);
    for (int i = 0; i < array_size; i++) {
        cJSON *item = cJSON_GetArrayItem(root, i);
        if (!cJSON_IsObject(item))
            continue;

        // 获取 sensorID 和 switch
        cJSON *sensorID = cJSON_GetObjectItem(item, "sensorID");
        cJSON *switch_val = cJSON_GetObjectItem(item, "switch");

        if (!cJSON_IsString(sensorID) || !cJSON_IsNumber(switch_val))
            continue;

        const char *id = sensorID->valuestring;
        int sw = switch_val->valueint;

        LOGI("解析到命令: %s = %d\n", id, sw);

        // 根据 sensorID 控制不同设备
        if (strcmp(id, "aircon_switch") == 0) {
            // control_aircon(sw);
            // send_timer = 25000;
        } else if (strcmp(id, "lighting_switch") == 0) {
            Control_Lighting(sw);
            send_timer = 25000;
        } else {
            LOGI("未知的设备ID: %s\n", id);
        }
    }

    cJSON_Delete(root);
}

// 处理接收到的数据
void IoT::Process_Received_Data() {
    uint8_t received_data;

    // 若存在串口接收保护，跳过读取，避免与HTTP流程抢占
    if (g_com3_guard) {
        return;
    }

    while (comGetChar(COM3, &received_data)) {
        // 处理心跳响应
        if (heartbeat_sent && received_data == 'A') {
            LOGI("\r\n收到心跳响应: A\r\n");
            connection_status = 1;
            heartbeat_sent = 0;
            consecutive_heartbeat_failures = 0;
            last_heartbeat_response_time = Timer_GetTickCount();
            continue;
        }

        // 处理JSON命令
        if (received_data == '[') {
            // 开始接收命令
            command_index = 0;
            command_buffer[command_index++] = received_data;
            command_ready = 0;
        } else if (received_data == ']' && command_index > 0) {
            // 命令接收完成
            command_buffer[command_index++] = received_data;
            command_buffer[command_index] = '\0';
            command_ready = 1;
        } else if (command_index > 0 && command_index < sizeof(command_buffer) - 1) {
            // 继续接收命令内容
            command_buffer[command_index++] = received_data;
        }

        // 如果命令准备好了，解析它
        if (command_ready) {
            ParseJson(command_buffer);
            command_ready = 0;
            command_index = 0;
        }
    }
}

// 检测心跳包 函数
void IoT::Check_Heartbeat() {
    Process_Received_Data();

    // 检查心跳响应超时
    if (heartbeat_sent && Timer_PassedDelay(last_heartbeat_response_time, HEARTBEAT_TIMEOUT)) {
        // LOGI("\r\n心跳响应超时 (失败次数: %d)\r\n", consecutive_heartbeat_failures + 1);
        heartbeat_sent = 0;
        consecutive_heartbeat_failures++;

        if (consecutive_heartbeat_failures >= MAX_HEARTBEAT_FAILURES) {
            if (connection_status == 1) {
                LOGI("\r\n连续%d次心跳失败，连接断开\r\n", MAX_HEARTBEAT_FAILURES);
                connection_status = 0;
                connection_lost_time = Timer_GetTickCount();
            }
        }
    }
}

// 心跳包发送函数
void IoT::Send_Heartbeat() {
    LOGI("\r\n发送心跳包: Q\r\n");
    comSendBuf(COM3, (uint8_t *)"Q", 1);
    heartbeat_sent = 1; // 标记已发送心跳包
    last_heartbeat_response_time = Timer_GetTickCount();
}


void IoT::Send_Status_Report() {
    lm75_temp = LM75::GetInstance().Read(); // 读取lm75温度值
    adc_value = analogRead();               // 读取ADC值
    sprintf(TlinkCommandStr, "#%d,%d,%d,%d#", lm75_temp, adc_value, 0, lighting_status);

    LOGI("\r\n上报状态: %s\r\n", TlinkCommandStr);

    if (connection_status) {
        comSendBuf(COM3, (uint8_t *)TlinkCommandStr, strlen(TlinkCommandStr));
    } else {
        LOGI("连接断开，状态未上报\r\n");
    }
}

// 控制照明
void IoT::Control_Lighting(uint8_t status) {
    lighting_status = status;
    if (status) {
        LED::GetInstance().On(LED_Green);
        LOGI("\r\n照明已开启 (LED_GREEN ON)\r\n");
    } else {
        LED::GetInstance().Off(LED_Green);
        LOGI("\r\n照明已关闭 (LED_GREEN OFF)\r\n");
    }
}
