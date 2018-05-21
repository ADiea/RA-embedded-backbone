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

#define PCC_PORTC_INDEX                          75
#define PCC_PORTD_INDEX                          76

/** PCC - Size of Registers Arrays */
#define PCC_PCCn_COUNT                           116u// 121 last register is at offset 0x1e4

/** PCC - Register Layout Typedef */
typedef struct {
   uint32_t PCCn[PCC_PCCn_COUNT];              /**< PCC Reserved Register 0..PCC CMP0 Register, array offset: 0x0, array step: 0x4 */
} PCC_Type, *PCC_MemMapPtr;

/** Peripheral PCC base address */
#define PCC_BASE                                 (0x40065000u)
/** Peripheral PCC base pointer */
#define PCC                                      ((PCC_Type *)PCC_BASE)

#define PCC_PCCn_CGC_MASK                        0x40000000u//1<<30

//############################ GPIO(general purpose input/output) enable definitions ############################

/** GPIO - Register Layout Typedef */
typedef struct {
   uint32_t PDOR;                              /**< Port Data Output Register, offset: 0x0 */
    uint32_t PSOR;                              /**< Port Set Output Register, offset: 0x4 */
    uint32_t PCOR;                              /**< Port Clear Output Register, offset: 0x8 */
    uint32_t PTOR;                              /**< Port Toggle Output Register, offset: 0xC */
    uint32_t PDIR;                              /**< Port Data Input Register, offset: 0x10 */
   uint32_t PDDR;                              /**< Port Data Direction Register, offset: 0x14 */
   uint32_t PIDR;                              /**< Port Input Disable Register, offset: 0x18 */
} GPIO_Type, *GPIO_MemMapPtr;

/** Peripheral PTC base address */
#define GPIOC_BASE                                 (0x400FF080u)
/** Peripheral PTC base pointer */
#define GPIOC                                      ((GPIO_Type *)GPIOC_BASE)
/** Peripheral PTD base address */
#define GPIOD_BASE                                 (0x400FF0C0u)
/** Peripheral PTD base pointer */
#define GPIOD                                      ((GPIO_Type *)GPIOD_BASE)

/** PORT - Size of Registers Arrays */
#define PORT_PCR_COUNT                           32u


typedef enum{
	eAF_pinDisabled=0,
	eAF_GPIO,
	eAF_inAF2,
	eAF_inAF3,
	eAF_inAF4,
	eAF_inAF5,
	eAF_inAF6,
	eAF_inAF7,
}eAlternateFunction;

#define PCR_MUX 8
#define PCR_PFE 4 //Passive Filter Enable

/** PORT - Register Layout Typedef */
typedef struct {
  uint32_t PCR[PORT_PCR_COUNT];               /**< Pin Control Register n, array offset: 0x0, array step: 0x4 */
    uint32_t GPCLR;                             /**< Global Pin Control Low Register, offset: 0x80 */
    uint32_t GPCHR;                             /**< Global Pin Control High Register, offset: 0x84 */
       uint8_t RESERVED_0[24];
   uint32_t ISFR;                              /**< Interrupt Status Flag Register, offset: 0xA0 */
       uint8_t RESERVED_1[28];
   uint32_t DFER;                              /**< Digital Filter Enable Register, offset: 0xC0 */
   uint32_t DFCR;                              /**< Digital Filter Clock Register, offset: 0xC4 */
   uint32_t DFWR;                              /**< Digital Filter Width Register, offset: 0xC8 */
} PORT_Type, *PORT_MemMapPtr;

/** Peripheral PORTC base address */
#define PORTC_BASE                               (0x4004B000u)
/** Peripheral PORTC base pointer */
#define PORTC                                    ((PORT_Type *)PORTC_BASE)
/** Peripheral PORTD base address */
#define PORTD_BASE                               (0x4004C000u)
/** Peripheral PORTD base pointer */
#define PORTD                                    ((PORT_Type *)PORTD_BASE)

#endif
