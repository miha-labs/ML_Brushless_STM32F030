/* -----------------------------------------------------------------------------
	include
----------------------------------------------------------------------------- */
#include	"Control.h"
		
#include	"Detection.h"
#include	"Commutation.h"
#include	"PID.h"

#include	"Utility/Log.h"
#include	"Utility/Averaging.h"

#include	"Interface/ML_GPIO.h"
#include	"Interface/ML_PWM.h"


/* -----------------------------------------------------------------------------
	Local Macro
----------------------------------------------------------------------------- */
#define	KP			10
#define	KI			5
#define	ILIM		80000
#define	DEADBAND	50

#define	MAX_DUTY	999
#define	MIN_DUTY	50

#define 	NEW_CTR	{ROT_NOTDET, 0,0}


/* -----------------------------------------------------------------------------
	Local Variable
----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
	local Structure
----------------------------------------------------------------------------- */
typedef struct
{
	rot_e		rotation;
	int16_t	current;
	int16_t	speed;
} ctr_s;


static ctr_s ctr_pre = NEW_CTR;
static ctr_s ctr_trg = NEW_CTR;


typedef enum
{
	START,
	STOP
} st_e;


/* -----------------------------------------------------------------------------
	local function
----------------------------------------------------------------------------- */
static inline void startRotation(void)
{
	//GPIO_EnableMotorDriver();
	Commutation( ctr_trg.rotation, GPIO_ReadHall() );
}


static inline void stopRotation(void)
{
	Commutation( ctr_trg.rotation, 0 );
	//GPIO_DisableMotorDriver();
}


static inline int16_t absoluteOut(int16_t out)
{
	return out>0? out : -out;
}


static inline int16_t saturationOut(int16_t out)
{
	if(out>MAX_DUTY)	out=MAX_DUTY;
	if(out<MIN_DUTY)	out=0;
	
	return out;
}


/* -----------------------------------------------------------------------------
	private function
----------------------------------------------------------------------------- */
static void controlStartStop(st_e st)
{
	static bool is_start_rot = false;
	
	if( st==START && !is_start_rot )
	{
		is_start_rot = true;
		startRotation();
	}
	
	if( st==STOP && is_start_rot )
	{
		is_start_rot = false;
		stopRotation();
	}
}


static void outputPWM(int16_t out)
{
	out = absoluteOut(out);
	out = saturationOut(out);

	st_e st = STOP;
	
	if( out!=0 )	st = START;
	
	PWMout_SetDuty(out);
	controlStartStop(st);
}


/* -----------------------------------------------------------------------------
	public function
----------------------------------------------------------------------------- */
void Ctr_Startup(void)
{
	stopRotation();
	GPIO_EnableMotorDriver();
	//GPIO_DisableMotorDriver();
}


void Ctr_ControlMotor(void)
{
  /* PID calc */
	static	PID_t		pid = NEW_PID(KP, KI, 0, ILIM);
			int16_t	error = ctr_trg.speed - ctr_pre.speed;
						pid.prop = PID_DeadBand(error, DEADBAND);
						
	if( ctr_trg.speed==0 )
	{
		pid.prop = 0;
		pid.intg = 0;
	}
	
	int16_t out = (int16_t)(PID_Control(&pid)/100);
	//out = ctr_trg.speed;


  /* PWM out */
	if( out>0 )		ctr_trg.rotation = ROT_CW;	/* ���] */
	else if( out<0 )	ctr_trg.rotation = ROT_CCW;	/* �t�] */
	else				ctr_trg.rotation = ROT_FREE;	/* ��~ */
	
	outputPWM(out);
}


void Ctr_SetTargetSpeed(int16_t speed)
{
	ctr_trg.speed = speed;
}


void Ctr_HallSensorDetection(uint32_t cnt_hall)
{
	uint8_t sector		= GPIO_ReadHall();
	Commutation(ctr_trg.rotation, sector);
	
	ctr_pre.rotation	= Det_Rotation(sector);
	ctr_pre.speed		= Ave_Speed( Det_Speed(cnt_hall, ctr_pre.rotation) );
}


void Ctr_HallSensorTimeout(void)
{
	ctr_pre.rotation	= ROT_NOTDET;
	ctr_pre.speed		= 0;
	ctr_pre.current	= 0;
	Ave_InitSpeed(0);
	Ave_InitCurrent(0);
}


void Ctr_CurrentDetection(uint16_t ad_val)
{
	ctr_pre.current = Ave_Current( Det_Current(ad_val) );
}


void Ctr_LogWrite(void)
{
	Log_Write(ctr_pre.speed, ctr_pre.current);
}