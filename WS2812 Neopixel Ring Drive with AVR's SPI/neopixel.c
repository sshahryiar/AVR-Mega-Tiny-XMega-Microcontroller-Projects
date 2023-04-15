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


#define delay1                      40
#define delay2                      20
#define delay3                      60
#define delay4                      90
#define delay5                      160
#define delay6                      120


unsigned char r_value[16] = {30, 45, 60, 75, 90, 105, 120, 135, 150, 165, 180, 195, 210, 225, 240, 255};
unsigned char g_value[16] = {90, 105, 120, 135, 150, 165, 180, 195, 210, 225, 240, 255, 30, 45, 60, 75};
unsigned char b_value[16] = {165, 180, 195, 210, 225, 240, 255, 30, 45, 60, 75, 90, 105, 120, 135, 150};

void setup();


void main()
{
     signed char i = 0x00;

     setup();

     while(1)
     {
             WS2812_reset();
             for(i = 0; i < number_of_LEDs; i++)
             {
                   WS2812_set_colour_on_channel((i - 1), 0, 0, 0);
                   WS2812_set_colour_on_channel(i, 255, 0, 0);
                   delay_ms(delay1);
             }
             
             WS2812_reset();
             for(i = 0; i < number_of_LEDs; i++)
             {
                   WS2812_set_colour_on_channel((i - 1), 0, 0, 0);
                   WS2812_set_colour_on_channel(i, 0, 255, 0);
                   delay_ms(delay1);
             }
             
             WS2812_reset();
             for(i = 0; i < number_of_LEDs; i++)
             {
                   WS2812_set_colour_on_channel((i - 1), 0, 0, 0);
                   WS2812_set_colour_on_channel(i, 0, 0, 255);
                   delay_ms(delay1);
             }
             
             WS2812_reset();
             for(i = 0; i < number_of_LEDs; i++)
             {
                   WS2812_set_colour_on_channel((i - 1), 0, 0, 0);
                   WS2812_set_colour_on_channel(i, 255, 0, 255);
                   delay_ms(delay1);
             }
             
             WS2812_reset();
             for(i = 0; i < number_of_LEDs; i++)
             {
                   WS2812_set_colour_on_channel((i - 1), 0, 0, 0);
                   WS2812_set_colour_on_channel(i, 0, 255, 255);
                   delay_ms(delay1);
             }
             
             WS2812_reset();
             for(i = 0; i < number_of_LEDs; i++)
             {
                   WS2812_set_colour_on_channel((i - 1), 0, 0, 0);
                   WS2812_set_colour_on_channel(i, 255, 255, 0);
                   delay_ms(delay1);
             }
             
             WS2812_reset();
             for(i = 0; i < number_of_LEDs; i++)
             {
                   WS2812_set_colour_on_channel((i - 1), 0, 0, 0);
                   WS2812_set_colour_on_channel(i, 255, 255, 255);
                   delay_ms(delay1);
             }
             
             WS2812_reset();
             for(i = 0; i < number_of_LEDs; i++)
             {
                   WS2812_set_colour_on_channel(i, r_value[i], g_value[i], b_value[i]);
                   delay_ms(90);
             }
             
             delay_ms(4000);
             
             WS2812_reset();
             for(i = 0; i < number_of_LEDs; i++)
             {
                   WS2812_set_colour_on_channel(i, 255, 0, 0);
                   delay_ms(delay2);
             }
             delay_ms(2000);

             WS2812_reset();
             for(i = 0; i < number_of_LEDs; i++)
             {
                   WS2812_set_colour_on_channel(i, 0, 255, 0);
                   delay_ms(delay2);
             }
             delay_ms(2000);

             WS2812_reset();
             for(i = 0; i < number_of_LEDs; i++)
             {
                   WS2812_set_colour_on_channel(i, 0, 0, 255);
                   delay_ms(delay2);
             }
             delay_ms(2000);

             WS2812_reset();
             for(i = 0; i < number_of_LEDs; i++)
             {
                   WS2812_set_colour_on_channel(i, 255, 0, 255);
                   delay_ms(delay2);
             }
             delay_ms(2000);

             WS2812_reset();
             for(i = 0; i < number_of_LEDs; i++)
             {
                   WS2812_set_colour_on_channel(i, 0, 255, 255);
                   delay_ms(delay2);
             }
             delay_ms(2000);

             WS2812_reset();
             for(i = 0; i < number_of_LEDs; i++)
             {
                   WS2812_set_colour_on_channel(i, 255, 255, 0);
                   delay_ms(delay2);
             }
             delay_ms(2000);

             WS2812_reset();
             for(i = 0; i < number_of_LEDs; i++)
             {
                   WS2812_set_colour_on_channel(i, 255, 255, 255);
                   delay_ms(delay2);
             }
             delay_ms(2000);
             
             WS2812_reset();
             WS2812_set_colour_on_channel(0, 255, 10, 30);
             delay_ms(delay3);
             WS2812_set_colour_on_channel(1, 240, 128, 128);
             delay_ms(delay3);
             WS2812_set_colour_on_channel(2, 255, 69, 10);
             delay_ms(delay3);
             WS2812_set_colour_on_channel(3, 255, 215, 10);
             delay_ms(delay3);
             WS2812_set_colour_on_channel(4, 154, 205, 50);
             delay_ms(delay3);
             WS2812_set_colour_on_channel(5, 34, 169, 34);
             delay_ms(delay3);
             WS2812_set_colour_on_channel(6, 50, 205, 50);
             delay_ms(delay3);
             WS2812_set_colour_on_channel(7, 10, 255, 127);
             delay_ms(delay3);
             WS2812_set_colour_on_channel(8, 175, 238, 238);
             delay_ms(delay3);
             WS2812_set_colour_on_channel(9, 10, 225, 255);
             delay_ms(delay3);
             WS2812_set_colour_on_channel(10, 10, 191, 255);
             delay_ms(delay3);
             WS2812_set_colour_on_channel(11, 30, 144, 255);
             delay_ms(delay3);
             WS2812_set_colour_on_channel(12, 10, 10, 205);
             delay_ms(delay3);
             WS2812_set_colour_on_channel(13, 138, 43, 226);
             delay_ms(delay3);
             WS2812_set_colour_on_channel(14, 186, 85, 211);
             delay_ms(delay3);
             WS2812_set_colour_on_channel(15, 218, 112, 214);
             delay_ms(6000);
             
             WS2812_reset();
             for(i = 0; i < number_of_LEDs; i++)
             {
                   WS2812_set_colour_on_channel(i, TCNT0, TCNT2, (TCNT2 | TCNT0));
                   delay_ms(delay4);
             }
             delay_ms(4000);
             
             WS2812_reset();
             for(i = 0; i < 4; i++)
             {
                   WS2812_set_colour_on_channel(i, 190, 190, 190);
                   WS2812_set_colour_on_channel((i + 4), 190, 190, 190);
                   WS2812_set_colour_on_channel((i + 8), 190, 190, 190);
                   WS2812_set_colour_on_channel((i + 12), 190, 190, 190);
                   delay_ms(delay5);
             }
             delay_ms(4000);
             
             WS2812_reset();
             for(i = 0; i < number_of_LEDs; i++)
             {
                   WS2812_set_colour_on_channel(i, 190, 190, 190);
                   delay_ms(delay5);
             }
             for(i = (number_of_LEDs - 1); i > -1; i--)
             {
                   WS2812_set_colour_on_channel(i, 0, 0, 0);
                   delay_ms(delay5);
             }
             delay_ms(600);
             
             WS2812_reset();
             for(i = 0; i < number_of_LEDs; i++)
             {
                   WS2812_set_colour_on_channel(i, 190, 190, 190);
                   delay_ms(delay5);
             }
             for(i = 0; i < number_of_LEDs; i++)
             {
                   WS2812_set_colour_on_channel(i, 0, 0, 0);
                   delay_ms(delay5);
             }
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