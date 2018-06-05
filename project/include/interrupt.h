/*
 * interrupt.h
 *
 *  Created on: Jun 3, 2018
 *      Author: marius
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "system.h"

#define PORTC_IRQ           61
#define FTM1Reload_IRQ 		110

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

/* S32_NVIC - Peripheral instance base addresses */
/** Peripheral S32_NVIC base address */
#define S32_NVIC_BASE                            (0xE000E100u)
/** Peripheral S32_NVIC base pointer */
#define S32_NVIC                                 ((S32_NVIC_Type *)S32_NVIC_BASE)

/* Specific interrupts sources based on S32K1xx_DMA_Interrupt_mapping.xlsx */

#define NVIC_ISR_REG(isr) ((isr) / 32)
#define NVIC_ISR_OFFSET(isr) ((isr) % 32)

//
void NVIC_enable_IRQ(uint8_t irq, uint8_t prio);

void NVIC_disable_IRQ(uint8_t irq);

void interruptsEnable(void);

inline void interruptsDisable(void);

#endif /* INTERRUPT_H_ */
