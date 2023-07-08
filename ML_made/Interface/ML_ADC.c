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
	/* (PWM�g���K�[��)AD�ϊ��������荞�� */
	if( !PWMout_IsCountUp() ) return;	// PWM�J�E���g�A�b�v��(OFF)��AD�ϊ����ʂ�ۑ����Ȃ�
	
	
	//HAL_GPIO_WritePin(DEBUG_O_GPIO_Port, DEBUG_O_Pin, GPIO_PIN_SET);
	/* vvv ���荞�ݎ��Ԍv���J�n vvv */
	{
		uint16_t ad_val = (uint16_t)HAL_ADC_GetValue(AdcHandle);
	
		Ctr_CurrentDetection(ad_val);	// �d���l���Z
	}
	/* ^^^ ���荞�ݎ��Ԍv���I�� ^^^ */
	//HAL_GPIO_WritePin(DEBUG_O_GPIO_Port, DEBUG_O_Pin, GPIO_PIN_RESET);
}