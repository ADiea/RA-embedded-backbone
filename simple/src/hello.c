/*
 * hello.c              Copyright NXP 2016
 * Description:  Simple program to exercise GPIO
 * 2015 Mar 31 S Mihalik/ O Romero - initial version
 *
 */

/*Modified 09.05.2018 by ADiea for simplification of code base*/

#include "S32K144_small.h"    /* include peripheral declarations S32K144 */

#define LED_BLUE   0          /* Port D, GPIO pin  0: FRDM EVB output to blue LED */
#define LED_RED   15		  /* Port D, GPIO pin 15: FRDM EVB output to red LED */
#define LED_GREEN 16 		  /* Port D, GPIO pin 16: FRDM EVB output to green LED */

#define BTN_0 12              /* Port C, GPIO pin 12: FRDM EVB input from BTN0 [SW2] */
#define BTN_1 13		      /* Port C, GPIO pin 13: FRDM EVB input from BTN1 [SW3] */


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
  int counter = 0;

  WDOG_disable();             /* Disable Watchdog in case it is not done in startup code */

                              /* Enable clocks to peripherals (PORT modules) */
  PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clock to PORT C */
  PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clock to PORT D */

                               /* Configure port C, pin 12 as GPIO input (BTN 0 [SW2] on EVB) */
  GPIOC->PDDR &= ~(1<<BTN_0);       /* Port C, pin 12: Data Direction= input (default)
   	   	   	   	 	 	 	 	 	 	 	 	 	   MUX = GPIO, input filter enabled */
  PORTC->PCR[BTN_0] = (eAF_pinGPIO << PCR_MUX) | (1 << PCR_PFE);

  	  	  	  	  	  	  	   /* Configure port C, pin 13 as GPIO input (BTN 1 [SW3] on EVB) */
  GPIOC->PDDR &= ~(1<<BTN_1);       /* Port C, pin 13: Data Direction= input (default)
  	  	  	  	  	  	  	  	  	  	  	  	  	   MUX = GPIO, input filter enabled */
  PORTC->PCR[BTN_1] = (eAF_pinGPIO << PCR_MUX) | (1 << PCR_PFE);

                               /* Configure port D, pin 0 as GPIO output (blue LED on EVB) */
  GPIOD->PDDR |= 1<<LED_BLUE;       /* Port D, pin 0: Data Direction= output
  	  	  	  	  	  	  	  	  	  	  	  	  	  MUX = GPIO */
  PORTD->PCR[0] = eAF_pinGPIO << PCR_MUX;

  	  	  	  	  	  	  	   /* Configure port D, pin 15 as GPIO output (red LED on EVB) */
  GPIOD->PDDR |= 1<<LED_RED;        /* Port D, pin 15: Data Direction= output
  	  	  	  	  	  	  	  	  	  	  	  	  	   MUX = GPIO */
  PORTD->PCR[15] = eAF_pinGPIO << PCR_MUX;

								/* Configure port D, pin 16 as GPIO output (green LED on EVB) */
  GPIOD->PDDR |= 1<<LED_GREEN;      /* Port D, pin 16: Data Direction= output
  	  	  	  	  	  	  	  	  	  	  	  	  	   MUX = GPIO */
  PORTD->PCR[16] = eAF_pinGPIO << PCR_MUX;


  for(;;) {
    if (GPIOC->PDIR & (1<<BTN_0)) {   /* If Pad Data Input = 1 (BTN0 [SW2] pushed) */
      GPIOD-> PCOR |= 1<<LED_BLUE;        /* Clear Output on port D0 (LED on) */
    }
    else if(GPIOC->PDIR & (1<<BTN_1)) {                          /* If BTN0 was not pushed */
      GPIOD-> PSOR |= 1<<LED_BLUE;        /* Set Output on port D0 (LED off) */
    }
    counter++;
  }
}
