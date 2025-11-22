/**
 * @brief ESP12 串口WIFI模块驱动程序
 * @file wifi.c
 */

#include "wifi.hpp"
#include "timer.h"
#include "uart.h"
// logger
#include <stdio.h>
#include <string.h>

#define COM_ESP12 COM3

#define AT_CR '\r'
#define AT_LF '\n'

char g_EspBuf[2048]; /* 用于解码 */

/**
 * @brief  ESP12 串口WIFI模块中断服务函数
 */
// #if ESP12_DEBUG
// void USART1_IRQHandler() {
//     if (USART1->ctrl1_bit.rdbfien != RESET) {
//         if (usart_flag_get(USART1, USART_RDBF_FLAG) != RESET) {
//             usart_data_transmit(ESP12_UART, usart_data_receive(USART1));
//         }
//     }
// }
// #endif

/**
 * @brief 初始化ESP12 串口WIFI模块
 * 配置无线模块相关的GPIO,  该函数被 bsp_Init() 调用。
 */
void Wifi::Init() {
    esp12_uart_init(UART3_BAUD);
}

/**
 * @brief 打印STM32从ESP12收到的数据到COM1串口，主要用于跟踪调试
 * @param _ch : 收到的数据
 */
void ESP12_PrintRxData(uint8_t _ch) {
#ifdef ESP12_PRINTF_EN
    comSendChar(COM1, _ch); /* 将接收到数据打印到调试串口1 */
#endif
}

/**
 * @brief 等待ESP12返回指定的应答字符串, 可以包含任意字符。只要接收齐全即可返回。
 * @param ack_str : 应答的字符串， 长度不得超过255
 * @param us_timeout : 命令执行超时，0表示一直等待. >０表示超时时间，单位1ms
 * @return bool true 表示成功  false 表示失败
 */
bool Wifi::WaitResponse(const char *ack_str, uint16_t us_timeout) {
    uint8_t ucData;
    uint16_t pos = 0;
    uint32_t len;
    bool ret = false;
    uint32_t rx_bytes = 0;

    len = strlen(ack_str);
    if (len > 255) {
        return false;
    }

    /* us_timeout == 0 表示无限等待 */
    if (us_timeout > 0) {
        bsp_StartTimer(Wifi_TMR_ID, us_timeout); /* 使用软件定时器3，作为超时控制 */
    }
    while (1) {

        if (us_timeout > 0) {
            if (bsp_CheckTimer(Wifi_TMR_ID)) {
                ret = false; /* 超时 */
                break;
            }
        }

        if (comGetChar(COM_ESP12, &ucData)) {
            rx_bytes++;
            ESP12_PrintRxData(ucData); /* 将接收到数据打印到调试串口1 */

            if (ucData == ack_str[pos]) {
                pos++;

                if (pos == len) {
                    ret = true; /* 收到指定的应答数据，返回成功 */
                    break;
                }
            } else {
                pos = 0;
            }
        }
    }
    return ret;
}

/**
 * @brief 读取ESP12返回的一行应答字符串(0x0D 0x0A结束)。该函数根据字符间超时判断结束。
 * @param buffer : 存放模块返回的完整字符串
 * @param size : 缓冲区最大长度
 * @param us_timeout : 命令执行超时，0表示一直等待. >0 表示超时时间，单位1ms
 * @return uint16_t 0 表示错误（超时）  > 0 表示应答的数据长度
 */
uint16_t Wifi::ReadLine(char *buffer, uint16_t size, uint16_t us_timeout) {
    uint8_t ucData;
    uint16_t pos = 0;
    uint8_t ret;

    /* us_timeout == 0 表示无限等待 */
    if (us_timeout > 0) {
        bsp_StartTimer(Wifi_TMR_ID, us_timeout); /* 使用软件定时器作为超时控制 */
    }
    while (1) {

        if (bsp_CheckTimer(Wifi_TMR_ID)) {
            buffer[pos] = 0; /* 结尾加0， 便于函数调用者识别字符串结束 */
            ret = pos;       /* 成功。 返回数据长度 */
            break;
        }

        if (comGetChar(COM_ESP12, &ucData)) {
            ESP12_PrintRxData(ucData); /* 将接收到数据打印到调试串口1 */

            bsp_StartTimer(Wifi_TMR_ID, 500);
            /* 保护缓冲区，避免溢出导致数据破坏 */
            if (pos < (uint16_t)(size - 1)) {
                buffer[pos++] = ucData; /* 保存接收到的数据 */
            } else {
                /* 缓冲区已满，提前终止本次读取，返回已有数据 */
                buffer[pos] = 0;
                ret = pos;
                break;
            }
            if (ucData == 0x0A) {
                buffer[pos] = 0;
                ret = pos; /* 成功。 返回数据长度 */
                break;
            }
        }
    }
    return ret;
}

/**
 * @brief 向模块发送AT命令。 本函数自动在AT字符串口增加<CR>字符
 * @param _Cmd : AT命令字符串，不包括末尾的回车<CR>. 以字符0结束
 */
void Wifi::SendAT(const char *_Cmd) {
    comSendBuf(COM_ESP12, (uint8_t *)_Cmd, strlen(_Cmd));
    comSendBuf(COM_ESP12, (uint8_t *)"\r\n", 2);
}

/**
 * @brief 设置WiFi模块工作模式
 * @param _mode : 1 = Station模式,  2 = AP模式,  3 = AP兼Station模式
 * @return bool true 表示成功  false 表示失败
 */
bool Wifi::SetWiFiMode(uint8_t _mode) {
    char cmd_buf[30];

    if (_mode == 0 || _mode > 3) {
        _mode = 3;
    }
    sprintf(cmd_buf, "AT+CWMODE=%d", _mode);
    SendAT(cmd_buf);
    // 兼容 OK、无CRLF的 OK
    if (WaitResponse("OK\r\n", 2000) == false) {
        if (WaitResponse("OK", 2000) == false) {
            return false;
        }
    }

    return true;
}

/**
 * @brief 启动多连接模式
 * @param _mode : 0,表示关闭， 1表示启动
 * @return bool true 表示成功  false 表示失败
 */
bool Wifi::EnableCIPMUX(uint8_t _mode) {
    char cmd_buf[30];

    if (_mode > 0) {
        _mode = 1;
    }
    sprintf(cmd_buf, "AT+CIPMUX=%d", _mode);
    SendAT(cmd_buf);
    if (WaitResponse("OK\r\n", 2000) == false) {
        if (WaitResponse("OK", 2000) == false) {
            return false;
        }
    }

    return true;
}

/**
 * @brief 设置AP的IP地址
 * @param _ip :AP的IP地址，标准字符串
 * @return bool true 表示成功  false 表示失败
 */
bool Wifi::SetAPIP(const char *_ip) {
    char cmd_buf[30];

    sprintf(cmd_buf, "AT+CIPAP=\"%s\"", _ip);
    SendAT(cmd_buf);
    if (WaitResponse("OK\r\n", 1000) == false) {
        if (WaitResponse("OK", 1000) == false) {
            return false;
        }
    }

    return true;
}

/**
 * @brief 设置SoftAP的名字，加密方式和密码.  加密方式为 0 表示不加密， 1 表示 WEP 加密， 2 表示 WPA_PSK 加密， 3 表示
 * WPA2_PSK 加密
 * @param _name :AP的名字，字符串参数，密码最长 64 字节 ASCII
 * @param _pwd : AP的密码，字符串参数，密码最长 64 字节 ASCII
 * @param _ch : 通道号
 * @param _ecn : 加密方式
 * @return bool true 表示成功  false 表示失败
 */
bool Wifi::SetAPNamePass(const char *_name, const char *_pwd, uint8_t _ch, uint8_t _ecn) {
    char cmd_buf[40];

    /* AT+CWSAP="ESP12","1234567890",5,3 */
    sprintf(cmd_buf, "AT+CWSAP=\"%s\",\"%s\",%d,%d", _name, _pwd, _ch, _ecn);
    SendAT(cmd_buf);
    if (WaitResponse("OK\r\n", 500) == false) {
        return false;
    }

    return true;
}

/**
 * @brief 创建一个TCP服务端。 必须在连接到AP之后才行。 需要先启用多连接
 * @param _TcpPort : TCP 端口号
 * @return bool true 表示成功  false 表示失败
 */
bool Wifi::CreateTCPServer(uint16_t _TcpPort) {
    char cmd_buf[30];

    SendAT("AT+CIPMUX=1"); /* 启动多连接 */
    if (WaitResponse("OK", 2000) == false) {
        return false;
    }

    /* 开启TCP server, 端口为 _TcpPort */
    sprintf(cmd_buf, "AT+CIPSERVER=1,%d", _TcpPort);
    SendAT(cmd_buf);
    if (WaitResponse("OK\r\n", 2000) == false) {
        return false;
    }

    SendAT("ATE0"); /* 关闭回显功能，主机发送的字符，模块无需返回 */
    if (WaitResponse("OK", 10000) == false) {
        return false;
    }

    return true;
}

/**
 * @brief 创建一个UDP服务端。 必须在连接到AP之后才行。 需要先启用多连接
 * @param _id : 连接ID, 0-4
 * @param _LaocalPort : UDP 端口号
 * @return bool true 表示成功  false 表示失败
 */
bool Wifi::CreateUDPServer(uint8_t _id, uint16_t _LaocalPort) {
    char cmd_buf[64];

    SendAT("AT+CIPMUX=1"); /* 启动多连接 */
    if (WaitResponse("OK", 2000) == false) {
        return false;
    }

    /* 多连接 UDP */
    // AT+CIPSTART=0,"UDP","255.255.255.255",8080,8080,0
    sprintf(cmd_buf, "AT+CIPSTART=%d,\"UDP\",\"255.255.255.255\",8080,%d, 0", _id, _LaocalPort);

    // AT+CIPSTART="UDP","255.255.255.255",8080,8080,1
    // sprintf(cmd_buf, "AT+CIPSTART=\"UDP\",\"255.255.255.255\",8080,%d,2", _LaocalPort);

    SendAT(cmd_buf);
    if (WaitResponse("OK\r\n", 3000) == false) {
        return false;
    }

    SendAT("ATE0"); /* 关闭回显功能，主机发送的字符，模块无需返回 */
    if (WaitResponse("OK", 10000) == false) {
        return false;
    }

    return true;
}

/**
 * @brief 连接到一个TCP服务端。  仅(+CIPMUX=1) 多连接模式。
 * @param _id : 连接的id号
 * @param _server_ip : 服务器域名或IP地址
 * @param _TcpPort : TCP 端口号
 * @return bool true 表示成功  false 表示失败
 */
bool Wifi::LinkTCPServer(uint8_t _id, const char *_server_ip, uint16_t _TcpPort) {
    char cmd_buf[30];

#if 0 /* 单连接 */
	//AT+CIPSTART="TCP","192.168.101.110",1000
	sprintf(cmd_buf, "AT+CIPSTART=\"TCP\",\"%s\",%d",_server_ip, _TcpPort);
#else /* 多连接 */
    // AT+CIPSTART=0, "TCP","192.168.101.110",1000
    sprintf(cmd_buf, "AT+CIPSTART=%d,\"TCP\",\"%s\",%d", _id, _server_ip, _TcpPort);
#endif
    SendAT(cmd_buf);
    if (WaitResponse("OK\r\n", 3000) == false) {
        if (WaitResponse("OK", 3000) == false) {
            return false;
        }
    }

    return true;
}

/**
 * @brief 发送TCP或UDP数据包
 * @param _id : 多连接时，连接ID （0-4）
 * @param _databuf 数据
 * @param _len 数据长度
 */
void Wifi::SendTcpUdp(uint8_t _id, uint8_t *_databuf, uint16_t _len) {
    char buf[32];

    if (_len > 2048) {
        _len = 2048;
    }

    sprintf(buf, "AT+CIPSEND=%d,%d\r\n", _id, _len);
    comSendBuf(COM_ESP12, (uint8_t *)buf, strlen(buf));

    WaitResponse(">", 1000);

    comSendBuf(COM_ESP12, _databuf, _len);
    WaitResponse("SEND OK", 8000);
}

/**
 * @brief 关闭TCP或UDP连接. 用于多路连接
 * @param _id : 多连接时，连接ID （0-4）
 */
void Wifi::CloseTcpUdp(uint8_t _id) {
    char buf[32];

    SendAT("ATE1"); /* 打开回显功能 */
    WaitResponse("SEND OK", 50);

    sprintf(buf, "AT+CIPCLOSE=%d", _id);
    SendAT(buf);
    WaitResponse("OK", 200);
}

/**
 * @brief 查询本机IP地址和MAC
 * @param _ip : 本机IP地址字符串
 * @param _mac : 本机MAC地址字符串
 * @return bool true 表示OK， false 表示未知
 */
bool Wifi::GetLocalIP(char *_ip, char *_mac) {
    char buf[64];
    uint8_t i, m;
    uint8_t ret = 0;
    uint8_t temp;

    SendAT("AT+CIFSR");

    /*　模块将应答:

    +CIFSR:STAIP,"192.168.1.18"
    +CIFSR:STAMAC,"18:fe:34:a6:44:75"

    OK
    */

    _ip[0] = 0;
    _mac[0] = 0;
    for (i = 0; i < 4; i++) {
        ReadLine(buf, sizeof(buf), 500);
        if (memcmp(buf, "+CIFSR:STAIP", 12) == 0) {

            for (m = 0; m < 20; m++) {
                temp = buf[14 + m];
                _ip[m] = temp;
                if (temp == '"') {
                    _ip[m] = 0;
                    ret = true;
                    break;
                }
            }
        } else if (memcmp(buf, "+CIFSR:STAMAC,", 14) == 0) {
            for (m = 0; m < 20; m++) {
                temp = buf[15 + m];
                _mac[m] = temp;
                if (temp == '"') {
                    _mac[m] = 0;
                    ret = true;
                    break;
                }
            }
        } else if (memcmp(buf, "OK", 2) == 0) {
            break;
        }
    }
    return ret;
}

/**
 * @brief 加入AP
 * @param _ssid : AP名字字符串
 * @param _pwd : 密码字符串
 * @param _timeout : 超时时间，单位毫秒
 * @return bool true 表示 0K  false 表示失败
 */
bool Wifi::JoinAP(const char *_ssid, const char *_pwd, uint16_t _timeout) {
    char buf[64];
    bool ret;

    sprintf(buf, "AT+CWJAP=\"%s\",\"%s\"", _ssid, _pwd);
    SendAT(buf);

    if (ReadLine(buf, 64, _timeout)) {
        /* ATE1的情况，有命令回显的情况 */
        if (memcmp(buf, "AT+CWJAP", 8) == 0) /* 第1次读到的是 命令本身 */
        {
            ReadLine(buf, 64, _timeout); /* 这个是回车 */
            ReadLine(buf, 64, _timeout); /* 这次是读应答的OK */

            if (memcmp(buf, "OK", 2) == 0) {
                return 1;
            }
        } else /* ATE0 无回显的情况 */
        {
            ret = WaitResponse("OK\r\n", _timeout);
            if (ret != true) {
                ret = WaitResponse("OK", _timeout);
            }
            if (ret == true) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief 退出当前的AP连接
 */
void Wifi::QuitAP() {
    SendAT("AT+ CWQAP");
}
