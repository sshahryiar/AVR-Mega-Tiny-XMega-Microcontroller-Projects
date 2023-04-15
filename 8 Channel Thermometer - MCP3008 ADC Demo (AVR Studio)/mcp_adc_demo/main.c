#include <xc.h>
#include <util/delay.h>
#include "lcd.h"
#include "MCP3008.h"


void setup(void);
void lcd_print_value(uint8_t x_pos, uint8_t y_pos, int16_t value);


int main(void)
{
    int16_t T_value = 0x00000;
	
	char txt1[5] = {"CH0:"};
	char txt2[5] = {"CH1:"};
	char txt3[5] = {"CH2:"};
	char txt4[5] = {"CH3:"};		
	char txt5[5] = {"CH4:"};
	char txt6[5] = {"CH5:"};
	char txt7[5] = {"CH6:"};
	char txt8[5] = {"CH7:"};
	
	setup();
	
	LCD_init();
	LCD_clear_home();
	MCP3008_init();
	
	LCD_goto(0, 0);
	LCD_putstr(txt1);
	LCD_goto(0, 1);
	LCD_putstr(txt2);
	LCD_goto(0, 2);
	LCD_putstr(txt3);
	LCD_goto(0, 3);
	LCD_putstr(txt4);	
	LCD_goto(11, 0);
	LCD_putstr(txt5);
	LCD_goto(11, 1);
	LCD_putstr(txt6);
	LCD_goto(11, 2);
	LCD_putstr(txt7);
	LCD_goto(11, 3);
	LCD_putstr(txt8);
	
	while(1)
    {
		T_value = MCP3008_read(MCP3008_S_CH0, MCP3008_SINGLE_MODE);
		lcd_print_value(4, 0, (T_value >> 1));
		
		T_value = MCP3008_read(MCP3008_S_CH1, MCP3008_SINGLE_MODE);
		lcd_print_value(4, 1, (T_value >> 1));
		
		T_value = MCP3008_read(MCP3008_S_CH2, MCP3008_SINGLE_MODE);
		lcd_print_value(4, 2, (T_value >> 1));

		T_value = MCP3008_read(MCP3008_S_CH3, MCP3008_SINGLE_MODE);
		lcd_print_value(4, 3, (T_value >> 1));
		
		T_value = MCP3008_read(MCP3008_S_CH4, MCP3008_SINGLE_MODE);
		lcd_print_value(15, 0, (T_value >> 1));

		T_value = MCP3008_read(MCP3008_S_CH5, MCP3008_SINGLE_MODE);
		lcd_print_value(15, 1, (T_value >> 1));

		T_value = MCP3008_read(MCP3008_S_CH6, MCP3008_SINGLE_MODE);
		lcd_print_value(15, 2, (T_value >> 1));

		T_value = MCP3008_read(MCP3008_S_CH7, MCP3008_SINGLE_MODE);
		lcd_print_value(15, 3, (T_value >> 1));
		
		_delay_ms(100);
    };
}


void setup(void)
{
	PORTA = 0x00;
	DDRA = 0xF0;
	PORTB = 0x00;
	DDRB = 0xB0;
	PORTC = 0x00;
	DDRC = 0xE0;
	PORTD = 0x00;
	DDRD = 0x00;
	PORTE = 0x00;
	DDRE = 0x00;
	TCCR0 = 0x00;
	TCNT0 = 0x00;
	OCR0 = 0x00;
	TCCR1A = 0x00;
	TCCR1B = 0x00;
	TCNT1H = 0x00;
	TCNT1L = 0x00;
	ICR1H = 0x00;
	ICR1L = 0x00;
	OCR1AH = 0x00;
	OCR1AL = 0x00;
	OCR1BH = 0x00;
	OCR1BL = 0x00;
	MCUCR = 0x00;
	EMCUCR = 0x00;
	TIMSK = 0x00;
	UCSRB = 0x00;
	ACSR = 0x80;
	SPCR = 0x51;
	SPSR = 0x00;
}


void lcd_print_value(uint8_t x_pos, uint8_t y_pos, int16_t value)
{
	char ch[6] = {0x20, 0x20, 0x20, 0x20, 0x20, '\0'};

	if(value < 0)
	{
		ch[0] = 0x2D;
		value = -value;
	}
	else
	{
		ch[0] = 0x20;
	}

	if((value > 999) && (value <= 9999))
	{
		ch[1] = (((value % 10000)/ 1000) + 0x30);
		ch[2] = (((value % 1000) / 100) + 0x30);
		ch[3] = (((value % 100) / 10) + 0x30);
		ch[4] = ((value % 10) + 0x30);
	}
	else if((value > 99) && (value <= 999))
	{
		ch[1] = 0x20;
		ch[2] = (((value % 1000) / 100) + 0x30);
		ch[3] = (((value % 100) / 10) + 0x30);
		ch[4] = ((value % 10) + 0x30);
	}
	else if((value > 9) && (value <= 99))
	{
		ch[1] = 0x20;
		ch[2] = 0x20;
		ch[3] = (((value % 100) / 10) + 0x30);
		ch[4] = ((value % 10) + 0x30);
	}
	else
	{
		ch[1] = 0x20;
		ch[2] = 0x20;
		ch[3] = 0x20;
		ch[4] = ((value % 10) + 0x30);
	}

	LCD_goto(x_pos, y_pos);
	LCD_putstr(ch);
}