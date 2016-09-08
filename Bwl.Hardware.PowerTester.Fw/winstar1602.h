#pragma once

#include "board/board.h"

#define RS_PORT PORTA
#define D7_PORT PORTD
#define D6_PORT PORTC
#define D5_PORT PORTC
#define D4_PORT PORTC
#define E_PORT PORTC

#define RS_DDR DDRA
#define D7_DDR DDRD
#define D6_DDR DDRC
#define D5_DDR DDRC
#define D4_DDR DDRC
#define E_DDR DDRC

#define D7_PIN 7
#define D6_PIN 0
#define D5_PIN 1
#define D4_PIN 6
#define RS_PIN 7
#define E_PIN 7

//delays in us
#define LCD_DELAY_PULSE 20
#define LCD_DELAY_SYMBOLS 20
#define LCD_DELAY_INIT 100

#define LCD_LINE_LENGTH 16
unsigned char lcd_line_1[LCD_LINE_LENGTH];
unsigned char lcd_line_2[LCD_LINE_LENGTH];

//Call after power-up. lcd_setup contains 500ms startup delay and lcd_setup
void lcd_setup();

//Call to reset and configure display
void lcd_init();

//Call to write buffer (lcd_line_X) to display
void lcd_writebuffer();