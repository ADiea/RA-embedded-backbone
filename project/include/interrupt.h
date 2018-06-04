/*
 * interrupt.h
 *
 *  Created on: Jun 3, 2018
 *      Author: marius
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_
#include "S32K144_small.h"

// NVIC IPR register number for PORTC
#define NVIC_IPR_REG_NR     15
#define PORTC_IRQ           61

typedef struct {
	uint32_t ISER[8];
	uint32_t RESERVED_0[24];
	uint32_t ICER[8];
	uint32_t RESERVED_1[24];
	uint32_t ISPR[8];
	uint32_t RESERVED_2[24];
	uint32_t ICPR[8];
	uint32_t RESERVED_3[24];
	uint32_t IABR[8];
}NVIC_Type;

// NVIC ISER register base
#define NVICISER_base 		(0xE000E100)
#define NVIC				((NVIC_Type *)NVICISER_base)


// NVIC IPR register 1 byte wide
#define NVICIPR_base 		(0xE000E400)
#define NVICIPR				((uint8_t *)NVICIPR_base)


//
void enableInterrupt(uint8_t IRQ);

void disableInterrupt(uint8_t IRQ);

#endif /* INTERRUPT_H_ */
