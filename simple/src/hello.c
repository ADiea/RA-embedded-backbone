/*
 * hello.c              Copyright NXP 2016
 * Description:  Simple program to exercise GPIO
 * 2015 Mar 31 S Mihalik/ O Romero - initial version
 *
 */

/*Modified 09.05.2018 by ADiea for simplification of code base*/

#include "S32K144_small.h"    /* include peripheral declarations S32K144 */

#define PTD0  0         /* Port PTD0, bit 0: FRDM EVB output to blue LED */
#define PTC12 12        /* Port PTC12, bit 12: FRDM EVB input from BTN0 [SW2] */
#define PTD15 15

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
  PTC->PDDR &= ~(1<<PTC12);    /* Port C12: Data Direction= input (default) */
  PORTC->PCR[12] = 0x00000110; /* Port C12: MUX = GPIO, input filter enabled */
                               /* Configure port D0 as GPIO output (LED on EVB) */
  PTD->PDDR |= 1<<PTD0;        /* Port D0: Data Direction= output */
  PORTD->PCR[0] = 0x00000100;  /* Port D0: MUX = GPIO */

  //PTD->PDDR |= 1<PTD15;
  //PORTD->PCR[15] = 0x00000100;

  for(;;) {
    if (PTC->PDIR & (1<<PTC12)) {   /* If Pad Data Input = 1 (BTN0 [SW2] pushed) */
     // PTD-> PCOR |= 1<<PTD15;        /* Clear Output on port D0 (LED on) */
      PTD-> PCOR |= 1<<PTD0;
    }
    else {                          /* If BTN0 was not pushed */
      //PTD-> PSOR |= 1<<PTD15;        /* Set Output on port D0 (LED off) */
      PTD-> PSOR |= 1<<PTD0;
    }
    counter++;
  }
}
