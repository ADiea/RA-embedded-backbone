/*
 * adc.h
 *
 *  Created on: 5 iun. 2018
 *      Author: Andrei
 */

#ifndef ADC_H_
#define ADC_H_

#include "system.h"

/** ADC - Size of Registers Arrays */
#define ADC_SC1_COUNT                            16u
#define ADC_R_COUNT                              16u
#define ADC_CV_COUNT                             2u

/** ADC - Register Layout Typedef */
typedef struct {
   uint32_t SC1[ADC_SC1_COUNT];                /**< ADC Status and Control Register 1, array offset: 0x0, array step: 0x4 */
   uint32_t CFG1;                              /**< ADC Configuration Register 1, offset: 0x40 */
   uint32_t CFG2;                              /**< ADC Configuration Register 2, offset: 0x44 */
   uint32_t R[ADC_R_COUNT];                    /**< ADC Data Result Registers, array offset: 0x48, array step: 0x4 */
   uint32_t CV[ADC_CV_COUNT];                  /**< Compare Value Registers, array offset: 0x88, array step: 0x4 */
   uint32_t SC2;                               /**< Status and Control Register 2, offset: 0x90 */
   uint32_t SC3;                               /**< Status and Control Register 3, offset: 0x94 */
   uint32_t BASE_OFS;                          /**< BASE Offset Register, offset: 0x98 */
   uint32_t OFS;                               /**< ADC Offset Correction Register, offset: 0x9C */
   uint32_t USR_OFS;                           /**< USER Offset Correction Register, offset: 0xA0 */
   uint32_t XOFS;                              /**< ADC X Offset Correction Register, offset: 0xA4 */
   uint32_t YOFS;                              /**< ADC Y Offset Correction Register, offset: 0xA8 */
   uint32_t G;                                 /**< ADC Gain Register, offset: 0xAC */
   uint32_t UG;                                /**< ADC User Gain Register, offset: 0xB0 */
   uint32_t CLPS;                              /**< ADC General Calibration Value Register S, offset: 0xB4 */
   uint32_t CLP3;                              /**< ADC Plus-Side General Calibration Value Register 3, offset: 0xB8 */
   uint32_t CLP2;                              /**< ADC Plus-Side General Calibration Value Register 2, offset: 0xBC */
   uint32_t CLP1;                              /**< ADC Plus-Side General Calibration Value Register 1, offset: 0xC0 */
   uint32_t CLP0;                              /**< ADC Plus-Side General Calibration Value Register 0, offset: 0xC4 */
   uint32_t CLPX;                              /**< ADC Plus-Side General Calibration Value Register X, offset: 0xC8 */
   uint32_t CLP9;                              /**< ADC Plus-Side General Calibration Value Register 9, offset: 0xCC */
   uint32_t CLPS_OFS;                          /**< ADC General Calibration Offset Value Register S, offset: 0xD0 */
   uint32_t CLP3_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register 3, offset: 0xD4 */
   uint32_t CLP2_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register 2, offset: 0xD8 */
   uint32_t CLP1_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register 1, offset: 0xDC */
   uint32_t CLP0_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register 0, offset: 0xE0 */
   uint32_t CLPX_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register X, offset: 0xE4 */
   uint32_t CLP9_OFS;                          /**< ADC Plus-Side General Calibration Offset Value Register 9, offset: 0xE8 */
} ADC_Type, *ADC_MemMapPtr;

 /** Number of instances of the ADC module. */
#define ADC_INSTANCE_COUNT                       (2u)

/* ADC - Peripheral instance base addresses */
/** Peripheral ADC0 base address */
#define ADC0_BASE                                (0x4003B000u)
/** Peripheral ADC0 base pointer */
#define ADC0                                     ((ADC_Type *)ADC0_BASE)
/** Peripheral ADC1 base address */
#define ADC1_BASE                                (0x40027000u)
/** Peripheral ADC1 base pointer */
#define ADC1                                     ((ADC_Type *)ADC1_BASE)

/* SC1 Bit Fields */
#define ADC_SC1_ADCH_MASK                        0x1Fu
#define ADC_SC1_COCO                             (1<<7)

void convertAdcChan(uint16_t);
void ADC_init(void);
uint32_t adc_complete(void);
uint32_t read_adc_chx(void);

#endif /* ADC_H_ */
