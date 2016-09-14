#ifndef BOARD_H
#define BOARD_H

#define F_CPU 8000000UL
#define BAUD 9600

#define UART_USB 0

#include <avr/io.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include <stdlib.h>
#include <string.h>
#include <util/setbaud.h>

#define getbit(port, bit)		((port) &   (1 << (bit)))
#define setbit(port,bit,val)	{if ((val)) {(port)|= (1 << (bit));} else {(port) &= ~(1 << (bit));}}

typedef unsigned char byte;

void board_led_set (byte _state);
void var_delay_ms(int ms);
void var_delay_us(int ms);
byte get_button_up();
byte get_button_left();
byte get_button_right();
byte get_button_down();
byte power_state;
void power_key(unsigned char state);
void board_init();

#endif /* BOARD_H_ */