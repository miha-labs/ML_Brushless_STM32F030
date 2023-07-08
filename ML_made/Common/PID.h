#ifndef PID_H
#define PID_H

/* include */
#include "main.h"


/* Macro */
#define	NEW_PID(kp, ki, kd, ilim)	{ 0, 0, 0, kp, ki, kd, ilim }


/* variables */


/* Structure */
typedef struct
{
	int16_t	prop;		// �΍�
	int32_t	intg;		// �ϕ��l (static)
	int16_t	diff;		// �����l (static)
	int16_t	kp;			// ���Q�C��
	int16_t	ki;			// �ϕ��Q�C��
	int16_t	kd;			// �ϕ��Q�C��
	int32_t	ilim;		// �ϕ�����l
} PID_t;


/* public */
int32_t PID_Control(PID_t *pid);
int16_t PID_DeadBand(int16_t target, int16_t dead_band);


#endif /* PID_H */
