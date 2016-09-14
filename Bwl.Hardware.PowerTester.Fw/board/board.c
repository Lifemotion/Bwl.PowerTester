#include "board.h"

void ir_led_set(char state)
{
	/*setbit(DDRB,0,1);
	setbit(PORTB,0,state);*/
}

void ir_modulation_delay()
{
	/*_delay_us(10.5);*/
}

void board_led_set (byte state)
{
	/*setbit(DDRB,1,1);
	setbit(PORTB,1,state);*/
}

void var_delay_ms(int ms)
{
	for (int i=0; i<ms; i++)_delay_ms(1.0);
}

void var_delay_us(int us)
{
	for (int i=0; i<(us/50); i++)_delay_us(50);
}


byte get_button_up()
{
	setbit(DDRD,4,0);
	setbit(PORTD,4,1);
	return getbit(PIND,4)==0;
}

byte get_button_right()
{
	setbit(DDRD,3,0);
	setbit(PORTD,3,1);
	return getbit(PIND,3)==0;
}

byte get_button_down()
{
	setbit(DDRD,5,0);
	setbit(PORTD,5,1);
	return getbit(PIND,5)==0;
}

byte power_state=0;
void power_key(unsigned char state)
{
	setbit(DDRA,5,1);setbit(PORTA,5,state);
	if (state==0)
	{
		DDRA=0; DDRB=0; DDRC=0; DDRD=0;
		PORTA=0; PORTB=0; PORTC=0; PORTD=0;
	}
	power_state=state;
}

void board_init()
{
		power_key(0);
		_delay_ms(200);
		power_key(1);
		get_button_up();
		get_button_right();
		get_button_down();
		_delay_ms(500);
}