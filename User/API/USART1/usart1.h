#ifndef __USART1_H
#define __USART1_H


#include "stm32f10x.h"
#include "common.h"


#define BUFFER_SIZE (256)


/**
* @brief 初始化串口usart1 实现数据的收发 用标准库函数
*
* @param brr 波特率
*
*/
void Usart1_Init(u32 brr);


/**
* @brief USART1 发送一个字节数据函数
*
* @param byte 用户提供一个字节数据
*/
void USART1_SendByte(u8 byte);

/**
* @brief USART1 发送一个字符串数据函数
*
* @param str 用户提供的需要发送的字符串数据
*/
void USART1_SendString(char *str);

/**
* @brief USART1 发送指定内存空间的数据内容，要求用户提供数据
*		空间首地址和对应的字节个数
*
* @param buffer 需要进行发送的内存空间首地址
* @param len    指定发送的字节个数
*/
void USART1_SendBuffer(u8 *buffer, u16 len);


uint8_t  USART1_ReceiveByte(void);



#endif
