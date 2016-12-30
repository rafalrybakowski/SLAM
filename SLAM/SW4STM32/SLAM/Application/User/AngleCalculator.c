/*
 * AngleCalculator.c
 *
 *  Created on: Sep 12, 2016
 *      Author: Rafal
 */

#include "stm32f4xx_hal.h"
#include "AngleCalculator.h"
#include "Math.h"

#define ABS(x) (((x) > 0) ? (x) : -(x))

float getGyroRate(int axis, int16_t *gyroReadings, uint32_t readResolution) {

	float rate = 0;

	if (axis == "x") {
		rate = gyroReadings[0];
	}
	if (axis == "y") {
		rate = gyroReadings[1];
	}
	if (axis == "z") {
		rate = gyroReadings[2];
	}

	float rawRate = rate / 32768.0;

	float dt = readResolution / 1000.0;
	float gyroDps = 250;

	return (float) (rawRate * gyroDps * dt);
}

int arctan2(int y, int x) {                                    // http://www.dspguru.com/comp.dsp/tricks/alg/fxdatan2.htm
	int coeff_1 = 128;                                          // angle in Quids (1024 Quids=360°)
	int coeff_2 = 3 * coeff_1;
	float abs_y = ABS(y) + 1e-10;
	float r, angle;

	if (x >= 0) {
		r = (x - abs_y) / (x + abs_y);
		angle = coeff_1 - coeff_1 * r;
	} else {
		r = (x + abs_y) / (abs_y - x);
		angle = coeff_2 - coeff_1 * r;
	}
	if (y < 0) {
		return (int) -angle;
	} else {
		return (int) angle;
	}
}

int getAccAngle(int axis, int16_t *accelReadings) {

	if (axis == "x") {
		int x = arctan2(accelReadings[2], accelReadings[1]);
		return x;
	}
	if (axis == "y") {
		int y = arctan2(accelReadings[2], accelReadings[0]);
		return y;
	} else {
		return 0;
	}

}
