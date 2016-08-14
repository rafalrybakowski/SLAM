/*
 * GyroManager.c
 *
 *  Created on: May 3, 2016
 *      Author: Rafal
 */

#include "GyroManager.h"

// sensor test
HAL_SPI_StateTypeDef gyroWhoAmI(SPI_HandleTypeDef *hspi, uint8_t *response) {

	uint8_t whoAmIRegAddr = 0b10001111;
	uint8_t output[] = {whoAmIRegAddr, 0x00};

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_SPI_StateTypeDef state = HAL_SPI_TransmitReceive(hspi, output, response, 2, 5000);
	HAL_Delay(5);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_Delay(100);

	return state;
}

// sensor setup
HAL_SPI_StateTypeDef gyroSetup(SPI_HandleTypeDef *hspi, uint8_t *response) {

	uint8_t configRegAddr = 0b00100000;
	uint8_t setupBytes = 0b00001111;
	uint8_t output[] = {configRegAddr, setupBytes};

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_SPI_StateTypeDef state = HAL_SPI_TransmitReceive(hspi, output, response, 2, 5000);
	HAL_Delay(5);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_Delay(100);

	return state;
}

// sensor read
HAL_SPI_StateTypeDef gyroRead(SPI_HandleTypeDef *hspi, uint8_t *response) {

	uint8_t outXLow = 0b11101000;
	uint8_t output[] = {outXLow};

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_SPI_StateTypeDef state = HAL_SPI_TransmitReceive(hspi, output, response, 7, 5000);
	HAL_Delay(5);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_Delay(10);

	return state;
}

