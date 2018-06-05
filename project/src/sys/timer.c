/*
 * timer.c
 *
 *  Created on: May 30, 2018
 *      Author: marius
 */

#include "timer.h"


void setWriteProtection(FTM_Type* whichTimer, eWriteProtection mode)
{
	if(mode == eWP_enabled) {
		whichTimer->MODE &= ~(1 << MODE_WPDIS);
	}
	else {
		whichTimer->MODE |= (1 << MODE_WPDIS);
	}
}

void selectClockSource(FTM_Type* whichTimer, eClockSource clk) {
	whichTimer->SC &= ~(eCS_ALL << SC_CLKS);
	whichTimer->SC |= (clk << SC_CLKS);

}

void selectPrescaleFactor(FTM_Type* whichTimer, ePrescaleFactor factor) {
	whichTimer->SC &= ~(ePF_ALL << SC_PS);
	whichTimer->SC |= (factor << SC_PS);
}

/*
 Enables the edge aligned PWM
	QUADEN = 0
	DECAPEN = 0
	MCOMBINE = 0
	COMBINE = 0
	CPWMS = 0, and
	MSB = 1
	The EPWM period is determined by (MOD − CNTIN + 0x0001) and the pulse width
	(duty cycle) is determined by (CnV − CNTIN).
	The CHF bit is set and the channel (n) interrupt is generated if CHIE = 1 at the channel
	(n) match (FTM counter = CnV), that is, at the end of the pulse width.

Clock freq is 48000000 /s (Hz)
Prescaler is set to 128
------------
=> timer counting freq = 375000 counts/s

We need a period of at least 24Hz for controlling the led without perceiving blinks

Use CTIN = 0 and MOD=255 => MOD-CTIN = 255
=> PWM freq is 375000 / (255+1) = 1464Hz

----____----____

<------>
1/1464 s

Duty cycle will be between 0 -> 255 (0% -> 100%)

PWM inverted mode because led lights up on 0 level

*/

void enablePWMOutput(FTM_Type* whichTimer, eFTMChannel whichChannel, ePWMoutput mode,
		 uint32_t cntin, uint32_t mod)
{
	uint32_t *pChannelConfig = 0;
	if(mode == ePWM_disabled) {
		whichTimer->SC &= ~(1 << (SC_PWMENn + whichChannel));
	}
	else {
		whichTimer->SC |= (1 << (SC_PWMENn + whichChannel));
	}

	whichTimer->CNT = 0;
	whichTimer->CNTIN = cntin;
	whichTimer->MOD = mod;

	pChannelConfig =TIMER_CH_SC(whichTimer, whichChannel);

	*pChannelConfig |= (1<<CxSC_MSB) | (1<<CxSC_ELSA);

	whichTimer->MODE |= 1<<MODE_INIT;

}

void setPWMDUty(FTM_Type* whichTimer, eFTMChannel whichChannel, uint32_t duty)
{
	uint32_t *pChannelConfig = TIMER_CH_V(whichTimer, whichChannel);
	*pChannelConfig  = duty;
}
