/* -----------------------------------------------------------------------------
	include
----------------------------------------------------------------------------- */
#include	"ML_UART.h"


/* -----------------------------------------------------------------------------
	Local Macro
----------------------------------------------------------------------------- */
#define	UART		huart2
#define	RX_SIZE	3
#define	TX_SIZE	3


/* -----------------------------------------------------------------------------
	Local Variable
----------------------------------------------------------------------------- */
extern	UART_HandleTypeDef		UART;

static	uint8_t	rx_buf[RX_SIZE] = {0};
static	bool		is_rx_cmp = false;



/* -----------------------------------------------------------------------------
	local Structure
----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
	local function
----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
	private function
----------------------------------------------------------------------------- */
static void enableReceiveInterrupt(void)
{
	if( HAL_UART_Receive_IT(&UART, rx_buf, RX_SIZE) != HAL_OK )
	{
		assert(0);
	}
}



/* -----------------------------------------------------------------------------
	public function
----------------------------------------------------------------------------- */
void UART_Startup(void)
{
	enableReceiveInterrupt();
}


void UART_Transmit(uint8_t *buf, uint16_t size)
{
	HAL_UART_Transmit( &huart2, buf, size, 100);
}


bool UART_Receive_3byte(uint8_t *buf)
{
	if(!is_rx_cmp) return false;
	is_rx_cmp = false;
	
	for (uint8_t i = 0; i < RX_SIZE; i++)
	{
		buf[i] = rx_buf[i];
	}
	
	enableReceiveInterrupt();
	
	return true;
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	is_rx_cmp = true;
	
	HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
}