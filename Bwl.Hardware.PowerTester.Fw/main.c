#define BAUD 9600

#define DEV_NAME "BwlPowTst1.0      "
#define ADC_ADJ ADC_ADJUST_RIGHT
#define ADC_REF ADC_REFS_INTERNAL_2_56
#define ADC_CLK ADC_PRESCALER_128

#include "board/board.h"
#include "winstar1602.h"
#include "refs-avr/bwl_ir.h"
#include "refs-avr/bwl_uart.h"
#include "refs-avr/bwl_simplserial.h"
#include "refs-avr/bwl_adc.h"
#include "refs-avr/strings.h"

#include <util/setbaud.h>

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
	//all adc
	if (sserial_request.command==12)
	{
		byte count=			sserial_request.data[1];
		adc_init(0,ADC_ADJ,ADC_REF,ADC_CLK);	int result0=adc_read_average(count);
		adc_init(1,ADC_ADJ,ADC_REF,ADC_CLK);	int result1=adc_read_average(count);
		adc_init(2,ADC_ADJ,ADC_REF,ADC_CLK);	int result2=adc_read_average(count);
		adc_init(3,ADC_ADJ,ADC_REF,ADC_CLK);	int result3=adc_read_average(count);
		adc_init(4,ADC_ADJ,ADC_REF,ADC_CLK);	int result4=adc_read_average(count);
		adc_init(5,ADC_ADJ,ADC_REF,ADC_CLK);	int result5=adc_read_average(count);
		adc_init(6,ADC_ADJ,ADC_REF,ADC_CLK);	int result6=adc_read_average(count);
		adc_init(7,ADC_ADJ,ADC_REF,ADC_CLK);	int result7=adc_read_average(count);
		
		sserial_response.result=128+sserial_request.command;
		sserial_response.datalength=16;
		sserial_response.data[0]=result0>>8;
		sserial_response.data[1]=result0&255;
		sserial_response.data[2]=result1>>8;
		sserial_response.data[3]=result1&255;
		sserial_response.data[4]=result2>>8;
		sserial_response.data[5]=result2&255;
		sserial_response.data[6]=result3>>8;
		sserial_response.data[7]=result3&255;
		sserial_response.data[8]=result4>>8;
		sserial_response.data[9]=result4&255;
		sserial_response.data[10]=result5>>8;
		sserial_response.data[11]=result5&255;
		sserial_response.data[12]=result6>>8;
		sserial_response.data[13]=result6&255;
		sserial_response.data[14]=result7>>8;
		sserial_response.data[15]=result7&255;
		sserial_send_response();
	}
}

int main(void)
{
	wdt_enable(WDTO_8S);
	uart_init_withdivider(UART_USB,UBRR_VALUE);
	sserial_find_bootloader();
	sserial_set_devname(DEV_NAME);
	sserial_append_devname(15,12,__DATE__);
	sserial_append_devname(27,8,__TIME__);
	
	//lcd_power_reset();
	lcd_init();
	
	for (int i=0; i<16; i++)
	{
		lcd_line_1[i]='0'+i;
		lcd_line_2[i]='a'+i;
	}
	lcd_writebuffer();
	
	while(1)
	{
		sserial_poll_uart(UART_USB);
		wdt_reset();
	}
}