/*
 * timer.c
 *
 *  Created on: May 30, 2018
 *      Author: marius
 */

#include "timer.h"

void setWriteProtection(FTM_Type* whichTimer, eWriteProtection mode) {
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

void enablePWMOutput(FTM_Type* whichTimer, eFTMChannel whichChannel, ePWMoutput mode) {
	if(mode == ePWM_disabled) {
		whichTimer->SC &= ~(1 << (SC_PWMENn + whichChannel));
	}
	else {
		whichTimer->SC |= (1 << (SC_PWMENn + whichChannel));
	}
}
