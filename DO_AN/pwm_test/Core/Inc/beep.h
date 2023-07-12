/*
 * beep.c
 *
 *  Created on: Apr 18, 2022
 *      Author: pai3_
 */


#include "stm32f1xx_hal.h"

#define BEEP_ON()      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,GPIO_PIN_SET)
#define BEEP_OFF()     HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,GPIO_PIN_RESET)
#define BEEP_TOGGLE()  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8)



void Delay_us(uint32_t t);
void BBB(uint32_t t);
