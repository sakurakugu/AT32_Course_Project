
/**
 * @brief  串口中断+FIFO驱动模块
 * @file   bsp_uart.h
 */

#pragma once
#include "at32f435_437.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 仅启用需要的串口 FIFO（USART1 调试、USART3 WiFi） */
#define UART1_FIFO_EN 1
#define UART3_FIFO_EN 1

#ifdef UART1_FIFO_EN
/* 打印串口（USART1） */
#define PRINT_UART USART1
#define PRINT_UART_CRM_CLK CRM_USART1_PERIPH_CLOCK
#define PRINT_UART_TX_PIN GPIO_PINS_6
#define PRINT_UART_TX_GPIO GPIOB
#define PRINT_UART_TX_GPIO_CRM_CLK CRM_GPIOB_PERIPH_CLOCK
#define PRINT_UART_TX_PIN_SOURCE GPIO_PINS_SOURCE6
#define PRINT_UART_TX_PIN_MUX_NUM GPIO_MUX_7
//    打印串口接收引脚定义，用于 uart_print_init
#define PRINT_UART_RX_PIN GPIO_PINS_7
#define PRINT_UART_RX_GPIO GPIOB
#define PRINT_UART_RX_GPIO_CRM_CLK CRM_GPIOB_PERIPH_CLOCK
#define PRINT_UART_RX_PIN_SOURCE GPIO_PINS_SOURCE7
#define PRINT_UART_RX_PIN_MUX_NUM GPIO_MUX_7
#endif

/* USART3 作为 WiFi 模块串口（ESP12） */
#ifdef UART3_FIFO_EN
#define ESP12_UART USART3
#define ESP12_UART_CRM_CLK CRM_USART3_PERIPH_CLOCK
#define ESP12_UART_TX_PIN GPIO_PINS_10
#define ESP12_UART_TX_GPIO GPIOC
#define ESP12_UART_TX_GPIO_CRM_CLK CRM_GPIOC_PERIPH_CLOCK
#define ESP12_UART_TX_PIN_SOURCE GPIO_PINS_SOURCE10
#define ESP12_UART_TX_PIN_MUX_NUM GPIO_MUX_7

#define ESP12_UART_RX_PIN GPIO_PINS_11
#define ESP12_UART_RX_GPIO GPIOC
#define ESP12_UART_RX_GPIO_CRM_CLK CRM_GPIOC_PERIPH_CLOCK
#define ESP12_UART_RX_PIN_SOURCE GPIO_PINS_SOURCE11
#define ESP12_UART_RX_PIN_MUX_NUM GPIO_MUX_7
#endif

/* PB2 控制RS485芯片的发送开启 */
#define RS485_TXEN_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define RS485_TXEN_GPIO_PORT GPIOB
#define RS485_TXEN_PIN GPIO_PIN_2

#define RS485_RX_EN() RS485_TXEN_GPIO_PORT->BSRRH = RS485_TXEN_PIN
#define RS485_TX_EN() RS485_TXEN_GPIO_PORT->BSRRL = RS485_TXEN_PIN

/* 定义端口号 */
typedef enum {
    COM1 = 0, /* USART1 */
    COM2 = 1, /* USART2 */
    COM3 = 2, /* USART3 */
    COM4 = 3, /* UART4 */
    COM5 = 4, /* UART5 */
    COM6 = 5, /* USART6 */
    COM7 = 6, /* UART7 */
    COM8 = 7  /* UART8 */
} COM_PORT_E;

/* 定义串口波特率和FIFO缓冲区大小，分为发送缓冲区和接收缓冲区, 支持全双工 */
/* USART1（调试串口）FIFO 参数 */
#if UART1_FIFO_EN == 1
#define UART1_BAUD 115200
#define UART1_TX_BUF_SIZE (1 * 1024)
#define UART1_RX_BUF_SIZE (1 * 1024)
#endif

/* USART3（WiFi串口）FIFO 参数 */
#if UART3_FIFO_EN == 1
#define UART3_BAUD 115200
#define UART3_TX_BUF_SIZE (1 * 1024)
#define UART3_RX_BUF_SIZE (1 * 1024)
#endif

void comSendBuf(COM_PORT_E _ucPort, uint8_t *_ucaBuf, uint16_t _usLen);
void comSendChar(COM_PORT_E _ucPort, uint8_t _ucByte);
uint8_t comGetChar(COM_PORT_E _ucPort, uint8_t *_pByte);
void comSendBuf(COM_PORT_E _ucPort, uint8_t *_ucaBuf, uint16_t _usLen);
void comClearTxFifo(COM_PORT_E _ucPort);
void comClearRxFifo(COM_PORT_E _ucPort);

void esp12_uart_init(uint32_t baudrate);
void uart_print_init(uint32_t baudrate);

#ifdef __cplusplus
}
#endif

class Uart {
  public:
    /* 通过外部提供的环形缓冲区进行构造，避免动态内存分配 */
    Uart(usart_type *usart, uint8_t *tx_buf, uint16_t tx_buf_size, uint8_t *rx_buf, uint16_t rx_buf_size);

    /* 配置串口基本参数并开启收发与接收中断 */
    void Begin(uint32_t baudrate);

    /* 发送 API */
    void SendBuf(const uint8_t *buf, uint16_t len);
    void SendChar(uint8_t byte);

    /* 接收 API（非阻塞，返回 1 表示读到数据） */
    uint8_t GetChar(uint8_t *out_byte);

    /* FIFO 管理 */
    void ClearTx();
    void ClearRx();
    uint8_t TxEmpty() const; /* 1=空，0=非空 */

    /* 可选回调（例如 RS485 用途） */
    void SetCallbacks(void (*SendBefor)(void), void (*SendOver)(void), void (*ReciveNew)(uint8_t));

    /* 中断处理入口 */
    void onIRQ();

    /* 访问底层 usart 寄存器指针 */
    usart_type *Instance() const { return uart_; }

  private:
    /* 禁止拷贝 */
    Uart(const Uart &) = delete;
    Uart &operator=(const Uart &) = delete;

    /* 内部工具：关/开全局中断（与原实现保持一致） */
    inline void DisableIRQ() const { __set_PRIMASK(1); }
    inline void EnableIRQ() const { __set_PRIMASK(0); }

    usart_type *uart_; // STM32内部串口设备指针
    uint8_t *tx_buf_;  // 发送缓冲区
    uint8_t *rx_buf_;  // 接收缓冲区
    uint16_t tx_size_; // 发送缓冲区大小
    uint16_t rx_size_; // 接收缓冲区大小

    volatile uint16_t tx_write_; // 发送缓冲区写指针
    volatile uint16_t tx_read_;  // 发送缓冲区读指针
    volatile uint16_t tx_count_; // 等待发送的数据个数

    volatile uint16_t rx_write_; // 接收缓冲区写指针
    volatile uint16_t rx_read_;  // 接收缓冲区读指针
    volatile uint16_t rx_count_; // 还未读取的新数据个数

    void (*SendBefor_)(void) = nullptr;    // 开始发送之前的回调函数指针（主要用于RS485切换到发送模式）
    void (*SendOver_)(void) = nullptr;     // 发送完毕的回调函数指针（主要用于RS485将发送模式切换为接收模式）
    void (*ReciveNew_)(uint8_t) = nullptr; // 串口收到数据的回调函数指针
};
