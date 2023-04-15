#include <atmel_start.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <SSD1306.h>
#include <MAX1704x.h>


extern PROGMEM const unsigned char font_regular[92][6];
extern unsigned char buffer[buffer_size];


void init_system(void);
void draw_batt_level(unsigned char bars);


int main(void)
{
	float V = 0.0;
	float SOC = 0.0;
	
	signed char lvl = 0;
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	OLED_init();
	MAX1704x_init();	
	
	init_system();

	/* Replace with your application code */
	while(true) 
	{
		V = MAX1704x_get_cell_voltage();
		SOC = MAX1704x_get_SOC();
		OLED_print_float(36, 6, V, 2);
		OLED_print_float(36, 7, SOC, 1);		

		lvl = (signed char)(SOC * 0.1);		
		
		draw_batt_level(lvl);
		
		_delay_ms(500);
	};
}


void init_system(void)
{
	unsigned char txt1[14] = {"MAX1704x Demo"};
	unsigned char txt2[14] = {"Cell: LiFePO4"};
	unsigned char txt3[6] = {"V/mv:"};
	unsigned char txt4[7] = {"SOC/%:"};
	unsigned char txt5[8] = {"Version"};	
	unsigned char txt6[8] = {"       "};		
	
	unsigned int ver = 0x0000;
	
	
	OLED_print_string(22, 1, txt1);
	
	Draw_Rectangle(111, 62, 126, 30, NO, YES, SQUARE);
	Draw_Rectangle(113, 28, 124, 30, NO, YES, SQUARE);

	OLED_print_string(1, 3, txt5);
	
	ver = MAX1704x_get_version();
	OLED_print_int(1, 4, ver);
	
	for(ver = 0; ver <= 10; ver++)
	{
		draw_batt_level(ver);
		_delay_ms(300);
	}
	
	for(ver = 9; ver > 0; ver--)
	{
		draw_batt_level(ver);
		_delay_ms(300);
	}

	draw_batt_level(10);
	_delay_ms(1000);
	
	OLED_print_string(1, 3, txt6);
	OLED_print_string(1, 4, txt6);
	
	OLED_print_string(1, 3, txt2);
	OLED_print_string(1, 6, txt3);
	OLED_print_string(1, 7, txt4);
}


void draw_batt_level(unsigned char bars)
{
	signed char i = 0x00;
	
	for(i = 9; i >= bars; i--)
	{
		Draw_Rectangle(113, (59 - (3 * i)), 124, (60 - (3 * i)), YES, NO, SQUARE);
	}
	
	for(i = 0; i < bars; i++)
	{
		Draw_Rectangle(113, (59 - (3 * i)), 124, (60 - (3 * i)), YES, YES, SQUARE);
	}
}
