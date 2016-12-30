/*
 * ReflectiveManager.c
 *
 *  Created on: Aug 15, 2016
 *      Author: Rafal
 */

#include "stm32f4xx_hal.h"

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

static uint8_t readingConfigs[] = { 0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111 };

void reflectiveRead(ADC_HandleTypeDef *hadc, uint32_t *reading) {

	for (int i = 0; i < 8; i++) {

		if (CHECK_BIT(readingConfigs[i], 0)) {
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);
		} else {
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
		}

		if (CHECK_BIT(readingConfigs[i], 1)) {
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);
		} else {
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);
		}

		if (CHECK_BIT(readingConfigs[i], 2)) {
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);
		} else {
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
		}

		if (CHECK_BIT(readingConfigs[i], 3)) {
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
		} else {
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
		}

		HAL_Delay(1);

		if (HAL_ADC_PollForConversion(hadc, 1000) == HAL_OK) {
			reading[i] = HAL_ADC_GetValue(hadc);
		}
	}

	int minimum = 10000;

	for (int i = 0; i < 8; i++) {
		if (reading[i] < minimum) {
			minimum = reading[i];
		}
	}

	for (int i = 0; i < 8; i++) {
		reading[i] -= minimum;
	}

}
