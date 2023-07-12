#ifndef _usart_H
#define _usart_H

#include "system.h" 
#include "stdio.h" 

extern s8 kxie;
extern u8 k210_t;
extern u8 k210_r;
extern u8 k210_mubiao;
extern u8 ce1;

void Usart1_Init(u32 bound);
void Usart3_Init(u32 bound);
void Uart4_Init(u32 bound);


#endif


