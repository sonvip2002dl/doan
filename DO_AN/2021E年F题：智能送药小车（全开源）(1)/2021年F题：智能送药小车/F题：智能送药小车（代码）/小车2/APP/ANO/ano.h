#ifndef _ano_H
#define _ano_H

#include <system.h>

#define BYET0(x) (unsigned char)(*((char *)(&x)))
#define BYET1(x) (unsigned char)(*((char *)(&x)+1))
#define BYET2(x) (unsigned char)(*((char *)(&x)+2))
#define BYET3(x) (unsigned char)(*((char *)(&x)+3))

// #define BYET0(x) ((x>>0 ) & 0x00ff)
// #define BYET1(x) ((x>>8 ) & 0x00ff)
// #define BYET2(x) ((x>>16) & 0x00ff)
// #define BYET3(x) ((x>>24) & 0x00ff)

void Ano_SenF1(s16 a,u8 b,u8 c);
void Usart1_Send(unsigned char *DataToSend,u8 data_num);

#endif
