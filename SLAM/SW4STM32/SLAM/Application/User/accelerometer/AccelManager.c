/*
 * AccelManager.c
 *
 *  Created on: May 28, 2016
 *      Author: Rafal
 */

#include "stm32f4xx_hal.h"

static uint16_t accelAddress = 0b00110011;

static int sensorZero[3];

void accelSetup(I2C_HandleTypeDef *hi2c) {

	uint8_t accelSendBuffer[] = { 0b00100000, 0b10010111 };

	while (HAL_I2C_Master_Transmit(hi2c, (uint16_t) accelAddress, (uint8_t*) accelSendBuffer, (uint16_t) 2, (uint32_t) 1000) != HAL_OK) {
		if (HAL_I2C_GetError(hi2c) != HAL_I2C_ERROR_AF) {
		}
	}
	while (HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY) {
	}
}

void accelRead(I2C_HandleTypeDef *hi2c, uint8_t *response) {

	uint8_t accelSendBuffer[] = { 0b10101000 };

	while (HAL_I2C_Master_Transmit(hi2c, (uint16_t) accelAddress, (uint8_t*) accelSendBuffer, (uint16_t) 1, (uint32_t) 1000) != HAL_OK) {
		if (HAL_I2C_GetError(hi2c) != HAL_I2C_ERROR_AF) {
		}
	}
	while (HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY) {
	}

	while (HAL_I2C_Master_Receive(hi2c, (uint16_t) accelAddress, (uint8_t *) response, (uint16_t) 6, (uint32_t) 1000) != HAL_OK) {
		if (HAL_I2C_GetError(hi2c) != HAL_I2C_ERROR_AF) {
		}
	}
	while (HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY) {
	}
}

void getAccelValues(I2C_HandleTypeDef *hi2c, int16_t *response) {

	int readingResolution = 5;

	uint8_t readings[6] = { 0, 0, 0, 0, 0, 0 };

	long xAccel = 0;
	long yAccel = 0;
	long zAccel = 0;

	for (int i = 0; i < readingResolution; i++) {
		accelRead(hi2c, readings);
		xAccel += (int16_t)(readings[0] + (readings[1] << 8));
		yAccel += (int16_t)(readings[2] + (readings[3] << 8));
		zAccel += (int16_t)(readings[4] + (readings[5] << 8));
	}

	response[0] = (xAccel / readingResolution) - sensorZero[0];
	response[1] = (yAccel / readingResolution) - sensorZero[1];
	response[2] = (zAccel / readingResolution) - sensorZero[2];
}

void accelCalibrate(I2C_HandleTypeDef *hi2c) {

	int calibrationResolution = 25;

	uint8_t readings[6] = { 0, 0, 0, 0, 0, 0 };

	long xAccel = 0;
	long yAccel = 0;
	long zAccel = 0;

	for (int i = 0; i < calibrationResolution; i++) {
		accelRead(hi2c, readings);
		xAccel += (int16_t)(readings[0] + (readings[1] << 8));
		yAccel += (int16_t)(readings[2] + (readings[3] << 8));
		zAccel += (int16_t)(readings[4] + (readings[5] << 8)); // Set zero sensor values
	}

	sensorZero[0] = xAccel / calibrationResolution;
	sensorZero[1] = yAccel / calibrationResolution;
	sensorZero[2] = (zAccel / calibrationResolution) - 16000;
}
