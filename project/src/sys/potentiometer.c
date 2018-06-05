/*
 * potentiometer.c
 *
 *  Created on: 5 iun. 2018
 *      Author: Andrei
 */

#include "potentiometer.h"

void initPotentiometer(void)
{
	ADC_init();
}

uint32_t readPotentiometer(void)
{
    convertAdcChan(POT_ADC_CHANNEL);                   /* Convert Channel AD12 to pot on EVB */
    while(adc_complete()==0){}            /* Wait for conversion complete flag */
    return read_adc_chx();       /* Get channel's conversion results in mv */
}
