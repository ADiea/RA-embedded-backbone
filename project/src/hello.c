/*
 * hello.c              Copyright NXP 2016
 * Description:  Simple program to exercise GPIO
 * 2015 Mar 31 S Mihalik/ O Romero - initial version
 *
 */

/*Modified 09.05.2018 by ADiea for simplification of code base*/

#include "S32K144_small.h"    /* include peripheral declarations S32K144 */
#include "gpio.h"

#define BTN_0		GPIO_Pin_12        /* Port PTC12, bit 12: FRDM EVB input from BTN0 [SW2] */
#define BTN_1		GPIO_Pin_13
#define NUMBER_BUTTONS 2

#define LED_ON 0
#define LED_OFF 1

#define CPU_FREQ 48000000
#define WHILE_INSTRUCTIONS 30
#define BUTTON_TEST_DELAY (CPU_FREQ / WHILE_INSTRUCTIONS)

typedef enum{
	LED_BLUE = GPIO_Pin_0,
	LED_RED = GPIO_Pin_15,
	LED_GREEN = GPIO_Pin_16,
}eLED;

typedef enum {
	eBtn_NotPressed,
	eBtn_Pressed,
	eBtn_LongPress,
}eButtonPress;

typedef enum{
	eButtonLeft = BTN_1,
	eButtonRight = BTN_0,
}eButton;

eLED gWhichLED;

void setLEDOn(eLED led)
{
	switch (led) {
		case LED_BLUE:
			setPinValue(GPIOD, LED_BLUE, LED_ON);
			setPinValue(GPIOD, LED_RED, LED_OFF);
			setPinValue(GPIOD, LED_GREEN, LED_OFF);
			break;
		case LED_RED:
			setPinValue(GPIOD, LED_BLUE, LED_OFF);
			setPinValue(GPIOD, LED_RED, LED_ON);
			setPinValue(GPIOD, LED_GREEN, LED_OFF);
			break;
		case LED_GREEN:
			setPinValue(GPIOD, LED_BLUE, LED_OFF);
			setPinValue(GPIOD, LED_RED, LED_OFF);
			setPinValue(GPIOD, LED_GREEN, LED_ON);
			break;
	}
}

eButtonPress isPressed(eButton btn)
{
	uint32_t delay=0;
	uint8_t value = getPinValue(GPIOC, btn);

	if(value)
	{
		if(eButtonRight == btn)
		{
			setLEDOn(gWhichLED);
		}
		while(delay < BUTTON_TEST_DELAY)
		{
			if(!getPinValue(GPIOC, btn))
			{
				return eBtn_Pressed;
			}
			delay++;
		}
		return eBtn_LongPress;
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

void resetLeds()
{
	  setPinValue(GPIOD, LED_BLUE, LED_OFF);
	  setPinValue(GPIOD, LED_RED, LED_OFF);
	  setPinValue(GPIOD, LED_GREEN, LED_OFF);
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
  WDOG_disable();             /* Disable Watchdog in case it is not done in startup code */
                              /* Enable clocks to peripherals (PORT modules) */

  //Clock Configuration
  PCC->PORTC_CLK = PCC_PCCn_CGC_MASK;
  PCC->PORTD_CLK = PCC_PCCn_CGC_MASK;

  //GPIO Configuration
  setPinDirection(GPIOC, BTN_0, ePinDir_Input);
  setPinFunction(PORTC, BTN_0, eAF_pinGPIO);
  setPinPasiveFilter(PORTC, BTN_0, ePasFilter_On);

  setPinDirection(GPIOC, BTN_1, ePinDir_Input);
  setPinFunction(PORTC, BTN_1, eAF_pinGPIO);
  setPinPasiveFilter(PORTC, BTN_1, ePasFilter_On);

  setPinDirection(GPIOD, LED_BLUE, ePinDir_Output);
  setPinFunction(PORTD, LED_BLUE, eAF_pinGPIO);

  setPinDirection(GPIOD, LED_RED, ePinDir_Output);
  setPinFunction(PORTD, LED_RED, eAF_pinGPIO);

  setPinDirection(GPIOD, LED_GREEN, ePinDir_Output);
  setPinFunction(PORTD, LED_GREEN, eAF_pinGPIO);

  resetLeds();

  uint8_t isPersistent = 0;
  gWhichLED = LED_BLUE;

  for(;;)
  {
	if( eBtn_NotPressed != isPressed(eButtonLeft) )
	{
		waitButtonRelease(eButtonLeft);
		switch (gWhichLED) {
			case LED_BLUE:
				gWhichLED = LED_GREEN;
				break;
			case LED_GREEN:
				gWhichLED = LED_RED;
				break;
			case LED_RED:
				gWhichLED = LED_BLUE;
				break;
			default:
				break;
		}
	}

	//open the LED if there was a longPress;
	if(isPersistent)
	{
		setLEDOn(gWhichLED);
	}


	eButtonPress btnPressed = isPressed(eButtonRight);
	if( eBtn_LongPress == btnPressed )
	{
		//making the LED stay on
		isPersistent = 1;
		waitButtonRelease(eButtonRight);
	}
	else if(eBtn_Pressed == btnPressed)
	{
		//switching off the LED if it was on
		isPersistent = 0;
	}
	resetLeds();
  }
}
