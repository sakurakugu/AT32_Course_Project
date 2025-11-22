// 这是后端
#pragma once

#include <stdint.h>

// 心跳包相关变量
extern uint32_t heartbeat_timer;
extern bool connection_status; // 0: 未连接, 1: 已连接
extern uint32_t last_heartbeat_response_time;
extern uint8_t heartbeat_sent;                 // 标记是否已发送心跳包等待响应
extern uint32_t connection_lost_time;          // 连接丢失时间
extern uint8_t consecutive_heartbeat_failures; // 连续心跳失败次数
// 命令解析缓冲区
extern char command_buffer[256];
extern uint8_t command_index;
extern uint8_t command_ready;
// 发送状态上报
extern char TlinkCommandStr[20];
// 状态上报定时器
extern uint32_t send_timer;
// 添加设备状态变量
extern uint8_t lm75_temp;       // lm75温度值
extern uint16_t adc_value;      // adc值
extern uint8_t lighting_status; // 照明状态 (LED_YELLOW)
#define HEARTBEAT_INTERVAL 55000            // 55秒心跳间隔
#define HEARTBEAT_TIMEOUT 5000              // 5秒心跳响应超时
#define MAX_HEARTBEAT_FAILURES 3            // 最大连续心跳失败次数
