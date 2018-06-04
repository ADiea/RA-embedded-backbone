/*
 * interrupts.c
 *
 *  Created on: June 04, 2018
 *      Author: Andrei Diea
 */
 
 #include "interrupts.h"
 
 void NVIC_enable_IRQ (uint8_t irq, uint8_t prio) 
 {
  S32_NVIC->ICPR[NVIC_ISR_REG(irq)] = 1 << NVIC_ISR_OFFSET(isr);  /* clr any pending IRQ*/
  S32_NVIC->ISER[NVIC_ISR_REG(irq)] = 1 << NVIC_ISR_OFFSET(isr);  /* enable IRQ */
  S32_NVIC->IP[irq] = prio & 0xF;       						  /* set priority 0-15*/
 }
 
 void NVIC_disable_IRQ (uint8_t irq) 
 {
  S32_NVIC->ICPR[NVIC_ISR_REG(irq)] = 1 << NVIC_ISR_OFFSET(isr);  /* clr any pending IRQ*/
  S32_NVIC->ICER[NVIC_ISR_REG(irq)] = 1 << NVIC_ISR_OFFSET(isr);  /* disable IRQ */
 }
 
 void interruptsEnable()
 {
	 /*The "memory" clobber makes GCC assume that any memory may be arbitrarily read or written by the asm block, 
	 so will prevent the compiler from reordering loads or stores across it:*/
	asm volatile ("cpsie i" : : : "memory");
 }
 
 void interruptsDisable()
 {
	 /*The "memory" clobber makes GCC assume that any memory may be arbitrarily read or written by the asm block, 
	 so will prevent the compiler from reordering loads or stores across it:*/
	asm volatile ("cpsid i" : : : "memory");
 }