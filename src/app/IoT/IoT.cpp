#include "IoT.hpp"

#include "bsp_uart.h"
#include "board.h"
#include "bsp_eep_lm75.h"
#include "at32f435_437_board.h"
#include "timer.h"
#include <cJSON.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

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
    printf("\r\n收到命令: %s\r\n", cmd);

    cJSON *root = cJSON_Parse(cmd);
    if (root == NULL) {
        printf("JSON解析失败！\n");
        return;
    }

    // 判断是否是数组
    if (!cJSON_IsArray(root)) {
        printf("JSON格式错误，应为数组！\n");
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

        printf("解析到命令: %s = %d\n", id, sw);

        // 根据 sensorID 控制不同设备
        if (strcmp(id, "aircon_switch") == 0) {
            // control_aircon(sw);
            // send_timer = 25000;
        } else if (strcmp(id, "lighting_switch") == 0) {
            Control_Lighting(sw);
            send_timer = 25000;
        } else {
            printf("未知的设备ID: %s\n", id);
        }
    }

    cJSON_Delete(root);
}

// 心跳包发送函数
void IoT::Send_Heartbeat() {
    printf("\r\n发送心跳包: Q\r\n");
    comSendBuf(COM3, (uint8_t *)"Q", 1);
    heartbeat_sent = 1; // 标记已发送心跳包
    last_heartbeat_response_time = Timer_GetTickCount();
}


void IoT::Send_Status_Report() {
    lm75_temp = LM75::GetInstance().Read(); // 读取lm75温度值
    adc_value = analogRead();               // 读取ADC值
    sprintf(TlinkCommandStr, "#%d,%d,%d,%d#", lm75_temp, adc_value, 0, lighting_status);

    printf("\r\n上报状态: %s\r\n", TlinkCommandStr);

    if (connection_status) {
        comSendBuf(COM3, (uint8_t *)TlinkCommandStr, strlen(TlinkCommandStr));
    } else {
        printf("连接断开，状态未上报\r\n");
    }
}

// 控制照明
void IoT::Control_Lighting(uint8_t status) {
    lighting_status = status;
    if (status) {
        at32_led_on(LED_Yellow);
        printf("\r\n照明已开启 (LED_YELLOW ON)\r\n");
    } else {
        at32_led_off(LED_Yellow);
        printf("\r\n照明已关闭 (LED_YELLOW OFF)\r\n");
    }
}
