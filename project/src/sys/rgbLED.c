/*
 * rgbLED.c
 *
 *  Created on: 5 iun. 2018
 *      Author: Andrei
 */

#include "rgbLED.h"


void turnLEDOn(eLED led)
{
	GPIO_setPinValue(GPIOD, LED_BLUE, LED_OFF);
	GPIO_setPinValue(GPIOD, LED_RED, LED_OFF);
	GPIO_setPinValue(GPIOD, LED_GREEN, LED_OFF);

	GPIO_setPinValue(GPIOD, led, LED_ON);
}

void turnLEDOff(eLED led)
{
	GPIO_setPinValue(GPIOD, led, LED_OFF);
}

#define LEDPWN_CNTIN_VAL 0
#define LEDPWN_MOD_VAL 255

//Using flexible timer 0 for controlling RGB LED with PWM
void rgbLED_initPWM()
{
	//RCC enable timer0
	PCC->PCC_FTM0 = PCC_PCCn_CGC_MASK;
	//enable the PORTD peripheral
    PCC->PORTD_CLK = PCC_PCCn_CGC_MASK;

	GPIO_setPinFunction(PORTD, LED_BLUE, eAF_pinAF2);
	GPIO_setPinFunction(PORTD, LED_RED, eAF_pinAF2);
	GPIO_setPinFunction(PORTD, LED_GREEN, eAF_pinAF2);

	enablePWMOutput(FTM0, ePWMLED_BLUE, ePWM_enabled, LEDPWN_CNTIN_VAL, LEDPWN_MOD_VAL);
	enablePWMOutput(FTM0, ePWMLED_RED, ePWM_enabled, LEDPWN_CNTIN_VAL, LEDPWN_MOD_VAL);
	enablePWMOutput(FTM0, ePWMLED_GREEN, ePWM_enabled, LEDPWN_CNTIN_VAL, LEDPWN_MOD_VAL);

	setPWMDUty(FTM0, ePWMLED_BLUE, 0);
	setPWMDUty(FTM0, ePWMLED_RED, 0);
	setPWMDUty(FTM0, ePWMLED_GREEN, 0);

	//configure timer 0
	selectClockSource(FTM0, eCS_FTM_InClk);
	selectPrescaleFactor(FTM0, ePF_DivBy128);
}

void rgbLED_initGPIO(void)
{
	  //enable the PORTD peripheral
	  PCC->PORTD_CLK = PCC_PCCn_CGC_MASK;

	  GPIO_setPinDirection(GPIOD, LED_BLUE, ePinDir_Output);
	  GPIO_setPinFunction(PORTD, LED_BLUE, eAF_pinGPIO);

	  GPIO_setPinDirection(GPIOD, LED_RED, ePinDir_Output);
	  GPIO_setPinFunction(PORTD, LED_RED, eAF_pinGPIO);

	  GPIO_setPinDirection(GPIOD, LED_GREEN, ePinDir_Output);
	  GPIO_setPinFunction(PORTD, LED_GREEN, eAF_pinGPIO);
}

void initLED(eLEDControlType control)
{
	if(eLEDCtrl_PWM == control)
	{
		rgbLED_initPWM();
	}
	else
	{
		rgbLED_initGPIO();
	}
}

void setRgbLEDColor(uint8_t factorR, uint8_t factorG, uint8_t factorB)
{
	setPWMDUty(FTM0, ePWMLED_RED, factorR);
	setPWMDUty(FTM0, ePWMLED_GREEN, factorG);
	setPWMDUty(FTM0, ePWMLED_BLUE, factorB);
}
