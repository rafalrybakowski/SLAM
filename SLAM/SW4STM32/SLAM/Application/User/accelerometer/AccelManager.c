/*
 * AccelManager.c
 *
 *  Created on: May 28, 2016
 *      Author: Rafal
 */

#include "stm32f4xx_hal.h"

uint16_t accelAddress = 0b00110011;

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