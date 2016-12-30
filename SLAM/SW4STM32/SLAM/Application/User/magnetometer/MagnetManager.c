/*
 * MagnetManager.c
 *
 *  Created on: May 28, 2016
 *      Author: Rafal
 */

#include "stm32f4xx_hal.h"

static uint16_t magnetAddress = 0b00111101;

static int sensorZero[3];

void magnetSetup(I2C_HandleTypeDef *hi2c) {

	uint8_t magnetSendBuffer[] = { 0b00000010, 0b00000000 };

	while (HAL_I2C_Master_Transmit(hi2c, (uint16_t) magnetAddress, (uint8_t*) magnetSendBuffer, (uint16_t) 2, (uint32_t) 1000) != HAL_OK) {
		if (HAL_I2C_GetError(hi2c) != HAL_I2C_ERROR_AF) {
		}
	}
	while (HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY) {
	}
}

void magnetRead(I2C_HandleTypeDef *hi2c, uint8_t *response) {

	uint8_t magnetSendBuffer[] = { 0b10000011 };

	while (HAL_I2C_Master_Transmit(hi2c, (uint16_t) magnetAddress, (uint8_t*) magnetSendBuffer, (uint16_t) 1, (uint32_t) 1000) != HAL_OK) {
		if (HAL_I2C_GetError(hi2c) != HAL_I2C_ERROR_AF) {
		}
	}
	while (HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY) {
	}

	while (HAL_I2C_Master_Receive(hi2c, (uint16_t) magnetAddress, (uint8_t *) response, (uint16_t) 6, (uint32_t) 1000) != HAL_OK) {
		if (HAL_I2C_GetError(hi2c) != HAL_I2C_ERROR_AF) {
		}
	}
	while (HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY) {
	}
}

void getMagnetValues(I2C_HandleTypeDef *hi2c, int16_t *response) {

	int readingResolution = 5;

	uint8_t readings[6] = { 0, 0, 0, 0, 0, 0 };

	long xMagnet = 0;
	long yMagnet = 0;
	long zMagnet = 0;

	for (int i = 0; i < readingResolution; i++) {
		magnetRead(hi2c, readings);
		xMagnet += (int16_t)(readings[0] + (readings[1] << 8));
		yMagnet += (int16_t)(readings[2] + (readings[3] << 8));
		zMagnet += (int16_t)(readings[4] + (readings[5] << 8));
	}

	response[0] = (xMagnet / readingResolution);
	response[1] = (yMagnet / readingResolution);
	response[2] = (zMagnet / readingResolution);
}
