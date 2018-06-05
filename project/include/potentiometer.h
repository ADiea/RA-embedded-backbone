/*
 * potentiometer.h
 *
 *  Created on: 5 iun. 2018
 *      Author: Andrei
 */

#ifndef POTENTIOMETER_H_
#define POTENTIOMETER_H_

#include "adc.h"

#define POT_ADC_CHANNEL 12

#define MAX_POT_VALUE 5000

void initPotentiometer(void);
uint32_t readPotentiometer(void);

#endif /* POTENTIOMETER_H_ */
