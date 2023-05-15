/*
 * 		mpu6050.h
 *
 *  	Created on: May 13, 2023
 *      Author: Satvik Agrawal
 */
/*-----------------------------------------------------------------------------------------------------------------*/

#include <mpu6050.h>
#include <main.h>
#include <stdio.h>

/* MPU6050 INIT FUNCTION DEF */

int _write(int file, char *ptr, int len){
		int i = 0;
		for (i = 0; i < len; i++)
			ITM_SendChar((*ptr++));
		return len;
	}


uint8_t MPU6050_Init( MPU6050 *dev, I2C_HandleTypeDef *i2cHandle){

	dev->i2cHandle     = i2cHandle;       //Initialise which I2C line is being used

	dev->accel_data[0] = 0.0f;            //Initialise all measurement data values
	dev->accel_data[1] = 0.0f;
	dev->accel_data[2] = 0.0f;

	dev->gyro_data[0]  = 0.0f;
	dev->gyro_data[1]  = 0.0f;
	dev->gyro_data[2]  = 0.0f;

	int errNum = 0;
	HAL_StatusTypeDef status;
	uint8_t initData;					 //Checking if Sensor is connected

	status = MPU6050_ReadRegister( dev, MPU6050_DEVICE_ID, &initData);

	if (status != HAL_OK){
		printf("Sensor is not connected. \n");
		errNum++;
	}
	else{
		if (initData != MPU6050_DEVICE_ID){
			printf("Sensor connected is not MPU6050! \n");
			errNum++;
		}
	}

	initData = 0;						 //Take device out of Sleep Mode

	status = MPU6050_WriteRegister(dev, MPU6050_PWR_MGMT1, &initData);

	if (status != HAL_OK){
		printf("Unable to exit sleep mode. \n\r");
		errNum++;
	}

	return errNum;
}




/* MEASUREMENT READINGS FUNCTIONS DEF */

HAL_StatusTypeDef MPU6050_ReadAccelData (MPU6050 *dev) {

	uint8_t readData[6];

	HAL_StatusTypeDef status = MPU6050_ReadRegisters(dev, MPU6050_ACCEL_XOUT_H, readData, 6);

	int16_t accRawData[3];

	accRawData[0] = ((readData[0] << 8) | readData[1]);
	accRawData[1] = ((readData[2] << 8) | readData[3]);
	accRawData[2] = ((readData[4] << 8) | readData[5]);

	dev->accel_data[0] = accRawData[0] / 16384.0;
	dev->accel_data[1] = accRawData[1] / 16384.0;
	dev->accel_data[2] = accRawData[2] / 16384.0;

	return status;

}

HAL_StatusTypeDef MPU6050_ReadGyroData  (MPU6050 *dev) {

	uint8_t readData[6];

	HAL_StatusTypeDef status = MPU6050_ReadRegisters(dev, MPU6050_GYRO_XOUT_H, readData, 6);

	int16_t gyroRawData[3];

	gyroRawData[0] = ((readData[0] << 8) | readData[1]);
	gyroRawData[1] = ((readData[2] << 8) | readData[3]);
	gyroRawData[2] = ((readData[4] << 8) | readData[5]);

	dev->gyro_data[0] = gyroRawData[0] / 131.0;
	dev->gyro_data[1] = gyroRawData[1] / 131.0;
	dev->gyro_data[2] = gyroRawData[2] / 131.0;

	return status;

}






/* BASE FUNCTIONS DEF */

HAL_StatusTypeDef MPU6050_ReadRegister( MPU6050 *dev, uint8_t reg, uint8_t *data) {

	return HAL_I2C_Mem_Read(dev->i2cHandle, MPU6050_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);

}

HAL_StatusTypeDef MPU6050_ReadRegisters( MPU6050 *dev, uint8_t reg, uint8_t *data, uint8_t length) {

	return HAL_I2C_Mem_Read(dev->i2cHandle, MPU6050_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, length, HAL_MAX_DELAY);

}

HAL_StatusTypeDef MPU6050_WriteRegister( MPU6050 *dev, uint8_t reg, uint8_t *data) {

	return HAL_I2C_Mem_Write(dev->i2cHandle, MPU6050_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);

}
