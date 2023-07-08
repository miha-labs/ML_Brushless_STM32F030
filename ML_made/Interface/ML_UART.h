#ifndef ML_UART_H
#define ML_UART_H

/* include */
#include "main.h"

/* Macro */


/* variables */


/* Structure */


/* public */
void UART_Startup(void);
void UART_Transmit(uint8_t *buf, uint16_t size);
bool UART_Receive_3byte(uint8_t *buf);


#endif /* ML_UART_H */
