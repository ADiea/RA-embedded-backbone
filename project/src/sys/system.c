/*
 * system.c
 *
 *  Created on: 5 iun. 2018
 *      Author: Andrei
 */
#include "system.h"

//define the application entry point
extern void applicationEntryPoint(void);

#if (defined(__ICCARM__))
    #pragma section = ".data"
    #pragma section = ".data_init"
    #pragma section = ".bss"
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : init_data_bss
 * Description   : Make necessary initializations for RAM.
 * - Copy the vector table from ROM to RAM.
 * - Copy initialized data from ROM to RAM.
 * - Copy code that should reside in RAM from ROM
 * - Clear the zero-initialized data section.
 *
 * Tool Chains:
 *   __GNUC__   : GNU Compiler Collection
 *   __ghs__    : Green Hills ARM Compiler
 *   __ICCARM__ : IAR ARM Compiler
 *   __CSMC__   : Cosmic C Cross Compiler
 *   __DCC__    : Wind River Diab Compiler
 *
 * Implements    : init_data_bss_Activity
 *END**************************************************************************/
void init_data_bss(void)
{
    /* Declare pointers for various data sections. These pointers
     * are initialized using values pulled in from the linker file */
    uint8_t * data_ram;
    uint8_t * code_ram;
    uint8_t * bss_start;
    const uint8_t * data_rom, * data_rom_end;
    const uint8_t * code_rom, * code_rom_end;
    const uint8_t * bss_end;

    /* Get section information from linker files */
#if defined(__ICCARM__)
    /* Data */
    data_ram        = __section_begin(".data");
    data_rom        = __section_begin(".data_init");
    data_rom_end    = __section_end(".data_init");

    /* CODE RAM */
    #pragma section = "__CODE_ROM"
    #pragma section = "__CODE_RAM"
    code_ram        = __section_begin("__CODE_RAM");
    code_rom        = __section_begin("__CODE_ROM");
    code_rom_end    = __section_end("__CODE_ROM");

    /* BSS */
    bss_start       = __section_begin(".bss");
    bss_end         = __section_end(".bss");
#else
    extern uint32_t __DATA_ROM[];
    extern uint32_t __DATA_RAM[];
    extern uint32_t __DATA_END[];

    extern uint32_t __CODE_RAM[];
    extern uint32_t __CODE_ROM[];
    extern uint32_t __CODE_END[];

    extern uint32_t __BSS_START[];
    extern uint32_t __BSS_END[];

    /* Data */
    data_ram        = (uint8_t *)__DATA_RAM;
    data_rom        = (uint8_t *)__DATA_ROM;
    data_rom_end    = (uint8_t *)__DATA_END;
    /* CODE RAM */
    code_ram        = (uint8_t *)__CODE_RAM;
    code_rom        = (uint8_t *)__CODE_ROM;
    code_rom_end    = (uint8_t *)__CODE_END;
    /* BSS */
    bss_start       = (uint8_t *)__BSS_START;
    bss_end         = (uint8_t *)__BSS_END;
#endif

    /* Copy initialized data from ROM to RAM */
    while (data_rom_end != data_rom)
    {
        *data_ram = *data_rom;
        data_ram++;
        data_rom++;
    }

    /* Copy functions from ROM to RAM */
    while (code_rom_end != code_rom)
    {
        *code_ram = *code_rom;
        code_ram++;
        code_rom++;
    }

    /* Clear the zero-initialized data section */
    while(bss_end != bss_start)
    {
        *bss_start = 0;
        bss_start++;
    }
}

/***** CLOCKS ******/

void SOSC_init_8MHz(void) {
  SCG->SOSCDIV=0x00000101;  /* SOSCDIV1 & SOSCDIV2 =1: divide by 1 */
  SCG->SOSCCFG=0x00000024;  /* Range=2: Medium freq (SOSC betw 1MHz-8MHz)*/
                            /* HGO=0:   Config xtal osc for low power */
                            /* EREFS=1: Input is external XTAL */
  while(SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK); /* Ensure SOSCCSR unlocked */
  SCG->SOSCCSR=0x00000001;  /* LK=0:          SOSCCSR can be written */
                            /* SOSCCMRE=0:    OSC CLK monitor IRQ if enabled */
                            /* SOSCCM=0:      OSC CLK monitor disabled */
                            /* SOSCERCLKEN=0: Sys OSC 3V ERCLK output clk disabled */
                            /* SOSCLPEN=0:    Sys OSC disabled in VLP modes */
                            /* SOSCSTEN=0:    Sys OSC disabled in Stop modes */
                            /* SOSCEN=1:      Enable oscillator */
  while(!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK)); /* Wait for sys OSC clk valid */
}

void SPLL_init_160MHz(void) {
  while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); /* Ensure SPLLCSR unlocked */
  SCG->SPLLCSR = 0x00000000;  /* SPLLEN=0: SPLL is disabled (default) */
  SCG->SPLLDIV = 0x00000302;  /* SPLLDIV1 divide by 2; SPLLDIV2 divide by 4 */
  SCG->SPLLCFG = 0x00180000;  /* PREDIV=0: Divide SOSC_CLK by 0+1=1 */
                              /* MULT=24:  Multiply sys pll by 4+24=40 */
                              /* SPLL_CLK = 8MHz / 1 * 40 / 2 = 160 MHz */
  while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); /* Ensure SPLLCSR unlocked */
  SCG->SPLLCSR = 0x00000001; /* LK=0:        SPLLCSR can be written */
                             /* SPLLCMRE=0:  SPLL CLK monitor IRQ if enabled */
                             /* SPLLCM=0:    SPLL CLK monitor disabled */
                             /* SPLLSTEN=0:  SPLL disabled in Stop modes */
                             /* SPLLEN=1:    Enable SPLL */
  while(!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK)); /* Wait for SPLL valid */
}

void NormalRUNmode_80MHz (void) {  /* Change to normal RUN mode with 8MHz SOSC, 80 MHz PLL*/
  SCG->RCCR=SCG_RCCR_SCS(6)      /* PLL as clock source*/
    |SCG_RCCR_DIVCORE(0b01)      /* DIVCORE=1, div. by 2: Core clock = 160/2 MHz = 80 MHz*/
    |SCG_RCCR_DIVBUS(0b01)       /* DIVBUS=1, div. by 2: bus clock = 40 MHz*/
    |SCG_RCCR_DIVSLOW(0b10);     /* DIVSLOW=2, div. by 2: SCG slow, flash clock= 26 2/3 MHz*/
  while (((SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT ) != 6) {}
                                 /* Wait for sys clk src = SPLL */
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

void sysInit(void)
{
	  init_data_bss();

	  WDOG_disable();             /* Disable Watchdog in case it is not done in startup code */

	  SOSC_init_8MHz();      /* Initialize system oscillator for 8 MHz xtal */
	  SPLL_init_160MHz();    /* Initialize SPLL to 160 MHz with 8 MHz SOSC */
	  NormalRUNmode_80MHz(); /* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */

	  // we could exit priviledged mode here to limit further configurations
	  // call application code, that uses system functionality to implement application logic
	  applicationEntryPoint();
}
