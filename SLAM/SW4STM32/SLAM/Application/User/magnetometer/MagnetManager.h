/*
 * MagnetManager.h
 *
 *  Created on: May 28, 2016
 *      Author: Rafal
 */

#ifndef APPLICATION_USER_MAGNETOMETER_MAGNETMANAGER_H_
#define APPLICATION_USER_MAGNETOMETER_MAGNETMANAGER_H_

void magnetSetup(I2C_HandleTypeDef *hi2c);
void getMagnetValues(I2C_HandleTypeDef *hi2c, int16_t *response);

#endif /* APPLICATION_USER_MAGNETOMETER_MAGNETMANAGER_H_ */
