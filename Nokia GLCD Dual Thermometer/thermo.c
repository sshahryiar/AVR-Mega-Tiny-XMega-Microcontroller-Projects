#include "3310.h"
#include "background.h"
#include <all.h>


void setup();
void draw_background();
double map(double v, float x_min, float x_max, float y_min, float y_max);
float constrain(float value, float value_min, float value_max);
float adc_avg(unsigned char channel);
void send_to_lcd(unsigned char x, unsigned char y, float value);


void main()
{
     unsigned char l1_present = 0;
     unsigned char l1_previous = 0;
     unsigned char l2_present = 0;
     unsigned char l2_previous = 0;
     float t1 = 0.0;
     float t2 = 0.0;
     setup();
     while(1)
     {
             l1_present = adc_avg(0);
             l1_present = constrain(l1_present, 0, 120);
             l1_present = map(l1_present, 0, 120, 0, 24);
             t1 = map(adc_avg(0), 0, 1023, 0, 512);
             t1 = constrain(t1, 0, 60);
             
             l2_present = adc_avg(1);
             l2_present = constrain(l2_present, 0, 120);
             l2_present = map(l2_present, 0, 120, 0, 24);
             t2 = map(adc_avg(1), 0, 1023, 0, 512);
             t2 = constrain(t2, 0, 60);
             
             if(l1_present != l1_previous)
             {
                           drawLine(15, (28 - l1_previous), 15, 28, 0);
                           drawLine(15, (28 - l1_present), 15, 28, 1);
                           drawLine(15, 31, 15, 28, 1);
                           drawLine(15, 2, 15, 2, 1);

             }
             if(l2_present != l2_previous)
             {
                           drawLine(69, 28, 69, (28 - l2_previous), 0);
                           drawLine(69, 28, 69, (28 - l2_present), 1);
                           drawLine(69, 31, 69, 28, 1);
                           drawLine(69, 2, 69, 2, 1);
             }
             
             l1_previous = l1_present;
             l2_previous = l2_present;

             send_to_lcd(2, 5, t1);
             send_to_lcd(54, 5, t2);
     }
}


void setup()
{
   CLKPR = 0x80;
   CLKPR = 0x00;
   DDRB = 0xFF;
   PORTB = 0x00;
   DDRC = 0x00;
   PORTC = 0x00;
   DDRD = 0x00;
   PORTD = 0x00;
   TCCR0A = 0x00;
   TCCR0B = 0x00;
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
   TCCR2B = 0x00;
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
   nokia_init();
   delay_ms(10);
   nokia_clear_screen();
   delay_ms(10);
   nokia_clean_ddram();
   delay_ms(10);
   draw_background();
   adc_init();
}


void draw_background()
{
   unsigned int i = 0;
   nokia_clean_ddram();
   nokia_clear_screen();
   nokia_gotoxy(0, 0);
   for(i = 0; i < 504; i++)
   {
        nokia_write_data((temp[i]));
   }
   delay_ms(20);
}


double map(double v, float x_min, float x_max, float y_min, float y_max)
{
    double m = 0.0;
    m = ((y_max - y_min)/(x_max - x_min));
    return (y_min + (m * (v - x_min)));
}


float constrain(float value, float value_min, float value_max)
{
      if(value >= value_max)
      {
           return value_max;
      }
      else if(value <= value_min)
      {
           return value_min;
      }
      else
      {
           return value;
      }
}


float adc_avg(unsigned char channel)
{
         unsigned int samples = 0;
         unsigned long tmp = 0;
         float avg = 0.0;
         while(samples < 128)
         {
             tmp += adc_read(channel);
             delay_us(4);
             samples++;
         }
         tmp >>= 7;
         avg = tmp;
         avg = (avg / 1.5152);
         return avg;
}


void send_to_lcd(unsigned char x, unsigned char y, float value)
{
     unsigned int tmp = 0;
     unsigned char ch = 0;
     
     if(value < 10)
     {
         tmp = (value * 1000);
         ch = (tmp / 1000);
         nokia_gotoxy(x, y);
         nokia_printchar((48 + ch));
         nokia_gotoxy((x + 7), y);
         nokia_printchar(46);
         ch = ((tmp / 100) % 10);
         nokia_gotoxy((x + 15), y);
         nokia_printchar((48 + ch));
         ch = ((tmp / 10) % 10);
         nokia_gotoxy((x + 23), y);
         nokia_printchar((48 + ch));
     }
     if(value >= 10 && value < 100)
     {
        tmp = (value * 100);
        ch = (tmp / 1000);
        nokia_gotoxy(x, y);
        nokia_printchar((48 + ch));
        ch = ((tmp / 100) % 10);
        nokia_gotoxy((x + 7), y);
        nokia_printchar((48 + ch));
        nokia_gotoxy((x + 15), y);
        nokia_printchar(46);
        ch = ((tmp / 10) % 10);
        nokia_gotoxy((x + 23), y);
        nokia_printchar((48 + ch));
     }
}