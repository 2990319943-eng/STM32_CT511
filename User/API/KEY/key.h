#ifndef __KEY_H
#define __KEY_H


//资源引入
#include "common.h"
#include "led.h"


/**
* @brief 用库函数初始化按键 KEY_UP KEY2 KEY1 KEY0
*			KEY_UP 控制 LED0 LED1 翻转
*			KEY0 控制 LED0 翻转
*			KEY1 控制 LED1 翻转
*			KEY2 控制 LED0 LED1 判断flag 如果是1 长亮 如果是0 长灭
*/
void Key_Init(void);


/**
* @brief KEY_UP 控制
*
*
*
*/
void Key_Up_Control_LED0_LED1(void);

void Key0_Control_LED0(void);

void Key1_Control_LED1(void);

void Key2_Control_LED0_LED1(u8 flag);



#endif
