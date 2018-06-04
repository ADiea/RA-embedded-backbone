#include "button.h"

void initLeftButton(){

	PCC->PCC_PORTC = PCC_PCCn_CGC_MASK;

	setPinDirection(GPIOC, BTN_1, ePinDir_Input);
	setPinFunction(PORTC, BTN_1, eAF_pinGPIO);
	setPinPasiveFilter(PORTC, BTN_1, ePasFilter_On);
}

void initRightButton(){

	PCC->PCC_PORTC = PCC_PCCn_CGC_MASK;

	setPinDirection(GPIOC, BTN_0, ePinDir_Input);
	setPinFunction(PORTC, BTN_0, eAF_pinGPIO);
	setPinPasiveFilter(PORTC, BTN_0, ePasFilter_On);
}

void initButtons(){

	PCC->PCC_PORTC = PCC_PCCn_CGC_MASK;

	setPinDirection(GPIOC, BTN_0, ePinDir_Input);
	setPinFunction(PORTC, BTN_0, eAF_pinGPIO);
	setPinPasiveFilter(PORTC, BTN_0, ePasFilter_On);

	setPinDirection(GPIOC, BTN_1, ePinDir_Input);
	setPinFunction(PORTC, BTN_1, eAF_pinGPIO);
	setPinPasiveFilter(PORTC, BTN_1, ePasFilter_On);
}
