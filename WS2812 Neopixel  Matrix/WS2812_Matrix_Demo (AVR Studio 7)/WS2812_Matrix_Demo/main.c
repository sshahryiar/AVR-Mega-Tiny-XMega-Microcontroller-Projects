#define F_CPU 16000000UL 

#include <atmel_start.h>
#include <util/delay.h>
#include "WS2812.h"


int main(void)
{
   signed char i = 0;
   signed char j = 0;
   
   atmel_start_init();
   WS2812_init();

   WS2812_set_common_colour_on_all_LEDs(200, 0, 0);
   _delay_ms(600);
   WS2812_set_common_colour_on_all_LEDs(0, 200, 0);
   _delay_ms(600);
   WS2812_set_common_colour_on_all_LEDs(0, 0, 200);
   _delay_ms(600);
   WS2812_set_common_colour_on_all_LEDs(180, 180, 180);
   _delay_ms(600);
   WS2812_Draw_Line(0, 0, 15, 15, 240, 0, 0);
   WS2812_Draw_Line(0, 15, 15, 0, 240, 0, 0);
   _delay_ms(2400);
   WS2812_reset();
   WS2812_set_common_colour_on_all_LEDs(160, 0, 0);
   WS2812_Draw_Triangle(0, 0, 0, 15, 15, 7, NO, 0, 0, 180);
   _delay_ms(2400);
   WS2812_reset();
   WS2812_Draw_Rectangle(2, 2, 14, 13, YES, 0, 160, 0);
   WS2812_Draw_Circle(8, 7, 2, YES, 190, 0, 0);
   _delay_ms(2400);
   WS2812_reset();
   
   while(1)
   {
       for(i = 0; i < 8; i += 2)
       {
           WS2812_Draw_Circle(7, 7, i, NO, 20, 60, 190);
           _delay_ms(400);
       }
       _delay_ms(1000);
       
       WS2812_reset();

       for(i = 0; i < 16; i += 2)
       {
           WS2812_Draw_V_Line(i, 0, 15, 32, 64, 160);
           _delay_ms(400);
       }
       for(i = 0; i < 16; i += 2)
       {
           WS2812_Draw_H_Line(0, 15, i, 64, 32, 160);
           _delay_ms(400);
       }
       _delay_ms(1000);

       WS2812_reset();

       for(i = 0; i < 16; i += 2)
       {
           WS2812_Draw_Rectangle(i, i, (15 - i), (15 - i), NO, 64, 128, 32);
           _delay_ms(400);
       }
       _delay_ms(1000);
       
       for(j = 0; j < 4; j++)
       {
           WS2812_set_common_colour_on_all_LEDs(160, 60, 0);
           for(i = 0; i < 99; i++)
           {
              WS2812_set_colour_on_channel((rand() >> 7), 220, 90, 9);
           }
       }
       
       WS2812_reset();
       
       for(j = 0; j < 4; j++)
       {
           i = 15;
           while(i > -1)
           {
               WS2812_Draw_V_Line(i, 0, 15, 0, 0, 0);
               WS2812_Draw_V_Line(i, 0, 15, (rand() >> 7), (rand() >> 7), (rand() >> 7));
               i--;
           }
       }
       
       WS2812_reset();
       
       for(j = 0; j < 99; j++)
       {
           for(i = 0; i < 99; i++)
           {
               WS2812_set_colour_on_channel((rand() >> 7), (rand() >> 7), (rand() >> 7), (rand() >> 7));
           }
       }
       
       WS2812_reset();
   }
}
