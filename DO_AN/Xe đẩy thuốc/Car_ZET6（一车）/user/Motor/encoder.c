/*��Ƶ�̳����� https://www.bilibili.com/video/BV1UL411V7XK?p=2&share_source=copy_web*/

#include "encoder.h"
#include "stm32f1xx.h"
#include "tim.h"//����timͷ�ļ�

long g_lMotorPulseSigma =0;//���25ms���ۼ������ܺ�
long g_lMotor2PulseSigma=0;
short g_nMotorPulse=0,g_nMotor2Pulse=0;//ȫ�ֱ����� ������������ֵ




/*******************ʵ������ʱ��ȡ��������ֵ************************/
void GetMotorPulse(void)//��ȡ�������
{
	g_nMotorPulse = (short)(__HAL_TIM_GET_COUNTER(&htim3));//��ȡ������ֵ
	g_nMotorPulse = -g_nMotorPulse;   //�����¿�������������
	__HAL_TIM_SET_COUNTER(&htim3,0);//TIM4����������
	
	g_nMotor2Pulse = (short)(__HAL_TIM_GET_COUNTER(&htim1));//��ȡ������ֵ
	
	g_nMotor2Pulse = g_nMotor2Pulse;  //�����¿������������� 

	
	//Ϊʲôֻ����������ȡ��֮�󣬲�������������PID���ã���Ȼ�ͻ���λ�û�ʧЧ
	//��ʱ��Ҫ�˷�ʱ��ȥ��ԭ��,ֱ�����ڻ����ٶȣ������ֵ�� ��ֵȡ�� �ͺá�
	
	__HAL_TIM_SET_COUNTER(&htim1,0);//TIM2����������
	
	g_lMotorPulseSigma += g_nMotorPulse;//λ���⻷ʹ�õ������ۻ�      //���һ��λ�ÿ���֮��������
	g_lMotor2PulseSigma += g_nMotor2Pulse;//λ���⻷ʹ�õ������ۻ�   //��¼��֮��ҲҪ��ʱ����ѽ������

}
