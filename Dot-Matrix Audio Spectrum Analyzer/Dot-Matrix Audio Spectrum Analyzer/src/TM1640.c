#include "TM1640.h"
#include "fonts.h"


void TM1640_init(unsigned char brightness_level)
{
	TM1640_DIN_set_level(true);
	TM1640_CLK_set_level(true);

	TM1640_send_command(auto_address);
	TM1640_send_command(brightness_level);
	TM1640_clear_display();
}


void TM1640_write(unsigned char value)
{
	unsigned char s = 0x08;

	while(s > 0x00)
	{
		TM1640_CLK_set_level(false);

		if((value & 0x01))
		{
			TM1640_DIN_set_level(true);
		}
		else
		{
			TM1640_DIN_set_level(false);
		}

		TM1640_CLK_set_level(true);

		value >>= 0x01;
		s--;
	}
}


void TM1640_send_command(unsigned char value)
{
	TM1640_DIN_set_level(false);
	TM1640_write(value);
	TM1640_DIN_set_level(true);
}


void TM1640_send_data(unsigned char address, unsigned char value)
{
	TM1640_send_command(fixed_address);
	TM1640_DIN_set_level(false);
	TM1640_write((start_address | (0x0F & address)));
	TM1640_write(value);
	TM1640_DIN_set_level(true);
}


void TM1640_clear_display(void)
{
	unsigned char s = 0x10;

	while(s > 0)
	{
		buffer[s] = 0x00;
		TM1640_send_data(s, 0x00);
		s--;
	}
}


void TM1640_draw_pixel(unsigned char x_pos, unsigned char y_pos, unsigned char state)
{
	switch(state)
	{
		case ON:
		{
			bit_set(buffer[x_pos], y_pos);
			break;
		}
		
		default:
		{
			bit_clr(buffer[x_pos], y_pos);
			break;
		}
	}
	
	TM1640_send_data(x_pos, buffer[x_pos]);
}


void TM1640_draw_line(signed char x1, signed char y1, signed char x2, signed char y2, unsigned char colour)
{
	signed int dx = 0x0000;
	signed int dy = 0x0000;
	signed int stepx = 0x0000;
	signed int stepy = 0x0000;
	signed int fraction = 0x0000;

	dy = (y2 - y1);
	dx = (x2 - x1);

	if (dy < 0)
	{
		dy = -dy;
		stepy = -1;
	}
	else
	{
		stepy = 1;
	}

	if (dx < 0)
	{
		dx = -dx;
		stepx = -1;
	}
	else
	{
		stepx = 1;
	}

	dx <<= 1;
	dy <<= 1;

	TM1640_draw_pixel(x1, y1, colour);

	if(dx > dy)
	{
		fraction = (dy - (dx >> 1));
		while (x1 != x2)
		{
			if(fraction >= 0)
			{
				y1 += stepy;
				fraction -= dx;
			}

			x1 += stepx;
			fraction += dy;

			TM1640_draw_pixel(x1, y1, colour);
		}
	}
	else
	{
		fraction = (dx - (dy >> 1));
		while (y1 != y2)
		{
			if (fraction >= 0)
			{
				x1 += stepx;
				fraction -= dy;
			}

			y1 += stepy;
			fraction += dx;

			TM1640_draw_pixel(x1, y1, colour);
		}
	}
}


void TM1640_draw_rectangle(signed char x1, signed char y1, signed char x2, signed char y2, unsigned char fill, unsigned char colour, unsigned char type)
{
	unsigned short i = 0x00;
	unsigned short xmin = 0x00;
	unsigned short xmax = 0x00;
	unsigned short ymin = 0x00;
	unsigned short ymax = 0x00;

	if(fill != NO)
	{
		if(x1 < x2)
		{
			xmin = x1;
			xmax = x2;
		}
		else
		{
			xmin = x2;
			xmax = x1;
		}

		if(y1 < y2)
		{
			ymin = y1;
			ymax = y2;
		}
		else
		{
			ymin = y2;
			ymax = y1;
		}

		for(; xmin <= xmax; ++xmin)
		{
			for(i = ymin; i <= ymax; ++i)
			{
				TM1640_draw_pixel(xmin, i, colour);
			}
		}
	}

	else
	{
		TM1640_draw_line(x1, y1, x2, y1, colour);
		TM1640_draw_line(x1, y2, x2, y2, colour);
		TM1640_draw_line(x1, y1, x1, y2, colour);
		TM1640_draw_line(x2, y1, x2, y2, colour);
	}

	if(type != SQUARE)
	{
		TM1640_draw_pixel(x1, y1, ~colour);
		TM1640_draw_pixel(x1, y2, ~colour);
		TM1640_draw_pixel(x2, y1, ~colour);
		TM1640_draw_pixel(x2, y2, ~colour);
	}
}


void TM1640_draw_circle(signed char xc, signed char yc, signed char radius, unsigned char fill, unsigned char colour)
{
	signed int a = 0x0000;
	signed int b = 0x0000;
	signed int P = 0x0000;

	b = radius;
	P = (1 - b);

	do
	{
		if(fill != NO)
		{
			TM1640_draw_line((xc - a), (yc + b), (xc + a), (yc + b), colour);
			TM1640_draw_line((xc - a), (yc - b), (xc + a), (yc - b), colour);
			TM1640_draw_line((xc - b), (yc + a), (xc + b), (yc + a), colour);
			TM1640_draw_line((xc - b), (yc - a), (xc + b), (yc - a), colour);
		}
		else
		{
			TM1640_draw_pixel((xc + a), (yc + b), colour);
			TM1640_draw_pixel((xc + b), (yc + a), colour);
			TM1640_draw_pixel((xc - a), (yc + b), colour);
			TM1640_draw_pixel((xc - b), (yc + a), colour);
			TM1640_draw_pixel((xc + b), (yc - a), colour);
			TM1640_draw_pixel((xc + a), (yc - b), colour);
			TM1640_draw_pixel((xc - a), (yc - b), colour);
			TM1640_draw_pixel((xc - b), (yc - a), colour);
		}

		if(P < 0)
		{
			P += (3 + (2 * a++));
		}
		else
		{
			P += (5 + (2 * ((a++) - (b--))));
		}
	}while(a <= b);
}


void TM1640_print_char(unsigned char x_pos, unsigned char y_pos, unsigned char ch)
{
	unsigned char chr = 0x00;
	unsigned char s = 0x00;

	chr = (ch - 0x20);

	if(x_pos > (x_max - 0x06))
	{
		x_pos = 0x00;
		y_pos++;
	}
	
	for(s = 0x00; s < 0x03; s++)
	{
		TM1640_send_data((x_pos + s), ((font_regular[chr][s]) << y_pos));
	}
}


void TM1640_print_string(unsigned char x_pos, unsigned char y_pos, unsigned char *ch)
{
	unsigned char s = 0x00;

	do
	{
		TM1640_print_char(x_pos, y_pos, ch[s++]);
		x_pos += 0x03;
	}while((ch[s] >= 0x20) && (ch[s] <= 0x7F));
}


void TM1640_print_chr(unsigned char x_pos, unsigned char y_pos, signed int value)
{
	unsigned char ch[5] = {' ', ' ', ' ', ' ', '\0'};

	if(value < 0x00)
	{
		value = -value;
		ch[0] = '-';
	}

	if((value > 99) && (value <= 999))
	{
		ch[1] = ((value / 100) + 0x30);
		ch[2] = (((value % 100) / 10) + 0x30);
		ch[3] = ((value % 10) + 0x30);
	}
	else if((value > 9) && (value <= 99))
	{
		ch[1] = (((value % 100) / 10) + 0x30);
		ch[2] = ((value % 10) + 0x30);
	}
	else if((value >= 0) && (value <= 9))
	{
		ch[1] = ((value % 10) + 0x30);
	}
	
	TM1640_print_string(x_pos, y_pos, ch);
}


void TM1640_print_int(unsigned char x_pos, unsigned char y_pos, signed long value)
{
	unsigned char ch[7] = {' ', ' ', ' ', ' ', ' ', ' ', '\0'};

	if(value < 0)
	{
		value = -value;
		ch[0] = '-';
	}

	if(value > 9999)
	{
		ch[1] = ((value / 10000) + 0x30);
		ch[2] = (((value % 10000)/ 1000) + 0x30);
		ch[3] = (((value % 1000) / 100) + 0x30);
		ch[4] = (((value % 100) / 10) + 0x30);
		ch[5] = ((value % 10) + 0x30);
	}

	else if((value > 999) && (value <= 9999))
	{
		ch[1] = (((value % 10000)/ 1000) + 0x30);
		ch[2] = (((value % 1000) / 100) + 0x30);
		ch[3] = (((value % 100) / 10) + 0x30);
		ch[4] = ((value % 10) + 0x30);
	}
	else if((value > 99) && (value <= 999))
	{
		ch[1] = (((value % 1000) / 100) + 0x30);
		ch[2] = (((value % 100) / 10) + 0x30);
		ch[3] = ((value % 10) + 0x30);
	}
	else if((value > 9) && (value <= 99))
	{
		ch[1] = (((value % 100) / 10) + 0x30);
		ch[2] = ((value % 10) + 0x30);
	}
	else
	{
		ch[1] = ((value % 10) + 0x30);
	}

	TM1640_print_string(x_pos, y_pos, ch);
}



