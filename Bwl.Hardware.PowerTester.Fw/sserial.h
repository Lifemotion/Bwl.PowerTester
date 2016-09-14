#include "refs-avr/bwl_uart.h"
#include "refs-avr/bwl_simplserial.h"

void sserial_send_start(unsigned char portindex){};//{if (portindex==UART_485)	{DDRB|=(1<<6);PORTB|=(1<<6);}}

void sserial_send_end(unsigned char portindex){};//{if (portindex==UART_485)	{DDRB|=(1<<6);PORTB&=(~(1<<6));}}

void sserial_process_request(unsigned char portindex)
{
	//read buttons
	if (sserial_request.command==1)
	{
		sserial_response.result=128+sserial_request.command;
		sserial_response.datalength=8;
		sserial_send_response();
	}
}

void sserial_init()
{
	uart_init_withdivider(UART_USB,UBRR_VALUE);
	sserial_find_bootloader();
	sserial_set_devname(DEV_NAME);
	sserial_append_devname(16,12,__DATE__);
	sserial_append_devname(27,8,__TIME__);
}
