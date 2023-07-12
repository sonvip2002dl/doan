#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__

#include "stm32f1xx.h"
#include "gpio.h"

//KEY1,KEY2,KEY3 �ö�ʱ������������ɨ��ķ�����⣬  �����Ķ��ö����ⲿ�жϵķ�ʽŪ�ɡ�  ��һ���K1~K3�Ķ�ʱ��������

#define KEY_UP  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)
#define KEY0   HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4)

#define KEY1   HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_1)
#define KEY2   HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2)
#define KEY3   HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3)

#define KEY4   HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6)
#define KEY5   HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_0)

#define KEY1_PRES 1
#define KEY2_PRES 2
#define KEY3_PRES 3

#define KEY0_DOWN_LEVEL 1

typedef enum
{
  KEY0_UP   = 0,
  KEY0_DOWN = 1,
}KEYState_TypeDef;
 
extern char g_nButton;   //�����ⲿ���������������ط����á���ʹ�ö�ʱ��������ʱ�������,�����¼����Ч������ʲô��
extern int iButtonFlag;  //��¼ȷʵ���������£�����Ч

void KEY_GPIO_Init(void);
uint8_t KEY_Scan(void);

void ButtonScan(void);

KEYState_TypeDef KEY0_StateRead(void);

#endif




