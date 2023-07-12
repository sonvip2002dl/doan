#ifndef _motion_H
#define _motion_H

#include "system.h"

extern u16 mot;
extern u16 motx;
extern u8 kting;
extern u8  mot1;
extern u8  mot2;
extern u8  mot3;
extern u8  mot4;
extern u8  mot5;

char Moton_Forward(u16 forw,u8 pp);
void Motion_Turn(u8 turn);
void Motion_Spin(u8 spin);
void Motion_Front(void);
void Motion_After(void);
void Motion_Jin(u8 jin);

#endif
