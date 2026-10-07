#include "ct511.h"

//CT511_CODE ct511_rev={0,0,0};

/**
* @brief 初始化串口 USART3 用USART3与4G模块连接进行数据的接收发送
*			配置 PB10(TX) 
*					 PB11(RX) 
*/
void USART3_Init(u32 brr)
{
	//参数结构体
	GPIO_InitTypeDef GPIO_InitStructure;	
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	/*
	1.时钟使能 USART3 GPIOB
	*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	/*
	2.配置 PB10 复用推挽输出模式
				 PB11 浮空输入模式
	*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*
	3.配置 USART3 
		波特率  
		数据位
		停止位
		校验位
		流控
	*/
	USART_InitStructure.USART_BaudRate = brr;
	USART_InitStructure.USART_WordLength =USART_WordLength_8b;
	USART_InitStructure.USART_StopBits =USART_StopBits_1;
	USART_InitStructure.USART_Parity =USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode =USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);

	/*
	4.开启USART3 RXNE 接收数据寄存器非空 中断 
	*/
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
	
	/*
	5.配置NVIC
	*/
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
	/*
	6.开启 USART3 ！！！
	*/
	USART_Cmd(USART3, ENABLE);
	
}

/*
中断服务函数
*/ 
volatile u8 USART3_RX_BUF[CT511_REV_BUFF_SIZE]={0};//USART3接收缓冲区
volatile u8 USART3_RX_COUNT =0;//USART3当前接收字节数
volatile u8 USART3_RX_LINE_COUNT = 0;//当前收到多少行
volatile uint8_t USART3_RX_Flag = 0 ;//USART3一帧数据接收完成标志
void USART3_IRQHandler(void)
{
	  uint8_t data;
		//判断接收数据寄存器是否为空 
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        data = USART_ReceiveData(USART3);//读取USART3接收到的数据

        if(USART3_RX_COUNT < CT511_REV_BUFF_SIZE -1)
				{
					USART3_RX_BUF[USART3_RX_COUNT++] = data;
					   /*
             * 保证字符串最后有 '\0'
             */
            USART3_RX_BUF[USART3_RX_COUNT] = '\0';
				}
				
				//检测换行符
				if(data == '\n')
				{
					USART3_RX_LINE_COUNT++;
				}
				if(USART3_RX_LINE_COUNT >=2)
				{
					USART3_RX_Flag =1;
					
				}
    }
}

void USART3_SendByte(u8 byte)
{

	//先判断上一个数据是否发送完成 即等待发送数据寄存器为空
	while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)== RESET);
	
		//写入发送数据寄存器
	USART_SendData(USART3,byte);
	//等待发送完成
	//while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

void USART3_SendString(char *str)
{
	while(*str)
	{
		USART3_SendByte(*str);
		str++;	
	}
}

void USART3_RX_Clear(void)
{
    uint16_t i;

    for(i = 0; i < CT511_REV_BUFF_SIZE; i++)
    {
        USART3_RX_BUF[i] = 0;
    }

    USART3_RX_COUNT = 0;
		
		USART3_RX_LINE_COUNT = 0;
		
    USART3_RX_Flag = 0;
}
