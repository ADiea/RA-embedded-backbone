/*
 * button.c
 *
 *  Created on: 5 iun. 2018
 *      Author: Andrei
 */
#include "button.h"
#include "interrupt.h"

void (*btnCallbacks[NUMBER_BUTTONS])(void) = {0, 0};

#define BUTTON_WHILE_INSTRUCTIONS (4*90)
#define BUTTON_TEST_DELAY (CPU_FREQ / BUTTON_WHILE_INSTRUCTIONS)

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
	if(PORTC->PCR[eButtonRight] & PCR_ISF_MASK)
	{
		// if pin 12 generated the interrupt, reset ISF from the corresponding PCRn register by writing 1
		// doesn't matter if we write 0 to other bits, because they are write 1 to clear (w1c)
		PORTC->ISFR = (1 << eButtonRight);

		//call the appropiate function if we have one configured
		if(btnCallbacks[0])
			btnCallbacks[0]();
	}

	if(PORTC->PCR[eButtonLeft] & PCR_ISF_MASK)
	{
		// if pin 13 generated the interrupt, reset ISF from the corresponding PCRn register by writing 1
		PORTC->ISFR = (1 << eButtonLeft);

		//call the appropiate function if we have one configured
		if(btnCallbacks[1])
			btnCallbacks[1]();
	}
}

void initSystemButtons(void)
{
	//enable the PORTC peripheral
	PCC->PORTC_CLK = PCC_PCCn_CGC_MASK;

	//GPIO Configuration
	GPIO_setPinDirection(GPIOC, BTN_0, ePinDir_Input);
	GPIO_setPinFunction(PORTC, BTN_0, eAF_pinGPIO);
	GPIO_setPinPasiveFilter(PORTC, BTN_0, ePasFilter_On);

	GPIO_setPinDirection(GPIOC, BTN_1, ePinDir_Input);
	GPIO_setPinFunction(PORTC, BTN_1, eAF_pinGPIO);
	GPIO_setPinPasiveFilter(PORTC, BTN_1, ePasFilter_On);

	//Enable Interrupt on PORTC
	NVIC_enable_IRQ(PORTC_IRQ, 7);

	//Interrupt Configuration
	GPIO_configInterrupt(PORTC, BTN_0, IRQC_RE);
	GPIO_configInterrupt(PORTC, BTN_1, IRQC_RE);

}

eButtonPress isPressed(eButton btn)
{
	static uint32_t buttonDelay[NUMBER_BUTTONS];

	if(GPIO_getPinValue(GPIOC, btn)) //button is pressed
	{
		if(buttonDelay[btn] < BUTTON_TEST_DELAY)
		{
			buttonDelay[btn]++;
			return eBtn_Pressed;
		}
		else
		{
			return eBtn_LongPress;
		}
	}
	//button is not pressed check if it was pressed last time
	else if(buttonDelay[btn] > 0)
	{
		buttonDelay[btn] = 0;
		return eBtn_Released;
	}

	return eBtn_NotPressed;
}

void waitButtonRelease(eButton btn)
{
	while(GPIO_getPinValue(GPIOC, btn))
	{
		;
	}
}
