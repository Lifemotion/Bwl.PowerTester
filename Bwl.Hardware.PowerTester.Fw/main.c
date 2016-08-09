#define BAUD 9600

#define DEV_NAME "BwlPowTst1.0      "
#define ADC_ADJ ADC_ADJUST_RIGHT
#define ADC_REF ADC_REFS_INTERNAL_1_1
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

float adc_get_voltage()
{
	adc_init(4,ADC_ADJ,ADC_REF,ADC_CLK);
	float result0=adc_read_average_float(64);
	float result=result0*1.1/1024.0*69.0;
	return result;
}

float adc_get_current()
{
	adc_init(3,ADC_ADJ,ADC_REF,ADC_CLK);
	float result0=adc_read_average_float(64);
	float result=result0*1.1/1024.0/0.01;
	return result;
}

void power_open(unsigned char state)
{
	setbit(DDRD,4,1);setbit(PORTD,4,state);
}

byte get_button_1()
{
	setbit(DDRD,3,0);
	setbit(PORTD,3,1);
	return getbit(PIND,3)==0;
}

byte get_button_2()
{
	setbit(DDRA,2,0);
	setbit(PORTA,2,1);
	return getbit(PINA,2)==0;
}

byte get_button_3()
{
	setbit(DDRA,1,0);
	setbit(PORTA,1,1);
	return getbit(PINA,1)==0;
}

void copy_string_to_line(char line)
{
	if (line==1)
	{
		for (int i=0; i<16; i++)
		{
			lcd_line_1[i]=string_buffer[i];
		}
	}
	if (line==2)
	{
		for (int i=0; i<16; i++)
		{
			lcd_line_2[i]=string_buffer[i];
		}
	}
	

}

void set_relay(int relay_code)
{
	if (relay_code<0) {relay_code=0;}
	setbit(DDRB,1,1);setbit(PORTB,1,relay_code&1);//200
	setbit(DDRB,2,1);setbit(PORTB,2,relay_code&2);//100
	setbit(DDRB,3,1);setbit(PORTB,3,relay_code&4);//62
	setbit(DDRB,0,1);setbit(PORTB,0,relay_code&8);//32
	setbit(DDRB,5,1);setbit(PORTB,5,relay_code&16);//16
	setbit(DDRB,6,1);setbit(PORTB,6,relay_code&32);//10
	setbit(DDRB,4,1);setbit(PORTB,4,relay_code&64);//4.7
	setbit(DDRA,0,1);setbit(PORTA,0,relay_code&128);//2
	setbit(DDRB,7,1);setbit(PORTB,7,relay_code&256);//1
}

float relay_get_resistance(int relay_code)
{
	float rev_sum=0.0;
	if (relay_code&1) {rev_sum+=1.0/200.0;}
	if (relay_code&2) {rev_sum+=1.0/100.0;}
	if (relay_code&4) {rev_sum+=1.0/62.0;}
	if (relay_code&8) {rev_sum+=1.0/32.0;}
	if (relay_code&16) {rev_sum+=1.0/16.0;}
	if (relay_code&32) {rev_sum+=1.0/10.0;}
	if (relay_code&64) {rev_sum+=1.0/4.7;}
	if (relay_code&128) {rev_sum+=1.0/2.0;}
	if (relay_code&256) {rev_sum+=1.0/1.0;}
	if (rev_sum==0.0)
	{
		return -1;
	}else
	{
		float resistance= 1.0/rev_sum;
		return resistance;
	}
}

void show_voltage_current(float volt, float current)
{
	string_clear();
	string_add_string("Voltage: ");
	string_add_float(volt,2);
	copy_string_to_line(1);
	
	string_clear();
	string_add_string("Current: ");
	string_add_float(current,2);
	copy_string_to_line(2);
	lcd_writebuffer();
}

void show_resistanse(int relay_code)
{
	string_clear();
	string_add_string("R = ");
	if (relay_code==0)
	{
		string_add_string("off");
	}else
	{
		string_add_float(relay_get_resistance(relay_code),1);
		string_add_string(" Ohm");
	}
	copy_string_to_line(1);
	string_clear();
	copy_string_to_line(2);
	lcd_writebuffer();
}

void show_resistanse_voltage_current(float resistance, float voltage)
{
	string_clear();
	string_add_string("R=");
	if (resistance<0)
	{
		string_add_string("off");
	}else
	{
		string_add_float(resistance,1);
	}
	string_add_string(", U=");
	string_add_float(voltage,2);
	copy_string_to_line(1);
	string_clear();
	if (resistance<0)
	{
		string_add_string("I=0 A, P=0 W");
	}else
	{
		string_add_string("I=");
		float curr=voltage/resistance;
		string_add_float(curr,2);
		
		string_add_string(", P=");
		float pow=voltage*curr;
		string_add_float(pow,2);
	}
	copy_string_to_line(2);
	lcd_writebuffer();
}

float meashure_voltage(int relay_code)
{
	set_relay(relay_code);
	float result=adc_get_voltage();
	set_relay(0);
	return result;
}

void manual_mode()
{
	static int manual_relaycode=0;
	
	if (get_button_1())
	{
		manual_relaycode+=1;
		show_resistanse(manual_relaycode);
		_delay_ms(200);
	}
	
	if (get_button_2())
	{
		float volt=meashure_voltage(manual_relaycode);
		float resist=relay_get_resistance(manual_relaycode);
		show_resistanse_voltage_current(resist,volt);
		_delay_ms(200);
	}
	
	/*if (get_button_3())
	{
	manual_relaycode-=1;
	show_resistanse(manual_relaycode);
	_delay_ms(200);
	}*/
}

void automatic_mode(float drop_level)
{
	//initial voltage
	string_clear();
	string_add_string("Auto drop-> ");
	string_add_float(drop_level,2);
	copy_string_to_line(1);
	float init_volt=adc_get_voltage();
	float volt=init_volt;
	float resist=-1;
	string_clear();
	string_add_string("Initial U=");
	string_add_float(init_volt,2);
	string_add_string(" V");
	copy_string_to_line(2);
	lcd_writebuffer();
	_delay_ms(500);
	//increasing load
	int relay=0;
	float last_volt=0.0, last_resist=0.0;
	while ((volt>init_volt*drop_level)&&(relay<500))
	{
		relay++;
		//if (relay>10) relay++;
		if (relay>40) relay++;
		if (relay>60) relay++;
		if (relay>120) relay++;
		if (relay>160) relay++;
		if (relay>200) relay++;
		if (relay>250) relay++;
		if (relay>250) relay++;
		last_volt=volt;
		last_resist=resist;
		show_resistanse_voltage_current(last_resist,last_volt);
		
		//volt=meashure_voltage(relay);
		volt=meashure_voltage(relay);
		volt=meashure_voltage(relay);
		resist=relay_get_resistance(relay);
		_delay_ms(50);
	}
	//float curr=last_volt/last_resist;
	//float pow=last_volt*curr;
		
	float curr=volt/resist;
	float pow=volt*curr;
	if (relay<500)
	{
		string_clear();
		string_add_string("U dropped-> ");
		string_add_float(drop_level,2);
		copy_string_to_line(1);

	}else
	{
		string_clear();
		string_add_string("U NOT drop-> ");
		string_add_float(drop_level,2);
		copy_string_to_line(1);
		string_clear();
	}
	string_clear();
	string_add_string("I=");
	string_add_float(curr,2);
	string_add_string(", P=");
	string_add_float(pow,1);
	copy_string_to_line(2);
	lcd_writebuffer();
}

int main(void)
{
	/*power_open(1);
	set_relay(1);_delay_ms(2000);
	set_relay(2);_delay_ms(2000);
	set_relay(4);_delay_ms(2000);
	set_relay(8);_delay_ms(2000);
	set_relay(16);_delay_ms(2000);
	set_relay(32);_delay_ms(2000);
	set_relay(64);_delay_ms(2000);
	set_relay(128);_delay_ms(2000);
	set_relay(256);_delay_ms(2000);
	set_relay(0);
	*/
	get_button_1();
	get_button_2();
	//wdt_enable(WDTO_8S);
	uart_init_withdivider(UART_USB,UBRR_VALUE);
	sserial_find_bootloader();
	sserial_set_devname(DEV_NAME);
	sserial_append_devname(15,12,__DATE__);
	sserial_append_devname(27,8,__TIME__);
	
	lcd_init();
	power_open(1);
	string_clear();
	string_add_string("Power Tester 1.0 ");
	copy_string_to_line(1);
	lcd_writebuffer();
	
	while(1)
	{
		if (get_button_1())
		{
			automatic_mode(0.9);
		}
		if (get_button_2())
		{
			automatic_mode(0.95);
		}
		wdt_reset();
	}
}