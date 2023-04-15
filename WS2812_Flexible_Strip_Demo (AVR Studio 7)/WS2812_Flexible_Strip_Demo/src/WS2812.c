#define F_CPU 16000000UL 


#include "WS2812.h"
#include "SPI.h"
#include <util/delay.h>


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