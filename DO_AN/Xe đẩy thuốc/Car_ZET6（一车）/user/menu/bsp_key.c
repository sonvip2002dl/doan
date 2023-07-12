/*��Ƶ�̳����� https://www.bilibili.com/video/BV1UL411V7XK?p=2&share_source=copy_web   �ǳƣ���ιιι*/

#include "bsp_key.h"
#include "bsp_sys.h"

int iButtonCount;
int iButtonFlag;
char g_nButton;     //�����ⲿ���������������ط����á���ʹ�ö�ʱ��������ʱ�������,�����¼����Ч������ʲô��


int key_3x3_flag=0;
u8 KEY=0;

void KEY_GPIO_Init(void)    //�Լ��Ŷ�������PCB���ϵ����������������ⲿ�жϵķ�ʽŪ��
{
	GPIO_InitTypeDef KEY_Init;
	
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	
	
	KEY_Init.Mode = GPIO_MODE_INPUT;
	KEY_Init.Pin = GPIO_PIN_0 ;
	KEY_Init.Pull =  GPIO_PULLDOWN;
	KEY_Init.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &KEY_Init);
	
	 //PE1�� PEO�޷�����ʹ�ã���������ΪF103ZET6���İ��������������SRAMר�õģ�û�н���IS62WV51216��Ƭѡ�Ļ��������������ò��˵���ͨIOʹ�õģ�
	//һ���ֹ����Ƭѡ�ķ����ǣ� ����Ӧ��Ƭѡ�źŵ����Ÿ���֮������ߵ�ƽ   ��  IS62WV51216 ��Ƭѡ�ź���PG10  
//	KEY_Init.Pin = 	GPIO_PIN_1|	GPIO_PIN_0;
//  KEY_Init.Pull =  GPIO_PULLUP;
//	HAL_GPIO_Init(GPIOE, &KEY_Init);
	
 
	
	KEY_Init.Pin = GPIO_PIN_6 | GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2 ;  //PE1��ʱ�����г�ʼ��
	KEY_Init.Pull =  GPIO_PULLUP;
	HAL_GPIO_Init(GPIOE, &KEY_Init);
	
}

void ButtonScan(void)   //���ö�ʱ������������������Ҳ���ڶ�ʱ���ĸ����жϺ�����
{                       //�ж����������Ƿ���Ч
	switch(KEY_Scan())   
	{
		case(1):  //KEY1
			iButtonCount++;        //sysTick��5ms����һ��ɨ�裬������5ms��һ�Σ�����2����10ms
			if(iButtonCount >= 10)   //�����Ӧ�����жϵĶ�ʱ���ĸ�������Ϊ3ms����ô������ǵñ�������30ms�İ������µĵ�ƽ
			{
				if(iButtonFlag == 0)       //�ж���û���ذ���1Ϊ�У�0Ϊû��
				{
					iButtonCount = 0;
					iButtonFlag = 1;
					g_nButton = 1;
				}
				else iButtonCount = 0; //����ذ������������¼���
			}
			else g_nButton = 0;  //���û���ȶ�����30ms�����ʾû�а��°���
		break;
		
		case(2):  //KEY2
			iButtonCount++;
			if(iButtonCount >= 10)   
			{
				if(iButtonFlag == 0)      
				{
					iButtonCount = 0;
					iButtonFlag = 1;
					
					g_nButton = 2;
				}
				else iButtonCount = 0; 
			}
			else g_nButton = 0;
		break;
		
		case(3):  //K3
			iButtonCount++;
			if(iButtonCount >= 10)   
			{
				if(iButtonFlag == 0)     
				{
					iButtonCount = 0;
					iButtonFlag = 1;
					
					g_nButton = 3;
				}
				else iButtonCount = 0; 
			}
			else g_nButton = 0;  
		break;
	
		default:                   
			iButtonCount = 0;
			iButtonFlag = 0;
		   g_nButton = 0;
		break;
	}
	
}

uint8_t KEY_Scan(void)   //������ް������� 
{
	if(KEY2==0)       return 1;      //�������if  else if  ��Խǰ������ȼ�Խ��
  else if(KEY3==0)  return 2;
	else if(KEY4==0)  return 3;
	
	return 0;   //�ް�������
}

/**
  * ��������: ��ȡ����KEY1��״̬
  * �����������
  * �� �� ֵ: KEY_DOWN�����������£�
  *           KEY_UP  ������û������
  * ˵    �����ޡ�
  */
KEYState_TypeDef KEY0_StateRead(void)
{
  /* ��ȡ��ʱ����ֵ���ж��Ƿ��Ǳ�����״̬������Ǳ�����״̬���뺯���� */
  if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)==KEY0_DOWN_LEVEL)
  {
    /* ��ʱһС��ʱ�䣬�������� */
    HAL_Delay(10);
    /* ��ʱʱ��������жϰ���״̬��������ǰ���״̬˵������ȷʵ������ */
    if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)==KEY0_DOWN_LEVEL)
    {
      /* �ȴ������������˳�����ɨ�躯�� */
      while(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)==KEY0_DOWN_LEVEL);      
       /* ����ɨ����ϣ�ȷ�����������£����ذ���������״̬ */
      return KEY0_DOWN;
    }
  }
  /* ����û�����£�����û������״̬ */
  return KEY0_UP;
}
