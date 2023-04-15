#include "lcd.c"


#define VDD                     5.0
#define ADC_Max                 1023.0
#define fixed_R                 10000.0
#define amp_scalar              1000000.0



void setup();
unsigned int adc_avg();
float get_voltage(unsigned int adc_counts);
float voltage_to_current_converter(float volts);
unsigned int current_to_lux_converter(unsigned int I);


void main() 
{
     unsigned char txt[6];
     float v = 0.0;
     unsigned int lux = 0;
     
     setup();
     
     LCD_goto(4, 1);
     LCD_putstr("Lux Meter");
     LCD_goto(1, 2);
     LCD_putstr("Light/Lux:");
     
     while(1)
     {
         v = adc_avg();
         v = get_voltage(v);
         v = voltage_to_current_converter(v);
         lux = current_to_lux_converter(v);

         WordToStr(lux, txt);
         LCD_goto(12, 2);
         LCD_putstr(txt);
         delay_ms(200);
     };
}


void setup()
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    PORTB = 0x00;
    DDRB = 0x00;
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
    LCD_init();
}


unsigned int adc_avg()
{
    unsigned char samples = 64;
    unsigned int avg = 0;
    
    while(samples > 0)
    {
        avg += ADC_Get_Sample(1);
        delay_us(10);
        samples--;
    };
    
    avg >>= 6;
    
    return avg;
}


float get_voltage(unsigned int adc_counts)
{
    float V_ADC = 0.0;
    
    V_ADC = (adc_counts * VDD);
    V_ADC /= ADC_Max;
    
    return V_ADC;
}


float voltage_to_current_converter(float volts)
{
    float V_ADC = 0.0;
    
    V_ADC = (volts / fixed_R);
    V_ADC *= amp_scalar;
    
    return V_ADC;
}


unsigned int current_to_lux_converter(unsigned int I)
{
    unsigned int L = 0;
    
    L = (I << 1);
    
    return L;
}