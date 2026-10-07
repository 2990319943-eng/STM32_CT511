#ifndef __DELAY_H
#define __DELAY_H


//资源引入
#include "stm32f10x.h"
#include "common.h"

//函数声明

/*
函数声明
*/
/**
* @brief 用for循环实现延时
*
*	@param us 延时的毫秒数
*/
void for_delay(uint32_t us);

/**
* @brief：手动设置延时时间 用 _nop 函数实现的
* @param: 要延时的us的数
* @author：MR.Wang
* @attention：手动模拟一个微妙级别的延时
*/
void delay_nop_us(uint32_t us);

/**
* @brief 延时控制函数，延时单位为 ms 毫秒
*
* @param ms 用户提供延时控制对应的时间毫秒数
*/
void delay_nop_ms(u32 ms);


/*
	用定时器实现延时函数
*/

/**
*
* @brief 初始化系统定时器systick  因为在内核内部 系统定时器本身就是内核自带的，是不需要我们自己去编写代码的；
* 			我们直接调用就行
*
*/
void systick_init(void);


/**
*
* @brief 毫秒级延时函数
*
*
*/
void systick_delay_ms(u32 tim);


#endif
