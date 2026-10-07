#include "delay.h"
#include "led.h"
#include "key.h"
#include "usart1.h"
#include "ct511.h"

int main(void) 	
{ 

	USART3_Init(115200);//4G
	Usart1_Init(115200);//调试用的
	delay_nop_ms(500);
	
	/*
	AT+ICCID
	返回 +ICCID:898600521617f0764557
	
	AT+CPIN?  //SIM状态

	返回 +CPIN: READY
	
	AT+CEREG? //网络注册 1表示 已注册本地网络

	返回 +CEREG: 0,1
	
	AT+CGDCONT?
	返回 +CGDCONT: 1,"IP","cmnet","0.0.0.0",0,0  1--PDP上下文编号 IP--协议类型 cmnet--APN名称
	+CGDCONT: 1,"IPV4V6","CMNET.MNC000.MCC460.GPRS","10.212.42.128 254.128.0.0.0.0.0.0.24.219.243.12.150.83.121.42",0,0,,,,
	
	AT+NETOPEN
	
	*/

USART3_SendString("AT+MCONFIG=\"code01\",\"a7idxzrqrkhqkxdm\",\"6MFuxaO3My\"\r\n");

	delay_nop_ms(1000);

USART3_SendString("AT+MIPSTART=\"sh-1-mqtt.iot-api.com\",1883\r\n");

	delay_nop_ms(5000);

USART3_SendString("AT+MCONNECT=1,60\r\n");


	while(1) 
	{ 
			if(USART3_RX_Flag)
			{
					printf("4G:%s\r\n",USART3_RX_BUF);
			
					USART3_RX_Clear();
				
			}
	} 
}

