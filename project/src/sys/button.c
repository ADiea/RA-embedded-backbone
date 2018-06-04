/*
 * button.c
 *
 *  Created on: June 04, 2018
 *      Author: Andrei Diea
 */

#include "gpio.h"
#include "button.h"
 
void (*btnCallbacks[NUMBER_BUTTONS])(void) = {0, 0};

GPIO_Type* buttonsPort = GPIOC;
 
 void registerBtnPressFn(eButton btn, void (*callback)(void))
 {
	uint8_t btnIndex = 0;
	
	if(btn == eButtonRight)
		btnIndex = 1;
	
	if(callback)
	{
		btnCallbacks[btnIndex] = callback;
	}		
 } 
 
 void PORTC_IRQHandler()
 {
	if(getPinValue(buttonsPort, eButtonLeft))
	{
		if(btnCallbacks[0]) 
			btnCallbacks[0]();
	}
	
	if(getPinValue(buttonsPort, eButtonRight))
	{
		if(btnCallbacks[1]) 
			btnCallbacks[1]();
	}
 }
 
 //todo, redesign
 void waitButtonRelease(eButton btn)
{
	while(getPinValue(GPIOC, btn))
	{
		;
	}
}