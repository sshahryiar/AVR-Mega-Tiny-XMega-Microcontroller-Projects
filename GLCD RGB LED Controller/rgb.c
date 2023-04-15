#include "background.h"


sbit GLCD_RS  at PORTB2_bit;
sbit GLCD_RW  at PORTB3_bit;
sbit GLCD_EN  at PORTB4_bit;
sbit GLCD_CS2 at PORTB5_bit;
sbit GLCD_CS1 at PORTB6_bit;
sbit GLCD_RST at PORTB7_bit;

sbit GLCD_RS_Direction  at DDB2_bit;
sbit GLCD_RW_Direction  at DDB3_bit;
sbit GLCD_EN_Direction  at DDB4_bit;
sbit GLCD_CS2_Direction at DDB5_bit;
sbit GLCD_CS1_Direction at DDB6_bit;
sbit GLCD_RST_Direction at DDB7_bit;

unsigned char GLCD_DataPort at PORTC;
unsigned char GLCD_DataPort_Direction at DDRC;


unsigned char r_text[6];
unsigned char g_text[6];
unsigned char b_text[6];

unsigned char r = 0;
unsigned char g = 0;
unsigned char b = 0;


void setup();
float map(float v, float x_min, float x_max, float y_min, float y_max);
unsigned int constrain(unsigned int value, unsigned int value_min, unsigned int value_max);//float constrain(float value, float value_min, float value_max);
unsigned int adc_avg(unsigned char channel);
void display_values();
void draw_slider(unsigned char x_pos, unsigned char y_pos, unsigned char colour);


void main()
{
     signed char pos = 0;
     unsigned char slider = 0;
     unsigned char R_old_position = 0;
     unsigned char G_old_position = 0;
     unsigned char B_old_position = 0;
     unsigned int s = 0;
     unsigned int pwm = 0;
     
     setup();
     while(1)
     {
             s = adc_avg(0);
             if(s >= 600)
             {
                 if(s > 900)
                 {
                      pwm += 10;
                 }
                 else
                 {
                      pwm += 1;
                 }
             }
             if(s <= 400)
             {
                 if(s < 100)
                 {
                      pwm -= 10;
                 }
                 else
                 {
                      pwm -= 1;
                 }
             }
             
             if(adc_avg(1) >= 680)
             {
                    while(adc_avg(1) >= 680);
                    pos++;
                    //pwm = 0;
                    delay_ms(100);
             }
             if(adc_avg(1) <= 340)
             {
                    while(adc_avg(1) <= 340);
                    pos--;
                    //pwm = 0;
                    delay_ms(100);
             }

             if(pos > 3)
             {
                    pos = 0;
             }

             pwm = constrain(pwm, 0, 255);
             slider = map(pwm, 0, 255, 9, 60);
             slider = constrain(slider, 9, 60);
             
             switch(pos)
             {
                  case 1:
                  {
                       Glcd_Write_Text(">", 1, 2, 1);
                       break;
                  }
                  case 2:
                  {
                       Glcd_Write_Text(">", 1, 4, 1);
                       break;
                  }
                  case 3:
                  {
                       Glcd_Write_Text(">", 1, 6, 1);
                       break;
                  }
                  default:
                  {
                       Glcd_Write_Text(" ", 1, 2, 1);
                       Glcd_Write_Text(" ", 1, 4, 1);
                       Glcd_Write_Text(" ", 1, 6, 1);
                       break;
                  }
             }
             
             if((slider != R_old_position) || (slider != G_old_position) || (slider != B_old_position))
             {
                 switch(pos)
                 {
                     case 1:
                     {
                          draw_slider(R_old_position, 17, 0);
                          draw_slider(slider, 17, 1);
                          r = pwm;
                          OCR1AL = r;
                          R_old_position = slider;
                          break;
                     }
                     case 2:
                     {
                          draw_slider(G_old_position, 33, 0);
                          draw_slider(slider, 33, 1);
                          g = pwm;
                          OCR1BL = g;
                          G_old_position = slider;
                          break;
                     }
                     case 3:
                     {
                          draw_slider(B_old_position, 49, 0);
                          draw_slider(slider, 49, 1);
                          b = pwm;
                          OCR2 = b;
                          B_old_position = slider;
                          break;
                     }
                     default:
                     {
                          break;
                     }
                 }
             }
             
             delay_ms(100);
             
             display_values();
     };
}


void setup()
{
      PORTA = 0x00;
      DDRA = 0x00;
      PORTB = 0x00;
      DDRB = 0x00;
      PORTC = 0x00;
      DDRC = 0x00;
      PORTD = 0x00;
      DDRD = 0xB0;
      TCCR0 = 0x00;
      TCNT0 = 0x00;
      OCR0 = 0x00;
      TCCR1A = 0xA1;
      TCCR1B = 0x0A;
      TCNT1H = 0x00;
      TCNT1L=0x00;
      ICR1H = 0x00;
      ICR1L = 0x00;
      OCR1AH = 0x00;
      OCR1AL = 0x00;
      OCR1BH = 0x00;
      OCR1BL = 0x00;
      ASSR = 0x00;
      TCCR2 = 0x6A;
      TCNT2 = 0x00;
      OCR2 = 0x00;
      MCUCR = 0x00;
      MCUCSR = 0x00;
      TIMSK = 0x00;
      UCSRB = 0x00;
      ACSR = 0x80;
      SFIOR = 0x00;
      ADCSRA = 0x00;
      SPCR = 0x00;
      TWCR = 0x00;
      ADC_init();
      Glcd_Init();
      Glcd_Fill(0x00);
      Glcd_Image(image);
      Glcd_Write_Text("R: ", 75, 2, 1);
      Glcd_Write_Text("G: ", 75, 4, 1);
      Glcd_Write_Text("B: ", 75, 6, 1);
      draw_slider(9, 17, 1);
      draw_slider(9, 33, 1);
      draw_slider(9, 49, 1);
}


float map(float v, float x_min, float x_max, float y_min, float y_max)
{
    double m = 0.0;
    m = ((y_max - y_min)/(x_max - x_min));
    return (y_min + (m * (v - x_min)));
}


unsigned int constrain(unsigned int value, unsigned int value_min, unsigned int value_max)
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


unsigned int adc_avg(unsigned char channel)
{
      unsigned char samples = 0;
      unsigned int avg = 0;
      
      while(samples < 64)
      {
          avg += adc_read(channel);
          delay_us(6);
          samples++;
      }
      avg >>= 6;
      return avg;
}



void display_values()
{
     ByteToStr(r, r_text);
     Glcd_Write_Text(r_text, 90, 2, 1);
     ByteToStr(g, g_text);
     Glcd_Write_Text(g_text, 90, 4, 1);
     ByteToStr(b, b_text);
     Glcd_Write_Text(b_text, 90, 6, 1);
     Glcd_Write_Text(" ", 1, 2, 1);
     Glcd_Write_Text(" ", 1, 4, 1);
     Glcd_Write_Text(" ", 1, 6, 1);
     delay_ms(120);
}

void draw_slider(unsigned char x_pos, unsigned char y_pos, unsigned char colour)
{
     Glcd_V_Line(y_pos, (y_pos + 5), x_pos, colour);
     Glcd_H_Line(9, 59, (y_pos + 2), 1);
     Glcd_H_Line(9, 59, (y_pos + 3), 1);
}