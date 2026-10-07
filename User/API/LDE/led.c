#include "led.h"

//下面放函数实现


/*
用标准库实现闪烁灯
*/
 void LED_Green_Red_Init(void)
{
	//声明GPIOE GPIOB 初始化结构体变量 
	GPIO_InitTypeDef GPIOE_information;
	GPIO_InitTypeDef GPIOB_Information;
	
	//1.时钟使能 RCC PE5 在LIB 标准库 中的 stm32f10x_rcc.h stm32f10x_rcc.c 中 但一般看 .h (从下往上找) 跳转到 .c 因为 .c 函数太多了
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//使能端口E
	//时钟使能 RCC PB5
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	
	//2.配置LED1 PE5 引脚模式 stm32f10x_gpio.h 里面模式是一个结构体
	GPIOE_information.GPIO_Pin =GPIO_Pin_5;//配置引脚为 5
	GPIOE_information.GPIO_Speed = GPIO_Speed_10MHz;//速度为 10 MHz
	GPIOE_information.GPIO_Mode =GPIO_Mode_Out_PP ;// 模式为 通用推挽输出
	//模式配置LED1 PE5 函数
	GPIO_Init(GPIOE,&GPIOE_information);
	
	
	//配置LED0 PB5 引脚模式 Red
	//配置结构体
	GPIOB_Information.GPIO_Pin = GPIO_Pin_5;
	GPIOB_Information.GPIO_Speed = GPIO_Speed_10MHz;
	GPIOB_Information.GPIO_Mode = GPIO_Mode_Out_PP;
	//引脚初始化函数
	GPIO_Init(GPIOB,&GPIOB_Information);

	
	//默认是关灯状态 
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
}



 void LED_Link(void)
{
	 //闪烁灯 控制开关灯的原理是 给引脚输出一个电平 还是跟 GPIO 有关
	 
	 //开灯
		LEDS0_Toggle;
		LEDS1_Toggle;

	 //延时 0.5 s
	delay_nop_ms(500);
	 
	 //关灯
		LEDS0_Toggle;
		LEDS1_Toggle;
	 //延时 0.5 s
	delay_nop_ms(500);
}


