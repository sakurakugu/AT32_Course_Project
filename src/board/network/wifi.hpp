/**
 * @brief ESP12 串口WIFI模块驱动程序
 * 
 */

#pragma once
#include <stdint.h>

#include "wifi.h"

/* 定义下面这句话, 将把收到的字符发送到调试串口1 */
#define ESP12_PRINTF_EN

/* 本模块部分函数用到了软件定时器最后1个ID。 因此主程序调用本模块的函数时，请注意回避定时器 TMR_COUNT - 1。
  bsp_StartTimer(3, _usTimeOut);

  TMR_COUNT 在 bsp_timer.h 文件定义
*/
#define ESP12_TMR_ID (TMR_COUNT - 1)
#define Wifi_TMR_ID ESP12_TMR_ID

// EEPROM 地址布局（16-bit 地址空间）
#define WIFI_EEP_ADDR_SSID     ((uint16_t)0x0000)   // 33字节：以'\0'结尾
#define WIFI_EEP_ADDR_PASSWORD ((uint16_t)0x0040)   // 65字节：以'\0'结尾

/* 加密方式 */
enum WIFI_ECN {
    ECN_OPEN = 0,
    ECN_WEP = 1,
    ECN_WPA_PSK = 2,
    ECN_WPA2_PSK = 3,
    ECN_WPA_WPA2_PSK = 4,
};

/**
 * @brief 串口设备结构体
 *  ecn:加密方式
 *    0   OPEN
 *    1   WEP
 *    2   WPA_PSK
 *    3   WPA2_PSK
 *    4   WPA_WPA2_PSK               
 */
typedef struct {
    char ssid[33];   /* SSID是一个无线局域网络（WLAN）的名称。SSID是区分大小写的文本字符串，最大长度32个字符 */
    uint8_t ecn;     /* 加密方式 */
    int32_t rssi;    /* 信号强度 */
    uint8_t mac[20]; /* MAC地址字符串*/
    uint8_t ch;      /* 信道 */
} WIFI_AP_T;



class Wifi {
  public:
    static Wifi &GetInstance() {
        static Wifi instance;
        return instance;
    }
    Wifi(const Wifi &) = delete;
    Wifi &operator=(const Wifi &) = delete;

    void init();
    void sendAT(const char *cmd); // 发送AT指令
    bool waitResponse(const char *ack_str, uint16_t us_timeout); // 等待响应
    uint16_t readLine(char *buffer, uint16_t size, uint16_t us_timeout); // 读取一行数据

    bool setWiFiMode(uint8_t mode); // 设置WiFi模式
    bool enableCIPMUX(uint8_t mode); // 启用CIPMUX模式

    bool setAPIP(const char *ip); // 设置AP IP地址
    bool setAPNamePass(const char *name, const char *pwd, uint8_t ch, uint8_t ecn); // 设置AP名称和密码

    bool createTCPServer(uint16_t port); // 创建TCP服务器
    bool createUDPServer(uint8_t id, uint16_t localPort); // 创建UDP服务器
    bool linkTCPServer(uint8_t id, const char *server_ip, uint16_t port); // 连接TCP服务器

    void sendTcpUdp(uint8_t id, uint8_t *data, uint16_t len); // 发送TCP/UDP数据
    void closeTcpUdp(uint8_t id); // 关闭TCP/UDP连接

    bool getLocalIP(char *ip, char *mac); // 获取本地IP地址和MAC地址
    bool joinAP(const char *ssid, const char *pwd, uint16_t timeout); // 加入AP
    void quitAP(); // 退出AP

  private:
    Wifi() = default;
};

