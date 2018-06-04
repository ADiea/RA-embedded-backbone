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


/* GPIO Interrupt API Definition */
void enableSingleInterrupt(PORT_Type* whichGPIO, uint8_t pinNumber, eIRQConfig config ){

	whichGPIO->PCR[pinNumber] &= ~(eIRQC_ALL << IRQC);
	whichGPIO->PCR[pinNumber] |= (config << IRQC);
}

uint32_t getPinInterruptStatusFlag(PORT_Type* whichGPIO, uint8_t pinNumber){
	return( whichGPIO->ISFR & (1<<pinNumber) );
}

void clearPinInterruptStatusFlag(PORT_Type* whichGPIO, uint8_t pinNumber){
	whichGPIO->ISFR |= (1<<pinNumber);
}

/*The IRQ_ID for a specific peripheral can be found in S32K1x_INT_MAP_ARM attached
 * to the Reference Manual*/
void enableNVICInterrupt( ePeriphIRQNumber IRQ_ID ){

	/*NVIC register number for IRQ_ID*/
	uint8_t IRQ_reg =  IRQ_ID / 32;
	/*NVIC register bit location*/
	uint8_t IRQ_bit = IRQ_ID % 32;

	S32_NVIC->IP[15] |= ~(15 << 12);

	S32_NVIC->ISER[IRQ_reg] |= (1 << IRQ_bit);
}

void clearNVICInterrupt( ePeriphIRQNumber IRQ_ID ){

	/*NVIC register number for IRQ_ID*/
	uint8_t IRQ_reg =  IRQ_ID / 32;
	/*NVIC register bit location*/
	uint8_t IRQ_bit = IRQ_ID % 32;

	S32_NVIC->ICER[IRQ_ID] |= (1 << IRQ_bit);
}
