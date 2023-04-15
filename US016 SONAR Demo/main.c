#include "TM1637.c"


#define HIGH                    1
#define LOW                     0

#define US016_RANGE_select      PINB0_bit

#define US016_3m_range          HIGH
#define US016_1m_range          LOW


void setup(void);
unsigned int ADC_avg(void);
unsigned int US016_get_distance(void);
void TM1637_print(unsigned int value);


void main(void)
{
   unsigned int r = 0x0000;
   
   setup();
   
   while(1)
   {
       r = US016_get_distance();
       TM1637_print(r);
       delay_ms(200);
   };
}


void setup(void)
{
  CLKPR = 0x80;
  CLKPR = 0x00;
  PORTB = 0x00;
  DDRB = 0x19;
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
  ADCSRA = 0x00;
  
  ADC_Init();
  TM1637_init();
}


unsigned int ADC_avg(void)
{
  signed char samples = 0x08;
  unsigned int avg = 0x0000;
  
  while(samples > 0x00)
  {
     avg += ADC_Read(1);
     delay_us(10);
     samples--;
  };
  
  avg >>= 3;
    
  return avg;
}


unsigned int US016_get_distance(void)
{
  unsigned int d = 0x0000;
  
  US016_RANGE_select = US016_1m_range;
  
  d = ADC_avg();

  if(d >= 1000)
  {
     US016_RANGE_select = US016_3m_range;

     d = (3 * ADC_avg());
  }

  return d;
}


void TM1637_print(unsigned int value)
{
  TM1637_display_segments(0, seg_data[(value / 1000)], 0);
  TM1637_display_segments(1, seg_data[(value % 1000) / 100], 0);
  TM1637_display_segments(2, seg_data[(value % 100) / 10], 0);
  TM1637_display_segments(3, seg_data[(value % 10)], 0);
}