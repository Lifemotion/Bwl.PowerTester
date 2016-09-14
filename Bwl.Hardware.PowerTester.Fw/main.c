#define DEV_NAME "BwlPowTst2-FW1.0      "

#include "board/board.h"
#include "refs-avr/winstar1602.h"
#include "refs-avr/strings.h"

#include "relays.h"
#include "sserial.h"
#include "adc.h"

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
	var_delay_ms(10);
	float result=adc_get_voltage();
	set_relay(0);
	return result;
}

void manual_mode()
{
	static int manual_relaycode=0;
	
	if (get_button_up())
	{
		manual_relaycode+=1;
		show_resistanse(manual_relaycode);
		_delay_ms(200);
	}
	
	if (get_button_right())
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
		wdt_reset();
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

void show_device_info()
{
	string_clear();
	string_add_string("Power Tester 2.0 ");
	copy_string_to_line(1);
	string_clear();
	string_add_string((char *)sserial_devname);
	copy_string_to_line(2);
	lcd_writebuffer();
}

int main(void)
{
	start:
	wdt_enable(WDTO_8S);
	board_init();
	sserial_init();
	lcd_init();
	show_device_info();
	
	while(1)
	{
		if (power_state==1)
		{
			
			if (get_button_up())
			{
				automatic_mode(0.9);
			}
			if (get_button_right())
			{
				automatic_mode(0.95);
			}
			if(get_button_down()){
				power_key(0);
			}
		}else
		{
			if (get_button_up())
			{
				goto start;
			}
		}
		wdt_reset();
		sserial_poll_uart(0);
	}
}