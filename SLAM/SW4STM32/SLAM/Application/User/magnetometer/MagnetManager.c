/*
 * MagnetManager.c
 *
 *  Created on: May 28, 2016
 *      Author: Rafal
 */

#include "stm32f4xx_hal.h"

uint16_t magnetAddress = 0b00111101;

void magnetSetup(I2C_HandleTypeDef *hi2c) {

	uint8_t accelSendBuffer[] = { 0b00000010, 0b00000000 };

	while (HAL_I2C_Master_Transmit(hi2c, (uint16_t) magnetAddress, (uint8_t*) accelSendBuffer, (uint16_t) 2, (uint32_t) 1000) != HAL_OK) {
		if (HAL_I2C_GetError(hi2c) != HAL_I2C_ERROR_AF) {
		}
	}
	while (HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY) {
	}
}

void magnetRead(I2C_HandleTypeDef *hi2c, uint8_t *response) {

	uint8_t accelSendBuffer[] = { 0b10000011 };

	while (HAL_I2C_Master_Transmit(hi2c, (uint16_t) magnetAddress, (uint8_t*) accelSendBuffer, (uint16_t) 1, (uint32_t) 1000) != HAL_OK) {
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