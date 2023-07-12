#ifndef _motor_H
#define _motor_H

#include "system.h"

/* ×óÂÖ */
#define AIN1 PCout(5)  
#define AIN2 PCout(4)

/* ÓÒÂÖ */
#define BIN1 PBout(0)  
#define BIN2 PBout(1)

void Motor_Init(u32 per,u16 psc);
void Motor_Motion(int pwm2,int pwm1);
void Motor_Limit(s16 *pwm);

#endif
