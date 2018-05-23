/*Very simple include file with only several definitions of the S32K144 MCU*/
/*09.05.2018 by ADiea for simplification of code base*/

#ifndef S32K144_SMALL_H
#define S32K144_SMALL_H

//From S32K144_features.h

/* @brief The 32-bit value used for unlocking the WDOG. */
#define FEATURE_WDOG_UNLOCK_VALUE                       (0xD928C520U)
/* @brief The value used to set WDOG source clock from LPO. */
#define FEATURE_WDOG_CLK_FROM_LPO                       (0x1UL)

//we are on a 32bit arch so unsigned int should be a uint32
typedef unsigned int uint32_t;
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
	uint32_t FTM0;
	uint32_t FTM1;
	uint32_t FTM2;
	uint32_t ADC0;
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




#endif
