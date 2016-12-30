/*
 * ClockManager.c
 *
 *  Created on: Sep 2, 2016
 *      Author: Rafal
 */

#include "ClockManager.h"

static __IO uint32_t sysTickCounter = 0;

void sysTickInit(void) {
	/****************************************
	 *SystemFrequency/1000      1ms         *
	 *SystemFrequency/100000    10us        *
	 *SystemFrequency/1000000   1us         *
	 *****************************************/
	while (SysTick_Config(SystemCoreClock / 1000) != 0) {
	}
}

void timeTickIncrement(void) {
	sysTickCounter++;
}

uint32_t getSysTickCounterValue() {
	return sysTickCounter;
}
