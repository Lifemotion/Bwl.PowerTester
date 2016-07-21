#include "bwl_uart.h"
#include <stdlib.h>

char uart_send_buffer[32]={};

/*char uart_receive_buffer_0[UART_RECEIVED_BUFFER_LENGTH]={};
char uart_receive_buffer_1[UART_RECEIVED_BUFFER_LENGTH]={};
char uart_receive_buffer_2[UART_RECEIVED_BUFFER_LENGTH]={};
char uart_receive_buffer_3[UART_RECEIVED_BUFFER_LENGTH]={};
unsigned char uart_receive_buffer_pos[4]={0,0,0,0};
		*/
void uart_send_line(unsigned char port,char *string)
{
	uart_send_string(port,string);
	uart_send_string(port,"\r\n");
}

void uart_send_string(unsigned char port,char *string)
{
	unsigned	char  i=0;
	while (string[i]>0)
	{
		uart_send(port,string[i]);
		i++;
	}
}

void uart_send_int(unsigned char port,int val)
{
	itoa(val,uart_send_buffer,10);
	uart_send_string(port,uart_send_buffer);
}

void uart_send_float(unsigned char port,float val, char precision)
{
	dtostrf(val,1,precision,uart_send_buffer);
	uart_send_string(port,uart_send_buffer);
}
/*
void uart_add_receive_buffer(unsigned char port, char byte)
{
	if (port==0){uart_receive_buffer_0[uart_receive_buffer_pos[port]++]=byte;}
	if (port==1){uart_receive_buffer_1[uart_receive_buffer_pos[port]++]=byte;}
	if (port==2){uart_receive_buffer_2[uart_receive_buffer_pos[port]++]=byte;}
	if (port==3){uart_receive_buffer_3[uart_receive_buffer_pos[port]++]=byte;}
}

char uart_receive_line(unsigned char port)
{
	if (uart_received(port))
	{
		unsigned char byte=uart_get(port);
		if ((byte==13)||(byte==10))
		{
			if (uart_receive_buffer_pos[port]>0)
			{
				uart_add_receive_buffer(port,0);
				uart_receive_buffer_pos[port]=0;
				return 1;
			}
		}else
		{
			if (uart_receive_buffer_pos[port]<UART_RECEIVED_BUFFER_LENGTH)
			{
				uart_add_receive_buffer(port,byte);
			}
		}
	}
	return 0;
}


char uart_wait_line(unsigned char port, int time_ms)
{
	long timer_limit=(long)time_ms*100;
	long timer=0;
	do
	{
		if (uart_receive_line(port)>0)
		{
			return 1;
		}
		timer+=1;
		//_delay_us(10);
	}while(timer<timer_limit);
	return 0;
}
*/