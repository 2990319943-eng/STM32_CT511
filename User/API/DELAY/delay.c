#include "delay.h"


/*
函数实现
*/
void for_delay(uint32_t us)
{
	for(uint32_t i = 0 ; i<us ; i++)
	{
		for(uint32_t j = 0 ; j < 72 ;j++)
		{
		
		
		}
	}
}

void delay_nop_us(uint32_t us)
{
	
	/*
	1s=1000ms
	1ms = 1000us
	该103单片机最高是1s 震荡72兆次   完成一次震荡时间是1/72 us
	一个nop大概就是1/72us
	*/
	while(us)//这是1 us
	{
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		
		us --;
	}
}
void delay_nop_ms(u32 ms)
{
	delay_nop_us(ms * 1000);
}

#if 0
/*
定义一个全局计数器变量，用来记录从系统启动以来，SysTick触发了多少次中断
*/
int sys_count = 0;

void systick_init(void)
{
	/**
 * @brief  初始化并启动SysTick计数器及其中断。
 *
 * @param   ticks   两个中断之间的滴答数
 * @return  1 = failed, 0 = successful
 *
 * 初始化系统滴答定时器及其中断，并启动	
 * 系统滴答定时器/计数器在自由运行模式下生成
 * 周期性中断。
 */
//static __INLINE uint32_t SysTick_Config(uint32_t ticks)
//{ 
//  if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);            /* 无法重新加载值 就是你定时的时间超过了最大SysTick重装载数值（重装载数值寄存器位数0~23位） */
//                                                               
//  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      /* 设置重载寄存器 */
//  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* 设置Cortex-M0系统中断的优先级 */
//  SysTick->VAL   = 0;                                          /* 加载 SysTick 计数器值 */
//  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | 
//                   SysTick_CTRL_TICKINT_Msk   | 
//                   SysTick_CTRL_ENABLE_Msk;                    /* 启用SysTick IRQ和SysTick定时器 */
//  return (0);                                                  /* Function successful */
//}

/*
上面就是内核已经实现的系统定时器函数

直接调就好
*/
/*系统时钟---时钟源72mhz 周期 1/72 us
参数：72---我需要72个时钟周期 即1 us  72000就是 1ms
*/
SysTick_Config(72000);//1ms
/*
虽然内核有初始化函数 但是没有实现中断服务函数 这个需要我们自己写
*/
}
/*
这里会出现一个错误 即SysTick_Handler函数重定义 这是因为 在 stm32f10x_it.c 标准库中有一个函数模板
解决办法 注释掉 标准库中的函数（推荐） 或者 注释掉自己的
*/
void SysTick_Handler(void)//每 1ms 触发一次 SysTick_Handler
{
	sys_count++;//每次++ 时间都过去了 1ms
}


void systick_delay_ms(u32 tim)
{
	//把当前  sys_count 的值(即当前的系统毫秒数)保存到局部变量 val 中
	int val = sys_count;
	/*
	val + tim 是 目标时间戳 计算出我希望延时结束时的未来时间戳
	
	循环 不断检查当前时间 sys_count 是否小于目标时间
	*/
	while(sys_count<(val + tim));
	
	//函数返回，实际好事恰好是 tim 毫秒
	
}
#endif
	
