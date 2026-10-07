#include "usart1.h"

//函数实现

/**
* @brief 初始化串口usart1 实现数据的收发 用标准库函数
*
* @param brr 波特率
*
*/
void Usart1_Init(u32 brr)
{
	/*
		usart1--APB2
		PA9--TX  复用推挽输出模式
		PA10--RX 浮空输入模式 
	*/
	
	GPIO_InitTypeDef GPIO_InitStructure;//引脚结构体
	USART_InitTypeDef Usart1_InitStructure;//串口1模式信息结构体
	
	/*
	1.开启时钟
	*/
	//RCC 时钟使能  USART1在总线APB2上 GPIOA 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//打开 GPIOA 时钟 的标准库函数
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//打开 USART1串口 时钟
	
	/*
	2.配置端口引脚
	*/
	//配置端口引脚模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//引脚9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;//速度
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出模式
	GPIO_Init(GPIOA, &GPIO_InitStructure);//引脚初始化函数
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//引脚10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入模式
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	/*3.配置串口1
	1.数据格式 8N1
	2.禁止校验
	设置波特率
	3.发送使能
	4.接收使能
	5.使能 USART1
	*/
	//配置串口 USART1 模式

	Usart1_InitStructure.USART_WordLength = USART_WordLength_8b;//8个数据位
	Usart1_InitStructure.USART_BaudRate = brr;//用户提供的波特率
	Usart1_InitStructure.USART_StopBits = USART_StopBits_1;//1个停止位 我们的串口里只能用1个停止位  0.5 1.5 2 需要用到的比如 红外
	Usart1_InitStructure.USART_Parity = USART_Parity_No;//无校验位 为什么现在都不用了 因为有些出错检验不出来
	Usart1_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//接收/发送使能
	Usart1_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件流控
	USART_Init(USART1,&Usart1_InitStructure);//串口配置模式初始化标准库函数
	
	/*
	4.开启USART1 中断 用于接收和发送
	*/
	//接收数据寄存器非空中断 有数据时 RXNE = 1  SET 是非空  RESET 是空
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	/*5.优先级注册和配置优先级，在main()中进行分组
	开启中断后还需要对NVIC进行配置 有两种写法
	*/
	//标准库写法
	NVIC_InitTypeDef NVIC_InitStructure;//优先级结构体
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; //
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //占先
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //子先
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//寄存器写法
	/*
	 NVIC_SetPriority(USART3_IRQn,6);
	 NVIC_EnableIRQ(USART3_IRQn);
	*/
		
	//串口开启！！
	USART_Cmd(USART1,ENABLE);//串口使能标准库函数
}

/*
中断服务函数
告诉CPU产生中断时应该进入哪个函数
*/
void USART1_IRQHandler(void)
{
	u8 data;
	
	/*
	判断是不是 RXNE 中断
	*/
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)//接收寄存器此时有数据
	{
		//读取接收到的数据 
		data = USART_ReceiveData(USART1);
		
		//原样发回去
		USART1_SendByte(data);
		
		/*
		【最重要】清标志位
		建议不要用标准库函数去清标志位
		去看寄存器手册该怎么清
		*/
		//不是必须的 因为 RXNE 标志位清除就是 读DR数据寄存器 上面data 已经读完了
		//USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
	
	
}

/*
发送函数
*/
void USART1_SendByte(u8 byte)
{
	//先判断上一个数据是否发送完成 即等待发送数据寄存器为空
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)== RESET);
	//写入发送数据寄存器
	USART_SendData(USART1,byte);
	//等待发送完成
	//while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

void USART1_SendString(char *str)
{
	while(*str)
	{
		USART1_SendByte(*str);
		str++;	
	}
}

void USART1_SendBuffer(u8 *buffer, u16 len)
{
		while (len--)
	{
		USART1_SendByte(*buffer);
		buffer += 1;
	}
}

/*
接收函数 
加上中断后就不需要了
*/


//USART1 接收一个字节
uint8_t  USART1_ReceiveByte(void)
{
		u8 data;
		//等待接收数据寄存器非空
		while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==RESET);
	
		//读取接收到的数据
		data = USART_ReceiveData(USART1);
	
	  return data;
} 

// 重定向 printf 到 USART1
int fputc(int ch, FILE *f)
{
    USART1_SendByte((u8)ch);
    return ch;
}

