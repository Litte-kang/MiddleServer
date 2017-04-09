#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "json.h"
#include "Common.h"
#include "Config.h"
#include "UartApi.h"
#include "Socket.h"
#include "RemoteDataServer.h"

void main()
{
	///*
	if (0 == Rds_Start())
	{
		
	}
	else
	{
		printf("get net config failure\n");
	}
 	//*/
	///*
	//get uart information (baud rate, data bit, parity, stop bit )
	Uart_GetUartConfigInfo();

	//open uart	
	Uart_Open(UART_PORT1);
	Uart_Open(UART_PORT2);

	printf("uart fd:%d,%d\n", g_UartDevInfo[0].m_Fd,g_UartDevInfo[1].m_Fd);
	
	//start uart recieve thread
	Uart_StartRecvThrd(UART_PORT1);
	Uart_StartRecvThrd(UART_PORT2);

	sleep(2);

	{
		uchar rgp1[12] = {0xff,0xfe,0x01,0x01,0x00,0x02,0x00,0x01,0x02};
		uchar rgp2[12] = {0xff,0xfe,0x02,0x01,0x00,0x02,0x00,0x03,0x04};
		ushort crc_code = 0;

		crc_code = CheckCode(rgp1, 9);

		rgp1[9] = (uchar)crc_code;
		rgp1[10] = (uchar)(crc_code >> 8);

		crc_code = CheckCode(rgp2, 9);

		rgp2[9] = (uchar)crc_code;
		rgp2[10] = (uchar)(crc_code >> 8);

		while(1)
		{		
			l_debug(NULL, "send data");	
			Uart_SendData(UART_PORT1, rgp1, 11);
			//sleep(1);
			Uart_SendData(UART_PORT2, rgp2, 11);
			//printf("send hello to uart 1\n");
			sleep(1);
		}
	}
	//*/

	while(1) sleep(1);
}
