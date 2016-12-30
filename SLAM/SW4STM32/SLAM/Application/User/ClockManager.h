/*
 * ClockManager.h
 *
 *  Created on: Sep 2, 2016
 *      Author: Rafal
 */

#include "stm32f4xx_hal.h"

#ifndef APPLICATION_USER_CLOCKMANAGER_H_
#define APPLICATION_USER_CLOCKMANAGER_H_

void sysTickInit(void);
void timeTickIncrement(void);
uint32_t getSysTickCounterValue();

#endif /* APPLICATION_USER_CLOCKMANAGER_H_ */
