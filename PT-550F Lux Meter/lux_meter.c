#include "MAX72xx.c"


#define ADC_VREF_TYPE           0x00
#define LED                     OCR0A


void setup();
unsigned int read_adc(unsigned char input_pin);
unsigned int adc_avg(unsigned char adc_channel);


void main() 
{
     unsigned int lux = 0;
     unsigned char pwm = 0;
     
     setup();
     while(1)
     {
             lux = adc_avg(2);
             lux *= 60;
             MAX72xx_write(DIG3, ((lux / 1000) % 10));
             MAX72xx_write(DIG2, ((lux / 100) % 10));
             MAX72xx_write(DIG1, ((lux / 10) % 10));
             MAX72xx_write(DIG0, (lux % 10));
             pwm = (lux >> 8);
             LED = pwm;
             delay_ms(100);
     };
}


void setup()
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    PORTB = 0x00;
    DDRB = 0x0F;
    TCCR0A = 0xC3;
    TCCR0B = 0x03;
    TCNT0 = 0x00;
    OCR0A = 0x00;
    OCR0B = 0x00;
    GIMSK = 0x00;
    MCUCR = 0x00;
    TIMSK0 = 0x00;
    ACSR = 0x80;
    ADCSRB = 0x00;
    DIDR0 = 0x00;
    DIDR0 &= 0x03;
    DIDR0 |= 0x20;
    ADMUX = (ADC_VREF_TYPE & 0xFF);
    ADCSRA = 0xA4;
    ADCSRB &= 0xF8;
    MAX72xx_init();
}


unsigned int read_adc(unsigned char input_pin)
{
    unsigned int temp = 0;
    unsigned int adc_res = 0;
    
    ADMUX = input_pin | (ADC_VREF_TYPE & 0xFF);
    delay_us(10);
    ADCSRA |= 0x40;
    while(!(ADCSRA & 0x10));
    ADCSRA |= 0x10;
    adc_res = ADCL;
    temp = ADCH;
    temp <<= 8;
    adc_res += temp;
    
    return adc_res;
}


unsigned int adc_avg(unsigned char adc_channel)
{
   unsigned char samples = 64;
   unsigned int avg = 0;
   
   while(samples > 0)
   {
       avg += read_adc(adc_channel);
       delay_us(10);
       samples--;
   };
   
   avg >>= 6;
   
   return avg;
}