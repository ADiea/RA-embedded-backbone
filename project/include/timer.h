/*
 * timer.h
 *
 *  Created on: May 30, 2018
 *      Author: marius
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "system.h"

// There are 4 FTM, each having 8 channels

/* FTM - Register Layout Typedef */
typedef struct {
	uint32_t SC;
	uint32_t CNT;
	uint32_t MOD;
	uint32_t C0SC;
	uint32_t C0V;
	uint32_t C1SC;
	uint32_t C1V;
	uint32_t C2SC;
	uint32_t C2V;
	uint32_t C3SC;
	uint32_t C3V;
	uint32_t C4SC;
	uint32_t C4V;
	uint32_t C5SC;
	uint32_t C5V;
	uint32_t C6SC;
	uint32_t C6V;
	uint32_t C7SC;
	uint32_t C7V;
	uint32_t CNTIN;
	uint32_t STATUS;
	uint32_t MODE;
	uint32_t SYNC;
	uint32_t OUTINIT;
	uint32_t OUTMASK;
	uint32_t COMBINE;
	uint32_t DEADTIME;
	uint32_t EXTTRIG;
	uint32_t POL;
	uint32_t FMS;
	uint32_t FILTER;
	uint32_t FLTCTRL;
	uint32_t QDCTRL;
	uint32_t CONF;
	uint32_t FLTPOL;
	uint32_t SYNCONF;
	uint32_t INVCTRL;
	uint32_t SWOCTRL;
	uint32_t PWMLOAD;
	uint32_t HCR;
	uint32_t PAIR0DEADTIME;
	uint32_t RESERVED_0;
	uint32_t PAIR1DEADTIME;
	uint32_t RESERVED_1;
	uint32_t PAIR2DEADTIME;
	uint32_t RESERVED_2;
	uint32_t PAIR3DEADTIME;
	uint32_t RESERVED_3[81];
	uint32_t MOD_MIRROR;
	uint32_t C0V_MIRROR;
	uint32_t C1V_MIRROR;
	uint32_t C2V_MIRROR;
	uint32_t C3V_MIRROR;
	uint32_t C4V_MIRROR;
	uint32_t C5V_MIRROR;
	uint32_t C6V_MIRROR;
	uint32_t C7V_MIRROR;

}FTM_Type, *FTM_MemMapPtr;

#define TIMER_CH_SC(timer, channel) (&((timer)->C0SC) + (channel)*2)
#define TIMER_CH_V(timer, channel) (&((timer)->C0V) + (channel)*2)

/* FTM - Timer instance base addresses */
/** Peripheral FTM0 base address **/
#define FTM0_BASE				(0x40038000)
/** Peripheral FTM0 base pointer **/
#define FTM0					((FTM_Type *)FTM0_BASE)

/** Peripheral FTM1 base address **/
#define FTM1_BASE				(0x40039000)
/** Peripheral FTM1 base pointer **/
#define FTM1					((FTM_Type *)FTM1_BASE)

/** Peripheral FTM2 base address **/
#define FTM2_BASE				(0x4003A000)
/** Peripheral FTM2 base pointer **/
#define FTM2					((FTM_Type *)FTM2_BASE)

/** Peripheral FTM3 base address **/
#define FTM3_BASE				(0x40026000)
/** Peripheral FTM3 base pointer **/
#define FTM3					((FTM_Type *)FTM3_BASE)

// -- MODE register --
// define the position of WriteProtection Disable pin in MODE register
#define MODE_WPDIS 2
#define MODE_INIT 1

// -- Status and Control register --
// define the starting position of pins
#define SC_PS     0
#define SC_CLKS   3
#define SC_CPWMS  5
#define SC_RIE    6
#define SC_RF     7
#define SC_TOIE   8
#define SC_TOF    9
#define SC_PWMENn 16
#define SC_FLTPS  24

#define CxSC_MSB 5
#define CxSC_ELSA 2

typedef enum {
	eFTM_CH0 = 0,
	eFTM_CH1,
	eFTM_CH2,
	eFTM_CH3,
	eFTM_CH4,
	eFTM_CH5,
	eFTM_CH6,
	eFTM_CH7
}eFTMChannel;

// Write protection pin modes in MODE register
typedef enum {
	eWP_enabled = 0,
	eWP_disabled

}eWriteProtection;

typedef enum {
	eCS_disabled = 0,
	eCS_FTM_InClk,
	eCS_FixedFreq,
	eCS_ExternClk,
	eCS_ALL = 0x3
}eClockSource;

typedef enum {
	ePF_DivBy1 = 0,
	ePF_DivBy2,
	ePF_DivBy4,
	ePF_DivBy8,
	ePF_DivBy16,
	ePF_DivBy32,
	ePF_DivBy64,
	ePF_DivBy128,
	ePF_ALL = 0x7
}ePrescaleFactor;

typedef enum {
	ePWM_disabled = 0,
	ePWM_enabled
}ePWMoutput;

void setWriteProtection(FTM_Type* whichTimer, eWriteProtection mode);

void selectClockSource(FTM_Type* whichTimer, eClockSource clk);

void selectPrescaleFactor(FTM_Type* whichTimer, ePrescaleFactor factor);

void enablePWMOutput(FTM_Type* whichTimer, eFTMChannel whichChannel, ePWMoutput mode, uint32_t cntin, uint32_t mod);

void setPWMDUty(FTM_Type* whichTimer, eFTMChannel whichChannel, uint32_t duty);

#endif /* TIMER_H_ */
