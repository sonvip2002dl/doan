/*
 * openmv.h
 *
 *  Created on: May 3, 2022
 *      Author: pai3_
 */

#ifndef INC_OPENMV_H_
#define INC_OPENMV_H_

void Openmv_Receive_Data(unsigned char data);
void Openmv_Data(void);
void Openmv_Flag();
void Car_mode_control(void);

extern int openmv[6];            //stm32接收数据数组
extern int OpenMV_RX;          /*OPENMV OpenMV_RX 轴反馈坐标*/
extern int OpenMV_RY;          /*OPENMV OpenMV_RX 轴反馈坐标*/
extern char OpenMV_L;
extern int i;
#endif /* INC_OPENMV_H_ */
