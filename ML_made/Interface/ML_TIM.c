/* -----------------------------------------------------------------------------
	include
----------------------------------------------------------------------------- */
#include	"ML_TIM.h"

#include	"Common/Control.h"


/* -----------------------------------------------------------------------------
	Local Macro
----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
	Local Variable
----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
	local Structure
----------------------------------------------------------------------------- */
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;


/* -----------------------------------------------------------------------------
	local function
----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
	private function
----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
	public function
----------------------------------------------------------------------------- */
void TIM_Startup(void)
{
	/* TIM3 */
	HAL_TIMEx_HallSensor_Start_IT(&htim3);
	__HAL_TIM_ENABLE_IT(&htim3, TIM_IT_UPDATE);
	
	/* TIM6 */
	HAL_TIM_Base_Start_IT(&htim6);
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	uint32_t cnt_hall = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
	
	Ctr_HallSensorDetection(cnt_hall);
	
	__HAL_TIM_CLEAR_IT(htim, TIM_IT_UPDATE);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/* hall sensor timeout */
	if(htim->Instance==TIM3)
	{
		Ctr_HallSensorTimeout();
	}
	
	/* 10msec */
	if(htim->Instance==TIM6)
	{
		Ctr_ControlMotor();
		Ctr_LogWrite();
	}
}