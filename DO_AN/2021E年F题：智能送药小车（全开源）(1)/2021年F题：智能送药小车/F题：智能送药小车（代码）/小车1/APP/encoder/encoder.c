#include <encoder.h>


void Encoder_Init()
{
	Encoder_Init_Tim3();
	Encoder_Init_Tim4();
}

void Encoder_Init_Tim3()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;  
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  //��ʱ��3ʱ��
	
	/* GPIO */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;   //�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	//PA6 | PA7
	
	/* ��ʱ�� */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);  //ȱʡ��ʱ���ӽṹ��
	TIM_TimeBaseStructure.TIM_Prescaler=0;  //Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_Period=65535; //�Զ���ת��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //ʱ�ӷ�Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	/* ������ */
	/* ��3��4�����ɾ����Ӽ����� */
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //ʹ�ñ�����ģʽ3
	
	/* �˲� */
	TIM_ICStructInit(&TIM_ICInitStructure);  //ȱʡ��ʱ���ӽṹ��
	TIM_ICInitStructure.TIM_ICFilter=10;  //�˲��� ��ͨ�˲�
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
	TIM_SetCounter(TIM3,0);  //���ö�ʱ��ֵ
	TIM_Cmd(TIM3, ENABLE);   //ʹ�ܶ�ʱ��
}


void Encoder_Init_Tim4()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;  
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  //��ʱ��4ʱ��
	
	/* GPIO */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;   //�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);	//PA6 | PA7
	
	/* ��ʱ�� */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);  //ȱʡ��ʱ���ӽṹ��
	TIM_TimeBaseStructure.TIM_Prescaler=0;  //Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_Period=65535; //�Զ���ת��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //ʱ�ӷ�Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	
	/* ������ */
	/* ��3��4�����ɾ����Ӽ����� */
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);  //ʹ�ñ�����ģʽ3
	
	/* �˲� */
	TIM_ICStructInit(&TIM_ICInitStructure);  //ȱʡ��ʱ���ӽṹ��
	TIM_ICInitStructure.TIM_ICFilter=10;  //�˲��� ��ͨ�˲�
	TIM_ICInit(TIM4,&TIM_ICInitStructure);
	
	TIM_SetCounter(TIM4,0);  //���ö�ʱ��ֵ
	TIM_Cmd(TIM4, ENABLE);   //ʹ�ܶ�ʱ��
}


/* ��ȡ��������ֵ */
short Encoder_Read(int TIMX)
{
	short encoder;
	switch(TIMX)
	{                           /* ��ȡ��ʱ��ֵ */     /* ��ʱ��ֵ���� */
		case 3:  encoder=(short)TIM_GetCounter(TIM3);  TIM_SetCounter(TIM3,0);  break;	
		case 4:  encoder=(short)TIM_GetCounter(TIM4);  TIM_SetCounter(TIM4,0);  break;	
		default: encoder=0;
	}
	return encoder;
}

