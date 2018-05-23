/*
 * hello.c              Copyright NXP 2016
 * Description:  Simple program to exercise GPIO
 * 2015 Mar 31 S Mihalik/ O Romero - initial version
 *
 */

/*Modified 09.05.2018 by ADiea for simplification of code base*/

#include "S32K144_small.h"    /* include peripheral declarations S32K144 */
#include "gpio.h"

#define LED_BLUE				GPIO_Pin_0         /* Port PTD0, bit 0: FRDM EVB output to blue LED */
#define LED_RED					GPIO_Pin_15
#define LED_GREEN				GPIO_Pin_16

#define BTN_0					GPIO_Pin_12        /* Port PTC12, bit 12: FRDM EVB input from BTN0 [SW2] */
#define BTN_1					GPIO_Pin_13
#define NUMBER_BUTTONS			2

#define CPU_FREQ 				4800000
#define WHILE_INSTRUCTIONS 		4
#define BUTTON_TEST_DELAY		(CPU_FREQ / WHILE_INSTRUCTIONS)

#define LED_ON 					0
#define LED_OFF					1

typedef enum{
	eBtn_NotPressed,
	eBtn_Pressed,
	eBtn_LongPressed
}eButtonPress;

typedef enum{
	eButtonLeft = BTN_1,
	eButtonRight = BTN_0
}eButton;

eButtonPress gButtonState[NUMBER_BUTTONS];

eButtonPress isPressed( eButton btn ){

	uint32_t delay = 0;
	uint32_t value = getPinValue(GPIOC,btn);

	if(value){
		while(delay < BUTTON_TEST_DELAY ){
			if(!getPinValue(GPIOC,btn)){
				return eBtn_Pressed;
			}
			delay++;
		}
		return eBtn_LongPressed;
	}
	return eBtn_NotPressed;
}

void waitButtonRelease( eButton btn ){
	while(getPinValue(GPIOC,btn));
}



void WDOG_disable (void)
{
	  /* Write of the WDOG unlock key to CNT register, must be done in order to allow any modifications*/
	  WDOG->CNT = (uint32_t ) FEATURE_WDOG_UNLOCK_VALUE;

	  /* The dummy read is used in order to make sure that the WDOG registers will be configured only
	   * after the write of the unlock value was completed. */
	  (void)WDOG->CNT;

	  /* Initial write of WDOG configuration register:
	   * enables support for 32-bit refresh/unlock command write words,
	   * clock select from LPO, update enable, watchdog disabled */
	  WDOG->CS  = (uint32_t ) ( (1UL << WDOG_CS_CMD32EN_SHIFT)                       |
	                            (FEATURE_WDOG_CLK_FROM_LPO << WDOG_CS_CLK_SHIFT) 	 |
	                            (0U << WDOG_CS_EN_SHIFT)                             |
	                            (1U << WDOG_CS_UPDATE_SHIFT)                         );

	  /* Configure timeout */
	  WDOG->TOVAL = (uint32_t )0xFFFF;
}

int main(void)
{
  //int counter = 0;
  uint8_t whichLED = 0;
  uint8_t LEDState[] = {0,0,0};

  WDOG_disable();             /* Disable Watchdog in case it is not done in startup code */
                              /* Enable clocks to peripherals (PORT modules) */

  //Clock Configuration

  PCC->PORTC_CLK = PCC_PCCn_CGC_MASK;
  PCC->PORTD_CLK = PCC_PCCn_CGC_MASK;

  //GPIO Configuration

  //Right Button
  setPinDirection(GPIOC, BTN_0, ePinDir_Input);
  setPinFunction(PORTC,BTN_0,eAF_pinGPIO);
  setPinPassiveFilter(PORTC, BTN_0, ePassFilter_On);

  //Left Button
  setPinDirection(GPIOC, BTN_1, ePinDir_Input);
  setPinFunction(PORTC,BTN_1,eAF_pinGPIO);
  setPinPassiveFilter(PORTC, BTN_1, ePassFilter_On);

  //Blue LED
  setPinDirection(GPIOD, LED_BLUE, ePinDir_Output);
  setPinFunction(PORTD,LED_BLUE,eAF_pinGPIO);

  //Red LED
  setPinDirection(GPIOD, LED_RED, ePinDir_Output);
  setPinFunction(PORTD,LED_RED,eAF_pinGPIO);

  //Green LED
  setPinDirection(GPIOD, LED_GREEN, ePinDir_Output);
  setPinFunction(PORTD,LED_GREEN,eAF_pinGPIO);

  setPinValue(GPIOD,LED_RED,LED_OFF);
  setPinValue(GPIOD,LED_BLUE,LED_OFF);
  setPinValue(GPIOD,LED_GREEN,LED_OFF);

  for(;;) {


	  //If the Left Button is pressed than the led is changed
	  //Wait the release of the button to increment only once per press
	  if( eBtn_NotPressed != isPressed(eButtonLeft) ){
		  waitButtonRelease(eButtonLeft);

		  whichLED = (whichLED + 1) % 3;
	  }

	  switch(whichLED){
	  	  case 0:

	  		  if( !LEDState[whichLED] && !getPinValue(GPIOC,eButtonRight)){
	  			  setPinValue(GPIOD,LED_RED,LED_OFF);
	  		  }

	  		  if( LEDState[whichLED] && !getPinValue(GPIOC,eButtonRight)){
	  			  setPinValue(GPIOD,LED_RED,LED_ON);
	  		  }

	  		  if( LEDState[whichLED] && getPinValue(GPIOC,eButtonRight)){
	  			  LEDState[whichLED] = 0;
	  			  setPinValue(GPIOD,LED_RED,LED_OFF);
	  		  }

	  		  if( !LEDState[whichLED] && getPinValue(GPIOC,eButtonRight)){
	  			  setPinValue(GPIOD,LED_RED,LED_ON);
	  			  if( eBtn_LongPressed == isPressed(eButtonRight)){
	  				  LEDState[whichLED] = 1;
	  				  waitButtonRelease(eButtonRight);
	  			  }
	  		  }

	  		  break;

	  	  case 1:

	  		if( !LEDState[whichLED] && !getPinValue(GPIOC,eButtonRight)){
	  			 setPinValue(GPIOD,LED_BLUE,LED_OFF);
	  		 }

	  		if( LEDState[whichLED] && !getPinValue(GPIOC,eButtonRight)){
	  			 setPinValue(GPIOD,LED_BLUE,LED_ON);
	  		}

	  		if( LEDState[whichLED] && getPinValue(GPIOC,eButtonRight)){
	  			LEDState[whichLED] = 0;
	  			setPinValue(GPIOD,LED_BLUE,LED_OFF);
	  		}

	  		if( !LEDState[whichLED] && getPinValue(GPIOC,eButtonRight)){
	  			 setPinValue(GPIOD,LED_BLUE,LED_ON);
	  			 if( eBtn_LongPressed == isPressed(eButtonRight)){
	  				 LEDState[whichLED] = 1;
	  				 waitButtonRelease(eButtonRight);
	  			  }
	  		}

	  		break;

	  	  case 2:

	  		if( !LEDState[whichLED] && !getPinValue(GPIOC,eButtonRight)){
	  			setPinValue(GPIOD,LED_GREEN,LED_OFF);
	  		}

	  		if( LEDState[whichLED] && !getPinValue(GPIOC,eButtonRight)){
	  			setPinValue(GPIOD,LED_GREEN,LED_ON);
	  		}

	  		if( LEDState[whichLED] && getPinValue(GPIOC,eButtonRight)){
	  			LEDState[whichLED] = 0;
	  			setPinValue(GPIOD,LED_GREEN,LED_OFF);
	  		}

	  		if( !LEDState[whichLED] && getPinValue(GPIOC,eButtonRight)){
	  			setPinValue(GPIOD,LED_GREEN,LED_ON);
	  			if( eBtn_LongPressed == isPressed(eButtonRight)){
	  				LEDState[whichLED] = 1;
	  			  	waitButtonRelease(eButtonRight);
	  			 }
	  		}

	  		break;

	  }

  }
}
