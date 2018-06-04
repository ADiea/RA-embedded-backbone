/*
 * interrupt.c
 *
 *  Created on: Jun 3, 2018
 *      Author: marius
 */
#include "interrupt.h"

// enable interrupt by writing 1 to the corresponding ISER bit
// the NVIC registers number used for configuration are given by IRQ div 32
// the particular IRQ's bit location is given by IRQ mod 32
// the NVIC IPR register number is given by IRQ div 4

void enableInterrupt(uint8_t IRQ)
{
	NVIC->ISER[IRQ/32] |= (1 << (IRQ % 32));
}

void disableInterrupt(uint8_t IRQ)
{
	NVIC->ICER[IRQ/32] |= (1 << (IRQ % 32));

}
