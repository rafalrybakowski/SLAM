/*
 * GyroManager.c
 *
 *  Created on: May 3, 2016
 *      Author: Rafal
 */

#include "GyroManager.h"

static int sensorZero[3];

// sensor test
HAL_SPI_StateTypeDef gyroWhoAmI(SPI_HandleTypeDef *hspi, uint8_t *response) {

	uint8_t whoAmIRegAddr = 0b10001111;
	uint8_t output[] = { whoAmIRegAddr, 0x00 };

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_SPI_StateTypeDef state = HAL_SPI_TransmitReceive(hspi, output, response, 2, 5000);
	HAL_Delay(5);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_Delay(10);

	return state;
}

// sensor setup
HAL_SPI_StateTypeDef gyroSetup(SPI_HandleTypeDef *hspi, uint8_t *response) {

	uint8_t configRegAddr = 0b00100000;
	uint8_t setupBytes = 0b00001111;
	uint8_t output[] = { configRegAddr, setupBytes };

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_SPI_StateTypeDef state = HAL_SPI_TransmitReceive(hspi, output, response, 2, 5000);
	HAL_Delay(5);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_Delay(10);

	return state;
}

// sensor read
HAL_SPI_StateTypeDef gyroRead(SPI_HandleTypeDef *hspi, uint8_t *response) {

	uint8_t outXLow = 0b11101000;
	uint8_t output[] = { outXLow };

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_SPI_StateTypeDef state = HAL_SPI_TransmitReceive(hspi, output, response, 7, 5000);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);

	return state;
}

void getGyroValues(SPI_HandleTypeDef *hspi, int16_t *response) {

	int readingResolution = 5;

	uint8_t readings[7] = { 0, 0, 0, 0, 0, 0, 0 };

	long xRotation = 0;
	long yRotation = 0;
	long zRotation = 0;

	for (int i = 0; i < readingResolution; i++) {
		gyroRead(hspi, readings);
		xRotation += (int16_t)(readings[1] + (readings[2] << 8));
		yRotation += (int16_t)(readings[3] + (readings[4] << 8));
		zRotation += (int16_t)(readings[5] + (readings[6] << 8)); // Set zero sensor values
	}

	response[0] = (xRotation / readingResolution) - sensorZero[0];
	response[1] = (yRotation / readingResolution) - sensorZero[1];
	response[2] = (zRotation / readingResolution) - sensorZero[2];
}

void gyroCalibrate(SPI_HandleTypeDef *hspi) {

	int calibrationResolution = 5;

	uint8_t readings[7] = { 0, 0, 0, 0, 0, 0, 0 };

	long xRotation = 0;
	long yRotation = 0;
	long zRotation = 0;

	for (int i = 0; i < calibrationResolution; i++) {
		gyroRead(hspi, readings);
		xRotation += (int16_t)(readings[1] + (readings[2] << 8));
		yRotation += (int16_t)(readings[3] + (readings[4] << 8));
		zRotation += (int16_t)(readings[5] + (readings[6] << 8)); // Set zero sensor values
	}

	sensorZero[0] = xRotation / calibrationResolution;
	sensorZero[1] = yRotation / calibrationResolution;
	sensorZero[2] = zRotation / calibrationResolution;
}

