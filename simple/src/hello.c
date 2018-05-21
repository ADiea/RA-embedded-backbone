/*
 * hello.c              Copyright NXP 2016
 * Description:  Simple program to exercise GPIO
 * 2015 Mar 31 S Mihalik/ O Romero - initial version
 *
 */

/*Modified 09.05.2018 by ADiea for simplification of code base*/

#include "S32K144_small.h"    /* include peripheral declarations S32K144 */

#define LED_BLUE  0         /* Port PTD0, bit 0: FRDM EVB output to LED_BLUEue LED */
#define LED_RED 15		/* Port PTD15, bit 15 : red LED */
#define LED_GREEN 16		/* Port PTD16, bit 16 : green LED */


#define BUTTON1 12        /* Port BUTTON, bit 12: FRDM EVB input from BTN0 [SW2] */
#define BUTTON2 13		/* Port ptc13*/


void WDOG_disable (void)
{
	  /* Write of the WDOG unlock key to CNT register, must be done in order to allow any modifications*/
	  WDOG->CNT = (uint32_t ) FEATURE_WDOG_UNLOCK_VALUE;

	  /* The dummy read is used in order to make sure that the WDOG registers will be configured only
	   * after the write of the unlock value was completed. */
	  (void)WDOG->CNT;

	  /* Initial write of WDOG configuration register:
	   * enaLED_BLUEes support for 32-bit refresh/unlock command write words,
	   * clock select from LPO, update enaLED_BLUEe, watchdog disaLED_BLUEed */
	  WDOG->CS  = (uint32_t ) ( (1UL << WDOG_CS_CMD32EN_SHIFT)                       |
	                            (FEATURE_WDOG_CLK_FROM_LPO << WDOG_CS_CLK_SHIFT) 	 |
	                            (0U << WDOG_CS_EN_SHIFT)                             |
	                            (1U << WDOG_CS_UPDATE_SHIFT)                         );

	  /* Configure timeout */
	  WDOG->TOVAL = (uint32_t )0xFFFF;
}

int main(void)
{
  int counter = 0;
  int i=0;

  WDOG_disable();             /* DisaLED_BLUEe Watchdog in case it is not done in startup code */
                              /* EnaLED_BLUEe clocks to peripherals (PORT modules) */
  PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; /* EnaLED_BLUEe clock to PORT C */
  PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; /* EnaLED_BLUEe clock to PORT D */
                               /* Configure port C12 as GPIO input (BTN 0 [SW2] on EVB) */
  GPIOC->PDDR &= ~(1<<BUTTON1);    /* Port C12: Data Direction= input (default) */
  PORTC->PCR[BUTTON1] = (eAF_pinGPIO<<PCR_MUX) | (1<<PCR_PFE); /* Port C12: MUX = GPIO, input filter enaLED_BLUEed */
  	  	  	  	  	  	  	   /* Configure port C13 as GPIO input (BTN 1 [SW3] on EVB) */
  GPIOC->PDDR &= ~(1<<BUTTON2);    /* Port C13: Data Direction= input (default) */
  PORTC->PCR[BUTTON2] = (eAF_pinGPIO<<PCR_MUX) | (1<<PCR_PFE); /* Port C13: MUX = GPIO, input filter enaLED_BLUEed */
                               /* Configure port D0 as GPIO output (LED on EVB) */


  GPIOD->PDDR |= 1<<LED_BLUE;        /* Port D0: Data Direction= output */
  PORTD->PCR[LED_BLUE] = (eAF_pinGPIO<<PCR_MUX);  /* Port D0: MUX = GPIO */

  GPIOD->PDDR |= 1<<LED_RED;		   /* Port D15: Data Direction= output */
  PORTD->PCR[LED_RED] = (eAF_pinGPIO<<PCR_MUX);

  GPIOD->PDDR |= 1<<LED_GREEN;		   /* Port D15: Data Direction= output */
  PORTD->PCR[LED_GREEN] = (eAF_pinGPIO<<PCR_MUX);

  for(;;) {
    if (GPIOC->PDIR & (1<<BUTTON2)) {   /* If Pad Data Input = 1 (BTN0 [SW2] pushed) */
    	counter++;       /* Clear Output on port D0 (LED on) */
    }
    if(counter >15){
       	if(i%3 == 0){
       		counter=1;
       	}
       	if(i%3 == 1){
       	    counter=6;
       	}
       	if(i%3 == 2){
       	   counter=11;
       	}
       	i=counter%24;
    }
    if(counter < 5 && (GPIOC->PDIR & (1<<BUTTON1))){
    	GPIOD->PCOR |= 1<<LED_BLUE;
    }
    if(counter >=5 && counter <10 && (GPIOC->PDIR & (1<<BUTTON1))){
    	GPIOD->PCOR |= 1<<LED_RED;
    }
    if(counter >=10 && counter <=15 && (GPIOC->PDIR & (1<<BUTTON1))){
    	GPIOD->PCOR |= 1<<LED_GREEN;
    }
    if(~(GPIOC->PDIR & (1<<BUTTON1))){
    	GPIOD->PSOR |= (1<<LED_BLUE);
    	GPIOD->PSOR |= (1<<LED_RED);
    	GPIOD->PSOR |= (1<<LED_GREEN);
    }
  }
}
