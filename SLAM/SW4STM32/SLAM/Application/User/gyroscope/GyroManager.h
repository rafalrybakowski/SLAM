/*
 * GyroManager.h
 *
 *  Created on: May 3, 2016
 *      Author: Rafal
 */

#include "stm32f4xx_hal.h"

#ifndef APPLICATION_USER_GYROMANAGER_H_
#define APPLICATION_USER_GYROMANAGER_H_

HAL_SPI_StateTypeDef gyroWhoAmI(SPI_HandleTypeDef *hspi, uint8_t *response);
HAL_SPI_StateTypeDef gyroSetup(SPI_HandleTypeDef *hspi, uint8_t *response);

void gyroCalibrate(SPI_HandleTypeDef *hspi);
void getGyroValues(SPI_HandleTypeDef *hspi, int16_t *response);

#endif /* APPLICATION_USER_GYROMANAGER_H_ */
