/*
 * KalmanFilter.c
 *
 *  Created on: Sep 12, 2016
 *      Author: Rafal
 */

#include "KalmanFilter.h"

float kalmanCalculate(float newAngle, float newRate, int looptime, KalmanFilter *filter) {

	filter->dt = (float) looptime / 1000;
	filter->x_angle += filter->dt * (newRate - filter->x_bias);
	filter->P_00 += -filter->dt * (filter->P_10 + filter->P_01) + filter->Q_angle * filter->dt;
	filter->P_01 += -filter->dt * filter->P_11;
	filter->P_10 += -filter->dt * filter->P_11;
	filter->P_11 += +filter->Q_gyro * filter->dt;

	filter->y = newAngle - filter->x_angle;
	filter->S = filter->P_00 + filter->R_angle;
	filter->K_0 = filter->P_00 / filter->S;
	filter->K_1 = filter->P_10 / filter->S;

	filter->x_angle += filter->K_0 * filter->y;
	filter->x_bias += filter->K_1 * filter->y;
	filter->P_00 -= filter->K_0 * filter->P_00;
	filter->P_01 -= filter->K_0 * filter->P_01;
	filter->P_10 -= filter->K_1 * filter->P_00;
	filter->P_11 -= filter->K_1 * filter->P_01;

	return filter->x_angle;
}
