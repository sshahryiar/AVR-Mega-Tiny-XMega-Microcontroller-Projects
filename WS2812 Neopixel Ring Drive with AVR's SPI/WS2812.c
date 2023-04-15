#include "WS2812.h"


void WS2812_init()
{
    SPI1_Init_Advanced(_SPI_MASTER, _SPI_FCY_DIV2, _SPI_CLK_HI_TRAILING);
    delay_ms(10);
    WS2812_reset();
}


void WS2812_update()
{
    delay_us(60);
}


void WS2812_reset()
{
    WS2812_set_common_colour_on_all_LEDs(0, 0, 0);
}


void WS2812_set_common_colour_on_all_LEDs(unsigned char r, unsigned char g, unsigned char b)
{
    unsigned int n = 0;

    for(n = 0; n < number_of_LEDs; n++)
    {
        LED_colours[n][0] = r;
        LED_colours[n][1] = g;
        LED_colours[n][2] = b;
        WS2812_send_data(LED_colours[n][0], LED_colours[n][1], LED_colours[n][2]);
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


void WS2812_send_data(unsigned char r, unsigned char g, unsigned char b)
{
    unsigned char s = number_of_bits;

    unsigned long value = 0x00000000;

    value = (((unsigned long)g << 16) | ((unsigned long)r << 8) | ((unsigned long)b));

    while(s > 0)
    {
       if((value & 0x800000) != LOW)
       {
           SPI1_Write(one);
           asm nop;
           asm nop;
       }

       else
       {
           SPI1_Write(zero);
       }

       value <<= 1;
       s--;
    }
}