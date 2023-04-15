#include "TM1637.c"


void setup(void);
signed int read_temp_channel(void);
signed int ADC_avg(signed int *values);
signed int get_temperature(signed int val);


void main(void)
{
   unsigned short done = 0x00;
   signed char samples = 0x00;
   signed int buf[16];
   
   signed int t = 0x0000;
   
   setup();
   
   while(1)
   {
       switch(done)
       {
           case 1:
           {
             TM1637_display_segments(0, seg_data[(t / 10)], 0);
             TM1637_display_segments(1, seg_data[(t % 10)], 0);
             TM1637_display_segments(2, 0x63, 0);
             TM1637_display_segments(3, 0x39, 0);
             
             done  = 0;
             
             break;
           }
           
           default:
           {
             buf[samples] = read_temp_channel();
             samples++;
             
             if(samples >= 16)
             {
               t = ADC_avg(buf);
               t = get_temperature(t);
               
               done = 1;
               samples = 0;
             }
             
             break;
           }
       }
       
       delay_ms(60);
   };
}


void setup(void)
{
  CLKPR = 0x80;
  CLKPR = 0x00;
  PORTB = 0x00;
  DDRB = 0x18;
  TCCR0A = 0x00;
  TCCR0B = 0x00;
  TCNT0 = 0x00;
  OCR0A = 0x00;
  OCR0B = 0x00;
  PLLCSR = 0x00;
  TCCR1 = 0x00;
  GTCCR = 0x00;
  TCNT1 = 0x00;
  OCR1A = 0x00;
  OCR1B = 0x00;
  OCR1C = 0x00;
  GIMSK = 0x00;
  MCUCR = 0x00;
  TIMSK = 0x00;
  USICR = 0x00;
  ACSR = 0x80;
  ADCSRB = 0x00;
  DIDR0 = 0x00;
  ADMUX = 0x80;
  ADCSRA = 0xA4;
  ADCSRB = 0x00;

  TM1637_init();
  
  TM1637_display_segments(0, 0x77, 0);
  TM1637_display_segments(1, 0x78, 0);
  TM1637_display_segments(2, 0x66, 0);
  TM1637_display_segments(3, 0x6D, 0);
  delay_ms(1000);
  
  TM1637_clear();
}


signed int read_temp_channel(void)
{
    signed int adc_res = 0;

    ADMUX = 0xCF;
    delay_us(10);
    ADCSRA |= 0x40;
    
    while ((ADCSRA & 0x10) == 0);
    ADCSRA |= 0x10;
    
    adc_res = ((ADCH << 8) | ADCL);

    return adc_res;
}


signed int ADC_avg(signed int *values)
{
    signed char s = 16;
    signed int avg = 0x0000;
    
    while(s > 0x00)
    {
        avg += values[s];
        s--;
    };
    
    return (avg >> 4);
}


signed int get_temperature(signed int val)
{
    return ((signed int)(((float)val * 0.0811) - 18.89));
}
