#include "background.c"


#define rad_per_deg        0.017453292


sbit GLCD_RS  at PORTD6_bit;
sbit GLCD_RW  at PORTD5_bit;
sbit GLCD_EN  at PORTD4_bit;
sbit GLCD_CS2 at PORTC4_bit;
sbit GLCD_CS1 at PORTC5_bit;
sbit GLCD_RST at PORTC6_bit;

sbit GLCD_RS_Direction  at DDD6_bit;
sbit GLCD_RW_Direction  at DDD5_bit;
sbit GLCD_EN_Direction  at DDD4_bit;
sbit GLCD_CS2_Direction at DDC4_bit;
sbit GLCD_CS1_Direction at DDC5_bit;
sbit GLCD_RST_Direction at DDC6_bit;

unsigned char GLCD_DataPort at PORTB;
unsigned char GLCD_DataPort_Direction at DDRB;


const unsigned char step_table[8] = {0x90, 0x80, 0xC0, 0x40, 0x60, 0x20, 0x30, 0x10};


void setup();
unsigned int adc_avg();
void motor_move(unsigned char i);
float map(float v, float x_min, float x_max, float y_min, float y_max);
float constrain(float value, float value_min, float value_max);


void main() 
{
     bit dir;
     
     unsigned char s = 1;
     signed char h1 = 0;
     signed char v1 = 0;
     signed char h2 = 0;
     signed char v2 = 0;
     
     unsigned int v = 0;
     signed int deg = 0;
     signed int steps = 0;

     float d = 0.0;

     dir = 0;
     
     setup();
     
     while(1)
     {
            v = adc_avg();
            d = ((0.0009 * v * v) - (v * 0.6367) + 119.7311);

            v = map(d, 10, 80, 0, 53);
            v = constrain(v, 0, 53);
            
            h1 = (64 + (53 * (cos(deg * rad_per_deg))));
            v1 = (64 - (53 * (sin(deg * rad_per_deg))));
            h2 = (64 + (v * (cos(deg * rad_per_deg))));
            v2 = (64 - (v * (sin(deg * rad_per_deg))));
            
            Glcd_Line(64, 63, h1, v1, 0);
            Glcd_Line(64, 63, h2, v2, 1);
            
            if((dir == 0) && (steps < 2048))
            {
                s++;
                
                if(s > 8)
                {
                   s = 1;
                }
                
                motor_move(s);
                steps++;
                
                if((steps % 11) == 0)
                {
                    Glcd_Line(64, 63, (64 + (53 * (cos((deg + 1) * rad_per_deg)))), (64 - (53 * (sin((deg + 1) * rad_per_deg)))), 0);
                    deg++;
                }

                if(steps == 2048)
                {
                    s = 7;
                    dir = 1;
                    deg = 180;
                    steps = 0;
                }
            }
            if((dir == 1) && (steps < 2048))
            {
                s--;
                if(s < 1)
                {
                   s = 8;
                }
                
                motor_move(s);
                steps++;
                
                if((steps % 11) == 0)
                {
                    Glcd_Line(64, 63, (64 + (53 * (cos((deg - 1) * rad_per_deg)))), (64 - (53 * (sin((deg - 1) * rad_per_deg)))), 0);
                    deg--;
                }

                if(steps == 2048)
                {
                    s = 1;
                    dir = 0;
                    deg = 0;
                    steps = 0;
                }
            }
     };
}


void setup()
{
      PORTA = 0x00;
      DDRA = 0xF0;
      PORTB = 0x00;
      DDRB = 0x00;
      PORTC = 0x00;
      DDRC |= 0x0F;
      PORTD = 0x00;
      DDRD = 0x00;
      TCCR0 = 0x00;
      TCNT0 = 0x00;
      OCR0 = 0x00;
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
      TCCR2 = 0x00;
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
      glcd_init();
      glcd_fill(0x00);
      Glcd_Image(RDR);
}


unsigned int adc_avg()
{
    unsigned char samples = 16;
    unsigned int avg = 0;
    
    while(samples > 0)
    {
        avg += adc_read(0);
        samples--;
    }
    
    avg >>= 4;
    return avg;
}


void motor_move(unsigned char i)
{
     PORTA = step_table[i];
}


float map(float v, float x_min, float x_max, float y_min, float y_max)
{
    return (y_min + (((y_max - y_min)/(x_max - x_min)) * (v - x_min)));
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