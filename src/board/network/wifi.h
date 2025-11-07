/*
*********************************************************************************************************
*
*	模块名称 : ESP12 串口WIFI模块驱动程序
*	文件名称 : bsp_uart_esp12.h
*
*********************************************************************************************************
*/

#pragma once
#include <stdint.h>

/* 定义下面这句话, 将把收到的字符发送到调试串口1 */
#define ESP12_PRINTF_EN

/* 本模块部分函数用到了软件定时器最后1个ID。 因此主程序调用本模块的函数时，请注意回避定时器 TMR_COUNT - 1。
  bsp_StartTimer(3, _usTimeOut);

  TMR_COUNT 在 bsp_timer.h 文件定义
*/
#define ESP12_TMR_ID (TMR_COUNT - 1)
#define Wifi_TMR_ID ESP12_TMR_ID

/* 串口设备结构体 */
typedef struct {
    char ssid[33];   /* SSID是一个无线局域网络（WLAN）的名称。SSID是区分大小写的文本字符串，最大长度32个字符 */
    uint8_t ecn;     /* 加密方式
                         0   OPEN
                         1   WEP
                         2   WPA_PSK
                         3   WPA2_PSK
                         4   WPA_WPA2_PSK
                     */
    int32_t rssi;    /* 信号强度 */
    uint8_t mac[20]; /* MAC地址字符串*/
    uint8_t ch;      /* 信道 */
} WIFI_AP_T;

/* 加密方式 */
enum {
    ECN_OPEN = 0,
    ECN_WEP = 1,
    ECN_WPA_PSK = 2,
    ECN_WPA2_PSK = 3,
    ECN_WPA_WPA2_PSK = 4,
};

class Wifi {
  public:
    void init();
    void sendAT(const char *cmd);
    uint8_t waitResponse(const char *ack_str, uint16_t us_timeout);
    uint16_t readLine(char *buffer, uint16_t size, uint16_t us_timeout);

    uint8_t setWiFiMode(uint8_t mode);
    uint8_t enableCIPMUX(uint8_t mode);

    uint8_t setAPIP(const char *ip);
    uint8_t setAPNamePass(const char *name, const char *pwd, uint8_t ch, uint8_t ecn);

    uint8_t createTCPServer(uint16_t port);
    uint8_t createUDPServer(uint8_t id, uint16_t localPort);
    uint8_t linkTCPServer(uint8_t id, const char *server_ip, uint16_t port);

    void sendTcpUdp(uint8_t id, uint8_t *data, uint16_t len);
    void closeTcpUdp(uint8_t id);

    uint8_t getLocalIP(char *ip, char *mac);
    uint8_t joinAP(const char *ssid, const char *pwd, uint16_t timeout);
    void quitAP();
};

extern Wifi g_wifi;
