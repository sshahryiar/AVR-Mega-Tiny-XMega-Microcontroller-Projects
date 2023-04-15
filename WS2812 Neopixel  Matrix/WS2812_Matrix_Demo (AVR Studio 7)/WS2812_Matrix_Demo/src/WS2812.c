#define F_CPU 16000000UL 


#include "WS2812.h"
#include "SPI.h"
#include <util/delay.h>


void swap(signed int *a, signed int *b)
{
    signed int temp = 0x0000;

    temp = *b;
    *b = *a;
    *a = temp;
}


void WS2812_init()
{
    WS2812_reset();
}


void WS2812_update()
{
    _delay_us(60);
}


void WS2812_reset()
{
    WS2812_set_common_colour_on_all_LEDs(0, 0, 0);
}


void WS2812_send_data(unsigned char r, unsigned char g, unsigned char b)
{
    unsigned char s = number_of_bits;

    unsigned long value = 0x00000000;

    value = (((unsigned long)g << 16) | ((unsigned long)r << 8) | ((unsigned long)b));

    while(s > 0)
    {
       if((value & 0x800000) != LOW)
       {
           SPDR = one;
		   while(!(SPSR & (1<<SPIF)));
		   asm("nop");
           asm("nop");
       }

       else
       {
           SPDR = zero;
	       while(!(SPSR & (1<<SPIF)));
       }

       value <<= 1;
       s--;
    }
}


void WS2812_set_common_colour_on_all_LEDs(unsigned char r, unsigned char g, unsigned char b)
{
    signed int n = (number_of_LEDs - 1);

    while(n > -1)
    {
        LED_colours[n][0] = r;
        LED_colours[n][1] = g;
        LED_colours[n][2] = b;
        WS2812_send_data(LED_colours[n][0], LED_colours[n][1], LED_colours[n][2]);
        n--;
    }

    WS2812_update();
}


void WS2812_set_colour_on_channel(unsigned int channel, unsigned char r, unsigned char g, unsigned char b)
{
    unsigned int n = 0;

    LED_colours[channel][0] = r;
    LED_colours[channel][1] = g;
    LED_colours[channel][2] = b;

    for(n = 0; n < number_of_LEDs; n++)
    {
        WS2812_send_data(LED_colours[n][0], LED_colours[n][1], LED_colours[n][2]);
    }

    WS2812_update();
}


void WS2812_set_colour_xy(signed int x_pos, signed int y_pos, unsigned char r, unsigned char g, unsigned char b)
{
    unsigned int channel = 0;

    channel = (x_pos << 0x04);

    if((x_pos % 2) == 0)
    {
        channel += y_pos;
    }
    else
    {
        channel += (0x0F - y_pos);
    }

    WS2812_set_colour_on_channel(channel, r, g, b);
}


void WS2812_Draw_Line(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char r, unsigned char g, unsigned char b)
{
    signed int dx = 0;
    signed int dy = 0;
    signed int stepx = 0;
    signed int stepy = 0;
    signed int fraction = 0;

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

    WS2812_set_colour_xy(x1, y1, r, g, b);

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

            WS2812_set_colour_xy(x1, y1, r, g, b);
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

            WS2812_set_colour_xy(x1, y1, r, g, b);
        }
    }
}


void WS2812_Draw_V_Line(signed int x1, signed int y1, signed int y2, unsigned char r, unsigned char g, unsigned char b)
{
    if(y1 > y2)
    {
       swap(&y1, &y2);
    }

    while(y2 > (y1 - 1))
    {
        WS2812_set_colour_xy(x1, y2, r, g, b);
        y2--;
    }
}


void WS2812_Draw_H_Line(signed int x1, signed int x2, signed int y1, unsigned char r, unsigned char g, unsigned char b)
{
    if(x1 > x2)
    {
       swap(&x1, &x2);
    }

    while(x2 > (x1 - 1))
    {
        WS2812_set_colour_xy(x2, y1, r, g, b);
        x2--;
    }
}


void WS2812_Draw_Rectangle(signed int x1, signed int y1, signed int x2, signed int y2, unsigned char fill, unsigned char r, unsigned char g, unsigned char b)
{
     unsigned short i = 0;
     unsigned short xmin = 0;
     unsigned short xmax = 0;
     unsigned short ymin = 0;
     unsigned short ymax = 0;

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
               WS2812_set_colour_xy(xmin, i, r, g, b);
           }
         }
     }

     else
     {
        WS2812_Draw_Line(x1, y1, x2, y1, r, g, b);
        WS2812_Draw_Line(x1, y2, x2, y2, r, g, b);
        WS2812_Draw_Line(x1, y1, x1, y2, r, g, b);
        WS2812_Draw_Line(x2, y1, x2, y2, r, g, b);
     }
}


void WS2812_Draw_Triangle(signed int x1, signed int y1, signed int x2, signed int y2, signed int x3, signed int y3, unsigned char fill, unsigned char r, unsigned char g, unsigned char b)
{
    signed int a = 0;
    signed int d = 0;
    signed int sa = 0;
    signed int sb = 0;
    signed int yp = 0;
    signed int last = 0;
    signed int dx12 = 0;
    signed int dx23 = 0;
    signed int dx13 = 0;
    signed int dy12 = 0;
    signed int dy23 = 0;
    signed int dy13 = 0;

    switch(fill)
    {
        case YES:
        {
            if(y1 > y2)
            {
                swap(&y1, &y2);
                swap(&x1, &x2);
            }
            if(y2 > y3)
            {
                swap(&y3, &y2);
                swap(&x3, &x2);
            }
            if(y1 > y2)
            {
                swap(&y1, &y2);
                swap(&x1, &x2);
            }

            if(y1 == y3)
            {
                a = d = x1;

                if(x2 < a)
                {
                    a = x2;
                }
                else if(x2 > d)
                {
                    d = x2;
                }
                if(x2 < a)
                {
                    a = x3;
                }
                else if(x3 > d)
                {
                    d = x3;
                }

                WS2812_Draw_H_Line(a, (a + (d - (a + 1))), y1, r, g, b);
                return;
            }

            dx12 = (x2 - x1);
            dy12 = (y2 - y1);
            dx13 = (x3 - x1);
            dy13 = (y3 - y1);
            dx23 = (x3 - x2);
            dy23 = (y3 - y2);
            sa = 0,
            sb = 0;

            if(y2 == y3)
            {
                last = y2;
            }
            else
            {
                last = (y2 - 1);
            }

            for(yp = y1; yp <= last; yp++)
            {
                a = (x1 + (sa / dy12));
                d = (x1 + (sb / dy13));
                sa += dx12;
                sb += dx13;
                if(a > d)
                {
                    swap(&a, &d);
                }
                WS2812_Draw_H_Line(a, (a + (d - (a + 1))), yp, r, g, b);
            }

            sa = (dx23 * (yp - y2));
            sb = (dx13 * (yp - y1));
            for(; yp <= y3; yp++)
            {
                a = (x2 + (sa / dy23));
                d = (x1 + (sb / dy13));
                sa += dx23;
                sb += dx13;

                if(a > d)
                {
                    swap(&a, &d);
                }
                WS2812_Draw_H_Line(a, (a + (d - (a + 1))), yp, r, g, b);
            }

            break;
        }
        default:
        {
            WS2812_Draw_Line(x1, y1, x2, y2, r, g, b);
            WS2812_Draw_Line(x2, y2, x3, y3, r, g, b);
            WS2812_Draw_Line(x3, y3, x1, y1, r, g, b);

            break;
        }
    }
}


void WS2812_Draw_Circle(signed int xc, signed int yc, signed int radius, unsigned char fill, unsigned char r, unsigned char g, unsigned char b)
{
   signed int a = 0;
   signed int d = 0;
   signed int p = 0;

   d = radius;
   p = (1 - d);

   do
   {    switch(fill)
        {
            case YES:
            {
                WS2812_Draw_H_Line((xc - a), (xc + a), (yc + d), r, g, b);
                WS2812_Draw_H_Line((xc - a), (xc + a), (yc - d), r, g, b);
                WS2812_Draw_H_Line((xc - d), (xc + d), (yc + a), r, g, b);
                WS2812_Draw_H_Line((xc - d), (xc + d), (yc - a), r, g, b);
                break;
            }
            
            default:
            {
                WS2812_set_colour_xy((xc + a), (yc + d), r, g, b);
                WS2812_set_colour_xy((xc + d), (yc + a), r, g, b);
                WS2812_set_colour_xy((xc - a), (yc + d), r, g, b);
                WS2812_set_colour_xy((xc - d), (yc + a), r, g, b);
                WS2812_set_colour_xy((xc + d), (yc - a), r, g, b);
                WS2812_set_colour_xy((xc + a), (yc - d), r, g, b);
                WS2812_set_colour_xy((xc - a), (yc - d), r, g, b);
                WS2812_set_colour_xy((xc - d), (yc - a), r, g, b);
              
                break;
            }
        }

        if(p < 0)
        {
           p += (3 + (2 * a++));
        }
        else
        {
           p += (5 + (2 * ((a++) - (d--))));
        }
    }while(a <= d);
}