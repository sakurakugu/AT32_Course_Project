#include "mpu6050.h"

#include "i2c_application.h"

// 重用全局 I2C handle 配置在 bsp_eep_lm75.cpp
extern i2c_handle_type hi2cx;

// 本地辅助函数：合并高字节和低字节为 16 位有符号整数
static inline int16_t combine_s16(uint8_t high, uint8_t low) {
    return static_cast<int16_t>((static_cast<int16_t>(high) << 8) | low);
}

bool MPU6050::init(bool ad0_high) {
    dev_addr_write_ = ad0_high ? MPU6050_I2C_ADDR_WRITE_69 : MPU6050_I2C_ADDR_WRITE_68;

    // 唤醒设备：清除睡眠位，选择内部时钟
    if (!writeReg(REG_PWR_MGMT_1, 0x00)) {
        return false;
    }

    // 采样率 = 陀螺仪输出 / (1 + SMPLRT_DIV)
    // 当 DLPF=3 (1kHz) 时，SMPLRT_DIV=7 -> 125 Hz
    if (!writeReg(REG_SMPLRT_DIV, 0x07)) {
        return false;
    }

    // DLPF_CFG = 3 用于 ~44/42/44 Hz 加速度/陀螺仪带宽
    if (!writeReg(REG_CONFIG, 0x03)) {
        return false;
    }

    // 陀螺仪满量程 = ±250 dps (0)
    if (!writeReg(REG_GYRO_CONFIG, 0x00)) {
        return false;
    }

    // 加速度满量程 = ±2g (0)
    if (!writeReg(REG_ACCEL_CONFIG, 0x00)) {
        return false;
    }

    // 可选: 配置 INT 引脚 (保留；无布线更改)
    // writeReg(REG_INT_PIN_CFG, 0x00);
    // writeReg(REG_INT_ENABLE, 0x00);

    // 验证身份：检查 WHO_AM_I 寄存器值是否为 0x68
    uint8_t id = whoAmI();
    return (id == 0x68);
}

bool MPU6050::writeReg(uint8_t reg, uint8_t value) {
    uint8_t data = value;
    auto status = i2c_memory_write(&hi2cx, I2C_MEM_ADDR_WIDIH_8, dev_addr_write_, reg, &data, 1, MPU6050_TIMEOUT);
    return status == I2C_OK;
}

bool MPU6050::readReg(uint8_t reg, uint8_t &value) {
    auto status = i2c_memory_read(&hi2cx, I2C_MEM_ADDR_WIDIH_8, dev_addr_write_, reg, &value, 1, MPU6050_TIMEOUT);
    return status == I2C_OK;
}

bool MPU6050::readRegs(uint8_t start_reg, uint8_t *buf, uint16_t len) {
    auto status = i2c_memory_read(&hi2cx, I2C_MEM_ADDR_WIDIH_8, dev_addr_write_, start_reg, buf, len, MPU6050_TIMEOUT);
    return status == I2C_OK;
}

uint8_t MPU6050::whoAmI() {
    uint8_t v = 0xFF;
    readReg(REG_WHO_AM_I, v);
    return v;
}

bool MPU6050::readAccelRaw(int16_t &ax, int16_t &ay, int16_t &az) {
    uint8_t buf[6];
    if (!readRegs(REG_ACCEL_XOUT_H, buf, sizeof(buf)))
        return false;
    ax = combine_s16(buf[0], buf[1]);
    ay = combine_s16(buf[2], buf[3]);
    az = combine_s16(buf[4], buf[5]);
    return true;
}

bool MPU6050::readGyroRaw(int16_t &gx, int16_t &gy, int16_t &gz) {
    uint8_t buf[6];
    if (!readRegs(REG_GYRO_XOUT_H, buf, sizeof(buf)))
        return false;
    gx = combine_s16(buf[0], buf[1]);
    gy = combine_s16(buf[2], buf[3]);
    gz = combine_s16(buf[4], buf[5]);
    return true;
}

bool MPU6050::readTemperatureRaw(int16_t &t) {
    uint8_t buf[2];
    if (!readRegs(REG_TEMP_OUT_H, buf, sizeof(buf)))
        return false;
    t = combine_s16(buf[0], buf[1]);
    return true;
}

bool MPU6050::readAccel(float &ax_g, float &ay_g, float &az_g) {
    int16_t ax, ay, az;
    if (!readAccelRaw(ax, ay, az))
        return false;
    // ±2g scale: 16384 LSB/g
    ax_g = static_cast<float>(ax) / 16384.0f;
    ay_g = static_cast<float>(ay) / 16384.0f;
    az_g = static_cast<float>(az) / 16384.0f;
    return true;
}

bool MPU6050::readGyro(float &gx_dps, float &gy_dps, float &gz_dps) {
    int16_t gx, gy, gz;
    if (!readGyroRaw(gx, gy, gz))
        return false;
    // ±250 dps scale: 131 LSB/(deg/s)
    gx_dps = static_cast<float>(gx) / 131.0f;
    gy_dps = static_cast<float>(gy) / 131.0f;
    gz_dps = static_cast<float>(gz) / 131.0f;
    return true;
}

bool MPU6050::readTemperatureC(float &temp_c) {
    int16_t t_raw;
    if (!readTemperatureRaw(t_raw))
        return false;
    // Datasheet: Temp(C) = (t_raw / 340) + 36.53
    temp_c = (static_cast<float>(t_raw) / 340.0f) + 36.53f;
    return true;
}