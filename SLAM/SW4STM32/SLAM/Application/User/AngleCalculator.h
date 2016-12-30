/*
 * AngleCalculator.h
 *
 *  Created on: Sep 12, 2016
 *      Author: Rafal
 */

#ifndef APPLICATION_USER_ANGLECALCULATOR_H_
#define APPLICATION_USER_ANGLECALCULATOR_H_

float getGyroRate(int axis, int16_t *gyroReadings, uint32_t readResolution);
int arctan2(int y, int x);
int getAccAngle(int axis, int16_t *accelReadings);

#endif /* APPLICATION_USER_ANGLECALCULATOR_H_ */
