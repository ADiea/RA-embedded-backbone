/*
 * delay.c
 *
 *  Created on: 5 iun. 2018
 *      Author: Andrei
 */

#include "delay.h"

//experimentally determined a calibration factor, it is not accurate
#define EXPERIMENTAL_CALIB 8
void cpuDelayMs(uint32_t ms)
{
	uint32_t counter;
	while(ms--)
	{
		//delay 1ms
		counter = CPU_FREQ / EXPERIMENTAL_CALIB / 1000;
		while(counter--);
	}
}

