/*
 * gpio.c
 *
 *  Created on: May 21, 2018
 *      Author: Andrei Diea
 */

#include "gpio.h"


void setPinDirection(GPIO_Type* whichGPIO, uint8_t pinNumber, ePinDirection dir)
{
	if(ePinDir_Input == dir)
	{
		whichGPIO->PDDR &= ~(1<<pinNumber);
	}
	else
	{
		whichGPIO->PDDR |= (1<<pinNumber);
	}
}

void setPinFunction(PORT_Type* whichGPIO, uint8_t pinNumber, eAlternateFunc func)
{
	whichGPIO->PCR[pinNumber] &= ~(eAF_pinAFALL << PCR_MUX);
	whichGPIO->PCR[pinNumber] |= (func << PCR_MUX);
}

void setPinPasiveFilter(PORT_Type* whichGPIO, uint8_t pinNumber, ePinPasFilter filter)
{
	if(ePasFilter_Off == filter)
	{
		whichGPIO->PCR[pinNumber] &= ~(1<<PCR_PFE);
	}
	else
	{
		whichGPIO->PCR[pinNumber] |= (1<<PCR_PFE);
	}
}

void setPinValue(GPIO_Type* whichGPIO, uint8_t pinNumber, uint8_t value)
{
	if(value)
	{
		whichGPIO->PDOR |= 1<<pinNumber;
	}
	else
	{
		whichGPIO->PDOR &= ~(1<<pinNumber);
	}
}

uint32_t getPinValue(GPIO_Type* whichGPIO, uint8_t pinNumber)
{
	return (whichGPIO->PDIR & (1<<pinNumber));
}
