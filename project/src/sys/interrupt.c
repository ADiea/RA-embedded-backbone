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

 void NVIC_enable_IRQ (uint8_t irq, uint8_t prio)
 {
  S32_NVIC->ICPR[NVIC_ISR_REG(irq)] = 1 << NVIC_ISR_OFFSET(irq);  /* clr any pending IRQ*/
  S32_NVIC->ISER[NVIC_ISR_REG(irq)] = 1 << NVIC_ISR_OFFSET(irq);  /* enable IRQ */
  S32_NVIC->IP[irq] = prio & 0xF;       						  /* set priority 0-15*/
 }

 void NVIC_disable_IRQ (uint8_t irq)
 {
  S32_NVIC->ICPR[NVIC_ISR_REG(irq)] = 1 << NVIC_ISR_OFFSET(irq);  /* clr any pending IRQ*/
  S32_NVIC->ICER[NVIC_ISR_REG(irq)] = 1 << NVIC_ISR_OFFSET(irq);  /* disable IRQ */
 }

 void interruptsEnable(void)
 {
 	 /*The "memory" clobber makes GCC assume that any memory may be arbitrarily read or written by the asm block,
 	 so will prevent the compiler from reordering loads or stores across it:*/
 	asm volatile ("cpsie i" : : : "memory");
 }

 void interruptsDisable(void)
 {
 	 /*The "memory" clobber makes GCC assume that any memory may be arbitrarily read or written by the asm block,
 	 so will prevent the compiler from reordering loads or stores across it:*/
 	asm volatile ("cpsid i" : : : "memory");
 }
