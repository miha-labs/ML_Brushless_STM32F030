/* -----------------------------------------------------------------------------
	include
----------------------------------------------------------------------------- */
#include	"ML_ADC.h"

#include	"Common/Control.h"
#include	"Interface/ML_PWM.h"


/* -----------------------------------------------------------------------------
	Local Macro
----------------------------------------------------------------------------- */
#define	CHSELR_MASK	0x0003FFFFUL


/* -----------------------------------------------------------------------------
	Local Variable
----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
	local Structure
----------------------------------------------------------------------------- */
extern	ADC_HandleTypeDef hadc;


/* -----------------------------------------------------------------------------
	local function
----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
	private function
----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
	public function
----------------------------------------------------------------------------- */
void ADC_Startup(void)
{
	if( HAL_ADCEx_Calibration_Start(&hadc)!=HAL_OK )
	{
		Error_Handler();
	}
	
	if( HAL_ADC_Start_IT(&hadc)!=HAL_OK )
	{
		Error_Handler();
	}
}


void ADC_SetChannel(adc_ch_e ch)
{
	hadc.Instance->CHSELR = ch & CHSELR_MASK;
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *AdcHandle)
{
	/* (PWMトリガー後)AD変換完了割り込み */
	if( !PWMout_IsCountUp() ) return;	// PWMカウントアップ時(OFF)はAD変換結果を保存しない
	
	
	//HAL_GPIO_WritePin(DEBUG_O_GPIO_Port, DEBUG_O_Pin, GPIO_PIN_SET);
	/* vvv 割り込み時間計測開始 vvv */
	{
		uint16_t ad_val = (uint16_t)HAL_ADC_GetValue(AdcHandle);
	
		Ctr_CurrentDetection(ad_val);	// 電流値演算
	}
	/* ^^^ 割り込み時間計測終了 ^^^ */
	//HAL_GPIO_WritePin(DEBUG_O_GPIO_Port, DEBUG_O_Pin, GPIO_PIN_RESET);
}