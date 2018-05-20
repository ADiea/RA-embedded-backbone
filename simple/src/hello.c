/*
 * hello.c              Copyright NXP 2016
 * Description:  Simple program to exercise GPIO
 * 2015 Mar 31 S Mihalik/ O Romero - initial version
 *
 */

/*Modified 09.05.2018 by ADiea for simplification of code base*/

#include "S32K144_small.h"    /* include peripheral declarations S32K144 */

#define LED_BLUE  	0         /* Port PTD0, bit 0: FRDM EVB output to blue LED */
#define LED_RED   	15		/*port PTD15,bit15*/
#define LED_GREEN 	16

#define BTN_0 		12        /* Port PTC12, bit 12: FRDM EVB input from BTN0 [SW2] */
#define BTN_1		13
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

  //gpio
  /* Configure port C12 as GPIO input (BTN 0 [SW2] on EVB) */
  GPIOC->PDDR &= ~(1<<BTN_0);    /* Port C12: Data Direction= input (default) */
  PORTC->PCR[BTN_0] =(eAF_pinGPIO << PCR_MUX) | (1 << PCR_PFE); // 0x00000110; /* Port C12: MUX = GPIO, input filter enabled */
  //configure port C13 as GPIO input (BTN 1)
  GPIOC->PDDR &= ~(1<<BTN_1);
  PORTC->PCR[BTN_1] =(eAF_pinGPIO << PCR_MUX) | (1 << PCR_PFE);

  /* Configure port D0 as GPIO output (LED on EVB) */
  GPIOD->PDDR |= 1<<LED_BLUE;        /* Port D0: Data Direction= output */
  PORTD->PCR[0] = eAF_pinGPIO << PCR_MUX;  /* Port D0: MUX = GPIO */

  GPIOD->PDDR |= 1<<LED_RED;        /* Port D15: Data Direction= output */
  PORTD->PCR[LED_RED] = eAF_pinGPIO << PCR_MUX;  /* Port D16: MUX = GPIO */

  GPIOD->PDDR |= 1<<LED_GREEN;        /* Port D16: Data Direction= output */
  PORTD->PCR[LED_GREEN] = eAF_pinGPIO << PCR_MUX;  /* Port D16: MUX = GPIO */

  for(;;) {
    if (GPIOC->PDIR & (1<<BTN_0)) {   /* If Pad Data Input = 1 (BTN0 [SW2] pushed) */
      if(counter%3==0)
      {
    	  GPIOD-> PCOR |= 1<<LED_BLUE;/* Clear Output on port D0 (LED on) */
      	  GPIOD-> PSOR |= (1<<LED_RED) | (1<<LED_GREEN);
      }
      else if(counter%3==1)
      {
    	  GPIOD-> PCOR |= 1<<LED_RED;
      	  GPIOD-> PSOR |= (1<<LED_BLUE) | (1<<LED_GREEN);
      }
      else
      {
    	  GPIOD-> PCOR |= 1<<LED_GREEN;
      	  GPIOD-> PSOR |= (1<<LED_BLUE) | (1<<LED_RED);
      }
      counter++;

    }
    if (GPIOC->PDIR & (1<<BTN_1)) {                          /* If BTN1 was pushed */
      GPIOD-> PSOR |= (1<<LED_BLUE) | (1<<LED_RED) | (1<<LED_GREEN);        /* Set Output on port D0 (LED off) */
      counter=0;
    }

  }
}
