#ifndef _led_H
#define _led_H

#include "system.h"

/*  LED时钟端口、引脚定义 */
#define LED1_PORT 			GPIOA   
#define LED1_PIN 			GPIO_Pin_8
#define LED1_PORT_RCC		RCC_APB2Periph_GPIOA

#define LED2_PORT 			GPIOD   
#define LED2_PIN 			GPIO_Pin_2
#define LED2_PORT_RCC		RCC_APB2Periph_GPIOD

#define LED3_PORT 			GPIOC   
#define LED3_PIN 			GPIO_Pin_1
#define LED3_PORT_RCC		RCC_APB2Periph_GPIOC

#define LED4_PORT 			GPIOC   
#define LED4_PIN 			GPIO_Pin_13
#define LED4_PORT_RCC		RCC_APB2Periph_GPIOC

#define LED5_PORT 			GPIOC   
#define LED5_PIN 			GPIO_Pin_14
#define LED5_PORT_RCC		RCC_APB2Periph_GPIOC


#define LED1 PAout(8)  	
#define LED2 PDout(2) 

#define led_R  PCout(1)	
#define led_Y  PCout(13)	
#define led_G  PCout(14)	


void LED_Init(void);


#endif
