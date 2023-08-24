/*
 * mpu6050.h
 *
 *  Created on: Aug 21, 2023
 *      Author: uvsaradhi
 */

#include <stm32f4xx_hal.h>
#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_
#define INT_PIN_CFG 0x37
#define INT_ENABLE 0x38
#define MPU_i2c_ADD (0x68<<1)
#define GYRO_CONFG 0x1B
#define PWR_MGMT_1 0x6B
#define ACC_CONFG 0x1C
#define ACC_XOUT_H 0x3B
#define ACC_XOUT_L 0x3C
#define ACC_YOUT_H 0x3D
#define ACC_YOUT_L 0x3E
#define ACC_ZOUT_H 0x3F
#define ACC_ZOUT_L 0x40


#endif /* INC_MPU6050_H_ */
