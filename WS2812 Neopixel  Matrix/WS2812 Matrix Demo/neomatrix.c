/*

Author: Shawon M. Shahryiar
Date: 28.12.2016

MCU = ATMega328P @ 16MHz crystal oscilator
Fuses: Low = 0xFF, High = 0xDF
Board = Arduino Nano
WS2812 = Neopixel Ring
Interface = SPI (only MOSI)

*/


#include "WS2812.c"


void setup();


void main()
{
   signed char i = 0;
   signed char j = 0;

   setup();

   WS2812_set_common_colour_on_all_LEDs(200, 0, 0);
   delay_ms(600);
   WS2812_set_common_colour_on_all_LEDs(0, 200, 0);
   delay_ms(600);
   WS2812_set_common_colour_on_all_LEDs(0, 0, 200);
   delay_ms(600);
   WS2812_set_common_colour_on_all_LEDs(180, 180, 180);
   delay_ms(600);
   WS2812_Draw_Line(0, 0, 15, 15, 240, 0, 0);
   WS2812_Draw_Line(0, 15, 15, 0, 240, 0, 0);
   delay_ms(2400);
   WS2812_reset();
   WS2812_set_common_colour_on_all_LEDs(160, 0, 0);
   WS2812_Draw_Triangle(0, 0, 0, 15, 15, 7, NO, 0, 0, 180);
   delay_ms(2400);
   WS2812_reset();
   WS2812_Draw_Rectangle(2, 2, 14, 13, YES, 0, 160, 0);
   WS2812_Draw_Circle(8, 7, 2, YES, 190, 0, 0);
   delay_ms(2400);
   WS2812_reset();
   
   while(1)
   {
       for(i = 0; i < 8; i += 2)
       {
           WS2812_Draw_Circle(7, 7, i, NO, 20, 60, 190);
           delay_ms(400);
       }
       delay_ms(1000);
       
       WS2812_reset();

       for(i = 0; i < 16; i += 2)
       {
           WS2812_Draw_V_Line(i, 0, 15, 32, 64, 160);
           delay_ms(400);
       }
       for(i = 0; i < 16; i += 2)
       {
           WS2812_Draw_H_Line(0, 15, i, 64, 32, 160);
           delay_ms(400);
       }
       delay_ms(1000);

       WS2812_reset();

       for(i = 0; i < 16; i += 2)
       {
           WS2812_Draw_Rectangle(i, i, (15 - i), (15 - i), NO, 64, 128, 32);
           delay_ms(400);
       }
       delay_ms(1000);
       
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


void setup()
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    PORTB = 0x00;
    DDRB = 0x28;
    PORTC = 0x00;
    DDRC = 0x00;
    PORTD = 0x00;
    DDRD = 0x00;
    TCCR0A = 0x00;
    TCCR0B = 0x05;
    TCNT0 = 0x00;
    OCR0A = 0x00;
    OCR0B = 0x00;
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
    ASSR = 0x00;
    TCCR2A = 0x00;
    TCCR2B = 0x06;
    TCNT2 = 0x00;
    OCR2A = 0x00;
    OCR2B = 0x00;
    EICRA = 0x00;
    EIMSK = 0x00;
    PCICR = 0x00;
    TIMSK0 = 0x00;
    TIMSK1 = 0x00;
    TIMSK2 = 0x00;
    UCSR0B = 0x00;
    ACSR = 0x80;
    ADCSRB = 0x00;
    DIDR1 = 0x00;
    ADCSRA = 0x00;
    SPCR = 0x00;
    TWCR = 0x00;

    WS2812_init();
}