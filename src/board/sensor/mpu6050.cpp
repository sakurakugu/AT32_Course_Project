/** @addtogroup AT32F403A_periph_examples
 * @{
 */

#include "mpu6050.h"
#include <stdio.h>
#include "delay.h"
#include "eeprom.h"

#define I2Cx_SPEED 100000              // I2C 速度
#define I2Cx_PORT I2C2                 // I2C 端口
#define I2Cx_CLK CRM_I2C2_PERIPH_CLOCK // I2C 时钟

#define I2Cx_SCL_PIN GPIO_PINS_10
#define I2Cx_SCL_GPIO_PORT GPIOB
#define I2Cx_SCL_GPIO_CLK CRM_GPIOB_PERIPH_CLOCK // I2C SCL 引脚时钟

#define I2Cx_SDA_PIN GPIO_PINS_11
#define I2Cx_SDA_GPIO_PORT GPIOB
#define I2Cx_SDA_GPIO_CLK CRM_GPIOB_PERIPH_CLOCK // I2C SDA 引脚时钟

#define I2Cx_DMA_CLK CRM_DMA1_PERIPH_CLOCK  // I2C DMA 时钟
#define I2Cx_DMA_TX_CHANNEL DMA1_CHANNEL4   // I2C DMA 发送通道
#define I2Cx_DMA_TX_IRQn DMA1_Channel4_IRQn // I2C DMA 发送通道中断

#define I2Cx_DMA_RX_CHANNEL DMA1_CHANNEL5   // I2C DMA 接收通道
#define I2Cx_DMA_RX_IRQn DMA1_Channel5_IRQn // I2C DMA 接收通道中断

#define I2Cx_EVT_IRQn I2C2_EVT_IRQn // I2C 事件中断
#define I2Cx_ERR_IRQn I2C2_ERR_IRQn // I2C 错误中断

extern i2c_handle_type hi2cx; // I2C 句柄

#define USING_IIC_INT_DMA 0 // 是否使用I2C DMA 中断
#define USING_IIC_POLLING 1 // 是否使用I2C 轮询

static void error_handler(uint32_t error_code);

void i2c_lowlevel_init(i2c_handle_type *hi2c); // I2C 低电平初始化函数

/**
 * @brief  error handler program
 * @param  i2c_status
 * @retval none
 */
static void error_handler(uint32_t error_code) // I2C 错误处理函数
{

    printf("I2C error code: %d\n", error_code);
}

#if 0
/**
  * @brief  initializes peripherals used by the i2c.
  * @param  none
  * @retval none
  */
void i2c_lowlevel_init(i2c_handle_type* hi2c) //I2C 低电平初始化函数
{
  gpio_init_type gpio_initstructure;

  if(hi2c->i2cx == I2Cx_PORT)
  {
    /* i2c periph clock enable */
    crm_periph_clock_enable(I2Cx_CLK, TRUE);
    crm_periph_clock_enable(I2Cx_SCL_GPIO_CLK, TRUE);
    crm_periph_clock_enable(I2Cx_SDA_GPIO_CLK, TRUE);

    /* gpio configuration */
    gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_OPEN_DRAIN;
    gpio_initstructure.gpio_pull           = GPIO_PULL_UP;
    gpio_initstructure.gpio_mode           = GPIO_MODE_MUX;
    gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;

    /* configure i2c pins: scl */
    gpio_initstructure.gpio_pins = I2Cx_SCL_PIN;
    gpio_init(I2Cx_SCL_GPIO_PORT, &gpio_initstructure);

    /* configure i2c pins: sda */
    gpio_initstructure.gpio_pins = I2Cx_SDA_PIN;
    gpio_init(I2Cx_SDA_GPIO_PORT, &gpio_initstructure);
#if USING_IIC_INT_DMA
    /* configure and enable i2c dma channel interrupt */
    nvic_irq_enable(I2Cx_DMA_TX_IRQn, 0, 0);
    nvic_irq_enable(I2Cx_DMA_RX_IRQn, 0, 0);

    /* configure and enable i2c interrupt */
    nvic_irq_enable(I2Cx_EVT_IRQn, 0, 0);
    nvic_irq_enable(I2Cx_ERR_IRQn, 0, 0);

    /* i2c dma tx and rx channels configuration */
    /* enable the dma clock */
    crm_periph_clock_enable(I2Cx_DMA_CLK, TRUE);

    /* i2c dma channel configuration */
    dma_reset(hi2c->dma_tx_channel);
    dma_reset(hi2c->dma_rx_channel);

    hi2c->dma_tx_channel = I2Cx_DMA_TX_CHANNEL;
    hi2c->dma_rx_channel = I2Cx_DMA_RX_CHANNEL;

    dma_default_para_init(&hi2c->dma_init_struct);
    hi2c->dma_init_struct.peripheral_inc_enable    = FALSE;
    hi2c->dma_init_struct.memory_inc_enable        = TRUE;
    hi2c->dma_init_struct.peripheral_data_width    = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
    hi2c->dma_init_struct.memory_data_width        = DMA_MEMORY_DATA_WIDTH_BYTE;
    hi2c->dma_init_struct.loop_mode_enable         = FALSE;
    hi2c->dma_init_struct.priority                 = DMA_PRIORITY_LOW;
    hi2c->dma_init_struct.direction                = DMA_DIR_MEMORY_TO_PERIPHERAL;

    dma_init(hi2c->dma_tx_channel, &hi2c->dma_init_struct);
    dma_init(hi2c->dma_rx_channel, &hi2c->dma_init_struct);
#endif
    i2c_init(hi2c->i2cx, I2C_FSMODE_DUTY_2_1, I2Cx_SPEED);

    i2c_own_address1_set(hi2c->i2cx, I2C_ADDRESS_MODE_7BIT, 0xb0); //0x0b0 is the own address,useless
  }
}
#endif

uint8_t mpu6050WrReg(uint8_t regAddr, uint8_t data) // 写入寄存器
{
    i2c_status_type i2c_status;
    i2c_bus_lock();
    i2c_status = i2c_memory_write(&hi2cx, I2C_MEM_ADDR_WIDIH_8, MPU6050_ADDRESS, regAddr, &data, 1, I2C_TIMEOUT);
    i2c_bus_unlock();
    if (i2c_status != I2C_OK) {
        error_handler(i2c_status);
        return 1;
    }
    return 0;
}
uint8_t mpuRdByte(uint8_t regAddr) // 读取寄存器
{
    uint8_t res = 0;
    i2c_status_type i2c_status;
    i2c_bus_lock();
    i2c_status = i2c_memory_read(&hi2cx, I2C_MEM_ADDR_WIDIH_8, MPU6050_ADDRESS, regAddr, &res, 1, I2C_TIMEOUT);
    i2c_bus_unlock();
    if (i2c_status != I2C_OK) {
        error_handler(i2c_status);
        return 0;
    }
    return res;
}

uint8_t mpuWrLen(uint8_t regAddr, uint8_t len, uint8_t *buf)
{
    i2c_status_type i2c_status;
    i2c_bus_lock();
    i2c_status = i2c_memory_write(&hi2cx, I2C_MEM_ADDR_WIDIH_8, MPU6050_ADDRESS, regAddr, buf, len, I2C_TIMEOUT);
    i2c_bus_unlock();
    if (i2c_status != I2C_OK) {
        error_handler(i2c_status);
        return 1;
    }
    return 0;
}

uint8_t mpuReadLen(uint8_t regAddr, uint8_t len, uint8_t *buf)
{
    i2c_status_type i2c_status;
    i2c_bus_lock();
    i2c_status = i2c_memory_read(&hi2cx, I2C_MEM_ADDR_WIDIH_8, MPU6050_ADDRESS, regAddr, buf, len, I2C_TIMEOUT);
    i2c_bus_unlock();
    if (i2c_status != I2C_OK) {
        error_handler(i2c_status);
        return 1;
    }
    return 0;
}
/**********************************************
MPU_Set_LPF
*/

uint8_t mpu6050SetLPF(u16 lpf) // 设置低通滤波器 ，lpf为低通滤波器截止频率，单位为Hz
{
    uint8_t data = 0;

    if (lpf >= 188)
        data = 1;
    else if (lpf >= 98)
        data = 2;
    else if (lpf >= 42)
        data = 3;
    else if (lpf >= 20)
        data = 4;
    else if (lpf >= 10)
        data = 5;
    else
        data = 6;
    return mpu6050WrReg(MPU_CFG_REG, data);
}

uint8_t mpuGetAcc(short *ax, short *ay, short *az) // 获取加速度值
{
    uint8_t buf[6], res;
    res = mpuReadLen(MPU6050_ACCEL_XOUT_H, 6, buf);
    if (res == 0) {
        *ax = ((u16)buf[0] << 8) | buf[1];
        *ay = ((u16)buf[2] << 8) | buf[3];
        *az = ((u16)buf[4] << 8) | buf[5];
    }
    return res;
}

uint8_t mpuGetGyro(short *gx, short *gy, short *gz) // 获取陀螺仪值
{
    uint8_t buf[6], res;

    res = mpuReadLen(MPU6050_GYRO_XOUT_H, 6, buf);
    if (res == 0) {
        *gx = ((u16)buf[0] << 8) | buf[1];
        *gy = ((u16)buf[2] << 8) | buf[3];
        *gz = ((u16)buf[4] << 8) | buf[5];
    }
    return res;
}

short MmpuGetTemp(void) // 获取温度值
{
    uint8_t buf[2];
    short raw;
    float temp;

    mpuReadLen(MPU6050_TEMP_OUT_H, 2, buf);
    raw = ((u16)buf[0] << 8) | buf[1];
    temp = 36.53 + ((double)raw) / 340;
    return temp * 100;
}

uint8_t mpuSetRate(u16 rate) // 设置采样率 ，rate为采样率，单位为Hz
{
    uint8_t data;
    if (rate > 1000)
        rate = 1000;
    if (rate < 4)
        rate = 4;
    data = 1000 / rate - 1;
    data = mpu6050WrReg(MPU_SAMPLE_RATE_REG, data); //?????????
    return mpu6050SetLPF(rate / 2);                 //????LPF???????
}

/*
0:200dps 1: 500dps; 3: 2000dps
*/
uint8_t mpuSetGyroFsr(uint8_t fsr) // 设置陀螺仪满量程范围 ，fsr为满量程范围，单位为dps
{
    return mpu6050WrReg(MPU6050_GYRO_CONFIG, fsr << 3); //??????????
}

uint8_t mpuSetAccFsr(uint8_t fsr) // 设置加速度器满量程范围 ，fsr为满量程范围，单位为g
{
    return mpu6050WrReg(MPU6050_ACCEL_CONFIG, fsr << 3); //?????????????
}

uint8_t mpu6050Init(void) // 初始化 MPU6050
{
    uint8_t res;
    mpu6050WrReg(MPU6050_PWR_MGMT_1, 0X80); // reset 6050
    delay_ms(100);
    mpu6050WrReg(MPU6050_PWR_MGMT_1, 0X00); // wakeup 6050

    mpuSetGyroFsr(3); // Gyro:+-2000dps
    mpuSetAccFsr(0);  // Acc：+-2g
    mpuSetRate(50);   // data-rate:50Hz

    mpu6050WrReg(MPU6050_INT_EN_REG, 0X00);    // disable the interrupt
    mpu6050WrReg(MPU6050_USER_CTRL_REG, 0X00); // diable I2C master mode
    mpu6050WrReg(MPU6050_FIFO_EN_REG, 0X00);   // disable FIFO
    mpu6050WrReg(MPU6050_INTBP_CFG_REG, 0X80); // INT Low-- not used

    res = mpuRdByte(MPU6050_DEVICE_ID_REG);
    if (res == (MPU6050_ADDRESS >> 1)) // device ID is correct
    {
        mpu6050WrReg(MPU6050_PWR_MGMT_1, 0X01); // CLKSEL,PLL X is the ref
        mpu6050WrReg(MPU6050_PWR_MGMT_2, 0X00); // enable Gyro and acc
        mpuSetRate(50);                         // set rate is 50Hz
    } else
        return 1; // init failed
    return 0;     // init success
    /*
        mpu6050WrReg(MPU6050_PWR_MGMT_1, 0x01);//
        mpu6050WrReg(MPU6050_PWR_MGMT_2, 0x00);//
        mpu6050WrReg(MPU6050_SMPLRT_DIV, 0x09);//
        mpu6050WrReg(MPU6050_CONFIG, 0x06);//
        mpu6050WrReg(MPU6050_GYRO_CONFIG, 0x18);//
        mpu6050WrReg(MPU6050_ACCEL_CONFIG, 0x18);//
    */
}
void mpu6050Test(void) {
    int16_t ax, ay, az, gx, gy, gz;
    mpuGetAcc(&ax, &ay, &az);
    mpuGetGyro(&gx, &gy, &gz);
    printf("Ax:%8d; Ay:%8d; Az:%8d\r\n", ax, ay, az);
    printf("Gx:%8d; Gy:%8d; Gz:%8d\r\n", gx, gy, gz);
}
