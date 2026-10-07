#ifndef __LED_H
#define __LED_H


//资源引入
#include "common.h"

//宏定义实现 LED 灯电平翻转
#define LEDS0_Toggle (GPIOB->ODR ^= (0x1 << 5))
#define LEDS1_Toggle (GPIOE->ODR ^= (0x1 << 5))

 /*
 使用 位带操作 实现 电平翻转
 */
//#define LED0 PBout(5)
//#define LED1 PBout(5)

//函数声明
 /**
 *
 * @brief 用标准库初始化 LED1 灯 
 *		PE5 Green 
 *		PB5 Red
 */
 void LED_Green_Red_Init(void);


 /**
 *
 * @brief LED1 闪烁函数 0.5秒 闪一次
 *
 */
 void LED_Link(void);

#endif
