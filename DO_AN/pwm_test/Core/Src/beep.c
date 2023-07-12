/*
 * beep.c
 *
 *  Created on: Apr 18, 2022
 *      Author: pai3_
 *      PA8    蜂鸣器
 */

#include "beep.h"


//毫秒级的延时  不调用HAL_Delay  --- > systick
void Delay_us(uint32_t t)//延时一微秒
{
    int n  =  11;
    while(--t)
    {
        while(--n);
        n = 11;
    }
}

void BBB(uint32_t t)
{
		BEEP_ON();
		Delay_us(t);
		BEEP_OFF();
}
