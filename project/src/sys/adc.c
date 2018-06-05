/*
 * adc.c
 *
 *  Created on: 5 iun. 2018
 *      Author: Andrei
 */

#include "adc.h"

void ADC_init(void)  {

  PCC->PCC_ADC0 &=~ PCC_PCCn_CGC_MASK;  /* Disable clock to change PCS */
  PCC->PCC_ADC0 |= 1 << PCC_PCS;     /* PCS=1: Select SOSCDIV2 */
  PCC->PCC_ADC0 |= PCC_PCCn_CGC_MASK;   /* Enable bus clock in ADC */

  ADC0->SC1[0] =0x00001F;         /* ADCH=1F: Module is disabled for conversions*/
                                  /* AIEN=0: Interrupts are disabled */
  ADC0->CFG1 = 1<<2/* | 3<<5*/;       /* ADICLK=0: Input clk=ALTCLK1=SOSCDIV2 */
                                  /* ADIV=0: Prescaler=1 */
                                  /* MODE=1: 12-bit conversion */
  ADC0->CFG2 = 0x000000002;       /* SMPLTS=12(default): sample time is 13 ADC clks */
  ADC0->SC2 = 0x00000000;         /* ADTRG=0: SW trigger */
                                  /* ACFE,ACFGT,ACREN=0: Compare func disabled */
                                  /* DMAEN=0: DMA disabled */
                                  /* REFSEL=0: Voltage reference pins= VREFH, VREEFL */
  ADC0->SC3 = 0x00000000;         /* CAL=0: Do not start calibration sequence */
                                  /* ADCO=0: One conversion performed */
                                  /* AVGE,AVGS=0: HW average function disabled */
}

void convertAdcChan(uint16_t adcChan) {   /* For SW trigger mode, SC1[0] is used */
  //ADC0->SC1[0] &= ~ADC_SC1_ADCH_MASK;	      /* Clear prior ADCH bits */
  ADC0->SC1[0] = adcChan;   /* Initiate Conversion*/
}

uint32_t adc_complete(void)  {
  return (ADC0->SC1[0] & ADC_SC1_COCO); /* Wait for completion */
}

uint32_t read_adc_chx(void)  {
  uint16_t adc_result=0;
  adc_result=ADC0->R[0];      /* For SW trigger mode, R[0] is used */
  return  (uint32_t) ((5000*adc_result)/0xFFF); /* Convert result to mv for 0-5V range */
}
