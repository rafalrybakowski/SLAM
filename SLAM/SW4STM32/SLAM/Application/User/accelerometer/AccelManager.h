/*
 * AccelManager.h
 *
 *  Created on: May 28, 2016
 *      Author: Rafal
 */

#ifndef APPLICATION_USER_ACCELEROMETER_ACCELMANAGER_H_
#define APPLICATION_USER_ACCELEROMETER_ACCELMANAGER_H_

void accelSetup(I2C_HandleTypeDef *hi2c);
void getAccelValues(I2C_HandleTypeDef *hi2c, int16_t *response);
void accelCalibrate(I2C_HandleTypeDef *hi2c);

#endif /* APPLICATION_USER_ACCELEROMETER_ACCELMANAGER_H_ */
