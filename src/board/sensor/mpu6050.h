#pragma once

#include <stdint.h>

// I2C 事务超时（匹配现有样式）
#ifndef MPU6050_TIMEOUT
#define MPU6050_TIMEOUT 0xFFFFFFF
#endif

// MPU6050 7-bit 地址: 0x68 (AD0=0), 0x69 (AD0=1)
// 库使用 8-bit 写入地址调用
#define MPU6050_I2C_ADDR_WRITE_68 0xD0
#define MPU6050_I2C_ADDR_WRITE_69 0xD2

// GPIO 占位符（保留；未连接/配置）
// INT 引脚（MPU6050 中断输出）
#define MPU6050_INT_GPIO_CLK 0
#define MPU6050_INT_GPIO_PORT 0
#define MPU6050_INT_GPIO_PIN 0
#define MPU6050_INT_GPIO_SRC 0
#define MPU6050_INT_GPIO_MUX 0

// AD0 引脚（地址选择）— 如果需要，外部设置为高电平
#define MPU6050_AD0_GPIO_CLK 0
#define MPU6050_AD0_GPIO_PORT 0
#define MPU6050_AD0_GPIO_PIN 0

class MPU6050 {
  public:
    static MPU6050 &GetInstance() {
        static MPU6050 instance;
        return instance;
    }
    MPU6050(const MPU6050 &) = delete;
    MPU6050 &operator=(const MPU6050 &) = delete;

    // 初始化 MPU6050 传感器
    // 如果 ad0_high=true 使用地址 0x69
    bool init(bool ad0_high = false);

    // 基本寄存器访问
    bool writeReg(uint8_t reg, uint8_t value);                    // 写入寄存器
    bool readReg(uint8_t reg, uint8_t &value);                    // 读取寄存器
    bool readRegs(uint8_t start_reg, uint8_t *buf, uint16_t len); // 读取多个寄存器

    // 身份验证
    uint8_t whoAmI(); // 读取设备 ID

    // 原始读数
    bool readAccelRaw(int16_t &ax, int16_t &ay, int16_t &az); // 读取加速度原始值
    bool readGyroRaw(int16_t &gx, int16_t &gy, int16_t &gz);  // 读取陀螺仪原始值
    bool readTemperatureRaw(int16_t &t);                      // 读取温度原始值

    // 转换读数
    bool readAccel(float &ax_g, float &ay_g, float &az_g);      // 读取加速度（单位：g）
    bool readGyro(float &gx_dps, float &gy_dps, float &gz_dps); // 读取陀螺仪（单位：度/秒）
    bool readTemperatureC(float &temp_c);                       // 读取温度（单位：摄氏度）

  private:
    MPU6050() = default;
    ~MPU6050() = default;

    // 8-bit 写入地址，由 i2c_application 助手使用
    uint8_t dev_addr_write_ = MPU6050_I2C_ADDR_WRITE_68;

    // 寄存器映射（部分）
    static constexpr uint8_t REG_SMPLRT_DIV = 0x19;
    static constexpr uint8_t REG_CONFIG = 0x1A;
    static constexpr uint8_t REG_GYRO_CONFIG = 0x1B;
    static constexpr uint8_t REG_ACCEL_CONFIG = 0x1C;
    static constexpr uint8_t REG_INT_PIN_CFG = 0x37;
    static constexpr uint8_t REG_INT_ENABLE = 0x38;
    static constexpr uint8_t REG_ACCEL_XOUT_H = 0x3B;
    static constexpr uint8_t REG_TEMP_OUT_H = 0x41;
    static constexpr uint8_t REG_GYRO_XOUT_H = 0x43;
    static constexpr uint8_t REG_PWR_MGMT_1 = 0x6B;
    static constexpr uint8_t REG_WHO_AM_I = 0x75;
};

/*
使用示例（确保在板级初始化期间调用 iic_init()）：

    auto &mpu = MPU6050::GetInstance();
    if (mpu.init()) {
        float ax, ay, az, gx, gy, gz, t;
        mpu.readAccel(ax, ay, az);
        mpu.readGyro(gx, gy, gz);
        mpu.readTemperatureC(t);
    }

*/