#ifndef ML_PWM_H
#define ML_PWM_H

/* include */
#include "main.h"


/* Macro */


/* variables */


/* Structure */
typedef enum
{
	CH_U = TIM_CHANNEL_1,
	CH_V = TIM_CHANNEL_2,
	CH_W = TIM_CHANNEL_3
}ch_e;


/* public */
void PWMout_LO_LO(ch_e ch);
void PWMout_LO_HI(ch_e ch);
void PWMout_HI_LO(ch_e ch);
void PWMout_PP_LO(ch_e ch);
void PWMout_LO_PP(ch_e ch);
void PWMout_PN_PP(ch_e ch);
void PWMout_PP_PN(ch_e ch);
void PWMout_SetDuty(uint16_t duty);
bool PWMout_IsCountUp(void);


#endif /* ML_PWM_H */
