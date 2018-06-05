/*
 * system.h
 *
 *  Created on: 5 iun. 2018
 *      Author: Andrei
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#define CPU_FREQ 48000000

/* @brief The 32-bit value used for unlocking the WDOG. */
#define FEATURE_WDOG_UNLOCK_VALUE                       (0xD928C520U)
/* @brief The value used to set WDOG source clock from LPO. */
#define FEATURE_WDOG_CLK_FROM_LPO                       (0x1UL)

//we are on a 32bit arch so unsigned int should be a uint32
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

//From S32K144.h

//############################ Watchdog definitions ############################

/** WDOG - Register Layout Typedef */
typedef struct {
   uint32_t CS;                                /**< Watchdog Control and Status Register, offset: 0x0 */
   uint32_t CNT;                               /**< Watchdog Counter Register, offset: 0x4 */
   uint32_t TOVAL;                             /**< Watchdog Timeout Value Register, offset: 0x8 */
   uint32_t WIN;                               /**< Watchdog Window Register, offset: 0xC */
} WDOG_Type, *WDOG_MemMapPtr;

/* WDOG - Peripheral instance base addresses */
/** Peripheral WDOG base address */
#define WDOG_BASE                                (0x40052000u)
/** Peripheral WDOG base pointer */
#define WDOG                                     ((WDOG_Type *)WDOG_BASE)

#define WDOG_CS_CLK_SHIFT                        8u
#define WDOG_CS_CMD32EN_SHIFT                    13u
#define WDOG_CS_EN_SHIFT                         7u
#define WDOG_CS_UPDATE_SHIFT                     5u

//############################ peripheral enable definitions ############################

typedef struct {
	uint8_t RESERVED_0[128];
	uint32_t FTFC;
	uint32_t DMAMUX;
	uint8_t RESERVED_1[8];
	uint32_t FlexCAN0;
	uint32_t FlexCAN1;
	uint32_t FTM3;
	uint32_t ADC1;
	uint8_t RESERVED_2[12];
	uint32_t FlexCAN2;
	uint32_t LPSPI0;
	uint32_t LPSPI1;
	uint32_t LPSPI2;
	uint8_t RESERVED_3[8];
	uint32_t PDB1;
	uint32_t CRC;
	uint8_t RESERVED_4[12];
	uint32_t PDB0;
	uint32_t LPIT;
	uint32_t PCC_FTM0;
	uint32_t PCC_FTM1;
	uint32_t FTM2;
	uint32_t PCC_ADC0;
	uint8_t RESERVED_5[4];
	uint32_t RTC;
	uint8_t RESERVED_6[8];
	uint32_t LPTMR0;
	uint8_t RESERVED_7[32];
	uint32_t PORTA_CLK;
	uint32_t PORTB_CLK;
	uint32_t PORTC_CLK;
	uint32_t PORTD_CLK;
	uint32_t PORTE_CLK;
	uint8_t RESERVED_8[24];
	uint32_t SAI0;
	uint32_t SAI1;
	uint8_t RESERVED_9[16];
	uint32_t FlexIO;
	uint8_t RESERVED_10[24];
	uint32_t EWM;
	uint8_t RESERVED_11[16];
	uint32_t LPI2C0;
	uint32_t LPI2C1;
	uint8_t RESERVED_12[8];
	uint32_t LPUART0;
	uint32_t LPUART1;
	uint32_t LPUART2;
	uint8_t RESERVED_13[4];
	uint32_t FTM4;
	uint32_t FTM5;
	uint32_t FTM6;
	uint32_t FTM7;
	uint8_t RESERVED_14[4];
	uint32_t CMP0;
	uint8_t RESERVED_15[8];
	uint32_t QSPI;
	uint8_t RESERVED_16[8];
	uint32_t ENET;

} PCC_Type, *PCC_MemMapPtr;

/** Peripheral PCC base address */
#define PCC_BASE                                 (0x40065000u)
/** Peripheral PCC base pointer */
#define PCC                                      ((PCC_Type *)PCC_BASE)

#define PCC_PCCn_CGC_MASK                        (1<<30)

#define PCC_PCS                        			 24

/*################# CLOCKS ######################*/

/** SCG - Register Layout Typedef */
typedef struct {
   uint32_t VERID;                             /**< Version ID Register, offset: 0x0 */
   uint32_t PARAM;                             /**< Parameter Register, offset: 0x4 */
   uint8_t RESERVED_0[8];
   uint32_t CSR;                               /**< Clock Status Register, offset: 0x10 */
   uint32_t RCCR;                              /**< Run Clock Control Register, offset: 0x14 */
   uint32_t VCCR;                              /**< VLPR Clock Control Register, offset: 0x18 */
   uint32_t HCCR;                              /**< HSRUN Clock Control Register, offset: 0x1C */
   uint32_t CLKOUTCNFG;                        /**< SCG CLKOUT Configuration Register, offset: 0x20 */
   uint8_t RESERVED_1[220];
   uint32_t SOSCCSR;                           /**< System OSC Control Status Register, offset: 0x100 */
   uint32_t SOSCDIV;                           /**< System OSC Divide Register, offset: 0x104 */
   uint32_t SOSCCFG;                           /**< System Oscillator Configuration Register, offset: 0x108 */
   uint8_t RESERVED_2[244];
   uint32_t SIRCCSR;                           /**< Slow IRC Control Status Register, offset: 0x200 */
   uint32_t SIRCDIV;                           /**< Slow IRC Divide Register, offset: 0x204 */
   uint32_t SIRCCFG;                           /**< Slow IRC Configuration Register, offset: 0x208 */
   uint8_t RESERVED_3[244];
   uint32_t FIRCCSR;                           /**< Fast IRC Control Status Register, offset: 0x300 */
   uint32_t FIRCDIV;                           /**< Fast IRC Divide Register, offset: 0x304 */
   uint32_t FIRCCFG;                           /**< Fast IRC Configuration Register, offset: 0x308 */
   uint8_t RESERVED_4[756];
   uint32_t SPLLCSR;                           /**< System PLL Control Status Register, offset: 0x600 */
   uint32_t SPLLDIV;                           /**< System PLL Divide Register, offset: 0x604 */
   uint32_t SPLLCFG;                           /**< System PLL Configuration Register, offset: 0x608 */
} SCG_Type, *SCG_MemMapPtr;

/* SCG - Peripheral instance base addresses */
/** Peripheral SCG base address */
#define SCG_BASE                                 (0x40064000u)
/** Peripheral SCG base pointer */
#define SCG                                      ((SCG_Type *)SCG_BASE)

#define SCG_SPLLCSR_LK_MASK                      0x800000u
#define SCG_SOSCCSR_LK_MASK                      0x800000u
#define SCG_SOSCCSR_SOSCVLD_MASK                 0x1000000u
#define SCG_SPLLCSR_SPLLVLD_MASK                 0x1000000u
#define SCG_CSR_SCS_MASK                         0xF000000u
#define SCG_CSR_SCS_SHIFT                        24u

/* RCCR Bit Fields */
#define SCG_RCCR_DIVSLOW_MASK                    0xFu
#define SCG_RCCR_DIVSLOW_SHIFT                   0u
#define SCG_RCCR_DIVSLOW_WIDTH                   4u
#define SCG_RCCR_DIVSLOW(x)                      (((uint32_t)(((uint32_t)(x))<<SCG_RCCR_DIVSLOW_SHIFT))&SCG_RCCR_DIVSLOW_MASK)
#define SCG_RCCR_DIVBUS_MASK                     0xF0u
#define SCG_RCCR_DIVBUS_SHIFT                    4u
#define SCG_RCCR_DIVBUS_WIDTH                    4u
#define SCG_RCCR_DIVBUS(x)                       (((uint32_t)(((uint32_t)(x))<<SCG_RCCR_DIVBUS_SHIFT))&SCG_RCCR_DIVBUS_MASK)
#define SCG_RCCR_DIVCORE_MASK                    0xF0000u
#define SCG_RCCR_DIVCORE_SHIFT                   16u
#define SCG_RCCR_DIVCORE_WIDTH                   4u
#define SCG_RCCR_DIVCORE(x)                      (((uint32_t)(((uint32_t)(x))<<SCG_RCCR_DIVCORE_SHIFT))&SCG_RCCR_DIVCORE_MASK)
#define SCG_RCCR_SCS_MASK                        0xF000000u
#define SCG_RCCR_SCS_SHIFT                       24u
#define SCG_RCCR_SCS_WIDTH                       4u
#define SCG_RCCR_SCS(x)                          (((uint32_t)(((uint32_t)(x))<<SCG_RCCR_SCS_SHIFT))&SCG_RCCR_SCS_MASK)



void sysInit(void);

#endif /* SYSTEM_H_ */
