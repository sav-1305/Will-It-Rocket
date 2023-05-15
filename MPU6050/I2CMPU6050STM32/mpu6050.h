/*
 * 		mpu6050.h
 *
 *  	Created on: May 13, 2023
 *    Author: Satvik Agrawal
 */
/*-----------------------------------------------------------------------------------------------------------------*/

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include <stm32f4xx_hal.h> /* required for I2C */

/* *
 * DEFINES
 * */

#define MPU6050_I2C_ADDR       (0x68 << 1)  // Default I2C address
									     	// Altered with R/W bit
#define MPU6050_DEVICE_ID    	0x68        // Correct value of WHO_AM_I register
#define MPU6050_SMPLRT_DIV   	0x19        // To calculate sample rate
#define MPU6050_CONFIG       	0x1A		// To setup FSYNC and and LPF
#define MPU6050_GYRO_CONFIG  	0x1B
#define MPU6050_ACCEL_CONFIG 	0x1C
#define MPU6050_USER_CNTRL   	0x6A
#define MPU6050_PWR_MGMT1    	0x6B
#define MPU6050_ACCEL_XOUT_H 	0x3B
#define MPU6050_ACCEL_XOUT_L 	0x3C
#define MPU6050_ACCEL_YOUT_H 	0x3D
#define MPU6050_ACCEL_YOUT_L 	0x3E
#define MPU6050_ACCEL_ZOUT_H 	0x3F
#define MPU6050_ACCEL_ZOUT_L 	0x40
#define MPU6050_GYRO_XOUT_H     0x43
#define MPU6050_GYRO_XOUT_L     0x44
#define MPU6050_GYRO_YOUT_H     0x45
#define MPU6050_GYRO_YOUT_L     0x46
#define MPU6050_GYRO_ZOUT_H     0x47
#define MPU6050_GYRO_ZOUT_L     0x48



/* SENSOR TYPEDEF STRUCT */

typedef struct {
	/* I2C Handle init */
	I2C_HandleTypeDef *i2cHandle;

	/* Acceleration Data */
	float accel_data[3];

	/* Gyroscope Data */
	float gyro_data[3] ;
} MPU6050;


/* MPU6050 INITIALISATION FUNCTION */

 uint8_t MPU6050_Init( MPU6050 *dev, I2C_HandleTypeDef *i2cHandle);


 /* MPU6050 MEASUREMENT READINGS FUNCTIONS INIT */

 HAL_StatusTypeDef MPU6050_ReadAccelData (MPU6050 *dev);
 HAL_StatusTypeDef MPU6050_ReadGyroData  (MPU6050 *dev);


/* BASE FUNCTIONS INIT */

HAL_StatusTypeDef MPU6050_ReadRegister( MPU6050 *dev, uint8_t reg, uint8_t *data);
													//Base Function to read from a 8-bit register

HAL_StatusTypeDef MPU6050_ReadRegisters( MPU6050 *dev, uint8_t reg, uint8_t *data, uint8_t length);
													//Base Function to read from a 16-bit (or more) register

HAL_StatusTypeDef MPU6050_WriteRegister( MPU6050 *dev, uint8_t reg, uint8_t *data);
													//Base Function to write to a register

/*-----------------------------------------------------------------------------------------------------------------*/

#endif /* INC_MPU6050_H_ */
