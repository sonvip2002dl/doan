#include "sys.h"
#include "usart.h"	
#include "led.h"	
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F4̽���߿�����
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/6/10
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
 
#if EN_USART2_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	

int adcx,pitch,roll,yaw; 		//ŷ����
int ek_ADC,ek_pre_ADC;
float ek_pitch,ek_roll,ek_yaw;
float ek_pre_pitch,ek_pre_roll,ek_pre_yaw;
float Kp_ADC=32,Kp=20;//PID����
int balance_pitch,balance_roll,balance_yaw,balance_ADC;
u8 Res;
u8 flag=0;
int real_ADC,real_pitch,real_roll,real_yaw;
static u8 a[6];

void uart1_init(u32 bound){
   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
  USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
#if EN_USART1_RX	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif
	
}


void uart3_init(u32 bound){
   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART2ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_USART3); //GPIOD5����ΪUSART1_TX
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_USART3); //GPIOD6����ΪUSART1_RX
	
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOD5��GPIOD6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOC,&GPIO_InitStructure); //��ʼ��PD5��PD6

   //USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART3, &USART_InitStructure); //��ʼ������2
	
  USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���2
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
#if EN_USART2_RX	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//����2�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif
	
}

void transport(void)
{
	int m;
	for(m=2;m<=4;m++)
	{
		if((a[m]&0xf0)==0x0f)
		{
			a[m]=a[m]&0x7f;
			a[m]=-a[m];
		}
	}
}

void Xianfu_Pwm_x(void)
{	
	  int Amplitude=1100;    //===PWM������7200 ������7100
		int Amplitude1=500;	
		if(balance_ADC>Amplitude)  balance_ADC=Amplitude;	
		if(balance_ADC<Amplitude1)  balance_ADC=Amplitude1;	
}

void Xianfu_Pwm_y(void)
{	
	  int Amplitude=2500;    //===PWM������7200 ������7100
		int Amplitude1=500;	
		if(balance_roll>Amplitude)  balance_roll=Amplitude;	
	  if(balance_yaw>Amplitude)  balance_yaw=Amplitude;	
	
		if(balance_roll<Amplitude1)  balance_roll=Amplitude1;	
	  if(balance_yaw<Amplitude1)  balance_yaw=Amplitude1;	
}

void Xianfu_Pwm_pitch(void)
{
	int Amplitude=1800;    //===PWM������7200 ������7100
	int Amplitude1=1000;	
	if(balance_pitch>Amplitude)  balance_pitch=Amplitude;
  if(balance_pitch<Amplitude1)  balance_pitch=Amplitude1;		
}
	

void PD(void)
{
	//��ץ
	  ek_ADC=real_ADC-a[0];
		balance_ADC+=(-Kp_ADC)*(ek_ADC);   //===����ƽ����Ƶĵ��PWM  PD����   kp��Pϵ�� kd��Dϵ�� ;
		Xianfu_Pwm_x();
		TIM_SetCompare4(TIM2,balance_ADC);
		ek_pre_ADC=ek_ADC;
	  real_ADC=a[0];

	//����roll
		/*ek_roll=real_roll-roll;
		balance_roll+=Kp*(ek_roll);   //===����ƽ����Ƶĵ��PWM  PD����   kp��Pϵ�� kd��Dϵ�� 
		Xianfu_Pwm_y();
		TIM_SetCompare4(TIM3,balance_roll);
		ek_pre_roll=ek_roll;
	  real_roll=roll;*/
	
	//����pitch
	  /*ek_pitch=real_pitch-pitch;
		balance_roll+=Kp*(ek_pitch);   //===����ƽ����Ƶĵ��PWM  PD����   kp��Pϵ�� kd��Dϵ�� 
		Xianfu_Pwm_pitch();
		TIM_SetCompare4(TIM3,balance_pitch);
		ek_pre_pitch=ek_pitch;
	  real_pitch=pitch;*/
		
		//�ֱ�
		/*ek_yaw=real_yaw-a[4];
		balance_yaw+=(-Kp)*(ek_yaw);   //===����ƽ����Ƶĵ��PWM  PD����   kp��Pϵ�� kd��Dϵ�� 
		Xianfu_Pwm_y();
		TIM_SetCompare4(TIM3,1500+balance_yaw);
		ek_pre_yaw=ek_yaw;
	  real_yaw=a[4];*/
		
		balance_pitch=1500+pitch*11;
		Xianfu_Pwm_pitch();
		TIM_SetCompare4(TIM3,balance_pitch);	//B1
		
		balance_roll=1500+roll*11;
		Xianfu_Pwm_y();
		TIM_SetCompare3(TIM2,balance_roll);   //B10
		
		balance_yaw=1500+yaw*8;
		Xianfu_Pwm_y();
		TIM_SetCompare3(TIM3,balance_yaw);	//B0
}

void USART3_IRQHandler(void)                	//����2�жϷ������
{
	static u8 i=0;
	
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE))  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{	
		Res =USART_ReceiveData(USART3);//(USART2->DR);	//��ȡ���յ�������
		
		if(Res==0xEE)
		{
			flag=0;
			i=0;
			if(a[1]>128) pitch=a[1]-256;
			else pitch=a[1];
				
			if(a[2]>128) roll=a[2]-256;
			else roll=a[2];
				
			if(a[3]>128) yaw=a[3]-256;
			else yaw=a[3];
				
			//USART_SendData(USART3,yaw);
			PD();
		}
		
		if(flag==1)
		{
		  a[i++]=Res;
		}
		
		if(Res==0xAA)
		{
			flag=1;
		}
	}
} 
#endif	 



