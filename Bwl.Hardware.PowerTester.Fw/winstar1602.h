#pragma once

#include "board/board.h"

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