/*
 * hello.c              Copyright NXP 2016
 * Description:  Simple program to exercise GPIO
 * 2015 Mar 31 S Mihalik/ O Romero - initial version
 *
 */

/*Modified 09.05.2018 by ADiea for simplification of code base*/

#include "S32K144_small.h"    /* include peripheral declarations S32K144 */

#define LED_BLUE  0         /* Port GPIOD0, bit 0: FRDM EVB output to blue LED */
#define LED_RED   15          /* Port GPIOD15, bit 15: FRDM EVB output to red LED */
#define BUTTON_1  12        /* Port GPIOC12, bit 12: FRDM EVB input from BTN0 [SW2] */
#define BUTTON_2  13
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

  //clock

  PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clock to PORT C */
  PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clock to PORT D */
                               /* Configure port C12 as GPIO input (BTN 0 [SW2] on EVB) */
  //gpio


  GPIOC->PDDR &= ~(1<<BUTTON_1);    /* Port C12: Data Direction= input (default) */
  PORTC->PCR[BUTTON_1] = (eAF_pinGPIO<<PCR_MUX) | (1<< PCR_PFE); /* Port C12: MUX = GPIO, input filter enabled */

  GPIOC->PDDR &= ~(1<<BUTTON_2);                  /* Configure port D0 as GPIO output (LED on EVB) */
  PORTC->PCR[BUTTON_2] = (eAF_pinGPIO<<PCR_MUX) | (1<< PCR_PFE);

  GPIOD->PDDR |= 1<<LED_BLUE;        /* Port D0: Data Direction= output */
  PORTD->PCR[0] = 256;        /* Port D0: MUX = GPIO */
  	  	  	  	  	  	  	  /* Configure port D15 as GPIO output (LED on EVB) */
  GPIOD->PDDR |= 1<<LED_RED;        /* Port D15: Data Direction= output */
  PORTD->PCR[15] = 256;      /* Port D15: MUX = GPIO */
  GPIOD-> PSOR |= 1<<LED_BLUE;
  GPIOD-> PSOR |= 1<<LED_RED;
  for(;;) {
	  int i=0;
	  rep:
	  if (i<200000){
    //if (GPIOC-> PDIR & (1<<BUTTON_1) ){    /* If Pad Data Input = 1 (BTN0 [SW2] pushed) */
		  GPIOD-> PCOR |= 1<<LED_RED;
		  i++;
		  goto rep;
     }
i=0;
GPIOD-> PSOR |= 1<<LED_RED;
rep1:
	  if (i<200000){
  //if (GPIOC-> PDIR & (1<<BUTTON_1) ){    /* If Pad Data Input = 1 (BTN0 [SW2] pushed) */
		  GPIOD-> PSOR |= 1<<LED_RED;
		  i++;
		  goto rep1;
	  	  	  }
	  GPIOD-> PSOR |= 1<<LED_BLUE;
i=0;
  }
}
