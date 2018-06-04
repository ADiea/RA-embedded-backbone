/*
 * gpio.h
 *
 *  Created on: May 21, 2018
 *      Author: Andrei Diea
 */

#ifndef GPIO_H_
#define GPIO_H_
#include "S32K144_small.h"

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


/** Peripheral PTD base address */
#define GPIOA_BASE                                 (0x400FF000u)
/** Peripheral PTD base pointer */
#define GPIOA                                      ((GPIO_Type *)GPIOA_BASE)


/** Peripheral PTD base address */
#define GPIOB_BASE                                 (0x400FF040u)
/** Peripheral PTD base pointer */
#define GPIOB                                      ((GPIO_Type *)GPIOB_BASE)


/** Peripheral PTC base address */
#define GPIOC_BASE                                 (0x400FF080u)
/** Peripheral PTC base pointer */
#define GPIOC                                    ((GPIO_Type *)GPIOC_BASE)


/** Peripheral PTD base address */
#define GPIOD_BASE                                 (0x400FF0C0u)
/** Peripheral PTD base pointer */
#define GPIOD                                      ((GPIO_Type *)GPIOD_BASE)


/** Peripheral PTE base address */
#define GPIOE_BASE                                 (0x400FF100u)
/** Peripheral PTD base pointer */
#define GPIOE                                      ((GPIO_Type *)GPIOE_BASE)


/*GPIO Pins*/
/*
 * 18 Pins on PORTA
 * 18 Pins on PORTB
 * 18 Pins on PORTC
 * 18 Pins on PORTD
 * 17 Pins on PORTE
 */

#define GPIO_Pin_0                 0 /*!< Pin 0 selected */
#define GPIO_Pin_1                 1  /*!< Pin 1 selected */
#define GPIO_Pin_2                 2  /*!< Pin 2 selected */
#define GPIO_Pin_3                 3  /*!< Pin 3 selected */
#define GPIO_Pin_4                 4  /*!< Pin 4 selected */
#define GPIO_Pin_5                 5  /*!< Pin 5 selected */
#define GPIO_Pin_6                 6  /*!< Pin 6 selected */
#define GPIO_Pin_7                 7  /*!< Pin 7 selected */
#define GPIO_Pin_8                 8  /*!< Pin 8 selected */
#define GPIO_Pin_9                 9  /*!< Pin 9 selected */
#define GPIO_Pin_10                10  /*!< Pin 10 selected */
#define GPIO_Pin_11                11  /*!< Pin 11 selected */
#define GPIO_Pin_12                12  /*!< Pin 12 selected */
#define GPIO_Pin_13                13  /*!< Pin 13 selected */
#define GPIO_Pin_14                14  /*!< Pin 14 selected */
#define GPIO_Pin_15                15  /*!< Pin 15 selected */
#define GPIO_Pin_16                16  /*!< Pin 16 selected */
#define GPIO_Pin_17                17  /*!< Pin 17 selected */



/** PORT - Size of Registers Arrays */
#define PORT_PCR_COUNT                           32u

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


/* PORT - Peripheral instance base addresses */
/** Peripheral PORTA base address */
#define PORTA_BASE                               (0x40049000u)
/** Peripheral PORTA base pointer */
#define PORTA                                    ((PORT_Type *)PORTA_BASE)

/** Peripheral PORTB base address */
#define PORTB_BASE                               (0x4004A000u)
/** Peripheral PORTB base pointer */
#define PORTB                                    ((PORT_Type *)PORTB_BASE)

/** Peripheral PORTC base address */
#define PORTC_BASE                               (0x4004B000u)
/** Peripheral PORTC base pointer */
#define PORTC                                    ((PORT_Type *)PORTC_BASE)

/** Peripheral PORTD base address */
#define PORTD_BASE                               (0x4004C000u)
/** Peripheral PORTD base pointer */
#define PORTD                                    ((PORT_Type *)PORTD_BASE)

/** Peripheral PORTE base address */
#define PORTE_BASE                               (0x4004D000u)
/** Peripheral PORTE base pointer */
#define PORTE                                    ((PORT_Type *)PORTE_BASE)

/*Interrupt Configuration*/
typedef enum{
	/*ISF flag and DMA request on rising edge */
	eIRQC_DMA_RE = 1,
	/*ISF flag and DMA request on falling edge */
	eIRQC_DMA_FE	= 2,
	/*ISF flag and DMA request on either edge */
	eIRQC_DMA_EE = 3,
	/*ISF flag ad Interrupt when logic 0*/
	eIRQC_L0		= 8,
	/*ISF flag ad Interrupt on rising edge*/
	eIRQC_RE		= 9,
	/*ISF flag ad Interrupt on falling edge*/
	eIRQC_FE		= 10,
	/*ISF flag ad Interrupt on either edge*/
	eIRQC_EE		= 11,
	/*ISF flag ad Interrupt when logic 1*/
	eIRQC_L1		= 12,
	/*All Interrupt Configurations*/
	eIRQC_ALL 	= 15
}eIRQConfig;

#define IRQC 	16
#define ISF		24


/** S32_NVIC - Size of Registers Arrays */
#define S32_NVIC_ISER_COUNT                      4u
#define S32_NVIC_ICER_COUNT                      4u
#define S32_NVIC_ISPR_COUNT                      4u
#define S32_NVIC_ICPR_COUNT                      4u
#define S32_NVIC_IABR_COUNT                      4u
#define S32_NVIC_IP_COUNT                        123u

/** S32_NVIC - Register Layout Typedef */
typedef struct {
		uint32_t ISER[S32_NVIC_ISER_COUNT];         /**< Interrupt Set Enable Register n, array offset: 0x0, array step: 0x4 */
		uint8_t RESERVED_0[112];
		uint32_t ICER[S32_NVIC_ICER_COUNT];         /**< Interrupt Clear Enable Register n, array offset: 0x80, array step: 0x4 */
		uint8_t RESERVED_1[112];
		uint32_t ISPR[S32_NVIC_ISPR_COUNT];         /**< Interrupt Set Pending Register n, array offset: 0x100, array step: 0x4 */
		uint8_t RESERVED_2[112];
		uint32_t ICPR[S32_NVIC_ICPR_COUNT];         /**< Interrupt Clear Pending Register n, array offset: 0x180, array step: 0x4 */
		uint8_t RESERVED_3[112];
		uint32_t IABR[S32_NVIC_IABR_COUNT];         /**< Interrupt Active bit Register n, array offset: 0x200, array step: 0x4 */
		uint8_t RESERVED_4[240];
		uint8_t IP[S32_NVIC_IP_COUNT];              /**< Interrupt Priority Register n, array offset: 0x300, array step: 0x1 */
		uint8_t RESERVED_5[2693];
		uint32_t STIR;                              /**< Software Trigger Interrupt Register, offset: 0xE00 */
} S32_NVIC_Type, *S32_NVIC_MemMapPtr;

 /** Number of instances of the S32_NVIC module. */
#define S32_NVIC_INSTANCE_COUNT                  (1u)

/*NCIV Register map*/
/*    	0xE000E000 - 0xE000E00F. Interrupt Type Register

		0xE000E010 - 0xE000E0FF. System Timer

    	0xE000E100 - 0xE000ECFF. NVIC

    	0xE000ED00 - 0xE000ED8F. System Control Block, including:

        	CPUID

        	System control, configuration, and status

        	Fault reporting

    	0xE000EF00 - 0xE000EF0F. Software Trigger Exception Register

    	0xE000EFD0 - 0xE000EFFF. ID space.*/

/* S32_NVIC - Peripheral instance base addresses */
/** Peripheral S32_NVIC base address */
#define S32_NVIC_BASE                            (0xE000E100u)
/** Peripheral S32_NVIC base pointer */
#define S32_NVIC                                 ((S32_NVIC_Type *)S32_NVIC_BASE)
/** Array initializer of S32_NVIC peripheral base addresses */
#define S32_NVIC_BASE_ADDRS                      { S32_NVIC_BASE }

/*NVIC Regs and Bits for PORTC*/
#define NVIC_PORTC_REGS							 1
/*Interrupt Set-enable bit*/
#define NVIC_PORTC_ISER							29
/*Intrerrupt Clear-enable bit*/
#define NVIC_PORTC_ICER							29
/*Interrupt Set-pending bit*/
#define NVIC_PORTC_ISPR							29
/*Interrupt Clear-pending bit*/
#define NVIC_PORTC_ICPR							29
/*Interrupt Active Bit*/
#define NVIC_PORTC_IABR							29

/*Interrupt Priority Register 4 bits*/
#define NVIC_PORTC_IPR						12

typedef enum{
	ePORTC_IRQ_Nr = 61
}ePeriphIRQNumber;


/*Pin Configuration Mux */
typedef enum{
	eAF_pinDisabled = 0,
	eAF_pinGPIO,
	eAF_pinAF2,
	eAF_pinAF3,
	eAF_pinAF4,
	eAF_pinAF5,
	eAF_pinAF6,
	eAF_pinAF7,
	eAF_pinAFALL = 0x7,
}eAlternateFunc;

typedef enum
{
	ePinDir_Input = 0,
	ePinDir_Output,
} ePinDirection;

/*Lock Register*/
#define PCR_LK			15

/*Pin Mux Control*/
#define PCR_MUX			 8

/*Drive Strength Enable */
#define	PCR_DSR			 6

/*Passive Filter Enable */
#define PCR_PFE			 4

/*Pull Enable*/
#define PCR_PE			 1

/*Pull Select */
#define PCR_PS			 0

typedef enum
{
	ePasFilter_Off,
	ePasFilter_On,
}ePinPasFilter;

/*  Standard GPIO API Definition */

void setPinDirection(GPIO_Type* whichGPIO, uint8_t pinNumber, ePinDirection dir);

void setPinFunction(PORT_Type* whichGPIO, uint8_t pinNumber, eAlternateFunc func);

void setPinPasiveFilter(PORT_Type* whichGPIO, uint8_t pinNumber, ePinPasFilter filter);

void setPinValue(GPIO_Type* whichGPIO, uint8_t pinNumber, uint8_t value);

uint32_t getPinValue(GPIO_Type* whichGPIO, uint8_t pinNumber);


/* GPIO Interrupt API Definition */

void enableSingleInterrupt(PORT_Type* whichGPIO, uint8_t pinNumber, eIRQConfig config );

uint32_t getPinInterruptStatusFlag(PORT_Type* whichGPIO, uint8_t pinNumber);

void clearPinInterruptStatusFlag(PORT_Type* whichGPIO, uint8_t pinNumber);

void enableNVICInterrupt( ePeriphIRQNumber IRQ_NR);

void clearNVICInterrupt( ePeriphIRQNumber IRQ_NR);


#endif /* GPIO_H_ */
