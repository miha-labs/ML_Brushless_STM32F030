#ifndef ML_ADC_H
#define ML_ADC_H

/* include */
#include "main.h"


/* Macro */


/* variables */


/* Structure */
typedef enum
{
	ADC_CH_U = 0x01,	// bit 1
	ADC_CH_V = 0x02,	// bit 2
	ADC_CH_W = 0x10	// bit 4
} adc_ch_e;


/* public */
void ADC_Startup(void);
void ADC_SetChannel(adc_ch_e ch);


#endif /* ML_ADC_H */
