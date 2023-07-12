#ifndef _encoder_h
#define _encoder_h

#include <system.h>

void Encoder_Init(void);
void Encoder_Init_Tim3(void);
void Encoder_Init_Tim4(void);
short Encoder_Read(int TIMX);

#endif
