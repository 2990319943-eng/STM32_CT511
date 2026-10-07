#include "key.h"

	u8 flag =0;
/**
* @brief 用库函数初始化按键 KEY_UP KEY2 KEY1 KEY0
*			KEY_UP 控制 LED0 LED1 翻转
*			KEY0 控制 LED0 翻转
*			KEY1 控制 LED1 翻转
*			KEY2 控制 LED0 LED1 判断flag 如果是1 常亮 如果是0 常灭
*/
void Key_Init_Lib(void)
{ 
	/*
	原理图
	KEY_UP 连着高电平 要想检测引脚的电平变化需要低电平 且要接收 按键带来的电平变化--输入模式
	
	KEY2 KEY1 KEY0 接地  引脚需要高电平
	
	KEY_UP ---- PA0 下拉输入模式
	KEY2 ---- PE2 上拉输入模式
	KEY1 ---- PE3 上拉输入模式
	KEY0 ---- PE4 上拉输入模式
	*/
	
	//RCC 时钟使能 GPIOA GPIOE
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	//配置端口引脚模式

	
	//2.配置模式
	GPIO_InitTypeDef GPIOA0_Information;//存储端口引脚模式信息的结构体（包括 引脚号 速度 GPIO模式）
	GPIO_InitTypeDef GPIOE2_Information;
	GPIO_InitTypeDef GPIOE3_Information;
	GPIO_InitTypeDef GPIOE4_Information;
	
	GPIOA0_Information.GPIO_Pin = GPIO_Pin_0;
	GPIOA0_Information.GPIO_Speed =GPIO_Speed_10MHz;
	GPIOA0_Information.GPIO_Mode =GPIO_Mode_IPD;//下拉输入模式
	
	GPIOE2_Information.GPIO_Pin =GPIO_Pin_2;
	GPIOE2_Information.GPIO_Speed =GPIO_Speed_10MHz;
	GPIOE2_Information.GPIO_Mode =GPIO_Mode_IPU;
	
	GPIOE3_Information.GPIO_Pin =GPIO_Pin_3;
	GPIOE3_Information.GPIO_Speed =GPIO_Speed_10MHz;
	GPIOE3_Information.GPIO_Mode =GPIO_Mode_IPU;//上拉输入模式
	
	GPIOE4_Information.GPIO_Pin =GPIO_Pin_4;
	GPIOE4_Information.GPIO_Speed =GPIO_Speed_10MHz;
	GPIOE4_Information.GPIO_Mode =GPIO_Mode_IPU;//上拉输入模式
	
	GPIO_Init(GPIOA,&GPIOA0_Information);//端口引脚初始化 具体的引脚号 和 对应引脚的结构体
	GPIO_Init(GPIOE,&GPIOE2_Information);
	GPIO_Init(GPIOE,&GPIOE3_Information);
	GPIO_Init(GPIOE,&GPIOE4_Information);
	
}

void Key_Up_Control_LED0_LED1(void)
{
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)== Bit_SET)//检测按键被按下
	{
		delay_nop_us(10000);//消抖
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)== Bit_SET)//按键真的被按下
		{
			//检测到按键被松开
				while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)== Bit_SET);//
				LEDS0_Toggle;
				LEDS1_Toggle;
		}
	}
}

void Key0_Control_LED0(void)
{
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==Bit_RESET)//检测按键被按下
	{
		delay_nop_us(10000);
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==Bit_RESET)//按键真的被按下
		{
			while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==Bit_RESET);
			//使用标准库函数实现电平翻转 PB5
			if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5) == Bit_SET)//如果此时 LED0 PB5引脚电平是高电平 就给它输出一个低电平
			{
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);
			}
			else//否则就给它输出一个高电平
			{
				GPIO_SetBits(GPIOB,GPIO_Pin_5);			
			}		
		}
	}
	
}

void Key1_Control_LED1(void)
{
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==Bit_RESET)//检测按键被按下
	{
		delay_nop_us(10000);
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==Bit_RESET)//按键真的被按下
		{
			while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==Bit_RESET);
			//使用标准库函数实现电平翻转 PB5
			if(GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_5) == Bit_RESET)//如果此时 LED1 PE5引脚电平是低电平 就给它输出一个高电平
			{
			GPIO_SetBits(GPIOE,GPIO_Pin_5);	
			}
			else//否则就给它输出一个高电平
			{
			GPIO_ResetBits(GPIOE,GPIO_Pin_5);				
			}		
		}
	}
	
}

void Key2_Control_LED0_LED1(u8 flag)
{
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==Bit_RESET)
	{
		delay_nop_us(10000);
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==Bit_RESET)//按键真的被按下
		{
			while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==Bit_RESET);
			if(flag)//为1 两个灯常亮
			{
					GPIO_ResetBits(GPIOE,GPIO_Pin_5);
					GPIO_ResetBits(GPIOB,GPIO_Pin_5);
			}
			else//0 两个灯长灭
			{
				GPIO_SetBits(GPIOE,GPIO_Pin_5);
				GPIO_SetBits(GPIOB,GPIO_Pin_5);
			}
		}
	}
	
	
	
}
