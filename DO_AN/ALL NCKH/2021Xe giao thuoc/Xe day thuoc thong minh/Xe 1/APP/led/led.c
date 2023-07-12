#include "led.h"

/*******************************************************************************
* �� �� ��         : LED_Init
* ��������		   : LED��ʼ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����
	
	RCC_APB2PeriphClockCmd(LED1_PORT_RCC|LED2_PORT_RCC|LED3_PORT_RCC|LED4_PORT_RCC|LED5_PORT_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=LED1_PIN;  //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(LED1_PORT,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	GPIO_SetBits(LED1_PORT,LED1_PIN);   //��LED�˿����ߣ�Ϩ������LED
	
	GPIO_InitStructure.GPIO_Pin=LED2_PIN;  //ѡ����Ҫ���õ�IO��
	GPIO_Init(LED2_PORT,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	GPIO_SetBits(LED2_PORT,LED2_PIN);   //��LED�˿����ߣ�Ϩ������LED
	
	GPIO_InitStructure.GPIO_Pin=LED3_PIN;  //ѡ����Ҫ���õ�IO��
	GPIO_Init(LED3_PORT,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	GPIO_SetBits(LED3_PORT,LED3_PIN);   //��LED�˿����ߣ�Ϩ������LED
	
	GPIO_InitStructure.GPIO_Pin=LED4_PIN;  //ѡ����Ҫ���õ�IO��
	GPIO_Init(LED4_PORT,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	GPIO_SetBits(LED4_PORT,LED4_PIN);   //��LED�˿����ߣ�Ϩ������LED
	
	GPIO_InitStructure.GPIO_Pin=LED5_PIN;  //ѡ����Ҫ���õ�IO��
	GPIO_Init(LED5_PORT,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	GPIO_SetBits(LED5_PORT,LED5_PIN);   //��LED�˿����ߣ�Ϩ������LED
	
	led_G=led_R=led_Y=0;
}


