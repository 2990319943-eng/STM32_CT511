#ifndef _CT511_H_
#define _CT511_H_

#include "stm32f10x.h"
#include "common.h"

#define CT511_REV_BUFF_SIZE 256

typedef struct
{
	u8 rev_buf[CT511_REV_BUFF_SIZE ];
	u16 rev_count;
	u8 rev_flag;
}CT511_CODE;

extern CT511_CODE ct511_rev;

/* USART3接收相关变量 */
extern volatile u8 USART3_RX_BUF[CT511_REV_BUFF_SIZE];
extern volatile u8 USART3_RX_COUNT;
extern volatile u8 USART3_RX_LINE_COUNT;
extern volatile uint8_t USART3_RX_Flag;
/**
* @brief 初始化串口 USART3 用USART3与4G模块连接进行数据的接收发送
*			配置 PB10(TX) --- 
*					 PB11(RX) ---
*/
void USART3_Init(u32 brr);

void USART3_SendByte(u8 byte);
void USART3_SendString(char *str);

void USART3_RX_Clear(void);
#endif
