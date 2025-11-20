#pragma once

#include <stdint.h>
#include "i2c_application.h"

#define MPU_SELF_TESTX_REG		0X0D	//X
#define MPU_SELF_TESTY_REG		0X0E	//Y
#define MPU_SELF_TESTZ_REG		0X0F	//Z
#define MPU_SELF_TESTA_REG		0X10	//A
#define MPU_SAMPLE_RATE_REG		0X19	//采样率
#define MPU_CFG_REG						0X1A	//配置寄存器

#define	MPU6050_SMPLRT_DIV		0x19 //采样率分频寄存器
#define	MPU6050_CONFIG			0x1A //配置寄存器
#define	MPU6050_GYRO_CONFIG		0x1B //陀螺仪配置寄存器
#define	MPU6050_ACCEL_CONFIG	0x1C //加速度器配置寄存器
#define MPU6050_MOTION_DET_REG		0X1F	//运动检测寄存器
#define MPU6050_FIFO_EN_REG				0X23	//FIFO使能寄存器
 
#define MPU6050_I2CMST_STA_REG		0X36	//IIC主模式状态寄存器
#define MPU6050_INTBP_CFG_REG			0X37	//中断/旁路配置寄存器
#define MPU6050_INT_EN_REG				0X38	//中断使能寄存器
#define MPU6050_INT_STA_REG				0X3A	//中断状态寄存器

#define	MPU6050_ACCEL_XOUT_H	0x3B //加速度X高字节
#define	MPU6050_ACCEL_XOUT_L	0x3C //加速度X低字节
#define	MPU6050_ACCEL_YOUT_H	0x3D //加速度Y高字节
#define	MPU6050_ACCEL_YOUT_L	0x3E //加速度Y低字节
#define	MPU6050_ACCEL_ZOUT_H	0x3F //加速度Z高字节
#define	MPU6050_ACCEL_ZOUT_L	0x40 //加速度Z低字节
#define	MPU6050_TEMP_OUT_H		0x41 //温度高字节
#define	MPU6050_TEMP_OUT_L		0x42 //温度低字节
#define	MPU6050_GYRO_XOUT_H		0x43 //陀螺仪X高字节
#define	MPU6050_GYRO_XOUT_L		0x44 //陀螺仪X低字节
#define	MPU6050_GYRO_YOUT_H		0x45 //陀螺仪Y高字节
#define	MPU6050_GYRO_YOUT_L		0x46 //陀螺仪Y低字节
#define	MPU6050_GYRO_ZOUT_H		0x47 //陀螺仪Z高字节
#define	MPU6050_GYRO_ZOUT_L		0x48 //陀螺仪Z低字节

#define MPU6050_USER_CTRL_REG			0X6A	//用户控制寄存器
#define	MPU6050_PWR_MGMT_1		0x6B //电源管理寄存器1
#define	MPU6050_PWR_MGMT_2		0x6C //电源管理寄存器2
#define	MPU6050_DEVICE_ID_REG		0x75 //设备ID寄存器 

#define MPU6050_ADDRESS (0xD0) //MPU6050 地址


#ifdef __cplusplus
extern "C" {
#endif

uint8_t mpu6050GetID(void); // 获取设备 ID
void mpu6050Test(void); // 测试初始化
uint8_t mpu6050Init(void); // 初始化 MPU6050

uint8_t mpuGetAcc(short *ax, short *ay, short *az);
uint8_t mpuGetGyro(short *gx, short *gy, short *gz);
short MmpuGetTemp(void);

#ifdef __cplusplus
}
#endif



