/*
 * rgbLED.h
 *
 *  Created on: 5 iun. 2018
 *      Author: Andrei
 */

#ifndef RGBLED_H_
#define RGBLED_H_

#include "gpio.h"
#include "timer.h"

#define MAX_LED_BRIGHTNESS 255

typedef enum{
	LED_ON,
	LED_OFF
}eLedState;

typedef enum{
	LED_BLUE = GPIO_Pin_0,
	LED_RED = GPIO_Pin_15,
	LED_GREEN = GPIO_Pin_16,
}eLED;

typedef enum
{
	ePWMLED_BLUE = eFTM_CH2,
	ePWMLED_RED = eFTM_CH0,
	ePWMLED_GREEN = eFTM_CH1,
}eLEDPWMChannels;

typedef enum
{
	eLEDCtrl_GPIO,
	eLEDCtrl_PWM,
}eLEDControlType;

void initLED(eLEDControlType control);

void turnLEDOn(eLED led);
void turnLEDOff(eLED led);

void setRgbLEDColor(uint8_t factorR, uint8_t factorG, uint8_t factorB);

#endif /* RGBLED_H_ */
