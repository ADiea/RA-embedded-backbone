
/*Modified 09.05.2018 by ADiea for simplification of code base*/

#include "S32K144_small.h"    /* include peripheral declarations S32K144 */
#include "gpio.h"
#include "timer.h"
#include "button.h"

typedef enum{
	LED_ON,
	LED_OFF
}eLedState;

//#define LED_OFF 1

#define CPU_FREQ 48000000
#define WHILE_INSTRUCTIONS (4*90)
#define BUTTON_TEST_DELAY (CPU_FREQ / WHILE_INSTRUCTIONS)

#define LEDPWN_CNTIN_VAL 0
#define LEDPWN_MOD_VAL 255

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

uint32_t buttonDelay[NUMBER_BUTTONS];

//experimentally determined a calibration factor, it is not accurate
#define EXPERIMENTAL_CALIB 8

void cpuDelayMs(uint32_t ms)
{
	uint32_t counter;
	while(ms--)
	{
		//delay 1ms
		counter = CPU_FREQ / EXPERIMENTAL_CALIB / 1000;
		while(counter--);
	}
}

eButtonPress leftButPressState = eBtn_NotPressed;
eButtonPress rightButPressState = eBtn_NotPressed;

void PORTC_IRQHandler(void)
{

	if(getPinInterruptStatusFlag(PORTC,eButtonRight)){
		rightButPressState = eBtn_Pressed;
		clearPinInterruptStatusFlag(PORTC,eButtonRight);
	}

	if(getPinInterruptStatusFlag(PORTC,eButtonLeft)){
		leftButPressState = eBtn_Pressed;
		clearPinInterruptStatusFlag(PORTC,eButtonLeft);
	}


}

void turnLEDOn(eLED led)
{
	setPinValue(GPIOD, LED_BLUE, LED_OFF);
	setPinValue(GPIOD, LED_RED, LED_OFF);
	setPinValue(GPIOD, LED_GREEN, LED_OFF);

	setPinValue(GPIOD, led, LED_ON);
}

void turnLEDOff(eLED led)
{
	setPinValue(GPIOD, led, LED_OFF);
}

eButtonPress isPressed(eButton btn)
{
	if(getPinValue(GPIOC, btn)) //button is pressed
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
	else if(buttonDelay[btn] > 0) //button is not pressed check if it was pressed last time
	{
		buttonDelay[btn] = 0;
		return eBtn_Released;
	}

	return eBtn_NotPressed;
}

void waitButtonRelease(eButton btn)
{
	while(getPinValue(GPIOC, btn))
	{
		;
	}
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



//Using flexible timer 0 for controlling RGB LED with PWM
void timer0Init()
{
	//RCC enable timer0
	PCC->PCC_FTM0 = PCC_PCCn_CGC_MASK;
	PCC->PCC_PORTD = PCC_PCCn_CGC_MASK;

	setPinFunction(PORTD, LED_BLUE, eAF_pinAF2);
    setPinFunction(PORTD, LED_RED, eAF_pinAF2);
	setPinFunction(PORTD, LED_GREEN, eAF_pinAF2);

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

void init_RGB_GPIO(void)
{
	  setPinDirection(GPIOD, LED_BLUE, ePinDir_Output);
	  setPinFunction(PORTD, LED_BLUE, eAF_pinGPIO);
	  setPinValue(GPIOD, LED_BLUE, LED_OFF);

	  setPinDirection(GPIOD, LED_RED, ePinDir_Output);
	  setPinFunction(PORTD, LED_RED, eAF_pinGPIO);
	  setPinValue(GPIOD, LED_RED, LED_OFF);

	  setPinDirection(GPIOD, LED_GREEN, ePinDir_Output);
	  setPinFunction(PORTD, LED_GREEN, eAF_pinGPIO);
	  setPinValue(GPIOD, LED_GREEN, LED_OFF);

}


int main(void)
{
	eLEDPWMChannels whichChannel = 0;
	uint8_t dutyCycle[3] = {0,0,0};

	WDOG_disable();             /* Disable Watchdog in case it is not done in startup code */
                              /* Enable clocks to peripherals (PORT modules) */

	timer0Init();
	  //init_RGB_GPIO();
	enableNVICInterrupt( ePORTC_IRQ_Nr );

	initButtons();

	enableSingleInterrupt(PORTC, eButtonRight, eIRQC_RE);
	enableSingleInterrupt(PORTC, eButtonLeft, eIRQC_RE);

	//leftButPressState = eBtn_NotPressed;
	//rightButPressState = eBtn_NotPressed;

	for(;;)
	{

		if( eBtn_Pressed == leftButPressState ){

			/*switch(whichChannel){
			case ePWMLED_RED:
				whichChannel = ePWMLED_GREEN;
				break;
			case ePWMLED_GREEN:
				whichChannel = ePWMLED_BLUE;
				break;
			case ePWMLED_BLUE:
				whichChannel = ePWMLED_RED;
				break;
			}
			leftButPressState = eBtn_NotPressed;*/

			 setPinValue(GPIOD, LED_BLUE, LED_OFF);

		}

		if(  rightButPressState == eBtn_Pressed ){

			/*dutyCycle[whichChannel] += 20;

			if( dutyCycle[whichChannel] > 255 ){
				dutyCycle[whichChannel] = 0;
			}

			setPWMDUty(FTM0, whichChannel, dutyCycle[whichChannel]);
			rightButPressState = eBtn_NotPressed;*/

			 setPinValue(GPIOD, LED_BLUE, LED_OFF);
		}
	  }
}

