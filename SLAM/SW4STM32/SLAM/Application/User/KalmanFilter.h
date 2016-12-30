/*
 * KalmanFilter.h
 *
 *  Created on: Sep 12, 2016
 *      Author: Rafal
 */

#ifndef APPLICATION_USER_KALMANFILTER_H_
#define APPLICATION_USER_KALMANFILTER_H_

typedef struct KalmanFilter {

	float Q_angle; //0.001
	float Q_gyro;  //0.003
	float R_angle;  //0.03

	float x_angle;
	float x_bias;
	float P_00, P_01, P_10, P_11;
	float dt, y, S;
	float K_0, K_1;
} KalmanFilter;

float kalmanCalculate(float newAngle, float newRate, int looptime, KalmanFilter *filter);

#endif /* APPLICATION_USER_KALMANFILTER_H_ */
