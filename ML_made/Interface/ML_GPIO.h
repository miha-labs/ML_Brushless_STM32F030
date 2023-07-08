#ifndef ML_GPIO_H
#define ML_GPIO_H

/* include */
#include "main.h"


/* Macro */


/* variables */


/* Structure */


/* inline */
static inline void GPIO_EnableMotorDriver(void)
{
	HAL_GPIO_WritePin(MD_EN_GPIO_Port, MD_EN_Pin, GPIO_PIN_SET);
}


static inline void GPIO_DisableMotorDriver(void)
{
	HAL_GPIO_WritePin(MD_EN_GPIO_Port, MD_EN_Pin, GPIO_PIN_RESET);
}


/* public */
uint8_t GPIO_ReadHall(void);


#endif /* ML_GPIO_H */
