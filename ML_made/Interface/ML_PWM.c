/* -----------------------------------------------------------------------------
	include
----------------------------------------------------------------------------- */
#include	"ML_PWM.h"


/* -----------------------------------------------------------------------------
	Local Macro
----------------------------------------------------------------------------- */
#define	PWMTIM		htim1


/* -----------------------------------------------------------------------------
	Local Variable
----------------------------------------------------------------------------- */
extern	TIM_HandleTypeDef		PWMTIM;


/* -----------------------------------------------------------------------------
	local Structure
----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
	local function
----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
	private function
----------------------------------------------------------------------------- */
static void SetOCMode(ch_e ch, uint32_t mode)
{
	assert( IS_TIM_PWM_MODE(mode) || IS_TIM_OC_MODE(mode) );

	switch(ch)
	{
		case CH_U:
			PWMTIM.Instance->CCMR1 &= ~TIM_CCMR1_OC1M_Msk;
			PWMTIM.Instance->CCMR1 |= ( mode<<0 );
			break;
			
		case CH_V:
			PWMTIM.Instance->CCMR1 &= ~TIM_CCMR1_OC2M_Msk;
			PWMTIM.Instance->CCMR1 |= ( mode<<8 );
			break;
			
		case CH_W:
			PWMTIM.Instance->CCMR2 &= ~TIM_CCMR2_OC3M_Msk;
			PWMTIM.Instance->CCMR2 |= ( mode<<0 );
			break;

		default:
			assert(0);
			break;
	}
}


/* -----------------------------------------------------------------------------
	public function
----------------------------------------------------------------------------- */

/*---------------------
 * ハイサイド出力 : Lo
 * ローサイド出力 : Lo
---------------------*/
void PWMout_LO_LO(ch_e ch)
{
	SetOCMode( ch, TIM_OCMODE_FORCED_INACTIVE );
	
	HAL_TIMEx_PWMN_Stop(&PWMTIM, ch);
	HAL_TIM_PWM_Stop(&PWMTIM, ch);
}

/*---------------------
 * ハイサイド出力 : Lo
 * ローサイド出力 : Hi
---------------------*/
void PWMout_LO_HI(ch_e ch)
{
	SetOCMode( ch, TIM_OCMODE_FORCED_ACTIVE );
	
	HAL_TIMEx_PWMN_Stop(&PWMTIM, ch);
	HAL_TIM_PWM_Start(&PWMTIM, ch);
}

/*---------------------
 * ハイサイド出力 : Hi
 * ローサイド出力 : Lo
---------------------*/
void PWMout_HI_LO(ch_e ch)
{
	SetOCMode( ch, TIM_OCMODE_FORCED_ACTIVE );
	
	HAL_TIMEx_PWMN_Start(&PWMTIM, ch);
	HAL_TIM_PWM_Stop(&PWMTIM, ch);
}

/*---------------------
 * ハイサイド出力 : PWM
 * ローサイド出力 : Lo
---------------------*/
void PWMout_PP_LO(ch_e ch)
{
	SetOCMode( ch, TIM_OCMODE_PWM1 );
	
	HAL_TIMEx_PWMN_Start(&PWMTIM, ch);
	HAL_TIM_PWM_Stop(&PWMTIM, ch);
}

/*---------------------
 * ハイサイド出力 : Lo
 * ローサイド出力 : PWM
---------------------*/
void PWMout_LO_PP(ch_e ch)
{
	SetOCMode( ch, TIM_OCMODE_PWM1 );
	
	HAL_TIMEx_PWMN_Stop(&PWMTIM, ch);
	HAL_TIM_PWM_Start(&PWMTIM, ch);
}

/*---------------------
 * ハイサイド出力 : PWM(補相)
 * ローサイド出力 : PWM
---------------------*/
void PWMout_PN_PP(ch_e ch)
{
	SetOCMode( ch, TIM_OCMODE_PWM1 );
	
	HAL_TIMEx_PWMN_Start(&PWMTIM, ch);
	HAL_TIM_PWM_Start(&PWMTIM, ch);
}

/*---------------------
 * ハイサイド出力 : PWM
 * ローサイド出力 : PWM(補相)
---------------------*/
void PWMout_PP_PN(ch_e ch)
{
	SetOCMode( ch, TIM_OCMODE_PWM2 );
	
	HAL_TIMEx_PWMN_Start(&PWMTIM, ch);
	HAL_TIM_PWM_Start(&PWMTIM, ch);
}

/*---------------------
 * Duty比設定
---------------------*/
void PWMout_SetDuty(uint16_t duty)
{
	__HAL_TIM_SetCompare(&PWMTIM, CH_U, duty);
	__HAL_TIM_SetCompare(&PWMTIM, CH_V, duty);
	__HAL_TIM_SetCompare(&PWMTIM, CH_W, duty);
}


bool PWMout_IsCountUp(void)
{
	return (PWMTIM.Instance->CR1 & TIM_CR1_DIR) == TIM_COUNTERMODE_UP;
}