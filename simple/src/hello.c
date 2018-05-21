/*
 * hello.c              Copyright NXP 2016
 * Description:  Simple program to exercise GPIO
 * 2015 Mar 31 S Mihalik/ O Romero - initial version
 *
 */

/*Modified 09.05.2018 by ADiea for simplification of code base*/

#include "S32K144_small.h"    /* include peripheral declarations S32K144 */

#define LED_BLUE  0  /* Port PTD0, bit 0: FRDM EVB output to blue LED */
#define LED_RED 15
#define BUTTON_PIN 12        /* Port PTC12, bit 12: FRDM EVB input from BTN0 [SW2] */

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
                               /* Configure port C12 as GPIO input (BTN 0 [SW2] on EVB) */

  GPIOC->PDDR &= ~(1<<BUTTON_PIN);    /* Port C12: Data Direction= input (default) */
  PORTC->PCR[BUTTON_PIN] = 0x00000110; /* Port C12: MUX = GPIO, input filter enabled */
                               /* Configure port D0 as GPIO output (LED on EVB) */
  GPIOD->PDDR |= 1<<LED_BLUE;        /* Port D0: Data Direction= output */
  PORTD->PCR[0] = 0x00000100;  /* Port D0: MUX = GPIO */
  GPIOD->PDDR |= 1<<LED_RED;
  PORTD->PCR[15] = 0x00000100;

  for(;;) {
    if (GPIOC->PDIR & (1<<BUTTON_PIN)) {   /* If Pad Data Input = 1 (BTN0 [SW2] pushed) */
      GPIOD-> PCOR |= 1<<LED_BLUE; /* Clear Output on port D0 (LED on) */
      GPIOD-> PSOR |= 1<<LED_RED;
    }
    else {                          /* If BTN0 was not pushed */
      GPIOD-> PCOR |= 1<<LED_RED;
      GPIOD-> PSOR |= 1<<LED_BLUE;        /* Set Output on port D0 (LED off) */
    }
    counter++;
  }
}
