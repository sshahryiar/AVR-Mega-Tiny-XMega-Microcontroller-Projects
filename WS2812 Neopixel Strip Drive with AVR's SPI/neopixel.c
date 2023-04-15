/*

Author: Shawon M. Shahryiar
Date: 16.11.2016

MCU = ATMega328P @ 16MHz crystal oscilator
Fuses: Low = 0xFF, High = 0xDF
Board = Arduino Nano
WS2812 = Adafruit's Neopixel Strip
Interface = SPI (only MOSI)

*/


#include "WS2812.c"

void setup();


void main()
{
     unsigned char i = 0x00;

     setup();

     while(1)
     {
         //All R

         WS2812_set_common_colour_on_all_LEDs(200, 0, 0);
         delay_ms(600);

         //All G

         WS2812_set_common_colour_on_all_LEDs(0, 200, 0);
         delay_ms(600);

         //All B

         WS2812_set_common_colour_on_all_LEDs(0, 0, 200);
         delay_ms(600);

         //Random Burst

         for(i = 0; i <= 99; i++)
         {
             WS2812_send_data(0, 0, TCNT0);
             WS2812_send_data((255 - TCNT0), 0, 127);
             WS2812_send_data(90, 60, TCNT2);
             WS2812_send_data(45, 95, (255 - TCNT2));
             WS2812_send_data(110, TCNT2, TCNT0);
             WS2812_send_data(35, TCNT0, TCNT2);
             WS2812_send_data(TCNT2, 25, TCNT0);
             WS2812_send_data(TCNT0, 66, TCNT2);
             delay_ms(100);
         }

         //Traffic Light

          WS2812_send_data(255, 0, 0);
          WS2812_send_data(0, 0, 0);
          WS2812_send_data(0, 0, 0);
          WS2812_send_data(0, 0, 0);
          WS2812_send_data(0, 0, 0);
          WS2812_send_data(0, 255, 0);
          WS2812_send_data(0, 0, 0);
          WS2812_send_data(0, 0, 0);
          delay_ms(900);
          WS2812_send_data(0, 0, 0);
          WS2812_send_data(255, 255, 0);
          WS2812_send_data(0, 0, 0);
          WS2812_send_data(0, 0, 0);
          WS2812_send_data(0, 0, 0);
          WS2812_send_data(0, 0, 0);
          WS2812_send_data(255, 255, 0);
          WS2812_send_data(0, 0, 0);
          delay_ms(900);
          WS2812_send_data(0, 0, 0);
          WS2812_send_data(0, 0, 0);
          WS2812_send_data(255, 0, 0);
          WS2812_send_data(0, 0, 0);
          WS2812_send_data(0, 0, 0);
          WS2812_send_data(0, 0, 0);
          WS2812_send_data(0, 0, 0);
          WS2812_send_data(0, 255, 0);
          delay_ms(900);

          //Rain Drop
          for(i= 0; i < 9; i++)
          {
              WS2812_send_data(255, 255, 255);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              delay_ms(60);
              WS2812_send_data(255, 255, 255);
              WS2812_send_data(255, 255, 255);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              delay_ms(60);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(255, 255, 255);
              WS2812_send_data(255, 255, 255);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              delay_ms(60);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(255, 255, 255);
              WS2812_send_data(255, 255, 255);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              delay_ms(60);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(255, 255, 255);
              WS2812_send_data(255, 255, 255);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              delay_ms(60);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(255, 255, 255);
              WS2812_send_data(255, 255, 255);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              delay_ms(60);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(255, 255, 255);
              WS2812_send_data(255, 255, 255);
              WS2812_send_data(0, 0, 0);
              delay_ms(60);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(255, 255, 255);
              WS2812_send_data(255, 255, 255);
              delay_ms(60);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(0, 0, 0);
              WS2812_send_data(255, 255, 255);
              delay_ms(60);
              WS2812_reset();
          }

          //Colours on Individual LEDs

          WS2812_send_data(255, 0, 0);
          WS2812_send_data(0, 255, 0);
          WS2812_send_data(0, 0, 255);
          WS2812_send_data(255, 255, 0);
          WS2812_send_data(0, 255, 255);
          WS2812_send_data(255, 0, 255);
          WS2812_send_data(0, 0, 0);
          WS2812_send_data(255, 255, 255);
          delay_ms(3000);
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