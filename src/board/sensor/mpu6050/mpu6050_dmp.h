#ifndef BSP_MPU6050_DMP_H
#define BSP_MPU6050_DMP_H

#include <stdint.h>

#define MPU6050_DMP_OK             0
#define MPU6050_DMP_NOT_READY      1
#define MPU6050_DMP_ERR_FIFO      -1
#define MPU6050_DMP_ERR_QUAT      -2
#define MPU6050_DMP_ERR_STATUS    -3
#define MPU6050_DMP_ERR_INIT      -4
#define MPU6050_DMP_ERR_CONFIG    -5
#define MPU6050_DMP_ERR_FEATURE   -6
#define MPU6050_DMP_ERR_ENABLE    -7
#define MPU6050_DMP_ERR_FIFO_RESET -8

typedef struct {
    float pitch;//qian and hou
    float roll;//left and right
    float yaw;//
    long quat[4];
    short gyro[3];
    short accel[3];
    unsigned long timestamp_ms;
} mpu6050_dmp_data_t;

int mpu6050_dmp_init(void);
int mpu6050_dmp_read(mpu6050_dmp_data_t *out);
int mpu6050_dmp_calibrate(void);
void mpu6050_dmp_clear_calibration(void);

#endif /* BSP_MPU6050_DMP_H */
