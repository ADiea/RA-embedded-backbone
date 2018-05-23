#include "gpio.h"

void setPinDirection(GPIO_Type* whichGPIO, uint8_t pinNumber, ePinDirection dir){

	//se poate reseta din prima si  eventual facut 1 dupa daca e nevoie -- varianta mai buna 
	//facem cu if pentru clariatate
	if( ePinDir_Input == dir){
		whichGPIO->PDDR &= ~(1<<pinNumber);
	}
	else{
		whichGPIO->PDDR |= (1<<pinNumber);
	}
}


void setPinFunction(PORT_Type* whichGPIO, uint8_t pinNumber, eAlternateFunc func ){

	//clear pins
	whichGPIO->PCR[pinNumber] &= ~(eAF_pinAFALL << PCR_MUX);
	//set Alternate Function
	whichGPIO->PCR[pinNumber] |= (func << PCR_MUX);
}


void setPinPassiveFilter(PORT_Type* whichGPIO, uint8_t pinNumber, ePinPassFilter filter){
	if( ePassFilter_Off == filter){
		whichGPIO->PCR[pinNumber] &= ~(1<< PCR_PFE);
	}
	else{
		whichGPIO->PCR[pinNumber] |= (1<< PCR_PFE);
	}
}


void setPinValue(GPIO_Type* whichGPIO, uint8_t pinNumber, uint8_t value){

	if(value){
		whichGPIO->PDOR |= (1<<pinNumber);
	}
	else{
		whichGPIO->PDOR &= ~(1<<pinNumber);
	}
}

void togglePinValue(GPIO_Type* whichGPIO, uint8_t pinNumber){
	whichGPIO->PDOR ^= (1 << pinNumber );
}

uint8_t getPinValue(GPIO_Type* whichGPIO, uint8_t pinNumber){
	if( (whichGPIO->PDIR & (1<<pinNumber)) > 0 )
		return 0x01;
	else
		return 0x00;
}
