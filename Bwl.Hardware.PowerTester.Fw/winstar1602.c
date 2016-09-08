#include "winstar1602.h"

unsigned char lcd_line_1[LCD_LINE_LENGTH]={};
unsigned char lcd_line_2[LCD_LINE_LENGTH]={};

const char charTable[256] = {
	' ',0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
	0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
	0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
	0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
	0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
	0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
	0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
	0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
	0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
	0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA2,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
	0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB5,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
	0x41,0xA0,0x42,0xA1,0xE0,0x45,0xA3,0xA4,0xA5,0xA6,0x4B,0xA7,0x4D,0x48,0x4F,0xA8,
	0x50,0x43,0x54,0xA9,0xAA,0x58,0xE1,0xAB,0xAC,0xE2,0xAD,0xAE,0x62,0xAF,0xB0,0xB1,
	0x61,0xB2,0xB3,0xB4,0xE3,0x65,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0x6F,0xBE,
0x70,0x63,0xBF,0x79,0xE4,0x78,0xE5,0xC0,0xC1,0xE6,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7};

void _lcd_write(char rs, unsigned char byte, char repeatfirst)
{
	setbit(RS_PORT,RS_PIN,1);setbit(RS_PORT, RS_PIN, rs);//rs 0-instr 1-data
	setbit(E_PORT, E_PIN, 1);setbit(E_PORT, E_PIN, 0);//e
	
	setbit(D7_PORT, D7_PIN,1); setbit(D7_PORT, D7_PIN,byte&128);//d7
	setbit(D6_PORT, D6_PIN,1); setbit(D6_PORT, D6_PIN,byte&64);
	setbit(D5_PORT, D5_PIN,1); setbit(D5_PORT, D5_PIN,byte&32);
	setbit(D4_PORT, D4_PIN,1); setbit(D4_PORT, D4_PIN,byte&16);
	
	_delay_us(LCD_DELAY_PULSE);
	setbit(E_PORT, E_PIN, 1);//e
	_delay_us(LCD_DELAY_PULSE);
	setbit(E_PORT, E_PIN, 0);//e
	_delay_us(LCD_DELAY_PULSE);
	
	if (repeatfirst)
	{
	setbit(D7_PORT, D7_PIN,1); setbit(D7_PORT, D7_PIN,byte&128);//d7
	setbit(D6_PORT, D6_PIN,1); setbit(D6_PORT, D6_PIN,byte&64);
	setbit(D5_PORT, D5_PIN,1); setbit(D5_PORT, D5_PIN,byte&32);
	setbit(D4_PORT, D4_PIN,1); setbit(D4_PORT, D4_PIN,byte&16);
	
		_delay_us(LCD_DELAY_PULSE);
		setbit(E_PORT, E_PIN, 1);//e
		_delay_us(LCD_DELAY_PULSE);
		setbit(E_PORT, E_PIN, 0);//e		
		_delay_us(LCD_DELAY_PULSE);
	}
		
	setbit(DDRD,7,1);setbit(PORTD,7,byte&8);//d3
	setbit(DDRC,0,1);setbit(PORTC,0,byte&4);
	setbit(DDRC,1,1);setbit(PORTC,1,byte&2);
	setbit(DDRC,6,1);setbit(PORTC,6,byte&1);
	
	_delay_us(LCD_DELAY_PULSE);
	setbit(E_PORT, E_PIN, 1);//e
	_delay_us(LCD_DELAY_PULSE);
	setbit(E_PORT, E_PIN, 0);//e
	_delay_us(LCD_DELAY_PULSE);
	
	_delay_us(LCD_DELAY_SYMBOLS);
}

void lcd_setup()
{
	//_lcd_write(0,0b00001000,0);

	//0 0 1 0 0 0 1 0 N F x x
	_lcd_write(0,0b00101000,1);_delay_us(LCD_DELAY_INIT);
	//0 0 0 0 1 D C B on off
	_lcd_write(0,0b00001100,0);_delay_us(LCD_DELAY_INIT);	
	//0 0 0 0 0 0 0 1 clear
	_lcd_write(0,0b00000001,0);_delay_us(LCD_DELAY_INIT);	
	//0 0 0 0 0
	_lcd_write(0,0b00000010,0);_delay_us(LCD_DELAY_INIT);	
	//0 0 0 0 0 1 i/d s/h
	_lcd_write(0,0b00000110,0);_delay_us(LCD_DELAY_INIT);
//_delay_ms(1000);
}

void lcd_init()
{
	_delay_ms(500);
	lcd_setup();
}

void lcd_writebuffer()
{
	//0 0 0 0 0 0 0 1 clear
	_lcd_write(0,0b00000001,0);_delay_us(LCD_DELAY_INIT);
	//0 0 0 0 0
	_lcd_write(0,0b00000010,0);_delay_us(LCD_DELAY_INIT);
	
	for (int i=0; i<LCD_LINE_LENGTH; i++) _lcd_write(1,charTable[lcd_line_1[i]],0);
	
	_lcd_write(0,0b11000000,0);
	for (int i=0; i<LCD_LINE_LENGTH; i++) _lcd_write(1,charTable[lcd_line_2[i]],0);
}
