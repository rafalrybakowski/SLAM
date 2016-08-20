/*
 * MotorManager.c
 *
 *  Created on: Aug 15, 2016
 *      Author: Rafal
 */

#include "stm32f4xx_hal.h"

void setLeftMotorOutput(float output) {

	int normalizedOutput = floor(1000 * output);
	TIM1->CCR1 = normalizedOutput;
}

void setRightMotorOutput(float output) {

	int normalizedOutput = floor(1000 * output);
	TIM1->CCR2 = normalizedOutput;
}
