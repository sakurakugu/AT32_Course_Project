/**
 *
 *  @brief 串口中断 + FIFO驱动模块 + 保留兼容的 C 接口
 */

#include "uart.h"
#include <stdio.h>

#ifdef __cplusplus

Uart::Uart(usart_type *usart, uint8_t *tx_buf, uint16_t tx_buf_size, uint8_t *rx_buf, uint16_t rx_buf_size)
    : uart_(usart), tx_buf_(tx_buf), rx_buf_(rx_buf), tx_size_(tx_buf_size), rx_size_(rx_buf_size), tx_write_(0),
      tx_read_(0), tx_count_(0), rx_write_(0), rx_read_(0), rx_count_(0) {}

void Uart::begin(uint32_t baudrate) {
    /* 配置串口参数并开启收发和接收中断 */
    usart_init(uart_, baudrate, USART_DATA_8BITS, USART_STOP_1_BIT);
    usart_transmitter_enable(uart_, TRUE);
    usart_receiver_enable(uart_, TRUE);
    usart_interrupt_enable(uart_, USART_RDBF_INT, TRUE);
    usart_enable(uart_, TRUE);
}

void Uart::sendBuf(const uint8_t *buf, uint16_t len) {
    if (SendBefor_) {
        SendBefor_();
    }
    for (uint16_t i = 0; i < len; i++) {
        /* 等待缓冲区有空位 */
        while (true) {
            volatile uint16_t count;
            disableIRQ();
            count = tx_count_;
            enableIRQ();
            if (count < tx_size_) {
                break;
            } else if (count == tx_size_) {
                /* 数据已填满缓冲区，确保发送缓冲区空中断开启 */
                if ((uart_->ctrl1_bit.tdbeien) == 0) {
                    uart_->ctrl1_bit.tdbeien = 1;
                }
            }
        }

        /* 填入发送 FIFO */
        tx_buf_[tx_write_] = buf[i];
        disableIRQ();
        if (++tx_write_ >= tx_size_) {
            tx_write_ = 0;
        }
        tx_count_++;
        enableIRQ();
    }

    /* 开启数据发送完毕中断（缓冲区空） */
    uart_->ctrl1_bit.tdcien = 1;
}

void Uart::sendChar(uint8_t byte) {
    sendBuf(&byte, 1);
}

/**
 *	 @brief UartGetChar
 *	 @details 从串口接收缓冲区读取1字节数据 （用于主程序调用）
 *	 @param _pUart : 串口设备
 *	 @param _pByte : 存放读取数据的指针
 *	 @return 0 表示无数据  1表示读取到数据
 */
uint8_t Uart::getChar(uint8_t *out_byte) {
    uint16_t count;
    disableIRQ();
    count = rx_count_;
    enableIRQ();
    if (count == 0) {
        return 0;
    } else {
        *out_byte = rx_buf_[rx_read_];
        disableIRQ();
        if (++rx_read_ >= rx_size_) {
            rx_read_ = 0;
        }
        rx_count_--;
        enableIRQ();
        return 1;
    }
}

void Uart::clearTx() {
    tx_write_ = 0;
    tx_read_ = 0;
    tx_count_ = 0;
}

void Uart::clearRx() {
    rx_write_ = 0;
    rx_read_ = 0;
    rx_count_ = 0;
}

/**
 *	 @brief UartTxEmpty
 *	 @details 判断发送缓冲区是否为空。
 *	 @param _pUart : 串口设备
 *	 @return 1为空。0为不空。
 */
uint8_t Uart::txEmpty() const {
    return tx_count_ == 0 ? 1 : 0;
}

void Uart::setCallbacks(void (*SendBefor)(void), void (*SendOver)(void), void (*ReciveNew)(uint8_t)) {
    SendBefor_ = SendBefor;
    SendOver_ = SendOver;
    ReciveNew_ = ReciveNew;
}

void Uart::onIRQ() {
    uint32_t isrflags = (uart_->sts);

    /* 接收中断处理 */
    if (uart_->ctrl1_bit.rdbfien != RESET) {
        if ((isrflags & USART_RDBF_FLAG) != RESET) {
            uint8_t ch = usart_data_receive(uart_);
            rx_buf_[rx_write_] = ch;
            if (++rx_write_ >= rx_size_) {
                rx_write_ = 0;
            }
            if (rx_count_ < rx_size_) {
                rx_count_++;
            }
            if (ReciveNew_) {
                ReciveNew_(ch);
            }
        }
    }

    /* 发送缓冲区空中断 */
    if (uart_->ctrl1_bit.tdbeien != RESET) {
        if ((isrflags & USART_TDBE_FLAG) != RESET) {
            if (tx_count_ == 0) {
                /* 发送缓冲区的数据已取完：关闭缓冲区空中断，开启发送完成中断 */
                usart_interrupt_enable(uart_, USART_TDBE_INT, FALSE);
                usart_interrupt_enable(uart_, USART_TDC_INT, TRUE);
            } else {
                /* 继续发送一个字节 */
                usart_data_transmit(uart_, tx_buf_[tx_read_]);
                if (++tx_read_ >= tx_size_) {
                    tx_read_ = 0;
                }
                tx_count_--;
            }
        }
    }

    /* 所有数据 bit 位发送完毕中断 */
    if (((isrflags & USART_TDC_FLAG) != RESET) && (uart_->ctrl1_bit.tdcien != RESET)) {
        if (tx_count_ == 0) {
            /* 所有数据已发送完毕，关闭发送完毕中断 */
            usart_interrupt_enable(uart_, USART_TDC_INT, FALSE);
            if (SendOver_) {
                SendOver_();
            }
        } else {
            /* 继续发送：正常情况下不进入该分支 */
            usart_data_transmit(uart_, tx_buf_[tx_read_]);
            if (++tx_read_ >= tx_size_) {
                tx_read_ = 0;
            }
            tx_count_--;
        }
    }
}

#endif /* __cplusplus */

/**
 *	 @brief PortToUart
 *	 @details 将 COM 端口映射到对应的 Uart 类实例
 *	 @param port : COM 端口枚举值
 *	 @return 指向 Uart 类实例的指针
 */

#if UART1_FIFO_EN == 1
static uint8_t s_tx1[UART1_TX_BUF_SIZE];
static uint8_t s_rx1[UART1_RX_BUF_SIZE];
static Uart g_Uart1(USART1, s_tx1, UART1_TX_BUF_SIZE, s_rx1, UART1_RX_BUF_SIZE);
#endif

#if UART3_FIFO_EN == 1
static uint8_t s_tx3[UART3_TX_BUF_SIZE];
static uint8_t s_rx3[UART3_RX_BUF_SIZE];
static Uart g_Uart3(USART3, s_tx3, UART3_TX_BUF_SIZE, s_rx3, UART3_RX_BUF_SIZE);
#endif

static inline Uart *PortToUart(COM_PORT_E port) {
    switch (port) {
    case COM1:
#if UART1_FIFO_EN == 1
        return &g_Uart1;
#else
        return nullptr;
#endif
    case COM3:
#if UART3_FIFO_EN == 1
        return &g_Uart3;
#else
        return nullptr;
#endif
    default:
        return nullptr;
    }
}

void esp12_uart_init(uint32_t baudrate) {
    gpio_init_type gpio_init_struct;

    /* 开启 UART 和 GPIO 时钟 */
    crm_periph_clock_enable(ESP12_UART_CRM_CLK, TRUE);
    crm_periph_clock_enable(ESP12_UART_TX_GPIO_CRM_CLK, TRUE);
    crm_periph_clock_enable(ESP12_UART_RX_GPIO_CRM_CLK, TRUE);

    gpio_default_para_init(&gpio_init_struct);

    /* 配置 UART 发送引脚 */
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_pins = ESP12_UART_TX_PIN;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(ESP12_UART_TX_GPIO, &gpio_init_struct);

    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_pins = ESP12_UART_RX_PIN;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(ESP12_UART_RX_GPIO, &gpio_init_struct);

    gpio_pin_mux_config(ESP12_UART_TX_GPIO, ESP12_UART_TX_PIN_SOURCE, ESP12_UART_TX_PIN_MUX_NUM);
    gpio_pin_mux_config(ESP12_UART_RX_GPIO, ESP12_UART_RX_PIN_SOURCE, ESP12_UART_RX_PIN_MUX_NUM);
    /* 配置 UART 接收引脚 */
    nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
    nvic_irq_enable(USART3_IRQn, 1, 1);

    /* 使用类实例进行统一管理 */
    g_Uart3.begin(baudrate);
}

/**
 * @brief  初始化 UART 打印功能
 * @param  baudrate: UART 波特率
 * @retval none
 */
void uart_print_init(uint32_t baudrate) {
    gpio_init_type gpio_init_struct;

#if defined(__GNUC__) && !defined(__clang__)
    setvbuf(stdout, NULL, _IONBF, 0);
#endif

    /* 开启 UART 和 GPIO 时钟 */
    crm_periph_clock_enable(PRINT_UART_CRM_CLK, TRUE);
    crm_periph_clock_enable(PRINT_UART_TX_GPIO_CRM_CLK, TRUE);

    gpio_default_para_init(&gpio_init_struct);

    /* 配置 UART 发送引脚 */
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_pins = PRINT_UART_TX_PIN;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(PRINT_UART_TX_GPIO, &gpio_init_struct);

    ///
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_pins = PRINT_UART_RX_PIN;
    gpio_init_struct.gpio_pull = GPIO_PULL_UP;
    gpio_init(PRINT_UART_RX_GPIO, &gpio_init_struct);

    gpio_pin_mux_config(PRINT_UART_TX_GPIO, PRINT_UART_TX_PIN_SOURCE, PRINT_UART_TX_PIN_MUX_NUM);
    gpio_pin_mux_config(PRINT_UART_RX_GPIO, PRINT_UART_RX_PIN_SOURCE, PRINT_UART_RX_PIN_MUX_NUM);
    /* 配置 UART 接收引脚 */
    nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
    nvic_irq_enable(USART1_IRQn, 0, 0);
    ///

    // gpio_pin_mux_config(PRINT_UART_TX_GPIO, PRINT_UART_TX_PIN_SOURCE, PRINT_UART_TX_PIN_MUX_NUM);

    g_Uart1.begin(baudrate);
}

/**
 * @brief  向串口发送一组数据
 * @param  _ucPort: 端口号(COM1 - COM8)
 * @param  _ucaBuf: 待发送的数据缓冲区
 * @param  _usLen : 数据长度
 * @retval none
 */
void comSendBuf(COM_PORT_E _ucPort, uint8_t *_ucaBuf, uint16_t _usLen) {
    Uart *uart = PortToUart(_ucPort);
    if (!uart)
        return;
    uart->sendBuf(_ucaBuf, _usLen);
}

/**
 * @brief  向串口发送1个字节
 * @param  _ucPort: 端口号(COM1 - COM8)
 * @param  _ucByte: 待发送的数据
 * @retval none
 */
void comSendChar(COM_PORT_E _ucPort, uint8_t _ucByte) {
    Uart *uart = PortToUart(_ucPort);
    if (!uart)
        return;
    uart->sendChar(_ucByte);
}

/**
 * @brief  从接收缓冲区读取1字节，非阻塞。无论有无数据均立即返回。
 * @param  _ucPort: 端口号(COM1 - COM8)
 * @param  _pByte: 接收到的数据存放在这个地址
 * @retval 0 表示无数据, 1 表示读取到有效字节
 */
uint8_t comGetChar(COM_PORT_E _ucPort, uint8_t *_pByte) {
    Uart *uart = PortToUart(_ucPort);
    if (!uart)
        return 0;
    return uart->getChar(_pByte);
}

/**
 * @brief  清零串口发送缓冲区
 * @param  _ucPort: 端口号(COM1 - COM8)
 * @retval none
 */
void comClearTxFifo(COM_PORT_E _ucPort) {
    Uart *uart = PortToUart(_ucPort);
    if (!uart)
        return;
    uart->clearTx();
}

/**
 * @brief  清零串口接收缓冲区
 * @param  _ucPort: 端口号(COM1 - COM8)
 * @retval none
 */
void comClearRxFifo(COM_PORT_E _ucPort) {
    Uart *uart = PortToUart(_ucPort);
    if (!uart)
        return;
    uart->clearRx();
}

/* 如果是RS485通信，请按如下格式编写函数， 我们仅举了 USART3作为RS485的例子 */

/**
 * @brief  判断发送缓冲区是否为空。
 * @param  _ucPort: 端口号(COM1 - COM8)
 * @retval 1为空。0为不空。
 */
uint8_t UartTxEmpty(COM_PORT_E _ucPort) {
    Uart *uart = PortToUart(_ucPort);
    if (!uart)
        return 0;
    return uart->txEmpty();
}

/**
 * @brief  供中断服务程序调用，通用串口中断处理函数
 * @param  none
 * @retval none
 */
extern "C" void USART3_IRQHandler(void) {
    g_Uart3.onIRQ();
}

extern "C" void USART1_IRQHandler(void) {
#if UART1_FIFO_EN == 1
    g_Uart1.onIRQ();
#endif
}
